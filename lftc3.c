#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum{ID, END, CT_INT, ASSIGN, SEMICOLON, BREAK, CHAR, DOUBLE, ELSE, FOR, IF, INT, RETURN, STRUCT, VOID, WHILE};

typedef struct TokenO{
    int     code;
    union{
        char    *text;
        long int    i;
        double      r;
    };
    
    int     line;
    struct TokenO   *next;
    
}Token;

void err(const char *fmt, ...){
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, va);
    fputc('\n', stderr);
    va_end(va);
    exit(-1);
}

void safeAlloc(Token *tk){
    if(!(tk = (Token*)malloc(sizeof(Token)))){
        err("not enough memory");
    }
}

Token *tokens;

Token *lastToken;

char* keywordStringList[11] = {
    "break", "char", "double", "else"
    "for", "if", "int", "return",
    "struct", "void", "while"
};

int enumList[11] = {
    BREAK, CHAR, DOUBLE, ELSE,
    FOR, IF, INT, RETURN,
    STRUCT, VOID, WHILE
};

int line = 0;

Token *addTk(int code){
    Token   *tk;
    safeAlloc(tk);
    tk->code = code;
    tk->line = line;
    tk->next = NULL;
    if(lastToken){
        lastToken->next = tk;
    }else{
        tokens = tk;        
    }
    
    lastToken = tk;
    return tk;
}


void tkerr(const Token *tk, const char *fmt, ...){
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "error on line %d: ", tk->line);
    vfprintf(stderr, fmt, va);
    fputc('\n', stderr);
    va_end(va);
    exit(-1);
}

int getNextToken(){
    int state = 0;
    int nCh;
    char ch;
    const char *pStartCh;
    Token *tk;
    char *pCrtCh;
    
    while(1){
        ch = *pCrtCh;
        switch(state){
            case 0:
                if(isalpha(ch) || ch == '_'){
                    pStartCh = pCrtCh;
                    pCrtCh++;
                    state = 1;
                    
                }else if(ch == '='){
                    pCrtCh++;
                    state = 39;
                }
                else if(ch == ' ' || ch == '\r' || ch == '\t'){
                    pCrtCh++;
                }
                else if(ch == '\n'){
                    line++;
                    pCrtCh++;
                }
                else if(ch == 0){
                    addTk(END);
                    return END;
                }
                else 
                    tkerr(addTk(END), "caracter invalid");
                break;
            case 1:
                if(isalnum(ch) || ch == '_'){
                    pStartCh++;
                }
                else
                    state = 2;
                break;
                
            case 2:
                nCh = pStartCh - pCrtCh;
                
                //checking for keywords
                
                for(int i = 0; i < 11; i++){
                    if(nCh == strlen(keywordStringList[i]) && !memcmp(pStartCh, keywordStringList[i], strlen(keywordStringList[i])))
                        tk = addTk(enumList[i]);
                }
                /*if(nCh == 5 && !memcmp(pStartCh, "break", 5))
                    tk = addTk(BREAK);
                else if(nCh == 4 && !memcmp(pStartCh, "char", 4))
                    tk = addTk(CHAR);
                else if(nCh == 6 && !memcmp(pStartCh, "double", 6))
                    tk = addTk(DOUBLE);
                else if(nCh == 4 && !memcmp(pStartCh, "else", 4))
                    tk = addTk(ELSE);
                else if(nCh == 3 && !memcmp(pStartCh, "for", 3))
                    tk = addTk(FOR);
                else if(nCh == 2 && !memcmp(pStartCh, "if", 2))
                    tk = addTk(IF);
                else if(nCh == 3 && !memcmp(pStartCh, "int", 3))
                    tk = addTk(INT);
                else if(nCh == 6 && !memcmp(pStartCh, "return", 6))
                    tk = addTk(RETURN);
                else if(nCh == 6 && !memcmp(pStartCh, "struct", 6))
                    tk = addTk(STRUCT);//and so on
					 * */
				
        }
    }
}


char inbuf[30001];

int main(int argc, char **argv){
    safeAlloc(tokens);
    safeAlloc(lastToken);

    char *pCh;
    FILE *f = fopen(argv[1], "r");
    int n = fread(inbuf, 1, 30000, f);
    inbuf[n] = '\0';
    pCh = inbuf;
    while(getNextToken() != END){
    }
    //printTokens(); TODO
        
}








