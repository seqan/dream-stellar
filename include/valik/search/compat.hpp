#pragma once

#include <seqan/basic.h>
#include <seqan/modifier/modifier_functors.h>

#include <seqan3/alphabet/concept.hpp>

namespace seqan2
{
    void begin(seqan2::Dna) = delete;
}
 
template <>
struct seqan3::custom::alphabet<seqan2::Dna>
{
    using alphabet_t = seqan2::Dna;
 
    static constexpr size_t alphabet_size = 4;
 
    static constexpr uint8_t to_rank(alphabet_t const a) noexcept
    {
        return seqan2::ordValue(a);
    }
 
    static constexpr alphabet_t & assign_rank_to(uint8_t const r, alphabet_t & a) noexcept
    {
        seqan2::assign(a, r);
        return a;
    }
 
    static constexpr char to_char(alphabet_t const a) noexcept
    {
        char c;
        seqan2::assign(c, a);
        return c;
    }
 
    static constexpr alphabet_t & assign_char_to(char const c, alphabet_t & a) noexcept
    {
        seqan2::assign(a, c);
        return a;
    }
    
    static constexpr alphabet_t complement(alphabet_t const a) noexcept
    {
        static seqan2::FunctorComplement<alphabet_t> func;
        return func(a);
    }
};
 
static_assert(seqan3::nucleotide_alphabet<seqan2::Dna>);
