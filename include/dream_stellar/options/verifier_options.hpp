
#pragma once

#include <seqan/basic/basic_debug.h>
#include <seqan/basic/basic_fundamental.h>

namespace dream_stellar
{

struct VerifyAllLocal_;
using AllLocal = seqan2::Tag<VerifyAllLocal_> const;

struct VerifyBestLocal_;
using BestLocal = seqan2::Tag<VerifyBestLocal_> const;

struct VerifyBandedGlobal_;
using BandedGlobal = seqan2::Tag<VerifyBandedGlobal_> const;

struct VerifyBandedGlobalExtend_;
using BandedGlobalExtend = seqan2::Tag<VerifyBandedGlobalExtend_> const;

// basically a std::variant<AllLocal, BestLocal, BandedGlobal, BandedGlobalExtend>
struct StellarVerificationMethod
{
    StellarVerificationMethod(AllLocal) : _index{0} {}
    StellarVerificationMethod(BestLocal) : _index{1} {}
    StellarVerificationMethod(BandedGlobal) : _index{2} {}
    StellarVerificationMethod(BandedGlobalExtend) : _index{3} {}

    constexpr std::size_t index() const noexcept
    {
        return _index;
    }

    friend constexpr bool operator==(
        StellarVerificationMethod const & m1,
        StellarVerificationMethod const & m2)
    {
        return m1.index() == m2.index();
    }

    friend inline std::string to_string(StellarVerificationMethod method)
    {
        using cstring_t = char const * const;
        cstring_t method_names[] = {"exact", "bestLocal", "bandedGlobal", "bandedGlobalExtend"};
        return method_names[method.index()];
    }

private:
    std::size_t _index{~std::size_t{0u}};
};

struct VerifierOptions
{
    double xDrop{5}; // maximal x-drop

    // verification strategy: exact, bestLocal, bandedGlobal
    std::string strVerificationMethod{"exact"};
    StellarVerificationMethod verificationMethod{AllLocal{}};
};

} // namespace dream_stellar
