import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Vector;

public class test {

    static public class TestClass
    {
        public void recursivoVector(Vector<Integer> vector, Integer iter)
        {
            vector.add(iter);

            if(iter > 0)
                recursivoVector(vector, iter-1);
        }

        public void multipleArgs(int ... args)
        {
            for(int a:args) System.out.println(a);
        }

        public Integer integer;
    }

    private final int   ERR_YA_EXISTE   = 1,
                        ERR_NO_VARIABLE = 2,
                        ERR_NO_DECL     = 3,
                        ERR_NO_BOOL     = 4,
                        ERR_ASIG_REAL   = 5,
                        ERR_SIMIENTRAS  = 6,
                        ERR_DIVENTERA   = 7;

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

   

    public static void main(String[] args) {
        TestClass test = new TestClass();

        Vector<Integer> vector = new Vector<>();
        test.recursivoVector(vector, 8);

        for(Integer it: vector)
            System.out.println(it);
    }
}
