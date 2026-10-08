/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file function_declaration.cpp
 * @brief Contains the definitions for the function_declaration class in the object model.
 */
#include <om.hpp>

using namespace opendraft::core;
using namespace std;

function_declaration::function_declaration(
    const string& name,
    const vector<parameter_declaration>& parameters,
    const std::shared_ptr<core::type>& return_type)
    : method_declaration(name, parameters),
      _return_type(return_type)
{
}