import java.util.TreeSet;

import javax.lang.model.util.ElementScanner6;

import java.sql.Struct;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;


public class AnalizadorSintacticoSLR
{
    private Token token;
    private AnalizadorLexico lexico;
    private Deque<Integer> pilaInstrucciones;
    private Deque<Integer> reglasAplicadas;

    enum Rule
    {
        ruleS,
        ruleVsp,
        ruleUnsp,
        ruleLV,
        ruleV,
        ruleTipo,
        ruleBloque,
        ruleSInstr,
        ruleInstr,
        ruleE,
        ruleFactor,
        ERROR
    };

    class NextAction
    {
        public NextAction(ActionType actionType, int nextState) 
        {
            this.actionType = actionType; 
            this.nextState = nextState; 
        }

        public ActionType actionType;
        public int nextState;
    };

    enum ActionType
    {
        dType,
        rType,
        acceptType,
        errorType,
    };

    final int 
        errorState  = -1;

    // Constructor
    public AnalizadorSintacticoSLR(AnalizadorLexico lexico)
    {
        this.lexico = lexico;
        //this.token = lexico.siguienteToken();
        this.reglasAplicadas = new ArrayDeque<>();
        this.pilaInstrucciones = new ArrayDeque<>();
    }
    
    // Functiones de impresión
    private void imprimirReglas()
    {
        Iterator<Integer> it = reglasAplicadas.descendingIterator();
        StringBuilder reglaStringBuilder = new StringBuilder();
        
        // Primera regla
        if(it.hasNext())
            reglaStringBuilder.append(it.next());

        // Concatena el resto de reglas
        while(it.hasNext()) 
            reglaStringBuilder.append(' ' + it.next().toString());

        // Imprime reglas
        System.out.println(reglaStringBuilder.toString());
    }

    private void errorSintaxis(int ... args)
    {
        TreeSet<Integer> terminosEsperados = new TreeSet<Integer>();
        StringBuilder argsEsperados = new StringBuilder();

        // Crear tree of tokens
        for(int tokEsperado:args) terminosEsperados.add(tokEsperado);

        // Crear listado de tokens ordenados
        for(int tokEsperado: terminosEsperados) argsEsperados.append(" " + Token.nombreToken.get(tokEsperado));

        // Comprobar tipo de error
        if(token.tipo == Token.EOF)
            System.err.printf("Error sintactico: encontrado fin de fichero, esperaba%s%n", argsEsperados.toString());
        else
            System.err.printf("Error sintactico (%d,%d): encontrado '%s', esperaba%s%n", token.fila, token.columna, token.lexema, argsEsperados.toString());
        
        System.exit(-1);
    }

    // Funciones de navegación entre estados
    private final NextAction getNextAction(int estado, Token token)
    {
        switch (estado)
        {
            case 0:
                if(token.tipo == Token.ALGORITMO) return new NextAction(ActionType.dType, 2);
                errorSintaxis(Token.ALGORITMO);
                break;
            case 1:
                if(token.tipo == Token.EOF) return new NextAction(ActionType.acceptType, 0);
                errorSintaxis(Token.EOF);
                break;
            case 2:
                if(token.tipo == Token.ID)  return new NextAction(ActionType.dType, 3);
                errorSintaxis(Token.ID);
                break;
            case 3: 
                if(token.tipo == Token.PYC) return new NextAction(ActionType.dType, 4);
                errorSintaxis(Token.PYC);
                break;
            case 4: 
                if(token.tipo == Token.VAR) return new NextAction(ActionType.dType, 7);
                errorSintaxis(Token.VAR);
                break;
            case 5: 
                if(token.tipo == Token.VAR) return new NextAction(ActionType.dType, 7);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.dType, 9);
                errorSintaxis(Token.VAR, Token.BLQ);
                break;
            case 6: 
                if(token.tipo == Token.VAR) return new NextAction(ActionType.rType, 3);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.rType, 3);
                errorSintaxis(Token.VAR, Token.BLQ);
                break;
            case 7: 
                if(token.tipo == Token.ID)  return new NextAction(ActionType.dType, 10);
                errorSintaxis(Token.ID);
                break;
            case 8: 
                if(token.tipo == Token.EOF) return new NextAction(ActionType.rType, 1);
                errorSintaxis(Token.EOF);
                break;
            case 9: 
                if(token.tipo == Token.ID)       return new NextAction(ActionType.dType, 21);
                if(token.tipo == Token.BLQ)      return new NextAction(ActionType.dType, 9 );
                if(token.tipo == Token.SI)       return new NextAction(ActionType.dType, 22);
                if(token.tipo == Token.MIENTRAS) return new NextAction(ActionType.dType, 23);
                if(token.tipo == Token.ESCRIBIR) return new NextAction(ActionType.dType, 24);
                errorSintaxis(Token.ID, Token.BLQ, Token.SI, Token.MIENTRAS, Token.ESCRIBIR);
                break;
            case 10:
                if(token.tipo == Token.DOSP)   return new NextAction(ActionType.dType, 11);
                errorSintaxis(Token.DOSP);
                break;
            case 11:
                if(token.tipo == Token.ENTERO) return new NextAction(ActionType.dType, 13);
                if(token.tipo == Token.REAL)   return new NextAction(ActionType.dType, 12);
                errorSintaxis(Token.ENTERO, Token.REAL);
                break;
            case 12:
                if(token.tipo == Token.PYC) return new NextAction(ActionType.rType, 9);
                errorSintaxis(Token.PYC);
                break;
            case 13:
                if(token.tipo == Token.PYC) return new NextAction(ActionType.rType, 8);
                errorSintaxis(Token.PYC);
                break;
            case 14:
                if(token.tipo == Token.PYC) return new NextAction(ActionType.dType, 15);
                errorSintaxis(Token.PYC);
                break;
            case 15:
                if(token.tipo == Token.ID)  return new NextAction(ActionType.rType, 7);
                if(token.tipo == Token.VAR) return new NextAction(ActionType.rType, 7);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.rType, 7);
                errorSintaxis(Token.ID, Token.VAR, Token.BLQ);
                break;
            case 16:
                if(token.tipo == Token.ID)  return new NextAction(ActionType.dType, 10);
                if(token.tipo == Token.VAR) return new NextAction(ActionType.rType, 4);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.rType, 4);
                errorSintaxis(Token.ID, Token.VAR, Token.BLQ);
                break;
            case 17:
                if(token.tipo == Token.ID)  return new NextAction(ActionType.rType, 6);
                if(token.tipo == Token.VAR) return new NextAction(ActionType.rType, 6);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.rType, 6);
                errorSintaxis(Token.ID, Token.VAR, Token.BLQ);
                break;
            case 18:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.dType, 26);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.dType, 25);
                errorSintaxis(Token.PYC, Token.FBLQ);
                break;
            case 19:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 12);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 12);
                errorSintaxis(Token.PYC, Token.FBLQ);
                break;
            case 20:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 13);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 13);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 13);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI);
                break;
            case 21:
                if(token.tipo == Token.ASIG) return new NextAction(ActionType.dType, 28);
                errorSintaxis(Token.ASIG);
                break;
            case 22:
                if(token.tipo == Token.ID)      return new NextAction(ActionType.dType, 29);
                if(token.tipo == Token.NENTERO) return new NextAction(ActionType.dType, 30);
                if(token.tipo == Token.NREAL)   return new NextAction(ActionType.dType, 31);
                errorSintaxis(Token.ID, Token.NENTERO, Token.NREAL);
                break;
            case 23:
                if(token.tipo == Token.ID)      return new NextAction(ActionType.dType, 29);
                if(token.tipo == Token.NENTERO) return new NextAction(ActionType.dType, 30);
                if(token.tipo == Token.NREAL)   return new NextAction(ActionType.dType, 31);
                errorSintaxis(Token.ID, Token.NENTERO, Token.NREAL);
                break;
            case 24:
                if(token.tipo == Token.PARI)    return new NextAction(ActionType.dType, 43);
                errorSintaxis(Token.PARI);
                break;
            case 25:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 10);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 10);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 10);
                if(token.tipo == Token.EOF)  return new NextAction(ActionType.rType, 10);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI, Token.EOF);
                break;
            case 26:
                if(token.tipo == Token.ID)       return  new NextAction(ActionType.dType, 21);
                if(token.tipo == Token.BLQ)      return  new NextAction(ActionType.dType, 9 );
                if(token.tipo == Token.SI)       return  new NextAction(ActionType.dType, 22);
                if(token.tipo == Token.MIENTRAS) return  new NextAction(ActionType.dType, 23);
                if(token.tipo == Token.ESCRIBIR) return  new NextAction(ActionType.dType, 24);
                errorSintaxis(Token.ID, Token.BLQ, Token.SI, Token.MIENTRAS, Token.ESCRIBIR);
                break;
            case 27:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 11);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 11);
                errorSintaxis(Token.PYC, Token.FBLQ);
                break;
            case 28:
                if(token.tipo == Token.ID)      return new NextAction(ActionType.dType, 29);
                if(token.tipo == Token.NENTERO) return new NextAction(ActionType.dType, 30);
                if(token.tipo == Token.NREAL)   return new NextAction(ActionType.dType, 31);
                errorSintaxis(Token.ID, Token.NENTERO, Token.NREAL);
                break;
            case 29:
                if(token.tipo == Token.PYC)      return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.FBLQ)     return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.FSI)      return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.HACER)    return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.PARD)     return new NextAction(ActionType.rType, 20);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.rType, 20);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.ENTONCES, Token.FSI, Token.HACER, Token.PARD, Token.OPAS);
                break;
            case 30:
                if(token.tipo == Token.PYC)      return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.FBLQ)     return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.FSI)      return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.HACER)    return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.PARD)     return new NextAction(ActionType.rType, 21);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.rType, 21);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.ENTONCES, Token.FSI, Token.HACER, Token.PARD, Token.OPAS);
                break;
            case 31:
                if(token.tipo == Token.PYC)      return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.FBLQ)     return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.FSI)      return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.HACER)    return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.PARD)     return new NextAction(ActionType.rType, 22);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.rType, 22);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.ENTONCES, Token.FSI, Token.HACER, Token.PARD, Token.OPAS);
                break;
            case 32:
                if(token.tipo == Token.PYC)      return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.FBLQ)     return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.FSI)      return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.HACER)    return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.PARD)     return new NextAction(ActionType.rType, 19);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.rType, 19);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.ENTONCES, Token.FSI, Token.HACER, Token.PARD, Token.OPAS);
                break;
            case 33:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 14);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 14);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 14);
                if(token.tipo == Token.OPAS) return new NextAction(ActionType.dType, 34);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI, Token.OPAS);
                break;
            case 34:
                if(token.tipo == Token.ID)      return new NextAction(ActionType.dType, 29);
                if(token.tipo == Token.NENTERO) return new NextAction(ActionType.dType, 30);
                if(token.tipo == Token.NREAL)   return new NextAction(ActionType.dType, 31);
                errorSintaxis(Token.ID, Token.NENTERO, Token.NREAL);
                break;
            case 35:
                if(token.tipo == Token.PYC)      return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.FBLQ)     return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.FSI)      return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.HACER)    return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.PARD)     return new NextAction(ActionType.rType, 18);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.rType, 18);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.ENTONCES, Token.FSI, Token.HACER, Token.PARD, Token.OPAS);
                break;
            case 36:
                if(token.tipo == Token.ENTONCES) return new NextAction(ActionType.dType, 37);
                if(token.tipo == Token.OPAS)     return new NextAction(ActionType.dType, 34);
                errorSintaxis(Token.ENTONCES, Token.OPAS);
                break;
            case 37:
                if(token.tipo == Token.ID)       return new NextAction(ActionType.dType, 21);
                if(token.tipo == Token.BLQ)      return new NextAction(ActionType.dType, 9 );
                if(token.tipo == Token.SI)       return new NextAction(ActionType.dType, 22);
                if(token.tipo == Token.MIENTRAS) return new NextAction(ActionType.dType, 23);
                if(token.tipo == Token.ESCRIBIR) return new NextAction(ActionType.dType, 24);
                errorSintaxis(Token.ID, Token.BLQ, Token.SI, Token.MIENTRAS, Token.ESCRIBIR);
                break;
            case 38:
                if(token.tipo == Token.FSI) return new NextAction(ActionType.dType, 39);
                errorSintaxis(Token.FSI);
                break;
            case 39:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 15);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 15);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 15);    
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI);
                break;
            case 40:
                if(token.tipo == Token.HACER) return new NextAction(ActionType.dType, 41);
                if(token.tipo == Token.OPAS)  return new NextAction(ActionType.dType, 34);
                errorSintaxis(Token.HACER, Token.OPAS);
                break;
            case 41:
                if(token.tipo == Token.ID)       return new NextAction(ActionType.dType, 21);
                if(token.tipo == Token.BLQ)      return new NextAction(ActionType.dType, 9 );
                if(token.tipo == Token.SI)       return new NextAction(ActionType.dType, 22);
                if(token.tipo == Token.MIENTRAS) return new NextAction(ActionType.dType, 23);
                if(token.tipo == Token.ESCRIBIR) return new NextAction(ActionType.dType, 24);
                errorSintaxis(Token.ID, Token.BLQ, Token.SI, Token.MIENTRAS, Token.ESCRIBIR);
                break;
            case 42:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 16);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 16);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 16);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI);
                break;
            case 43:
                if(token.tipo == Token.ID)      return new NextAction(ActionType.dType, 29);
                if(token.tipo == Token.NENTERO) return new NextAction(ActionType.dType, 30);
                if(token.tipo == Token.NREAL)   return new NextAction(ActionType.dType, 31);
                errorSintaxis(Token.ID, Token.NENTERO, Token.NREAL);
                break;
            case 44:
                if(token.tipo == Token.PARD) return new NextAction(ActionType.dType, 45);
                if(token.tipo == Token.OPAS) return new NextAction(ActionType.dType, 34);
                errorSintaxis(Token.PARD, Token.OPAS);
                break;
            case 45:
                if(token.tipo == Token.PYC)  return new NextAction(ActionType.rType, 17);
                if(token.tipo == Token.FBLQ) return new NextAction(ActionType.rType, 17);
                if(token.tipo == Token.FSI)  return new NextAction(ActionType.rType, 17);
                errorSintaxis(Token.PYC, Token.FBLQ, Token.FSI);
                break;
            case 46:
                if(token.tipo == Token.ID)   return new NextAction(ActionType.rType, 5);
                if(token.tipo == Token.VAR)  return new NextAction(ActionType.rType, 5);
                if(token.tipo == Token.BLQ)  return new NextAction(ActionType.rType, 5);
                errorSintaxis(Token.ID, Token.VAR, Token.BLQ);
                break;
            case 47:
                if(token.tipo == Token.VAR) return new NextAction(ActionType.rType, 2);
                if(token.tipo == Token.BLQ) return new NextAction(ActionType.rType, 2);
                errorSintaxis(Token.VAR, Token.BLQ);
                break;
        }
        
        return new NextAction(ActionType.errorType, errorState);
    }

    private final int getRightSizeFromRule(int rule)
    {
        switch(rule)
        {
            case 1:  return 5;
            case 2:  return 2;
            case 3:  return 1;
            case 4:  return 2;
            case 5:  return 2;
            case 6:  return 1;
            case 7:  return 4;
            case 8:  return 1;
            case 9:  return 1;
            case 10: return 3;
            case 11: return 3;
            case 12: return 1;
            case 13: return 1;
            case 14: return 3;
            case 15: return 5;
            case 16: return 4;
            case 17: return 4;
            case 18: return 3;
            case 19: return 1;
            case 20: return 1;
            case 21: return 1;
            case 22: return 1;
        } 
        return -1;
    } 

    private final Rule getLeftPartFromRule(int rule)
    {
        switch(rule)
        {
            case 1:  return Rule.ruleS;
            case 2:  
            case 3:  return Rule.ruleVsp;
            case 4:  return Rule.ruleUnsp;
            case 5:  
            case 6:  return Rule.ruleLV;
            case 7:  return Rule.ruleV;
            case 8:  
            case 9:  return Rule.ruleTipo;
            case 10: return Rule.ruleBloque;
            case 11: 
            case 12: return Rule.ruleSInstr;
            case 13: 
            case 14: 
            case 15: 
            case 16: 
            case 17: return Rule.ruleInstr;
            case 18: 
            case 19: return Rule.ruleE;
            case 20: 
            case 21: 
            case 22: return Rule.ruleFactor;
        } 
        return Rule.ERROR;
    } 

    private final int lr_A(int state, Rule leftKRule)
    {
        switch(leftKRule)
        {
            case ruleS:
                if(state == 0) return 1;
                break;
            case ruleVsp:
                if(state == 4) return 5;
                break;
            case ruleUnsp:
                if(state == 4) return 6;
                if(state == 5) return 47;
                break;
            case ruleLV:
                if(state == 7) return 16;
                break;
            case ruleV:
                if(state == 7)  return 17;
                if(state == 16) return 46;
                break;
            case ruleTipo:
                if(state == 11) return 14;
                break;
            case ruleBloque:
                if(state == 5)  return 8;
                if(state == 9)  return 20;
                if(state == 26) return 20;
                if(state == 37) return 20;
                if(state == 41) return 20;
                break;
            case ruleSInstr:
                if(state == 9)  return 18;
                break;
            case ruleInstr:
                if(state == 9)  return 19;
                if(state == 26) return 27;
                if(state == 37) return 38;
                if(state == 41) return 42;
                break;
            case ruleE:
                if(state == 22) return 36;
                if(state == 23) return 40;
                if(state == 28) return 33;
                if(state == 43) return 44;
                break;
            case ruleFactor:
                if(state == 22) return 32;
                if(state == 23) return 32;
                if(state == 28) return 32;
                if(state == 34) return 35;
                if(state == 43) return 32;
                break;
            default:
                break;
            }
                    
        return errorState;
    }

    // Función analizar
    public final void analizar()
    {
        boolean endAnalisis = false;
        int lastDequeState, rightInstructionSize;

        Rule ruleCompleted;
        NextAction nextAction;

        pilaInstrucciones.addLast(0);
        token = lexico.siguienteToken();

        do{
            lastDequeState = pilaInstrucciones.getFirst();
            nextAction = getNextAction(lastDequeState, token);

            if(nextAction.actionType == ActionType.dType)
            {
                if(nextAction.nextState == errorState)
                {
                    System.err.printf("ERROR ESTADO: estado previo %d con token de tipo %s obtenido estado %d", lastDequeState, Token.nombreToken.get(token.tipo), nextAction.nextState);
                    System.exit(-1);
                }

                pilaInstrucciones.push(nextAction.nextState);
                token = lexico.siguienteToken();
            }
            else if(nextAction.actionType == ActionType.rType)
            {
                if(nextAction.nextState == errorState)
                {
                    System.err.printf("ERROR ESTADO: estado previo %d con token de tipo %s obtenido estado %d\n", lastDequeState, Token.nombreToken.get(token.tipo), nextAction.nextState);
                    System.exit(-1);
                }
                // Add R rule applied
                reglasAplicadas.add(nextAction.nextState);

                // Get size of rule
                rightInstructionSize = getRightSizeFromRule(nextAction.nextState);
                
                // Get type of rule compleated
                ruleCompleted = getLeftPartFromRule(nextAction.nextState);
                
                // Remove all right elements
                for(int removeIt = 0; removeIt < rightInstructionSize; ++removeIt) pilaInstrucciones.pop();
                
                // Get the new last state
                lastDequeState = pilaInstrucciones.getFirst();

                // Adds the state where we go with the last state and the instruction completed
                pilaInstrucciones.push(lr_A(lastDequeState, ruleCompleted));

            }
            else if(nextAction.actionType == ActionType.acceptType)
            {
                endAnalisis = true;
            }
            else
            {
                System.err.println("AQUI NO DEBERÍA LLEGAR");
                System.exit(-1);
            }
        } while(!endAnalisis);

        imprimirReglas();
    }
}