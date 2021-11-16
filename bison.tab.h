/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "bison.y"

	#include "util.h"
	#include "ast.h"

#line 53 "bison.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PROGRAM = 258,
    TK_VAR = 259,
    TK_PROCEDURE = 260,
    TK_FUNCTION = 261,
    TK_BEGIN = 262,
    TK_END = 263,
    TK_FALSE = 264,
    TK_TRUE = 265,
    TK_IF = 266,
    TK_THEN = 267,
    TK_ELSE = 268,
    TK_WHILE = 269,
    TK_DO = 270,
    TK_READ = 271,
    TK_WRITE = 272,
    TK_AND = 273,
    TK_OR = 274,
    TK_NOT = 275,
    TK_DIV = 276,
    TK_LPAREN = 277,
    TK_RPAREN = 278,
    TK_ATRIBUICAO = 279,
    TK_MAIS = 280,
    TK_MENOS = 281,
    TK_MULT = 282,
    TK_IGUAL = 283,
    TK_DIFERENTE = 284,
    TK_MAIOR = 285,
    TK_MENOR = 286,
    TK_MAIORIGUAL = 287,
    TK_MENORIGUAL = 288,
    TK_VIRGULA = 289,
    TK_PONTVIRG = 290,
    TK_DOISPONTOS = 291,
    TK_PONTO = 292,
    TK_NUM = 293,
    TK_IDENT = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "bison.y"

   String str;
   int num;
   A_Programa programa;
   A_Bloco bloco;
   A_BlocoSub bloco_sub;
   A_LstDecSub secDecSub;
   //A_DecVar decVar;
   A_LstDecVar secDecVar;
   A_ListaId listaId;
   A_DecProc decProc;
   A_DecParam decParam;
   A_DecParamList decParamList;
   A_CmdComp cmdComp;
   A_Cmd cmd;
   A_Atrib atrib;
   A_ChamProc chamProc;
   A_Cond cond;
   A_Loop loop;
   A_IO IO;
   A_ListExp listExp;
   A_Exp exp;
   //A_Termo termo;
   //A_Fator fator;
   A_Var var;
   A_ChamFunc chamFunc;

#line 132 "bison.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
