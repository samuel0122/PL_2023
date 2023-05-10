/*------------------------------ ejemplo.y -------------------------------*/
%token pari pard opmd opas oprel
%token pyc dosp coma asig
%token var real entero
%token algoritmo blq fblq
%token funcion si entonces sino fsi
%token mientras hacer escribir
%token id nentero nreal


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TablaSimbolos.h"


using namespace std;

#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;

TablaSimbolos *tsActual = new TablaSimbolos(NULL);
Simbolo *simbolo;

vector<string> vVariablesId;


extern int yylex();
extern char *yytext;
extern FILE *yyin;


int yyerror(char *s);
void errorSemantico(int nerr,int fila,int columna,char *lexema);


const int ERR_YA_EXISTE   = 1,
          ERR_NO_VARIABLE = 2,
          ERR_NO_DECL     = 3,
          ERR_NO_BOOL     = 4,
          ERR_ASIG_REAL   = 5,
          ERR_SIMIENTRAS  = 6,
          ERR_DIVENTERA   = 7;

const int ENTERO  = 1,
          REAL    = 2,
          BOOLEAN = 3,
          FUNCION = 4;

string operador, s1, s2;  // string auxiliares
int tipo1, tipo2;

%}

%%


S     : algoritmo id pyc { $$.th = ""; } Vsp Bloque    { 
                                                         /* comprobar que después del programa no hay ningún token más */
                                                         int tk = yylex();
                                                         if (tk != 0) yyerror("");

                                                         s1 = "// " + string($1.lexema) + " " + string($2.lexema) + "\n";
                                                         s2 = $5.cod + "int main() " + $6.cod;

                                                         $$.cod = s1 + s2;
                                                         cout << ("// " + string($1.lexema) + " " + string($2.lexema) + "\n") << ($5.cod + "int main() " + $6.cod);
                                                      }
      ;


Vsp   : Vsp { $$.th = $0.th; } Unsp       {  s1 = $1.cod;
                                             s2 = $3.cod;
                                             $$.cod = s1 + s2;
                                          }
      | Unsp                              { $$.cod = $1.cod; } 
      ;

Unsp  : funcion id dosp Tipo pyc {  
                                    s1 = $0.th;             // TH
                                    s2 = string($2.lexema); // id.lexema
                                    $$.th = s1.empty() ? s2 : s1 + '_' + s2; // Nombre función
                                    
                                    if(!tsActual->nuevoSimbolo({s2, FUNCION, $$.th})) 
                                       errorSemantico(ERR_YA_EXISTE, $2.nlin, $2.ncol, $2.lexema);

                                    tsActual = new TablaSimbolos(tsActual);
                                    } Vsp Bloque pyc {  tsActual = tsActual->getAmbitoAnterior();
                                                         s1 = $7.cod;   // Vsp
                                                         s2 = $4.cod + ' ' + $6.th + " () " + $8.cod;  // Tipo nombreFuncion () Bloque
                                                         $$.cod = s1 + s2;
                                                      }
      | var {  $$.th = $0.th; } LV                    {  
                                                         $$.cod = $3.cod;
                                                      }
      ;

LV    :  LV { $$.th = $0.th; } V    { $$.cod = $1.cod + $3.cod; }
      |  V                          { $$.cod = $1.cod; }
      ;

V     :  {  vVariablesId.clear(); 
            s1 = $0.th;
            if(s1.empty()) s1 = "main";
            $$.th = s1 + '_'; } Lid dosp Tipo pyc  {  
                                                      for(string vars: vVariablesId)
                                                      {
                                                         simbolo = tsActual->buscar(vars);
                                                         if(simbolo == NULL) yyerror(NULL);
                                                         simbolo->tipo = $4.tipo;   // Tipo
                                                      }
                                                      $$.cod = $4.cod + " " + $2.cod + ";\n";   // Tipo Lid
                                                   }
      ;

Lid   :  Lid coma id    {  
                           s1 = $0.th;       // TH
                           s2 = string($3.lexema); //id

                           if(!tsActual->nuevoSimbolo({s2, -1, s1+s2}))
                              errorSemantico(ERR_YA_EXISTE, $3.nlin, $3.ncol, $3.lexema);
                           
                           vVariablesId.push_back(s2);
                           //$$.th  = s1;
                           $$.cod = $1.cod + ", " + (s1+s2);   //Lid, id
                        }
      |  id             { 
                           s1 = $0.th;
                           s2 = string($1.lexema);

                           if(!tsActual->nuevoSimbolo({s2, -1, s1+s2}))
                              errorSemantico(ERR_YA_EXISTE, $1.nlin, $1.ncol, $1.lexema);
                           
                           vVariablesId.push_back(s2);
                           //$$.th  = s1;
                           $$.cod = s1+s2; 
                        }
      ;

Tipo  : entero    {  $$.tipo = ENTERO;
                     $$.cod = "int";
                  }
      | real      {  $$.tipo = REAL;
                     $$.cod = "double";
                  }
      ;

Bloque: blq SInstr fblq { $$.cod = "{\n" + $2.cod + "}\n";
                        }
      ;

SInstr: SInstr pyc Instr   { $$.cod = $1.cod + $3.cod;
                           }
      | Instr              /* $$ = $1 */
      ;

Instr : Bloque          /* $$ = $1 */
      | id  {  simbolo = tsActual->buscar($1.lexema);
                                       
               if (simbolo == NULL)
                  errorSemantico(ERR_NO_DECL, $1.nlin, $1.ncol, $1.lexema);
               if (simbolo->tipo == FUNCION)
                  errorSemantico(ERR_NO_VARIABLE, $1.nlin, $1.ncol, $1.lexema);
            }  asig E               {  
                                       simbolo = tsActual->buscar($1.lexema);
                                       
                                       if (simbolo == NULL)
                                          errorSemantico(ERR_NO_DECL, $1.nlin, $1.ncol, $1.lexema);
                                       
                                       if ($4.tipo == BOOLEAN)
                                          errorSemantico(ERR_NO_BOOL, $3.nlin, $3.ncol, $3.lexema);
                                       
                                       s1 = simbolo->nomtrad;  // Nombre variable
                                       
                                       tipo1 = simbolo->tipo;
                                       tipo2 = $4.tipo;

                                       operador = "=";
                                       if (tipo1 != tipo2)
                                       {
                                          if (tipo1 == ENTERO) // Si id es ENTERO, E es REAL
                                             errorSemantico(ERR_ASIG_REAL, $1.nlin, $1.ncol, $1.lexema);
                                          
                                          s2 = "itor(" + $4.cod + ")";
                                          operador +="r";
                                       }
                                       else
                                       {
                                          s2 = $4.cod;
                                          operador += (tipo1 == REAL) ? "r" : "i";
                                       }

                                       $$.cod = s1 + " " + operador + " " + s2 + ";\n";   // id =i/r s2
                                    }
      | si E entonces Instr ColaIf  {  if ($2.tipo != BOOLEAN)
                                          errorSemantico(ERR_SIMIENTRAS, $1.nlin, $1.ncol, $1.lexema);

                                       $$.cod = "if (" + $2.cod + ")\n" + $4.cod + $5.cod;   // if (E) Instr ColaIf
                                    }
      | mientras E hacer Instr      {  if ($2.tipo != BOOLEAN)
                                          errorSemantico(ERR_SIMIENTRAS, $1.nlin, $1.ncol, $1.lexema);

                                       $$.cod = "while (" + $2.cod + ")\n" + $4.cod;      // while (E) Instr
                                    }
      | escribir pari E pard        {  if ($3.tipo == BOOLEAN)
                                          errorSemantico(ERR_NO_BOOL, $1.nlin, $1.ncol, $1.lexema);

                                       s1 = ($3.tipo == ENTERO) ? "%d" : "%g";
                                       $$.cod = "printf(\"" + s1 + "\\n\"," + $3.cod + ");\n";  // printf("%d/g \n", E)
                                    }
      ;

ColaIf: fsi             {  $$.cod = "";   }
      | sino Instr fsi  {  $$.cod = "else\n" + $2.cod;   }
      ;

E     : Expr oprel Expr {  if (!strcmp($2.lexema,"="))
                              operador = "==";
                           else if (!strcmp($2.lexema,"<>"))
                              operador = "!=";
                           else
                              operador = string($2.lexema);
                           
                           tipo1 = $1.tipo;
                           tipo2 = $3.tipo;

                           if (tipo1 != tipo2)
                           {
                              // Distintos tipos
                              s1 = (tipo1 == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                              s2 = (tipo2 == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                              operador +="r";
                           }
                           else
                           {
                              // Mismos tipos
                              s1 = $1.cod;
                              s2 = $3.cod;
                              operador += (tipo1 == REAL)  ? "r" : "i";
                           }
                           $$.cod = s1 + " " + operador + " " + s2;
                           $$.tipo = BOOLEAN;
                        }
      | Expr            /* $$ = $1 */
      ;

Expr  : Expr opas Term  {  operador = string($2.lexema);
                           
                           tipo1 = $1.tipo;
                           tipo2 = $3.tipo;

                           if (tipo1 != tipo2)
                           {
                              // Distintos tipos
                              s1 = (tipo1 == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                              s2 = (tipo2 == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                              operador += "r";
                              $$.tipo = REAL;
                           }
                           else
                           {
                              // Mismos tipos
                              s1 = $1.cod;
                              s2 = $3.cod;
                              operador += (tipo1 == REAL)  ? "r" : "i";
                              $$.tipo = tipo1;
                           }
                           $$.cod = s1 + " " + operador + " " + s2;
                        }
      | Term            /* $$ = $1 */
      ;

Term  : Term opmd Factor   {  if (!strcmp($2.lexema,"*"))
                                 operador = "*";
                              else 
                                 operador = "/";
   
                              tipo1 = $1.tipo;
                              tipo2 = $3.tipo;
   
                              if (tipo1 != tipo2)
                              {
                                 // Distintos tipos
                                 if (!strcmp($2.lexema,"//"))
                                    errorSemantico(ERR_DIVENTERA, $2.nlin, $2.ncol, $2.lexema); // ERROR SINTACTICO

                                 s1 = (tipo1 == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                                 s2 = (tipo2 == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                                 operador += "r";
                                 $$.tipo = REAL;
                              }
                              else
                              {
                                 // Los dos tipos son iguales

                                 if (!strcmp($2.lexema,"//") && tipo1 != ENTERO) // Si es una división entera y son numeros reales
                                    errorSemantico(ERR_DIVENTERA, $2.nlin, $2.ncol, $2.lexema); // ERROR SINTACTICO
                                 
                                 s1 = $1.cod;
                                 s2 = $3.cod;

                                 if (!strcmp($2.lexema,"/") && tipo1 == ENTERO)
                                 {
                                    // Si es una división real con numeros enteros
                                    s1 = "itor(" + s1 + ")";
                                    s2 = "itor(" + s2 + ")";
                                    operador += "r";
                                    $$.tipo = REAL;
                                 }
                                 else
                                 {
                                    operador += (tipo1 == REAL)  ? "r" : "i";
                                    $$.tipo = tipo1;
                                 }

                              }
                              $$.cod = s1 + " " + operador + " " + s2;
                           }
      | Factor             /* $$ = $1 */
      ;

Factor: id                 {  simbolo = tsActual->buscar($1.lexema);
                              
                              
                              if (simbolo == NULL)
                                 errorSemantico(ERR_NO_DECL, $1.nlin, $1.ncol, $1.lexema);
                              
                              if (simbolo->tipo == FUNCION)
                                 errorSemantico(ERR_NO_VARIABLE, $1.nlin, $1.ncol, $1.lexema);
                              
                              
                              $$.tipo = simbolo->tipo; // todas las variables son enteras
                              $$.cod  = simbolo->nomtrad;
                           }
      | nentero            {  $$.tipo = ENTERO;
                              $$.cod  = $1.lexema;
                           }
      | nreal              {  $$.tipo = REAL;
                              $$.cod  = $1.lexema;
                           }
      | pari Expr pard     {  $$.tipo = $2.tipo;
                              $$.cod  = '(' + $2.cod + ')';
                           }
      ;

%%

void errorSemantico(int nerr,int fila,int columna,char *lexema) 
{
        fprintf(stderr,"Error semantico (%d,%d): ",fila,columna);
        switch (nerr) {
	        	case ERR_YA_EXISTE:
	        		fprintf(stderr,"'%s' ya existe en este ambito\n",lexema);
	        		break;
			case ERR_NO_VARIABLE:
			        fprintf(stderr,"'%s' no es una variable\n",lexema);
				break;
			case ERR_NO_DECL:
				fprintf(stderr,"'%s' no ha sido declarado\n",lexema);
				break;
			case ERR_NO_BOOL:
			    	fprintf(stderr,"'%s' no admite expresiones booleanas\n",lexema);
				break;
			case ERR_ASIG_REAL:
			    	fprintf(stderr,"'%s' debe ser de tipo real\n",lexema);
				break;
			case ERR_SIMIENTRAS:
			    	fprintf(stderr,"en la instruccion '%s' la expresion debe ser relacional\n",lexema);
				break;
			case ERR_DIVENTERA:
			    	fprintf(stderr,"los dos operandos de '%s' deben ser enteros\n",lexema);
				break;
        }
	exit(-1);
}


void msgError(int nerror,int nlin,int ncol,const char *s)
{
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
     }
        
     exit(1);
}


int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,0,0,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    exit(-1);
    return -1;
}

int main(int argc,char *argv[])
{
    FILE *fent;
    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}
