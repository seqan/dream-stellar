
#pragma once

#include <chrono>

namespace dream_stellar
{

struct stellar_runtime
{
    using clock_t = std::chrono::steady_clock;
    using time_point_t = typename clock_t::time_point;
    using duration_t = typename clock_t::duration;

    template <typename execute_fn>
    auto measure_time(execute_fn && execute)
    {
        constexpr bool has_return = !std::is_same_v<decltype(execute()), void>;
        auto start = now();

        if constexpr(has_return)
        {
            auto value = execute();
            _runtime += now() - start;
            return value;
        } else
        {
            execute();
            _runtime += now() - start;
        }
    }

    static time_point_t now()
    {
        return clock_t::now();
    }

    void manual_timing(time_point_t time_point)
    {
        manual_timing(now() - time_point);
    }

    void manual_timing(duration_t duration)
    {
        _runtime += duration;
    }

    size_t milliseconds() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(_runtime).count();
    }

    duration_t _runtime{};
};

} // namespace dream_stellar
