/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file class_type.cpp
 * @brief Contains the definitions for the class_type class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

class_type::class_type(const std::string& name)
    : type(name)
{
}

type_kind class_type::kind() const
{
    return TYPE_KIND_CLASS;
}