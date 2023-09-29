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

inline void write_time_statistics(search_time_statistics const & time_statistics, std::string const & time_file)
{
    std::filesystem::path file_path{time_file};
    std::ofstream file_handle(file_path, std::ofstream::app);

    file_handle << "Ref I/O\tIBF I/O\t\tSearch\tMin cart time\tAvg cart time\tMax cart time\tNr carts\tConsolidation\n";
    file_handle << std::fixed
                << std::setprecision(2)
                << time_statistics.ref_io_time << '\t'
                << time_statistics.index_io_time << '\t'
                << time_statistics.search_time << '\t';
    if (!time_statistics.cart_processing_times.empty())
    {
        file_handle << time_statistics.get_cart_min() << '\t'
                    << time_statistics.get_cart_avg() << '\t'
                    << time_statistics.get_cart_max() << '\t'
                    << time_statistics.cart_processing_times.size() << '\t';
    }

    file_handle << time_statistics.consolidation_time << '\n';

}

} // namespace valik::app
