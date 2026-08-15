// <copyright file="Program.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.LangToXml;

using System.IO;
using System.Xml;

using OpenDraft.Lang;
using OpenDraft.Lang.Tools;

/// <summary>
/// The main program class for the odlang2xml tool, which converts OpenDraft language files to XML format.
/// </summary>
internal class Program
{
    private static int Main(string[] args)
    {
        if (args.Length < 1 || args.Length > 2)
        {
            PrintUsage();
            return 1;
        }

        string inputFilePath = args[0];
        string? outputFilePath = args.Length == 2 ? args[1] : null;

        using var reader = CreateTextReader(inputFilePath);

        var tokenReader = new TokenReader(
            reader,
            new SourceReference(inputFilePath, 1, 1),
            MessageLogger);

        var parser = new Parser(MessageLogger, tokenReader);

        var programNode = parser.Parse();
        if (programNode == null)
        {
            Console.Error.WriteLine("Parsing failed. No output generated.");
            return 1;
        }

        using var writer = CreateXmlWriter(outputFilePath);
        var exporter = new ParseTreeXmlExporter(writer);
        exporter.Export(programNode);

        return 0;
    }

    private static void MessageLogger(Message message)
    {
        string messageText = $"{message.Source}: {message.Severity}: {message.Text}";
        if (message.Severity == MessageSeverity.Error)
        {
            Console.Error.WriteLine(messageText);
        }
        else
        {
            Console.WriteLine(messageText);
        }
    }

    private static XmlWriter CreateXmlWriter(string? outputFilePath)
    {
        XmlWriterSettings settings = new XmlWriterSettings
        {
            Indent = true,
            IndentChars = "  ",
            NewLineOnAttributes = false,
            OmitXmlDeclaration = true,
        };

        if (outputFilePath != null)
        {
            return XmlWriter.Create(outputFilePath, settings);
        }
        else
        {
            return XmlWriter.Create(Console.Out, settings);
        }
    }

    private static TextReader CreateTextReader(string inputFilePath)
    {
        if (inputFilePath == "--")
        {
            return Console.In;
        }
        else
        {
            return new StreamReader(inputFilePath);
        }
    }

    private static void PrintUsage()
    {
        Console.WriteLine("Usage: odlang2xml <input_file> [output_file]");
        Console.WriteLine("Converts an OpenDraft language file to XML format.");
        Console.WriteLine("If the input file is '--', the program reads from standard input.");
        Console.WriteLine("If the output file is not specified, the program writes to standard output.");
    }
}