/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file type_system_test.cpp
 * @brief Unit tests for the type_system class.
 */
#include <om.hpp>
#include <testfx.hpp>

using namespace opendraft::core;
using namespace testfx;
using namespace std;

/**
 * @brief Unit tests for the type_system class.
 */
class type_system_test : public test_class
{
public:
    static type_system_test instance;

    type_system_test();

    void instance_test();
    void boolean_type_test();
    void integer_type_test();
    void real_type_test();
    void byte_type_test();
    void string_type_test();
    void get_array_type_test();
    void create_boolean_test();
    void create_integer_test();
    void create_real_test();
    void create_byte_test();
    void create_string_test();
    void create_boolean_array_test();
    void create_integer_array_test();
    void create_real_array_test();
    void create_byte_array_test();
    void create_multi_dim_boolean_array_test();
    void create_multi_dim_integer_array_test();
    void create_multi_dim_real_array_test();
    void create_multi_dim_byte_array_test();
};

type_system_test type_system_test::instance;

type_system_test::type_system_test()
: test_class("type_system_test")
{
    add("instance_test", (test_method)&type_system_test::instance_test);
    add("boolean_type_test", (test_method)&type_system_test::boolean_type_test);
    add("integer_type_test", (test_method)&type_system_test::integer_type_test);
    add("real_type_test", (test_method)&type_system_test::real_type_test);
    add("byte_type_test", (test_method)&type_system_test::byte_type_test);
    add("string_type_test", (test_method)&type_system_test::string_type_test);
    add("get_array_type_test", (test_method)&type_system_test::get_array_type_test);
    add("create_boolean_test", (test_method)&type_system_test::create_boolean_test);
    add("create_integer_test", (test_method)&type_system_test::create_integer_test);
    add("create_real_test", (test_method)&type_system_test::create_real_test);
    add("create_byte_test", (test_method)&type_system_test::create_byte_test);
    add("create_string_test", (test_method)&type_system_test::create_string_test);
    add("create_boolean_array_test", (test_method)&type_system_test::create_boolean_array_test);
    add("create_integer_array_test", (test_method)&type_system_test::create_integer_array_test);
    add("create_real_array_test", (test_method)&type_system_test::create_real_array_test);
    add("create_byte_array_test", (test_method)&type_system_test::create_byte_array_test);
    add("create_multi_dim_boolean_array_test", (test_method)&type_system_test::create_multi_dim_boolean_array_test);
    add("create_multi_dim_integer_array_test", (test_method)&type_system_test::create_multi_dim_integer_array_test);
    add("create_multi_dim_real_array_test", (test_method)&type_system_test::create_multi_dim_real_array_test);
    add("create_multi_dim_byte_array_test", (test_method)&type_system_test::create_multi_dim_byte_array_test);
}

void type_system_test::instance_test()
{
    assert_not_null(type_system::instance.boolean_type());
}

void type_system_test::boolean_type_test()
{
    auto bool_type = type_system::instance.boolean_type();
    assert_not_null(bool_type);
    assert_equal(type_kind::TYPE_KIND_PRIMITIVE, bool_type->kind());
    auto primitive_bool_type = (primitive_type*)bool_type.get();
    assert_not_null(primitive_bool_type);
    assert_equal(primitive_kind::PRIMITIVE_KIND_BOOLEAN, primitive_bool_type->primitive_kind());
}

void type_system_test::integer_type_test()
{
    auto int_type = type_system::instance.integer_type();
    assert_not_null(int_type);
    assert_equal(type_kind::TYPE_KIND_PRIMITIVE, int_type->kind());
    auto primitive_int_type = (primitive_type*)int_type.get();
    assert_not_null(primitive_int_type);
    assert_equal(primitive_kind::PRIMITIVE_KIND_INTEGER, primitive_int_type->primitive_kind());
}

void type_system_test::real_type_test()
{
    auto real_type = type_system::instance.real_type();
    assert_not_null(real_type);
    assert_equal(type_kind::TYPE_KIND_PRIMITIVE, real_type->kind());
    auto primitive_real_type = (primitive_type*)real_type.get();
    assert_not_null(primitive_real_type);
    assert_equal(primitive_kind::PRIMITIVE_KIND_REAL, primitive_real_type->primitive_kind());
}

void type_system_test::byte_type_test()
{
    auto byte_type = type_system::instance.byte_type();
    assert_not_null(byte_type);
    assert_equal(type_kind::TYPE_KIND_PRIMITIVE, byte_type->kind());
    auto primitive_byte_type = (primitive_type*)byte_type.get();
    assert_not_null(primitive_byte_type);
    assert_equal(primitive_kind::PRIMITIVE_KIND_BYTE, primitive_byte_type->primitive_kind());
}

void type_system_test::string_type_test()
{
    auto string_type = type_system::instance.string_type();
    assert_not_null(string_type);
    assert_equal(type_kind::TYPE_KIND_PRIMITIVE, string_type->kind());
    auto primitive_string_type = (primitive_type*)string_type.get();
    assert_not_null(primitive_string_type);
    assert_equal(primitive_kind::PRIMITIVE_KIND_STRING, primitive_string_type->primitive_kind());
}

void type_system_test::get_array_type_test()
{
    auto at = type_system::instance.get_array_type(type_system::instance.integer_type());
    assert_not_null(at);
    assert_equal(type_kind::TYPE_KIND_ARRAY, at->kind());
    auto array_type_ptr = (array_type*)at.get();
    assert_not_null(array_type_ptr);
    assert_equal((size_t)1, array_type_ptr->dimension_count());
    assert_equal(type_system::instance.integer_type().get(), array_type_ptr->element_type().get());
}

void type_system_test::create_boolean_test()
{
    auto boolean_value = type_system::instance.create(true);
    assert_not_null(boolean_value);
    assert_equal(const_cast<const type*>(type_system::instance.boolean_type().get()), &boolean_value->type());
    assert_equal(true, boolean_value->storage().get_boolean(0));
}

void type_system_test::create_integer_test()
{
    auto integer_value = type_system::instance.create(42L);
    assert_not_null(integer_value);
    assert_equal(const_cast<const type*>(type_system::instance.integer_type().get()), &integer_value->type());
    assert_equal(42L, integer_value->storage().get_integer(0));
}

void type_system_test::create_real_test()
{
    auto real_value = type_system::instance.create(3.14);
    assert_not_null(real_value);
    assert_equal(const_cast<const type*>(type_system::instance.real_type().get()), &real_value->type());
    assert_equal(3.14, real_value->storage().get_real(0));
}

void type_system_test::create_byte_test()
{
    auto byte_value = type_system::instance.create((uint8_t)255);
    assert_not_null(byte_value);
    assert_equal(const_cast<const type*>(type_system::instance.byte_type().get()), &byte_value->type());
    assert_equal((uint8_t)255, byte_value->storage().get_byte(0));
}

void type_system_test::create_string_test()
{
    auto string_value = type_system::instance.create("hello");
    assert_not_null(string_value);
    assert_equal(const_cast<const type*>(type_system::instance.string_type().get()), &string_value->type());
    assert_equal(string_view("hello"), string_value->storage().get_string(0));
}

void type_system_test::create_boolean_array_test()
{
    auto boolean_array_value = type_system::instance.create({true, false, true});
    assert_not_null(boolean_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.boolean_type()).get()), &boolean_array_value->type());
    assert_equal(3L, boolean_array_value->storage().length());
    assert_equal(true, boolean_array_value->storage().get_boolean(0));
    assert_equal(false, boolean_array_value->storage().get_boolean(1));
    assert_equal(true, boolean_array_value->storage().get_boolean(2));
}

void type_system_test::create_integer_array_test()
{
    auto integer_array_value = type_system::instance.create({1L, 2L, 3L, 4L});
    assert_not_null(integer_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.integer_type()).get()), &integer_array_value->type());
    assert_equal(4L, integer_array_value->storage().length());
    assert_equal(1L, integer_array_value->storage().get_integer(0));
    assert_equal(2L, integer_array_value->storage().get_integer(1));
    assert_equal(3L, integer_array_value->storage().get_integer(2));
    assert_equal(4L, integer_array_value->storage().get_integer(3));
}

void type_system_test::create_real_array_test()
{
    auto real_array_value = type_system::instance.create({1.1, 2.2, 3.3});
    assert_not_null(real_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.real_type()).get()), &real_array_value->type());
    assert_equal(3L, real_array_value->storage().length());
    assert_equal(1.1, real_array_value->storage().get_real(0));
    assert_equal(2.2, real_array_value->storage().get_real(1));
    assert_equal(3.3, real_array_value->storage().get_real(2));
}

void type_system_test::create_byte_array_test()
{
    auto byte_array_value = type_system::instance.create({(uint8_t)1, (uint8_t)2, (uint8_t)3});
    assert_not_null(byte_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.byte_type()).get()), &byte_array_value->type());
    assert_equal(3L, byte_array_value->storage().length());
    assert_equal((uint8_t)1, byte_array_value->storage().get_byte(0));
    assert_equal((uint8_t)2, byte_array_value->storage().get_byte(1));
    assert_equal((uint8_t)3, byte_array_value->storage().get_byte(2));
}

void type_system_test::create_multi_dim_boolean_array_test()
{
    auto multi_dim_boolean_array_value = type_system::instance.create(
        {2, 2}, 
        {true, false, false, true});
    assert_not_null(multi_dim_boolean_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.boolean_type(), 2).get()), &multi_dim_boolean_array_value->type());
    assert_equal(2L, multi_dim_boolean_array_value->storage().length(0));
    assert_equal(2L, multi_dim_boolean_array_value->storage().length(1));
    assert_equal(true, multi_dim_boolean_array_value->storage().get_boolean(0));
    assert_equal(false, multi_dim_boolean_array_value->storage().get_boolean(1));
    assert_equal(false, multi_dim_boolean_array_value->storage().get_boolean(2));
    assert_equal(true, multi_dim_boolean_array_value->storage().get_boolean(3));
}

void type_system_test::create_multi_dim_integer_array_test()
{
    auto multi_dim_integer_array_value = type_system::instance.create(
        {2, 2}, 
        {1L, 2L, 3L, 4L});
    assert_not_null(multi_dim_integer_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.integer_type(), 2).get()), &multi_dim_integer_array_value->type());
    assert_equal(2L, multi_dim_integer_array_value->storage().length(0));
    assert_equal(2L, multi_dim_integer_array_value->storage().length(1));
    assert_equal(1L, multi_dim_integer_array_value->storage().get_integer(0));
    assert_equal(2L, multi_dim_integer_array_value->storage().get_integer(1));
    assert_equal(3L, multi_dim_integer_array_value->storage().get_integer(2));
    assert_equal(4L, multi_dim_integer_array_value->storage().get_integer(3));
}

void type_system_test::create_multi_dim_real_array_test()
{
    auto multi_dim_real_array_value = type_system::instance.create(
        {2, 2}, 
        {1.1, 2.2, 3.3, 4.4});
    assert_not_null(multi_dim_real_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.real_type(), 2).get()), &multi_dim_real_array_value->type());
    assert_equal(2L, multi_dim_real_array_value->storage().length(0));
    assert_equal(2L, multi_dim_real_array_value->storage().length(1));
    assert_equal(1.1, multi_dim_real_array_value->storage().get_real(0));
    assert_equal(2.2, multi_dim_real_array_value->storage().get_real(1));
    assert_equal(3.3, multi_dim_real_array_value->storage().get_real(2));
    assert_equal(4.4, multi_dim_real_array_value->storage().get_real(3));
}

void type_system_test::create_multi_dim_byte_array_test()
{
    auto multi_dim_byte_array_value = type_system::instance.create(
        {2L, 2L}, 
        {(uint8_t)0x01, (uint8_t)0x02, (uint8_t)0x03, (uint8_t)0x04});
    assert_not_null(multi_dim_byte_array_value);
    assert_equal(const_cast<const type*>(type_system::instance.get_array_type(type_system::instance.byte_type(), 2).get()), &multi_dim_byte_array_value->type());
    assert_equal(2L, multi_dim_byte_array_value->storage().length(0));
    assert_equal(2L, multi_dim_byte_array_value->storage().length(1));
    assert_equal((uint8_t)0x01, multi_dim_byte_array_value->storage().get_byte(0));
    assert_equal((uint8_t)0x02, multi_dim_byte_array_value->storage().get_byte(1));
    assert_equal((uint8_t)0x03, multi_dim_byte_array_value->storage().get_byte(2));
    assert_equal((uint8_t)0x04, multi_dim_byte_array_value->storage().get_byte(3));
}