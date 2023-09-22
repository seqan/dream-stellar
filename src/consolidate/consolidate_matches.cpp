#include <utilities/consolidate/consolidate_matches.hpp>

namespace valik
{

void consolidate_matches(search_arguments const & arguments)
{
    auto ref_meta = metadata(arguments.ref_meta_path);
    auto matches = read_stellar_output(arguments.all_matches, ref_meta);

    std::sort( matches.begin(), matches.end(), std::greater<stellar_match>());
    matches.erase( std::unique( matches.begin(), matches.end() ), matches.end() );

    write_stellar_output(arguments.out_file, matches);
}

}  // namespace valik
