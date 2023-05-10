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
#include "plp5.tab.h"

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

" "                {ncol++;}
[\t]               {ncol++;}
[\n]               {nlin++;ncol=1;}

"//"                    {ncol += strlen(yytext);BEGIN(COMENTARIO);}
<COMENTARIO>[^/*\n]+    {ncol += strlen(yytext);}
<COMENTARIO>\n          {nlin++; ncol=1; BEGIN(INITIAL);}
<COMENTARIO><<EOF>>     {msgError(ERREOF,-1,-1,"");}

"algoritmo"     {return ret(algoritmo);}    
"falgoritmo"    {return ret(falgoritmo);}        
"var"           {return ret(var);}
"fvar"          {return ret(fvar);}
"entero"        {return ret(entero);}    
"real"          {return ret(real);}
"logico"        {return ret(logico);}    
"tabla"         {return ret(tabla);}
"de"            {return ret(de);}
"escribe"       {return ret(escribe);}    
"lee"           {return ret(lee);}
"si"            {return ret(si);}
"entonces"      {return ret(entonces);}    
"sino"          {return ret(sino);}
"mientras"      {return ret(mientras);}    
"hacer"         {return ret(hacer);}
"repetir"       {return ret(repetir);}    
"hasta"         {return ret(hasta);}
"blq"           {return ret(blq);}
"fblq"          {return ret(fblq);}
"cierto"        {return ret(cierto);}    
"falso"         {return ret(falso);}

{L}({LD})*         {return ret(id);}
{D}+               {return ret(nentero);}
{D}+(\.){D}+       {return ret(nreal);}

","                 {return ret(coma);}
";"                 {return ret(pyc);}
":"                 {return ret(dospto);}
"("                 {return ret(pari);}
")"                 {return ret(pard);}
"="                 {return ret(oprel);}
"<>"                {return ret(oprel);}    
"<"                 {return ret(oprel);}
"<="                {return ret(oprel);}    
">"                 {return ret(oprel);}
">="                {return ret(oprel);}    
"+"                 {return ret(opas);}
"-"                 {return ret(opas);}
"*"                 {return ret(opmd);}
"/"                 {return ret(opmd);}
":="                {return ret(opasig);}    
"["                 {return ret(cori);}
"]"                 {return ret(cord);}
"&&"                {return ret(ybool);}    
"||"                {return ret(obool);}    
"!"                 {return ret(nobool);}

.                  {msgError(ERRLEXICO,nlin,ncol,yytext);}

%%

int yywrap(void) {findefichero=1; return 1;} /* para no tener que linkar con la
                                libreria del lex */


int ret(int token)
{
   yylval.lexema=strdup(yytext);
   yylval.nlin=nlin;
   yylval.ncol=ncol;
   ncol+=(strlen(yytext));
   return(token);
}
