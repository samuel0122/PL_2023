/*------------------------------ ejemplo.l -------------------------------*/
D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]

%{
#include <string.h> 
#include <string>
#include <iostream>

using namespace std;

#include "comun.h"
#include "plp4.tab.h"

int ncol = 1,
    nlin = 1;

int findefichero = 0;

int ret(int token);  
// función que actualiza 'nlin' y 'ncol' y devuelve el token

void msgError(int nerror, int nlin,int ncol,const char *s);
// función para producir mensajes de error

%}

%x COMENTARIO

%%
%{

%}

" "                {ncol++;}
[\t]               {ncol++;}
[\n]               {nlin++;ncol=1;}

"(*"                    {ncol += strlen(yytext);BEGIN(COMENTARIO);}
<COMENTARIO>[^/*\n]+    {ncol += strlen(yytext);}
<COMENTARIO>\n          {nlin++;ncol=1;}
<COMENTARIO><<EOF>>     {msgError(ERRLEXEOF,-1,-1,"");}
<COMENTARIO>"*)"        {ncol+=strlen(yytext); BEGIN(INITIAL);}
<COMENTARIO>[*)]        {ncol += strlen(yytext);}

"var"            {return ret(var);}
"real"           {return ret(real);}
"entero"         {return ret(entero);}
"algoritmo"      {return ret(algoritmo);}
"blq"            {return ret(blq);}
"fblq"           {return ret(fblq);}
"funcion"        {return ret(funcion);}
"si"             {return ret(si);}
"entonces"       {return ret(entonces);}
"sino"           {return ret(sino);}
"fsi"            {return ret(fsi);}
"mientras"       {return ret(mientras);}
"hacer"          {return ret(hacer);}
"escribir"       {return ret(escribir);}

{L}({LD})*         {return ret(id);}
{D}+               {return ret(nentero);}
{D}+(\.){D}+       {return ret(nreal);}

"("                {return ret(pari);}
")"                {return ret(pard);}
"*"                {return ret(opmd);}
"/"                {return ret(opmd);}
"//"               {return ret(opmd);}
"+"                {return ret(opas);}
"-"                {return ret(opas);}
"<"                {return ret(oprel);}
">"                {return ret(oprel);}
"<="               {return ret(oprel);}
">="               {return ret(oprel);}
"="                {return ret(oprel);}
"<>"               {return ret(oprel);}
";"                {return ret(pyc);}
":"                {return ret(dosp);}
","                {return ret(coma);}
":="               {return ret(asig);}
.                  {msgError(ERRLEXICO,nlin,ncol,yytext);}

%%

int yywrap(void) {findefichero=1; return 1;} /* para no tener que linkar con la
                                libreria del lex */


int ret(int token)
{
   std::cout << std::string(yytext) << '\n';
   yylval.lexema=strdup(yytext);
   yylval.nlin=nlin;
   yylval.ncol=ncol;
   ncol+=(strlen(yytext));
   return(token);
}
