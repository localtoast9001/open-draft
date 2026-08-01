/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file parser.cpp
 * @brief Implementation file for the parser class.
 */

#include <parser.hpp>
#include <message_utility.hpp>

using namespace std;
using namespace opendraft::lang;

parser::parser(
    function<void(const message&)> log,
    token_reader& reader)
    : _log(log), _reader(reader)
{
}

parser::token_with_comments::token_with_comments(
    const shared_ptr<opendraft::lang::token>& token,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : _token(token), _preceding_comments(preceding_comments)
{
}

shared_ptr<program_parse_node> parser::parse()
{
    list<shared_ptr<import_parse_node>> imports;
    list<shared_ptr<program_element_parse_node>> program_elements;

    auto start = peek();
    if (!start)
    {
        _log(message_utility::unexpected_end_of_file(_reader.current_source()));
        return nullptr;
    }

    auto token = start;
    while (is(token, keyword::KEYWORD_IMPORT))
    {
        auto import_node = parse_import();
        if (!import_node)
        {
            return nullptr;
        }

        imports.push_back(import_node);
        token = peek();
    }

    while (token)
    {
        auto element = parse_program_element();
        if (!element)
        {
            return nullptr;
        }

        program_elements.push_back(element);
        token = peek();
    }

    return make_shared<program_parse_node>(
        imports,
        program_elements,
        start->token(),
        start->preceding_comments());
}

bool parser::is(const shared_ptr<token_with_comments>& token, keyword keyword)
{
    if (!token || !token->token())
    {
        return false;
    }
    
    auto token_ptr = token->token();
    if (token_ptr->type() != token::KEYWORD)
    {
        return false;
    }

    auto keyword_token_ptr = static_pointer_cast<keyword_token>(token_ptr);
    return keyword_token_ptr->value() == keyword;
}

bool parser::is(const shared_ptr<token_with_comments>& token, symbol symbol)
{
    if (!token || !token->token())
    {
        return false;
    }
    
    auto token_ptr = token->token();
    if (token_ptr->type() != token::SYMBOL)
    {
        return false;
    }

    auto symbol_token_ptr = static_pointer_cast<symbol_token>(token_ptr);
    return symbol_token_ptr->value() == symbol;
}

shared_ptr<import_parse_node> parser::parse_import()
{
    auto token = peek();
    if (!expect(keyword::KEYWORD_IMPORT))
    {
        return nullptr;
    }

    auto module_name_token = expect_string_literal();
    if (!module_name_token)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<import_parse_node>(
        module_name_token->value(),
        token->token(),
        token->preceding_comments());
}

shared_ptr<program_element_parse_node> parser::parse_program_element()
{
    auto token = peek();
    if (!token)
    {
        // checked by the caller.
        return nullptr;
    }

    if (is(token, keyword::KEYWORD_CLASS))
    {
        return parse_class();
    }
    else if (is(token, keyword::KEYWORD_INTERFACE))
    {
        return parse_interface();
    }
    else if (is(token, keyword::KEYWORD_ENUM))
    {
        return parse_enum();
    }
    else if (is(token, keyword::KEYWORD_FUNCTION))
    {
        return parse_function();
    }
    else if (is(token, keyword::KEYWORD_TEMPLATE))
    {
        return parse_template();
    }
    else
    {
        return parse_core_statement();
    }
}

shared_ptr<class_parse_node> parser::parse_class()
{
    throw std::logic_error("Not implemented.");
}

shared_ptr<interface_parse_node> parser::parse_interface()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_INTERFACE))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    auto token = peek();
    if (token && is(token, symbol::SYMBOL_COLON))
    {
        read();
        auto base_type_reference = parse_type_reference();
        if (!base_type_reference)
        {
            return nullptr;
        }
    }

    list<shared_ptr<interface_member_parse_node>> members;
    if (!expect(symbol::SYMBOL_LEFT_BRACE))
    {
        return nullptr;
    }

    token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_BRACE))
    {
        auto member = parse_interface_member();
        if (!member)
        {
            return nullptr;
        }

        members.push_back(member);
        token = peek();
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACE))
    {
        return nullptr;
    }

    return make_shared<interface_parse_node>(
        name_token->name(),
        members,
        start->token(),
        start->preceding_comments());
}

shared_ptr<interface_member_parse_node> parser::parse_interface_member()
{
    auto token = peek();
    if (!token)
    {
        // checked by the caller.
        return nullptr;
    }

    if (is(token, keyword::KEYWORD_FUNCTION))
    {
        return parse_interface_function();
    }
    else if (is(token, keyword::KEYWORD_TEMPLATE))
    {
        return parse_interface_template();
    }
    else
    {
        _log(message_utility::unexpected_token(
            token->token(),
            _reader.current_source()));
        return nullptr;
    }
}

shared_ptr<function_declaration_parse_node> parser::parse_interface_function()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_FUNCTION))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    list<shared_ptr<parameter_declaration_parse_node>> parameters;
    if (!parse_parameter_declarations(parameters))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<function_declaration_parse_node>(
        name_token->name(),
        parameters,
        start->token(),
        start->preceding_comments());   
}

shared_ptr<template_declaration_parse_node> parser::parse_interface_template()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_TEMPLATE))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    list<shared_ptr<parameter_declaration_parse_node>> parameters;
    if (!parse_parameter_declarations(parameters))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<template_declaration_parse_node>(
        name_token->name(),
        parameters,
        start->token(),
        start->preceding_comments());
}

bool parser::parse_parameter_declarations(
    /*out*/ list<shared_ptr<parameter_declaration_parse_node>>& parameters)
{
    if (!expect(symbol::SYMBOL_LEFT_PAREN))
    {
        return false;
    }

    auto token = peek();
    if (token && !is(token, symbol::SYMBOL_RIGHT_PAREN))
    {
        auto parameter = parse_parameter_declaration();
        if (!parameter)
        {
            return false;
        }

        parameters.push_back(parameter);
        token = peek();
        while (token && is(token, symbol::SYMBOL_COMMA))
        {
            read();
            parameter = parse_parameter_declaration();
            if (!parameter)
            {
                return false;
            }

            parameters.push_back(parameter);
            token = peek();
        }
    }

    return expect(symbol::SYMBOL_RIGHT_PAREN);
}

shared_ptr<parameter_declaration_parse_node> parser::parse_parameter_declaration()
{
    auto start = peek();
    auto type = parse_type_reference();
    if (!type)
    {
        return nullptr;
    }

    auto token = peek();
    shared_ptr<identifier_token> name_token;
    if (token && token->token()->type() == token::IDENTIFIER)
    {
        name_token = static_pointer_cast<identifier_token>(token->token());
        read();
    }
    else
    {
        name_token = static_pointer_cast<identifier_token>(type->start());
        type = nullptr;
    }

    token = peek();
    shared_ptr<expression_parse_node> default_value;
    if (token && is(token, symbol::SYMBOL_ASSIGN))
    {
        read();
        default_value = parse_expression();
        if (!default_value)
        {
            return nullptr;
        }
    }

    return make_shared<parameter_declaration_parse_node>(
        name_token->name(),
        type,
        default_value,
        start->token(),
        start->preceding_comments());
}

shared_ptr<enum_parse_node> parser::parse_enum()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_ENUM))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    list<shared_ptr<enum_member_parse_node>> members;
    if (!expect(symbol::SYMBOL_LEFT_BRACE))
    {
        return nullptr;
    }

    auto member = parse_enum_member();
    if (!member)
    {
        return nullptr;
    }

    members.push_back(member);

    auto comma_token = peek();
    while (comma_token && is(comma_token, symbol::SYMBOL_COMMA))
    {
        read();
        member = parse_enum_member();
        if (!member)
        {
            return nullptr;
        }

        members.push_back(member);

        comma_token = peek();
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACE))
    {
        return nullptr;
    }

    return make_shared<enum_parse_node>(
        name_token->name(),
        members,
        start->token(),
        start->preceding_comments());
}

shared_ptr<enum_member_parse_node> parser::parse_enum_member()
{
    auto start = peek();
    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    long value = 0;
    bool has_value = false;
    auto token = peek();
    if (token && is(token, symbol::SYMBOL_ASSIGN))
    {
        read();
        auto value_token = expect_integer();
        if (!value_token)
        {
            return nullptr;
        }
        value = value_token->integer_value();
        has_value = true;
    }

    return make_shared<enum_member_parse_node>(
        name_token->name(),
        has_value,
        value,
        start->token(),
        start->preceding_comments());
}

shared_ptr<function_parse_node> parser::parse_function()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_FUNCTION))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    list<shared_ptr<parameter_declaration_parse_node>> parameters;
    if (!parse_parameter_declarations(parameters))
    {
        return nullptr;
    }

    auto body = parse_block_statement();
    if (!body)
    {
        return nullptr;
    }

    return make_shared<function_parse_node>(
        name_token->name(),
        parameters,
        body,
        start->token(),
        start->preceding_comments());
}

shared_ptr<template_parse_node> parser::parse_template()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_TEMPLATE))
    {
        return nullptr;
    }

    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    list<shared_ptr<parameter_declaration_parse_node>> parameters;
    if (!parse_parameter_declarations(parameters))
    {
        return nullptr;
    }

    auto body = parse_block_statement();
    if (!body)
    {
        return nullptr;
    }
    
    return make_shared<template_parse_node>(
        name_token->name(),
        parameters,
        body,
        start->token(),
        start->preceding_comments());
}

shared_ptr<statement_parse_node> parser::parse_core_statement()
{
    auto start = peek();
    if (!start)
    {
        _log(message_utility::unexpected_end_of_file(_reader.current_source()));
        return nullptr;
    }

    if (is(start, keyword::KEYWORD_IF))
    {
        return parse_if_statement();
    }
    
    if (is(start, keyword::KEYWORD_FOR))
    {
        return parse_for_statement();
    }
    
    if (is(start, keyword::KEYWORD_BREAK))
    {
        return parse_break_statement();
    }

    if (is(start, keyword::KEYWORD_CONTINUE))
    {
        return parse_continue_statement();
    }

    if (is(start, keyword::KEYWORD_RETURN))
    {
        return parse_return_statement();
    }

    if (is(start, keyword::KEYWORD_THROW))
    {
        return parse_throw_statement();
    }

    if (is(start, keyword::KEYWORD_ERROR) ||
        is(start, keyword::KEYWORD_WARN) ||
        is(start, keyword::KEYWORD_INFO) ||
        is(start, keyword::KEYWORD_VERBOSE) ||
        is(start, keyword::KEYWORD_DEBUG))
    {
        return parse_trace_statement();
    }

    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    if (expr->type() == parse_node_type::PARSE_NODE_CALL_EXPRESSION)
    {
        if (!expect(symbol::SYMBOL_SEMICOLON))
        {
            return nullptr;
        }

        return call_statement_parse_node::from_call_expression(
            static_pointer_cast<call_expression_parse_node>(expr));
    }

    if (expr->type() == parse_node_type::PARSE_NODE_VARIABLE_REFERENCE ||
        expr->type() == parse_node_type::PARSE_NODE_MEMBER_REFERENCE_EXPRESSION)
    {
        auto ref_expr = static_pointer_cast<reference_expression_parse_node>(expr);
        auto type_ref = ref_expr->to_type_reference();
        if (type_ref)
        {
            auto var_name = type_ref->names().front();
            auto token = peek();

            shared_ptr<identifier_token> var_name_token;
            if (token && token->token()->type() == token::token_type::IDENTIFIER)
            {
                var_name_token = static_pointer_cast<identifier_token>(token->token());
                var_name = var_name_token->name();
                read();
            }
            else if (type_ref->names().size() > 1)
            {
                _log(message_utility::variable_name_expected_after_type_reference(
                    token ? token->token() : nullptr,
                    _reader.current_source()));
                return nullptr;
            }
            else
            {
                type_ref = nullptr;
            }

            if (!expect(symbol::SYMBOL_ASSIGN))
            {
                return nullptr;
            }

            auto value = parse_expression();
            if (!value)
            {
                return nullptr;
            }

            if (!expect(symbol::SYMBOL_SEMICOLON))
            {
                return nullptr;
            }

            return make_shared<variable_definition_parse_node>(
                var_name,
                type_ref,
                value,
                start->token(),
                start->preceding_comments());
        }
    }

    _log(message_utility::unexpected_token(
        start->token(),
        _reader.current_source()));
    return nullptr;
}

shared_ptr<block_statement_parse_node> parser::parse_block_statement()
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_LEFT_BRACE))
    {
        return nullptr;
    }

    list<shared_ptr<statement_parse_node>> statements;
    auto token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_BRACE))
    {
        if (is(token, symbol::SYMBOL_SEMICOLON))
        {
            read();
        }
        else
        {
            auto statement = parse_core_statement();
            if (!statement)
            {
                return nullptr;
            }

            statements.push_back(statement);
        }

        token = peek();
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACE))
    {
        return nullptr;
    }

    return make_shared<block_statement_parse_node>(
        statements,
        start->token(),
        start->preceding_comments());
}

shared_ptr<statement_parse_node> parser::parse_statement()
{
    auto start = peek();
    if (start && is(start, symbol::SYMBOL_LEFT_BRACE))
    {
        return parse_block_statement();
    }
    else
    {
        return parse_core_statement();
    }
}

shared_ptr<break_statement_parse_node> parser::parse_break_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_BREAK))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<break_statement_parse_node>(
        start->token(),
        start->preceding_comments());
}

shared_ptr<continue_statement_parse_node> parser::parse_continue_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_CONTINUE))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<continue_statement_parse_node>(
        start->token(),
        start->preceding_comments());
}

shared_ptr<return_statement_parse_node> parser::parse_return_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_RETURN))
    {
        return nullptr;
    }

    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<return_statement_parse_node>(
        expr,
        start->token(),
        start->preceding_comments());
}

shared_ptr<if_statement_parse_node> parser::parse_if_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_IF))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_LEFT_PAREN))
    {
        return nullptr;
    }

    auto condition = parse_expression();
    if (!condition)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_RIGHT_PAREN))
    {
        return nullptr;
    }

    auto then_branch = parse_statement();
    if (!then_branch)
    {
        return nullptr;
    }

    shared_ptr<statement_parse_node> else_branch;
    auto token = peek();
    if (token && is(token, keyword::KEYWORD_ELSE))
    {
        read();
        else_branch = parse_statement();
        if (!else_branch)
        {
            return nullptr;
        }
    }

    return make_shared<if_statement_parse_node>(
        condition,
        then_branch,
        else_branch,
        start->token(),
        start->preceding_comments());
}

shared_ptr<for_statement_parse_node> parser::parse_for_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_FOR))
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_LEFT_PAREN))
    {
        return nullptr;
    }

    list<shared_ptr<for_condition_parse_node>> conditions;
    auto condition = parse_for_condition();
    if (!condition)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_SEMICOLON))
    {
        read();
        conditions.push_back(condition);
        condition = parse_for_condition();
        if (!condition)
        {
            return nullptr;
        }

        token = peek();
    }
    
    if (!expect(symbol::SYMBOL_RIGHT_PAREN))
    {
        return nullptr;
    }

    auto body = parse_statement();
    if (!body)
    {
        return nullptr;
    }

    return make_shared<for_statement_parse_node>(
        conditions,
        body,
        start->token(),
        start->preceding_comments());
}

shared_ptr<for_condition_parse_node> parser::parse_for_condition()
{
    auto start = peek();

    auto type_ref = parse_type_reference();
    if (!type_ref)
    {
        return nullptr;
    }

    auto token = peek();
    list<string> var_names;
    if (token && token->token()->type() == token::token_type::IDENTIFIER)
    {
        auto name_token = static_pointer_cast<identifier_token>(token->token());
        var_names.push_back(name_token->name());
        read();
    }
    else
    {
        if (type_ref->names().size() > 1)
        {
            _log(message_utility::variable_name_expected_after_type_reference(
                token ? token->token() : nullptr,
                _reader.current_source()));
            return nullptr;
        }

        var_names.push_back(type_ref->names().front());
        type_ref = nullptr;
    }

    while (token && is(token, symbol::SYMBOL_COMMA))
    {
        read();
        token = peek();
        if (!token || token->token()->type() != token::token_type::IDENTIFIER)
        {
            _log(message_utility::identifier_expected(
                token ? token->token() : nullptr,
                _reader.current_source()));
            return nullptr;
        }

        auto name_token = static_pointer_cast<identifier_token>(token->token());
        var_names.push_back(name_token->name());
        read();
        token = peek();
    }

    if (!expect(symbol::SYMBOL_COLON))
    {
        return nullptr;
    }

    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    return make_shared<for_condition_parse_node>(
        var_names,
        expr,
        type_ref,
        start->token(),
        start->preceding_comments());
}

shared_ptr<throw_statement_parse_node> parser::parse_throw_statement()
{
    auto start = peek();
    if (!expect(keyword::KEYWORD_THROW))
    {
        return nullptr;
    }

    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<throw_statement_parse_node>(
        expr,
        start->token(),
        start->preceding_comments());
}

shared_ptr<statement_parse_node> parser::parse_trace_statement()
{
    auto start = read();
    if (!start)
    {
        return nullptr;
    }

    shared_ptr<keyword_token> keywordToken = static_pointer_cast<keyword_token>(start->token());
    trace_statement_severity severity;
    switch (keywordToken->value())
    {
        case keyword::KEYWORD_ERROR:
            severity = trace_statement_severity::TRACE_SEVERITY_ERROR;
            break;
        case keyword::KEYWORD_WARN:
            severity = trace_statement_severity::TRACE_SEVERITY_WARNING;
            break;
        case keyword::KEYWORD_INFO:
            severity = trace_statement_severity::TRACE_SEVERITY_INFO;
            break;
        case keyword::KEYWORD_VERBOSE:
            severity = trace_statement_severity::TRACE_SEVERITY_VERBOSE;
            break;
        case keyword::KEYWORD_DEBUG:
            severity = trace_statement_severity::TRACE_SEVERITY_DEBUG;
            break;
        default:
            throw runtime_error("Internal Error: Invalid trace keyword.");
    }

    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_SEMICOLON))
    {
        return nullptr;
    }

    return make_shared<trace_statement_parse_node>(
        severity,
        expr,
        start->token(),
        start->preceding_comments());
}

shared_ptr<type_reference_parse_node> parser::parse_type_reference()
{
    list<string> names;
    auto start = peek();
    auto name_token = expect_identifier();
    if (!name_token)
    {
        return nullptr;
    }

    names.push_back(name_token->name());
    auto token = peek();
    while (token && is(token, symbol::SYMBOL_DOT))
    {
        read();
        name_token = expect_identifier();
        if (!name_token)
        {
            return nullptr;
        }

        names.push_back(name_token->name());
        token = peek();
    }

    return make_shared<type_reference_parse_node>(
        names,
        start->token(),
        start->preceding_comments());
}

shared_ptr<expression_parse_node> parser::parse_expression()
{
    auto inner = parse_logical_or_expression();
    if (!inner)
    {
        return nullptr;
    }

    auto token = peek();
    if (token && is(token, symbol::SYMBOL_QUESTION))
    {
        read();
        auto true_expr = parse_expression();
        if (!true_expr)
        {
            return nullptr;
        }

        if (!expect(symbol::SYMBOL_COLON))
        {
            return nullptr;
        }

        auto false_expr = parse_expression();
        if (!false_expr)
        {
            return nullptr;
        }

        return make_shared<conditional_expression_parse_node>(
            inner,
            true_expr,
            false_expr,
            inner->start(),
            inner->preceding_comments());
    }

    return inner;
}

shared_ptr<expression_parse_node> parser::parse_logical_or_expression()
{
    auto term = parse_logical_and_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_DOUBLE_PIPE))
    {
        read();
        auto next_term = parse_logical_and_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<logical_or_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_logical_and_expression()
{
    auto term = parse_bitwise_or_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_DOUBLE_AMPERSAND))
    {
        read();
        auto next_term = parse_bitwise_or_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<logical_and_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_bitwise_or_expression()
{
    auto term = parse_bitwise_xor_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_PIPE))
    {
        read();
        auto next_term = parse_bitwise_xor_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<bitwise_or_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_bitwise_xor_expression()
{
    auto term = parse_bitwise_and_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_CARET))
    {
        read();
        auto next_term = parse_bitwise_and_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<bitwise_xor_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_bitwise_and_expression()
{
    auto term = parse_equality_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && is(token, symbol::SYMBOL_AMPERSAND))
    {
        read();
        auto next_term = parse_equality_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<bitwise_and_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_equality_expression()
{
    auto term = parse_relational_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && (is(token, symbol::SYMBOL_EQUALS) || is(token, symbol::SYMBOL_NOT_EQUALS)))
    {
        bool is_inequality = is(token, symbol::SYMBOL_NOT_EQUALS);
        read();
        auto next_term = parse_relational_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<equality_expression_parse_node>(
            term,
            next_term,
            is_inequality,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_relational_expression()
{
    auto term = parse_shift_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && (
        is(token, symbol::SYMBOL_LESS_THAN) || 
        is(token, symbol::SYMBOL_LESS_THAN_EQUALS) ||
        is(token, symbol::SYMBOL_GREATER_THAN) ||
        is(token, symbol::SYMBOL_GREATER_THAN_EQUALS) ||
        is(token, keyword::KEYWORD_IN)))
    {
        relational_operator op = relational_operator::RELATIONAL_OPERATOR_IN_SET;
        if(!is(token, keyword::KEYWORD_IN))
        {
            symbol symbol_value = static_pointer_cast<symbol_token>(token->token())->value();
            switch (symbol_value)
            {
                case symbol::SYMBOL_LESS_THAN:
                    op = relational_operator::RELATIONAL_OPERATOR_LESS_THAN;
                    break;
                case symbol::SYMBOL_LESS_THAN_EQUALS:
                    op = relational_operator::RELATIONAL_OPERATOR_LESS_THAN_OR_EQUAL;
                    break;
                case symbol::SYMBOL_GREATER_THAN:
                    op = relational_operator::RELATIONAL_OPERATOR_GREATER_THAN;
                    break;
                case symbol::SYMBOL_GREATER_THAN_EQUALS:
                    op = relational_operator::RELATIONAL_OPERATOR_GREATER_THAN_OR_EQUAL;
                    break;
                default:
                    throw logic_error("Internal Error: Invalid relational operator.");
            }
        }

        auto next_term = parse_shift_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<relational_expression_parse_node>(
            term,
            next_term,
            op,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_shift_expression()
{
    auto term = parse_add_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && (is(token, symbol::SYMBOL_LEFT_SHIFT) || is(token, symbol::SYMBOL_RIGHT_SHIFT)))
    {
        symbol shift_symbol = static_pointer_cast<symbol_token>(token->token())->value();
        shift_operator op = shift_symbol == symbol::SYMBOL_LEFT_SHIFT ? 
            shift_operator::SHIFT_OPERATOR_LEFT_SHIFT : 
            shift_operator::SHIFT_OPERATOR_RIGHT_SHIFT;
        read();
        auto next_term = parse_add_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<shift_expression_parse_node>(
            term,
            next_term,
            op,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_add_expression()
{
    auto term = parse_multiply_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && (is(token, symbol::SYMBOL_PLUS) || is(token, symbol::SYMBOL_MINUS)))
    {
        bool is_subtraction = is(token, symbol::SYMBOL_MINUS);
        read();
        auto next_term = parse_multiply_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<add_expression_parse_node>(
            term,
            next_term,
            is_subtraction,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_multiply_expression()
{
    auto term = parse_range_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    while (token && 
        (is(token, symbol::SYMBOL_STAR) || 
         is(token, symbol::SYMBOL_SLASH) ||
         is(token, symbol::SYMBOL_PERCENT) ))
    {
        mul_operator op = mul_operator::MUL_OPERATOR_MODULO;
        symbol symbol_value = static_pointer_cast<symbol_token>(token->token())->value();
        switch (symbol_value)
        {
            case symbol::SYMBOL_STAR:
                op = mul_operator::MUL_OPERATOR_MULTIPLY;
                break;
            case symbol::SYMBOL_SLASH:
                op = mul_operator::MUL_OPERATOR_DIVIDE;
                break;
            case symbol::SYMBOL_PERCENT:
                op = mul_operator::MUL_OPERATOR_MODULO;
                break;
            default:
                throw logic_error("Internal Error: Invalid multiplication operator.");
        }

        read();
        auto next_term = parse_range_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<mul_expression_parse_node>(
            term,
            next_term,
            op,
            term->start(),
            term->preceding_comments());

        token = peek();
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_range_expression()
{
    auto term = parse_unary_expression();
    if (!term)
    {
        return nullptr;
    }

    auto token = peek();
    if (token && is(token, symbol::SYMBOL_DOTDOT))
    {
        read();
        auto next_term = parse_unary_expression();
        if (!next_term)
        {
            return nullptr;
        }

        term = make_shared<range_expression_parse_node>(
            term,
            next_term,
            term->start(),
            term->preceding_comments());
    }

    return term;
}

shared_ptr<expression_parse_node> parser::parse_unary_expression()
{
    auto token = peek();
    if (!token)
    {
        return nullptr;
    }

    // Handle unary operators here (e.g., +, -, !, ~)
    if (is(token, symbol::SYMBOL_PLUS) ||
        is(token, symbol::SYMBOL_MINUS) ||
        is(token, symbol::SYMBOL_BANG) ||
        is(token, symbol::SYMBOL_TILDE))
    {
        symbol unary_symbol = static_pointer_cast<symbol_token>(token->token())->value();
        unary_operator op;
        bool has_operator = false;
        switch (unary_symbol)
        {
            case symbol::SYMBOL_MINUS:
                op = unary_operator::UNARY_OPERATOR_NEGATION;
                has_operator = true;
                break;
            case symbol::SYMBOL_BANG:
                op = unary_operator::UNARY_OPERATOR_LOGICAL_NOT;
                has_operator = true;
                break;
            case symbol::SYMBOL_TILDE:
                op = unary_operator::UNARY_OPERATOR_BITWISE_NOT;
                has_operator = true;
                break;
        }

        read();
        auto operand = parse_unary_expression();
        if (!operand)
        {
            return nullptr;
        }

        if (!has_operator)
        {
            return operand;
        }

        return make_shared<unary_expression_parse_node>(
            op,
            operand,
            token->token(),
            token->preceding_comments());
    }

    if (is(token, symbol::SYMBOL_LEFT_PAREN))
    {
        read();
        auto inner = parse_expression();
        if (!inner)
        {
            return nullptr;
        }

        if (!expect(symbol::SYMBOL_RIGHT_PAREN))
        {
            return nullptr;
        }

        return inner;
    }

    if (is(token, symbol::SYMBOL_LEFT_BRACKET))
    {
        return parse_array_expression();
    }

    if (is(token, symbol::SYMBOL_LEFT_BRACE))
    {
        return parse_object_expression();
    }

    if (is(token, keyword::KEYWORD_NULL))
    {
        read();
        return make_shared<null_expression_parse_node>(
            token->token(),
            token->preceding_comments());
    }

    if (is(token, keyword::KEYWORD_TRUE) || is(token, keyword::KEYWORD_FALSE))
    {
        bool value = is(token, keyword::KEYWORD_TRUE);
        read();
        return make_shared<boolean_literal_expression_parse_node>(
            value,
            token->token(),
            token->preceding_comments());
    }

    if (token->token()->type() == token::token_type::NUMERIC_LITERAL)
    {
        auto numeric_token = static_pointer_cast<numeric_literal_token>(token->token());
        read();
        return make_shared<numeric_literal_expression_parse_node>(
            numeric_token->integer_value(),
            numeric_token->double_value(),
            numeric_token->is_integer(),
            numeric_token,
            token->preceding_comments());
    }

    if (token->token()->type() == token::token_type::STRING_LITERAL)
    {
        auto string_token = static_pointer_cast<string_literal_token>(token->token());
        read();
        return make_shared<string_literal_expression_parse_node>(
            string_token->value(),
            string_token,
            token->preceding_comments());
    }

    return parse_reference_expression();
}

shared_ptr<expression_parse_node> parser::parse_array_expression()
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_LEFT_BRACKET))
    {
        return nullptr;
    }

    list<list<shared_ptr<expression_parse_node>>> elements;
    auto token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_BRACKET))
    {
        elements.push_back(list<shared_ptr<expression_parse_node>>());
        if (!parse_array_row(elements.back()))
        {
            return nullptr;
        }

        token = peek();
        if (token && is(token, symbol::SYMBOL_SEMICOLON))
        {
            read();
            token = peek();
        }
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACKET))
    {
        return nullptr;
    }
    
    return make_shared<array_expression_parse_node>(
        elements,
        start->token(),
        start->preceding_comments());
}

bool parser::parse_array_row(/*out*/ list<shared_ptr<expression_parse_node>>& row)
{
    auto token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_BRACKET) && !is(token, symbol::SYMBOL_SEMICOLON))
    {
        auto expr = parse_expression();
        if (!expr)
        {
            return false;
        }

        row.push_back(expr);
        token = peek();
        if (token && is(token, symbol::SYMBOL_COMMA))
        {
            read();
            token = peek();
        }
        else
        {
            break;
        }
    }

    return true;
}

shared_ptr<expression_parse_node> parser::parse_object_expression()
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_LEFT_BRACE))
    {
        return nullptr;
    }

    list<shared_ptr<object_member_parse_node>> members;

    auto token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_BRACE))
    {
        auto member = parse_object_member();
        if (!member)
        {
            return nullptr;
        }

        members.push_back(member);

        token = peek();
        if (token && is(token, symbol::SYMBOL_COMMA))
        {
            read();
            token = peek();
        }
        else
        {
            break;
        }
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACE))
    {
        return nullptr;
    }

    return make_shared<object_expression_parse_node>(
        members,
        start->token(),
        start->preceding_comments());
}

shared_ptr<object_member_parse_node> parser::parse_object_member()
{
    auto start = peek();
    auto identifier = expect_identifier();
    if (!identifier)
    {
        return nullptr;
    }

    if (!expect(symbol::SYMBOL_ASSIGN))
    {
        return nullptr;
    }

    auto value = parse_expression();
    if (!value)
    {
        return nullptr;
    }

    return make_shared<object_member_parse_node>(
        identifier->name(),
        value,
        start->token(),
        start->preceding_comments());
}

shared_ptr<expression_parse_node> parser::parse_reference_expression()
{
    auto start = peek();
    auto identifier = expect_identifier();
    if (!identifier)
    {   
        return nullptr;
    }

    shared_ptr<reference_expression_parse_node> result = make_shared<variable_reference_expression_parse_node>(
        identifier->name(),
        start->token(),
        start->preceding_comments());

    auto token = peek();
    while (token && 
        (is(token, symbol::SYMBOL_DOT) || 
         is(token, symbol::SYMBOL_LEFT_BRACKET) ||
         is(token, symbol::SYMBOL_LEFT_PAREN)))
    {
        symbol symbol_value = static_pointer_cast<symbol_token>(token->token())->value();
        switch (symbol_value)
        {
            case symbol::SYMBOL_DOT:
                result = parse_member_reference(result);
                break;
            case symbol::SYMBOL_LEFT_BRACKET:
                result = parse_index_expression(result);
                break;
            case symbol::SYMBOL_LEFT_PAREN:
                result = parse_call_expression(result);
                break;
            default:
                throw logic_error("Internal Error: Invalid reference expression operator.");
        }

        if (!result)
        {
            return nullptr;
        }

        token = peek();
    }

    return result;
}

shared_ptr<reference_expression_parse_node> parser::parse_member_reference(
    const shared_ptr<reference_expression_parse_node>& target)
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_DOT))
    {
        return nullptr;
    }

    auto identifier = expect_identifier();
    if (!identifier)
    {
        return nullptr;
    }

    return make_shared<member_reference_expression_parse_node>(
        target,
        identifier->name(),
        start->token(),
        start->preceding_comments());
}

shared_ptr<reference_expression_parse_node> parser::parse_index_expression(
    const shared_ptr<reference_expression_parse_node>& target)
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_LEFT_BRACKET))
    {
        return nullptr;
    }

    list<shared_ptr<expression_parse_node>> indexes;
    auto index = parse_expression();
    if (!index)
    {
        return nullptr;
    }

    indexes.push_back(index);
    auto token = peek();
    while (token && is(token, symbol::SYMBOL_COMMA))
    {
        read();
        index = parse_expression();
        if (!index)
        {
            return nullptr;
        }

        indexes.push_back(index);
        token = peek();
    }

    if (!expect(symbol::SYMBOL_RIGHT_BRACKET))
    {
        return nullptr;
    }

    return make_shared<index_expression_parse_node>(
        target,
        indexes,
        start->token(),
        start->preceding_comments());
}

shared_ptr<reference_expression_parse_node> parser::parse_call_expression(
    const shared_ptr<reference_expression_parse_node>& target)
{
    auto start = peek();
    if (!expect(symbol::SYMBOL_LEFT_PAREN))
    {
        return nullptr;
    }

    auto arguments = list<shared_ptr<argument_parse_node>>();
    auto token = peek();
    while (token && !is(token, symbol::SYMBOL_RIGHT_PAREN))
    {
        auto argument = parse_argument();
        if (!argument)
        {
            return nullptr;
        }

        arguments.push_back(argument);
        token = peek();
        if (token && is(token, symbol::SYMBOL_COMMA))
        {
            read();
            token = peek();
        }
        else
        {
            break;
        }
    }

    if (!expect(symbol::SYMBOL_RIGHT_PAREN))
    {
        return nullptr;
    }

    return make_shared<call_expression_parse_node>(
        target,
        arguments,
        start->token(),
        start->preceding_comments());
}

shared_ptr<argument_parse_node> parser::parse_argument()
{
    auto start = peek();
    auto expr = parse_expression();
    if (!expr)
    {
        return nullptr;
    }

    string name;
    if (expr->type() == parse_node_type::PARSE_NODE_VARIABLE_REFERENCE)
    {
        auto token = peek();
        if (token && is(token, symbol::SYMBOL_ASSIGN))
        {
            read();
            name = static_pointer_cast<variable_reference_expression_parse_node>(expr)->name();
            expr = parse_expression();
            if (!expr)
            {
                return nullptr;
            }
        }
    }

    return make_shared<argument_parse_node>(
        name,
        expr,
        start->token(),
        start->preceding_comments());
}

bool parser::expect(symbol symbol)
{
    auto token = read();
    if (!token || token->token()->type() != token::SYMBOL)
    {
        _log(message_utility::symbol_expected(
            token ? token->token() : nullptr,
            _reader.current_source(),
            symbol));
        return false;
    }

    return true;
}

bool parser::expect(keyword keyword)
{
    auto token = read();
    if (!token || token->token()->type() != token::KEYWORD)
    {
        _log(message_utility::keyword_expected(
            token ? token->token() : nullptr,
            _reader.current_source(),
            keyword));
        return false;
    }

    return true;
}

shared_ptr<string_literal_token> parser::expect_string_literal()
{
    auto token = read();
    if (!token || token->token()->type() != token::STRING_LITERAL)
    {
        _log(message_utility::string_literal_expected(
            token ? token->token() : nullptr,
            _reader.current_source()));
        return nullptr;
    }

    return static_pointer_cast<string_literal_token>(token->token());
}

shared_ptr<identifier_token> parser::expect_identifier()
{
    auto token = read();
    if (!token || token->token()->type() != token::IDENTIFIER)
    {
        _log(message_utility::identifier_expected(
            token ? token->token() : nullptr,
            _reader.current_source()));
        return nullptr;
    }

    return static_pointer_cast<identifier_token>(token->token());
}

shared_ptr<numeric_literal_token> parser::expect_integer()
{
    auto token = read();
    if (!token || token->token()->type() != token::NUMERIC_LITERAL)
    {
        _log(message_utility::integer_literal_expected(
            token ? token->token() : nullptr,
            _reader.current_source()));
        return nullptr;
    }

    return static_pointer_cast<numeric_literal_token>(token->token());
}

shared_ptr<parser::token_with_comments> parser::peek()
{
    if (!_peeked_token)
    {
        _peeked_token = inner_read();
    }

    return _peeked_token;
}

shared_ptr<parser::token_with_comments> parser::read()
{
    auto token = peek();
    _peeked_token.reset();
    return token;
}

shared_ptr<parser::token_with_comments> parser::inner_read()
{
    list<shared_ptr<comment_token>> preceding_comments;
    auto token = _reader.read();
    while (token && token->type() == token::COMMENT)
    {
        auto comment_token_ptr = static_pointer_cast<comment_token>(token);
        preceding_comments.push_back(comment_token_ptr);
        token = _reader.read(); 
    }

    if (!token)
    {
        return nullptr;
    }

    return make_shared<token_with_comments>(token, preceding_comments);
}