 #pragma once

#include <dream_stellar/utils/stellar_runtime.hpp>

namespace dream_stellar
{

struct stellar_best_extension_time : public stellar_runtime
{
    stellar_runtime banded_needleman_wunsch_time;
    stellar_runtime banded_needleman_wunsch_left_time;
    stellar_runtime banded_needleman_wunsch_right_time;
    stellar_runtime longest_eps_match_time;
    stellar_runtime construct_seed_alignment_time;

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            banded_needleman_wunsch_time._runtime +
            longest_eps_match_time._runtime +
            construct_seed_alignment_time._runtime);

        return total;
    }
};

struct stellar_extension_time : public stellar_runtime
{
    stellar_runtime extend_seed_time;
    stellar_best_extension_time best_extension_time;

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            extend_seed_time._runtime +
            best_extension_time._runtime);

        return total;
    }
};

struct stellar_verification_time : public stellar_runtime
{
    stellar_runtime next_local_alignment_time;
    stellar_runtime split_at_x_drops_time;
    stellar_extension_time extension_time;

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            next_local_alignment_time._runtime +
            split_at_x_drops_time._runtime +
            extension_time._runtime);

        return total;
    }
};

struct stellar_kernel_runtime : public stellar_runtime
{
    stellar_runtime swift_filter_time{};
    stellar_verification_time verification_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            swift_filter_time._runtime +
            verification_time._runtime);

        return total;
    }
};

} // namespace dream_stellar
