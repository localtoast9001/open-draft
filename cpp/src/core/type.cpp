/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file type.cpp
 * @brief Contains the definitions for the type class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

size_t type::dimension_count() const
{
    return 1;
}