#pragma once

#include <array>
#include <cassert>
#include <filesystem>
#include <memory>
#include <ranges>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>


/** !\brief a class that executes a process as a child
 *
 * The constructor expects the list of arguments and the path the child process should use as its working directory
 * The constructor directly executes the child process and waits until it terminates.
 *
 * The function cout(), cerr() can be used to gather information about the output.
 * The function status() can be used to gather the returned process value.
 */
class external_process final {
private:
    static constexpr inline int READ_END = 0;
    static constexpr inline int WRITE_END = 1;


    std::array<int, 2> stdoutpipe;
    std::array<int, 2> stderrpipe;
    int status_;

    std::string stdcout;
    std::string stdcerr;
public:
    external_process(std::vector<std::string> const& prog, std::filesystem::path const& _cwd = std::filesystem::current_path()) {
        int ret1 = pipe(stdoutpipe.data());
        int ret2 = pipe(stderrpipe.data());
        if (ret1 == -1 || ret2 == -1) {
            throw std::runtime_error("couldn't create pipes");
        }

        auto pid = fork();
        if (pid==0) {
            std::filesystem::current_path(_cwd);
            child_process(prog);
        } else {
            parent_process(pid);
        }
    }

    ~external_process() {
        close(stdoutpipe[READ_END]);
        close(stderrpipe[READ_END]);
    }
    external_process(external_process const&) = delete;
    external_process(external_process&&) = delete;
    auto operator=(external_process const&) -> external_process& = delete;
    auto operator=(external_process&&) -> external_process& = delete;

    [[nodiscard]] auto cout() const { return stdcout; }
    [[nodiscard]] auto cerr() const { return stdcerr; }
    [[nodiscard]] auto status() const -> int { return status_; }
private:
    auto findExecutableFullName(std::string _execName) const -> std::filesystem::path {
        if (_execName.empty()) {
            throw std::runtime_error("executable name can't be empty");
        }
        // Relative path given, must not search through PATH
        if (!std::filesystem::path{_execName}.parent_path().empty()) {
            return _execName;
        }


        auto envPath = getenv("PATH");
        if (!envPath) {
            throw std::runtime_error("PATH variable is not accessible");
        }
        std::string_view{envPath} | std::views::split(':');
        for (auto _view : std::string_view{envPath} | std::views::split(':')) {

            // The following lambda can be replaced with using gcc-12 and above
            // auto _p = std::filesystem::path{_view.begin(), _view.end()};
            auto _p = [&]() -> std::filesystem::path {
                std::string s;
                for (auto c : _view) {
                     s += c;
                }
                return s;
            }();
            if (exists(_p / _execName)) {
                return _p / _execName;
            }
        }
        throw std::runtime_error("Can not find " + _execName + " inside of PATH paths");

    }

    void child_process(std::vector<std::string> const& _prog) {
        assert(_prog.size() >= 1);

        auto execName = findExecutableFullName(_prog[0]);

        // List of arguments, with an extra null terminating 0
        auto argv = std::vector<char*>{};
        for (auto& a : _prog) {
            argv.push_back(const_cast<char*>(a.c_str()));
        }
        argv.push_back(nullptr);

        dup2(stdoutpipe[WRITE_END], STDOUT_FILENO);
        close(stdoutpipe[READ_END]);

        dup2(stderrpipe[WRITE_END], STDERR_FILENO);
        close(stderrpipe[READ_END]);

        execv(execName.c_str(), argv.data());
        throw std::runtime_error("Running " + execName.string() + " failed");
    }

    void parent_process(pid_t pid) {
        auto readUntilEnd = [](auto& file, auto& out) {
            auto buffer = std::array<char, 4096>{};
            while (true) {
                if (auto size = ::read(file, buffer.data(), buffer.size()); size >= 0) {
                    out += std::string_view{buffer.data(), buffer.data()+size};
                    if (size == 0) return;
                } else return;
            }
        };
        auto t1 = std::jthread{[&] { readUntilEnd(stdoutpipe[READ_END], stdcout); }};
        auto t2 = std::jthread{[&] { readUntilEnd(stderrpipe[READ_END], stdcerr); }};

        waitpid(pid, &status_, 0); /* wait for child to exit */
        status_ = status_ >> 8;
        close(stdoutpipe[WRITE_END]);
        close(stderrpipe[WRITE_END]);
    }
};
