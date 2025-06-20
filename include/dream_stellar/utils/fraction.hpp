
#pragma once

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <string_view>
#include <regex>

namespace dream_stellar::utils
{

struct fraction
{
    using difference_t = std::ptrdiff_t;

    fraction() = default;

    constexpr explicit fraction(uint32_t const precision_limit) :
        _numerator{1}
    {
        _limiter = std::max(_limiter, precision_limit);
        _denominator = limiter();
        if (_denominator == 0u)
            throw std::domain_error{"denominator shouldn't be zero."};
    }

    template <typename TDenominator>
    constexpr explicit fraction(difference_t const numerator, TDenominator const denominator, std::enable_if_t<std::is_unsigned_v<TDenominator>, int> = 0) :
        _numerator{numerator},
        _denominator{denominator}
    {
        if (_denominator == 0u)
            throw std::domain_error{"denominator can't be zero."};
    }

    template <typename TDenominator>
    constexpr fraction(difference_t const numerator, TDenominator const denominator, std::enable_if_t<std::is_signed_v<TDenominator>, int> = 0) :
        fraction{_abs(numerator), static_cast<size_t>(_abs(denominator))}
    {
        if (numerator < 0)
            _numerator = -_numerator;

        if (denominator < 0)
            _numerator = -_numerator;
    }

    static fraction from_string(std::string_view const str)
    {
        using double_t = long double;
        char * sentinel = nullptr;

        std::cmatch simple_float_match;
        std::regex simple_float_regex{"^([+-]|)([0-9]+)(.([0-9]+)|)$"};

        static constexpr size_t float_sign_id = 1;
        static constexpr size_t float_integer_id = 2;
        static constexpr size_t float_fraction_id = 4;

        if (std::regex_search(str.begin(), str.end(), simple_float_match, simple_float_regex))
        {
            std::string float_fraction_str = simple_float_match[float_fraction_id];

            // NOTE: all digits without dot
            std::string float_significand_str = std::string{simple_float_match[float_integer_id]} + float_fraction_str;

            auto parse_int = [](std::string_view const str) -> size_t
            {
                char * str_end;
                return std::strtoll(str.data(), &str_end, 10);
            };

            difference_t numerator = parse_int(float_significand_str);
            std::size_t denominator = 1u;
            for (std::size_t exponent = float_fraction_str.size(); exponent > 0u; --exponent)
                denominator *= 10;

            if (simple_float_match[float_sign_id].compare("-") == 0)
                numerator = -numerator;

            return {numerator, static_cast<difference_t>(denominator)};
        }

        double_t value = std::strtold(str.data(), &sentinel);
        return from_double(value);
    }

    static fraction from_double_with_limit(long double value, uint32_t const precision_limit)
    {
        // Applying a lower bound to the error rate because values close to 0 increase runtime dramatically  
        if (std::abs(value) < (1.0 / (precision_limit * 1.05)))
        {
            return fraction(precision_limit);
        }    
        else
            return from_double(value);        
    }

    static fraction from_double(long double value)
    {
        constexpr size_t max_iterations = 400;

        int exponent{0u};
        double_t normalized_value = std::frexp(value, &exponent);

        for (size_t i = 0; i < max_iterations && normalized_value != std::floor(normalized_value); ++i)
        {
            // otherwise over/underflows
            if (exponent <= -62 || exponent >= 62)
                break;

            normalized_value *= 2.0;
            exponent--;
        }

        difference_t numerator = std::llround(normalized_value);
        difference_t denominator = 1;

        if (exponent > 0) // normalized_value * 2^exponent
        {
            numerator <<= exponent;
        } else
        {
            denominator <<= -exponent;
        }
        return fraction(numerator, denominator);
    }

    constexpr operator double() const
    {
        return static_cast<double>(_numerator) / _denominator;
    }

    constexpr difference_t numerator() const
    {
        return _numerator;
    }

    constexpr size_t denominator() const
    {
        return _denominator;
    }

    constexpr uint32_t limiter() const
    {
        return _limiter;
    }

    constexpr bool is_proper() const
    {
        // i.e. proper: 1/3, 2/3, -1/3, inproper: 3/2, 2/2, -14/3
        return _abs(_numerator) < static_cast<difference_t>(_denominator);
    }

    constexpr friend difference_t floor(fraction a)
    {
        difference_t i = a.numerator() / static_cast<difference_t>(a.denominator());
        difference_t m = a.numerator() % static_cast<difference_t>(a.denominator());
        return i + (m < 0 ? -1 : 0);
    }

    constexpr friend difference_t ceil(fraction a)
    {
        difference_t value = a.numerator() + a.denominator() - 1;
        difference_t i = value / static_cast<difference_t>(a.denominator());
        difference_t m = value % static_cast<difference_t>(a.denominator());
        return i + (m < 0 ? -1 : 0);
    }

    constexpr friend fraction abs(fraction a)
    {
        return fraction{_abs(a.numerator()), a.denominator()};
    }

    constexpr friend fraction inverse(fraction a)
    {
        return fraction{static_cast<difference_t>(a.denominator()), a.numerator()};
    }

    constexpr friend fraction operator/(fraction a, fraction b)
    {
        return a * inverse(b);
    }

    constexpr friend fraction operator*(fraction a, fraction b)
    {
        return fraction{a.numerator() * b.numerator(), a.denominator() * b.denominator()};
    }

    constexpr friend fraction operator-(fraction a, fraction b)
    {
        return fraction{
            _numerator_times_denominator(a, b) - _numerator_times_denominator(b, a),
            a.denominator() * b.denominator()
        };
    }

    constexpr fraction limit_denominator(size_t max_denominator=1000000) const
    {
        // https://stackoverflow.com/questions/17537613/does-python-have-a-function-to-reduce-fractions
        // https://hg.python.org/cpython/file/822c7c0d27d1/Lib/fractions.py#l211
        if (_denominator <= max_denominator)
            return *this;

        bool is_negative = _numerator < 0;

        size_t p0 = 0;
        size_t q0 = 1;
        size_t p1 = 1;
        size_t q1 = 0;
        size_t n = _abs(_numerator);
        size_t d = _denominator;

        while (true)
        {
            if (d == 0)
                break;

            size_t a = n / d;
            size_t q2 = q0 + a * q1;
            size_t p2 = p0 + a * p1;

            if (q2 > max_denominator)
                break;

            p0 = p1;
            q0 = q1;
            p1 = p2;
            q1 = q2;

            assert(n >= a * d);

            size_t new_d = n - a * d;
            n = d;
            d = new_d;
        }

        assert(max_denominator >= q0);
        size_t k = (max_denominator - q0) / q1;

        size_t p2 = p0 + k * p1;
        size_t q2 = q0 + k * q1;

        assert(q2 != 0);
        assert(q1 != 0);
        fraction bound1{static_cast<difference_t>(p2) * (is_negative ? -1 : 1), q2};
        fraction bound2{static_cast<difference_t>(p1) * (is_negative ? -1 : 1), q1};

        // abs(bound1 - *this)
        difference_t numerator1 = _abs(_numerator_times_denominator(bound1, *this) - _numerator_times_denominator(*this, bound1));
        // abs(bound2 - *this)
        difference_t numerator2 = _abs(_numerator_times_denominator(bound2, *this) - _numerator_times_denominator(*this, bound2));
        if (numerator2 <= numerator1)
            return {bound2};
        else
            return {bound1};
    }

    template< class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT,Traits> & os, fraction const & fraction)
    {
        if (fraction.denominator() != fraction.limiter())
            os << ((double)fraction.numerator() / fraction.denominator()) << " = (" << fraction.numerator() << "/" << fraction.denominator() << ")";
        else
            os << "0 = (0/1)";  // if floating point value <10e6 treat it as 0
        return os;
    }

private:
    constexpr static difference_t _numerator_times_denominator(fraction a, fraction b)
    {
        return a.numerator() * static_cast<difference_t>(b.denominator());
    }

    // std::abs is not constexpr
    constexpr static auto _abs = [](auto a) { return a < 0 ? -a : a; };

    /* 
    The longest allowed min local match length is 1000 which means that the smallest meaningful error rate is 1 / 1000.
    Adding a 5% allowance to account for floating point inexactness the _limiter gives a lower bound for the error rate.
    It is crucial to have a lower bound for the error rate because values close to 0 have a detrimental effect on the runtime. 
    */ 
    uint32_t _limiter{1050u}; 
    difference_t _numerator{0u};
    size_t _denominator{1u};
};

} // namespace dream_stellar::utils
