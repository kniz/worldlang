%{
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "wrdcNode.hpp"
using namespace std;

int yylex();
extern int yylineno;
extern char* yytext;
namespace wrd {
    const char* getName(int type);
}

void yyerror(const char* s)
{
    cout << Node::clr(Node::RED) << "error " << yylineno << Node::clr(Node::WHITE) << ": " << s << ", " << yytext << "\n";
    //asm("int3");
}
%}

%glr-parser
%union {
    int typeId;
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;
    const char* strVal;
    Node* node;
    void* nodes;
}

%verbose
%start tfile

%token tfor tdef twith tret tretfun tretif tretwith tretfor tif telse telif tfrom tagain tprop timport taka tthis tme tgot tnode tnull tsuper tout tin tindent tdedent
%token <intVal> tinteger teof
%token <floatVal> tfloat
%token <boolVal> tbool
%token <charVal> tchar
%token <strVal> tstr
%token <strVal> tidentifier tfuncname
%token teol topDefAssign topMinusAssign topSquareAssign topDivideAssign topModAssign topPowAssign topLessEqual topMoreEqual topEqual topRefEqual topNotEqual topNotRefEqual topPlusAssign
%type <node> tstmt tlhsexpr/*only lhs*/ trhsexpr tcast targs ttlist tblock tindentBlock tfile tfunc telseBlock telifBlock tbranch termIf
%type <nodes> telifBlocks

%printer { fprintf(yyo, "%s[%d]", wrd::getName($$), $$); } tinteger;
%printer { fprintf(yyo, "%s", $$); } tidentifier;

// 우선순위: 밑으로 갈수록 높음.
//  결합 순서 정의:
//      정해주지 않으면 모호성 오류 나온다.
//      left: 왼쪽 결합.
//      right: 오른쪽 결합.
%left ":=" '=' "+=" "-=" "/=" "*=" "%=" "^="
%left '%' '^'
%left '+' '-'
%left '*' '/'

%%

telseBlock  : teol telse teol tindentBlock {
                $$ = $4;
            }

telifBlock  : teol telif tbranch {
                $$ = $3;
            }

telifBlocks : telifBlock {
                vector<Branch*>* ret = new vector<Branch*>;
                ret->push_back((Branch*) $1);
                $$ = ret;
            }
            | telifBlocks telifBlock {
                vector<Branch*>* blk = (vector<Branch*>*) $1;
                blk->push_back((Branch*) $2);
                $$ = $1;
            }

tbranch     : trhsexpr teol tindentBlock {
                $$ = new Branch($1, (Container*) $3);
            }

termIf      : tif tbranch telifBlocks telseBlock {
                $$ = new If((Branch*) $2, (vector<Branch*>*) $3, (Block*) $4);
            }
            | tif tbranch telifBlocks {
                $$ = new If((Branch*) $2, (vector<Branch*>*) $3, 0);
            }
            | tif tbranch telseBlock {
                $$ = new If((Branch*) $2, (Block*) $3);
            }
            | tif tbranch {
                $$ = new If((Branch*) $2);
            }
            ;

// trhsexpr과 tlhsexpr:
//  tlhsexpr은 할당이 가능한 변수. lvalue.
//  trhsexpr은 값을 나타내는 모든 표현식.
//  따라서 범주상으로 보았을때 trhsexpr 은 tlhsexpr을 포함한다. 더 크다는 얘기다.
trhsexpr    : tinteger {
                $$ = new Int($1);
            }
            | tbool {
                $$ = new Bool($1);
            }
            | tfloat {
                $$ = new Float($1);
            }
            | tstr {
                $$ = new Str($1);
            }
            | tchar {
                $$ = new Char($1);
            }
            | ttlist {
                $$ = $1;
            }
            | tlhsexpr {
                $$ = $1;
            }

            | trhsexpr '+' trhsexpr {
                $$ = new Plus($1, $3);
            }
            | trhsexpr '-' trhsexpr {
                $$ = new Minus($1, $3);
            }
            | trhsexpr '*' trhsexpr {
                $$ = new Square($1, $3);
            }
            | trhsexpr '/' trhsexpr {
                $$ = new Divide($1, $3);
            }
            | trhsexpr '%' trhsexpr {
                $$ = new Moduler($1, $3);
            }
            | trhsexpr '^' trhsexpr {
                $$ = new Power($1, $3);
            }
            | trhsexpr '<' trhsexpr {
                $$ = new Less($1, $3);
            }
            | trhsexpr topLessEqual trhsexpr {
                $$ = new LessEqual($1, $3);
            }
            | trhsexpr '>' trhsexpr {
                $$ = new More($1, $3);
            }
            | trhsexpr topMoreEqual trhsexpr {
                $$ = new MoreEqual($1, $3);
            }
            | trhsexpr topEqual trhsexpr {
                $$ = new Equal($1, $3);
            }
            | trhsexpr topRefEqual trhsexpr {
                $$ = new RefEqual($1, $3);
            }
            | trhsexpr topNotEqual trhsexpr {
                $$ = new NotEqual($1, $3);
            }
            | trhsexpr topNotRefEqual trhsexpr {
                $$ = new NotRefEqual($1, $3);
            }

            | tcast { $$ = $1; }
            | tfor tidentifier tin trhsexpr teol tindentBlock {
                $$ = new For(new Id($2), $4, (Container*) $6);
            }
            | termIf { $$ = $1; }
            | tfunc { $$ = $1; }
            ;

tlhsexpr    : tidentifier { $$ = new Id($1); }
            | tlhsexpr '=' trhsexpr {
                $$ = new Assign($1, $3);
            }
            | tlhsexpr topDefAssign trhsexpr {
                $$ = new DefAssign($1, $3);
            }
            | tlhsexpr topPlusAssign trhsexpr {
                $$ = new PlusAssign($1, $3);
            }
            | tlhsexpr topMinusAssign trhsexpr {
                $$ = new MinusAssign($1, $3);
            }
            | tlhsexpr topSquareAssign trhsexpr {
                $$ = new SquareAssign($1, $3);
            }
            | tlhsexpr topDivideAssign trhsexpr {
                $$ = new DivideAssign($1, $3);
            }
            | tlhsexpr topModAssign trhsexpr {
                $$ = new ModulerAssign($1, $3);
            }
            | tlhsexpr topPowAssign trhsexpr {
                $$ = new PowAssign($1, $3);
            }
            ;

tcast       : tidentifier trhsexpr {
                $$ = new Cast(new Id($1), $2);
            }
            ;

targs       : trhsexpr {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | targs ',' trhsexpr {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;

ttlist      : '(' targs ')' { //  " "를 쓰면 안된다.
                $$ = new TypeList((Args*) $2);
            }
            | '(' ')' {
                $$ = new TypeList();
            }
            ;

tfunc       : tfuncname ttlist {
                $$ = new Func($1, (TypeList*) $2);
            }
            ;

tstmt       : trhsexpr teol {
                $$ = new Stmt($1);
            }
            | teol {
                $$ = new Stmt(new Str(""));
            }
            | trhsexpr teof {
                $$ = new Stmt($1);
            }
            ;

tblock      : tstmt {
                Block* ret = new Block();
                if ($1)
                    ret->add($1);
                $$ = ret;
            }
            | tblock tstmt {
                Block* ret = (Block*) $1;
                if ($2)
                    ret->add($2);
                $$ = ret;
            }
            ;

tindentBlock: tindent tblock tdedent {
                $$ = $2;
            }

tfile       : tblock teof {
                Block* blk = (Block*) $1;
                File* ret = new File(blk);
                cout << ret->print();
                $$ = ret;
            }
            ;