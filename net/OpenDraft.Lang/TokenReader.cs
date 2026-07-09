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

    private Token? InnerRead()
    {
        this.SkipWhitespace();
        int lineStart = this.line;
        int columnStart = this.column;
        int ch = this.PeekChar();
        if (ch == -1)
        {
            return null;
        }

        if (char.IsLetter((char)ch) || ch == '_')
        {
            return this.ReadIdentifierOrKeyword();
        }
        else if (char.IsDigit((char)ch))
        {
            return this.ReadNumberLiteral(lineStart, columnStart);
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
                return this.ReadNumberLiteral(lineStart, columnStart, startWithDot: true);
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

        switch (ch)
        {
            case '(':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.LeftParen);
            case ')':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.RightParen);
            case '[':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.LeftBracket);
            case ']':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.RightBracket);
            case ';':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.Semicolon);
            case ',':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.Comma);
            case '+':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.Plus);
            case '-':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.Minus);
            case '*':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.Asterisk);
            case '{':
                _ = this.ReadChar();
                return new SymbolToken(
                    this.GetTokenSource(lineStart, columnStart),
                    Symbol.LeftBrace);
            case '}':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.RightBrace);
            case '^':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.Caret);
            case '%':
                _ = this.ReadChar();
                return new SymbolToken(
                    new SourceReference(
                        this.startSource.Path,
                        lineStart,
                        columnStart,
                        this.line,
                        this.column),
                    Symbol.Modulus);
            default:
                break;
        }

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
        while (ch > 0 && (char.IsLetterOrDigit((char)ch) || ch == '_'))
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

    private NumericLiteralToken ReadNumberLiteral(
        int lineStart,
        int columnStart,
        bool startWithDot = false)
    {
        long intPart = 0;
        double fracPart = 0;
        long expPart = 0;
        int ch = this.PeekChar();
        if (!startWithDot)
        {
            while (ch > 0 && char.IsDigit((char)ch))
            {
                _ = this.ReadChar();
                intPart = (intPart * 10) + (ch - '0');
                ch = this.PeekChar();
            }
        }

        if (ch == '.' && !startWithDot)
        {
            _ = this.ReadChar();
            ch = this.PeekChar();
        }

        double fracMul = 0.1;
        while (ch > 0 && char.IsDigit((char)ch))
        {
            _ = this.ReadChar();
            fracPart = fracPart + ((ch - '0') * fracMul);
            fracMul *= 0.1;
            ch = this.PeekChar();
        }

        if (ch == 'e' || ch == 'E')
        {
            _ = this.ReadChar();
            ch = this.PeekChar();
            bool expNegative = false;
            if (ch == '+' || ch == '-')
            {
                expNegative = ch == '-';
                _ = this.ReadChar();
                ch = this.PeekChar();
            }

            while (ch > 0 && char.IsDigit((char)ch))
            {
                _ = this.ReadChar();
                expPart = (expPart * 10) + (ch - '0');
                ch = this.PeekChar();
            }

            if (expNegative)
            {
                expPart = -expPart;
            }
        }

        var source = this.GetTokenSource(lineStart, columnStart);
        var result = intPart + fracPart;
        if (expPart != 0)
        {
            result *= Math.Pow(10, expPart);
        }

        return new NumericLiteralToken(source, result);
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
            value = (value * 0x10) + ch;
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