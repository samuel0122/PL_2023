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

%}

%%


S     : algoritmo id pyc Vsp Bloque    { /* comprobar que después del programa no hay ningún token más */
                                          int tk = yylex();
                                          if (tk != 0) yyerror("");

                                          s1 = "// " + string($1.lexema) + " " + $2.lexema + "\n";
                                          s2 = $4.cod + "int main() " + $5.cod;

                                          cout << s1 + s2;
                                       }
      ;


Vsp   : Vsp Unsp        {  s1 = $1.cod;
                           s2 = $2.cod;
                           $$.cod = s1 + s2;
                        }
      | Unsp            /* $$ = $1 */
      ;

Unsp  : funcion id dosp Tipo pyc Vsp Bloque pyc {  
                                                }
      | var LV                                  {
                                                }
      ;

LV    : LV V
      | V
      ;

V     : Lid dosp Tipo pyc  {
                           }
      ;

Lid   : Lid coma id  {  
                     }
      | id           /* $$ = $1 */
      ;

Tipo  : entero    /* $$ = $1 */
      | real      /* $$ = $1 */
      ;

Bloque: blq SInstr fblq { $$.cod = "{\n" + $2.cod + "}\n";
                        }
      ;

SInstr: SInstr pyc Instr   { $$.cod = $1.cod + $2.cod;
                           }
      | Instr              /* $$ = $1 */
      ;

Instr : Bloque          /* $$ = $1 */
      | id asig E                   {  simbolo = tsActual.buscar($1.lexema);
                                       
                                       if (simbolo == NULL)
                                          errorSemantico(ERR_NO_DECL);
                                       if (simbolo.tipo == FUNCION)
                                          errorSemantico(ERR_NO_VARIABLE);
                                       if ($3.tipo == BOOLEAN)
                                          errorSemantico(ERR_NO_BOOL);
                                       
                                       operador = "=";
                                       if ($1.tipo != $3.tipo)
                                       {
                                          if ($1.tipo == ENTERO)
                                             errorSemantico(ERR_ASIG_REAL);
                                          
                                          s1 = $1.cod; 
                                          s2 = "itor(" + $3.cod + ")";
                                          operador +="r";
                                          $$.cod = s1 + " " + operador + " " + s2 + ";\n";
                                       }
                                       else
                                       {
                                          s1 = $1.cod;
                                          s2 = $3.cod;
                                          operador += ($1.tipo == REAL)  ? "r" : "i";
                                          $$.cod = s1 + " " + operador + " " + s2 + ";\n";
                                       }
                                    }
      | si E entonces Instr ColaIf  {  if ($2.tipo != BOOLEAN)
                                          errorSemantico(ERR_SIMIENTRAS);

                                       $$.cod = "if (" + $2.cod + ")\n" + $4.cod + $5.cod;
                                    }
      | mientras E hacer Instr      {  if ($2.tipo != BOOLEAN)
                                          errorSemantico(ERR_SIMIENTRAS);

                                       $$.cod = "while (" + $2.cod + ")\n" + $4.cod;
                                    }
      | escribir pari E pard        {  if ($2.tipo == BOOLEAN)
                                          errorSemantico(ERR_NO_BOOL);

                                       s1 = ($3.tipo == ENTERO) ? "%d" : "%g";
                                       $$.cod = "printf(\"" + s1 + "\\n\"," + $3.cod + ");\n";
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
                              operador.assign($2.lexema);
                           
                           if ($1.tipo != $3.tipo)
                           {
                              s1 = ($1.tipo == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                              s2 = ($3.tipo == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                              operador +="r";
                              $$.cod = s1 + " " + operador + " " + s2;
                           }
                           else
                           {
                              s1 = $1.cod;
                              s2 = $3.cod;
                              operador += ($1.tipo == REAL)  ? "r" : "i";
                              $$.cod = s1 + " " + operador + " " + s2;
                           }
                           $$.tipo = BOOLEAN;
                        }
      | Expr            /* $$ = $1 */
      ;

Expr  : Expr opas Term  {  operador.assign($2.lexema);
                           if ($1.tipo != $3.tipo)
                           {
                              s1 = ($1.tipo == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                              s2 = ($3.tipo == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                              operador +="r";
                              $$.tipo = REAL;
                              $$.cod = s1 + " " + operador + " " + s2;
                           }
                           else
                           {
                              s1 = $1.cod;
                              s2 = $3.cod;
                              operador += ($1.tipo == REAL)  ? "r" : "i";
                              $$.tipo = $1.tipo;
                              $$.cod = s1 + " " + operador + " " + s2;
                           }
                        }
      | Term            /* $$ = $1 */
      ;

Term  : Term opmd Factor   {  if (!strcmp($2.lexema,"*"))
                                 operador = "*";
                              else 
                                 operador = "/";
                              
                              if ($1.tipo != $3.tipo)
                              {
                                 if (!strcmp($2.lexema,"//"))
                                    errorSemantico(ERR_DIVENTERA) // ERROR SINTACTICO

                                 s1 = ($1.tipo == ENTERO) ? ("itor(" + $1.cod + ")") : $1.cod; 
                                 s2 = ($3.tipo == ENTERO) ? ("itor(" + $3.cod + ")") : $3.cod; 
                                 operador +="r";
                                 $$.tipo = REAL;
                                 $$.cod = s1 + " " + operador + " " + s2;
                              }
                              else
                              {
                                 if (!strcmp($2.lexema,"//") && $1.tipo != ENTERO)
                                    errorSemantico(ERR_DIVENTERA) // ERROR SINTACTICO
                                 
                                 s1 = $1.cod;
                                 s2 = $3.cod;
                                 operador += ($1.tipo == REAL)  ? "r" : "i";
                                 $$.tipo = $1.tipo;
                                 $$.cod = s1 + " " + operador + " " + s2;
                              }
                           }
      | Factor             /* $$ = $1 */
      ;

Factor: id                 {  simbolo = tsActual.buscar($1.lexema);
                                       
                              if (simbolo == NULL)
                                 errorSemantico(ERR_NO_DECL);
                              if (simbolo.tipo == FUNCION)
                                 errorSemantico(ERR_NO_VARIABLE);
                              
                              $$.tipo = simbolo.tipo; // todas las variables son enteras
                              $$.cod  = simbolo.nomtrad;
                           }
      | nentero            {  $$.tipo = ENTERO;
                              $$.cod  = $1.lexema;
                           }
      | nreal              {  $$.tipo = REAL;
                              $$.cod  = $1.lexema;
                           }
      | pari Exp pard      {  $$.tipo = $2.tipo;
                              $$.cod  = $2.cod;
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
