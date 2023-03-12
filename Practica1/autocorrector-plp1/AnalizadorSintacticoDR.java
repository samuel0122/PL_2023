import java.util.TreeSet;

//TODO: tests de mensajes de salida de error

public class AnalizadorSintacticoDR
{
    private Token token;
    private AnalizadorLexico lexico;
    private StringBuilder reglasAplicadas;
    private TreeSet<Integer> terminosEsperados;

    public AnalizadorSintacticoDR(AnalizadorLexico lexico)
    {
        terminosEsperados = new TreeSet<Integer>();
        this.lexico = lexico;
        token = lexico.siguienteToken();
        reglasAplicadas = new StringBuilder();
    }
    
    private void errorSintaxis()
    {
        StringBuilder argsEsperados = new StringBuilder();

        for(int tokEsperado: terminosEsperados)
            argsEsperados.append(" " + Token.nombreToken.get(tokEsperado));

        if(token.tipo == Token.EOF)
            System.err.printf("Error sintactico: encontrado fin de fichero, esperaba%s%n", argsEsperados.toString());
        else
            System.err.printf("Error sintactico (%d,%d): encontrado %s, esperaba%s%n", token.fila, token.columna, Token.nombreTokenErroneo.get(token.tipo), argsEsperados.toString());
        
        System.exit(-1);
    }

    public final void emparejar(int tokEsperado)
    {
        if (token.tipo == tokEsperado)
            token = lexico.siguienteToken();
        else
        {
            terminosEsperados.add(tokEsperado);
            errorSintaxis();
        }
    }

    

    public final void comprobarFinFichero()
    {
        if(token.tipo != Token.EOF)
            errorSintaxis();
        
        System.out.println(reglasAplicadas.toString());
    }

    
    public final void S()
    {
        switch(token.tipo)
        {
            case Token.ALGORITMO:
                reglasAplicadas.append(" 1");
                emparejar(Token.ALGORITMO);
                emparejar(Token.ID);
                emparejar(Token.PYC);
                Vsp();
                Bloque();
                break;
            
            default: 
                terminosEsperados.add(Token.ALGORITMO);
                errorSintaxis();
        }
    }

    private final void Vsp()
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
            case Token.VAR:
                reglasAplicadas.append(" 2");
                Unsp();
                Vspp();
                break;
            
            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                errorSintaxis();
        }
    }

    private final void Vspp()
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
            case Token.VAR:
                reglasAplicadas.append(" 3");
                Unsp();
                Vspp();
                break;
            
            case Token.BLQ:
                reglasAplicadas.append(" 4");
                break;

            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                terminosEsperados.add(Token.BLQ);
                errorSintaxis();
        }
    }

    private final void Unsp()
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
                reglasAplicadas.append(" 5");
                emparejar(Token.FUNCION);
                emparejar(Token.ID);
                emparejar(Token.DOSP);
                Tipo();
                emparejar(Token.PYC);
                Vsp();
                Bloque();
                emparejar(Token.PYC);
                break;
            
            case Token.VAR:
                reglasAplicadas.append(" 6");
                emparejar(Token.VAR);
                LV();
                break;

            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);    
                errorSintaxis();
        }
    }

    private final void LV()
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 7");
                V();
                LVp();
                break;
            
            default:
                terminosEsperados.add(Token.ID);
                errorSintaxis();
        }

    }

    private final void LVp()
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 8");
                V();
                LVp();
                break;
            
            case Token.FUNCION:
            case Token.VAR:
            case Token.BLQ:
                reglasAplicadas.append(" 9");
                break;
                
            default:
                terminosEsperados.add(Token.ID);
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                terminosEsperados.add(Token.BLQ);
                errorSintaxis();
        }
    }

    private final void V()
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 10");
                emparejar(Token.ID);
                Lid();
                emparejar(Token.DOSP);
                Tipo();
                emparejar(Token.PYC);
                break;
                
            default: 
                terminosEsperados.add(Token.ID);
                errorSintaxis();
        }
    }

    private final void Lid()
    {
        switch(token.tipo)
        {
            case Token.COMA:
                reglasAplicadas.append(" 11");
                emparejar(Token.COMA);
                emparejar(Token.ID);
                Lid();
                break;

            case Token.DOSP:
                reglasAplicadas.append(" 12");
                break;
                
            default: 
            terminosEsperados.add(Token.COMA);
            terminosEsperados.add(Token.DOSP);
            errorSintaxis();
        }
    }

    private final void Tipo()
    {
        switch(token.tipo)
        {
            case Token.ENTERO:
                reglasAplicadas.append(" 13");
                emparejar(Token.ENTERO);
                break;

            case Token.REAL:
                reglasAplicadas.append(" 14");
                emparejar(Token.REAL);
                break;
                
            default: 
            terminosEsperados.add(Token.ENTERO);
            terminosEsperados.add(Token.REAL);
            errorSintaxis();
        }
    }
    
    private final void Bloque()
    {
        switch(token.tipo)
        {
            case Token.BLQ:
                reglasAplicadas.append(" 15");
                emparejar(Token.BLQ);
                SInstr();
                emparejar(Token.FBLQ);
                break;

            default: 
            terminosEsperados.add(Token.BLQ);
            errorSintaxis();
        }
    }

    private final void SInstr()
    {
        switch(token.tipo)
        {
            case Token.BLQ:
            case Token.ID:
            case Token.SI:
            case Token.MIENTRAS:
            case Token.ESCRIBIR:
                reglasAplicadas.append(" 16");
                Instr();
                SInstrp();
                break;

            default: 
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            terminosEsperados.add(Token.ID);
            errorSintaxis();
        }
    }

    private final void SInstrp()
    {
        switch(token.tipo)
        {
            case Token.PYC:
                reglasAplicadas.append(" 17");
                emparejar(Token.PYC);
                Instr();
                SInstrp();
                break;

            case Token.FBLQ:
                reglasAplicadas.append(" 18");
                break;

            default: 
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            terminosEsperados.add(Token.ID);
            errorSintaxis();
        }
    }

    private final void Instr()
    {
        switch(token.tipo)
        {
            case Token.BLQ:
                reglasAplicadas.append(" 19");
                Bloque();
                break;

            case Token.ID:
                reglasAplicadas.append(" 20");
                emparejar(Token.ID);
                emparejar(Token.ASIG);
                E();
                break;
            
            case Token.SI:
                reglasAplicadas.append(" 21");
                emparejar(Token.SI);
                E();
                emparejar(Token.ENTONCES);
                Instr();
                Instrp();
                break;
            
            case Token.MIENTRAS:
                reglasAplicadas.append(" 24");
                emparejar(Token.MIENTRAS);
                E();
                emparejar(Token.HACER);
                Instr();
                break;

            case Token.ESCRIBIR:
                reglasAplicadas.append(" 25");
                emparejar(Token.ESCRIBIR);
                emparejar(Token.PARI);
                E();
                emparejar(Token.PARD);
                break;

            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            errorSintaxis();
        }
    }

    private final void Instrp()
    {
        switch(token.tipo)
        {
            case Token.FSI:
                reglasAplicadas.append(" 22");
                emparejar(Token.FSI);
                break;

            case Token.SINO:
                reglasAplicadas.append(" 23");
                emparejar(Token.SINO);
                Instr();
                emparejar(Token.FSI);
                break;
                
            default: 
            terminosEsperados.add(Token.FSI);
            terminosEsperados.add(Token.SINO);
            errorSintaxis();
        }
    }

    private final void E()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:
                reglasAplicadas.append(" 26");
                Expr();
                Ep();
                break;
                
            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }
    }

    private final void Ep()
    {
        switch(token.tipo)
        {
            case Token.OPREL:
                reglasAplicadas.append(" 27");
                emparejar(Token.OPREL);
                Expr();
                break;

            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
                reglasAplicadas.append(" 28");
                break;
                
            default: 
            terminosEsperados.add(Token.OPREL);
            terminosEsperados.add(Token.PYC);
            terminosEsperados.add(Token.FSI);
            terminosEsperados.add(Token.SINO);
            terminosEsperados.add(Token.FBLQ);
            terminosEsperados.add(Token.ENTONCES);
            terminosEsperados.add(Token.HACER);
            terminosEsperados.add(Token.PARD);
            errorSintaxis();
        }
    }

    private final void Expr()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:
                reglasAplicadas.append(" 29");
                Term();
                Exprp();
                break;
                
            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }
    }

    private final void Exprp()
    {
        switch(token.tipo)
        {
            case Token.OPAS:
                reglasAplicadas.append(" 30");
                emparejar(Token.OPAS);
                Term();
                Exprp();
                break;
            
            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
            case Token.OPREL:
                reglasAplicadas.append(" 31");
                break;

            default: 
            terminosEsperados.add(Token.OPAS);
            terminosEsperados.add(Token.OPREL);
            terminosEsperados.add(Token.PYC);
            terminosEsperados.add(Token.FSI);
            terminosEsperados.add(Token.SINO);
            terminosEsperados.add(Token.FBLQ);
            terminosEsperados.add(Token.ENTONCES);
            terminosEsperados.add(Token.HACER);
            terminosEsperados.add(Token.PARD);
            errorSintaxis();
        }
    }

    private final void Term()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:
                reglasAplicadas.append(" 32");
                Factor();
                Termp();
                break;

            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }
    }

    private final void Termp()
    {
        switch(token.tipo)
        {
            case Token.OPMD:
                reglasAplicadas.append(" 33");
                emparejar(Token.OPMD);
                Factor();
                Termp();
                break;
            
            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
            case Token.OPREL:
            case Token.OPAS:
                reglasAplicadas.append(" 34");
                break;

            default: 
            terminosEsperados.add(Token.OPMD);
            terminosEsperados.add(Token.OPAS);
            terminosEsperados.add(Token.OPREL);
            terminosEsperados.add(Token.PYC);
            terminosEsperados.add(Token.FSI);
            terminosEsperados.add(Token.SINO);
            terminosEsperados.add(Token.FBLQ);
            terminosEsperados.add(Token.ENTONCES);
            terminosEsperados.add(Token.HACER);
            terminosEsperados.add(Token.PARD);
            errorSintaxis();
        }
    }

    private final void Factor()
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 35");
                emparejar(Token.ID);
                break;
            
            case Token.NENTERO:
                reglasAplicadas.append(" 36");
                emparejar(Token.NENTERO);
                break;
            
            case Token.NREAL:
                reglasAplicadas.append(" 37");
                emparejar(Token.NREAL);
                break;

            case Token.PARI:
                reglasAplicadas.append(" 38");
                emparejar(Token.PARI);
                Expr();
                emparejar(Token.PARD);
                break;

            default: 
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }
    }
}