#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#define MAX 40
#define kInitialAllocationSize 4
char str[MAX];
int sp = 0;
int opPriority[256] = { ['('] = 0, ['+'] = 1, ['-'] = 1, ['*'] = 2, ['/'] = 2, ['^'] = 3 };
char stack[MAX];
long longs[MAX];
char pop(void) {
    if (sp > 0) {
        return stack[--sp];
    } else {
        fprintf(stderr, "Невозможно выполнить POP для пустого стека.\n");
        return 0;
    }
};
char peek(void) {
    int a = sp;
    a--;
    if (a >= 0)
    {
        printf("Peek: %c ", stack[a]);
        return stack[a];
    } else {
        fprintf(stderr, "Невозможно выполнить PEEK для пустого стека.\n");
        return 0;
    }
};
void push(char a) {
    stack[sp++] = a;
};
int IsEmpty() {
    if (sp <=
        0)
        return 1;
    else
    {
       // printf("Стек пуст(IsEmptySource)\n");
        return 0;
    }
}
int np = 0;
long popLong(void) {
    if (np > 0) {
        return longs[--np];
    } else {
        fprintf(stderr, "Невозможно выполнить POP для пустого стека.\n");
        return 0;
    }
};
long peekLong(void) {
    long a = np;
    a--;
    if (a >= 0)
    {
        printf("Peek: %ld ", longs[a]);
        return longs[a];
    } else {
        fprintf(stderr, "Невозможно выполнить PEEK для пустого стекаLong.\n");
        return 0;
    }
};
void pushLong(long a) {
    longs[np++] = a;
};
int IsEmptyLong() {
    if (np <=
        0)
        return 1;
    else
    {
        // printf("Стек пуст(IsEmptySource)\n");
        return 0;
    }
}
int LengthOfMas(char* mas)
{
    int length = 0;
    for (int index = 0; mas[index] != '\0'; ++index) {
        ++length;
    }
    return length;
}
char* Parse(char* mas,  int length)
{
    int jndex = 0;
    char op1;
    int curPriority = 0;
    int stackPriority = 0;
    memset(str, 0, sizeof(str));
    for (int i = 0; i < length; ++i) {
        if (isspace(mas[i])) {
            printf("space\n");
        }
        if(mas[i] >= '0' && mas[i] <= '9')
        {
            str[jndex] = mas[i];
            jndex++;
        }
        else if(mas[i] == '(')
        {
            str[jndex] = '|';
            jndex++;
            push(mas[i]);
        }
        else if(mas[i] == ')')
        {
            //char b = peek();
           // printf("Peek:%c\n", b);
            while (peek() != '(') {
                str[jndex] = pop();
                jndex++;
            }
            pop();
//            char a = peek();
//            printf("Peek after: %c \n", a);
        }
        else if (mas[i] == '+' || mas[i] == '-'  || mas[i] == '/' || mas[i] == '*' ||  mas[i] == '^')
        {
            if (opPriority[mas[i]] == 1) {
                curPriority = 1;
            }
            else if(opPriority[mas[i]] == 2)
                curPriority = 2;
            else if(opPriority[mas[i]] == 3)
                curPriority = 3;
            if(IsEmpty())
            {
                str[jndex] = '|';
                jndex++;
                push(mas[i]);
                //printf("empty stack in oper processing)\n");
            }
            else if (!IsEmpty())
            {
                op1 = peek();
                if (opPriority[op1] == 1) {
                    stackPriority = 1;
                }
                else if (opPriority[op1] == 2)
                {
                    stackPriority = 2;
                }
                else if (opPriority[op1] == 3)
                {
                    stackPriority = 3;
                }
                else if (opPriority[op1] == 0)
                {
                    stackPriority = 0;
                }
                while (curPriority <= stackPriority) {
                    if(!IsEmpty()){
                        str[jndex] = '|';
                        jndex++;
                    str[jndex] = pop();
                    jndex++;
                    op1 = peek();
                    if (opPriority[op1] == 1) {
                        stackPriority = 1;
                    }
                    else if (opPriority[op1] == 2)
                    {
                        stackPriority = 2;
                    }
                    else if (opPriority[op1] == 3)
                    {
                        stackPriority = 3;
                    }
                    else curPriority = (stackPriority + 1);
                    }
                    else
                    {
                        printf("wtf");
                    }
                }
                str[jndex] = '|';
                jndex++;
                push(mas[i]);
            }
            else printf("dont  know \n");
        }
        else printf("You are\n")  ;
        
    }
    str[jndex] = '|';
    jndex++;
    while (!IsEmpty()) {
        str[jndex] = pop();
        jndex++;
    }
    return str;
}
long Power(long a, long st)
{
    if (st == 0) {

        return 1;
    }
    long d = 1;
    int i = 0;
    while (i < st ) {
        d*=a;
        i++;
    }
    printf("Power %ld", d);
    return a;
}
long DoInt(char* mas, int length)
{
    char* masConverted;
    int allocLength = kInitialAllocationSize;
    int curLength = 0;
    masConverted = (char*)malloc(sizeof(char)*kInitialAllocationSize);
    int j = 0;
    for (int i = 0; i < length ; ++i) {
        if( allocLength == curLength )
        {
            allocLength += kInitialAllocationSize;
            masConverted = (char*)realloc(masConverted, sizeof(char) * kInitialAllocationSize);
        }
        curLength++;
        masConverted[j] = mas[i];
        j++;
    }
    char *end;
    long number = 0;
    for (long i = strtol(masConverted, &end, 10);
         masConverted != end;
         i = strtol(masConverted, &end, 10))
    {
        masConverted = end;
        if (errno == ERANGE){
            printf("range error, got ");
            errno = 0;
        }
        number = i;
        
    }
    return number;
}

void Count(char* mas, int length)
{
    char masToDoInt[200] = {} ;
    long num = 0;
   
    for (int i = 0; i < length ; ++i)
    {
      int j  = 0;
      int k = 0;
      if(mas[i] >= '0' && mas[i] <= '9')
        {
            j = i;
            while (mas[j] >= '0' && mas[j] <= '9') {
                masToDoInt[k] = mas[j];
                j++;
                k++;
            }
            num = DoInt(masToDoInt, k);
            pushLong(num);
            k = 0;
            memset(masToDoInt, 0, sizeof(masToDoInt));
        }
       else if (mas[i] == '+'){
           pushLong(  popLong() + popLong() );
       }
       else if (mas[i] == '-'){
           pushLong(  -popLong() + popLong() );
       }
       else if (mas[i] == '*'){
           pushLong(  popLong() * popLong() );
       }
       else if (mas[i] == '/'){
           long delimiter  = popLong();
           pushLong(  popLong() / delimiter);
       }
       else if (mas[i] == '^'){
           long st  = popLong();
           long a = popLong();
           pushLong(  Power(a , st) );
       }
    }
    printf("void Peek is :%ld", peekLong()  );

}
int main()
{
    double n = atof("12.4");
    printf("%.3f", n);
    long g = 4;
    long h = 8;
    long c = g/h;
    printf("a/b %ld", c);
    Power(-4, 3);
    char mas[] = "(8+2*5)/(1+3*2-4)";
    char mas2[] = "3+4*2/(1-5)^2";
    //Power(2, 0);
    int length = 0;
    int length2 = 0;
    memset(str, 0 , sizeof(str));
    length = LengthOfMas(mas2);
    char* myStr = Parse(mas2, length);
    //DoInt("123", 3);
    length2 = LengthOfMas(myStr);
    for (int i = 0; i < length2 ; ++i) {
        printf("OPN str: %c\n", myStr[i] );
    }

    Count(myStr, length2);
    
 
    long a = peekLong();
    printf("%ld", a);
    return 0;
}

