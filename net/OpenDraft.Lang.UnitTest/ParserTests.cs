// <copyright file="ParserTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.Runtime.CompilerServices;

/// <summary>
/// Unit tests for the <see cref="Parser"/> class.
/// </summary>
[TestClass]
public class ParserTests
{
    /// <summary>
    /// Tests parsing an empty program.
    /// </summary>
    [TestMethod]
    public void ParseEmptyProgramTest()
    {
        var log = new TestMessageLog();
        var parser = CreateParser(log, string.Empty);
        var program = parser.Parse();
        Assert.IsNull(program);
        Assert.HasCount(1, log.Messages);
        Assert.AreEqual(MessageSeverity.Error, log.Messages[0].Severity);
        Assert.AreEqual(MessageUtility.UnexpectedEndOfFileMessageId, log.Messages[0].Id);
    }

    /// <summary>
    /// Tests parsing an enum definition.
    /// </summary>
    [TestMethod]
    public void EnumDefinitionTest()
    {
        var log = new TestMessageLog();
        var parser = CreateParser(log, "enum Color { Red = 0, Green, Blue }");
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(0, log.Messages);
        var enumDef = program.ProgramElements[0] as EnumParseNode;
        Assert.IsNotNull(enumDef);
        Assert.AreEqual("Color", enumDef.Name);
        Assert.HasCount(3, enumDef.Members);
        Assert.AreEqual("Red", enumDef.Members[0].Name);
        Assert.AreEqual("Green", enumDef.Members[1].Name);
        Assert.AreEqual("Blue", enumDef.Members[2].Name);
        Assert.AreEqual(0, enumDef.Members[0].Value);
        Assert.IsNull(enumDef.Members[1].Value);
        Assert.IsNull(enumDef.Members[2].Value);
    }

    /// <summary>
    /// Parse a basic interface definition.
    /// </summary>
    [TestMethod]
    public void InterfaceDefinitionTest()
    {
        const string testCase = @"
        interface IIcon {
            function GetName();
            function GetSize();
            template Draw(x, y);
        }";
        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);
        var interfaceDef = program.ProgramElements[0] as InterfaceParseNode;
        Assert.IsNotNull(interfaceDef);
        Assert.HasCount(3, interfaceDef.Members);
        var getNameFunction = interfaceDef.Members[0] as FunctionDeclarationParseNode;
        Assert.IsNotNull(getNameFunction);
        Assert.HasCount(0, getNameFunction.Parameters);
        var getSizeFunction = interfaceDef.Members[1] as FunctionDeclarationParseNode;
        Assert.IsNotNull(getSizeFunction);
        Assert.HasCount(0, getSizeFunction.Parameters);
        var drawTemplate = interfaceDef.Members[2] as TemplateDeclarationParseNode;
        Assert.IsNotNull(drawTemplate);
        Assert.HasCount(2, drawTemplate.Parameters);
        Assert.AreEqual("x", drawTemplate.Parameters[0].Name);
        Assert.AreEqual("y", drawTemplate.Parameters[1].Name);
    }

    /// <summary>
    /// Parse a single-line function definition.
    /// </summary>
    [TestMethod]
    public void SingleLineFunctionTest()
    {
        const string testCase = @"
        function LengthSq(x, y) {
            return x * x + y * y;
        }";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);
        var functionDef = program.ProgramElements[0] as FunctionParseNode;
        Assert.IsNotNull(functionDef);
        Assert.AreEqual("LengthSq", functionDef.Name);
        Assert.HasCount(2, functionDef.Parameters);
        Assert.AreEqual("x", functionDef.Parameters[0].Name);
        Assert.AreEqual("y", functionDef.Parameters[1].Name);
        var body = functionDef.Body as BlockStatementParseNode;
        Assert.IsNotNull(body);
        Assert.HasCount(1, body.Statements);
        var returnStatement = body.Statements[0] as ReturnStatementParseNode;
        Assert.IsNotNull(returnStatement);
        var addExpression = returnStatement.Expression as AddExpressionParseNode;
        Assert.IsNotNull(addExpression);
        Assert.IsFalse(addExpression.IsSubtraction);
        var leftMul = addExpression.Left as MulExpressionParseNode;
        Assert.IsNotNull(leftMul);
        Assert.AreEqual(MulOperator.Multiply, leftMul.Operator);
        var xLeft = leftMul.Left as VariableReferenceParseNode;
        Assert.IsNotNull(xLeft);
        Assert.AreEqual("x", xLeft.Name);
        var xRight = leftMul.Right as VariableReferenceParseNode;
        Assert.IsNotNull(xRight);
        Assert.AreEqual("x", xRight.Name);
        var rightMul = addExpression.Right as MulExpressionParseNode;
        Assert.IsNotNull(rightMul);
        Assert.AreEqual(MulOperator.Multiply, rightMul.Operator);
        var yLeft = rightMul.Left as VariableReferenceParseNode;
        Assert.IsNotNull(yLeft);
        Assert.AreEqual("y", yLeft.Name);
        var yRight = rightMul.Right as VariableReferenceParseNode;
        Assert.IsNotNull(yRight);
        Assert.AreEqual("y", yRight.Name);
    }

    /// <summary>
    /// Tests parsing of a template with multiple statements.
    /// </summary>
    [TestMethod]
    public void TemplateTestMultipleStatements()
    {
        const string testCase = @"
        template Border(r, w) {
            debug rect(r);
            info rect(
                x = r.x - w,
                y = r.y - w,
                width = r.width + 2 * w,
                height = r.height + 2 * w);
        }";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var templateElement = program.ProgramElements[0] as TemplateParseNode;
        Assert.IsNotNull(templateElement);
        Assert.AreEqual("Border", templateElement.Name);
        Assert.HasCount(2, templateElement.Parameters);
        Assert.AreEqual("r", templateElement.Parameters[0].Name);
        Assert.AreEqual("w", templateElement.Parameters[1].Name);

        var body = templateElement.Body as BlockStatementParseNode;
        Assert.IsNotNull(body);
        Assert.HasCount(2, body.Statements);
        var debugStatement = body.Statements[0] as TraceStatementParseNode;
        Assert.IsNotNull(debugStatement);
        Assert.AreEqual(TraceStatementSeverity.Debug, debugStatement.Severity);
        var infoStatement = body.Statements[1] as TraceStatementParseNode;
        Assert.IsNotNull(infoStatement);
        Assert.AreEqual(TraceStatementSeverity.Info, infoStatement.Severity);
    }

    /// <summary>
    /// Tests a single statement that assigns a variable.
    /// </summary>
    [TestMethod]
    public void VariableAssignmentStatementTest()
    {
        const string testCase = @"
        x = 5;";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as VariableDefinitionParseNode;
        Assert.IsNotNull(statement);
        Assert.AreEqual("x", statement.Name);
        Assert.IsNull(statement.Type);
        var value = statement.Value as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(value);
        Assert.AreEqual(5, value.Value);
    }

    /// <summary>
    /// Tests a single statement that assigns a typed variable.
    /// </summary>
    [TestMethod]
    public void TypedVariableAssignmentStatementTest()
    {
        const string testCase = @"
            int x = 5;
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as VariableDefinitionParseNode;
        Assert.IsNotNull(statement);
        Assert.AreEqual("x", statement.Name);
        Assert.IsNotNull(statement.Type);
        Assert.AreEqual("int", statement.Type!.Names[0]);
        var value = statement.Value as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(value);
        Assert.AreEqual(5, value.Value);
    }

    /// <summary>
    /// Tests a single statement that calls a function.
    /// </summary>
    [TestMethod]
    public void CallStatementTest()
    {
        const string testCase = @"
        foo(42);";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as CallStatementParseNode;
        Assert.IsNotNull(statement);
        var target = statement.Target as VariableReferenceParseNode;
        Assert.AreEqual("foo", target!.Name);
        Assert.HasCount(1, statement.Arguments);
        var arg = statement.Arguments[0].Value as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(arg);
        Assert.AreEqual(42, arg.Value);
    }

    /// <summary>
    /// Tests a single statement that contains an array expression.
    /// </summary>
    [TestMethod]
    public void ArrayExpressionTest()
    {
        const string testCase = @"
            debug [1, 2, 3];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var array = statement.Expression as ArrayExpressionParseNode;
        Assert.IsNotNull(array);
        Assert.HasCount(1, array.Elements);
        Assert.HasCount(3, array.Elements[0]);
    }

    /// <summary>
    /// Tests a single statement that contains a multi-dimensional array expression.
    /// </summary>
    [TestMethod]
    public void MultiDimArrayTest()
    {
        const string testCase = @"
            debug [1, 2, 3;
                   4, 5, 6];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var array = statement.Expression as ArrayExpressionParseNode;
        Assert.IsNotNull(array);
        Assert.HasCount(2, array.Elements);
        Assert.HasCount(3, array.Elements[0]);
        Assert.HasCount(3, array.Elements[1]);
    }

    /// <summary>
    /// Tests a single statement that contains an empty array expression.
    /// </summary>
    [TestMethod]
    public void EmptyArrayTest()
    {
        const string testCase = @"
            debug [];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var array = statement.Expression as ArrayExpressionParseNode;
        Assert.IsNotNull(array);
        Assert.HasCount(0, array.Elements);
    }

    /// <summary>
    /// Tests a single statement that contains a jagged array expression.
    /// </summary>
    [TestMethod]
    public void JaggedArrayTest()
    {
        const string testCase = @"
            debug [[1, 2, 3], [4, 5]];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var array = statement.Expression as ArrayExpressionParseNode;
        Assert.IsNotNull(array);
        Assert.HasCount(1, array.Elements);
        Assert.HasCount(2, array.Elements[0]);
        var row1 = array.Elements[0][0] as ArrayExpressionParseNode;
        Assert.IsNotNull(row1);
        Assert.HasCount(1, row1.Elements);
        Assert.HasCount(3, row1.Elements[0]);

        var row2 = array.Elements[0][1] as ArrayExpressionParseNode;
        Assert.IsNotNull(row2);
        Assert.HasCount(1, row2.Elements);
        Assert.HasCount(2, row2.Elements[0]);
    }

    /// <summary>
    /// Tests a single statement that contains an index expression.
    /// </summary>
    [TestMethod]
    public void IndexExpressionTest()
    {
        const string testCase = @"
            debug a[0];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var indexExpression = statement.Expression as IndexExpressionParseNode;
        Assert.IsNotNull(indexExpression);
        var array = indexExpression.Target as VariableReferenceParseNode;
        Assert.IsNotNull(array);
        Assert.AreEqual("a", array.Name);
        Assert.HasCount(1, indexExpression.Indexes);
        var index = indexExpression.Indexes[0] as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(index);
        Assert.AreEqual(0, index.Value);
    }

    /// <summary>
    /// Tests a single statement that contains a multi-dimensional index expression.
    /// </summary>
    [TestMethod]
    public void MultiDimIndexExpressionTest()
    {
        const string testCase = @"
            debug a[0, 1];
        ";

        var log = new TestMessageLog();
        var parser = CreateParser(log, testCase);
        var program = parser.Parse();
        Assert.IsNotNull(program);
        Assert.HasCount(1, program.ProgramElements);

        var statement = program.ProgramElements[0] as TraceStatementParseNode;
        Assert.IsNotNull(statement);
        var indexExpression = statement.Expression as IndexExpressionParseNode;
        Assert.IsNotNull(indexExpression);
        var array = indexExpression.Target as VariableReferenceParseNode;
        Assert.IsNotNull(array);
        Assert.AreEqual("a", array.Name);
        Assert.HasCount(2, indexExpression.Indexes);
        var index0 = indexExpression.Indexes[0] as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(index0);
        Assert.AreEqual(0, index0.Value);
        var index1 = indexExpression.Indexes[1] as LiteralExpressionParseNode<long>;
        Assert.IsNotNull(index1);
        Assert.AreEqual(1, index1.Value);
    }

    private static Parser CreateParser(
        TestMessageLog log,
        string text,
        [CallerFilePath] string? callerFilePath = null,
        [CallerLineNumber] int callerLineNumber = 0)
    {
        var sourceRef = new SourceReference(callerFilePath!, callerLineNumber);
        var textReader = new StringReader(text);
        var tokenReader = new TokenReader(textReader, sourceRef, log.Log);
        return new Parser(log.Log, tokenReader);
    }
}