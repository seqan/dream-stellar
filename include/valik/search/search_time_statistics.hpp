#pragma once

#include <filesystem>

#include <valik/shared.hpp>

namespace valik::app
{

struct search_time_statistics
{
    double ref_io_time{0.0};
    double index_io_time{0.0};
    std::vector<double> cart_processing_times;
    double search_time{0.0};
    double consolidation_time{0.0};

    double get_cart_min() const
    {
        auto min_it = std::min_element(cart_processing_times.begin(), cart_processing_times.end());
        return *min_it;
    }

    double get_cart_avg() const
    {
        double sum{0};
        for (auto t : cart_processing_times)
            sum += t;
        return sum / cart_processing_times.size();
    }

    double get_cart_max() const
    {
        auto max_it = std::max_element(cart_processing_times.begin(), cart_processing_times.end());
        return *max_it;
    }
};

inline void write_time_statistics(search_time_statistics const & time_statistics,
                                  std::string const & time_file,
                                  search_arguments const & arguments)
{
    std::filesystem::path file_path{time_file};
    std::ofstream file_handle(file_path, std::ofstream::app);

    // the effective query count gives an estimate on how many total queries were done across all reference segments
    // this helps assess the effectiveness of the prefiltering
    // the effective query count is an upper bound because some carts are only partially filled
    file_handle << "Ref I/O\tIBF I/O\t\tSearch\tEffective query count\tMin cart time\tAvg cart time\tMax cart time\tConsolidation\n";
    file_handle << std::fixed
                << std::setprecision(2)
                << time_statistics.ref_io_time << '\t'
                << time_statistics.index_io_time << '\t'
                << time_statistics.search_time << '\t';
    if (!time_statistics.cart_processing_times.empty())
    {
        file_handle << std::fixed
                    << std::setprecision(4)
                    << time_statistics.cart_processing_times.size() * arguments.cart_max_capacity << '\t'
                    << time_statistics.get_cart_min() << '\t'
                    << time_statistics.get_cart_avg() << '\t'
                    << time_statistics.get_cart_max() << '\t';
    }

    file_handle << time_statistics.consolidation_time << '\n';

}

} // namespace valik::app
