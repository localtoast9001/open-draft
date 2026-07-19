/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "test_message_log.hpp"

void test_message_log::log(const opendraft::lang::message& msg)
{
    _messages.push_back(msg);
}