/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file vector_ref_object_storage.cpp
 * @brief Implementation of the vector_ref_object_storage class.
 */
#include <object_storage_impl.hpp>

using namespace opendraft::core;
using namespace std;

uint8_t* vector_ref_object_storage::alloc(long length)
{
    return new uint8_t[sizeof(vector_ref_object_storage) + sizeof(std::shared_ptr<object>) * length];
}

vector_ref_object_storage::vector_ref_object_storage(
    long length,
    const std::shared_ptr<object>& value)
    : _length(length)
{
    shared_ptr<object>* p = data();
    shared_ptr<object>* end = data() + _length;
    for (; p != end; ++p)
    {
        new (p) shared_ptr<object>(value);
    }
}

vector_ref_object_storage::vector_ref_object_storage(
    const std::shared_ptr<object>* data,
    long length)
    : _length(length)
{
    shared_ptr<object>* dest = this->data();
    const shared_ptr<object>* src = data;
    shared_ptr<object>* end = this->data() + _length;
    for (; dest != end; dest++, src++)
    {
        new (dest) shared_ptr<object>(*src);
    }
}

vector_ref_object_storage::~vector_ref_object_storage()
{
    shared_ptr<object>* p = data();
    shared_ptr<object>* end = data() + _length;
    for (; p != end; ++p)
    {
        p->~shared_ptr<object>();
    }
}

std::shared_ptr<object_storage> vector_ref_object_storage::create(
    long length,
    std::shared_ptr<object> value)
{
    auto p = alloc(length);
    return std::shared_ptr<object_storage>(new (p) vector_ref_object_storage(length, value));
}

std::shared_ptr<object_storage> vector_ref_object_storage::create(
    std::initializer_list<std::shared_ptr<object>> value)
{
    auto p = alloc(value.size());
    return std::shared_ptr<object_storage>(new (p) vector_ref_object_storage(value.begin(), value.size()));
}

std::shared_ptr<object_storage> vector_ref_object_storage::create(
    const std::shared_ptr<object>* data,
    long length)
{
    auto p = alloc(length);
    return std::shared_ptr<object_storage>(new (p) vector_ref_object_storage(data, length));
}

long vector_ref_object_storage::length(long dimension) const
{
    if (dimension != 0)
    {
        throw out_of_range("dimension out of range");
    }

    return _length;
}

long vector_ref_object_storage::get_integer(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw runtime_error("null reference.");
    }

    return element->storage().get_integer(0);
}

double vector_ref_object_storage::get_real(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw runtime_error("null reference.");
    }

    return element->storage().get_real(0);
}

uint8_t vector_ref_object_storage::get_byte(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw runtime_error("null reference.");
    }

    return element->storage().get_byte(0);
}

bool vector_ref_object_storage::get_boolean(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw runtime_error("null reference.");
    }

    return element->storage().get_boolean(0);
}

std::string_view vector_ref_object_storage::get_string(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw runtime_error("null reference.");
    }

    return element->storage().get_string(0);
}

std::shared_ptr<object> vector_ref_object_storage::get_object(long ordinal) const
{
    if (ordinal < 0 || ordinal >= _length)
    {
        throw out_of_range("ordinal out of range");
    }

    return cdata()[ordinal];
}
