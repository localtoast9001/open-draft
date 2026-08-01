/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file parser.hpp
 * @brief Header file for the parser class.
 */
#pragma once
#ifndef __OPENDRAFT_LANG_PARSER_HPP__
#define __OPENDRAFT_LANG_PARSER_HPP__

#include "token_reader.hpp"
#include <functional>
#include "parse_node.hpp"

namespace opendraft::lang
{
    /**
     * @brief The parser class is responsible for parsing the OpenDraft language from tokens into an abstract syntax tree (AST).
     */
    class parser
    {
    public:
        parser(
            std::function<void(const message&)> log,
            token_reader& reader);
        virtual ~parser() = default;

        std::shared_ptr<program_parse_node> parse();

    private:
        /**
         * @brief A helper class that represents a token along with its preceding comments.
         */
        class token_with_comments
        {
        public:
            token_with_comments(
                const std::shared_ptr<opendraft::lang::token>& token,
                const std::list<std::shared_ptr<comment_token>>& preceding_comments);
            ~token_with_comments() = default;

            const std::shared_ptr<opendraft::lang::token>& token() const { return _token; }
            const std::list<std::shared_ptr<comment_token>>& preceding_comments() const { return _preceding_comments; }
        private:
            std::shared_ptr<opendraft::lang::token> _token;
            std::list<std::shared_ptr<comment_token>> _preceding_comments;
        };

        static bool is(const std::shared_ptr<token_with_comments>& token, keyword keyword);
        static bool is(const std::shared_ptr<token_with_comments>& token, symbol symbol);

        std::shared_ptr<import_parse_node> parse_import();
        std::shared_ptr<program_element_parse_node> parse_program_element();
        std::shared_ptr<class_parse_node> parse_class();
        std::shared_ptr<interface_parse_node> parse_interface();
        std::shared_ptr<interface_member_parse_node> parse_interface_member();
        std::shared_ptr<function_declaration_parse_node> parse_interface_function();
        std::shared_ptr<template_declaration_parse_node> parse_interface_template();
        bool parse_parameter_declarations(/*out*/ std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters);
        std::shared_ptr<parameter_declaration_parse_node> parse_parameter_declaration();
        std::shared_ptr<enum_parse_node> parse_enum();
        std::shared_ptr<enum_member_parse_node> parse_enum_member();
        std::shared_ptr<function_parse_node> parse_function();
        std::shared_ptr<template_parse_node> parse_template();
        std::shared_ptr<statement_parse_node> parse_core_statement();
        std::shared_ptr<block_statement_parse_node> parse_block_statement();
        std::shared_ptr<statement_parse_node> parse_statement();
        std::shared_ptr<break_statement_parse_node> parse_break_statement();
        std::shared_ptr<continue_statement_parse_node> parse_continue_statement();
        std::shared_ptr<return_statement_parse_node> parse_return_statement();
        std::shared_ptr<if_statement_parse_node> parse_if_statement();
        std::shared_ptr<for_statement_parse_node> parse_for_statement();
        std::shared_ptr<for_condition_parse_node> parse_for_condition();
        std::shared_ptr<throw_statement_parse_node> parse_throw_statement();
        std::shared_ptr<statement_parse_node> parse_trace_statement();
        std::shared_ptr<type_reference_parse_node> parse_type_reference();
        std::shared_ptr<expression_parse_node> parse_expression();
        std::shared_ptr<expression_parse_node> parse_logical_or_expression();
        std::shared_ptr<expression_parse_node> parse_logical_and_expression();
        std::shared_ptr<expression_parse_node> parse_bitwise_or_expression();
        std::shared_ptr<expression_parse_node> parse_bitwise_xor_expression();
        std::shared_ptr<expression_parse_node> parse_bitwise_and_expression();
        std::shared_ptr<expression_parse_node> parse_equality_expression();
        std::shared_ptr<expression_parse_node> parse_relational_expression();
        std::shared_ptr<expression_parse_node> parse_shift_expression();
        std::shared_ptr<expression_parse_node> parse_add_expression();
        std::shared_ptr<expression_parse_node> parse_multiply_expression();
        std::shared_ptr<expression_parse_node> parse_range_expression();
        std::shared_ptr<expression_parse_node> parse_unary_expression();
        std::shared_ptr<expression_parse_node> parse_array_expression();
        bool parse_array_row(/*out*/ std::list<std::shared_ptr<expression_parse_node>>& row);
        std::shared_ptr<expression_parse_node> parse_object_expression();
        std::shared_ptr<object_member_parse_node> parse_object_member();
        std::shared_ptr<expression_parse_node> parse_reference_expression();
        std::shared_ptr<reference_expression_parse_node> parse_member_reference(
            const std::shared_ptr<reference_expression_parse_node>& target);
        std::shared_ptr<reference_expression_parse_node> parse_index_expression(
            const std::shared_ptr<reference_expression_parse_node>& target);
        std::shared_ptr<reference_expression_parse_node> parse_call_expression(
            const std::shared_ptr<reference_expression_parse_node>& target);
        std::shared_ptr<argument_parse_node> parse_argument();

        bool expect(symbol symbol);
        bool expect(keyword keyword);
        std::shared_ptr<string_literal_token> expect_string_literal();
        std::shared_ptr<identifier_token> expect_identifier();
        std::shared_ptr<numeric_literal_token> expect_integer();

        std::shared_ptr<token_with_comments> peek();
        std::shared_ptr<token_with_comments> read();
        std::shared_ptr<token_with_comments> inner_read();

        parser(const parser&) = delete;
        parser& operator=(const parser&) = delete;

        std::function<void(const message&)> _log;
        token_reader& _reader;
        std::shared_ptr<token_with_comments> _peeked_token;
    };
}

#endif /* __OPENDRAFT_LANG_PARSER_HPP__ */