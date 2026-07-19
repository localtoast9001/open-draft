/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once
#ifndef __TEST_MESSAGE_LOG_H__
#define __TEST_MESSAGE_LOG_H__

#include <vector>
#include <message.hpp>

/**
 * @brief In-memory message logs for tests.
 */
class test_message_log
{
public:
    test_message_log() = default;

    void log(const opendraft::lang::message& msg);

    inline const std::vector<opendraft::lang::message>& messages() const 
    {
        return _messages;
    }

private:
    std::vector<opendraft::lang::message> _messages;
    
    test_message_log(const test_message_log&) = delete;
    test_message_log& operator=(const test_message_log&) = delete;
};
#endif /* __TEST_MESSAGE_LOG_H__ */