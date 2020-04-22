#include "translate.h"

#include <stddef.h>
#include <stdlib.h>

// Helper function for interpreting escapes. Given the character that
// follows a backslash, returns the character that the combination
// should be replaced with. Recognizes the seven standard C escapes, and
// maps every other character to itself.
char interpret_escape(char c)
{
    switch (c) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    default:  return c;
    }
}

size_t charseq_length(const char* src)
{
    size_t count = 0;
    size_t pos = 0;
    while(src[pos] != 0){
        size_t next= pos+1;
        size_t nextnext= next+1;
        if(src[next]== '-' && src[nextnext]!= 0){
            char start= src[pos];
            char end= src[nextnext];
            if (start <= end){
                count = count + end - start + 1;
                pos = pos + 3;
            } else {
                pos=pos+3;
                }
        } else if (src[pos] == '\\' && src[next] != 0) {
            count = count + 1; // this is the only improtant par
            pos = pos + 2;
        } else {
            count= count+1;
            pos=pos+1;
        }
    }
    return count;
}


char* expand_charseq(const char* src)
{
    char* result = malloc(charseq_length(src) + 1);
    if (!result) return NULL;
    char* dst    = result;
    size_t spos = 0;
    size_t dpos = 0;
    while (src[spos] != 0) {
        size_t next= spos+1;
        size_t nextnext= next+1;
        if(nextnext<strlen(src) && src[next]== '-' && src[nextnext]!= 0){
            int start= src[spos];
            int end= src[nextnext];
            if (start<=end){
                spos=spos+3;
            }
            while (start <= end){
                dst[dpos]=start;
                dpos=dpos+1;
                start=start+1;
            }
        } else if (next<strlen(src) && src[spos] == '\\' && src[next] != 0) {
            dst[dpos]=interpret_escape(src[next]);
            dpos=dpos+1;
            spos=spos+2;
        } else {
            dst[dpos]=src[spos];
            dpos=dpos+1;
            spos=spos+1;
        }
    }
    dst[dpos]=0;
    return dst;
}


char translate_char(char c, const char* from, const char* to)
{
    ssize_t pos = 0;
    while (pos < strlen(from)){
        if (from[pos] == c){
        return to[pos];
        } else {
            pos = pos + 1;
        }

    }

    return c;
}

void translate(char* s, const char* from, const char* to)
{
   size_t pos = 0;
    while (pos < strlen(s)){
        s[pos] = translate_char(s[pos], from, to);
        pos = pos + 1;

    }
}

