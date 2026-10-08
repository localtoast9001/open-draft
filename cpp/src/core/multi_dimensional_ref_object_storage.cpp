/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file multi_dimensional_ref_object_storage.cpp
 * @brief Implementation of the multi_dimensional_ref_object_storage class.
 */
#include <object_storage_impl.hpp>

using namespace opendraft::core;
using namespace std;

multi_dimensional_ref_object_storage::multi_dimensional_ref_object_storage(
    const std::vector<long>& dimensions,
    const std::shared_ptr<object>* data,
    size_t total_element_count)
    : _dimensions(dimensions)
{
    const shared_ptr<object>* src = data;
    const shared_ptr<object>* end = data + total_element_count;
    shared_ptr<object>* dest = this->data();
    for (; src != end; src++, dest++)
    {
        new (dest) shared_ptr<object>(*src);
    }
}

multi_dimensional_ref_object_storage::multi_dimensional_ref_object_storage(
    const std::vector<long>& dimensions,
    size_t total_element_count,
    const std::shared_ptr<object>& value)
    : _dimensions(dimensions)
{
    shared_ptr<object>* dest = data();
    shared_ptr<object>* end = data() + total_element_count;
    for (; dest != end; dest++)
    {
        new (dest) shared_ptr<object>(value);
    }
}

multi_dimensional_ref_object_storage::~multi_dimensional_ref_object_storage()
{
    shared_ptr<object>* p = data();
    shared_ptr<object>* end = data() + total_element_count();
    for (; p != end; p++)
    {
        p->~shared_ptr<object>();
    }
}

uint8_t* multi_dimensional_ref_object_storage::alloc(
    const std::vector<long>& dimensions,
    size_t& total_element_count)
{
    total_element_count = get_total_element_count(dimensions);
    return new uint8_t[sizeof(multi_dimensional_ref_object_storage) + sizeof(shared_ptr<object>) * total_element_count];
}

size_t multi_dimensional_ref_object_storage::total_element_count() const
{
    return get_total_element_count(_dimensions);
}

std::shared_ptr<object_storage> multi_dimensional_ref_object_storage::create(
    const std::vector<long>& dimensions,
    const std::shared_ptr<object>* data)
{
    size_t size = 0;
    auto p = alloc(dimensions, size);
    auto storage = new (p) multi_dimensional_ref_object_storage(dimensions, data, size);
    return std::shared_ptr<object_storage>(static_cast<object_storage*>(storage));
}

std::shared_ptr<object_storage> multi_dimensional_ref_object_storage::create(
    const std::vector<long>& dimensions,
    const std::shared_ptr<object>& value)
{
    size_t size = 0;
    auto p = alloc(dimensions, size);
    auto storage = new (p) multi_dimensional_ref_object_storage(dimensions, size, value);
    return std::shared_ptr<object_storage>(static_cast<object_storage*>(storage));
}

std::shared_ptr<object_storage> multi_dimensional_ref_object_storage::create(
    const std::vector<long>& dimensions,
    std::initializer_list<std::shared_ptr<object>> values)
{
    if (values.size() != get_total_element_count(dimensions))
    {
        throw std::invalid_argument("Initializer list size does not match total element count.");
    }

    return create(dimensions, values.begin());
}

long multi_dimensional_ref_object_storage::length(long dimension) const
{
    if (dimension < 0 || dimension >= static_cast<long>(_dimensions.size()))
    {
        throw std::out_of_range("Dimension index out of range.");
    }

    return _dimensions[dimension];
}

long multi_dimensional_ref_object_storage::get_integer(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw std::runtime_error("Element is null.");
    }

    return element->storage().get_integer(0);
}

double multi_dimensional_ref_object_storage::get_real(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw std::runtime_error("Element is null.");
    }

    return element->storage().get_real(0);
}

uint8_t multi_dimensional_ref_object_storage::get_byte(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw std::runtime_error("Element is null.");
    }

    return element->storage().get_byte(0);
}

bool multi_dimensional_ref_object_storage::get_boolean(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw std::runtime_error("Element is null.");
    }

    return element->storage().get_boolean(0);
}

std::string_view multi_dimensional_ref_object_storage::get_string(long ordinal) const
{
    auto element = get_object(ordinal);
    if (!element)
    {
        throw std::runtime_error("Element is null.");
    }

    return element->storage().get_string(0);
}

std::shared_ptr<object> multi_dimensional_ref_object_storage::get_object(long ordinal) const
{
    if (ordinal < 0 || ordinal >= static_cast<long>(total_element_count()))
    {
        throw std::out_of_range("Ordinal index out of range.");
    }

    return cdata()[ordinal];
}
