#include <utilities/consolidate/consolidate.hpp>

namespace valik::app
{

void valik_consolidate(consolidation_arguments const & arguments)
{
    reference_metadata reference(arguments.ref_meta_path, false);

    auto matches = read_stellar_output(arguments.matches_in, reference);

    std::sort( matches.begin(), matches.end(), std::greater<stellar_match>());
    matches.erase( std::unique( matches.begin(), matches.end() ), matches.end() );

    write_stellar_output(arguments.matches_out, matches);
}

} // namespace valik::app
