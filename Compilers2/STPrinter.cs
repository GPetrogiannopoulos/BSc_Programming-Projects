using System.Diagnostics;
using Antlr4.Runtime.Tree;

namespace Laboratory1.obj;

public class STPrinter : SimpleCalcBaseVisitor<int>
{
    private StreamWriter dotFile = new StreamWriter("SyntaxTree.dot");
    private static int ms_serialNumber = 0;
    private Stack<string> m_parentsLabels = new Stack<string>();
    public override int VisitCompileUnit(SimpleCalcParser.CompileUnitContext context) {   
        // 0. Emmit Prologue
        dotFile.WriteLine("digraph G{");
        
        // 1. Generate Label
        string label = "CompileUnit_" + ms_serialNumber++;
        
        // 2. Push label
        m_parentsLabels.Push(label);
        
        // 3. Visit children
        base.VisitCompileUnit(context);
        
        m_parentsLabels.Pop(); // adeiazo
        // 4. Emmit Epilogue
        dotFile.WriteLine("}");
        dotFile.Close();
        
        // 5. Call Graphviz
            // Prepare the process dot to run
            ProcessStartInfo start = new ProcessStartInfo();
            // Enter in the command line arguments, everything you would enter after the executable name itself
            start.Arguments = "-Tgif " +
                              Path.GetFileName("SyntaxTree.dot") + " -o " +
                              Path.GetFileNameWithoutExtension("SyntaxTree") + ".gif";
            // Enter the executable to run, including the complete path
            start.FileName = "dot";
            // Do you want to show a console window?
            start.WindowStyle = ProcessWindowStyle.Hidden;
            start.CreateNoWindow = true;
            int exitCode;

            // Run the external process & wait for it to finish
            using (Process proc = Process.Start(start)) {
                proc.WaitForExit();

                // Retrieve the app's exit code
                exitCode = proc.ExitCode;
            }

        return 0;
    }

    public override int VisitAssignment(SimpleCalcParser.AssignmentContext context)
    {
        //1. Generate Label          
        string label = "Assignment_" + ms_serialNumber++;
        
        //2. Export ST edge
        dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");  // peek() -> apo to patera
        
        //3. Push label                  
        m_parentsLabels.Push(label);    
        
        //4. visit children
        base.VisitAssignment(context);

        //5. Pop Label
        m_parentsLabels.Pop();
        
        return 0;
    }

    public override int VisitNUMBER(SimpleCalcParser.NUMBERContext context)
    {
        //1. Generate Label                                                                               
        string label = "Parenthesis_" + ms_serialNumber++;                                                 
                                                                                                  
        //2. Export ST edge                                                                               
        dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");  // peek() -> apo to patera  
                                                                                                          
        //3. Push label                                                                                   
        m_parentsLabels.Push(label);                                                                      
                                                                                                          
        //4. visit children                                                                               
        //base.VisitAssignment(context);                                                                    
                                                                                                          
        //5. Pop Label                                                                                    
        m_parentsLabels.Pop();                                                                            
                                                                                                  
        return 0;                                                                                         
    }
    
    public override int VisitParenthesis(SimpleCalcParser.ParenthesisContext context) // OK 
    {
        // 1. Generate Label
        string label = "Parenthesis" + ms_serialNumber++;
        
        // 2. Export ST edge
        dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");
        
        // 3. Push Label
        m_parentsLabels.Push(label);
        
        // 4. Visit children
        base.VisitParenthesis(context);
        
        // 5. Pop Label
        m_parentsLabels.Pop();
        
        return 0;
    } 

    //-----------------------------------------
    public override int VisitMultDiv(SimpleCalcParser.MultDivContext context) // OK
    {
        String label="";
        switch (context.op.Type)
        {
            case SimpleCalcLexer.MULT:
                label = "Multiplication" + ms_serialNumber++;
                break;
            case SimpleCalcLexer.DIV:
                label = "Division" + ms_serialNumber++;
                break;
        }
        
        // 2. Export ST edge
        dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");
        
        // 3. Push Label
        m_parentsLabels.Push(label);
        
        // 4. Visit children
        base.VisitMultDiv(context);
        
        // 5. Pop Label
        m_parentsLabels.Pop();
        
        return 0;               
    }

    public override int VisitAddSub(SimpleCalcParser.AddSubContext context) // OK
    {
        String label="";
        switch (context.op.Type)
        {
            case SimpleCalcLexer.ADD:
                label = "Addition" + ms_serialNumber++;
                break;
            case SimpleCalcLexer.SUB:
                label = "Subtraction" + ms_serialNumber++;
                break;
        }
        
        // 2. Export ST edge
        dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");
        
        // 3. Push Label
        m_parentsLabels.Push(label);
        
        // 4. Visit children
        base.VisitAddSub(context);
        
        // 5. Pop Label
        m_parentsLabels.Pop();
        
        return 0;              
    }

    public override int VisitTerminal(ITerminalNode node) // OK
    {
        String label="";
        switch (node.Symbol.Type)
        {
            case SimpleCalcLexer.NUMBER:
                label = "NUMBER" + ms_serialNumber++;
                break;
            case SimpleCalcLexer.IDENTIFIER:
                label = "IDENTIFIER" + ms_serialNumber++;
                // 2. Export ST edge
                dotFile.WriteLine("\""+m_parentsLabels.Peek()+"\"->\""+label+"\";");
                break;
        }
        
        return 0;              
    }
}