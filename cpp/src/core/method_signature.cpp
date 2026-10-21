/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file method_signature.cpp
 * @brief Implementation of the method_signature class in the object model.
 */
#include <om.hpp>
#include <sstream>

using namespace std;
using namespace opendraft::core;

method_signature::method_signature(
    const std::string& class_name,
    const std::string& name,
    const std::string& return_type,
    const std::vector<std::string>& parameter_types)
    : _class_name(class_name),
      _name(name),
      _return_type(return_type),
      _parameter_types(parameter_types)
{
}

bool method_signature::operator==(const method_signature& other) const
{
    return *this <=> other == 0;
}

bool method_signature::operator!=(const method_signature& other) const
{
    return *this <=> other != 0;
}

bool method_signature::operator<(const method_signature& other) const
{
    return *this <=> other < 0;
}

bool method_signature::operator<=(const method_signature& other) const
{
    return *this <=> other <= 0;
}

bool method_signature::operator>(const method_signature& other) const
{
    return *this <=> other > 0;
}
bool method_signature::operator>=(const method_signature& other) const
{
    return *this <=> other >= 0;
}

strong_ordering method_signature::operator<=>(const method_signature& other) const
{
    strong_ordering result = _class_name <=> other._class_name;
    if (result != 0)
    {
        return result;
    }

    result = _name <=> other._name;
    if (result != 0)
    {
        return result;
    }

    result = _return_type <=> other._return_type;
    if (result != 0)
    {
        return result;
    }

    auto p_it = _parameter_types.begin();
    auto other_p_it = other._parameter_types.begin();
    for(; p_it != _parameter_types.end() && other_p_it != other._parameter_types.end(); ++p_it, ++other_p_it)
    {
        result = (*p_it) <=> (*other_p_it);
        if (result != 0)
        {
            return result;
        }
    }

    return _parameter_types.size() <=> other._parameter_types.size();
}

method_signature method_signature::create(
    const class_type& class_type,
    const method_declaration& method,
    bool is_static)
{
    std::vector<std::string> param_types;
    if (!is_static)
    {
        param_types.push_back(class_type.name());
    }

    for (const auto& param : method.parameters())
    {
        param_types.push_back(param.type() ? param.type()->name() : type_system::object_type_name);
    }

    string return_type;
    if (!method.is_template())
    {
        const function_declaration& func_decl = static_cast<const function_declaration&>(method);
        return_type = func_decl.return_type() ? func_decl.return_type()->name() : type_system::object_type_name;
    }

    return method_signature(
        class_type.name(),
        method.name(),
        return_type,
        param_types);
}

string method_signature::to_string() const
{
    stringstream ss;
    ss << _class_name << "::" << _name << "(";
    for (size_t i = 0; i < _parameter_types.size(); ++i)
    {
        if (i > 0)
        {
            ss << ",";
        }

        ss << _parameter_types[i];
    }

    ss << ")";
    if (!_return_type.empty())
    {
        ss << ":" << _return_type;
    }

    return ss.str();
}
