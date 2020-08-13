//
// Created by zy on 8/8/20.
//

#ifndef TIMELY_LANG_BASIC_H
#define TIMELY_LANG_BASIC_H

#include <stdio.h>
#include <stdarg.h>
#include "list.h"
#include "token.h"
#include "log.h"
#include "string.h"
#include "setjmp.h"
#include "errno.h"

#define GET_CHAR(chr) memset(malloc(sizeof(char)), chr, 1)
#define t_bool int
#define t_true  1
#define t_false 0

#ifndef __TIMELY__JMP__
#define __TIMELY__JMP__

#define STR2(s) #s
#define STR(s) STR2(s)

#define error(...) log_error(__FILE__ ":" STR(__LINE__), 1, 1, __VA_ARGS__)
#define errort(file, token, ...) log_error(file, token->row_pos, token->col_pos, __VA_ARGS__)
#define MALLOC_SIZE(t, size) sizeof(t) size

#define try(buff) if(!setjmp(buff))
#define catch(no) else if(errno == no)
#define throw(buff, v) longjmp(buff,v);
#endif


typedef struct str_buff_ {
    unsigned int len;
    unsigned int buff_size;
    char *body;
} StringBuff;


void log_error(char *file, unsigned int line, unsigned int pos, char *fmt, ...);

char *get_token_pos(Token *token);

unsigned long hash(void *key);

void print(char *, ...);


void out_token(Token *token);

long to_number(List *list);


/**
 * buff.c
 */

char *reverse(char *s);

StringBuff *new_sbuff(int size);

int append_str(StringBuff *buff, char *c);

int append_chr(StringBuff *buff, char c);

char buff_get(StringBuff* buff, int index);

char *to_string(StringBuff *buff);

void print_buff(StringBuff *buff);

void clear_buff(StringBuff *buff);

/**
 * int 类型转 字符类型
 * @return 转换好的
 */
char *itochr(int i);

#endif //TIMELY_LANG_BASIC_H
