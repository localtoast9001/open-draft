/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file source_reference.hpp
 * @brief Contains the declarations for the source_reference class and related functions.
 */
#pragma once

#ifndef _OPEN_DRAFT_SOURCE_REFERENCE_HPP_
#define _OPEN_DRAFT_SOURCE_REFERENCE_HPP_

#include <string>

namespace opendraft::lang
{
    /**
    * @brief Represents a reference to a source file and line number.
    */
    class source_reference
    {
    public:
        source_reference();
        source_reference(const source_reference&) = default;

        /**
        * @brief Constructs a new source_reference object.
        * @param path The path to the source file.
        * @param line The starting line number.
        * @param column The starting column number.
        * @param end_line The ending line number.
        * @param end_column The ending column number.
        */
        source_reference(
            const std::string& path,
            int line = 0,
            int column = 0,
            int end_line = 0,
            int end_column = 0);

        ~source_reference() = default;

        /**
        * @brief Gets the path to the source file.
        * @return The path to the source file.
        */
        constexpr const std::string& path() const { return _path; }
        
        /**
        * @brief Gets the starting line number.
        * @return The starting line number.
        */
        constexpr int line() const { return _line; }
        
        /**
        * @brief Gets the starting column number.
        * @return The starting column number.
        */
        constexpr int column() const { return _column; }
        
        /**
        * @brief Gets the ending line number.
        * @return The ending line number.
        */
        constexpr int end_line() const { return _end_line; }
        
        /**
        * @brief Gets the ending column number.
        * @return The ending column number.
        */
        constexpr int end_column() const { return _end_column; }

        /**
        * @brief Assigns a new value to the source_reference object.
        * @param other The source_reference object to copy from.
        * @return A reference to the updated source_reference object.
        */
        source_reference& operator=(const source_reference&) = default;

        /**
        * @brief Converts the source_reference object to a string representation.
        * @return A string representation of the source_reference object.
        */
        std::string to_string() const;

        bool operator==(const source_reference& other) const;
        bool operator!=(const source_reference& other) const;

    private:
        std::string _path;
        int _line;
        int _column;
        int _end_line;
        int _end_column;
    };

    std::ostream& operator<<(std::ostream& os, const source_reference& ref);
}

#endif /* _OPEN_DRAFT_SOURCE_REFERENCE_HPP_ */