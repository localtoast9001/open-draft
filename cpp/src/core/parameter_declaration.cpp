/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file parameter_declaration.cpp
 * @brief Contains the definitions for the parameter_declaration class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;
using namespace std;

parameter_declaration::parameter_declaration(
    const std::string& name,
    const std::shared_ptr<core::type>& parameter_type)
    : _name(name),
      _type(parameter_type)
{
}