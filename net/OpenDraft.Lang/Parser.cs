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
    public ParseNode? Parse()
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

        if (!this.Expect(Symbol.LeftParen))
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
        if (token != null && Is(token, Symbol.Equals))
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
        throw new NotImplementedException();
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
        throw new NotImplementedException();
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