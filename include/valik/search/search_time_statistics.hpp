#pragma once

#include <filesystem>

#include <valik/shared.hpp>

namespace valik::app
{

struct search_time_statistics
{
    double index_io_time{0.0};
    std::vector<double> cart_processing_times;
    double reads_io_time{0.0};
    double prefilter_time{0.0};

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

inline void write_time_statistics(search_time_statistics const & time_statistics, search_arguments const & arguments)
{
    std::filesystem::path file_path{arguments.out_file};
    file_path += ".time";
    std::ofstream file_handle{file_path};

    file_handle << "IBF I/O\tReads I/O\tPrefilter\tMin cart time\tAvg cart time\tMax cart time\tNr carts\n";
    file_handle << std::fixed
                << std::setprecision(2)
                << time_statistics.index_io_time << '\t'
                << time_statistics.reads_io_time << '\t'
                << time_statistics.prefilter_time << '\t'
                << time_statistics.get_cart_min() << '\t'
                << time_statistics.get_cart_avg() << '\t'
                << time_statistics.get_cart_max() << '\t'
                << time_statistics.cart_processing_times.size() << '\n';

}

} // namespace valik::app
