#pragma once

#include <set>
#include <string>

namespace sliding_window
{

// "query" is a noun not a verb
class query_result
{
private:
    std::string id;
    std::set<size_t> bin_hits;

public:
    query_result() = default;
    query_result(query_result const &) = default;
    query_result & operator=(query_result const &) = default;
    query_result(query_result &&) = default;
    query_result & operator=(query_result &&) = default;
    ~query_result() = default;

    query_result(std::string const query_id, std::set<size_t> const & query_hits)
    {
        id = query_id;
        bin_hits = query_hits; 
    }

    const std::set<size_t>& get_hits() const
    {
        return bin_hits;
    }

    const std::string & get_id() const
    {
        return id;
    }
    
};

} // namespace sliding_window
