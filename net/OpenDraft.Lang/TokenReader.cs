// <copyright file="TokenReader.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

using System.Text;

/// <summary>
/// Reads tokens from a text input text stream.
/// </summary>
public class TokenReader : IDisposable
{
    private readonly TextReader inner;
    private readonly Action<Message> log;
    private readonly SourceReference startSource;
    private bool disposed;
    private int line;
    private int column;
    private Token? peekedToken;

    /// <summary>
    /// Initializes a new instance of the <see cref="TokenReader"/> class.
    /// </summary>
    /// <param name="inner">The text reader to read from.</param>
    /// <param name="startSource">The starting source reference.</param>
    /// <param name="log">The action to log messages.</param>
    /// <exception cref="ArgumentNullException">
    /// Thrown if any of the parameters are <c>null</c>.
    /// </exception>
    public TokenReader(
        TextReader inner,
        SourceReference startSource,
        Action<Message> log)
    {
        this.inner = inner ?? throw new ArgumentNullException(nameof(inner));
        this.startSource = startSource ?? throw new ArgumentNullException(nameof(startSource));
        this.log = log ?? throw new ArgumentNullException(nameof(log));
        this.line = startSource.LineNumber > 0 ? startSource.LineNumber : 1;
        this.column = startSource.ColumnNumber > 0 ? startSource.ColumnNumber : 1;
    }

    /// <summary>
    /// Gets the current source reference for the next token to be read.
    /// </summary>
    public SourceReference CurrentSource =>
        new SourceReference(this.startSource.Path, this.line, this.column);

    /// <inheritdoc/>
    public void Dispose()
    {
        if (!this.disposed)
        {
            this.inner.Dispose();
            this.disposed = true;
        }
    }

    /// <summary>
    /// Peeks at the next token without consuming it.
    /// </summary>
    /// <returns>The next token, or <c>null</c> if there are no more tokens or a terminating error was encountered.</returns>
    public Token? Peek()
    {
        if (this.peekedToken == null)
        {
            this.peekedToken = this.InnerRead();
        }

        return this.peekedToken;
    }

    /// <summary>
    /// Reads the next token from the input.
    /// </summary>
    /// <returns>The next token, or <c>null</c> if there are no more tokens or a terminating error was encountered.</returns>
    public Token? Read()
    {
        var token = this.Peek();
        this.peekedToken = null;
        return token;
    }

    private static bool IsDigit(int ch) =>
        ch >= '0' && ch <= '9';

    private static bool IsLetter(int ch) =>
        (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');

    private static int GetDigit(int ch, int radix)
    {
        if (radix <= 10)
        {
            if (ch >= '0' && ch < '0' + radix)
            {
                return ch - '0';
            }
            else
            {
                return -1;
            }
        }

        if (radix == 16)
        {
            if (IsDigit(ch))
            {
                return ch - '0';
            }
            else if (ch >= 'a' && ch <= 'f')
            {
                return ch - 'a' + 10;
            }
            else if (ch >= 'A' && ch <= 'F')
            {
                return ch - 'A' + 10;
            }
        }

        return -1;
    }

    private static int GetRadix(int ch)
    {
        switch (ch)
        {
            case 'x':
            case 'X':
                return 16;
            case 'o':
            case 'O':
                return 8;
            case 'b':
            case 'B':
                return 2;
            default:
                return 10;
        }
    }

    private static bool IsIdentifierStart(int ch) =>
        IsLetter(ch) || ch == '_';

    private static bool IsIdentifierPart(int ch) =>
        IsIdentifierStart(ch) || IsDigit(ch);

    private static bool IsUnitStart(int ch) =>
        IsIdentifierStart(ch) ||
        ch == '\'' || ch == '"' || ch == '°' || ch == '㎭';

    private static bool IsUnitPart(int ch) =>
        IsIdentifierPart(ch);

    private Token? InnerRead()
    {
        this.SkipWhitespace();
        var startSourceRef = this.CurrentSource;
        int lineStart = this.line;
        int columnStart = this.column;
        int ch = this.PeekChar();
        if (ch == -1)
        {
            return null;
        }

        if (IsIdentifierStart(ch))
        {
            return this.ReadIdentifierOrKeyword();
        }
        else if (IsDigit(ch))
        {
            return this.ReadNumericLiteral();
        }
        else if (ch == '"')
        {
            return this.ReadStringLiteral();
        }
        else if (ch == '/')
        {
            _ = this.ReadChar();
            ch = this.PeekChar();
            switch (ch)
            {
                case '/':
                    return this.ReadSingleLineComment(lineStart, columnStart);
                case '*':
                    return this.ReadBlockComment(lineStart, columnStart);
                default:
                    return new SymbolToken(
                        new SourceReference(
                            this.startSource.Path,
                            lineStart,
                            columnStart,
                            this.line,
                            this.column),
                        Symbol.Slash);
            }
        }
        else if (ch == '.')
        {
            _ = this.ReadChar();
            ch = this.PeekChar();
            if (char.IsDigit((char)ch))
            {
                return this.ReadDecimalLiteral(
                    startSourceRef,
                    intPart: 0);
            }
            else if (ch == '.')
            {
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.Range);
            }
            else
            {
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.Dot);
            }
        }

        return this.ReadSymbol();
    }

    private Token? ReadSymbol()
    {
        var startSourceRef = this.CurrentSource;
        var ch = this.PeekChar();

        switch (ch)
        {
            case '(':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.LeftParen);
            case ')':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.RightParen);
            case '[':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.LeftBracket);
            case ']':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.RightBracket);
            case ';':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Semicolon);
            case ',':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Comma);
            case '+':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Plus);
            case '-':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Minus);
            case '*':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Asterisk);
            case '{':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.LeftBrace);
            case '}':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.RightBrace);
            case '^':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Caret);
            case '%':
                _ = this.ReadChar();
                return new SymbolToken(
                    startSourceRef,
                    Symbol.Modulus);
            case '!':
                {
                    _ = this.ReadChar();
                    ch = this.PeekChar();
                    if (ch == '=')
                    {
                        _ = this.ReadChar();
                        return new SymbolToken(
                            startSourceRef,
                            Symbol.NotEquals);
                    }

                    return new SymbolToken(
                        startSourceRef,
                        Symbol.Bang);
                }

            case '=':
                {
                    _ = this.ReadChar();
                    ch = this.PeekChar();
                    if (ch == '=')
                    {
                        _ = this.ReadChar();
                        return new SymbolToken(
                            startSourceRef,
                            Symbol.Equals);
                    }

                    return new SymbolToken(
                        startSourceRef,
                        Symbol.Assignment);
                }

            case '<':
                {
                    _ = this.ReadChar();
                    ch = this.PeekChar();
                    if (ch == '=')
                    {
                        _ = this.ReadChar();
                        return new SymbolToken(
                            startSourceRef,
                            Symbol.LessThanOrEqual);
                    }

                    return new SymbolToken(
                        startSourceRef,
                        Symbol.LessThan);
                }

            case '>':
                {
                    _ = this.ReadChar();
                    ch = this.PeekChar();
                    if (ch == '=')
                    {
                        _ = this.ReadChar();
                        return new SymbolToken(
                            startSourceRef,
                            Symbol.GreaterThanOrEqual);
                    }

                    return new SymbolToken(
                        startSourceRef,
                        Symbol.GreaterThan);
                }

            case '?':
                {
                    _ = this.ReadChar();
                    ch = this.PeekChar();
                    if (ch == '?')
                    {
                        _ = this.ReadChar();
                        return new SymbolToken(
                            startSourceRef,
                            Symbol.DoubleQuestion);
                    }

                    return new SymbolToken(
                        startSourceRef,
                        Symbol.Question);
                }

            default:
                break;
        }

        this.log(MessageUtility.InvalidCharacter(this.CurrentSource, (char)ch));
        return null;
    }

    /// <summary>
    /// Reads an identifier or keyword token from the input.
    /// </summary>
    /// <returns>The read identifier or keyword token.</returns>
    private Token ReadIdentifierOrKeyword()
    {
        StringBuilder sb = new StringBuilder();
        int lineStart = this.line;
        int columnStart = this.column;
        int ch = this.PeekChar();
        while (ch > 0 && IsIdentifierPart(ch))
        {
            _ = this.ReadChar();
            sb.Append((char)ch);
            ch = this.PeekChar();
        }

        string value = sb.ToString();
        var source = this.GetTokenSource(lineStart, columnStart);
        var keyword = KeywordUtility.GetKeyword(value);
        if (keyword != Keyword.None)
        {
            return new KeywordToken(source, keyword);
        }
        else
        {
            return new IdentifierToken(source, value);
        }
    }

    private Token? ReadNumericLiteral()
    {
        var startSource = this.CurrentSource;
        long intPart = 0;
        int ch = this.PeekChar();
        int radix = 10;
        if (ch == '0')
        {
            _ = this.ReadChar();
            ch = this.PeekChar();
            radix = GetRadix(ch);
            if (radix != 10)
            {
                _ = this.ReadChar();
                ch = this.PeekChar();
                if (GetDigit(ch, radix) < 0)
                {
                    this.log(MessageUtility.InvalidNumberAfterRadixSpecifier(this.CurrentSource));
                    return null;
                }
            }
        }

        int digit = GetDigit(ch, radix);
        while (digit >= 0)
        {
            _ = this.ReadChar();
            intPart = (intPart * radix) + digit;
            ch = this.PeekChar();
            digit = GetDigit(ch, radix);
        }

        int exponent = 0;
        bool hasExponent = false;
        if (radix == 10)
        {
            if (ch == '.')
            {
                _ = this.ReadChar();
                return this.ReadDecimalLiteral(startSource, intPart);
            }

            if (ch == 'e' || ch == 'E')
            {
                _ = this.ReadChar();
                hasExponent = true;
                if (!this.TryReadExponentPart(out exponent))
                {
                    return null; // Error message already logged.
                }
            }
        }

        string? unit = null;
        ch = this.PeekChar();
        if (IsUnitStart(ch))
        {
            unit = this.ReadUnit();
            if (unit == null)
            {
                return null; // Error message already logged.
            }
        }

        if (hasExponent)
        {
            decimal result = intPart * (decimal)Math.Pow(10, exponent);
            var source = new SourceReference(
                this.startSource.Path,
                startSource.LineNumber,
                startSource.ColumnNumber,
                this.line,
                this.column);
            return new NumericLiteralToken(
                source,
                result,
                unit);
        }
        else
        {
            var source = new SourceReference(
                this.startSource.Path,
                startSource.LineNumber,
                startSource.ColumnNumber,
                this.line,
                this.column);
            return new NumericLiteralToken(
                source,
                intPart,
                unit);
        }
    }

    private string? ReadUnit()
    {
        StringBuilder sb = new StringBuilder();
        int ch = this.ReadChar();
        sb.Append((char)ch);
        ch = this.PeekChar();
        while (IsUnitPart(ch))
        {
            _ = this.ReadChar();
            sb.Append((char)ch);
            ch = this.PeekChar();
        }

        // The 1st underscore is a delimiter and is removed from the result.
        if (sb[0] == '_')
        {
            sb.Remove(0, 1);
        }

        if (sb.Length == 0)
        {
            this.log(MessageUtility.InvalidUnitSpecifier(this.GetTokenSource(), sb.ToString()));
            return null; // error.
        }

        return sb.ToString();
    }

    private Token? ReadDecimalLiteral(
        SourceReference startSource,
        long intPart)
    {
        // The decimal point has already been read.
        decimal fracPart = 0m;
        decimal multiplier = 0.1m;
        int ch = this.PeekChar();
        while (IsDigit(ch))
        {
            _ = this.ReadChar();
            fracPart += (ch - '0') * multiplier;
            multiplier *= 0.1m;
            ch = this.PeekChar();
        }

        int exponent = 0;
        if (ch == 'e' || ch == 'E')
        {
            _ = this.ReadChar();
            if (!this.TryReadExponentPart(out exponent))
            {
                return null; // Error message already logged.
            }
        }

        // The exponent sign has already been handled in TryReadExponentPart.
        decimal result = intPart + fracPart;
        if (exponent != 0)
        {
            result *= (decimal)Math.Pow(10, exponent);
        }

        string? unit = null;
        ch = this.PeekChar();
        if (IsUnitStart(ch))
        {
            unit = this.ReadUnit();
            if (unit == null)
            {
                return null; // Error message already logged.
            }
        }

        var source = new SourceReference(
            this.startSource.Path,
            startSource.LineNumber,
            startSource.ColumnNumber,
            this.line,
            this.column);
        return new NumericLiteralToken(
            source,
            result,
            unit);
    }

    private bool TryReadExponentPart(
        out int exponent)
    {
        // 'e' or 'E' has already been read.
        exponent = 0;
        bool negativeExponent = false;
        int ch = this.PeekChar();
        if (ch == '+' || ch == '-')
        {
            negativeExponent = ch == '-';
            _ = this.ReadChar();
            ch = this.PeekChar();
        }

        if (!IsDigit(ch))
        {
            this.log(MessageUtility.ExpectedDigitAfterExponent(this.GetTokenSource()));
            return false;
        }

        while (IsDigit(ch))
        {
            _ = this.ReadChar();
            exponent = (exponent * 10) + (ch - '0');
            ch = this.PeekChar();
        }

        if (negativeExponent)
        {
            exponent = -exponent;
        }

        return true;
    }

    /// <summary>
    /// Reads a string literal token from the input.
    /// </summary>
    /// <returns>The read string literal token, or <c>null</c> if the string literal is unterminated.</returns>
    private StringLiteralToken? ReadStringLiteral()
    {
        // Use a UTF-8 encoding to handle multi-byte characters correctly.
        using var ms = new MemoryStream();
        using var writer = new StreamWriter(
            ms,
            Encoding.UTF8,
            1,
            leaveOpen: true);
        int lineStart = this.line;
        int columnStart = this.column;
        _ = this.ReadChar(); // Consume the opening quote.
        int ch = this.PeekChar();
        while (ch > 0 && ch != '"' && ch != '\n')
        {
            _ = this.ReadChar();
            if (ch == '\\')
            {
                ch = this.ReadChar();
                switch (ch)
                {
                    case 'a':
                        writer.Write('\a');
                        break;
                    case 'b':
                        writer.Write('\b');
                        break;
                    case 'f':
                        writer.Write('\f');
                        break;
                    case 'v':
                        writer.Write('\v');
                        break;
                    case 'n':
                        writer.Write('\n');
                        break;
                    case 'r':
                        writer.Write('\r');
                        break;
                    case 't':
                        writer.Write('\t');
                        break;
                    case '"':
                        writer.Write('"');
                        break;
                    case '\\':
                        writer.Write('\\');
                        break;
                    case 'x':
                        {
                            int hexValue = this.ReadHexEscapeSequence();
                            if (hexValue < 0)
                            {
                                this.log(MessageUtility.InvalidHexEscapeSequence(this.GetTokenSource(lineStart, columnStart)));
                                return null;
                            }

                            writer.Flush();
                            ms.WriteByte((byte)hexValue);
                        }

                        break;
                    default:
                        this.log(MessageUtility.UnknownEscapeSequence(this.GetTokenSource(lineStart, columnStart), (char)ch));
                        return null;
                }
            }
            else
            {
                writer.Write((char)ch);
            }

            ch = this.PeekChar();
        }

        if (ch == '"')
        {
            _ = this.ReadChar(); // Consume the closing quote.
        }
        else
        {
            var source = this.GetTokenSource(lineStart, columnStart);
            this.log(MessageUtility.UnterminatedStringLiteral(source));
            return null;
        }

        writer.Flush();
        ms.Position = 0;
        string value = Encoding.UTF8.GetString(ms.ToArray());
        if (value.Length > 0)
        {
            value = value.Substring(1); // Remove encoding byte.
        }

        var tokenSource = this.GetTokenSource(lineStart, columnStart);
        return new StringLiteralToken(tokenSource, value);
    }

    /// <summary>
    /// Reads the next 1 or 2 digits of a hexadecimal escape sequence from the input.
    /// </summary>
    /// <returns>The integer value of the hexadecimal escape sequence, or -1 if invalid.</returns>
    private int ReadHexEscapeSequence()
    {
        int value = 0;
        int ch = this.PeekHexDigit();
        if (ch < 0)
        {
            return -1;
        }

        _ = this.ReadChar();
        value = ch;

        ch = this.PeekHexDigit();
        if (ch >= 0)
        {
            _ = this.ReadChar();
            value = (value << 4) | ch;
        }

        return value;
    }

    private int PeekHexDigit()
    {
        int ch = this.PeekChar();
        if (ch >= '0' && ch <= '9')
        {
            return ch - '0';
        }

        if (ch >= 'a' && ch <= 'f')
        {
            return ch - 'a' + 10;
        }

        if (ch >= 'A' && ch <= 'F')
        {
            return ch - 'A' + 10;
        }

        return -1;
    }

    private CommentToken ReadSingleLineComment(int lineStart, int columnStart)
    {
        StringBuilder sb = new StringBuilder();
        _ = this.ReadChar(); // Consume the second slash.
        int ch = this.PeekChar();
        while (ch > 0 && ch != '\n')
        {
            _ = this.ReadChar();
            sb.Append((char)ch);
            ch = this.PeekChar();
        }

        string value = sb.ToString();
        var source = new SourceReference(
            this.startSource.Path,
            lineStart,
            columnStart,
            this.line,
            this.column);
        return new CommentToken(source, value, isBlock: false);
    }

    private CommentToken ReadBlockComment(int lineStart, int columnStart)
    {
        StringBuilder sb = new StringBuilder();
        _ = this.ReadChar(); // Consume the asterisk.
        int ch = this.PeekChar();
        while (ch > 0)
        {
            if (ch == '*')
            {
                _ = this.ReadChar();
                ch = this.PeekChar();
                if (ch == '/')
                {
                    _ = this.ReadChar(); // Consume the slash.
                    break;
                }
                else
                {
                    sb.Append('*');
                    continue;
                }
            }

            _ = this.ReadChar();
            sb.Append((char)ch);
            ch = this.PeekChar();
        }

        string value = sb.ToString();
        var source = new SourceReference(
            this.startSource.Path,
            lineStart,
            columnStart,
            this.line,
            this.column);
        return new CommentToken(source, value, isBlock: true);
    }

    private void SkipWhitespace()
    {
        int ch = this.PeekChar();
        while (ch > 0 && char.IsWhiteSpace((char)ch))
        {
            this.ReadChar();
            ch = this.PeekChar();
        }
    }

    private int PeekChar() => this.inner.Peek();

    private int ReadChar()
    {
        var ch = this.inner.Read();
        if (ch == '\n')
        {
            this.line++;
            this.column = 1;
        }
        else if (ch != -1)
        {
            this.column++;
        }

        return ch;
    }

    private SourceReference GetTokenSource() =>
        new SourceReference(this.startSource.Path, this.line, this.column);

    private SourceReference GetTokenSource(int lineStart, int columnStart) =>
        new SourceReference(this.startSource.Path, lineStart, columnStart, this.line, this.column);
}