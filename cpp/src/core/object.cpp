/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file object.cpp
 * @brief Contains the definitions for the object class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

object::~object()
{
    
}

long object::length(long dim) const
{
    size_t dim_count = _type->dimension_count();
    if (dim < 0 || static_cast<size_t>(dim) >= dim_count)
    {
        throw std::out_of_range("Dimension index out of range.");
    }

    if (dim == 0)
    {
        return _length;
    }

    const long* len_data = reinterpret_cast<const long*>(_data);

    return len_data[dim - 1];
}

long object::get_integer(long ordinal) const
{
}

double object::get_real(long ordinal) const
{
}

uint8_t object::get_byte(long ordinal) const
{
}

bool object::get_boolean(long ordinal) const
{
}

std::string_view object::get_string(long ordinal) const
{
}

std::shared_ptr<object> object::get_object(long ordinal) const
{
}

std::shared_ptr<object> object::create(bool value)
{
}

std::shared_ptr<object> object::create(long value)
{
}

std::shared_ptr<object> object::create(double value)
{
}

std::shared_ptr<object> object::create(uint8_t value)
{
}

std::shared_ptr<object> object::create(const char* value)
{
}