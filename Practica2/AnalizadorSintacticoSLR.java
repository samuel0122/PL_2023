import java.util.TreeSet;


public class AnalizadorSintacticoSLR
{
    private Token token;
    private AnalizadorLexico lexico;
    private StringBuilder reglasAplicadas;
    private TreeSet<Integer> terminosEsperados;

    public AnalizadorSintacticoSLR(AnalizadorLexico lexico)
    {
        this.terminosEsperados = new TreeSet<Integer>();
        this.lexico = lexico;
        this.token = lexico.siguienteToken();
        this.reglasAplicadas = new StringBuilder();
    }
    
    private void errorSintaxis()
    {
        StringBuilder argsEsperados = new StringBuilder();

        for(int tokEsperado: terminosEsperados)
            argsEsperados.append(" " + Token.nombreToken.get(tokEsperado));

        if(token.tipo == Token.EOF)
            System.err.printf("Error sintactico: encontrado fin de fichero, esperaba%s%n", argsEsperados.toString());
        else
            System.err.printf("Error sintactico (%d,%d): encontrado '%s', esperaba%s%n", token.fila, token.columna, token.lexema, argsEsperados.toString());
        
        System.exit(-1);
    }

    public final void analizar()
    {

    }

    

    public final void comprobarFinFichero()
    {
        if(token.tipo != Token.EOF)
        {
            terminosEsperados.add(Token.EOF);
            errorSintaxis();
        }
        
        System.out.println(reglasAplicadas.toString());
    }

    
    public final void S()
    {
        
    }

    private final void Vsp()
    {
        
    }

    private final void Unsp()
    {
        
    }

    private final void LV()
    {

    }

    private final void V()
    {
        
    }

    private final void Tipo()
    {
        
    }
    
    private final void Bloque()
    {
        
    }

    private final void SInstr()
    {
        
    }

    private final void Instr()
    {
        
    }

    private final void E()
    {
       
    }

    private final void Factor()
    {
        
    }
}