/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file type_system.cpp
 * @brief Contains the implementation for the type system.
 */
#include <om.hpp>
#include <sstream>
#include <object_storage_impl.hpp>

using namespace opendraft::core;
using namespace std;

type_system type_system::instance;

type_system::type_system()
{
    _boolean_type = std::make_shared<primitive_type>("boolean", PRIMITIVE_KIND_BOOLEAN);
    _integer_type = std::make_shared<primitive_type>("integer", PRIMITIVE_KIND_INTEGER);
    _real_type = std::make_shared<primitive_type>("real", PRIMITIVE_KIND_REAL);
    _byte_type = std::make_shared<primitive_type>("byte", PRIMITIVE_KIND_BYTE);
    _string_type = std::make_shared<primitive_type>("string", PRIMITIVE_KIND_STRING);
    _types_by_name[_boolean_type->name()] = _boolean_type;
    _types_by_name[_integer_type->name()] = _integer_type;
    _types_by_name[_real_type->name()] = _real_type;
    _types_by_name[_byte_type->name()] = _byte_type;
    _types_by_name[_string_type->name()] = _string_type;
}

std::shared_ptr<type> type_system::get_type_by_name(const std::string& name) const
{
    auto it = _types_by_name.find(name);
    if (it != _types_by_name.end())
    {
        return it->second;
    }

    return nullptr;
}

std::shared_ptr<type> type_system::get_array_type(
    const std::shared_ptr<type>& element_type,
    size_t dimension_count)
{
    if (dimension_count < 1)
    {
        throw std::invalid_argument("dimension_count must be at least 1");
    }

    if (!element_type)
    {
        throw std::invalid_argument("element_type must not be null");
    }

    stringstream name;
    name << element_type->name();
    name << "[";
    for (size_t i = 1; i < dimension_count; ++i)
    {
        name << ",";
    }

    name << "]";

    auto name_str = name.str();
    auto existing = get_type_by_name(name_str);
    if (existing)
    {
        return existing;
    }

    auto new_array_type = std::make_shared<array_type>(
        name_str,
        element_type,
        dimension_count);
    _types_by_name[name_str] = new_array_type;
    return new_array_type;
}

std::shared_ptr<object> type_system::create(bool value)
{
    return make_shared<object>(
        _boolean_type,
        make_shared<primitive_object_storage<bool>>(value));
}

std::shared_ptr<object> type_system::create(long value)
{
    return make_shared<object>(
        _integer_type,
        make_shared<primitive_object_storage<long>>(value));
}

std::shared_ptr<object> type_system::create(double value)
{
    return make_shared<object>(
        _real_type,
        make_shared<primitive_object_storage<double>>(value));
}

std::shared_ptr<object> type_system::create(uint8_t value)
{
    return make_shared<object>(
        _byte_type,
        make_shared<primitive_object_storage<uint8_t>>(value));
}

std::shared_ptr<object> type_system::create(const char* value)
{
    return create(std::string_view(value));
}

std::shared_ptr<object> type_system::create(const std::string_view& value)
{
    auto storage = vector_object_storage<uint8_t>::create(
        *this,
        reinterpret_cast<const uint8_t*>(value.data()),
        static_cast<long>(value.size()));
    return make_shared<object>(
        _string_type,
        storage);
}

std::shared_ptr<object> type_system::create(std::initializer_list<bool> value)
{
    auto t = get_array_type(_boolean_type, 1);
    return make_shared<object>(
        t,
        vector_object_storage<bool>::create(*this, value));
}

std::shared_ptr<object> type_system::create(std::initializer_list<long> value)
{
    auto t = get_array_type(_integer_type, 1);
    return make_shared<object>(
        t,
        vector_object_storage<long>::create(*this, value));
}

std::shared_ptr<object> type_system::create(std::initializer_list<double> value)
{
    auto t = get_array_type(_real_type, 1);
    return make_shared<object>(
        t,
        vector_object_storage<double>::create(*this, value));
}

std::shared_ptr<object> type_system::create(std::initializer_list<uint8_t> value)
{
    auto t = get_array_type(_byte_type, 1);
    return make_shared<object>(
        t,
        vector_object_storage<uint8_t>::create(*this, value));
}

std::shared_ptr<object> type_system::create(
    const std::shared_ptr<core::type>& type,
    std::initializer_list<std::shared_ptr<object>> values)
{
    return make_shared<object>(
        type,
        vector_ref_object_storage::create(values));
}

std::shared_ptr<object> type_system::create(
    std::initializer_list<long> dimensions,
    std::initializer_list<bool> value)
{
    auto t = get_array_type(_boolean_type, dimensions.size());
    return make_shared<object>(
        t,
        multi_dimensional_object_storage<bool>::create(*this, dimensions, value));
}

std::shared_ptr<object> type_system::create(
    std::initializer_list<long> dimensions,
    std::initializer_list<long> value)
{
    auto t = get_array_type(_integer_type, dimensions.size());
    return make_shared<object>(
        t,
        multi_dimensional_object_storage<long>::create(*this, dimensions, value));
}

std::shared_ptr<object> type_system::create(
    std::initializer_list<long> dimensions,
    std::initializer_list<double> value)
{
    auto t = get_array_type(_real_type, dimensions.size());
    return make_shared<object>(
        t,
        multi_dimensional_object_storage<double>::create(*this, dimensions, value));
}

std::shared_ptr<object> type_system::create(
    std::initializer_list<long> dimensions,
    std::initializer_list<uint8_t> value)
{
    auto t = get_array_type(_byte_type, dimensions.size());
    return make_shared<object>(
        t,
        multi_dimensional_object_storage<uint8_t>::create(*this, dimensions, value.begin()));
}

