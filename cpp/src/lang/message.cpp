/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message.cpp
 * @brief Defines the message class and related functions.
 */
#include <message.hpp>

namespace opendraft::lang
{
    message::message(
        const source_reference& source,
        const message_id& id,
        opendraft::lang::severity severity,
        const std::string& text)
        : _source(source), _id(id), _severity(severity), _text(text)
    {
    }

    message::message()
        : _source(), _id(), _severity(SEVERITY_ERROR), _text()
    {
    }

    std::string message::to_string() const
    {
        return
            _source.to_string() + ": " + 
            std::string(opendraft::lang::to_string(_severity)) + ": " + 
            _id.to_string() + ": " + 
            _text;
    }

    std::ostream& operator<<(std::ostream& os, const message& msg)
    {
        return os << msg.to_string();
    }
}