/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file primitive_type.cpp
 * @brief Contains the definitions for the primitive_type class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

primitive_type::primitive_type(const std::string& name, core::primitive_kind kind)
    : type(name), _kind(kind)
{
}

type_kind primitive_type::kind() const
{
    return TYPE_KIND_PRIMITIVE;
}