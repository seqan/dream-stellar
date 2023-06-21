#pragma once

#include <utilities/shared.hpp>
#include <valik/split/reference_metadata.hpp>

namespace valik
{

struct stellar_match
{
    std::string dname{};
    size_t ref_ind{};
    uint64_t dbegin{};
    uint64_t dend{};
    std::string percid;
    bool is_forward_match{true};

    // Stellar GFF attributes
    // 1;seq2Range=1280,1378;cigar=97M1D2M;mutations=14A,45G,58T,92C
    std::string attributes{};

    stellar_match(std::vector<std::string> const match_vec, reference_metadata const & reference)
    {
        dname = match_vec[0];

        ref_ind = reference.ind_from_id(dname);

        dbegin = stoi(match_vec[3]);
        dend = stoi(match_vec[4]);

        percid = match_vec[5];

        if (match_vec[6] == "-")
            is_forward_match = false;

        attributes = match_vec[8];
    }

    bool operator == (stellar_match const & other) const
    {
        if (dname == other.dname &&
            dbegin == other.dbegin &&
            dend == other.dend &&
            is_forward_match == other.is_forward_match)
            return true;
        else
            return false;
    }

    bool operator > (const stellar_match& match) const
    {
        if (ref_ind > match.ref_ind)
            return true;
        else if (ref_ind < match.ref_ind)
            return false;
        else
        {
            if (dbegin > match.dbegin)
                return true;
            else if (dbegin < match.dbegin)
                return false;
            else
                return (dend > match.dend);
        }
    }

    std::string to_string() const
    {
        std::string match_str = dname;
        match_str += "\tStellar\teps-matches\t";
        match_str += std::to_string(dbegin);
        match_str += "\t";
        match_str += std::to_string(dend);
        match_str += "\t";
        match_str += percid;

        match_str += "\t";

        if (is_forward_match)
            match_str += "+";
        else
            match_str += "-";

        match_str += "\t.\t";
        match_str += attributes;
        match_str += "\n";

        return match_str;
    }

};

}   // namespace valik
