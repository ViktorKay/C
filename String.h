#ifndef STRING_H
#define STRING_H

typedef struct{
    unsigned long length;
    unsigned long capacity;
    char* ptr;
}*String_t;

String_t String_ctor();
String_t String_dtor(String_t);
String_t String_set(String_t, char*);

#endif 

