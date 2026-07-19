/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message_id.cpp
 * @brief Defines the message_id class and related functions.
 */
#include <message.hpp>
#include <cstring>

namespace opendraft::lang
{
    message_id::message_id()
        : _category{0}, _code(0)
    {
    }

    message_id::message_id(const std::string_view& category, int code)
        : _category{0}, _code(code)
    {
        for (size_t i = 0; i < message_id::MAX_CATEGORY_LENGTH && i < category.size(); ++i)
        {
            _category[i] = category[i];
        }
    }

    std::string_view message_id::category() const
    {
        return std::string_view(_category, category_length());
    }

    bool message_id::operator==(const message_id& other) const
    {
        // Safe to compare the category arrays directly with the max length since they are fixed size and padded with zeros.
        return std::memcmp(
            _category,
            other._category,
            MAX_CATEGORY_LENGTH) == 0 && 
            _code == other._code;
    }

    std::string message_id::to_string() const
    {
        // this is the category immediately followed by the code padded to 4 digits with leading zeros.
        char buffer[5];
        std::snprintf(buffer, sizeof(buffer), "%04d", _code);
        return std::string(category()) + buffer;
    }

    size_t message_id::category_length() const
    {
        size_t length = 0;
        for (size_t i = 0; i < message_id::MAX_CATEGORY_LENGTH; ++i)
        {
            if (_category[i] == '\0')
            {
                break;
            }

            length++;
        }

        return length;
    }

    std::ostream& operator<<(std::ostream& os, const message_id& id)
    {
        return os << id.to_string();
    }
}