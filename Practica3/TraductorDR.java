import java.util.TreeSet;
import java.util.Vector;

import javax.lang.model.util.ElementScanner6;

public class TraductorDR
{
    private class TipoClass{
        public TipoClass(Token tipoToken)
        {
            boolean isInt = tipoToken.tipo == Token.ENTERO;

            this.tipo =  isInt ? tipoInt : tipoDouble;
            this.trad =  isInt ? "int" : "double";
        }

        public int tipoToSimbolo()
        {
            switch(this.tipo)
            {
                case tipoInt:
                    return Simbolo.ENTERO;
                
                case tipoDouble:
                    return Simbolo.REAL;
                
                default:
                    //TODO: Error
                    return -1;
            }
        }

        public String trad;
        public int tipo;
    }

    private class EType{
        public EType(int tipo, String trad)
        {
            this.tipo = tipo;
            this.trad = trad;
        }

        public String print()
        {
            return (this.tipo == Simbolo.ENTERO) ? "%d" : "%g";
        }

        public int tipo;
        public String trad;
    }

    private TablaSimbolos tsActual;
    private Token token;
    private AnalizadorLexico lexico;
    private StringBuilder reglasAplicadas;
    private TreeSet<Integer> terminosEsperados;


    private final int   ERR_YA_EXISTE   = 1,
                        ERR_NO_VARIABLE = 2,
                        ERR_NO_DECL     = 3,
                        ERR_NO_BOOL     = 4,
                        ERR_ASIG_REAL   = 5,
                        ERR_SIMIENTRAS  = 6,
                        ERR_DIVENTERA   = 7;
    
    private final int   tipoInt    = 0,
                        tipoDouble = 1,
                        tipoBool   = 2;

    private void errorSemantico(int nerr,int fila,int columna,String lexema) {
        System.err.print("Error semantico ("+fila+","+columna+"): ");
        switch (nerr) {
            case ERR_YA_EXISTE:
                System.err.println("'"+lexema+"' ya existe en este ambito");
                break;
            case ERR_NO_VARIABLE:
                System.err.println("'"+lexema+"' no es una variable");
                break;
            case ERR_NO_DECL:
                System.err.println("'"+lexema+"' no ha sido declarado");
                break;
            case ERR_NO_BOOL:
                System.err.println("'"+lexema+"' no admite expresiones booleanas");
                break;
            case ERR_ASIG_REAL:
                System.err.println("'"+lexema+"' debe ser de tipo real");
                break;
            case ERR_SIMIENTRAS:
                System.err.println("en la instruccion '"+lexema+"' la expresion debe ser relacional");
                break;
            case ERR_DIVENTERA:
                System.err.println("los dos operandos de '"+lexema+"' deben ser enteros");
                break;
        }
        System.exit(-1);
    }


    public TraductorDR(AnalizadorLexico lexico)
    {
        terminosEsperados = new TreeSet<Integer>();
        this.lexico = lexico;
        token = lexico.siguienteToken();
        reglasAplicadas = new StringBuilder();
        tsActual = new TablaSimbolos(null);
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

    private final Token emparejar(int tokEsperado)
    {   
        Token tokenCopia = new Token(token);

        if (token.tipo == tokEsperado)
            token = lexico.siguienteToken();
        else
        {
            terminosEsperados.add(tokEsperado);
            errorSintaxis();
        }

        return tokenCopia;
    }

    public final void comprobarFinFichero()
    {
        if(token.tipo != Token.EOF)
        {
            terminosEsperados.add(Token.EOF);
            errorSintaxis();
        }
        
        // System.out.println(reglasAplicadas.toString());
    }

    
    public String S()
    {
        switch(token.tipo)
        {
            case Token.ALGORITMO:
                reglasAplicadas.append(" 1");

                Token algoritmo = emparejar(Token.ALGORITMO);
                Token id = emparejar(Token.ID);
                emparejar(Token.PYC);

                String tradVsp = Vsp("");
                String tradBloque = Bloque("");
                
                
                return "// " + algoritmo.lexema + " " + id.lexema + '\n' + tradVsp + "int main() " + tradBloque;
            
            default: 
                terminosEsperados.add(Token.ALGORITMO);
                errorSintaxis();
        }

        return "";
    }

    private final String Vsp(String th)
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
            case Token.VAR:
                reglasAplicadas.append(" 2");

                String tradUnsp = Unsp(th);
                String tradVspp = Vspp(th);
                
                return tradUnsp + tradVspp;
            
            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                errorSintaxis();
        }
        return "";
    }

    private final String Vspp(String th)
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
            case Token.VAR:
                reglasAplicadas.append(" 3");
                
                String tradUnsp = Unsp(th);
                String tradVspp = Vspp(th);
                
                return tradUnsp + tradVspp;
            
            case Token.BLQ:
                return "";

            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                terminosEsperados.add(Token.BLQ);
                errorSintaxis();
        }

        return "";
    }

    private final String Unsp(String th)
    {
        switch(token.tipo)
        {
            case Token.FUNCION:
                reglasAplicadas.append(" 5");

                emparejar(Token.FUNCION);
                Token id = emparejar(Token.ID);
                emparejar(Token.DOSP);
                TipoClass tipo = Tipo();
                emparejar(Token.PYC);

                String nombreFuncionBloque = (th == "") ? id.lexema : th + '_' + id.lexema;
                
                // Inserto la función como nuevo símbolo
                if(!tsActual.nuevoSimbolo(new Simbolo(id.lexema, nombreFuncionBloque, Simbolo.FUNCION)))
                    errorSemantico(ERR_YA_EXISTE, id.fila, id.columna, id.lexema);
                
                // Creo nuevo ámbito para este algoritmo
                tsActual = new TablaSimbolos(tsActual);

                String tradVsp = Vsp(th + id.lexema + '_');
                String tradBloque = Bloque(nombreFuncionBloque);

                emparejar(Token.PYC);
                
                // Recupero el ámbito anterior al algoritmo
                tsActual = tsActual.getAmbitoAnterior();

                return tradVsp + tipo.trad + ' ' + nombreFuncionBloque + " ()" + tradBloque;
            
            case Token.VAR:
                reglasAplicadas.append(" 6");

                emparejar(Token.VAR);
                String tradLV = LV(th);
                
                return tradLV;

            default: 
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);    
                errorSintaxis();
        }

        return null;
    }

    private final String LV(String th)
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 7");

                String tradV = V(th);
                String tradLVp = LVp(th);
                
                return tradV + tradLVp;
            
            default:
                terminosEsperados.add(Token.ID);
                errorSintaxis();
        }

        return null;
    }

    private final String LVp(String th)
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 8");
                
                String tradV = V(th);
                String tradLVp = LVp(th);

                return tradV + tradLVp;
            
            case Token.FUNCION:
            case Token.VAR:
            case Token.BLQ:

                reglasAplicadas.append(" 9");

                return "";

            default:
                terminosEsperados.add(Token.ID);
                terminosEsperados.add(Token.FUNCION);
                terminosEsperados.add(Token.VAR);
                terminosEsperados.add(Token.BLQ);
                errorSintaxis();
        }
     
        return null;
    }

    private final String V(String th)
    {
        switch(token.tipo)
        {
            case Token.ID:
                reglasAplicadas.append(" 10");

                if(th == "")
                    th = "main_";
                
                Vector<Token> vTokens = new Vector<>();

                Token id = emparejar(Token.ID);

                // Guardar variable para añadir al ámbito
                vTokens.add(id);

                String tradLid = Lid(th, vTokens);
                emparejar(Token.DOSP);
                TipoClass tipo = Tipo();
                emparejar(Token.PYC);

                int tipoSimbolo = tipo.tipoToSimbolo();

                // Añade variables al ámbito
                for (Token token : vTokens) {
                    if(!tsActual.nuevoSimbolo(new Simbolo(token.lexema, th+token.lexema, tipoSimbolo)))
                        errorSemantico(ERR_YA_EXISTE, token.fila, token.columna, token.lexema);
                }

                return tipo.trad + ' ' + th + id.lexema + tradLid + ";\n";
                
            default: 
                terminosEsperados.add(Token.ID);
                errorSintaxis();
        }
     
        return null;
    }

    private final String Lid(String th, Vector<Token> vTokens)
    {
        switch(token.tipo)
        {
            case Token.COMA:
                reglasAplicadas.append(" 11");
                
                emparejar(Token.COMA);

                Token id = emparejar(Token.ID);

                vTokens.add(id);

                String tradLid = Lid(th, vTokens);
                
                return ',' + th + id.lexema + tradLid;

            case Token.DOSP:
                reglasAplicadas.append(" 12");

                return "";
                
            default: 
            terminosEsperados.add(Token.COMA);
            terminosEsperados.add(Token.DOSP);
            errorSintaxis();
        }
     
        return null;
    }

    private final TipoClass Tipo()
    {
        switch(token.tipo)
        {
            case Token.ENTERO:
                reglasAplicadas.append(" 13");

                return new TipoClass(emparejar(Token.ENTERO));

            case Token.REAL:
                reglasAplicadas.append(" 14");

                return new TipoClass(emparejar(Token.REAL));
                
            default: 
            terminosEsperados.add(Token.ENTERO);
            terminosEsperados.add(Token.REAL);
            errorSintaxis();
        }

        return null;
    }
    
    private final String Bloque(String th)
    {
        switch(token.tipo)
        {
            case Token.BLQ:
                reglasAplicadas.append(" 15");

                emparejar(Token.BLQ);
                String tradSInstr = SInstr(th);
                emparejar(Token.FBLQ);

                return "{\n" + tradSInstr + "}\n";

            default: 
            terminosEsperados.add(Token.BLQ);
            errorSintaxis();
        }

        return null;
    }

    private final String SInstr(String th)
    {
        switch(token.tipo)
        {
            case Token.BLQ:
            case Token.ID:
            case Token.SI:
            case Token.MIENTRAS:
            case Token.ESCRIBIR:
                reglasAplicadas.append(" 16");

                String tradInstr = Instr(th);
                String tradSInstrp = SInstrp(th);
                
                return tradInstr + tradSInstrp;

            default: 
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            terminosEsperados.add(Token.ID);
            errorSintaxis();
        }

        return null;
    }

    private final String SInstrp(String th)
    {
        switch(token.tipo)
        {
            case Token.PYC:
                reglasAplicadas.append(" 17");

                emparejar(Token.PYC);
                String tradInstr = Instr(th);
                String tradSInstrp = SInstrp(th);
                
                return tradInstr + tradSInstrp;

            case Token.FBLQ:
                reglasAplicadas.append(" 18");

                return "";

            default: 
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            terminosEsperados.add(Token.ID);
            errorSintaxis();
        }

        return null;
    }

    private final String Instr(String th)
    {
        switch(token.tipo)
        {
            case Token.BLQ:
            {
                reglasAplicadas.append(" 19");

                String tradBloque = Bloque(th);
                
                return tradBloque;
            }

            case Token.ID:
            {
                reglasAplicadas.append(" 20");

                Token id   = emparejar(Token.ID);
                Token asig = emparejar(Token.ASIG);

                Simbolo idSimbolo = tsActual.buscar(id.lexema);
                
                if(idSimbolo == null)
                    errorSemantico(ERR_NO_DECL, id.fila, id.columna, id.lexema);
                
                if(idSimbolo.tipo == Simbolo.FUNCION)
                    errorSemantico(ERR_NO_VARIABLE, id.fila, id.columna, id.lexema);
                
                EType eType = E();

                if(idSimbolo.tipo == Simbolo.ENTERO)
                {
                    if(eType.tipo == tipoDouble)
                        //TODO: ERROR asignando real a entero
                        errorSemantico(ERR_ASIG_REAL, id.fila, id.columna, id.lexema);
                    else if(eType.tipo == tipoInt)
                        return idSimbolo.nombreCompleto + " =i " + eType.trad + " ;\n";
                }
                else if(idSimbolo.tipo == Simbolo.REAL)
                {
                    if(eType.tipo == tipoDouble)
                        return idSimbolo.nombreCompleto + " =r " + eType.trad + " ;\n";
                    else if(eType.tipo == tipoInt)
                        return idSimbolo.nombreCompleto + " =r itor(" + eType.trad + ") ;\n";
                }
                
                //TODO: ERROR es nombre función
                if(idSimbolo.tipo == Simbolo.FUNCION)
                    errorSemantico(ERR_NO_VARIABLE, id.fila, id.columna, id.lexema);
                
                //TODO: ERROR es bool
                if(eType.tipo == tipoBool)
                    errorSemantico(ERR_NO_BOOL, asig.fila, asig.columna, asig.lexema);

                return null;
            }
            
            case Token.SI:
            {
                reglasAplicadas.append(" 21");
                
                Token si = emparejar(Token.SI);
                EType eType = E();
                
                // TODO: error
                if(eType.tipo != tipoBool)
                    errorSemantico(ERR_SIMIENTRAS, si.fila, si.columna, si.lexema);

                emparejar(Token.ENTONCES);
                String tradInstr = Instr(th);
                String tradInstrp = Instrp(th);

                return "if (" + eType.trad + ")\n" + tradInstr + tradInstrp;
            }

            case Token.MIENTRAS:
            {
                reglasAplicadas.append(" 24 ");

                Token mientras = emparejar(Token.MIENTRAS);
                EType eType = E();

                // TODO: error
                if(eType.tipo != tipoBool)
                    errorSemantico(ERR_SIMIENTRAS, mientras.fila, mientras.columna, mientras.lexema);

                emparejar(Token.HACER);
                String tradInstr = Instr(th);
                
                return "while ( " + eType.trad + " )\n" + tradInstr;
            }

            case Token.ESCRIBIR:
            {
                reglasAplicadas.append(" 25");

                Token escribir = emparejar(Token.ESCRIBIR);
                emparejar(Token.PARI);
                EType eType = E();
                emparejar(Token.PARD);
                
                // TODO: error
                if(eType.tipo == tipoBool)
                    errorSemantico(ERR_NO_BOOL, escribir.fila, escribir.columna, escribir.lexema);

                return "printf(\"" + eType.print() + "\"," + eType.trad +");\n";
            }

            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.BLQ);
            terminosEsperados.add(Token.SI);
            terminosEsperados.add(Token.MIENTRAS);
            terminosEsperados.add(Token.ESCRIBIR);
            errorSintaxis();
        }

        return null;
    }

    private final String Instrp(String th)
    {
        switch(token.tipo)
        {
            case Token.FSI:
            {
                reglasAplicadas.append(" 22");

                emparejar(Token.FSI);
                
                return "";
            }

            case Token.SINO:
            {
                reglasAplicadas.append(" 23");

                emparejar(Token.SINO);
                String tradInstr = Instr(th);
                emparejar(Token.FSI);

                return "else\n" + tradInstr;
            }

            default: 
            terminosEsperados.add(Token.FSI);
            terminosEsperados.add(Token.SINO);
            errorSintaxis();
        }

        return null;
    }

    private final EType E()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:
                reglasAplicadas.append(" 26");
            
                EType eExpr = Expr();
                EType eEp = Ep(eExpr.tipo);

                // Si no hay expresión booleana
                if(eEp == null)
                    return eExpr;
                
                // Si la expresión booleana son dos enteros
                if(eEp.tipo == tipoInt)
                    return new EType(tipoBool, eExpr.trad + eEp.trad);
                
                // Si hay un double, comprobar tipo Expr
                if(eEp.tipo == tipoDouble)
                {
                    // Si ambos double, concat
                    if(eExpr.tipo == tipoDouble)
                        return new EType(tipoBool, eExpr.trad + eEp.trad);
                    // Si este int, cast
                    if(eExpr.tipo == tipoInt)
                        return new EType(tipoBool, "itor(" + eExpr.trad + ')' + eEp.trad);
                }
    
                break;
                
            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }

        return null;
    }

    private final EType Ep(int tipoH)
    {
        switch(token.tipo)
        {
            case Token.OPREL:
                reglasAplicadas.append(" 27");

                Token oprel = emparejar(Token.OPREL);
                EType eExpr = Expr();
                
                if(eExpr.tipo == tipoInt)
                {
                    // Los dos enteros
                    if(tipoH == tipoInt)
                        return new EType(tipoInt, ' ' + oprel.lexema + "i " + eExpr.trad);
                    // El anterior entero pero este real
                    if(tipoH == tipoDouble)
                        return new EType(tipoDouble, ' ' + oprel.lexema + "r " + eExpr.trad);
                }

                if(eExpr.tipo == tipoDouble)
                {
                    // El anterior real pero este entero
                    if(tipoH == tipoInt)
                        return new EType(tipoDouble, ' ' + oprel.lexema + "r itor(" + eExpr.trad + ')');
                    // Los dos reales
                    if(tipoH == tipoDouble)
                        return new EType(tipoDouble, ' ' + oprel.lexema + "r " + eExpr.trad);
                }

                break;

            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
                reglasAplicadas.append(" 28");

                return null;
                
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
     
        return null;
    }

    private final EType Expr()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:
                reglasAplicadas.append(" 29");

                EType eTerm = Term();
                EType eExprp = Exprp(eTerm.tipo);
                
                // Todos los Expr son Int
                if(eExprp.tipo == tipoInt)
                    return new EType(tipoInt, eTerm.trad + eExprp.trad);

                // Si hay algún Expr Double y este es double, operador Double
                if(eTerm.tipo == tipoDouble)
                    return new EType(tipoDouble, eTerm.trad + eExprp.trad);

                // Si hay algún Expr Double y este es Int, operador Double y casteo
                if(eTerm.tipo == tipoInt)
                    return new EType(tipoDouble, "itor(" + eTerm.trad + ')' + eExprp.trad);
            
                
                break;
                
            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }

        return null;
    }

    private final EType Exprp(int tipoH)
    {
        switch(token.tipo)
        {
            case Token.OPAS:
            {
                reglasAplicadas.append(" 30");

                Token opas = emparejar(Token.OPAS);
                EType eTerm = Term();

                // Si hasta ahora tengo int, el tipo dependerá del eFactor (si es int sigue, si es double cambia)
                if(tipoH == tipoInt)
                    tipoH = eTerm.tipo;
                
                EType eExprp = Exprp(tipoH);
                
                // Todos los Expr son Int
                if(eExprp.tipo == tipoInt)
                    return new EType(tipoInt, ' ' + opas.lexema + "i " + eTerm.trad + eExprp.trad);

                // Si hay algún Expr Double y este es double, operador Double
                if(eTerm.tipo == tipoDouble)
                    return new EType(tipoDouble, ' ' + opas.lexema + "r " + eTerm.trad + eExprp.trad);

                // Si hay algún Expr Double y este es Int, operador Double y casteo
                if(eTerm.tipo == tipoInt)
                    return new EType(tipoDouble, ' ' + opas.lexema + "r itor(" + eTerm.trad + ')' + eExprp.trad);
            

            }
            
            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
            case Token.OPREL:
                reglasAplicadas.append(" 31");

                return new EType(tipoH, "");

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
     
        return null;
    }

    private final EType Term()
    {
        switch(token.tipo)
        {
            case Token.ID:
            case Token.NENTERO:
            case Token.NREAL:
            case Token.PARI:

                reglasAplicadas.append(" 32");

                EType eFactor = Factor();
                EType eTermp = Termp(eFactor.tipo);
                
                // Todos los Term son Int
                if(eTermp.tipo == tipoInt)
                    return new EType(tipoInt, eFactor.trad + eTermp.trad);

                // Si hay algún Term Double y este es double, operador Double
                if(eFactor.tipo == tipoDouble)
                    return new EType(tipoDouble, eFactor.trad + eTermp.trad);

                // Si hay algún Term Double y este es Int, operador Double y casteo
                if(eFactor.tipo == tipoInt)
                    return new EType(tipoDouble, "itor(" + eFactor.trad + ')' + eTermp.trad);
            

                break;

            default: 
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }

        return null;
    }

    private final EType Termp(int tipoH)
    {
        switch(token.tipo)
        {
            case Token.OPMD:
            {
                reglasAplicadas.append(" 33");

                Token opmd = emparejar(Token.OPMD);
                EType eFactor = Factor();

                // Si hasta ahora tengo int, el tipo dependerá del eFactor (si es int sigue, si es double cambia)
                if(tipoH == tipoInt)
                    tipoH = eFactor.tipo;
                
                // Se trata de operación Double y se traduce a /r
                if(opmd.lexema == "/")
                    tipoH = tipoDouble;
                
                EType eTermp = Termp(tipoH);
                
                if(opmd.lexema == "//")
                {
                    // Debe ser todo tipo int y se traduce a /i
                    if(tipoH != tipoInt || eTermp.tipo != tipoInt)
                        errorSemantico(ERR_DIVENTERA, opmd.fila, opmd.columna, opmd.lexema);
                    
                    opmd.lexema = "/";
                }

                // Todos los Term son Int
                if(eTermp.tipo == tipoInt)
                    return new EType(tipoInt, ' ' + opmd.lexema + "i " + eFactor.trad + eTermp.trad);

                // Si hay algún Term Double y este es double, operador Double
                if(eFactor.tipo == tipoDouble)
                    return new EType(tipoDouble, ' ' + opmd.lexema + "r " + eFactor.trad + eTermp.trad);

                // Si hay algún Term Double y este es Int, operador Double y casteo
                if(eFactor.tipo == tipoInt)
                    return new EType(tipoDouble, ' ' + opmd.lexema + "r itor(" + eFactor.trad + ')' + eTermp.trad);
            
            }
            
            case Token.PYC:
            case Token.FSI:
            case Token.SINO:
            case Token.FBLQ:
            case Token.ENTONCES:
            case Token.HACER:
            case Token.PARD:
            case Token.OPREL:
            case Token.OPAS:
            {
                reglasAplicadas.append(" 34");
                
                return new EType(tipoH, "");
            }

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
    
        return null;
    }

    private final EType Factor()
    {
        switch(token.tipo)
        {
            case Token.ID:
            {
                reglasAplicadas.append(" 35");
                
                Token id = emparejar(Token.ID);
                Simbolo idSimbolo = tsActual.buscar(id.lexema);

                // Si el nombre no existe
                if(idSimbolo == null)
                    errorSemantico(ERR_NO_DECL, id.fila, id.columna, id.lexema);
                
                // Si el nombre corresponde a una función
                if(idSimbolo.tipo == Simbolo.FUNCION)
                    errorSemantico(ERR_NO_VARIABLE, id.fila, id.columna, id.lexema);
                
                return new EType((idSimbolo.tipo == Simbolo.ENTERO) ? tipoInt : tipoDouble, idSimbolo.nombreCompleto);
            }
            
            case Token.NENTERO:
            {
                reglasAplicadas.append(" 36");

                Token entero = emparejar(Token.NENTERO);

                return new EType(tipoInt, entero.lexema);
            }
            
            case Token.NREAL:
            {
                reglasAplicadas.append(" 37");

                Token real = emparejar(Token.NREAL);

                return new EType(tipoDouble, real.lexema);
            }

            case Token.PARI:
            {
                reglasAplicadas.append(" 38");

                emparejar(Token.PARI);
                EType expr = Expr();
                emparejar(Token.PARD);
                
                return new EType(expr.tipo, '(' + expr.trad + ')');
            }

            default: 
            terminosEsperados.add(Token.NREAL);
            terminosEsperados.add(Token.ID);
            terminosEsperados.add(Token.NENTERO);
            terminosEsperados.add(Token.PARI);
            errorSintaxis();
        }
     
        return null;
    }
}