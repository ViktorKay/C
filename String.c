#include <stdlib.h>
#include <string.h>
#include <String.h>

String_t String_ctor(){
    String_t ret = malloc(sizeof(*ret));
    if(!ret)
        return NULL;
    ret->length = 0;
    ret->capacity = 4096;
    ret->ptr = malloc(ret->capacity * sizeof(*ret->ptr));
    if(!ret->ptr){
        free(ret);
        return NULL;
    }
    memset(ret->ptr, '\0', ret->capacity);
    return ret;
}
String_t String_dtor(String_t src){
    free(src->ptr);
    src->ptr = NULL;
    free(src);
    src = NULL;
    return src;
}
String_t String_set(String_t src, char* text){
    if(!src)
        return NULL;
    unsigned long newLength = strlen(text)+1;
    // resize container if needed
    if(newLength > src->capacity){
        unsigned long pageCount = 0;
        long modLength = newLength;
        while(modLength > 0){
            ++pageCount;
            modLength -=4096;
        }
        src->capacity = pageCount*4096;
        free(src->ptr);
        src->ptr = malloc(src->capacity * sizeof(*src->ptr));
    }
    // update container
    src->length = newLength;
    strncpy(src->ptr, text, src->length);
    return src;
}

