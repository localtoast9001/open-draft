/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file field.cpp
 * @brief Contains the definitions for the field class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;
using namespace std;

field::field(
    const std::string& name,
    const std::shared_ptr<type>& field_type)
    : _name(name),
      _field_type(field_type)
{
}