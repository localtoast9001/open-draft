/**
 * @file float_utility.cpp
 * @brief Defines utility functions for floating-point operations.
 */
#include <float_utility.hpp>
#include <cmath>

namespace opendraft::lang
{
    long double float_utility::compose(
        long int_part,
        long frac_part,
        int divisor_exponent,
        int exponent)
    {
        long double frac_part_value = mul_pow10((long double)frac_part, divisor_exponent + exponent);
        long double int_part_value = mul_pow10((long double)int_part, exponent);
        long double value = frac_part_value + int_part_value;

        return value;
    }

    long double float_utility::mul_pow10(long double base, int exponent)
    {
        // return base * std::pow(10.0, exponent);
        if (exponent == 0)
        {
            return base;
        }

        long double result = base;
        bool is_negative = exponent < 0;
        if (is_negative)
        {
            exponent = -exponent;
            for (int i = 0; i < exponent; ++i)
            {
                result /= 10.0;
            }
        }
        else
        {
            for (int i = 0; i < exponent; ++i)
            {
                result *= 10.0;
            }
        }

        return result;
    }
}