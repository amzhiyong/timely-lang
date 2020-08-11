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

#define try(buff) if(!setjmp(buff))
#define catch(no) else if(errno == no)
#define throw(buff,v) longjmp(buff,v);
#endif

unsigned long hash(void* key);

void print(char *, ...);


void out_token(Token* token);

long to_number(struct list *list);


#endif //TIMELY_LANG_BASIC_H