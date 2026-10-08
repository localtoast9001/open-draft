/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file template_declaration.cpp
 * @brief Contains the definitions for the template_declaration class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;
using namespace std;

template_declaration::template_declaration(
    const string& name,
    const vector<parameter_declaration>& parameters)
    : method_declaration(name, parameters)
{
}