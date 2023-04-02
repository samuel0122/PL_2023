import java.io.EOFException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.HashMap;
// import java.util.HashSet;

// import javax.lang.model.util.ElementScanner14;


public class AnalizadorLexico
{
    private static HashMap<String, Integer> palabrasReservadas = new HashMap<>();

    private RandomAccessFile fileReading;

    private long filePosition;
    private int currentRow, currentColumn;
    
    private static final char EOF = (char) -1;

    private static final int 
        initialState    = 0,
        commentaryLoop  = 2,
        endingComentary = 3,
        endComentary    = 4,
        errorEOF        = -5,
        errorClass      = -6;


    static{
        palabrasReservadas.put("var", Token.VAR);
		palabrasReservadas.put("real", Token.REAL);
		palabrasReservadas.put("entero", Token.ENTERO);
		palabrasReservadas.put("algoritmo", Token.ALGORITMO);
		palabrasReservadas.put("blq", Token.BLQ);
		palabrasReservadas.put("fblq", Token.FBLQ);
		palabrasReservadas.put("si", Token.SI);
		palabrasReservadas.put("entonces", Token.ENTONCES);
		palabrasReservadas.put("fsi", Token.FSI);
		palabrasReservadas.put("mientras", Token.MIENTRAS);
		palabrasReservadas.put("hacer", Token.HACER);
		palabrasReservadas.put("escribir", Token.ESCRIBIR);
    }

    public AnalizadorLexico(RandomAccessFile entrada){
        currentColumn = currentRow = 1;
        filePosition = 0;
        fileReading = entrada;
    }
    
    private void retrocederLectura() throws IOException{
        --filePosition;
        --currentColumn;
        fileReading.seek(filePosition);
        
    }

    private char leerCaracter(){
        char currentChar = ' ';

        ++filePosition;

        try 
        {
            currentChar = (char) fileReading.readByte();
        } 
        catch (EOFException e) 
        {
            return EOF;
        } 
        catch (IOException e) 
        {
        }

        return currentChar;
    }

    private boolean isFinal(int estado){
        switch(estado){
            case 6:
            case 8:
            case 10:
            case 12:
            case 15:
            case 16:
            case 17:
            case 20:

            case 5:
            case 9:
            case 14:
            case 19:
            case 22:
            case 25:
            case 27:
            case 28:
            case 29: return true;
        }

        return false;
    }

    private int retrocesos(int estado){
        switch(estado){
            case 6:
            case 8:
            case 10:
            case 12:
            case 15:
            case 16:
            case 17:
            case 20: return 0;

            case 5:
            case 9:
            case 14:
            case 19:
            case 22:
            case 25:
            case 27:
            case 28: return 1;

            case 29: return 2;
        }

        return 0;
    }

    private int tokenClass(int estado, String palabra){
        switch(estado){
            case 5:  return Token.PARI;
            case 6:  return Token.PARD;
            case 10: return Token.OPAS;
            case 16: return Token.PYC;
            case 19: return Token.DOSP;
            case 20: return Token.ASIG;
            case 22:
            case 29: return Token.NENTERO;
            case 25: return Token.NREAL;
            case 27:
                if(palabrasReservadas.containsKey(palabra)) 
                {
                    return palabrasReservadas.get(palabra);
                }
                else
                {
                    return Token.ID;
                }
            case 28: return Token.EOF;
        }

        return -1;
    }

    private int delta(int estado, char caracter){

        if(caracter >= 'a' && caracter <= 'z' || caracter >= 'A' && caracter <= 'Z')
        {
            // Case lower & upper
            switch(estado){
                case 0:  return 26;
                case 26: return 26;
            }

        }
        else if(caracter >= '0' && caracter <= '9')
        {
            // Case digit
            switch(estado){
                case 0:  return 21;
                case 21: return 21;
                case 23: return 24;
                case 24: return 24;
                case 26: return 26;
            }
        
        }
        else
        {
            switch(caracter){
                case '(':
                    switch(estado){
                        case 0: return 1;
                    }
                break;
                
                case ')':
                    switch(estado){
                        case 0: return 6;
                        case endingComentary:   return endComentary;
                    }
                break;

                case '*':
                    switch(estado){
                        case 0: return errorClass;
                        case 1: return commentaryLoop;
                        case commentaryLoop:    return endingComentary;
                        case endingComentary:   return endingComentary;
                    }
                break;

                case '/':
                    switch(estado){
                        case 0: return errorClass;
                        //case 7: return 8;
                    }
                break;

                case '+':
                    switch(estado){
                        case 0: return 10;
                    }
                break;

                case '-':
                    switch(estado){
                        case 0: return 10;
                    }
                break;

                case '<':
                    switch(estado){
                        case 0: return errorClass;
                    }
                break;

                case '>':
                    switch(estado){
                        case 0:  return errorClass;
                        //case 11: return 12;
                    }
                break;

                case '=':
                    switch(estado){
                        //case 0:  return 15;
                        case 11: return 12;
                        case 13: return 12;
                        case 18: return 20;
                    }
                break;

                case ';':
                    switch(estado){
                        case 0: return 16;
                    }
                break;

                case ',':
                    switch(estado){
                        case 0: return errorClass;
                    }
                break;

                case ':':
                    switch(estado){
                        case 0: return 18;
                    }
                break;

                case '.':
                    switch(estado){
                        case 0:  return errorClass;
                        case 21: return 23;
                    }
                break;

                case '\n':
                case ' ':
                case '\t':
                    switch(estado){
                        case 0: return 0;
                    }
            }
        }

        //Case otro caracter [oc]
        if(caracter != EOF)
        {
            switch(estado){
                case 2:  return 2;
                case 3:  return 2;
                case 23: return 29;
            }
        }
        else
        {
            switch(estado){
                case 0: return 28;
            }
        }
            
        //Case otro [o]
        switch(estado){
            case 1:  return 5;
            case 7:  return 9;
            case 11: return 14;
            case 13: return 14;
            case 18: return 19;
            case 21: return 22;
            case 24: return 25;
            case 26: return 27;
        }

        // Cases ERROR
        if(caracter == EOF)
        {
            // Case EOF error
            switch(estado){
                case 2:  return errorEOF;
                case 3:  return errorEOF;
                case 23: return errorEOF;
            }
        }
        else
        {
            // Case NOT EOF error
            switch(estado){
                case 23: return errorClass;    // Sin clase
            }
        }

        //if(estado == initialState) return initialState;

        return -1;
    }

    private void checkError(int nuevoEstado, char c){
        if(nuevoEstado == errorEOF)
        {
            // System.err("Error lexico: fin de fichero inesperado");
            System.err.println("Error lexico: fin de fichero inesperado");
            System.exit(-1);
        } 
        
        if(nuevoEstado == errorClass)
        {
            // System.err("Error lexico (" + nuevoToken.fila + ',' + nuevoToken.columna + "): caracter '" + c + "' incorrecto");
            System.err.printf("Error lexico (%d,%d): caracter '%s' incorrecto%n", currentRow, currentColumn, c);
            //System.err.println("Error lexico (" + currentRow + ',' + (currentColumn-1) + "): caracter '" + c + "' incorrecto");
            System.exit(-1);
        }

    }


    public Token siguienteToken(){
        char c, previousC;
        int estado, nuevoEstado;

        StringBuilder palabra = new StringBuilder();
        Token nuevoToken = new Token();

        nuevoToken.columna = currentColumn;
        nuevoToken.fila = currentRow;
        nuevoToken.tipo = Token.EOF;

        nuevoEstado = estado = initialState;

        // algoritmo de análisis léxico
        try {
            previousC = c = leerCaracter();
            
            do
            {
                nuevoEstado = delta(estado, c);

                if(previousC == ' ') previousC = c;
    
                // ERROR
                checkError(nuevoEstado, c);
                
                ++currentColumn;

                // Ignore comentary
                if(nuevoEstado == endComentary)
                {
                    nuevoEstado = initialState;
                    palabra.setLength(0);
                    nuevoToken.columna = currentColumn;
                    nuevoToken.fila = currentRow;
                }
                else if(nuevoEstado == -1)
                {
                    System.out.println("ERROR INESPERADO");
                    System.exit(-1);
                }

                if(nuevoEstado != initialState && nuevoEstado != commentaryLoop && nuevoEstado != endingComentary) 
                {
                    // Ignore if initial state (no token started)
                    palabra.append(c);
                }
                else if(c == '\n')
                {
                    nuevoToken.columna = 1;
                    ++nuevoToken.fila;
            
                    // If state 0 & '\n', go to next line
                    currentColumn = 1;
                    ++currentRow;
                }
                else if(c == ' ' || c == '\t')
                {
                    ++nuevoToken.columna;
                }

                // Check final
                if(isFinal(nuevoEstado))
                {
                    int numberRetrocesos = retrocesos(nuevoEstado);
                    
                    for(int i = 0; i < numberRetrocesos; ++i) retrocederLectura();

                    palabra.setLength(palabra.length() - numberRetrocesos);
                    break;
                } 

                estado = nuevoEstado;
                previousC = c;
                c = leerCaracter();
                
            } while (true);

        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }
        
        nuevoToken.lexema = palabra.toString();
        nuevoToken.tipo = tokenClass(nuevoEstado, nuevoToken.lexema);

        return nuevoToken;
    }
}