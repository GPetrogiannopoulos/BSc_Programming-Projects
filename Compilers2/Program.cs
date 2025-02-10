// See https://aka.ms/new-console-template for more information

using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Laboratory1.obj;

StreamReader aStream = new StreamReader(args[0]);
AntlrInputStream ANTLRstream = new AntlrInputStream(aStream);
SimpleCalcLexer lexer = new SimpleCalcLexer(ANTLRstream);
CommonTokenStream tokens = new CommonTokenStream(lexer);
SimpleCalcParser parser = new SimpleCalcParser(tokens);
IParseTree tree = parser.compileUnit();
Console.WriteLine(tree.ToStringTree());


STPrinter printer = new STPrinter();
printer.Visit(tree);  // visit ton root komvo