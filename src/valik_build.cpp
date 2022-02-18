#include <valik/build/build.hpp>
#include <valik/build/index_factory.hpp>
#include <valik/build/store_index.hpp>

namespace valik::app
{

template <bool compressed>
void run_program(build_arguments const & arguments)
{
    index_factory<compressed> generator{arguments};
    auto index = generator();
    store_index(arguments.out_path, index);
}

void valik_build(build_arguments const & arguments)
{
    if (arguments.compressed)
        run_program<true>(arguments);
    else
        run_program<false>(arguments);
    return;
}

} // namespace valik::app
