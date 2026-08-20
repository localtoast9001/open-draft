/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file parse_tree_xml_exporter.hpp
 * @brief Contains the declaration of the parse_tree_xml_exporter class.
 */
#pragma once
#ifndef __OPENDRAFT_LANG_TOOLS_PARSE_TREE_XML_EXPORTER_HPP__
#define __OPENDRAFT_LANG_TOOLS_PARSE_TREE_XML_EXPORTER_HPP__

#include <ostream>

#include "../parse_node.hpp"

namespace opendraft::lang::tools
{
    /**
     * @brief A class that exports a parse tree to XML format.
     */
    class parse_tree_xml_exporter
    {
    public:
        parse_tree_xml_exporter(std::ostream& os);
        ~parse_tree_xml_exporter() = default;

        void export_program(const program_parse_node& root);

    private:
        std::ostream& _os;

        parse_tree_xml_exporter(const parse_tree_xml_exporter&) = delete;
        parse_tree_xml_exporter& operator=(const parse_tree_xml_exporter&) = delete;
    };
}

#endif /* __OPENDRAFT_LANG_TOOLS_PARSE_TREE_XML_EXPORTER_HPP__ */
