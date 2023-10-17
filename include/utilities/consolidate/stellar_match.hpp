#pragma once

#include <utilities/shared.hpp>
#include <valik/split/metadata.hpp>

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
    std::string qname{};
    uint64_t qbegin{};
    uint64_t qend{};
    std::string alignment_attributes{};

    stellar_match(std::vector<std::string> const & match_vec, metadata const & meta)
    {
        dname = match_vec[0];

        ref_ind = meta.ind_from_id(dname);

        dbegin = stoi(match_vec[3]);
        dend = stoi(match_vec[4]);

        percid = match_vec[5];

        if (match_vec[6] == "-")
            is_forward_match = false;

        // Stellar GFF attributes
        // 1;seq2Range=1280,1378;cigar=97M1D2M;mutations=14A,45G,58T,92C

        /*
        for (std::string m : match_vec)
            seqan3::debug_stream << m << '\t';        
        seqan3::debug_stream << '\n';
        */
        
        std::vector<std::string> attributes_vec = get_line_vector<std::string>(match_vec[8], ';');
        if (attributes_vec.size() != 4)
        {
            std::string attributes{};
            for (auto & field : attributes_vec)
                attributes += field;
        
            throw std::runtime_error("Malformed GFF record:\n" + attributes);
        }
            
        qname = attributes_vec[0];
        qbegin = stoi(attributes_vec[1].substr(attributes_vec[1].find("=") + 1, 
                                               attributes_vec[1].find(",") - attributes_vec[1].find("=") - 1));
        qend = stoi(attributes_vec[1].substr(attributes_vec[1].find(",") + 1));
        alignment_attributes = attributes_vec[2] + attributes_vec[3];
    }

    struct length_order
    {
        inline bool operator() (stellar_match const & left, stellar_match const & right)
        {
            return ((left.dend - left.dbegin) < (right.dend - right.dbegin));
        }
    };

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
        
        // 1;seq2Range=1280,1378;cigar=97M1D2M;mutations=14A,45G,58T,92C
        match_str += qname;
        match_str += ";";
        match_str += "seq2Range=";
        match_str += qbegin;
        match_str += ",";
        match_str += qend;
        match_str += ";";
        match_str += alignment_attributes;
        match_str += "\n";

        return match_str;
    }

};

}   // namespace valik
