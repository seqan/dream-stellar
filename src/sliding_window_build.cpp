#include <sliding_window/build/build.hpp>
#include <sliding_window/build/ibf_factory.hpp>
#include <sliding_window/build/store_index.hpp>

#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/utility/views/slice.hpp>

namespace sliding_window::app
{

template <bool compressed>
void run_program(build_arguments const & arguments)
{
    ibf_factory<compressed> generator{arguments};
    auto ibf = generator();
    store_index(arguments.out_path, ibf, arguments);
}

void sliding_window_build(build_arguments const & arguments)
{
    if (arguments.compressed)
        run_program<true>(arguments);
    else
        run_program<false>(arguments);
    return;
}

} // namespace sliding_window::app
