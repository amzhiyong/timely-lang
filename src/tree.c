//
// Created by zy on 8/9/20.
//
#include "../include/eval.h"
#include "../include/basic.h"
#include "string.h"




void* binary_eval(Environment* env, BinaryExpr* expr){
    print("call: %s", __FUNCTION__ );
    GET_EVAL(expr->left)->eval(env, expr->left);
    GET_EVAL(expr->right)->eval(env,expr->right);
    return NULL;
}

void* while_eval(Environment* env, WhileStmt* stmt){
    print("call: %s", __FUNCTION__ );
//    while (GET_EVAL(stmt->expr)->eval(env, stmt->expr)){
//        GET_EVAL(stmt->block)->eval(env, stmt->block);
//    }
    return NULL;
}

void* var_eval(Environment* env, VarTerm* term){
    print("call: %s", __FUNCTION__ );
//    void* value = GET_EVAL(term->value)->eval(env,term);
//    map_put(&env->map, term->name->text, value);
    return NULL;
}

void* constant_eval(Environment* env, ConstantTerm* term){
    print("call: %s", __FUNCTION__ );
    switch (term->name->kind) {
        case NUMBER:
            return atol(term->name->text);
        case STRING:
            return "hello world";
        case ID:
            return term->name->text;
        default:
            print("类型解析失败!");
            abort();
    }
}

void* block_eval(Environment* env, BlockStmt* stmt){
    print("call: %s", __FUNCTION__ );
    struct list *comm = stmt->stmts;
    void* node;
    for (int i = 0; i < comm->size; ++i) {
        node = list_get(stmt->stmts, i);
        if (node == NULL)continue;
        GET_EVAL(node)->eval(env, node);
    }
    return NULL;
}

void* start_eval(Environment* env, StartTerm * stmt){
    print("call: %s", __FUNCTION__ );
    return NULL;
}

void* end_eval(Environment* env, EndTerm * stmt){
    print("call: %s", __FUNCTION__ );
    return NULL;
}


void* call_eval(Environment* env, CallTerm* term){
    print("call: %s", __FUNCTION__ );
    ConstantTerm* constant = term->expr;
    struct list *args = term->args;
    void* stmt;
    char buff[1024];
//    for (int i = 0; i < args->size; ++i) {
//        stmt = list_get(args,i);
//        strcat(buff, GET_EVAL(stmt)->eval(env,stmt));
//    }
    if (strcmp("print", constant->name->text) == 0){
        print("%s", buff);
    }

    return NULL;
}


void* empty_eval(Environment* env, EmptyStmt* term){

    return NULL;
}

void* fun_eval(Environment* env, FunStmt* fun){
    print("call: %s", __FUNCTION__ );
}


void* tree_eval(Environment* env, Tree* eval){
//    print("call: %s", __FUNCTION__ );
    struct list* stmts = eval->stmts;
    void* node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        GET_EVAL(node)->eval(NULL,node);
    }
    return NULL;
}


void* try_eval(Environment* env, TryStmt* stmt){
    print("call: %s", __FUNCTION__ );



}
void* catch_eval(Environment* env, CatchStmt* stmt){
    print("call: %s", __FUNCTION__ );
}


Eval* new_eval(void* (*eval_call)(Environment* env, void* node)){
    Eval* eval = malloc(sizeof(Eval));
    eval->eval = eval_call;
    return eval;
}


Tree* new_tree(struct list* list){
    Tree* tree = malloc(sizeof(Tree));
    tree->stmts = list;
    tree->eval = *new_eval(GET_FUN(tree_eval));
    return tree;
}

VarTerm* new_var_term(Token* name, void* expr){
    VarTerm* var = malloc(sizeof(VarTerm));
    var->eval = *new_eval(GET_FUN(var_eval));
    var->name = name;
    var->value = expr;
    return var;
}

ConstantTerm* new_constant_term(Token* name){
    ConstantTerm* constraint = malloc(sizeof(ConstantTerm));
    constraint->name = name;
    constraint->eval = *new_eval(GET_FUN(constant_eval));
    return constraint;
}

BinaryExpr* new_binary_expr(void* left,Token* op, void* right){
    BinaryExpr* binary = malloc(sizeof(BinaryExpr));
    binary->left = left;
    binary->op = op;
    binary->right = right;
    binary->eval = *new_eval(GET_FUN(binary_eval));
    return binary;
}

BlockStmt* new_block_stmt(struct list* stmts){
    BlockStmt* block = malloc(sizeof(BlockStmt));
    block->stmts = stmts;
    block->eval = *new_eval(GET_FUN(block_eval));
    return block;
}

WhileStmt* new_while_stmt(Token* name, void* expr, void* block){
    WhileStmt* t_while = malloc(sizeof(WhileStmt));
    t_while ->name = name;
    t_while->expr = expr;
    t_while->block = block;
    t_while->eval = *new_eval(GET_FUN(while_eval));
    return t_while;
}

StartTerm* new_start_term(Token* op, void* expr){
    StartTerm* term = malloc(sizeof(StartTerm));
    term->eval = *new_eval(GET_FUN(start_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

EndTerm* new_end_term(Token* op, void* expr){
    EndTerm* term = malloc(sizeof(EndTerm));
    term->eval= *new_eval(GET_FUN(end_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

CallTerm* new_call_term(void* expr, struct list* args){
    CallTerm *term = malloc(sizeof(CallTerm));
    term->expr = expr;
    term->eval = *new_eval(GET_FUN(call_eval));
    term->args = args;
    return term;
}

EmptyStmt* new_empty(Token *op){
    EmptyStmt* empty= malloc(sizeof(EmptyStmt));
    empty->token = op;
    empty->eval = *new_eval(GET_FUN(empty_eval));
    return empty;
}

FunStmt* new_fun_stmt(Token* name, struct list* args, void* block){
    FunStmt* fun = malloc(sizeof(FunStmt));
    fun->eval = *new_eval(GET_FUN(fun_eval));
    fun->name = name;
    fun->args = args;
    fun->block = block;
    return fun;
}

TryStmt* new_try_stmt(void* block, struct list *stmts, void* finally){
    TryStmt* stmt = malloc(sizeof(TryStmt));
    stmt->eval = *new_eval(GET_FUN(try_eval));
    stmt->block = block;
    stmt->stmts = stmts;
    stmt->stmt = finally;
    return stmt;
}

CatchStmt* new_catch_stmt(void* expr, void* block){
    CatchStmt* stmt = malloc(sizeof(CatchStmt));
    stmt->eval = *new_eval(GET_FUN(catch_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}