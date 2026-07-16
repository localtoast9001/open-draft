// <copyright file="Parser.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parser that takes a stream of tokens and produces a parse tree. The parser is responsible for handling the syntax of the language and reporting any errors that occur during parsing.
/// </summary>
public class Parser
{
    private readonly Action<Message> log;
    private readonly TokenReader tokenReader;
    private TokenWithComments? peekedToken;

    /// <summary>
    /// Initializes a new instance of the <see cref="Parser"/> class.
    /// </summary>
    /// <param name="log">The action to log messages.</param>
    /// <param name="tokenReader">The token reader to read tokens from.</param>
    /// <exception cref="ArgumentNullException">Thrown when <paramref name="log"/> or <paramref name="tokenReader"/> is <c>null</c>.</exception>
    public Parser(Action<Message> log, TokenReader tokenReader)
    {
        this.log = log ?? throw new ArgumentNullException(nameof(log));
        this.tokenReader = tokenReader ?? throw new ArgumentNullException(nameof(tokenReader));
    }

    /// <summary>
    /// Parses an OpenDraft language file and produces a parse tree. The parse tree is represented as a hierarchy of <see cref="ParseNode"/> objects. If any errors occur during parsing, they are logged using the provided <see cref="Action{Message}"/>.
    /// </summary>
    /// <returns>The root node of the parse tree, or <c>null</c> if parsing fails.</returns>
    public ProgramParseNode? Parse()
    {
        List<ImportParseNode> imports = new List<ImportParseNode>();
        List<ProgramElementParseNode> programElements = new List<ProgramElementParseNode>();
        var start = this.Peek();
        if (start == null)
        {
            this.log(MessageUtility.UnexpectedEndOfFile(
                this.tokenReader.CurrentSource));
            return null;
        }

        var token = start;
        while (token != null && Is(token, Keyword.Import))
        {
            var importNode = this.ParseImport();
            if (importNode == null)
            {
                return null;
            }

            imports.Add(importNode);

            token = this.Peek();
        }

        while (token != null)
        {
            var programElement = this.ParseProgramElement();
            if (programElement == null)
            {
                return null;
            }

            programElements.Add(programElement);

            token = this.Peek();
        }

        return new ProgramParseNode(
            imports,
            programElements,
            start.Token,
            start.PrecedingComments);
    }

    private static bool Is(TokenWithComments token, Keyword keyword)
    {
        return token.Token is KeywordToken keywordToken &&
            keywordToken.Value == keyword;
    }

    private static bool Is(TokenWithComments token, Symbol symbol)
    {
        return token.Token is SymbolToken symbolToken &&
            symbolToken.Value == symbol;
    }

    private ImportParseNode? ParseImport()
    {
        var token = this.Peek();
        if (!this.Expect(Keyword.Import))
        {
            return null;
        }

        var moduleNameToken = this.ExpectStringLiteral();
        if (moduleNameToken == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new ImportParseNode(
            moduleNameToken.Value,
            token!.Token,
            token!.PrecedingComments);
    }

    private ProgramElementParseNode? ParseProgramElement()
    {
        var token = this.Peek();
        if (token == null)
        {
            // The caller would have checked.
            return null;
        }

        if (Is(token, Keyword.Class))
        {
            return this.ParseClass();
        }
        else if (Is(token, Keyword.Interface))
        {
            return this.ParseInterface();
        }
        else if (Is(token, Keyword.Enum))
        {
            return this.ParseEnum();
        }
        else if (Is(token, Keyword.Function))
        {
            return this.ParseFunction();
        }
        else if (Is(token, Keyword.Template))
        {
            return this.ParseTemplate();
        }
        else
        {
            return this.ParseCoreStatement();
        }
    }

    private ClassParseNode? ParseClass()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Class))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var token = this.Peek();
        if (token != null && Is(token, Symbol.Colon))
        {
            this.Read();
            var baseType = this.ParseTypeReference();
            if (baseType == null)
            {
                return null;
            }
        }

        if (!this.Expect(Symbol.LeftBrace))
        {
            return null;
        }

        throw new NotImplementedException();
    }

    private InterfaceParseNode? ParseInterface()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Interface))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var token = this.Peek();
        if (token != null && Is(token, Symbol.Colon))
        {
            this.Read();
            var baseType = this.ParseTypeReference();
            if (baseType == null)
            {
                return null;
            }
        }

        if (!this.Expect(Symbol.LeftBrace))
        {
            return null;
        }

        List<InterfaceMemberParseNode> members = new List<InterfaceMemberParseNode>();
        var memberToken = this.Peek();
        while (memberToken != null && !Is(memberToken, Symbol.RightBrace))
        {
            var member = this.ParseInterfaceMember();
            if (member == null)
            {
                return null;
            }

            members.Add(member);

            memberToken = this.Peek();
        }

        if (!this.Expect(Symbol.RightBrace))
        {
            return null;
        }

        return new InterfaceParseNode(
            nameToken.Value,
            members,
            start!.Token,
            start!.PrecedingComments);
    }

    private InterfaceMemberParseNode? ParseInterfaceMember()
    {
        var token = this.Peek();
        if (token == null)
        {
            // The caller would have checked.
            return null;
        }

        if (Is(token, Keyword.Function))
        {
            return this.ParseInterfaceFunction();
        }
        else if (Is(token, Keyword.Template))
        {
            return this.ParseInterfaceTemplate();
        }
        else
        {
            this.log(MessageUtility.UnexpectedToken(
                token.Token,
                this.tokenReader.CurrentSource));
            return null;
        }
    }

    private FunctionDeclarationParseNode? ParseInterfaceFunction()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Function))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var parameters = this.ParseParameterDeclarations();
        if (parameters == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new FunctionDeclarationParseNode(
            nameToken.Value,
            parameters,
            start!.Token,
            start!.PrecedingComments);
    }

    private TemplateDeclarationParseNode? ParseInterfaceTemplate()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Template))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var parameters = this.ParseParameterDeclarations();
        if (parameters == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new TemplateDeclarationParseNode(
            nameToken.Value,
            parameters,
            start!.Token,
            start!.PrecedingComments);
    }

    private IEnumerable<ParameterDeclarationParseNode>? ParseParameterDeclarations()
    {
        List<ParameterDeclarationParseNode> parameters = new List<ParameterDeclarationParseNode>();
        if (!this.Expect(Symbol.LeftParen))
        {
            return null;
        }

        var token = this.Peek();
        if (token != null && !Is(token, Symbol.RightParen))
        {
            var parameter = this.ParseParameterDeclaration();
            if (parameter == null)
            {
                return null;
            }

            parameters.Add(parameter);
            token = this.Peek();
            while (token != null && Is(token, Symbol.Comma))
            {
                this.Read();
                parameter = this.ParseParameterDeclaration();
                if (parameter == null)
                {
                    return null;
                }

                parameters.Add(parameter);
                token = this.Peek();
            }
        }

        if (!this.Expect(Symbol.RightParen))
        {
            return null;
        }

        return parameters;
    }

    private ParameterDeclarationParseNode? ParseParameterDeclaration()
    {
        var start = this.Peek();
        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        TypeReferenceParseNode? type = null;
        var token = this.Peek();
        if (token != null && Is(token, Symbol.Colon))
        {
            this.Read();
            type = this.ParseTypeReference();
            if (type == null)
            {
                return null;
            }
        }

        ExpressionParseNode? defaultValue = null;
        token = this.Peek();
        if (token != null && Is(token, Symbol.Equals))
        {
            this.Read();
            defaultValue = this.ParseExpression();
            if (defaultValue == null)
            {
                return null;
            }
        }

        return new ParameterDeclarationParseNode(
            nameToken.Value,
            type,
            defaultValue,
            start!.Token,
            start!.PrecedingComments);
    }

    private EnumParseNode? ParseEnum()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Enum))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.LeftBrace))
        {
            return null;
        }

        List<EnumMemberParseNode> members = new List<EnumMemberParseNode>();
        var member = this.ParseEnumMember();
        if (member == null)
        {
            return null;
        }

        members.Add(member);

        var commaToken = this.Peek();
        while (commaToken != null && Is(commaToken, Symbol.Comma))
        {
            this.Read();
            member = this.ParseEnumMember();
            if (member == null)
            {
                return null;
            }

            members.Add(member);

            commaToken = this.Peek();
        }

        if (!this.Expect(Symbol.RightBrace))
        {
            return null;
        }

        return new EnumParseNode(
            nameToken.Value,
            members,
            start!.Token,
            start!.PrecedingComments);
    }

    private EnumMemberParseNode? ParseEnumMember()
    {
        var start = this.Peek();
        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        long? value = null;
        var token = this.Peek();
        if (token != null && Is(token, Symbol.Assignment))
        {
            this.Read();
            var valueToken = this.ExpectInteger();
            if (valueToken == null)
            {
                return null;
            }

            value = valueToken.IntegerValue;
        }

        return new EnumMemberParseNode(
            nameToken.Value,
            value,
            start!.Token,
            start!.PrecedingComments);
    }

    private FunctionParseNode? ParseFunction()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Function))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var parameters = this.ParseParameterDeclarations();
        if (parameters == null)
        {
            return null;
        }

        var body = this.ParseBlockStatement();
        if (body == null)
        {
            return null;
        }

        return new FunctionParseNode(
            nameToken.Value,
            parameters,
            body,
            start!.Token,
            start!.PrecedingComments);
    }

    private TemplateParseNode? ParseTemplate()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Template))
        {
            return null;
        }

        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        var parameters = this.ParseParameterDeclarations();
        if (parameters == null)
        {
            return null;
        }

        var body = this.ParseBlockStatement();
        if (body == null)
        {
            return null;
        }

        return new TemplateParseNode(
            nameToken.Value,
            parameters,
            body,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseCoreStatement()
    {
        var start = this.Peek();
        if (start == null)
        {
            this.log(MessageUtility.UnexpectedEndOfFile(this.tokenReader.CurrentSource));
            return null;
        }

        if (Is(start, Keyword.If))
        {
            return this.ParseIfStatement();
        }

        if (Is(start, Keyword.For))
        {
            return this.ParseForStatement();
        }

        if (Is(start, Keyword.Break))
        {
            return this.ParseBreakStatement();
        }

        if (Is(start, Keyword.Continue))
        {
            return this.ParseContinueStatement();
        }

        if (Is(start, Keyword.Return))
        {
            return this.ParseReturnStatement();
        }

        if (Is(start, Keyword.Throw))
        {
            return this.ParseThrowStatement();
        }

        if (Is(start, Keyword.Error) ||
            Is(start, Keyword.Warn) ||
            Is(start, Keyword.Info) ||
            Is(start, Keyword.Verbose) ||
            Is(start, Keyword.Debug))
        {
            return this.ParseTraceStatement();
        }

        var expr = this.ParseExpression();
        if (expr == null)
        {
            return null;
        }

        if (expr is CallExpressionParseNode callExpr)
        {
            if (!this.Expect(Symbol.Semicolon))
            {
                return null;
            }

            return CallStatementParseNode.FromCallExpression(callExpr);
        }

        if (expr is ReferenceExpressionParseNode refExpr)
        {
            var typeRef = refExpr.ToTypeReference();
            if (typeRef != null)
            {
                string varName = typeRef.Names[0];
                var token = this.Peek();
                if (token != null && token.Token is IdentifierToken varNameToken)
                {
                    varName = varNameToken.Value;
                    _ = this.Read();
                }
                else if (typeRef.Names.Count > 1)
                {
                    this.log(MessageUtility.VariableNameExpectedAfterType(
                        token?.Token, this.tokenReader.CurrentSource));
                    return null;
                }
                else
                {
                    typeRef = null;
                }

                if (!this.Expect(Symbol.Assignment))
                {
                    return null;
                }

                expr = this.ParseExpression();
                if (expr == null)
                {
                    return null;
                }

                if (!this.Expect(Symbol.Semicolon))
                {
                    return null;
                }

                return new VariableDefinitionParseNode(
                    varName,
                    typeRef,
                    expr,
                    start!.Token,
                    start!.PrecedingComments);
            }
        }

        this.log(MessageUtility.UnexpectedToken(start.Token, start.Token.Source));
        return null;
    }

    private BlockStatementParseNode? ParseBlockStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.LeftBrace))
        {
            return null;
        }

        List<StatementParseNode> statements = new List<StatementParseNode>();
        var token = this.Peek();
        while (token != null && !Is(token, Symbol.RightBrace))
        {
            if (Is(token, Symbol.Semicolon))
            {
                this.Read();
            }
            else
            {
                var statement = this.ParseStatement();
                if (statement == null)
                {
                    return null;
                }

                statements.Add(statement);
            }

            token = this.Peek();
        }

        if (!this.Expect(Symbol.RightBrace))
        {
            return null;
        }

        return new BlockStatementParseNode(
            statements,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseStatement()
    {
        var start = this.Peek();
        if (start != null && Is(start, Symbol.LeftBrace))
        {
            return this.ParseBlockStatement();
        }
        else
        {
            return this.ParseCoreStatement();
        }
    }

    private StatementParseNode? ParseBreakStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Break))
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new BreakStatementParseNode(
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseContinueStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Continue))
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new ContinueStatementParseNode(
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseReturnStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Return))
        {
            return null;
        }

        var expression = this.ParseExpression();
        if (expression == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new ReturnStatementParseNode(
            expression,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseIfStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.If))
        {
            return null;
        }

        if (!this.Expect(Symbol.LeftParen))
        {
            return null;
        }

        var condition = this.ParseExpression();
        if (condition == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.RightParen))
        {
            return null;
        }

        var thenStatement = this.ParseStatement();
        if (thenStatement == null)
        {
            return null;
        }

        StatementParseNode? elseStatement = null;
        var next = this.Peek();
        if (next != null && Is(next, Keyword.Else))
        {
            this.Read();
            elseStatement = this.ParseStatement();
            if (elseStatement == null)
            {
                return null;
            }
        }

        return new IfStatementParseNode(
            condition,
            thenStatement,
            elseStatement,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseForStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.For))
        {
            return null;
        }

        if (!this.Expect(Symbol.LeftParen))
        {
            return null;
        }

        List<ForConditionParseNode> conditions = new List<ForConditionParseNode>();
        var condition = this.ParseForCondition();
        if (condition == null)
        {
            return null;
        }

        conditions.Add(condition);

        var token = this.Peek();
        while (token != null && Is(token, Symbol.Semicolon))
        {
            _ = this.Read();
            condition = this.ParseForCondition();
            if (condition == null)
            {
                return null;
            }

            conditions.Add(condition);
            token = this.Peek();
        }

        if (!this.Expect(Symbol.RightParen))
        {
            return null;
        }

        var body = this.ParseStatement();
        if (body == null)
        {
            return null;
        }

        return new ForStatementParseNode(
            conditions,
            body,
            start!.Token,
            start!.PrecedingComments);
    }

    private ForConditionParseNode? ParseForCondition()
    {
        var start = this.Peek();

        var typeReference = this.ParseTypeReference();
        if (typeReference == null)
        {
            return null;
        }

        var token = this.Peek();
        List<string> varNames = new List<string>();
        if (token != null && token.Token is IdentifierToken identifierToken)
        {
            varNames.Add(identifierToken.Value);
            _ = this.Read();
            token = this.Peek();
        }
        else
        {
            if (typeReference.Names.Count != 1)
            {
                // TODO: error. - Missing variable name.
                return null;
            }

            varNames.Add(typeReference.Names[0]);
            typeReference = null;
        }

        while (token != null && Is(token, Symbol.Comma))
        {
            _ = this.Read();
            var nextVarNameToken = this.ExpectIdentifier();
            if (nextVarNameToken == null)
            {
                return null;
            }

            varNames.Add(nextVarNameToken.Value);
            token = this.Peek();
        }

        if (!this.Expect(Symbol.Colon))
        {
            return null;
        }

        var expr = this.ParseExpression();
        if (expr == null)
        {
            return null;
        }

        return new ForConditionParseNode(
            varNames,
            expr,
            typeReference,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseThrowStatement()
    {
        var start = this.Peek();
        if (!this.Expect(Keyword.Throw))
        {
            return null;
        }

        var expression = this.ParseExpression();
        if (expression == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new ThrowStatementParseNode(
            expression,
            start!.Token,
            start!.PrecedingComments);
    }

    private StatementParseNode? ParseTraceStatement()
    {
        var start = this.Peek();
        if (start == null)
        {
            return null;
        }

        KeywordToken keywordToken = (KeywordToken)start.Token;
        TraceStatementSeverity severity = keywordToken.Value switch
        {
            Keyword.Error => TraceStatementSeverity.Error,
            Keyword.Warn => TraceStatementSeverity.Warn,
            Keyword.Info => TraceStatementSeverity.Info,
            Keyword.Verbose => TraceStatementSeverity.Verbose,
            Keyword.Debug => TraceStatementSeverity.Debug,
            _ => throw new InvalidOperationException("Internal Error: Invalid trace keyword."),
        };

        // Read the trace keyword (Error, Warn, Info, Verbose, Debug)
        this.Read();

        var expression = this.ParseExpression();
        if (expression == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Semicolon))
        {
            return null;
        }

        return new TraceStatementParseNode(
            severity,
            expression,
            start.Token,
            start.PrecedingComments);
    }

    private TypeReferenceParseNode? ParseTypeReference()
    {
        var nameList = new List<string>();
        var start = this.Peek();
        var nameToken = this.ExpectIdentifier();
        if (nameToken == null)
        {
            return null;
        }

        nameList.Add(nameToken.Value);
        var token = this.Peek();
        while (token != null && Is(token, Symbol.Dot))
        {
            this.Read();
            nameToken = this.ExpectIdentifier();
            if (nameToken == null)
            {
                return null;
            }

            nameList.Add(nameToken.Value);
            token = this.Peek();
        }

        return new TypeReferenceParseNode(
            nameList,
            start!.Token,
            start!.PrecedingComments);
    }

    private bool Expect(Keyword keyword)
    {
        var token = this.Read();
        if (token == null || !Is(token, keyword))
        {
            this.log(MessageUtility.KeywordExpected(
                token?.Token,
                this.tokenReader.CurrentSource,
                keyword));
            return false;
        }

        return true;
    }

    private ExpressionParseNode? ParseExpression()
    {
        var inner = this.ParseLogicalOrExpression();
        if (inner == null)
        {
            return null;
        }

        var token = this.Peek();
        if (token != null && Is(token, Symbol.Question))
        {
            this.Read();
            var trueExpression = this.ParseExpression();
            if (trueExpression == null)
            {
                return null;
            }

            if (!this.Expect(Symbol.Colon))
            {
                return null;
            }

            var falseExpression = this.ParseExpression();
            if (falseExpression == null)
            {
                return null;
            }

            return new ConditionalExpressionParseNode(
                inner!,
                trueExpression,
                falseExpression,
                inner!.Start,
                inner.PrecedingComments);
        }

        return inner;
    }

    private ExpressionParseNode? ParseLogicalOrExpression()
    {
        var term = this.ParseLogicalAndExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null && Is(token, Symbol.DoublePipe))
        {
            this.Read();
            var nextTerm = this.ParseLogicalAndExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new LogicalOrExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseLogicalAndExpression()
    {
        var term = this.ParseBitwiseOrExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null && Is(token, Symbol.DoubleAmpersand))
        {
            this.Read();
            var nextTerm = this.ParseBitwiseOrExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new LogicalAndExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseBitwiseOrExpression()
    {
        var term = this.ParseBitwiseXorExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null && Is(token, Symbol.Pipe))
        {
            this.Read();
            var nextTerm = this.ParseBitwiseXorExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new BitwiseOrExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseBitwiseXorExpression()
    {
        var term = this.ParseBitwiseAndExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null && Is(token, Symbol.Caret))
        {
            this.Read();
            var nextTerm = this.ParseBitwiseAndExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new BitwiseXorExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseBitwiseAndExpression()
    {
        var term = this.ParseEqualityExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null && Is(token, Symbol.Ampersand))
        {
            this.Read();
            var nextTerm = this.ParseEqualityExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new BitwiseAndExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseEqualityExpression()
    {
        var term = this.ParseRelationalExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.Equals) ||
            Is(token, Symbol.NotEquals)))
        {
            var symbolToken = (SymbolToken)token.Token;
            this.Read();
            var nextTerm = this.ParseRelationalExpression();
            if (nextTerm == null)
            {
                return null;
            }

            var isInequality = symbolToken.Value == Symbol.NotEquals;
            term = new EqualityExpressionParseNode(
                term,
                nextTerm,
                isInequality,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseRelationalExpression()
    {
        var term = this.ParseShiftExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.LessThan) ||
            Is(token, Symbol.LessThanOrEqual) ||
            Is(token, Symbol.GreaterThan) ||
            Is(token, Symbol.GreaterThanOrEqual) ||
            Is(token, Keyword.In)))
        {
            this.Read();
            var op = RelationalOperator.InSet;
            if (!Is(token, Keyword.In))
            {
                var symbolToken = (SymbolToken)token.Token;
                op = symbolToken.Value switch
                {
                    Symbol.LessThan => RelationalOperator.LessThan,
                    Symbol.LessThanOrEqual => RelationalOperator.LessThanOrEqual,
                    Symbol.GreaterThan => RelationalOperator.GreaterThan,
                    _ => RelationalOperator.GreaterThanOrEqual,
                };
            }

            var nextTerm = this.ParseShiftExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new RelationalExpressionParseNode(
                term,
                nextTerm,
                op,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseShiftExpression()
    {
        var term = this.ParseAddExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.DoubleLessThan) ||
            Is(token, Symbol.DoubleGreaterThan)))
        {
            var symbolToken = (SymbolToken)token.Token;
            this.Read();
            var nextTerm = this.ParseAddExpression();
            if (nextTerm == null)
            {
                return null;
            }

            var op = symbolToken.Value == Symbol.DoubleLessThan
                ? ShiftOperator.LeftShift
                : ShiftOperator.RightShift;

            term = new ShiftExpressionParseNode(
                term,
                nextTerm,
                op,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseAddExpression()
    {
        var term = this.ParseMultiplyExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.Plus) ||
            Is(token, Symbol.Minus)))
        {
            var symbolToken = (SymbolToken)token.Token;
            this.Read();
            var nextTerm = this.ParseMultiplyExpression();
            if (nextTerm == null)
            {
                return null;
            }

            var isMinus = symbolToken.Value == Symbol.Minus;

            term = new AddExpressionParseNode(
                term,
                nextTerm,
                isMinus,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseMultiplyExpression()
    {
        var term = this.ParseRangeExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.Asterisk) ||
            Is(token, Symbol.Slash) ||
            Is(token, Symbol.Modulus)))
        {
            var symbolToken = (SymbolToken)token.Token;
            this.Read();
            var nextTerm = this.ParseRangeExpression();
            if (nextTerm == null)
            {
                return null;
            }

            var op = symbolToken.Value == Symbol.Asterisk
                ? MulOperator.Multiply
                : symbolToken.Value == Symbol.Slash
                    ? MulOperator.Divide
                    : MulOperator.Modulo;

            term = new MulExpressionParseNode(
                term,
                nextTerm,
                op,
                term.Start,
                term.PrecedingComments);
            token = this.Peek();
        }

        return term;
    }

    private ExpressionParseNode? ParseRangeExpression()
    {
        var term = this.ParseUnaryExpression();
        if (term == null)
        {
            return null;
        }

        var token = this.Peek();
        if (token != null && Is(token, Symbol.Range))
        {
            this.Read();
            var nextTerm = this.ParseUnaryExpression();
            if (nextTerm == null)
            {
                return null;
            }

            term = new RangeExpressionParseNode(
                term,
                nextTerm,
                term.Start,
                term.PrecedingComments);
        }

        return term;
    }

    private ExpressionParseNode? ParseUnaryExpression()
    {
        var token = this.Peek();
        if (token == null)
        {
            return null;
        }

        // Handle unary operators here (e.g., +, -, !, ~)
        if (Is(token, Symbol.Plus) ||
            Is(token, Symbol.Minus) ||
            Is(token, Symbol.Bang) ||
            Is(token, Symbol.Tilde))
        {
            var symbolToken = (SymbolToken)token.Token;
            this.Read();
            UnaryOperator? op = symbolToken.Value switch
            {
                Symbol.Minus => UnaryOperator.Negate,
                Symbol.Bang => UnaryOperator.LogicalNot,
                Symbol.Tilde => UnaryOperator.BitwiseNot,
                _ => null,
            };

            var operand = this.ParseUnaryExpression();
            if (operand == null)
            {
                return null;
            }

            if (op == null)
            {
                return operand;
            }

            return new UnaryExpressionParseNode(
                operand,
                op.Value,
                token.Token,
                token.PrecedingComments);
        }

        if (Is(token, Symbol.LeftParen))
        {
            _ = this.Read();
            var inner = this.ParseExpression();
            if (!this.Expect(Symbol.RightParen))
            {
                return null;
            }

            return inner;
        }

        if (Is(token, Symbol.LeftBracket))
        {
            return this.ParseArrayExpression();
        }

        if (Is(token, Symbol.LeftBrace))
        {
            return this.ParseObjectExpression();
        }

        if (Is(token, Keyword.True))
        {
            _ = this.Read();
            return new LiteralExpressionParseNode<bool>(
                true,
                token.Token,
                token.PrecedingComments);
        }

        if (Is(token, Keyword.False))
        {
            _ = this.Read();
            return new LiteralExpressionParseNode<bool>(
                false,
                token.Token,
                token.PrecedingComments);
        }

        if (Is(token, Keyword.Null))
        {
            _ = this.Read();
            return new NullExpressionParseNode(token.Token, token.PrecedingComments);
        }

        if (token.Token is StringLiteralToken stringLiteralToken)
        {
            _ = this.Read();
            return new LiteralExpressionParseNode<string>(
                stringLiteralToken.Value,
                token.Token,
                token.PrecedingComments);
        }

        if (token.Token is NumericLiteralToken numericLiteralToken)
        {
            _ = this.Read();
            if (numericLiteralToken.IsFloatingPoint)
            {
                return new LiteralExpressionParseNode<decimal>(
                    numericLiteralToken.FloatingPointValue,
                    token.Token,
                    token.PrecedingComments);
            }

            return new LiteralExpressionParseNode<long>(
                numericLiteralToken.IntegerValue,
                token.Token,
                token.PrecedingComments);
        }

        return this.ParseReferenceExpression();
    }

    private ExpressionParseNode? ParseArrayExpression()
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.LeftBracket))
        {
            return null;
        }

        var elements = new List<List<ExpressionParseNode>>();
        var token = this.Peek();
        while (token != null && !Is(token, Symbol.RightBracket))
        {
            var row = this.ParseArrayRow();
            if (row == null)
            {
                return null;
            }

            elements.Add(row.ToList());

            token = this.Peek();
            if (token != null && Is(token, Symbol.Semicolon))
            {
                _ = this.Read();
                token = this.Peek();
            }
            else
            {
                break;
            }
        }

        if (!this.Expect(Symbol.RightBracket))
        {
            return null;
        }

        return new ArrayExpressionParseNode(
            elements,
            start!.Token,
            start.PrecedingComments);
    }

    private IEnumerable<ExpressionParseNode>? ParseArrayRow()
    {
        var elements = new List<ExpressionParseNode>();
        var token = this.Peek();
        while (token != null &&
            !Is(token, Symbol.RightBracket) &&
            !Is(token, Symbol.Semicolon))
        {
            var element = this.ParseExpression();
            if (element == null)
            {
                return null;
            }

            elements.Add(element);

            token = this.Peek();
            if (token != null && Is(token, Symbol.Comma))
            {
                _ = this.Read();
                token = this.Peek();
            }
            else
            {
                break;
            }
        }

        return elements;
    }

    private ExpressionParseNode? ParseObjectExpression()
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.LeftBrace))
        {
            return null;
        }

        var members = new List<ObjectMemberParseNode>();
        var token = this.Peek();
        while (token != null && !Is(token, Symbol.RightBrace))
        {
            var member = this.ParseObjectMember();
            if (member == null)
            {
                return null;
            }

            members.Add(member);

            token = this.Peek();
            if (token != null && Is(token, Symbol.Comma))
            {
                _ = this.Read();
                token = this.Peek();
            }
            else
            {
                break;
            }
        }

        if (!this.Expect(Symbol.RightBrace))
        {
            return null;
        }

        return new ObjectExpressionParseNode(
            members,
            start!.Token,
            start.PrecedingComments);
    }

    private ObjectMemberParseNode? ParseObjectMember()
    {
        var start = this.Peek();
        IdentifierToken? identifier = this.ExpectIdentifier();
        if (identifier == null)
        {
            return null;
        }

        if (!this.Expect(Symbol.Assignment))
        {
            return null;
        }

        var value = this.ParseExpression();
        if (value == null)
        {
            return null;
        }

        return new ObjectMemberParseNode(
            identifier.Value,
            value,
            start!.Token,
            start.PrecedingComments);
    }

    private ExpressionParseNode? ParseReferenceExpression()
    {
        var start = this.Peek();
        IdentifierToken? identifier = this.ExpectIdentifier();
        if (identifier == null)
        {
            return null;
        }

        ReferenceExpressionParseNode result = new VariableReferenceParseNode(
            identifier.Value,
            start!.Token,
            start.PrecedingComments);

        var token = this.Peek();
        while (token != null &&
            (Is(token, Symbol.Dot) ||
            Is(token, Symbol.LeftBracket) ||
            Is(token, Symbol.LeftParen)))
        {
            Symbol symbol = ((SymbolToken)token.Token).Value;
            switch (symbol)
            {
                case Symbol.Dot:
                    {
                        var member = this.ParseMemberReference(result);
                        if (member == null)
                        {
                            return null;
                        }

                        result = member;
                    }

                    break;
                case Symbol.LeftBracket:
                    {
                        var index = this.ParseIndexExpression(result);
                        if (index == null)
                        {
                            return null;
                        }

                        result = index;
                    }

                    break;
                case Symbol.LeftParen:
                    {
                        var call = this.ParseCallExpression(result);
                        if (call == null)
                        {
                            return null;
                        }

                        result = call;
                    }

                    break;
            }

            token = this.Peek();
        }

        return result;
    }

    private ReferenceExpressionParseNode? ParseMemberReference(
        ReferenceExpressionParseNode target)
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.Dot))
        {
            return null;
        }

        var memberName = this.ExpectIdentifier();
        if (memberName == null)
        {
            return null;
        }

        return new MemberReferenceExpressionParseNode(
            target,
            memberName.Value,
            start!.Token,
            start.PrecedingComments);
    }

    private ReferenceExpressionParseNode? ParseIndexExpression(
        ReferenceExpressionParseNode target)
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.LeftBracket))
        {
            return null;
        }

        var indexes = new List<ExpressionParseNode>();
        var index = this.ParseExpression();
        if (index == null)
        {
            return null;
        }

        indexes.Add(index);
        var token = this.Peek();
        while (token != null && Is(token, Symbol.Comma))
        {
            _ = this.Read();
            var nextIndex = this.ParseExpression();
            if (nextIndex == null)
            {
                return null;
            }

            indexes.Add(nextIndex);
            token = this.Peek();
        }

        if (!this.Expect(Symbol.RightBracket))
        {
            return null;
        }

        return new IndexExpressionParseNode(
            target,
            indexes,
            start!.Token,
            start.PrecedingComments);
    }

    private ReferenceExpressionParseNode? ParseCallExpression(
        ReferenceExpressionParseNode target)
    {
        var start = this.Peek();
        if (!this.Expect(Symbol.LeftParen))
        {
            return null;
        }

        var arguments = new List<ArgumentParseNode>();
        var token = this.Peek();
        while (token != null && !Is(token, Symbol.RightParen))
        {
            var argument = this.ParseArgument();
            if (argument == null)
            {
                return null;
            }

            arguments.Add(argument);

            token = this.Peek();
            if (token != null && Is(token, Symbol.Comma))
            {
                this.Read();
                token = this.Peek();
            }
            else
            {
                break;
            }
        }

        if (!this.Expect(Symbol.RightParen))
        {
            return null;
        }

        return new CallExpressionParseNode(
            target,
            arguments,
            start!.Token,
            start.PrecedingComments);
    }

    private ArgumentParseNode? ParseArgument()
    {
        var start = this.Peek();
        var expr = this.ParseExpression();
        if (expr == null)
        {
            return null;
        }

        string? name = null;
        if (expr is VariableReferenceParseNode variableReference)
        {
            var token = this.Peek();
            if (token != null && Is(token, Symbol.Assignment))
            {
                _ = this.Read();
                expr = this.ParseExpression();
                if (expr == null)
                {
                    return null;
                }

                name = variableReference.Name;
            }
        }

        return new ArgumentParseNode(
            name,
            expr,
            start!.Token,
            start.PrecedingComments);
    }

    /// <summary>
    /// Creates a message for a symbol expected error.
    /// </summary>
    /// <param name="symbol">The expected symbol.</param>
    /// <returns>True if the expected symbol is found; otherwise, false.</returns>
    private bool Expect(Symbol symbol)
    {
        var token = this.Read();
        if (token == null || !Is(token, symbol))
        {
            this.log(MessageUtility.SymbolExpected(
                token?.Token,
                this.tokenReader.CurrentSource,
                symbol));
            return false;
        }

        return true;
    }

    private StringLiteralToken? ExpectStringLiteral()
    {
        var token = this.Read();
        if (token == null || token.Token is not StringLiteralToken stringLiteralToken)
        {
            this.log(MessageUtility.StringLiteralExpected(
                token?.Token,
                this.tokenReader.CurrentSource));
            return null;
        }

        return stringLiteralToken;
    }

    private IdentifierToken? ExpectIdentifier()
    {
        var token = this.Read();
        if (token == null || token.Token is not IdentifierToken identifierToken)
        {
            this.log(MessageUtility.IdentifierExpected(
                token?.Token,
                this.tokenReader.CurrentSource));
            return null;
        }

        return identifierToken;
    }

    private NumericLiteralToken? ExpectInteger()
    {
        var token = this.Read();
        if (token == null ||
            token.Token is not NumericLiteralToken integerLiteralToken ||
            integerLiteralToken.IsFloatingPoint)
        {
            this.log(MessageUtility.IntegerLiteralExpected(
                token?.Token,
                this.tokenReader.CurrentSource));
            return null;
        }

        return integerLiteralToken;
    }

    private TokenWithComments? Peek()
    {
        if (this.peekedToken == null)
        {
            this.peekedToken = this.InnerRead();
        }

        return this.peekedToken;
    }

    private TokenWithComments? Read()
    {
        var result = this.Peek();
        this.peekedToken = null;
        return result;
    }

    private TokenWithComments? InnerRead()
    {
        List<CommentToken> precedingComments = new List<CommentToken>();
        var token = this.tokenReader.Read();
        while (token is CommentToken commentToken)
        {
            precedingComments.Add(commentToken);
            token = this.tokenReader.Read();
        }

        if (token == null)
        {
            return null;
        }

        return new TokenWithComments(token, precedingComments);
    }

    private class TokenWithComments
    {
        public TokenWithComments(Token token, List<CommentToken> precedingComments)
        {
            this.Token = token;
            this.PrecedingComments = precedingComments;
        }

        public Token Token { get; }

        public List<CommentToken> PrecedingComments { get; }
    }
}