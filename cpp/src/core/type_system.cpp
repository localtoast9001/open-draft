/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file type_system.cpp
 * @brief Contains the implementation for the type system.
 */
#include <om.hpp>

using namespace opendraft::core;

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
