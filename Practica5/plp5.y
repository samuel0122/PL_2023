/*------------------------------ ejemplo.y -------------------------------*/
%token algoritmo dospto id falgoritmo
%token var fvar
%token pyc coma
%token entero real logico 
%token tabla nentero de
%token escribe lee si entonces sino 
%token mientras hacer repetir hasta 
%token blq fblq
%token opasig obool ybool oprel opas opmd
%token nreal pari pard nobool 
%token cierto falso cori cord


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TablaSimbolos.h"
#include "TablaTipos.h"


using namespace std;

#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;

TablaSimbolos *tsActual = new TablaSimbolos(NULL);
TablaTipos *tt = new TablaTipos();
Simbolo *simbolo;

vector<Simbolo> vVariablesId;


extern int yylex();
extern char *yytext;
extern FILE *yyin;


int yyerror(char *s);
void errorSemantico(int nerror,int nlin,int ncol,const char *s);

// const int ENTERO  = 1,
//           REAL    = 2,
//           BOOLEAN = 3,
//           FUNCION = 4;

string operador, s1, s2;  // string auxiliares
int tipo1, tipo2;
int numentero;

int ctemp {INIT_DIR_TEMP};
int nuevaTemp(void);

int cvar {INIT_DIR_VAR};
int nuevaVar(string nombreVar, int tamVar);

unsigned int tam, dir, tipo;
%}

%%


S     : algoritmo dospto id SDec falgoritmo  { 
                                                /* comprobar que después del programa no hay ningún token más */
                                                int tk = yylex();
                                                if (tk != 0) yyerror("");
                                                tt->imprimir();
                                                tsActual->imprimir();
                                             }
      ;


SDec  :  Dec SInstr  {}
      |  SInstr      {}
      ;

Dec   :  var MDVar fvar {}
      ;

MDVar :  MDVar DVar  {}
      |  DVar        {}
      ;

DVar  :  Tipo dospto {$$.tipoH = $1.tipo; $$.tamH = $1.tam; } LId pyc  {}
      ;

LId   :  LId coma id    {  
                           tipo = $0.tipoH;        // tipoH
                           tam = $0.tamH;          // tam
                           dir = nuevaVar(s1, tam);// dir
                           s1 = string($3.lexema); // id

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, $3.nlin, $3.ncol, $3.lexema);
                           
                        }
      |  id             {
                           tipo = $0.tipoH;        // tipoH
                           tam = $0.tamH;          // tam
                           dir = nuevaVar(s1, tam);// dir
                           s1 = string($1.lexema); // id

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, $1.nlin, $1.ncol, $1.lexema);
                        }
      ;

Tipo  :  entero                  { $$.tipo = ENTERO; $$.tam = 1; }
      |  real                    { $$.tipo = REAL; $$.tam = 1; }
      |  logico                  { $$.tipo = LOGICO; $$.tam = 1; }
      |  tabla nentero de Tipo   { 
                                    numentero = stoi($2.lexema); 
                                    $$.tipo = tt->nuevoTipoArray(numentero, $4.tipo); 
                                    $$.tam = $4.tam * numentero; }
      ;

SInstr:  SInstr pyc Instr  {}
      |  Instr             {}
      ;

Instr :  escribe Expr                     {}
      |  lee Ref                          {}
      |  si Expr entero Instr             {}
      |  si Expr entero Instr sino Instr  {}
      |  mientras Expr hacer Expr         {}
      |  repetir Instr hasta Expr         {}
      |  Ref opasig Expr                  {}
      |  blq SDec fblq                    {}
      ;

Expr  :  Expr obool Econj  {}
      |  Econj             {}
      ;

Econj :  Econj ybool Ecomp {}
      |  Ecomp             {}
      ;

Ecomp :  Esimple oprel Esimple   {}
      |  Esimple                 {}
      ;

Esimple  :  Esimple opas Term {}
         |  Term              {}
         |  opas Term         {}
         ;

Term  :  Term opmd Factor  {}
      |  Factor            {}
      ;

Factor:  Ref            {}
      |  nentero        {}
      |  nreal          {}
      |  pari Expr pard {}
      |  nobool Factor  {}
      |  cierto         {}
      |  falso          {}
      ;

Ref   :  id                      {}
      |  Ref cori Esimple cord   {}
      ;

%%
int nuevaTemp(void)
{
   if (ctemp > MAX_DIR_TEMP)
      errorSemantico (ERR_MAXTMP, 0, 0, NULL);
   
   int tempReservado = ctemp;
   ++ctemp;
   
   return tempReservado;
}

int nuevaVar(string nombreVar, int tamVar)
{
   if (cvar + tamVar - 1 > MAX_DIR_VAR)
      errorSemantico (ERR_NOCABE, 0, 0, nombreVar.c_str());
   
   int tempReservado = cvar;
   cvar += tamVar;
   
   return tempReservado;
}

void errorSemantico(int nerror,int nlin,int ncol,const char *s)
{
   fprintf(stderr,"Error semantico (%d,%d): ", nlin,ncol);
   switch(nerror) {
         case ERR_YADECL:        fprintf(stderr,"variable '%s' ya declarada\n",s);
            break;
         case ERR_NODECL:        fprintf(stderr,"variable '%s' no declarada\n",s);
            break;
         case ERR_DIM:           fprintf(stderr,"la dimension debe ser mayor que cero\n");
            break;
         case ERR_FALTAN:        fprintf(stderr,"faltan indices\n");
            break;
         case ERR_SOBRAN:        fprintf(stderr,"sobran indices\n");
            break;
         case ERR_INDICE_ENTERO: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n");
            break;
         case ERR_EXP_LOG:       fprintf(stderr,"la expresion debe ser de tipo logico\n");
            break;
         case ERR_EXDER_LOG:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo logico\n",s);
            break;
         case ERR_EXDER_ENT:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo entero\n",s);
            break;
         case ERR_EXDER_RE:      fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo real o entero\n",s);
            break;        
         case ERR_EXIZQ_LOG:     fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo logico\n",s);
            break;       
         case ERR_EXIZQ_RE:      fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo real o entero\n",s);
            break;       
         case ERR_NOCABE:        fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
            break;
         case ERR_MAXTMP:        fprintf(stderr,"no hay espacio para variables temporales\n");
            break;
   }
   exit(-1);
}

void msgError(int nerror,int nlin,int ncol,const char *s)
{
    switch (nerror) {
         case ERRLEXICO:   fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT:     fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF:      fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
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
