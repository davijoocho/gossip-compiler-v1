#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// DEFINITIONS
struct stmt;
enum expr_type { BINARY, UNARY, LITERAL, CALL, VARIABLE, ARRAY_LITERAL };
enum volatile_registers { RDI, RSI, RDX, RCX, RAX, R8, R9, R10, R11,
    XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7 };  // 9 - 16

struct expr {
    enum expr_type type;
    union {
        struct binary* binary;
        struct unary* unary;
        struct literal* literal;
        struct call* call;
        struct variable* variable;
        struct array_literal* array_literal;
    };

    // information for type checker
    enum token_type eval_to;
    char* struct_id;
    int indirect;
    int error;
    int line;

    // information for compiler
    enum volatile_registers reg_occupied;
};

struct binary {
    struct token* op;
    struct expr* left;
    struct expr* right;
};

struct unary {
    struct token* op;
    struct expr* right;
};

struct literal {
    struct token* value;
};

struct array_literal {
    struct expr** literals;
    int n_literals;
};

struct variable {
    struct token* id;
};

struct call {
    struct token* id;
    struct expr** args;
    int n_args;
};

enum stmt_type { STRUCT_DEF, FUNCTION_DEF, PROCEDURE_DEF, PROCEDURAL_CALL, RETURN_STMT, ASSIGN_STMT, IF_STMT, WHILE_STMT, VAR_DECL_STMT, BLOCK_STMT };

struct stmt {
    enum stmt_type type;
    union {
        struct defun* defun;
        struct defproc* defproc;
        struct proc* proc;
        struct ret* ret;
        struct assign* assign;
        struct if_stmt* if_stmt;
        struct while_stmt* while_stmt;
        struct var_decl* var_decl;
        struct block* block;
        struct defstruct* defstruct;
    };
};

struct defstruct {
    struct token* id;
    struct stmt** fields;
    int n_fields;
};

struct else_stmt {
    struct stmt* body;
};

struct elif_stmt {
    struct expr* cond;
    struct stmt* body;
};

struct if_stmt {
    struct expr* cond;
    struct stmt* body;
    struct elif_stmt** elifs;
    struct else_stmt* _else;
    int n_elifs;
};

struct while_stmt {
    struct expr* cond;
    struct stmt* body;
};

struct proc {
    struct token* id;
    struct expr** args;
    int n_args;
};

struct block {
    struct stmt** stmts;
    int n_stmts;
};

struct defproc {
    struct token* id;
    struct stmt** params;
    int n_params;
    struct stmt* def;

    int* reloc_idx;
    int n_reloc;
    int reloc_capacity;
};

struct defun {
    struct token* id;
    struct token* return_type;
    struct stmt** params;
    struct stmt* def;
    char* ret_type_repr;
    int n_params;
    int indirect;

    int* reloc_idx;
    int n_reloc;
    int reloc_capacity;
};

struct assign {
    struct expr* lhv;
    struct expr* rhv;
};


// only one level of depth allowed for array literals
// strings are not modifiable
// if array_literal = 1, then indirect + 1

struct var_decl {
    struct token* type;
    struct token* id;
    struct expr* value;
    int indirect;
    int array_literal;
    char* type_repr;
};

struct ret {
    struct token* token;  
    struct expr* value;
};

struct program {
    struct stmt** stmts;
    int n_stmts;
};

struct program* syntax_analysis(struct tokens* tokens);
struct stmt* parse_stmt(struct tokens* tokens, int scope);
struct expr* parse_expr(struct tokens* tokens, int rbp);
struct expr* parse_nud(struct tokens* tokens, struct token* op);
struct expr* parse_led(struct expr* left, struct tokens* tokens, struct token* op);



#endif
