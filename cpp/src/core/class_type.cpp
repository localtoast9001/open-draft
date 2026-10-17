/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file class_type.cpp
 * @brief Contains the definitions for the class_type class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;

class_type::class_type(
    const std::string& name,
    const std::shared_ptr<type>& base_type,
    std::initializer_list<field> fields,
    std::initializer_list<field> static_fields,
    std::initializer_list<std::shared_ptr<method_declaration>> methods,
    std::initializer_list<std::shared_ptr<method_declaration>> static_methods)
    : type(name),
      _base_type(base_type),
      _fields(fields),
      _static_fields(static_fields),
      _methods(methods),
      _static_methods(static_methods)
{
}

type_kind class_type::kind() const
{
    return TYPE_KIND_CLASS;
}