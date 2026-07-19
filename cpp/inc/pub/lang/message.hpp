/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message.hpp
 * @brief Declares the message class and related types.
 */
#pragma once
#ifndef __OPENDRAFT_LANG_MESSAGE_HPP__
#define __OPENDRAFT_LANG_MESSAGE_HPP__

#include <string>
#include <ostream>
#include "source_reference.hpp"

namespace opendraft::lang
{
    /**
     * @brief Represents the severity of a message produced by the compiler.
     */
    enum severity
    {
        SEVERITY_ERROR = 0,
        SEVERITY_WARNING,
        SEVERITY_INFO,
    };

    const char* to_string(severity value);

    /**
     * @brief Represents the identifier of a message produced by the compiler.
     */
    class message_id
    {
    public:
        message_id();
        message_id(const std::string_view& category, int code);
        message_id(const message_id&) = default;

        ~message_id() = default;

        std::string_view category() const;
        constexpr int code() const { return _code; }

        message_id& operator=(const message_id&) = default;

        bool operator==(const message_id& other) const;

        std::string to_string() const;

    private:
        static constexpr size_t MAX_CATEGORY_LENGTH = 4;
        char _category[MAX_CATEGORY_LENGTH];
        int _code;

        size_t category_length() const;
    };

    /**
     * @brief Represents a message produced by the compiler.
     */
    class message
    {
    public:
        message();
        message(
            const source_reference& source,
            const message_id& id,
            opendraft::lang::severity severity,
            const std::string& text);

        message(const message&) = default;

        ~message() = default;

        constexpr const source_reference& source() const { return _source; }
        constexpr const message_id& id() const { return _id; }
        constexpr opendraft::lang::severity severity() const { return _severity; }
        constexpr const std::string& text() const { return _text; }

        message& operator=(const message&) = default;

        std::string to_string() const;
    private:
        source_reference _source;
        message_id _id;
        opendraft::lang::severity _severity;
        std::string _text;
    };

    std::ostream& operator<<(std::ostream& os, const message_id& id);
    std::ostream& operator<<(std::ostream& os, const message& msg);
}

#endif /* __OPENDRAFT_LANG_MESSAGE_HPP__ */