#include <seqan3/argument_parser/all.hpp>

#include <sliding_window/argument_parsing/build.hpp>
#include <sliding_window/argument_parsing/search.hpp>
#include <sliding_window/argument_parsing/shared.hpp>
#include <sliding_window/argument_parsing/top_level.hpp>
#include <sliding_window/sliding_window.hpp>

int main(int argc, char ** argv)
{
    try
    {
        seqan3::argument_parser top_level_parser{"sliding_window", argc, argv, seqan3::update_notifications::on, {"build", "search"}};
        sliding_window::init_top_level_parser(top_level_parser);

        sliding_window::try_parsing(top_level_parser);

        seqan3::argument_parser & sub_parser = top_level_parser.get_sub_parser();
        if (sub_parser.info.app_name == std::string_view{"sliding_window-build"})
            sliding_window::run_build(sub_parser);
        if (sub_parser.info.app_name == std::string_view{"sliding_window-search"})
            sliding_window::run_search(sub_parser);
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }

    return 0;
}
