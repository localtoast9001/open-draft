/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file parse_tree_xml_exporter.cpp
 * @brief Contains the implementation of the parse_tree_xml_exporter class.
 */
#include <tools/parse_tree_xml_exporter.hpp>
#include <tools/xml_writer.hpp>
#include <format>

using namespace opendraft::lang;
using namespace opendraft::lang::tools;
using namespace std;

/**
 * @brief Implementation class for parse_tree_xml_exporter.
 * This class encapsulates the internal implementation details of the parse_tree_xml_exporter.
 * It is used to separate the interface from the implementation, allowing for better encapsulation and maintainability of the code.
 * The implementation class is not exposed to users of the parse_tree_xml_export
 */
class parse_tree_xml_exporter_impl
{
public:
    parse_tree_xml_exporter_impl(xml_writer& writer)
        : _writer(writer)
    {
    }

    void export_program(const program_parse_node& root);

private:
    xml_writer& _writer;

    static string type_reference_to_string(const type_reference_parse_node& type_ref_node);

    void write_program_element(const program_element_parse_node& element);
    void write_class(const class_parse_node& class_node);
    void write_enum(const enum_parse_node& enum_node);
    void write_interface(const interface_parse_node& interface_node);
    void write_function(const function_parse_node& function_node);
    void write_template(const template_parse_node& template_node);
    void write_statement(const statement_parse_node& statement_node);
    void write_expression(const expression_parse_node& expression_node);

    void write_function_declaration(const function_declaration_parse_node& func_decl_node);
    void write_template_declaration(const template_declaration_parse_node& template_decl_node);

    void write_block_statement(const block_statement_parse_node& block_node);
    void write_if_statement(const if_statement_parse_node& if_node);
    void write_for_statement(const for_statement_parse_node& for_node);
    void write_return_statement(const return_statement_parse_node& return_node);
    void write_call_statement(const call_statement_parse_node& call_node);
    void write_variable_definition(const variable_definition_parse_node& var_def_node);
    void write_throw_statement(const throw_statement_parse_node& throw_node);
    void write_break_statement(const break_statement_parse_node& break_node);
    void write_continue_statement(const continue_statement_parse_node& continue_node);
    void write_trace_statement(const trace_statement_parse_node& trace_node);

    void write_for_condition(const for_condition_parse_node& for_cond_node);

    void write_add_expression(const add_expression_parse_node& add_node);
    void write_mul_expression(const mul_expression_parse_node& mul_node);
    void write_range_expression(const range_expression_parse_node& range_node);
    void write_conditional_expression(const conditional_expression_parse_node& cond_node);
    void write_logical_or_expression(const logical_or_expression_parse_node& or_node);
    void write_logical_and_expression(const logical_and_expression_parse_node& and_node);
    void write_equality_expression(const equality_expression_parse_node& eq_node);
    void write_relational_expression(const relational_expression_parse_node& rel_node);
    void write_reference_expression(const reference_expression_parse_node& var_ref_node);
    void write_variable_reference_expression(const variable_reference_expression_parse_node& var_ref_node);
    void write_member_reference_expression(const member_reference_expression_parse_node& member_ref_node);
    void write_index_expression(const index_expression_parse_node& index_node);
    void write_call_expression(const call_expression_parse_node& call_node);
    void write_array_expression(const array_expression_parse_node& array_node);
    void write_boolean_literal_expression(const boolean_literal_expression_parse_node& bool_node);
    void write_numeric_literal_expression(const numeric_literal_expression_parse_node& int_node);
    void write_string_literal_expression(const string_literal_expression_parse_node& str_node);
    void write_null_expression(const null_expression_parse_node& null_node);
    void write_object_expression(const object_expression_parse_node& obj_node);
    void write_object_member(const object_member_parse_node& member_node);
    void write_shift_expression(const shift_expression_parse_node& shift_node);
    void write_unary_expression(const unary_expression_parse_node& unary_node);
    void write_bitwise_and_expression(const bitwise_and_expression_parse_node& bitwise_and_node);
    void write_bitwise_or_expression(const bitwise_or_expression_parse_node& bitwise_or_node);
    void write_bitwise_xor_expression(const bitwise_xor_expression_parse_node& bitwise_xor_node);
    void write_parameters(const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters);
    void write_arguments(const std::list<std::shared_ptr<argument_parse_node>>& arguments);
    void write_argument(const argument_parse_node& argument_node);

    // Disable copy and assignment
    parse_tree_xml_exporter_impl(const parse_tree_xml_exporter_impl&) = delete;
    parse_tree_xml_exporter_impl& operator=(const parse_tree_xml_exporter_impl&) = delete;
};

void parse_tree_xml_exporter_impl::export_program(const program_parse_node& root)
{
    _writer.write_start_element("program");
    
    // Export imports
    _writer.write_start_element("imports");
    for (const auto& import : root.imports())
    {
        _writer.write_start_element("import");
        _writer.write_attribute("moduleName", import->module_name());
        _writer.write_end_element(); // End of import
    }

    _writer.write_full_end_element(); // End of imports

    // Export program elements
    for (const auto& element : root.program_elements())
    {
        write_program_element(*element);
    }

    _writer.write_full_end_element(); // End of program
}

string parse_tree_xml_exporter_impl::type_reference_to_string(const type_reference_parse_node& type_ref_node)
{
    std::string result;
    for (const auto& name : type_ref_node.names())
    {
        if (!result.empty())
        {
            result += ".";
        }

        result += name;
    }

    return result;
}

void parse_tree_xml_exporter_impl::write_program_element(const program_element_parse_node& element)
{
    switch (element.type())
    {
    case parse_node_type::PARSE_NODE_CLASS:
        write_class(static_cast<const class_parse_node&>(element));
        break;
    case parse_node_type::PARSE_NODE_ENUM:
        write_enum(static_cast<const enum_parse_node&>(element));
        break;
    case parse_node_type::PARSE_NODE_INTERFACE:
        write_interface(static_cast<const interface_parse_node&>(element));
        break;
    case parse_node_type::PARSE_NODE_FUNCTION:
        write_function(static_cast<const function_parse_node&>(element));
        break;
    case parse_node_type::PARSE_NODE_TEMPLATE:
        write_template(static_cast<const template_parse_node&>(element));
        break;
    default:
        if (!element.is_statement())
        {
            throw std::logic_error("Unsupported program element type for XML export.");
        }

        return write_statement(static_cast<const statement_parse_node&>(element));
    }
}

void parse_tree_xml_exporter_impl::write_class(const class_parse_node& class_node)
{
    _writer.write_start_element("class");
    _writer.write_attribute("name", class_node.name());
    _writer.write_full_end_element(); // End of class
}

void parse_tree_xml_exporter_impl::write_enum(const enum_parse_node& enum_node)
{
    _writer.write_start_element("enum");
    _writer.write_attribute("name", enum_node.name());
    for (const auto& member : enum_node.members())
    {
        _writer.write_start_element("member");
        _writer.write_attribute("name", member->name());
        if (member->has_value())
        {
            _writer.write_attribute("value", std::to_string(member->value()));
        }

        _writer.write_full_end_element(); // End of member
    }

    _writer.write_full_end_element(); // End of enum
}

void parse_tree_xml_exporter_impl::write_interface(const interface_parse_node& interface_node)
{
    _writer.write_start_element("interface");
    _writer.write_attribute("name", interface_node.name());
    for (const auto& member : interface_node.members())
    {
        switch (member->type())
        {
        case parse_node_type::PARSE_NODE_FUNCTION_DECLARATION:
            write_function_declaration(static_cast<const function_declaration_parse_node&>(*member));
            break;
        case parse_node_type::PARSE_NODE_TEMPLATE_DECLARATION:
            write_template_declaration(static_cast<const template_declaration_parse_node&>(*member));
            break;
        default:
            // Handle other interface member types if needed
            break;
        }
    }

    _writer.write_full_end_element(); // End of interface
}

void parse_tree_xml_exporter_impl::write_function(const function_parse_node& function_node)
{
    _writer.write_start_element("function");
    _writer.write_attribute("name", function_node.name());
    write_parameters(function_node.parameters());
    write_statement(*function_node.body());
    _writer.write_full_end_element(); // End of function
}

void parse_tree_xml_exporter_impl::write_template(const template_parse_node& template_node)
{
    _writer.write_start_element("template");
    _writer.write_attribute("name", template_node.name());
    write_parameters(template_node.parameters());
    write_statement(*template_node.body());
    _writer.write_full_end_element(); // End of template
}

void parse_tree_xml_exporter_impl::write_statement(const statement_parse_node& statement_node)
{
    switch (statement_node.type())
    {
    case parse_node_type::PARSE_NODE_BLOCK_STATEMENT:
        write_block_statement(static_cast<const block_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_IF_STATEMENT:
        write_if_statement(static_cast<const if_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_FOR_STATEMENT: 
        write_for_statement(static_cast<const for_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_RETURN_STATEMENT:
        write_return_statement(static_cast<const return_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_CALL_STATEMENT:
        write_call_statement(static_cast<const call_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_VARIABLE_DEFINITION:
        write_variable_definition(static_cast<const variable_definition_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_THROW_STATEMENT:
        write_throw_statement(static_cast<const throw_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_BREAK_STATEMENT:
        write_break_statement(static_cast<const break_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_CONTINUE_STATEMENT:
        write_continue_statement(static_cast<const continue_statement_parse_node&>(statement_node));
        break;
    case parse_node_type::PARSE_NODE_TRACE_STATEMENT:
        write_trace_statement(static_cast<const trace_statement_parse_node&>(statement_node));
        break;
    default:
        // Handle other statement types if needed
        break;
    }
}

void parse_tree_xml_exporter_impl::write_expression(const expression_parse_node& expression_node)
{
    switch (expression_node.type())
    {
    case parse_node_type::PARSE_NODE_ADD_EXPRESSION:
        write_add_expression(static_cast<const add_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_MUL_EXPRESSION:
        write_mul_expression(static_cast<const mul_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_RANGE_EXPRESSION:
        write_range_expression(static_cast<const range_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_CONDITIONAL_EXPRESSION:
        write_conditional_expression(static_cast<const conditional_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_LOGICAL_OR_EXPRESSION:
        write_logical_or_expression(static_cast<const logical_or_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_LOGICAL_AND_EXPRESSION:
        write_logical_and_expression(static_cast<const logical_and_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_EQUALITY_EXPRESSION:
        write_equality_expression(static_cast<const equality_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_RELATIONAL_EXPRESSION:
        write_relational_expression(static_cast<const relational_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_UNARY_EXPRESSION:
        write_unary_expression(static_cast<const unary_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_NUMERIC_LITERAL_EXPRESSION:
        write_numeric_literal_expression(static_cast<const numeric_literal_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_STRING_LITERAL_EXPRESSION:
        write_string_literal_expression(static_cast<const string_literal_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_BOOLEAN_LITERAL_EXPRESSION:
        write_boolean_literal_expression(static_cast<const boolean_literal_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_SHIFT_EXPRESSION:
        write_shift_expression(static_cast<const shift_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_BITWISE_AND_EXPRESSION:
        write_bitwise_and_expression(static_cast<const bitwise_and_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_BITWISE_OR_EXPRESSION:
        write_bitwise_or_expression(static_cast<const bitwise_or_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_BITWISE_XOR_EXPRESSION:
        write_bitwise_xor_expression(static_cast<const bitwise_xor_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_NULL_EXPRESSION:
        write_null_expression(static_cast<const null_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_ARRAY_EXPRESSION:
        write_array_expression(static_cast<const array_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_OBJECT_EXPRESSION:
        write_object_expression(static_cast<const object_expression_parse_node&>(expression_node));
        break;
    case parse_node_type::PARSE_NODE_VARIABLE_REFERENCE:
    case parse_node_type::PARSE_NODE_MEMBER_REFERENCE_EXPRESSION:
    case parse_node_type::PARSE_NODE_INDEX_EXPRESSION:
    case parse_node_type::PARSE_NODE_CALL_EXPRESSION:
        write_reference_expression(static_cast<const reference_expression_parse_node&>(expression_node));
        break;
    default:
        // Handle other expression types if needed
        break;
    }
}

void parse_tree_xml_exporter_impl::write_block_statement(const block_statement_parse_node& block_node)
{
    _writer.write_start_element("block");
    for (const auto& statement : block_node.statements())
    {
        write_statement(*statement);
    }

    _writer.write_full_end_element(); // End of block
}

void parse_tree_xml_exporter_impl::write_if_statement(const if_statement_parse_node& if_node)
{
    _writer.write_start_element("if");
    _writer.write_start_element("condition");
    write_expression(*if_node.condition());
    _writer.write_end_element(); // End of condition
    _writer.write_start_element("then");
    write_statement(*if_node.then_statement());
    _writer.write_end_element(); // End of then
    if (if_node.else_statement())
    {
        _writer.write_start_element("else");
        write_statement(*if_node.else_statement());
        _writer.write_end_element(); // End of else
    }

    _writer.write_end_element(); // End of if
}

void parse_tree_xml_exporter_impl::write_for_statement(const for_statement_parse_node& for_node)
{
    _writer.write_start_element("for");
    _writer.write_start_element("conditions");
    for (const auto& condition : for_node.condition())
    {
        write_for_condition(*condition);
    }

    _writer.write_full_end_element(); // End of conditions
    write_statement(*for_node.body());
    _writer.write_end_element(); // End of for
}

void parse_tree_xml_exporter_impl::write_for_condition(const for_condition_parse_node& for_cond_node)
{
    _writer.write_start_element("condition");
    _writer.write_start_element("variableNames");
    for (const auto& var_name : for_cond_node.variable_names())
    {
        _writer.write_element("name", var_name);
    }

    _writer.write_end_element(); // End of variableNames

    _writer.write_start_element("expression");
    write_expression(*for_cond_node.expression());
    _writer.write_end_element(); // End of expression
    _writer.write_end_element(); // End of condition
}

void parse_tree_xml_exporter_impl::write_return_statement(const return_statement_parse_node& return_node)
{
    _writer.write_start_element("return");
    if (return_node.expression())
    {
        write_expression(*return_node.expression());
    }

    _writer.write_end_element(); // End of return
}

void parse_tree_xml_exporter_impl::write_call_statement(const call_statement_parse_node& call_node)
{
    _writer.write_start_element("call");
    _writer.write_start_element("target");
    write_expression(*call_node.target());
    _writer.write_end_element(); // End of target
    write_arguments(call_node.arguments());
    _writer.write_end_element(); // End of call
}

void parse_tree_xml_exporter_impl::write_variable_definition(const variable_definition_parse_node& var_def_node)
{
    _writer.write_start_element("variable");
    _writer.write_attribute("name", var_def_node.name());
    if (var_def_node.type_reference())
    {
        _writer.write_attribute("type", type_reference_to_string(*var_def_node.type_reference()));
    }

    if (var_def_node.value())
    {
        write_expression(*var_def_node.value());
    }

    _writer.write_end_element(); // End of variable
}

void parse_tree_xml_exporter_impl::write_throw_statement(const throw_statement_parse_node& throw_node)
{
    _writer.write_start_element("throw");
    write_expression(*throw_node.expression());
    _writer.write_end_element(); // End of throw
}

void parse_tree_xml_exporter_impl::write_break_statement(const break_statement_parse_node& break_node)
{
    _writer.write_start_element("break");
    _writer.write_end_element(); // End of break
}

void parse_tree_xml_exporter_impl::write_continue_statement(const continue_statement_parse_node& continue_node)
{
    _writer.write_start_element("continue");
    _writer.write_end_element(); // End of continue
}

void parse_tree_xml_exporter_impl::write_trace_statement(const trace_statement_parse_node& trace_node)
{
    const char* element_name = nullptr;
    switch (trace_node.severity())
    {
    case trace_statement_severity::TRACE_SEVERITY_INFO:
        element_name = "info";
        break;
    case trace_statement_severity::TRACE_SEVERITY_WARNING:
        element_name = "warn";
        break;
    case trace_statement_severity::TRACE_SEVERITY_ERROR:
        element_name = "error";
        break;
    case trace_statement_severity::TRACE_SEVERITY_VERBOSE:
        element_name = "verbose";
        break;
    case trace_statement_severity::TRACE_SEVERITY_DEBUG:
        element_name = "debug";
        break;
    default:
        // Handle unknown trace type if needed
        element_name = "unknown";
        break;
    }

    _writer.write_start_element(element_name);
    write_expression(*trace_node.expression());
    _writer.write_end_element(); // End of element_name
}

void parse_tree_xml_exporter_impl::write_function_declaration(const function_declaration_parse_node& func_decl_node)
{
    _writer.write_start_element("function");
    _writer.write_attribute("name", func_decl_node.name());
    write_parameters(func_decl_node.parameters());
    _writer.write_full_end_element(); // End of functionDeclaration
}

void parse_tree_xml_exporter_impl::write_template_declaration(const template_declaration_parse_node& template_decl_node)
{
    _writer.write_start_element("template");
    _writer.write_attribute("name", template_decl_node.name());
    write_parameters(template_decl_node.parameters());
    _writer.write_full_end_element(); // End of templateDeclaration
}

void parse_tree_xml_exporter_impl::write_parameters(const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters)
{
    _writer.write_start_element("parameters");
    for (const auto& param : parameters)
    {
        _writer.write_start_element("parameter");
        _writer.write_attribute("name", param->name());
        if (param->type_reference())
        {
            _writer.write_attribute("type", type_reference_to_string(*param->type_reference()));
        }

        _writer.write_full_end_element(); // End of parameter
    }

    _writer.write_full_end_element(); // End of parameters
}

void parse_tree_xml_exporter_impl::write_add_expression(const add_expression_parse_node& add_node)
{
    _writer.write_start_element(add_node.is_subtraction() ? "sub" : "add");
    write_expression(*add_node.left());
    write_expression(*add_node.right());
    _writer.write_end_element(); // End of add or sub
}

void parse_tree_xml_exporter_impl::write_mul_expression(const mul_expression_parse_node& mul_node)
{
    const char* element_name = nullptr;
    switch (mul_node.op())
    {
    case mul_operator::MUL_OPERATOR_MULTIPLY:
        element_name = "mul";
        break;
    case mul_operator::MUL_OPERATOR_DIVIDE:
        element_name = "div";
        break;
    case mul_operator::MUL_OPERATOR_MODULO:
        element_name = "mod";
        break;
    default:
        // Handle unknown operator if needed
        break;
    }

    _writer.write_start_element(element_name);
    write_expression(*mul_node.left());
    write_expression(*mul_node.right());
    _writer.write_end_element(); // End of mul or div or mod
}

void parse_tree_xml_exporter_impl::write_range_expression(const range_expression_parse_node& range_node)
{
    _writer.write_start_element("range");
    write_expression(*range_node.from());
    write_expression(*range_node.to());
    _writer.write_end_element(); // End of range
}

void parse_tree_xml_exporter_impl::write_conditional_expression(const conditional_expression_parse_node& cond_node)
{
    _writer.write_start_element("conditional");
    _writer.write_start_element("condition");
    write_expression(*cond_node.condition());
    _writer.write_end_element(); // End of condition
    _writer.write_start_element("true");
    write_expression(*cond_node.true_expression());
    _writer.write_end_element(); // End of true
    _writer.write_start_element("false");
    write_expression(*cond_node.false_expression());
    _writer.write_end_element(); // End of false
    _writer.write_end_element(); // End of conditional
}

void parse_tree_xml_exporter_impl::write_logical_or_expression(const logical_or_expression_parse_node& or_node)
{
    _writer.write_start_element("or");
    write_expression(*or_node.left());
    write_expression(*or_node.right());
    _writer.write_end_element(); // End of or
}

void parse_tree_xml_exporter_impl::write_logical_and_expression(const logical_and_expression_parse_node& and_node)
{
    _writer.write_start_element("and");
    write_expression(*and_node.left());
    write_expression(*and_node.right());
    _writer.write_end_element(); // End of and
}

void parse_tree_xml_exporter_impl::write_equality_expression(const equality_expression_parse_node& eq_node)
{
    _writer.write_start_element(eq_node.is_inequality() ? "notEqual" : "equal");
    write_expression(*eq_node.left());
    write_expression(*eq_node.right());
    _writer.write_end_element(); // End of equal or notEqual
}

void parse_tree_xml_exporter_impl::write_relational_expression(const relational_expression_parse_node& rel_node)
{
    const char* element_name = nullptr;
    switch (rel_node.op())
    {
    case relational_operator::RELATIONAL_OPERATOR_LESS_THAN:
        element_name = "lessThan";
        break;
    case relational_operator::RELATIONAL_OPERATOR_LESS_THAN_OR_EQUAL:
        element_name = "lessThanOrEqual";
        break;
    case relational_operator::RELATIONAL_OPERATOR_GREATER_THAN:
        element_name = "greaterThan";
        break;
    case relational_operator::RELATIONAL_OPERATOR_GREATER_THAN_OR_EQUAL:
        element_name = "greaterThanOrEqual";
        break;
    case relational_operator::RELATIONAL_OPERATOR_IN_SET:
        element_name = "in";
        break;
    default:
        // Handle unknown relation type if needed
        break;
    }

    _writer.write_start_element(element_name);
    write_expression(*rel_node.left());
    write_expression(*rel_node.right());
    _writer.write_end_element(); // End of relational expression
}

void parse_tree_xml_exporter_impl::write_reference_expression(const reference_expression_parse_node& ref_node)
{
    switch (ref_node.type())
    {
    case parse_node_type::PARSE_NODE_VARIABLE_REFERENCE:
        write_variable_reference_expression(static_cast<const variable_reference_expression_parse_node&>(ref_node));
        break;
    case parse_node_type::PARSE_NODE_MEMBER_REFERENCE_EXPRESSION:
        write_member_reference_expression(static_cast<const member_reference_expression_parse_node&>(ref_node));
        break;
    case parse_node_type::PARSE_NODE_INDEX_EXPRESSION:
        write_index_expression(static_cast<const index_expression_parse_node&>(ref_node));
        break;
    case parse_node_type::PARSE_NODE_CALL_EXPRESSION:
        write_call_expression(static_cast<const call_expression_parse_node&>(ref_node));
        break;
    default:
        // Handle other reference expression types if needed
        break;
    }
}

void parse_tree_xml_exporter_impl::write_variable_reference_expression(const variable_reference_expression_parse_node& var_ref_node)
{
    _writer.write_start_element("var");
    _writer.write_attribute("name", var_ref_node.name());
    _writer.write_full_end_element(); // End of variableReference
}

void parse_tree_xml_exporter_impl::write_member_reference_expression(const member_reference_expression_parse_node& member_ref_node)
{
    _writer.write_start_element("member");
    _writer.write_attribute("name", member_ref_node.member_name());
    _writer.write_start_element("target");
    write_reference_expression(*member_ref_node.target());
    _writer.write_end_element(); // End of target
    _writer.write_end_element(); // End of member
}

void parse_tree_xml_exporter_impl::write_index_expression(const index_expression_parse_node& index_node)
{
    _writer.write_start_element("index");
    _writer.write_start_element("target");
    write_reference_expression(*index_node.target());
    _writer.write_end_element(); // End of target

    for (const auto& index_expr : index_node.indexes())
    {
        write_expression(*index_expr);
    }

    _writer.write_end_element(); // End of indexExpression
}

void parse_tree_xml_exporter_impl::write_call_expression(const call_expression_parse_node& call_node)
{
    _writer.write_start_element("call");
    _writer.write_start_element("target");
    write_reference_expression(*call_node.target());
    _writer.write_end_element(); // End of target
    write_arguments(call_node.arguments());
    _writer.write_end_element(); // End of call
}

void parse_tree_xml_exporter_impl::write_array_expression(const array_expression_parse_node& array_node)
{
    _writer.write_start_element("array");
    for (const auto& row : array_node.elements())
    {
        _writer.write_start_element("row");
        for (const auto& element : row)
        {
            write_expression(*element);
        }

        _writer.write_full_end_element(); // End of row
    }

    _writer.write_full_end_element(); // End of array
}

void parse_tree_xml_exporter_impl::write_object_expression(const object_expression_parse_node& obj_node)
{
    _writer.write_start_element("object");
    for (const auto& member : obj_node.members())
    {
        write_object_member(*member);
    }

    _writer.write_end_element(); // End of object
}

void parse_tree_xml_exporter_impl::write_object_member(const object_member_parse_node& member_node)
{
    _writer.write_start_element("member");
    _writer.write_attribute("name", member_node.name());
    write_expression(*member_node.value());
    _writer.write_end_element(); // End of objectMember
}

void parse_tree_xml_exporter_impl::write_unary_expression(const unary_expression_parse_node& unary_node)
{
    const char* element_name = nullptr;
    switch (unary_node.op())
    {
    case unary_operator::UNARY_OPERATOR_NEGATION:
        element_name = "neg";
        break;
    case unary_operator::UNARY_OPERATOR_LOGICAL_NOT:
        element_name = "not";
        break;
    case unary_operator::UNARY_OPERATOR_BITWISE_NOT:
        element_name = "bitwiseNot";
        break;
    default:
        // Handle unknown unary operator if needed
        break;
    }

    _writer.write_start_element(element_name);
    write_expression(*unary_node.operand());
    _writer.write_end_element(); // End of unaryExpression
}

void parse_tree_xml_exporter_impl::write_bitwise_and_expression(const bitwise_and_expression_parse_node& bitwise_and_node)
{
    _writer.write_start_element("bitwiseAnd");
    write_expression(*bitwise_and_node.left());
    write_expression(*bitwise_and_node.right());
    _writer.write_end_element(); // End of bitwiseAnd
}

void parse_tree_xml_exporter_impl::write_bitwise_or_expression(const bitwise_or_expression_parse_node& bitwise_or_node)
{
    _writer.write_start_element("bitwiseOr");
    write_expression(*bitwise_or_node.left());
    write_expression(*bitwise_or_node.right());
    _writer.write_end_element(); // End of bitwiseOr
}

void parse_tree_xml_exporter_impl::write_bitwise_xor_expression(const bitwise_xor_expression_parse_node& bitwise_xor_node)
{
    _writer.write_start_element("bitwiseXor");
    write_expression(*bitwise_xor_node.left());
    write_expression(*bitwise_xor_node.right());
    _writer.write_end_element(); // End of bitwiseXor
}

void parse_tree_xml_exporter_impl::write_null_expression(const null_expression_parse_node& null_node)
{
    _writer.write_start_element("null");
    _writer.write_end_element(); // End of null
}

void parse_tree_xml_exporter_impl::write_numeric_literal_expression(const numeric_literal_expression_parse_node& int_node)
{
    if (int_node.is_integer())
    {
        _writer.write_start_element("integer");
        _writer.write_attribute("value", std::to_string(int_node.integer_value()));
        _writer.write_end_element(); // End of integer
        return;
    }

    _writer.write_start_element("decimal");
    auto value = std::format(
        "{:.{}g}",
        int_node.float_value(),
        std::numeric_limits<double>::digits10 + 1);
    _writer.write_attribute("value", value);
    _writer.write_end_element(); // End of decimal
}

void parse_tree_xml_exporter_impl::write_string_literal_expression(const string_literal_expression_parse_node& str_node)
{
    _writer.write_element("string", str_node.value());
}

void parse_tree_xml_exporter_impl::write_boolean_literal_expression(const boolean_literal_expression_parse_node& bool_node)
{
    _writer.write_start_element("boolean");
    _writer.write_attribute("value", bool_node.value() ? "true" : "false");
    _writer.write_end_element(); // End of boolean
}

void parse_tree_xml_exporter_impl::write_shift_expression(const shift_expression_parse_node& shift_node)
{
    const char* element_name = nullptr;
    switch (shift_node.op())
    {
    case shift_operator::SHIFT_OPERATOR_LEFT_SHIFT:
        element_name = "shiftLeft";
        break;
    case shift_operator::SHIFT_OPERATOR_RIGHT_SHIFT:
        element_name = "shiftRight";
        break;
    default:
        // Handle unknown shift operator if needed
        break;
    }

    _writer.write_start_element(element_name);
    write_expression(*shift_node.left());
    write_expression(*shift_node.right());
    _writer.write_end_element(); // End of shiftLeft or shiftRight
}

void parse_tree_xml_exporter_impl::write_arguments(const std::list<std::shared_ptr<argument_parse_node>>& arguments)
{
    _writer.write_start_element("arguments");
    for (const auto& arg : arguments)
    {
        write_argument(*arg);
    }

    _writer.write_full_end_element(); // End of arguments
}

void parse_tree_xml_exporter_impl::write_argument(const argument_parse_node& argument_node)
{
    _writer.write_start_element("argument");
    if (!argument_node.name().empty())
    {
        _writer.write_attribute("name", argument_node.name());
    }

    write_expression(*argument_node.expression());
    _writer.write_end_element(); // End of argument
}

parse_tree_xml_exporter::parse_tree_xml_exporter(ostream& os)
    : _os(os)
{
}

void parse_tree_xml_exporter::export_program(const program_parse_node& root)
{
    xml_writer writer(_os);
    parse_tree_xml_exporter_impl impl(writer);
    impl.export_program(root);
}
