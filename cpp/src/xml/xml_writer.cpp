/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file xml_writer.cpp
 * @brief Contains the implementation of the xml_writer class.
 */
#include <xml_writer.hpp>

using namespace xml;
using namespace std;

xml_writer::xml_writer(ostream& os)
    : _os(os), _element_stack()
{
}

void xml_writer::write_start_element(const std::string& name)
{
    if (!_element_stack.empty())
    {
        auto& parent_elem = _element_stack.top();
        if (parent_elem.is_open)
        {
            _os << ">";
            parent_elem.is_open = false;
        }

        parent_elem.has_child_elements = true;
        _os << endl;
    }

    _os << string(indent_level() * 2, ' ') << "<" << name;
    _element_stack.push({name, true, false});
}

void xml_writer::write_end_element()
{
    if (_element_stack.empty())
    {
        throw std::logic_error("No element to end.");
    }

    auto& elem = _element_stack.top();

    if (elem.is_open)
    {
        _os << " />";
        _element_stack.pop();
        return;
    }
    else
    {
        write_full_end_element();
    }
}

void xml_writer::write_full_end_element()
{
    if (_element_stack.empty())
    {
        throw std::logic_error("No element to end.");
    }

    // pop before writing the end tag to have the correct indent level.
    auto elem = _element_stack.top();
    _element_stack.pop();

    if (elem.is_open)
    {
        _os << ">";
        elem.is_open = false;
    }

    if (elem.has_child_elements)
    {
        _os << endl;
        write_indent();
    }

    _os << "</" << elem.name << ">";
}

void xml_writer::write_element(const std::string& name, const std::string& content)
{
    write_start_element(name);
    auto& elem = _element_stack.top();
    elem.is_open = false; // Mark the element as not open since we are writing content
    _os << ">";
    write_text_content(content);
    write_full_end_element();
}

void xml_writer::write_attribute(const std::string& name, const std::string& value)
{
    if (_element_stack.empty() || !_element_stack.top().is_open)
    {
        throw std::logic_error("Cannot write attribute when no element is open.");
    }

    auto& elem = _element_stack.top();

    _os << " " << name << "=\"" << value << "\"";
}

void xml_writer::write_attribute(const std::string& name, const char* value)
{
    write_attribute(name, std::string(value));
}

void xml_writer::write_attribute(const std::string& name, int value)
{
    write_attribute(name, std::to_string(value));
}

void xml_writer::write_attribute(const std::string& name, double value)
{
    write_attribute(name, std::to_string(value));
}

void xml_writer::write_attribute(const std::string& name, bool value)
{
    string bool_str = value ? "true" : "false";
    write_attribute(name, bool_str);
}

void xml_writer::write_attribute(const std::string& name, char value)
{
    write_attribute(name, std::string(1, value));
}

void xml_writer::write_indent()
{
    _os << string(indent_level() * 2, ' ');
}

void xml_writer::write_attribute_value(const std::string& value)
{
    // TODO: escape special characters in the value if needed.
    _os << "\"" << value << "\"";
}

void xml_writer::write_text_content(const std::string& text)
{
    // TODO: escape special characters in the text if needed.
    _os << text;
}