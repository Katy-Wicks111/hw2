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
            if(nextnext<strlen(src) && src[next]== '-' && src[nextnext]!== 0){
                char start= src[pos];
                char end= src[nextnext];
                if (start <= end){
                count = count + end - start + 1;
                pos = pos + 3;
                }
            }
            else if (next<strlen(src) && src[pos] == '\\' && src[next] != 0){
            count = count + 1;
            pos = pos + 2;
            }
        else{
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

    while (*src != 0 && spos < charseq_length(src)) {
        if (src[spos + 1] == '-' && src[spos + 2] != 0){
            int start = src[spos];
            int end = src[spos + 2];
            while (start <= end){
                dst[dpos] = start;
                dpos = dpos + 1;
                start = start + 1;
            }
            spos = spos + 3;
        }
        else if (src[spos] == '\\' && src[spos + 1] != 0){
            dst[dpos] = interpret_escape(src[spos+1]);
            dpos = dpos + 1;
            spos = spos + 2;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = 0;
    return result;
}

char translate_char(char c, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //

    return c;
}

void translate(char* s, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //
}

