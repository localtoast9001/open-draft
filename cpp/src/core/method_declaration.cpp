/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file method_declaration.cpp
 * @brief Contains the definitions for the method_declaration class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;
using namespace std;

method_declaration::method_declaration(
    const string& name,
    const vector<parameter_declaration>& parameters)
    : _name(name),
      _parameters(parameters)
{
}