%code top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */
    #pragma once

    typedef void* yyscan_t;

    #include <iostream>
    using std::cout;
}

/*  ============================================================================================
    |                                          C++ DECLS                                       |
    ============================================================================================  */

%code requires {

}

/*  ============================================================================================
    |                                         BISON FLAGS                                      |
    ============================================================================================  */

%union {
    int nint; // n means 'native'.
    void* voidp;
}

%verbose
%define api.pure /* reentrant */
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
/*%define api.namespace { wrd }*/

/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start prog

%token <nint> INT
%type <voidp> prog

/*%type ?? ?? */

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
/*%right ?? ?? */
/*%left ?? ?? */


/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

prog: INT ';' {
   cout << "wow!";
}

%%

%code provides {
    #include "wrdScanner.hpp"
}

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */
