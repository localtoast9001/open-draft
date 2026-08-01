/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file parse_node.hpp
 * @brief Header file for the parse_node and derived classes.
 */
#pragma once
#ifndef __OPENDRAFT_LANG_PARSE_NODE_HPP__
#define __OPENDRAFT_LANG_PARSE_NODE_HPP__

#include "token.hpp"
#include <memory>
#include <list>

namespace opendraft::lang
{
    // Forward declarations of classes in this file (since there are a large number of them).
    class add_expression_parse_node;
    class argument_parse_node;
    class array_expression_parse_node;
    class bitwise_and_expression_parse_node;
    class bitwise_or_expression_parse_node;
    class bitwise_xor_expression_parse_node;
    class block_statement_parse_node;
    class boolean_literal_expression_parse_node;
    class break_statement_parse_node;
    class call_expression_parse_node;
    class call_statement_parse_node;
    class class_parse_node;
    class conditional_expression_parse_node;
    class continue_statement_parse_node;
    class enum_member_parse_node;
    class enum_parse_node;
    class equality_expression_parse_node;
    class expression_parse_node;
    class for_condition_parse_node;
    class for_statement_parse_node;
    class function_declaration_parse_node;
    class function_parse_node;
    class if_statement_parse_node;
    class import_parse_node;
    class index_expression_parse_node;
    class interface_member_parse_node;
    class interface_parse_node;
    class literal_expression_parse_node;
    class logical_and_expression_parse_node;
    class logical_or_expression_parse_node;
    class member_reference_expression_parse_node;
    class mul_expression_parse_node;
    class namespace_parse_node;
    class null_expression_parse_node;
    class numeric_literal_expression_parse_node;
    class object_expression_parse_node;
    class object_member_parse_node;
    class parameter_declaration_parse_node;
    class parse_node;
    class program_element_parse_node;
    class program_parse_node;
    class range_expression_parse_node;
    class reference_expression_parse_node;
    class relational_expression_parse_node;
    class return_statement_parse_node;
    class shift_expression_parse_node;
    class statement_parse_node;
    class string_literal_expression_parse_node;
    class template_declaration_parse_node;
    class template_parse_node;
    class throw_statement_parse_node;
    class type_reference_parse_node;
    class unary_expression_parse_node;
    class variable_definition_parse_node;
    class variable_reference_expression_parse_node;

    /**
     * @brief The parse_node_type enum defines the types of parse nodes in the abstract syntax tree (AST).
     */
    enum parse_node_type
    {
        PARSE_NODE_UNDEFINED = 0,
        PARSE_NODE_ADD_EXPRESSION,
        PARSE_NODE_ARGUMENT,
        PARSE_NODE_ARRAY_EXPRESSION,
        PARSE_NODE_BITWISE_AND_EXPRESSION,
        PARSE_NODE_BITWISE_OR_EXPRESSION,
        PARSE_NODE_BITWISE_XOR_EXPRESSION,
        PARSE_NODE_BLOCK_STATEMENT,
        PARSE_NODE_BOOLEAN_LITERAL_EXPRESSION,
        PARSE_NODE_BREAK_STATEMENT,
        PARSE_NODE_CALL_EXPRESSION,
        PARSE_NODE_CALL_STATEMENT,
        PARSE_NODE_CLASS,
        PARSE_NODE_CONDITIONAL_EXPRESSION,
        PARSE_NODE_CONTINUE_STATEMENT,
        PARSE_NODE_ENUM_MEMBER,
        PARSE_NODE_ENUM,
        PARSE_NODE_EQUALITY_EXPRESSION,
        PARSE_NODE_FOR_CONDITION,
        PARSE_NODE_FOR_STATEMENT,
        PARSE_NODE_FUNCTION_DECLARATION,
        PARSE_NODE_FUNCTION,
        PARSE_NODE_IF_STATEMENT,
        PARSE_NODE_IMPORT,
        PARSE_NODE_INDEX_EXPRESSION,
        PARSE_NODE_INTERFACE_MEMBER,
        PARSE_NODE_INTERFACE,
        PARSE_NODE_LITERAL_EXPRESSION,
        PARSE_NODE_LOGICAL_AND_EXPRESSION,
        PARSE_NODE_LOGICAL_OR_EXPRESSION,
        PARSE_NODE_MEMBER_REFERENCE_EXPRESSION,
        PARSE_NODE_MUL_EXPRESSION,
        PARSE_NODE_NAMESPACE,
        PARSE_NODE_NULL_EXPRESSION,
        PARSE_NODE_NUMERIC_LITERAL_EXPRESSION,
        PARSE_NODE_OBJECT_EXPRESSION,
        PARSE_NODE_OBJECT_MEMBER,
        PARSE_NODE_PARAMETER_DECLARATION,
        PARSE_NODE_PROGRAM, // This is the root node of the AST.
        PARSE_NODE_RANGE_EXPRESSION,
        PARSE_NODE_RELATIONAL_EXPRESSION,
        PARSE_NODE_RETURN_STATEMENT,
        PARSE_NODE_SHIFT_EXPRESSION,
        PARSE_NODE_STRING_LITERAL_EXPRESSION,
        PARSE_NODE_TEMPLATE_DECLARATION,
        PARSE_NODE_TEMPLATE,
        PARSE_NODE_THROW_STATEMENT,
        PARSE_NODE_TRACE_STATEMENT,
        PARSE_NODE_TYPE_REFERENCE,
        PARSE_NODE_UNARY_EXPRESSION,
        PARSE_NODE_VARIABLE_DEFINITION,
        PARSE_NODE_VARIABLE_REFERENCE,
    };

    /**
     * @brief The parse_node class is the base class for all nodes in the abstract syntax tree (AST).
     */
    class parse_node
    {
    public:
        virtual ~parse_node() = default;

        /**
         * @brief Gets the starting token of the parse node.
         * @return A shared pointer to the starting token of the parse node.
         */
        std::shared_ptr<token> start() const { return _start; }

        /**
         * @brief Gets the preceding comments associated with the parse node.
         * @return A list of shared pointers to the preceding comments associated with the parse node.
         * @remarks This is used to preserve comments in the source code for documentation or use in code generation.
         */
        const std::list<std::shared_ptr<comment_token>>& preceding_comments() const { return _preceding_comments; }

        /**
         * @brief Gets the type of the parse node.
         * @return The type of the parse node.
         */
        virtual parse_node_type type() const = 0;
    
    protected:
        parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    
    private:
        std::shared_ptr<token> _start;
        std::list<std::shared_ptr<comment_token>> _preceding_comments;

        parse_node(const parse_node&) = delete;
        parse_node& operator=(const parse_node&) = delete;
    };

    /**
     * @brief Represents an import statement in the abstract syntax tree (AST).
     */
    class import_parse_node : public parse_node
    {
    public:
        import_parse_node(
            const std::string& module_name,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        /**
         * @brief Gets the name of the module being imported.
         * @return The name of the module being imported.
         */
        const std::string& module_name() const { return _module_name; }

        virtual parse_node_type type() const override;

    private:
        std::string _module_name;
    };

    /**
     * @brief The base class for all program elements.
     */
    class program_element_parse_node : public parse_node
    {
    protected:
        program_element_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    };

    /**
     * @brief Base class for interface members in the abstract syntax tree (AST).
     */
    class interface_member_parse_node : public parse_node
    {
    protected:
        interface_member_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    };

    /**
     * @brief The base class for all statements in the abstract syntax tree (AST).
     */
    class statement_parse_node : public program_element_parse_node
    {
    protected:
        statement_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    };

    /**
     * @brief The base class for all expressions in the abstract syntax tree (AST).
     */
    class expression_parse_node : public parse_node
    {
    protected:
        expression_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    };

    /**
     * @brief The base class for all reference expressions in the abstract syntax tree (AST).
     */
    class reference_expression_parse_node : public expression_parse_node
    {
    public:
        /**
         * @brief Converts the reference expression to a type reference parse node (if supported).
         * @return A shared pointer to the type reference parse node, or nullptr if the conversion is not supported.
         */
        virtual std::shared_ptr<type_reference_parse_node> to_type_reference() const;

    protected:
        reference_expression_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    };

    /**
     * @brief The program_parse_node class represents the root node of the abstract syntax tree (AST) for an OpenDraft program.
     */
    class program_parse_node : public parse_node
    {
    public:
        program_parse_node(
            const std::list<std::shared_ptr<import_parse_node>>& imports,
            const std::list<std::shared_ptr<program_element_parse_node>>& program_elements,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::list<std::shared_ptr<import_parse_node>>& imports() const { return _imports; }

        const std::list<std::shared_ptr<program_element_parse_node>>& program_elements() const { return _program_elements; }

        virtual parse_node_type type() const override;
    private:
        std::list<std::shared_ptr<import_parse_node>> _imports;
        std::list<std::shared_ptr<program_element_parse_node>> _program_elements;
    };

    /**
     * @brief Represents an addition or subtraction expression in the abstract syntax tree (AST).
     */
    class add_expression_parse_node : public expression_parse_node
    {
    public:
        add_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            bool is_subtraction,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }
        constexpr bool is_subtraction() const { return _is_subtraction; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
        bool _is_subtraction;
    };

    /**
     * @brief Represents an argument in a function or template call in the abstract syntax tree (AST).
     */
    class argument_parse_node : public parse_node
    {
    public:
        argument_parse_node(
            const std::string& name,
            const std::shared_ptr<expression_parse_node>& expression,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::shared_ptr<expression_parse_node>& expression() const { return _expression; }
        virtual parse_node_type type() const override;
    private:
        std::string _name;
        std::shared_ptr<expression_parse_node> _expression;
    };

    /**
     * @brief Represents an array expression in the abstract syntax tree (AST).
     */
    class array_expression_parse_node : public expression_parse_node
    {
    public:
        array_expression_parse_node(
            const std::list<std::list<std::shared_ptr<expression_parse_node>>>& elements,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::list<std::list<std::shared_ptr<expression_parse_node>>>& elements() const { return _elements; }

        virtual parse_node_type type() const override;
    private:
        std::list<std::list<std::shared_ptr<expression_parse_node>>> _elements;
    };

    /**
     * @brief Represents a bitwise AND expression in the abstract syntax tree (AST).
     */
    class bitwise_and_expression_parse_node : public expression_parse_node
    {
    public:
        bitwise_and_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
    };

    /**
     * @brief Represents a bitwise OR expression in the abstract syntax tree (AST).
     */
    class bitwise_or_expression_parse_node : public expression_parse_node
    {
    public:
        bitwise_or_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
    };

    /**
     * @brief Represents a bitwise XOR expression in the abstract syntax tree (AST).
     */
    class bitwise_xor_expression_parse_node : public expression_parse_node
    {
    public:
        bitwise_xor_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
    };

    /**
     * @brief Represents a block statement in the abstract syntax tree (AST).
     */
    class block_statement_parse_node : public statement_parse_node
    {
    public:
        block_statement_parse_node(
            const std::list<std::shared_ptr<statement_parse_node>>& statements,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::list<std::shared_ptr<statement_parse_node>>& statements() const { return _statements; }

        virtual parse_node_type type() const override;

    private:
        std::list<std::shared_ptr<statement_parse_node>> _statements;
    };

    /**
     * @brief Represents a boolean literal expression in the abstract syntax tree (AST).
     */
    class boolean_literal_expression_parse_node : public expression_parse_node
    {
    public:
        boolean_literal_expression_parse_node(
            bool value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        constexpr bool value() const { return _value; }

        virtual parse_node_type type() const override;

    private:
        bool _value;
    };

    /**
     * @brief Represents a break statement in the abstract syntax tree (AST).
     */
    class break_statement_parse_node : public statement_parse_node
    {
    public:
        break_statement_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        
        virtual parse_node_type type() const override;
    };

    /**
     * @brief Represents a call expression in the abstract syntax tree (AST).
     */
    class call_expression_parse_node : public reference_expression_parse_node
    {
    public:
        call_expression_parse_node(
            const std::shared_ptr<reference_expression_parse_node>& target,
            const std::list<std::shared_ptr<argument_parse_node>>& arguments,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<reference_expression_parse_node>& target() const { return _target; }
        const std::list<std::shared_ptr<argument_parse_node>>& arguments() const { return _arguments; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<reference_expression_parse_node> _target;
        std::list<std::shared_ptr<argument_parse_node>> _arguments;
    };

    /**
     * @brief Represents a call statement in the abstract syntax tree (AST).
     */
    class call_statement_parse_node : public statement_parse_node
    {
    public:
        call_statement_parse_node(
            const std::shared_ptr<reference_expression_parse_node>& target,
            const std::list<std::shared_ptr<argument_parse_node>>& arguments,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        static std::shared_ptr<call_statement_parse_node> from_call_expression(
            const std::shared_ptr<call_expression_parse_node>& call_expression);

        const std::shared_ptr<reference_expression_parse_node>& target() const { return _target; }
        const std::list<std::shared_ptr<argument_parse_node>>& arguments() const { return _arguments; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<reference_expression_parse_node> _target;
        std::list<std::shared_ptr<argument_parse_node>> _arguments;
    };

    /**
     * @brief Represents a class declaration in the abstract syntax tree (AST).
     */
    class class_parse_node : public program_element_parse_node
    {
    public:
        class_parse_node(
            const std::string& name,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
    };

    /**
     * @brief Represents a conditional expression in the abstract syntax tree (AST).
     */
    class conditional_expression_parse_node : public expression_parse_node
    {
    public:
        conditional_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& condition,
            const std::shared_ptr<expression_parse_node>& true_expression,
            const std::shared_ptr<expression_parse_node>& false_expression,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& condition() const { return _condition; }
        const std::shared_ptr<expression_parse_node>& true_expression() const { return _true_expression; }
        const std::shared_ptr<expression_parse_node>& false_expression() const { return _false_expression; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _condition;
        std::shared_ptr<expression_parse_node> _true_expression;
        std::shared_ptr<expression_parse_node> _false_expression;
    };

    /**
     * @brief Represents a continue statement in the abstract syntax tree (AST).
     */
    class continue_statement_parse_node : public statement_parse_node
    {
    public:
        continue_statement_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        virtual parse_node_type type() const override;
    };

    /**
     * @brief Represents an enum member in the abstract syntax tree (AST).
     */
    class enum_member_parse_node : public program_element_parse_node
    {
    public:
        enum_member_parse_node(
            const std::string& name,
            long value,
            bool has_value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        long value() const { return _value; }
        bool has_value() const { return _has_value; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
        long _value;
        bool _has_value;
    };

    /**
     * @brief Represents an enum declaration in the abstract syntax tree (AST).
     */
    class enum_parse_node : public program_element_parse_node
    {
    public:
        enum_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<enum_member_parse_node>>& members,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
    
        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<enum_member_parse_node>>& members() const { return _members; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::list<std::shared_ptr<enum_member_parse_node>> _members;
    };

    /**
     * @brief Represents an equality or inequality expression in the abstract syntax tree (AST).
     */
    class equality_expression_parse_node : public expression_parse_node
    {
    public:
        equality_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            bool is_inequality,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }
        constexpr bool is_inequality() const { return _is_inequality; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
        bool _is_inequality;
    };

    /**
     * @brief Represents a for loop condition in the abstract syntax tree (AST).
     */
    class for_condition_parse_node : public parse_node
    {
    public:
        for_condition_parse_node(
            const std::list<std::string>& variable_names,
            const std::shared_ptr<expression_parse_node>& expression,
            const std::shared_ptr<type_reference_parse_node>& type_reference,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::list<std::string>& variable_names() const { return _variable_names; }
        const std::shared_ptr<expression_parse_node>& expression() const { return _expression; }
        const std::shared_ptr<type_reference_parse_node>& type_reference() const { return _type_reference; }

        virtual parse_node_type type() const override;

    private:
        std::list<std::string> _variable_names;
        std::shared_ptr<expression_parse_node> _expression;
        std::shared_ptr<type_reference_parse_node> _type_reference;
    };

    /**
     * @brief Represents a for loop statement in the abstract syntax tree (AST).
     */
    class for_statement_parse_node : public statement_parse_node
    {
    public:
        for_statement_parse_node(
            const std::list<std::shared_ptr<for_condition_parse_node>>& condition,
            const std::shared_ptr<statement_parse_node>& body,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::list<std::shared_ptr<for_condition_parse_node>>& condition() const { return _condition; }
        const std::shared_ptr<statement_parse_node>& body() const { return _body; }

        virtual parse_node_type type() const override;

    private:
        std::list<std::shared_ptr<for_condition_parse_node>> _condition;
        std::shared_ptr<statement_parse_node> _body;
    };

    /**
     * @brief Represents a function declaration in the abstract syntax tree (AST).
     */
    class function_declaration_parse_node : public interface_member_parse_node
    {
    public:
        function_declaration_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters() const { return _parameters; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::list<std::shared_ptr<parameter_declaration_parse_node>> _parameters;
    };

    /**
     * @brief Represents a function definition in the abstract syntax tree (AST).
     */
    class function_parse_node : public program_element_parse_node
    {
    public:
        function_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
            const std::shared_ptr<statement_parse_node>& body,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters() const { return _parameters; }
        const std::shared_ptr<statement_parse_node>& body() const { return _body; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::list<std::shared_ptr<parameter_declaration_parse_node>> _parameters;
        std::shared_ptr<statement_parse_node> _body;
    };

    /**
     * @brief Represents an if statement in the abstract syntax tree (AST).
     */
    class if_statement_parse_node : public statement_parse_node
    {
    public:
        if_statement_parse_node(
            const std::shared_ptr<expression_parse_node>& condition,
            const std::shared_ptr<statement_parse_node>& then_statement,
            const std::shared_ptr<statement_parse_node>& else_statement,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& condition() const { return _condition; }
        const std::shared_ptr<statement_parse_node>& then_statement() const { return _then_statement; }
        const std::shared_ptr<statement_parse_node>& else_statement() const { return _else_statement; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _condition;
        std::shared_ptr<statement_parse_node> _then_statement;
        std::shared_ptr<statement_parse_node> _else_statement;
    };

    /**
     * @brief Represents an array index expression in the abstract syntax tree (AST).
     */
    class index_expression_parse_node : public reference_expression_parse_node
    {
    public:
        index_expression_parse_node(
            const std::shared_ptr<reference_expression_parse_node>& target,
            const std::list<std::shared_ptr<expression_parse_node>>& indexes,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<reference_expression_parse_node>& target() const { return _target; }
        const std::list<std::shared_ptr<expression_parse_node>>& indexes() const { return _indexes; }

        virtual parse_node_type type() const override;
    
    private:
        std::shared_ptr<reference_expression_parse_node> _target;
        std::list<std::shared_ptr<expression_parse_node>> _indexes;
    };

    /**
     * @brief Represents an interface declaration in the abstract syntax tree (AST).
     */
    class interface_parse_node : public program_element_parse_node
    {
    public:
        interface_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<interface_member_parse_node>>& members,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<interface_member_parse_node>>& members() const { return _members; }
        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::list<std::shared_ptr<interface_member_parse_node>> _members;
    };

    /**
     * @brief Represents a logical AND expression in the abstract syntax tree (AST).
     */
    class logical_and_expression_parse_node : public expression_parse_node
    {
    public:
        logical_and_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
    };

    /**
     * @brief Represents a logical OR expression in the abstract syntax tree (AST).
     */
    class logical_or_expression_parse_node : public expression_parse_node
    {
    public:
        logical_or_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
    };

    /**
     * @brief Represents a member reference expression in the abstract syntax tree (AST).
     */
    class member_reference_expression_parse_node : public reference_expression_parse_node
    {
    public:
        member_reference_expression_parse_node(
            const std::shared_ptr<reference_expression_parse_node>& target,
            const std::string& member_name,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<reference_expression_parse_node>& target() const { return _target; }
        const std::string& member_name() const { return _member_name; }

        virtual parse_node_type type() const override;

        virtual std::shared_ptr<type_reference_parse_node> to_type_reference() const override;

    private:
        std::shared_ptr<reference_expression_parse_node> _target;
        std::string _member_name;
    };

    /**
     * @brief Represents a multiplication, division, or modulo expression in the abstract syntax tree (AST).
     */
    enum mul_operator
    {
        // Represents the multiplication operator (*).
        MUL_OPERATOR_MULTIPLY,
        
        // Represents the division operator (/).
        MUL_OPERATOR_DIVIDE,
        
        // Represents the modulo operator (%).
        MUL_OPERATOR_MODULO
    };

    /**
     * @brief Represents a multiplication, division, or modulo expression in the abstract syntax tree (AST).
     */
    class mul_expression_parse_node : public expression_parse_node
    {
    public:
        mul_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            mul_operator op,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }
        constexpr mul_operator op() const { return _op; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
        mul_operator _op;
    };

    /**
     * @brief Represents a namespace declaration in the abstract syntax tree (AST).
     */
    class namespace_parse_node : public program_element_parse_node
    {
    public:
        namespace_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<program_element_parse_node>>& program_elements,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        virtual parse_node_type type() const override;
    private:
        std::string _name;
        std::list<std::shared_ptr<program_element_parse_node>> _program_elements;
    };

    /**
     * @brief Represents a null expression in the abstract syntax tree (AST).
     */
    class null_expression_parse_node : public expression_parse_node
    {
    public:
        null_expression_parse_node(
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        virtual parse_node_type type() const override;
    };

    /**
     * @brief Represents a numeric literal expression in the abstract syntax tree (AST).
     */
    class numeric_literal_expression_parse_node : public expression_parse_node
    {
    public:
        numeric_literal_expression_parse_node(
            double float_value,
            long integer_value,
            bool is_integer,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        constexpr double float_value() const { return _float_value; }
        constexpr long integer_value() const { return _integer_value; }
        constexpr bool is_integer() const { return _is_integer; }

        virtual parse_node_type type() const override;

    private:
        double _float_value;
        long _integer_value;
        bool _is_integer;
    };

    /**
     * @brief Represents an object expression in the abstract syntax tree (AST).
     */
    class object_expression_parse_node : public expression_parse_node
    {
    public:
        object_expression_parse_node(
            const std::list<std::shared_ptr<object_member_parse_node>>& members,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::list<std::shared_ptr<object_member_parse_node>>& members() const { return _members; }
        
        virtual parse_node_type type() const override;

    private:
        std::list<std::shared_ptr<object_member_parse_node>> _members;
    };

    /**
     * @brief Represents a member of an object expression in the abstract syntax tree (AST).
     */
    class object_member_parse_node : public parse_node
    {
    public:
        object_member_parse_node(
            const std::string& name,
            const std::shared_ptr<expression_parse_node>& value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::shared_ptr<expression_parse_node>& value() const { return _value; }
        
        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::shared_ptr<expression_parse_node> _value;
    };

    /**
     * @brief Represents a parameter declaration in the abstract syntax tree (AST).
     */
    class parameter_declaration_parse_node : public parse_node
    {
    public:
        parameter_declaration_parse_node(
            const std::string& name,
            const std::shared_ptr<type_reference_parse_node>& type_reference,
            const std::shared_ptr<expression_parse_node>& default_value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::shared_ptr<type_reference_parse_node>& type_reference() const { return _type_reference; }
        const std::shared_ptr<expression_parse_node>& default_value() const { return _default_value; }

        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::shared_ptr<type_reference_parse_node> _type_reference;
        std::shared_ptr<expression_parse_node> _default_value;
    };

    /**
     * @brief Represents a range expression in the abstract syntax tree (AST).
     */
    class range_expression_parse_node : public expression_parse_node
    {
    public:
        range_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& from,
            const std::shared_ptr<expression_parse_node>& to,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& from() const { return _from; }
        const std::shared_ptr<expression_parse_node>& to() const { return _to; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _from;
        std::shared_ptr<expression_parse_node> _to;
    };

    /**
     * @brief Represents a relational operator in the abstract syntax tree (AST).
     */
    enum relational_operator
    {
        // Represents the less than operator (<).
        RELATIONAL_OPERATOR_LESS_THAN,
        
        // Represents the less than or equal to operator (<=).
        RELATIONAL_OPERATOR_LESS_THAN_OR_EQUAL,
        
        // Represents the greater than operator (>).
        RELATIONAL_OPERATOR_GREATER_THAN,
        
        // Represents the greater than or equal to operator (>=).
        RELATIONAL_OPERATOR_GREATER_THAN_OR_EQUAL,

        // Represents the "in" operator (in).
        RELATIONAL_OPERATOR_IN_SET,
    };

    /**
     * @brief Represents a relational expression in the abstract syntax tree (AST).
     */
    class relational_expression_parse_node : public expression_parse_node
    {
    public:
        relational_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            relational_operator op,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }
        constexpr relational_operator op() const { return _op; }

        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
        relational_operator _op;
    };

    /**
     * @brief Represents a return statement in the abstract syntax tree (AST).
     */
    class return_statement_parse_node : public statement_parse_node
    {
    public:
        return_statement_parse_node(
            const std::shared_ptr<expression_parse_node>& expression,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& expression() const { return _expression; }
        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _expression;
    };

    /**
     * @brief Represents a shift operator in the abstract syntax tree (AST).
     */
    enum shift_operator
    {
        // Represents the left shift operator (<<).
        SHIFT_OPERATOR_LEFT_SHIFT,
        
        // Represents the right shift operator (>>).
        SHIFT_OPERATOR_RIGHT_SHIFT
    };

    /**
     * @brief Represents a shift expression in the abstract syntax tree (AST).
     */
    class shift_expression_parse_node : public expression_parse_node
    {
    public:
        shift_expression_parse_node(
            const std::shared_ptr<expression_parse_node>& left,
            const std::shared_ptr<expression_parse_node>& right,
            shift_operator op,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::shared_ptr<expression_parse_node>& left() const { return _left; }
        const std::shared_ptr<expression_parse_node>& right() const { return _right; }
        constexpr shift_operator op() const { return _op; }
        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _left;
        std::shared_ptr<expression_parse_node> _right;
        shift_operator _op;
    };

    /**
     * @brief Represents a string literal expression in the abstract syntax tree (AST).
     */
    class string_literal_expression_parse_node : public expression_parse_node
    {
    public:
        string_literal_expression_parse_node(
            const std::string& value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& value() const { return _value; }
        virtual parse_node_type type() const override;

    private:
        std::string _value;
    };

    /**
     * @brief Represents a template declaration in the abstract syntax tree (AST).
     */
    class template_declaration_parse_node : public interface_member_parse_node
    {
    public:
        template_declaration_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters() const { return _parameters; }
        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::list<std::shared_ptr<parameter_declaration_parse_node>> _parameters;
    };

    /**
     * @brief Represents a template definition in the abstract syntax tree (AST).
     */
    class template_parse_node : public program_element_parse_node
    {
    public:
        template_parse_node(
            const std::string& name,
            const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
            const std::shared_ptr<statement_parse_node>& body,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        const std::string& name() const { return _name; }
        const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters() const { return _parameters; }
        const std::shared_ptr<statement_parse_node>& body() const { return _body; }
        virtual parse_node_type type() const override;
    private:
        std::string _name;
        std::list<std::shared_ptr<parameter_declaration_parse_node>> _parameters;
        std::shared_ptr<statement_parse_node> _body;
    };

    /**
     * @brief Represents a throw statement in the abstract syntax tree (AST).
     */
    class throw_statement_parse_node : public statement_parse_node
    {
    public:
        throw_statement_parse_node(
            const std::shared_ptr<expression_parse_node>& expression,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::shared_ptr<expression_parse_node>& expression() const { return _expression; }
        virtual parse_node_type type() const override;

    private:
        std::shared_ptr<expression_parse_node> _expression;
    };

    /**
     * @brief Represents the severity of a trace statement in the abstract syntax tree (AST).
     */
    enum trace_statement_severity
    {
        TRACE_SEVERITY_ERROR,
        TRACE_SEVERITY_WARNING,
        TRACE_SEVERITY_INFO,
        TRACE_SEVERITY_VERBOSE,
        TRACE_SEVERITY_DEBUG,
    };

    /**
     * @brief Represents a trace statement in the abstract syntax tree (AST).
     */
    class trace_statement_parse_node : public statement_parse_node
    {
    public:
        trace_statement_parse_node(
            trace_statement_severity severity,
            const std::shared_ptr<expression_parse_node>& expression,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        trace_statement_severity severity() const { return _severity; }
        const std::shared_ptr<expression_parse_node>& expression() const { return _expression; }
        virtual parse_node_type type() const override;

    private:
        trace_statement_severity _severity;
        std::shared_ptr<expression_parse_node> _expression;
    };

    /**
     * @brief Represents a type reference in the abstract syntax tree (AST).
     */
    class type_reference_parse_node : public parse_node
    {
    public:
        type_reference_parse_node(
            const std::list<std::string>& names,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::list<std::string>& names() const { return _names; }
        virtual parse_node_type type() const override;

    private:
        std::list<std::string> _names;
    };

    /**
     * @brief Represents the operator in a unary expression in the abstract syntax tree (AST).
     */
    enum unary_operator
    {
        // Represents the negation operator (-).
        UNARY_OPERATOR_NEGATION,

        // Represents the logical NOT operator (!).
        UNARY_OPERATOR_LOGICAL_NOT,

        // Represents the bitwise NOT operator (~).
        UNARY_OPERATOR_BITWISE_NOT,
    };

    /**
     * @brief Represents a unary expression in the abstract syntax tree (AST).
     */
    class unary_expression_parse_node : public expression_parse_node
    {
    public:
        unary_expression_parse_node(
            unary_operator op,
            const std::shared_ptr<expression_parse_node>& operand,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);

        unary_operator op() const { return _op; }
        const std::shared_ptr<expression_parse_node>& operand() const { return _operand; }
        virtual parse_node_type type() const override;

    private:
        unary_operator _op;
        std::shared_ptr<expression_parse_node> _operand;
    };

    /**
     * @brief Represents a variable definition in the abstract syntax tree (AST).
     */
    class variable_definition_parse_node : public statement_parse_node
    {
    public:
        variable_definition_parse_node(
            const std::string& name,
            const std::shared_ptr<type_reference_parse_node>& type_reference,
            const std::shared_ptr<expression_parse_node>& value,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::string& name() const { return _name; }
        const std::shared_ptr<type_reference_parse_node>& type_reference() const { return _type_reference; }
        const std::shared_ptr<expression_parse_node>& value() const { return _value; }
        virtual parse_node_type type() const override;

    private:
        std::string _name;
        std::shared_ptr<type_reference_parse_node> _type_reference;
        std::shared_ptr<expression_parse_node> _value;
    };

    /**
     * @brief Represents a variable reference expression in the abstract syntax tree (AST).
     */
    class variable_reference_expression_parse_node : public reference_expression_parse_node
    {
    public:
        variable_reference_expression_parse_node(
            const std::string& name,
            const std::shared_ptr<token>& start,
            const std::list<std::shared_ptr<comment_token>>& preceding_comments);
        const std::string& name() const { return _name; }
        virtual parse_node_type type() const override;

        virtual std::shared_ptr<type_reference_parse_node> to_type_reference() const override;
    private:
        std::string _name;
    };
}

#endif /* __OPENDRAFT_LANG_PARSE_NODE_HPP__ */