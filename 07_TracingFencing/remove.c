#define _GNU_SOURCE#include <dlfcn.h>#include <stdio.h>#include <string.h>#include <ctype.h>typedef int (*_remove)(const char* file);// strcasestr function not always present, using weak declaration to define it if not definedchar* strcasestr(const char* str1, const char* str2) __attribute__((weak)); // weak declaration must always be present// optional definition:char* strcasestr( const char* str1, const char* str2 ){    const char* p1 = str1 ;    const char* p2 = str2 ;    const char* r = *p2 == 0 ? str1 : 0 ;    while( *p1 != 0 && *p2 != 0 )    {        if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )        {            if( r == 0 )            {                r = p1 ;            }            p2++ ;        }        else        {            p2 = str2 ;            if( r != 0 )            {                p1 = r + 1 ;            }            if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )            {                r = p1 ;                p2++ ;            }            else            {                r = 0 ;            }        }        p1++ ;    }    return *p2 == 0 ? (char*)r : 0 ;}int remove(const char* file) {    fprintf(stderr, "IN PRELOAD");    if (strcasestr(file, "protect") != NULL)    {        return 100;    } else        return ((_remove)dlsym(RTLD_NEXT,"remove"))(file);}