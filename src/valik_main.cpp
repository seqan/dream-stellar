#include <seqan3/argument_parser/all.hpp>

#include <utilities/argument_parsing/consolidate.hpp>

#include <valik/argument_parsing/split.hpp>
#include <valik/argument_parsing/build.hpp>
#include <valik/argument_parsing/search.hpp>
#include <valik/argument_parsing/shared.hpp>
#include <valik/argument_parsing/top_level.hpp>
#include <valik/valik.hpp>

int main(int argc, char ** argv)
{
    try
    {
        seqan3::argument_parser top_level_parser{"valik", argc, argv, seqan3::update_notifications::on, {"split", "build", "search", "consolidate"}};
        valik::app::init_top_level_parser(top_level_parser);

        valik::app::try_parsing(top_level_parser);

        seqan3::argument_parser & sub_parser = top_level_parser.get_sub_parser();
        if (sub_parser.info.app_name == std::string_view{"valik-split"})
            valik::app::run_split(sub_parser);
        if (sub_parser.info.app_name == std::string_view{"valik-build"})
            valik::app::run_build(sub_parser);
        if (sub_parser.info.app_name == std::string_view{"valik-search"})
            valik::app::run_search(sub_parser);
        if (sub_parser.info.app_name == std::string_view{"valik-consolidate"})
            valik::app::run_consolidation(sub_parser);
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }

    return 0;
}
