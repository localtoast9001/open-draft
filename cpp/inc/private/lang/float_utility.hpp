/**
 * Copyright (C) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file float_utility.hpp
 * @brief Declares utility functions for floating-point operations.
 */
#pragma once
#ifndef __OPENDRAFT_LANG_FLOAT_UTILITY_HPP__
#define __OPENDRAFT_LANG_FLOAT_UTILITY_HPP__

namespace opendraft::lang
{
    /**
     * @brief Provides utility functions for floating-point operations used by the lexer.
     */
    class float_utility
    {
    public:
        /**
         * @brief Composes a floating-point number from its integer part, fractional part, divisor, and exponent.
         * @param int_part The integer part of the number.
         * @param frac_part The fractional part of the number.
         * @param divisor_exponent The exponent of 10 for the divisor of the fractional part. The divisor is 10^divisor_exponent.
         * @param exponent The exponent to apply.
         * @return The composed floating-point number.
         */
        static long double compose(
            long int_part,
            long frac_part,
            int divisor_exponent,
            int exponent);

        /**
         * @brief Multiplies the given base by 10 raised to the specified exponent.
         * @param base The base value.
         * @param exponent The exponent to apply.
         * @return The result of base * 10^exponent.
         */
        static long double mul_pow10(long double base, int exponent);

    private:
        float_utility() = delete;
        ~float_utility() = delete;
    };
}

#endif /* __OPENDRAFT_LANG_FLOAT_UTILITY_HPP__ */