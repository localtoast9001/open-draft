/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file array_type.cpp
 * @brief Contains the definitions for the array_type class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

array_type::array_type(
    const std::string& name,
    const std::shared_ptr<type>& element_type,
    size_t dimension_count)
    : type(name), _element_type(element_type), _dimension_count(dimension_count)
{
}

type_kind array_type::kind() const
{
    return TYPE_KIND_ARRAY;
}

size_t array_type::dimension_count() const
{
    return _dimension_count;
}