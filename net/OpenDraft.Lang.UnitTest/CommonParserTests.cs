// <copyright file="CommonParserTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.Xml;
using OpenDraft.Lang.Tools;

/// <summary>
/// Tests the common suite of parser test cases, comparing the parser output against expected XML representations of the parse tree.
/// </summary>
[TestClass]
public class CommonParserTests
{
    /// <summary>
    /// Gets the common parser test cases.
    /// </summary>
    /// <returns>
    /// A collection of test cases, each consisting of a test case name, source code string, and expected XML string.
    /// </returns>
    public static IEnumerable<object[]> GetTestData()
    {
        var parserTestDirRelPath = Path.Combine("testcases", "parser");
        var inputPaths = Directory.EnumerateFiles(parserTestDirRelPath, "*.odl", SearchOption.TopDirectoryOnly);
        foreach (var inputPath in inputPaths)
        {
            var testCaseName = Path.GetFileNameWithoutExtension(inputPath);
            var source = File.ReadAllText(inputPath);
            var expectedXmlPath = Path.ChangeExtension(inputPath, ".xml");
            var expectedXml = File.Exists(expectedXmlPath) ? File.ReadAllText(expectedXmlPath) : string.Empty;
            yield return new object[] { testCaseName, source, expectedXml };
        }
    }

    /// <summary>
    /// Runs the parser on the provided source code and compares the output against the expected XML representation of the parse tree.
    /// </summary>
    /// <param name="testCaseName">The name of the test case.</param>
    /// <param name="source">The source code to be parsed.</param>
    /// <param name="expectedXml">The expected XML representation of the parse tree.</param>
    [TestMethod]
    [DynamicData(nameof(GetTestData))]
    public void ParserCommonTests(string testCaseName, string source, string expectedXml)
    {
        TestMessageLog logger = new TestMessageLog();
        using var reader = new StringReader(source);
        var tokenReader = new TokenReader(reader, new SourceReference(testCaseName, 1, 1), logger.Log);
        var parser = new Parser(logger.Log, tokenReader);
        var programNode = parser.Parse();
        Assert.IsNotNull(programNode, "Parsing failed. No output generated.");

        using var stringWriter = new StringWriter();
        using var xmlWriter = XmlWriter.Create(stringWriter, new XmlWriterSettings { Indent = true, OmitXmlDeclaration = true });
        var exporter = new ParseTreeXmlExporter(xmlWriter);
        exporter.Export(programNode);
        xmlWriter.Flush();
        var actualXml = stringWriter.ToString();
        Assert.AreEqual(expectedXml, actualXml, "Parsed XML does not match expected XML.");
    }
}