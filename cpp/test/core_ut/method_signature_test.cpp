/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file method_signature_test.cpp
 * @brief Unit tests for the method_signature class.
 */
#include <om.hpp>
#include <testfx.hpp>

using namespace opendraft::core;
using namespace std;
using namespace testfx;

class method_signature_test : public test_class
{
public:
    static method_signature_test instance;

    method_signature_test();

    void to_string_test();
    void comparison_test();
    void create_test();
    void copy_test();
    void move_test();
};

method_signature_test method_signature_test::instance;

method_signature_test::method_signature_test()
: test_class("method_signature_test")
{
    add("to_string_test", (test_method)&method_signature_test::to_string_test);
    add("comparison_test", (test_method)&method_signature_test::comparison_test);
    add("create_test", (test_method)&method_signature_test::create_test);
    add("copy_test", (test_method)&method_signature_test::copy_test);
    add("move_test", (test_method)&method_signature_test::move_test);
}

void method_signature_test::to_string_test()
{
    type_system ts;
    auto sig1 = method_signature(
        string("class_name"),
        string("method_name"),
        string("return_type"),
        {"type1", "type2"});
    auto actual = sig1.to_string();
    assert_equal(
        string("class_name::method_name(type1,type2):return_type"),
        actual);

    auto sig2 = method_signature(
        string("class_name"),
        string("method_name"),
        string(),
        {"type1", "type2"});
    auto actual2 = sig2.to_string();
    assert_equal(
        string("class_name::method_name(type1,type2)"),
        actual2);
}

void method_signature_test::comparison_test()
{
    type_system ts;
    auto sig1 = method_signature(
        string("class_name"),
        string("method_name"),
        string("return_type"),
        {"type1", "type2"});
    auto sig2 = method_signature(
        string("class_name"),
        string("method_name"),
        string(),
        {"type1", "type2"});
    auto sig3 = method_signature(
        string("class_name"),
        string("method_name"),
        string("return_type"),
        {"type1", "type2", "type3"});
    assert_equal(false, sig1 == sig2);
    assert_equal(true, sig1 != sig2);
    assert_equal(true, sig1 <=> sig2 > 0);
    assert_equal(false, sig1 == sig3);
    assert_equal(true, sig1 != sig3);
    assert_equal(true, sig1 <=> sig3 < 0);
}

void method_signature_test::create_test()
{
    type_system ts;
    auto f1p1 = parameter_declaration("p1", &ts.integer_type());
    auto f1p2 = parameter_declaration("p2", &ts.string_type());
    auto f1 = make_shared<function_declaration>(
        string("f1"),
        vector<parameter_declaration>({f1p1, f1p2}),
        &ts.boolean_type());
    auto t1p1 = parameter_declaration("p1", &ts.integer_type());
    auto t1 = make_shared<template_declaration>(
        string("t1"),
        vector<parameter_declaration>({t1p1}));
    auto fld1 = field(
        string("fld1"),
        &ts.boolean_type());
    initializer_list<shared_ptr<method_declaration>> empty_methods({});
    initializer_list<shared_ptr<method_declaration>> methods = {f1, t1};
    initializer_list<field> empty_fields({});
    initializer_list<field> fields = {fld1};

    auto cls = make_shared<class_type>(
        string("class_name"),
        nullptr);

    auto sig1 = method_signature::create(
        *cls,
        *f1);

    assert_equal(string("class_name"), sig1.class_name());
    assert_equal(string("f1"), sig1.name());
    assert_equal(string("boolean"), sig1.return_type());
    assert_equal((size_t)3, sig1.parameter_types().size());
    assert_equal(string("class_name"), sig1.parameter_types()[0]);
    assert_equal(string("integer"), sig1.parameter_types()[1]);
    assert_equal(string("string"), sig1.parameter_types()[2]);

    auto sig2 = method_signature::create(
        *cls,
        *t1);
    assert_equal(string("class_name"), sig2.class_name());
    assert_equal(string("t1"), sig2.name());
    assert_equal(string(""), sig2.return_type());
    assert_equal((size_t)2, sig2.parameter_types().size());
    assert_equal(string("class_name"), sig2.parameter_types()[0]);
    assert_equal(string("integer"), sig2.parameter_types()[1]);
}

void method_signature_test::copy_test()
{
    method_signature original(
        string("class_name"),
        string("method_name"),
        string("return_type"),
        {"type1", "type2"});
    auto copy = original;
    assert_equal(original.class_name(), copy.class_name());
    assert_equal(original.name(), copy.name());
    assert_equal(original.return_type(), copy.return_type());
    assert_equal(original.parameter_types().size(), copy.parameter_types().size());
}

void method_signature_test::move_test()
{
    method_signature original(
        string("class_name"),
        string("method_name"),
        string("return_type"),
        {"type1", "type2"});
    auto moved = std::move(original);
    assert_equal(string("class_name"), moved.class_name());
    assert_equal(string("method_name"), moved.name());
    assert_equal(string("return_type"), moved.return_type());
    assert_equal((size_t)2, moved.parameter_types().size());
}

