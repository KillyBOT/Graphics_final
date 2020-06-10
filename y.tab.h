/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMENT = 258,
    DOUBLE = 259,
    LIGHT = 260,
    AMBIENT = 261,
    CONSTANTS = 262,
    SAVE_COORDS = 263,
    CAMERA = 264,
    SPHERE = 265,
    TORUS = 266,
    BOX = 267,
    LINE = 268,
    CS = 269,
    MESH = 270,
    TEXTURE = 271,
    CYLINDER = 272,
    PLANE = 273,
    STRING = 274,
    SET = 275,
    SET_LIGHT_LOCATION = 276,
    SET_LIGHT_COLOR = 277,
    MOVE = 278,
    SCALE = 279,
    ROTATE = 280,
    BASENAME = 281,
    SAVE_KNOBS = 282,
    TWEEN = 283,
    FRAMES = 284,
    VARY = 285,
    PUSH = 286,
    POP = 287,
    SAVE = 288,
    GENERATE_RAYFILES = 289,
    SHADING = 290,
    SHADING_TYPE = 291,
    SETKNOBS = 292,
    FOCAL = 293,
    DISPLAY = 294,
    WEB = 295,
    CO = 296
  };
#endif
/* Tokens.  */
#define COMMENT 258
#define DOUBLE 259
#define LIGHT 260
#define AMBIENT 261
#define CONSTANTS 262
#define SAVE_COORDS 263
#define CAMERA 264
#define SPHERE 265
#define TORUS 266
#define BOX 267
#define LINE 268
#define CS 269
#define MESH 270
#define TEXTURE 271
#define CYLINDER 272
#define PLANE 273
#define STRING 274
#define SET 275
#define SET_LIGHT_LOCATION 276
#define SET_LIGHT_COLOR 277
#define MOVE 278
#define SCALE 279
#define ROTATE 280
#define BASENAME 281
#define SAVE_KNOBS 282
#define TWEEN 283
#define FRAMES 284
#define VARY 285
#define PUSH 286
#define POP 287
#define SAVE 288
#define GENERATE_RAYFILES 289
#define SHADING 290
#define SHADING_TYPE 291
#define SETKNOBS 292
#define FOCAL 293
#define DISPLAY 294
#define WEB 295
#define CO 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "mdl.y" /* yacc.c:1909  */

  double val;
  char string[255];

#line 141 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
