/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file xml_writer.hpp
 * @brief Declares the xml_writer class and related functions.
 */
#pragma once

#ifndef __XML_WRITER_HPP__
#define __XML_WRITER_HPP__

#include <string>
#include <ostream>
#include <stack>

namespace opendraft::lang::tools
{
    /**
     * @brief A class for writing XML.
     */
    class xml_writer
    {
    public:
        xml_writer(std::ostream& os);
        ~xml_writer() = default;

        void write_start_element(const std::string& name);
        void write_end_element();
        void write_full_end_element();
        void write_element(const std::string& name, const std::string& content);
        void write_attribute(const std::string& name, const std::string& value);

    private:
        struct element_state
        {
            std::string name;
            bool is_open;
            bool has_child_elements;
        };

        std::ostream& _os;
        std::stack<element_state> _element_stack;

        inline size_t indent_level() const
        {
            return _element_stack.size();
        }

        void write_indent();
        void write_attribute_value(const std::string& value);
        void write_text_content(const std::string& text);

        // Disable copy semantics for xml_writer to prevent accidental copying.
        xml_writer(const xml_writer&) = delete;
        xml_writer& operator=(const xml_writer&) = delete;
    };
}

#endif /* __XML_WRITER_HPP__ */