// <copyright file="ParseTreeXmlExporter.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.Tools;

using System;
using System.Xml;
using OpenDraft.Lang;

/// <summary>
/// Exports a parse tree to XML.
/// </summary>
public class ParseTreeXmlExporter : IDisposable
{
    private readonly XmlWriter writer;
    private readonly bool leaveOpen;

    /// <summary>
    /// Initializes a new instance of the <see cref="ParseTreeXmlExporter"/> class.
    /// </summary>
    /// <param name="writer">The XML writer to which the parse tree will be exported.</param>
    /// <param name="leaveOpen">A value indicating whether to leave the writer open after exporting.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="writer"/> is <c>null</c>.</exception>
    public ParseTreeXmlExporter(XmlWriter writer, bool leaveOpen = false)
    {
        this.writer = writer ?? throw new ArgumentNullException(nameof(writer));
        this.leaveOpen = leaveOpen;
    }

    /// <summary>
    /// Exports the specified program parse node to XML.
    /// </summary>
    /// <param name="program">The program parse node to export.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="program"/> is <c>null</c>.</exception>
    public void Export(ProgramParseNode program)
    {
        if (program == null)
        {
            throw new ArgumentNullException(nameof(program));
        }

        this.writer.WriteStartDocument();
        this.writer.WriteStartElement("program");
        this.writer.WriteStartElement("imports");
        foreach (var import in program.Imports)
        {
            this.writer.WriteStartElement("import");
            this.writer.WriteAttributeString("moduleName", import.ModuleName);
            this.writer.WriteEndElement(); // end "import"
        }

        this.writer.WriteFullEndElement(); // end "imports"

        foreach (var element in program.ProgramElements)
        {
            this.WriteProgramElement(element);
        }

        this.writer.WriteFullEndElement(); // end "program"
        this.writer.WriteEndDocument();
    }

    /// <inheritdoc/>
    public void Dispose()
    {
        if (!this.leaveOpen)
        {
            this.writer?.Close();
        }

        GC.SuppressFinalize(this);
    }

    private static string TypeReferenceToString(TypeReferenceParseNode typeReference)
    {
        if (typeReference == null)
        {
            throw new ArgumentNullException(nameof(typeReference));
        }

        return string.Join(".", typeReference.Names);
    }

    private void WriteProgramElement(ProgramElementParseNode element)
    {
        if (element is ClassParseNode classNode)
        {
            this.WriteClass(classNode);
            return;
        }

        if (element is EnumParseNode enumNode)
        {
            this.WriteEnum(enumNode);
            return;
        }

        if (element is InterfaceParseNode interfaceNode)
        {
            this.WriteInterface(interfaceNode);
            return;
        }

        if (element is FunctionParseNode functionNode)
        {
            this.WriteFunction(functionNode);
            return;
        }

        if (element is NamespaceParseNode namespaceNode)
        {
            this.WriteNamespace(namespaceNode);
            return;
        }

        if (element is TemplateParseNode templateNode)
        {
            this.WriteTemplate(templateNode);
            return;
        }

        if (element is StatementParseNode statementNode)
        {
            this.WriteStatement(statementNode);
            return;
        }

        throw new NotSupportedException($"Unsupported program element type: {element.GetType().FullName}");
    }

    private void WriteClass(ClassParseNode classNode)
    {
        this.writer.WriteStartElement("class");
        this.writer.WriteAttributeString("name", classNode.Name);
        this.writer.WriteFullEndElement(); // end "class"
    }

    private void WriteEnum(EnumParseNode enumNode)
    {
        this.writer.WriteStartElement("enum");
        this.writer.WriteAttributeString("name", enumNode.Name);
        foreach (var member in enumNode.Members)
        {
            this.writer.WriteStartElement("member");
            this.writer.WriteAttributeString("name", member.Name);
            if (member.Value != null)
            {
                this.writer.WriteAttributeString("value", member.Value.ToString());
            }

            this.writer.WriteFullEndElement(); // end "member"
        }

        this.writer.WriteFullEndElement(); // end "enum"
    }

    private void WriteInterface(InterfaceParseNode interfaceNode)
    {
        this.writer.WriteStartElement("interface");
        this.writer.WriteAttributeString("name", interfaceNode.Name);
        foreach (var member in interfaceNode.Members)
        {
            if (member is FunctionDeclarationParseNode functionMember)
            {
                this.WriteFunctionDeclaration(functionMember);
                continue;
            }

            if (member is TemplateDeclarationParseNode templateMember)
            {
                this.WriteTemplateDeclaration(templateMember);
                continue;
            }
        }

        this.writer.WriteFullEndElement(); // end "interface"
    }

    private void WriteFunctionDeclaration(FunctionDeclarationParseNode functionMember)
    {
        this.writer.WriteStartElement("function");
        this.writer.WriteAttributeString("name", functionMember.Name);
        this.WriteParameters(functionMember.Parameters);
        this.writer.WriteFullEndElement(); // end "function"
    }

    private void WriteTemplateDeclaration(TemplateDeclarationParseNode templateMember)
    {
        this.writer.WriteStartElement("template");
        this.writer.WriteAttributeString("name", templateMember.Name);
        this.WriteParameters(templateMember.Parameters);
        this.writer.WriteFullEndElement(); // end "template"
    }

    private void WriteFunction(FunctionParseNode functionNode)
    {
        this.writer.WriteStartElement("function");
        this.writer.WriteAttributeString("name", functionNode.Name);
        this.WriteParameters(functionNode.Parameters);
        this.WriteStatement(functionNode.Body);
        this.writer.WriteFullEndElement(); // end "function"
    }

    private void WriteNamespace(NamespaceParseNode namespaceNode)
    {
        this.writer.WriteStartElement("namespace");
        this.writer.WriteAttributeString("name", namespaceNode.Name);
        foreach (var element in namespaceNode.NamespaceMembers)
        {
            this.WriteProgramElement(element);
        }

        this.writer.WriteFullEndElement(); // end "namespace"
    }

    private void WriteTemplate(TemplateParseNode templateNode)
    {
        this.writer.WriteStartElement("template");
        this.writer.WriteAttributeString("name", templateNode.Name);
        this.WriteParameters(templateNode.Parameters);
        this.WriteStatement(templateNode.Body);
        this.writer.WriteFullEndElement(); // end "template"
    }

    private void WriteParameters(IEnumerable<ParameterDeclarationParseNode> parameters)
    {
        this.writer.WriteStartElement("parameters");
        foreach (var parameter in parameters)
        {
            this.writer.WriteStartElement("parameter");
            this.writer.WriteAttributeString("name", parameter.Name);
            if (parameter.Type != null)
            {
                this.writer.WriteAttributeString("type", TypeReferenceToString(parameter.Type));
            }

            this.writer.WriteFullEndElement(); // end "parameter"
        }

        this.writer.WriteFullEndElement(); // end "parameters"
    }

    private void WriteStatement(StatementParseNode statementNode)
    {
        if (statementNode is BlockStatementParseNode blockStatement)
        {
            this.WriteBlockStatement(blockStatement);
            return;
        }

        if (statementNode is BreakStatementParseNode breakStatement)
        {
            this.WriteBreakStatement(breakStatement);
            return;
        }

        if (statementNode is CallStatementParseNode callStatement)
        {
            this.WriteCallStatement(callStatement);
            return;
        }

        if (statementNode is ContinueStatementParseNode continueStatement)
        {
            this.WriteContinueStatement(continueStatement);
            return;
        }

        if (statementNode is ForStatementParseNode forStatement)
        {
            this.WriteForStatement(forStatement);
            return;
        }

        if (statementNode is IfStatementParseNode ifStatement)
        {
            this.WriteIfStatement(ifStatement);
            return;
        }

        if (statementNode is ReturnStatementParseNode returnStatement)
        {
            this.WriteReturnStatement(returnStatement);
            return;
        }

        if (statementNode is ThrowStatementParseNode throwStatement)
        {
            this.WriteThrowStatement(throwStatement);
            return;
        }

        if (statementNode is TraceStatementParseNode traceStatement)
        {
            this.WriteTraceStatement(traceStatement);
            return;
        }

        if (statementNode is VariableDefinitionParseNode variable)
        {
            this.WriteVariableDefinition(variable);
            return;
        }

        throw new NotSupportedException($"Unsupported statement type: {statementNode.GetType().FullName}");
    }

    private void WriteBlockStatement(BlockStatementParseNode blockStatement)
    {
        this.writer.WriteStartElement("block");
        foreach (var statement in blockStatement.Statements)
        {
            this.WriteStatement(statement);
        }

        this.writer.WriteFullEndElement(); // end "block"
    }

    private void WriteBreakStatement(BreakStatementParseNode breakStatement)
    {
        this.writer.WriteStartElement("break");
        this.writer.WriteEndElement(); // end "break"
    }

    private void WriteCallStatement(CallStatementParseNode callStatement)
    {
        this.writer.WriteStartElement("call");
        this.writer.WriteStartElement("target");
        this.WriteReferenceExpression(callStatement.Target);
        this.writer.WriteFullEndElement(); // end "target"
        this.writer.WriteStartElement("arguments");
        foreach (var argument in callStatement.Arguments)
        {
            this.WriteArgument(argument);
        }

        this.writer.WriteFullEndElement(); // end "arguments"
        this.writer.WriteFullEndElement(); // end "call"
    }

    private void WriteContinueStatement(ContinueStatementParseNode continueStatement)
    {
        this.writer.WriteStartElement("continue");
        this.writer.WriteEndElement(); // end "continue"
    }

    private void WriteForStatement(ForStatementParseNode forStatement)
    {
        this.writer.WriteStartElement("for");
        this.writer.WriteStartElement("conditions");
        foreach (var condition in forStatement.Conditions)
        {
            this.WriteForCondition(condition);
        }

        this.writer.WriteFullEndElement(); // end "conditions"
        this.WriteStatement(forStatement.Body);
        this.writer.WriteFullEndElement(); // end "for"
    }

    private void WriteForCondition(ForConditionParseNode condition)
    {
        this.writer.WriteStartElement("condition");
        if (condition.TypeReference != null)
        {
            this.writer.WriteAttributeString("type", TypeReferenceToString(condition.TypeReference));
        }

        this.writer.WriteStartElement("variableNames");
        foreach (var name in condition.VariableNames)
        {
            this.writer.WriteStartElement("name");
            this.writer.WriteString(name);
            this.writer.WriteFullEndElement(); // end "name"
        }

        this.writer.WriteFullEndElement(); // end "variableNames"

        this.writer.WriteStartElement("expression");
        this.WriteExpression(condition.Expression);
        this.writer.WriteFullEndElement(); // end "expression"

        this.writer.WriteFullEndElement(); // end "condition"
    }

    private void WriteIfStatement(IfStatementParseNode ifStatement)
    {
        this.writer.WriteStartElement("if");
        this.writer.WriteStartElement("condition");
        this.WriteExpression(ifStatement.Condition);
        this.writer.WriteFullEndElement(); // end "condition"
        this.writer.WriteStartElement("then");
        this.WriteStatement(ifStatement.ThenStatement);
        this.writer.WriteFullEndElement(); // end "then"
        if (ifStatement.ElseStatement != null)
        {
            this.writer.WriteStartElement("else");
            this.WriteStatement(ifStatement.ElseStatement);
            this.writer.WriteFullEndElement(); // end "else"
        }

        this.writer.WriteFullEndElement(); // end "if"
    }

    private void WriteReturnStatement(ReturnStatementParseNode returnStatement)
    {
        this.writer.WriteStartElement("return");
        if (returnStatement.Expression != null)
        {
            this.WriteExpression(returnStatement.Expression);
        }

        this.writer.WriteEndElement(); // end "return"
    }

    private void WriteThrowStatement(ThrowStatementParseNode throwStatement)
    {
        this.writer.WriteStartElement("throw");
        this.WriteExpression(throwStatement.Expression);
        this.writer.WriteFullEndElement(); // end "throw"
    }

    private void WriteTraceStatement(TraceStatementParseNode traceStatement)
    {
        string elementName = traceStatement.Severity switch
        {
            TraceStatementSeverity.Debug => "debug",
            TraceStatementSeverity.Info => "info",
            TraceStatementSeverity.Warn => "warn",
            TraceStatementSeverity.Error => "error",
            TraceStatementSeverity.Verbose => "verbose",
            _ => throw new NotSupportedException($"Unsupported trace severity: {traceStatement.Severity}"),
        };

        this.writer.WriteStartElement(elementName);
        this.WriteExpression(traceStatement.Expression);
        this.writer.WriteFullEndElement(); // end elementName
    }

    private void WriteVariableDefinition(VariableDefinitionParseNode variable)
    {
        this.writer.WriteStartElement("variable");
        this.writer.WriteAttributeString("name", variable.Name);
        if (variable.Type != null)
        {
            this.writer.WriteAttributeString("type", TypeReferenceToString(variable.Type));
        }

        this.WriteExpression(variable.Value);
        this.writer.WriteFullEndElement(); // end "variable"
    }

    private void WriteExpression(ExpressionParseNode expression)
    {
        if (expression is AddExpressionParseNode addExpression)
        {
            this.WriteAddExpression(addExpression);
            return;
        }

        if (expression is ArrayExpressionParseNode arrayExpression)
        {
            this.WriteArrayExpression(arrayExpression);
            return;
        }

        if (expression is BitwiseAndExpressionParseNode bitwiseAndExpression)
        {
            this.WriteBitwiseAndExpression(bitwiseAndExpression);
            return;
        }

        if (expression is BitwiseOrExpressionParseNode bitwiseOrExpression)
        {
            this.WriteBitwiseOrExpression(bitwiseOrExpression);
            return;
        }

        if (expression is BitwiseXorExpressionParseNode bitwiseXorExpression)
        {
            this.WriteBitwiseXorExpression(bitwiseXorExpression);
            return;
        }

        if (expression is ConditionalExpressionParseNode conditionalExpression)
        {
            this.WriteConditionalExpression(conditionalExpression);
            return;
        }

        if (expression is EqualityExpressionParseNode equalityExpression)
        {
            this.WriteEqualityExpression(equalityExpression);
            return;
        }

        if (expression is LiteralExpressionParseNode<bool> boolExpression)
        {
            this.WriteLiteralExpression(boolExpression);
            return;
        }

        if (expression is LiteralExpressionParseNode<string> stringExpression)
        {
            this.WriteLiteralExpression(stringExpression);
            return;
        }

        if (expression is LiteralExpressionParseNode<long> longExpression)
        {
            this.WriteLiteralExpression(longExpression);
            return;
        }

        if (expression is LiteralExpressionParseNode<decimal> decimalExpression)
        {
            this.WriteLiteralExpression(decimalExpression);
            return;
        }

        if (expression is LogicalAndExpressionParseNode logicalAndExpression)
        {
            this.WriteLogicalAndExpression(logicalAndExpression);
            return;
        }

        if (expression is LogicalOrExpressionParseNode logicalOrExpression)
        {
            this.WriteLogicalOrExpression(logicalOrExpression);
            return;
        }

        if (expression is MulExpressionParseNode mulExpression)
        {
            this.WriteMulExpression(mulExpression);
            return;
        }

        if (expression is NullExpressionParseNode nullExpression)
        {
            this.WriteLiteralExpression(nullExpression);
            return;
        }

        if (expression is ObjectExpressionParseNode objectExpression)
        {
            this.WriteObjectExpression(objectExpression);
            return;
        }

        if (expression is RangeExpressionParseNode rangeExpression)
        {
            this.WriteRangeExpression(rangeExpression);
            return;
        }

        if (expression is RelationalExpressionParseNode relationalExpression)
        {
            this.WriteRelationalExpression(relationalExpression);
            return;
        }

        if (expression is ShiftExpressionParseNode shiftExpression)
        {
            this.WriteShiftExpression(shiftExpression);
            return;
        }

        if (expression is UnaryExpressionParseNode unaryExpression)
        {
            this.WriteUnaryExpression(unaryExpression);
            return;
        }

        if (expression is ReferenceExpressionParseNode referenceExpression)
        {
            this.WriteReferenceExpression(referenceExpression);
            return;
        }
    }

    private void WriteReferenceExpression(ReferenceExpressionParseNode referenceExpression)
    {
        if (referenceExpression is CallExpressionParseNode callExpression)
        {
            this.WriteCallExpression(callExpression);
            return;
        }

        if (referenceExpression is MemberReferenceExpressionParseNode memberAccessExpression)
        {
            this.WriteMemberReferenceExpression(memberAccessExpression);
            return;
        }

        if (referenceExpression is VariableReferenceParseNode variableReferenceExpression)
        {
            this.WriteVariableReference(variableReferenceExpression);
            return;
        }

        if (referenceExpression is IndexExpressionParseNode indexExpression)
        {
            this.WriteIndexExpression(indexExpression);
            return;
        }

        throw new NotSupportedException($"Unsupported reference expression type: {referenceExpression.GetType().FullName}");
    }

    private void WriteCallExpression(CallExpressionParseNode callExpression)
    {
        this.writer.WriteStartElement("call");
        this.writer.WriteStartElement("target");
        this.WriteReferenceExpression(callExpression.Target);
        this.writer.WriteFullEndElement(); // end "target"
        this.writer.WriteStartElement("arguments");
        foreach (var argument in callExpression.Arguments)
        {
            this.WriteArgument(argument);
        }

        this.writer.WriteFullEndElement(); // end "arguments"
        this.writer.WriteFullEndElement(); // end "call"
    }

    private void WriteMemberReferenceExpression(MemberReferenceExpressionParseNode memberAccessExpression)
    {
        this.writer.WriteStartElement("member");
        this.writer.WriteAttributeString("name", memberAccessExpression.Name);
        this.writer.WriteStartElement("target");
        this.WriteReferenceExpression(memberAccessExpression.Target);
        this.writer.WriteFullEndElement(); // end "target"
        this.writer.WriteFullEndElement(); // end "member"
    }

    private void WriteVariableReference(VariableReferenceParseNode variableReferenceExpression)
    {
        this.writer.WriteStartElement("var");
        this.writer.WriteAttributeString("name", variableReferenceExpression.Name);
        this.writer.WriteFullEndElement(); // end "variableReference"
    }

    private void WriteIndexExpression(IndexExpressionParseNode indexExpression)
    {
        this.writer.WriteStartElement("index");
        this.writer.WriteStartElement("target");
        this.WriteReferenceExpression(indexExpression.Target);
        this.writer.WriteFullEndElement(); // end "target"

        foreach (var index in indexExpression.Indexes)
        {
            this.WriteExpression(index);
        }

        this.writer.WriteFullEndElement(); // end "index"
    }

    private void WriteArgument(ArgumentParseNode argument)
    {
        this.writer.WriteStartElement("argument");
        if (argument.Name != null)
        {
            this.writer.WriteAttributeString("name", argument.Name);
        }

        this.WriteExpression(argument.Value);
        this.writer.WriteFullEndElement(); // end "argument"
    }

    private void WriteAddExpression(AddExpressionParseNode addExpression)
    {
        this.writer.WriteStartElement(addExpression.IsSubtraction ? "sub" : "add");
        this.WriteExpression(addExpression.Left);
        this.WriteExpression(addExpression.Right);
        this.writer.WriteFullEndElement(); // end add/sub
    }

    private void WriteArrayExpression(ArrayExpressionParseNode arrayExpression)
    {
        this.writer.WriteStartElement("array");
        foreach (var row in arrayExpression.Elements)
        {
            this.writer.WriteStartElement("row");
            foreach (var element in row)
            {
                this.WriteExpression(element);
            }

            this.writer.WriteFullEndElement(); // end "row"
        }

        this.writer.WriteFullEndElement(); // end "array"
    }

    private void WriteBitwiseAndExpression(BitwiseAndExpressionParseNode bitwiseAndExpression)
    {
        this.writer.WriteStartElement("bitwiseAnd");
        this.WriteExpression(bitwiseAndExpression.Left);
        this.WriteExpression(bitwiseAndExpression.Right);
        this.writer.WriteFullEndElement(); // end "bitwiseAnd"
    }

    private void WriteBitwiseOrExpression(BitwiseOrExpressionParseNode bitwiseOrExpression)
    {
        this.writer.WriteStartElement("bitwiseOr");
        this.WriteExpression(bitwiseOrExpression.Left);
        this.WriteExpression(bitwiseOrExpression.Right);
        this.writer.WriteFullEndElement(); // end "bitwiseOr"
    }

    private void WriteBitwiseXorExpression(BitwiseXorExpressionParseNode bitwiseXorExpression)
    {
        this.writer.WriteStartElement("bitwiseXor");
        this.WriteExpression(bitwiseXorExpression.Left);
        this.WriteExpression(bitwiseXorExpression.Right);
        this.writer.WriteFullEndElement(); // end "bitwiseXor"
    }

    private void WriteConditionalExpression(ConditionalExpressionParseNode conditionalExpression)
    {
        this.writer.WriteStartElement("conditional");
        this.writer.WriteStartElement("condition");
        this.WriteExpression(conditionalExpression.Condition);
        this.writer.WriteFullEndElement(); // end "condition"

        this.writer.WriteStartElement("true");
        this.WriteExpression(conditionalExpression.TrueExpression);
        this.writer.WriteFullEndElement(); // end "true"

        this.writer.WriteStartElement("false");
        this.WriteExpression(conditionalExpression.FalseExpression);
        this.writer.WriteFullEndElement(); // end "false"

        this.writer.WriteFullEndElement(); // end "conditional"
    }

    private void WriteEqualityExpression(EqualityExpressionParseNode equalityExpression)
    {
        this.writer.WriteStartElement(equalityExpression.IsInequality ? "notEqual" : "equal");
        this.WriteExpression(equalityExpression.Left);
        this.WriteExpression(equalityExpression.Right);
        this.writer.WriteFullEndElement(); // end "equal"/"notEqual"
    }

    private void WriteLogicalAndExpression(LogicalAndExpressionParseNode logicalAndExpression)
    {
        this.writer.WriteStartElement("and");
        this.WriteExpression(logicalAndExpression.Left);
        this.WriteExpression(logicalAndExpression.Right);
        this.writer.WriteFullEndElement(); // end "and"
    }

    private void WriteLogicalOrExpression(LogicalOrExpressionParseNode logicalOrExpression)
    {
        this.writer.WriteStartElement("or");
        this.WriteExpression(logicalOrExpression.Left);
        this.WriteExpression(logicalOrExpression.Right);
        this.writer.WriteFullEndElement(); // end "or"
    }

    private void WriteMulExpression(MulExpressionParseNode mulExpression)
    {
        string elementName = mulExpression.Operator switch
        {
            MulOperator.Multiply => "mul",
            MulOperator.Divide => "div",
            MulOperator.Modulo => "mod",
            _ => throw new NotSupportedException($"Unsupported multiplication operator: {mulExpression.Operator}"),
        };

        this.writer.WriteStartElement(elementName);
        this.WriteExpression(mulExpression.Left);
        this.WriteExpression(mulExpression.Right);
        this.writer.WriteFullEndElement(); // end elementName
    }

    private void WriteLiteralExpression(NullExpressionParseNode nullExpression)
    {
        this.writer.WriteStartElement("null");
        this.writer.WriteEndElement(); // end "null"
    }

    private void WriteObjectExpression(ObjectExpressionParseNode objectExpression)
    {
        this.writer.WriteStartElement("object");
        foreach (var member in objectExpression.Members)
        {
            this.writer.WriteStartElement("member");
            this.writer.WriteAttributeString("name", member.Name);
            this.WriteExpression(member.Value);
            this.writer.WriteFullEndElement(); // end "member"
        }

        this.writer.WriteFullEndElement(); // end "object"
    }

    private void WriteRangeExpression(RangeExpressionParseNode rangeExpression)
    {
        this.writer.WriteStartElement("range");
        this.WriteExpression(rangeExpression.From);
        this.WriteExpression(rangeExpression.To);
        this.writer.WriteFullEndElement(); // end "range"
    }

    private void WriteRelationalExpression(RelationalExpressionParseNode relationalExpression)
    {
        string elementName = relationalExpression.Operator switch
        {
            RelationalOperator.LessThan => "lessThan",
            RelationalOperator.LessThanOrEqual => "lessThanOrEqual",
            RelationalOperator.GreaterThan => "greaterThan",
            RelationalOperator.GreaterThanOrEqual => "greaterThanOrEqual",
            RelationalOperator.InSet => "in",
            _ => throw new NotSupportedException($"Unsupported relational operator: {relationalExpression.Operator}"),
        };

        this.writer.WriteStartElement(elementName);
        this.WriteExpression(relationalExpression.Left);
        this.WriteExpression(relationalExpression.Right);
        this.writer.WriteFullEndElement(); // end elementName
    }

    private void WriteShiftExpression(ShiftExpressionParseNode shiftExpression)
    {
        string elementName = shiftExpression.Operator switch
        {
            ShiftOperator.LeftShift => "shiftLeft",
            ShiftOperator.RightShift => "shiftRight",
            _ => throw new NotSupportedException($"Unsupported shift operator: {shiftExpression.Operator}"),
        };

        this.writer.WriteStartElement(elementName);
        this.WriteExpression(shiftExpression.Left);
        this.WriteExpression(shiftExpression.Right);
        this.writer.WriteFullEndElement(); // end elementName
    }

    private void WriteUnaryExpression(UnaryExpressionParseNode unaryExpression)
    {
        string elementName = unaryExpression.Operator switch
        {
            UnaryOperator.Negate => "neg",
            UnaryOperator.BitwiseNot => "bitwiseNot",
            UnaryOperator.LogicalNot => "not",
            _ => throw new NotSupportedException($"Unsupported unary operator: {unaryExpression.Operator}"),
        };

        this.writer.WriteStartElement(elementName);
        this.WriteExpression(unaryExpression.Operand);
        this.writer.WriteFullEndElement(); // end elementName
    }

    private void WriteLiteralExpression(LiteralExpressionParseNode<bool> boolExpression)
    {
        this.writer.WriteStartElement("boolean");
        this.writer.WriteAttributeString("value", boolExpression.Value ? "true" : "false");
        this.writer.WriteEndElement(); // end "boolean"
    }

    private void WriteLiteralExpression(LiteralExpressionParseNode<string> stringExpression)
    {
        this.writer.WriteStartElement("string");
        this.writer.WriteString(stringExpression.Value);
        this.writer.WriteEndElement(); // end "string"
    }

    private void WriteLiteralExpression(LiteralExpressionParseNode<long> longExpression)
    {
        this.writer.WriteStartElement("integer");
        this.writer.WriteAttributeString("value", longExpression.Value.ToString());
        this.writer.WriteEndElement(); // end "integer"
    }

    private void WriteLiteralExpression(LiteralExpressionParseNode<decimal> decimalExpression)
    {
        this.writer.WriteStartElement("decimal");
        var value = decimalExpression.Value.ToString("G29", System.Globalization.CultureInfo.InvariantCulture);
        this.writer.WriteAttributeString("value", value);
        this.writer.WriteEndElement(); // end "decimal"
    }
}