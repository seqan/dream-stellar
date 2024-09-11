
#pragma once

#include <ostream>

#include <dream_stellar/utils/stellar_kernel_runtime.hpp>
#include <dream_stellar/utils/stellar_runtime.hpp>

namespace dream_stellar
{

struct stellar_strand_time : public stellar_runtime
{
    stellar_kernel_runtime prefiltered_stellar_time{};
    stellar_runtime post_process_eps_matches_time{};
    stellar_runtime output_eps_matches_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            prefiltered_stellar_time._runtime +
            post_process_eps_matches_time._runtime +
            output_eps_matches_time._runtime);

        return total;
    }
};

template <typename TStream>
void _print_stellar_strand_time(stellar_strand_time const & strand_runtime, std::string strandDirection, TStream & outStr)
{
    stellar_kernel_runtime const & prefiltered_stellar_time
        = strand_runtime.prefiltered_stellar_time;
    stellar_verification_time const & verification_time
        = strand_runtime.prefiltered_stellar_time.verification_time;
    stellar_extension_time const & extension_time
        = verification_time.extension_time;
    stellar_best_extension_time const & best_extension_time
        = extension_time.best_extension_time;

    outStr << "       + Prefiltered Stellar Time (" << strandDirection << "): " << prefiltered_stellar_time.milliseconds() << "ms" << std::endl;
    outStr << "          + Swift Filter Time (" << strandDirection << "): " << prefiltered_stellar_time.swift_filter_time.milliseconds() << "ms" << std::endl;
    outStr << "          + Seed Verification Time (" << strandDirection << "): " << verification_time.milliseconds() << "ms" << std::endl;
    outStr << "             + Find Next Local Alignment Time (" << strandDirection << "): " << verification_time.next_local_alignment_time.milliseconds() << "ms" << std::endl;
    outStr << "             + Split At X-Drops Time (" << strandDirection << "): " << verification_time.split_at_x_drops_time.milliseconds() << "ms" << std::endl;
    outStr << "             + Extension Time (" << strandDirection << "): " << extension_time.milliseconds() << "ms" << std::endl;
    outStr << "                + Extend Seed Time (" << strandDirection << "): " << extension_time.extend_seed_time.milliseconds() << "ms" << std::endl;
    outStr << "                + Best Extension Time (" << strandDirection << "): " << best_extension_time.milliseconds() << "ms" << std::endl;
    outStr << "                   + Banded Needleman-Wunsch Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_time.milliseconds() << "ms" << std::endl;
    outStr << "                      + Banded Needleman-Wunsch (Left Extension) Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_left_time.milliseconds() << "ms" << std::endl;
    outStr << "                      + Banded Needleman-Wunsch (Right Extension) Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_right_time.milliseconds() << "ms" << std::endl;
    outStr << "                   + Longest EPS Match Time (" << strandDirection << "): " << best_extension_time.longest_eps_match_time.milliseconds() << "ms" << std::endl;
    outStr << "                   + Construct Alignment Time (" << strandDirection << "): " << best_extension_time.construct_seed_alignment_time.milliseconds() << "ms" << std::endl;
    outStr << "                   = total time: " << best_extension_time.total_time().milliseconds() << "ms" << std::endl;
    outStr << "                = total time: " << extension_time.total_time().milliseconds() << "ms" << std::endl;
    outStr << "             = total time: " << verification_time.total_time().milliseconds() << "ms" << std::endl;
    outStr << "          = total time: " << prefiltered_stellar_time.total_time().milliseconds() << "ms" << std::endl;
    outStr << "       + Post-Process Eps-Matches Time (" << strandDirection << "): " << strand_runtime.post_process_eps_matches_time.milliseconds() << "ms" << std::endl;
    outStr << "       + File Output Eps-Matches Time (" << strandDirection << "): " << strand_runtime.output_eps_matches_time.milliseconds() << "ms" << std::endl;
    outStr << "       = total time: " << strand_runtime.total_time().milliseconds() << "ms" << std::endl;
};


struct stellar_app_runtime : public stellar_runtime
{
    stellar_runtime input_queries_time{};
    stellar_runtime input_databases_time{};
    stellar_runtime swift_index_construction_time{};
    stellar_strand_time forward_strand_stellar_time{};
    stellar_runtime reverse_complement_database_time{};
    stellar_strand_time reverse_strand_stellar_time{};
    stellar_runtime output_disabled_queries_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            input_queries_time._runtime +
            input_databases_time._runtime +
            swift_index_construction_time._runtime +
            forward_strand_stellar_time._runtime +
            reverse_complement_database_time._runtime +
            reverse_strand_stellar_time._runtime +
            output_disabled_queries_time._runtime);

        return total;
    }
};

template <typename TStream>
void _print_stellar_app_time(stellar_app_runtime const & stellar_time, TStream & strOut)
{
    strOut << "Running time: " << stellar_time.milliseconds() << "ms" << std::endl;
    strOut << " * Stellar Application Time: " << stellar_time.milliseconds() << "ms" << std::endl;
    strOut << "    + File Input Queries Time: " << stellar_time.input_queries_time.milliseconds() << "ms" << std::endl;
    strOut << "    + File Input Databases Time: " << stellar_time.input_databases_time.milliseconds() << "ms" << std::endl;
    strOut << "    + SwiftFilter Construction Time: " << stellar_time.swift_index_construction_time.milliseconds() << "ms" << std::endl;
    strOut << "    + Stellar Forward Strand Time: " << stellar_time.forward_strand_stellar_time.milliseconds() << "ms" << std::endl;
    _print_stellar_strand_time(stellar_time.forward_strand_stellar_time, "Forward", strOut);
    strOut << "    + Database Reverse Complement Time: " << stellar_time.reverse_complement_database_time.milliseconds() << "ms" << std::endl;
    strOut << "    + Stellar Reverse Strand Time: " << stellar_time.reverse_strand_stellar_time.milliseconds() << "ms" << std::endl;
    _print_stellar_strand_time(stellar_time.reverse_strand_stellar_time, "Reverse", strOut);
    strOut << "    + File Output Disabled Queries Time: " << stellar_time.output_disabled_queries_time.milliseconds() << "ms" << std::endl;
    strOut << "    = total time: " << stellar_time.total_time().milliseconds() << "ms" << std::endl;
}

} // namespace dream_stellar
