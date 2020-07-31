#include <stdlib.h>
#include "String.h"
#include "List.h"

LL_head_t LL_ctor(type_t T){
    LL_head_t ret = malloc(sizeof(*ret));
    if(!ret)
        return NULL;
    ret->type      = T;
    ret->UsedBegin = NULL;
    ret->UsedEnd   = NULL;
    ret->FreeBegin = malloc(sizeof(*ret->FreeBegin));
    if(!ret->FreeBegin){
        free(ret);
        return NULL;
    }
    ret->FreeEnd         = ret->FreeBegin;
    ret->FreeBegin->next = NULL;
    ret->FreeBegin->prev = NULL;
    
    if(ret->type == e_long){
        long* l = malloc(sizeof(*l));
        if(!l){
            free(ret);
            return NULL;
        }
        ret->FreeBegin->value = l;
    }
    else if(ret->type == e_ulong){
        unsigned long* ul = malloc(sizeof(*ul));
        if(!ul){
            free(ret);
            return NULL;
        }
        ret->FreeBegin->value = ul;
    }
    else if(ret->type == e_double){
        double* d = malloc(sizeof(*d));
        if(!d){
            free(ret);
            return NULL;
        }
        ret->FreeBegin->value = d;
    }
    else if(ret->type == e_string){
        ret->FreeBegin->value = String_ctor();
    }
    return ret;
}
LL_head_t LL_dtor(LL_head_t src){
    if(!src)
        return NULL;
    if(src->type == e_long || src->type == e_ulong || src->type == e_double){
        LL_node_t ptr = src->UsedBegin;
        LL_node_t del = ptr;
        while(ptr){
            del = ptr;
            ptr = ptr->next;
            free(del->value);
            del->value = NULL;
            free(del);
            del = NULL;
        }
        ptr = src->FreeBegin;
        while(ptr){
            del = ptr;
            ptr = ptr->next;
            free(del->value);
            del->value = NULL;
            free(del);
            del = NULL;
        }
    }
    else if(src->type == e_string){
        LL_node_t ptr = src->UsedBegin, del;
        String_t string;
        char* str;
        if(ptr){
            string = ptr->value;
            str = string->ptr;
            while(ptr){
                del = ptr;
                string = del->value;
                str = string->ptr;
                ptr = ptr->next;
                free(str);
                free(string);
                free(del);
                del = NULL;
            }
        }
        ptr = src->FreeBegin;
        if(ptr){
            while(ptr){
                del = ptr;
                string = del->value;
                str = string->ptr;
                ptr = ptr->next;
                free(str);
                free(string);
                free(del);
                del = NULL;
            }
        }
    }
    else if(src->type == e_vector){
        LL_node_t ptr = src->UsedBegin, del;
        String_t vec;
        void* val;
        if(ptr){
            vec = ptr->value;
            val = vec->ptr;
            while(ptr){
                del = ptr;
                vec = del->value;
                val = vec->ptr;
                ptr = ptr->next;
                free(val);
                free(vec);
                free(del);
                del = NULL;
            }
        }
        ptr = src->FreeBegin;
        if(ptr){
            vec = ptr->value;
            val = vec->ptr;
            while(ptr){
                del = ptr;
                vec = del->value;
                val = vec->ptr;
                ptr = ptr->next;
                free(val);
                free(vec);
                free(del);
                del = NULL;
            }
        }
    }
    else{// user defined types //
        ;
    }
    
    src->FreeBegin = NULL;
    src->FreeEnd   = NULL;
    src->UsedBegin = NULL;
    src->UsedEnd   = NULL;
    free(src);
    src = NULL;
    return src;
}

LL_node_t LL_push_back(LL_head_t head, void* value){
    if(!head)
        return NULL;
    LL_node_t ret = head->FreeEnd;
    if(!ret){// make new node
        ret = calloc(1,sizeof(struct LL_node_t));
        if(!ret) 
            return NULL;
        if(head->type == e_long){
            long* l = malloc(sizeof(*l));
            if(!l){
                free(ret);
                return NULL;
            }
            ret->value = l;
        }
        else if(head->type == e_ulong){
            unsigned long* ul = malloc(sizeof(*ul));
            if(!ul){
                free(ret);
                return NULL;
            }
            ret->value = ul;
        }
        else if(head->type == e_double){
            double* d = malloc(sizeof(*d));
            if(!d){
                free(ret);
                return NULL;
            }
            ret->value = d;
        }
        else if(head->type == e_string){
            String_t s = String_ctor();
            if(!s){
                free(ret);
                return NULL;
            }
            ret->value = s;
        }
    }
    //adjust free nodes
    if(ret->prev){
        head->FreeEnd = head->FreeEnd->prev;
        head->FreeEnd->next = NULL;
    }
    else{
        head->FreeEnd   = NULL;
        head->FreeBegin = NULL;
    }
    // adjust used nodes
    if(head->UsedEnd){
        head->UsedEnd->next = ret;
        ret->prev = head->UsedEnd;
        head->UsedEnd = ret;
    }
    else{
        head->UsedEnd = ret;
        head->UsedBegin = ret;
        ret->prev = NULL;
    }
    // assign value
    if(head->type == e_long){
        long* l = ret->value;
        *l = *(long*)value;
    }
    else if(head->type == e_ulong){
        unsigned long* ul = ret->value;
        *ul = *(unsigned long*)value;
    }
    else if(head->type == e_double){
        double* d = ret->value;
        *d = *(double*)value;
    }
    else if(head->type == e_string){
        String_t s = ret->value;
        String_set(s, (char*)value);
    }
    else{/* add custom types */
        ;
    }
    
    return ret;
}
LL_node_t LL_push_front(LL_head_t head, void* value){
    if(!head)
        return NULL;
    LL_node_t ret = head->FreeEnd;
    if(!ret){// make new node
        ret = calloc(1,sizeof(struct LL_node_t));
        if(!ret) 
            return NULL;
        if(head->type == e_long){
            long* l = malloc(sizeof(*l));
            if(!l){
                free(ret);
                return NULL;
            }
            ret->value = l;
        }
        else if(head->type == e_ulong){
            unsigned long* ul = malloc(sizeof(*ul));
            if(!ul){
                free(ret);
                return NULL;
            }
            ret->value = ul;
        }
        else if(head->type == e_double){
            double* d = malloc(sizeof(*d));
            if(!d){
                free(ret);
                return NULL;
            }
            ret->value = d;
        }
        else if(head->type == e_string){
            String_t s = String_ctor("");
            if(!s){
                free(ret);
                return NULL;
            }
            ret->value = s;
        }
    }
    //adjust free nodes
    if(ret->prev){
        head->FreeEnd = head->FreeEnd->prev;
        head->FreeEnd->next = NULL;
    }
    else{
        head->FreeEnd   = NULL;
        head->FreeBegin = NULL;
    }
    // adjust used nodes
    if(head->UsedBegin){
        head->UsedBegin->prev = ret;
        ret->next = head->UsedBegin;
        head->UsedBegin = ret;
    }
    else{
        head->UsedEnd = ret;
        head->UsedBegin = ret;
    }
    ret->prev = NULL;
    // assign value
    if(head->type == e_long){
        long* l = ret->value;
        *l = *(long*)value;
    }
    else if(head->type == e_ulong){
        unsigned long* ul = ret->value;
        *ul = *(unsigned long*)value;
    }
    else if(head->type == e_double){
        double* d = ret->value;
        *d = *(double*)value;
    }
    else if(head->type == e_string){
        String_t s = ret->value;
        String_set(s, (char*)value);
    }
    return ret;
}
LL_node_t LL_insert(LL_head_t head, LL_node_t node, void* value){
    if(!head)
        return NULL;
    if(!node)
        return NULL;
    LL_node_t ret = head->FreeEnd;
    if(!ret){ // make new node
        ret = calloc(1,sizeof(struct LL_node_t));
        if(!ret) 
            return NULL;
        if(head->type == e_long){
            long* l = malloc(sizeof(*l));
            if(!l){
                free(ret);
                return NULL;
            }
            ret->value = l;
        }
        else if(head->type == e_ulong){
            unsigned long* ul = malloc(sizeof(*ul));
            if(!ul){
                free(ret);
                return NULL;
            }
            ret->value = ul;
        }
        else if(head->type == e_double){
            double* d = malloc(sizeof(*d));
            if(!d){
                free(ret);
                return NULL;
            }
            ret->value = d;
        }
        else if(head->type == e_string){
            String_t s = String_ctor();
            if(!s){
                free(ret);
                return NULL;
            }
            ret->value = s;
        }
    }
    
    LL_node_t prev = node->prev;
    LL_node_t next = node->next;
    if(!prev){ //first node
        if(!next){ //only node
            head->UsedBegin->prev = ret;
            ret->next = head->UsedBegin;
        }
        else{
            head->UsedBegin->prev = ret;
            ret->next = node;
            node->prev = ret;
        }
        head->UsedBegin = ret;
    }
    else if(!next){ //last node
        if(prev){
            prev->next = ret;
            ret->prev = prev;
            ;
        }
        ret->next = head->UsedEnd;
        head->UsedEnd->prev = ret;
    }
    else{ //middle node
        prev->next = ret;
        ret->prev = prev;
        ret->next = node;
        node->prev = ret;
    }
    // assign value
    if(head->type == e_long){
        long* l = ret->value;
        *l = *(long*)value;
    }
    else if(head->type == e_ulong){
        unsigned long* ul = ret->value;
        *ul = *(unsigned long*)value;
    }
    else if(head->type == e_double){
        double* d = ret->value;
        *d = *(double*)value;
    }
    else if(head->type == e_string){
        String_t s = ret->value;
        String_set(s, (char*)value);
    }
    return ret;
}

LL_node_t LL_pop(LL_head_t head, LL_node_t node){
    if(!head)
        return NULL;
        
    // adjust used
    LL_node_t prev = node->prev;
    LL_node_t next = node->next;
    if(!prev){// first node
        if(!next){// only node
            head->UsedBegin = NULL;
            head->UsedEnd = NULL;
            node->prev = NULL;
        }
        else{
            head->UsedBegin = head->UsedBegin->next;
            next->prev = NULL;
        }
    }
    else if(!next){// last node
        prev->next = NULL;
        head->UsedEnd = prev;
    }
    else{// middle node
        prev->next = next;
        next->prev = prev;
    }
    
    // put node in the FreeEnd location
    if(!head->FreeEnd){
        head->FreeEnd = node;
        head->FreeBegin = node;
        node->prev = NULL;
    }
    else{
        head->FreeEnd->next = node;
        node->prev =  head->FreeEnd;
        head->FreeEnd = node;
    }
    node->next = NULL;
    return node;
}


void debugPrintList(LL_head_t head){
    if(!head){
        printf("null");
        return;
    }
    LL_node_t ptr = head->FreeBegin;
    unsigned long count = 0;
    puts("FREE NODES");
    printf("| index                | prev             | self             | next             |\n");
    if(!ptr){
        printf("empty\n");
    }
    else{
        while(ptr){
            printf("| %-20lu | %-16p | %-16p | %-16p |\n", count++, ptr->prev, ptr, ptr->next);
            ptr = ptr->next;
        }
    }
    ptr = head->UsedBegin;
    count = 0;
    puts("USED NODES");
    printf("| index                | prev             | self             | next             |\n");
    if(!ptr){
        printf("empty\n");
    }
    else{
        while(ptr){
            printf("| %-20lu | %-16p | %-16p | %-16p |\n", count++, ptr->prev, ptr, ptr->next);
            ptr = ptr->next;
        }
    }
}

