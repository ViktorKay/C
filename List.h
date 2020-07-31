#ifndef LIST_H
#define LIST_H

#include "Types.h"

typedef struct LL_node_t* LL_node_t;
typedef struct LL_head_t* LL_head_t;
struct LL_node_t{
    void* value;
    LL_node_t prev;
    LL_node_t next;
};
struct LL_head_t{
    int type;
    LL_node_t FreeBegin;
    LL_node_t FreeEnd;
    LL_node_t UsedBegin;
    LL_node_t UsedEnd;
};

LL_head_t LL_ctor(type_t);
LL_head_t LL_dtor(LL_head_t);

LL_node_t LL_push_back(LL_head_t, void*);
LL_node_t LL_push_front(LL_head_t, void*);
LL_node_t LL_insert(LL_head_t, LL_node_t, void*);

LL_node_t LL_pop(LL_head_t, LL_node_t);

#include <stdio.h>
void debugPrintList(LL_head_t);

#endif

