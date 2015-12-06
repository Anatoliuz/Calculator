#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define totalFunc 2
#define totalConst 2
#define MAX 40
#define kInitialAllocationSize 4
const char* func[totalFunc] = { "cos", "sin"};
const char funcChar[totalFunc] = {'c', 's'};
const char* consts[totalConst] = {"pi", "e"};
const int constDouble[totalConst] = {M_PI, M_E};
char str[MAX];
int sp = 0;
int opPriority[256] = { ['('] = 0, ['+'] = 1, ['-'] = 1, ['*'] = 2, ['/'] = 2, ['^'] = 3,
                        ['c'] = 0, ['s'] = 0 };
char stack[MAX];
double doubles[MAX];
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
double popDouble(void) {
    if (np > 0) {
        return doubles[--np];
    } else {
        fprintf(stderr, "Невозможно выполнить POP для пустого стека.\n");
        return 0;
    }
};
double peekDouble(void) {
    int a = np;
    a--;
    if (a >= 0)
    {
        return doubles[a];
    } else {
        fprintf(stderr, "Невозможно выполнить PEEK для пустого стекаDouble.\n");
        return 0;
    }
};
void pushDouble(double a) {
    doubles[np++] = a;
};
int IsEmptyDouble() {
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
    if (length == 0) {
        fprintf(stderr, "Error: String is empty!\n");
    }
    return length;
}
char* Parse(char* mas,  int length)
{
    int jndex = 0;
    char op1;
    int curPriority = 0;
    int stackPriority = 0;
    int dotFlag = 0;
    int opFlag = 0;
    memset(str, 0, sizeof(str));
    for (int i = 0; i < length; ++i) {
        if (isspace(mas[i])) {
        }
        else if(mas[i] >= '0' && mas[i] <= '9' )
        {
            if(dotFlag == 0 || dotFlag == 1){
            str[jndex] = mas[i];
            jndex++;
            }
        }
        else if(mas[i] == 'p' || mas[i] == 'e' ){
            dotFlag  = 0;
            int k = 0;
            char temp[2] = {};
            if (mas[i] == 'e') {
                str[jndex] = 'e';
                jndex++;
            }
            else if( mas[i] == 'p'){
                while (mas[i] == consts[0][k] && k<= 2  ) {
                    temp[k] = mas[i];
                    i++;
                    k++;
                }
                i--;
                if (strcmp(temp, consts[0])) {
                    str[jndex] = 'p';
                    jndex++;
                }
            }
            else fprintf(stderr, "Error: unknown function!\n");
        }
        
        
        else if (mas[i] == '.') //you should work out errors here (double number input)
        {
            if (dotFlag == 0 ) {
                str[jndex] = mas[i];
                jndex++;
                dotFlag++;
            }
            else {
                fprintf(stderr, "Ошибка в количестве запятых\n");
            }
        }
        else if(mas[i] == '(')
        {
            dotFlag = 0;
            str[jndex] = '|';
            jndex++;
            push(mas[i]);
        }
        else if(mas[i] == ')')
        {
            dotFlag = 0;

            if ( !peek() ) {
                fprintf(stderr, "Че то со скобками");
            }
            else if(peek()){ ///!!!
            while (peek() != '(') {
                str[jndex] = pop();
                jndex++;
            }
            if (peek() != '(') {
                fprintf(stderr, "Error: check braces!\n");
            }
            }
            pop();
            
        }
        else if (mas[i] == '+' || mas[i] == '-'  || mas[i] == '/' || mas[i] == '*' ||  mas[i] == '^')
        {
            opFlag++;
            if (opFlag > 1) {
                fprintf(stderr, "Error: operators error input\n");
            }
            dotFlag = 0;
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
        else if(mas[i] == 'c' || mas[i] == 's')
        {
           
            if(mas[i] == 'c')
            {
                int k = 0;
                char temp[3] = {};
                while (mas[i] == func[0][k] && k <= 3 ) {
                temp[k] = mas[i];
                i++;
                k++;
            }
                i--;
                if (strcmp(temp, func[0])) {
                    push('c');
                }
            }
            else if(mas[i] == 's')
            {
                int k = 0;
                char temp[3] = {};
                
                while (mas[i] == func[1][k] && k <= 3 ) {
                    temp[k] = mas[i];
                    i++;
                    k++;
                }
                i--;
                if (strcmp(temp, func[1])) {
                    push('s');
                }
                
            }
        }
     
        else fprintf(stderr, "Error\n"  )  ;
        opFlag = 0;
    }
    str[jndex] = '|';
    jndex++;
    while (!IsEmpty()) {
        str[jndex] = pop();
        jndex++;
    }
    return str;
}
double Power(double a, double st)
{
    if (st == 0) {

        return 1;
    }
    double d = 1;
    int i = 0;
    while (i < st ) {
        d*=a;
        i++;
    }
    return d;
}
double DoDouble(char* mas, int length)
{
    double number = 0;
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
    number = atof(masConverted);
    return number;

}

void Count(char* mas, int length)
{
    char masToDoInt[200] = {} ;
    double num = 0;
    //memset(stack, 0 , sizeof(stack));

    for (int i = 0; i < length ; ++i)
    {
      int j  = 0;
      int k = 0;
      if(mas[i] >= '0' && mas[i] <= '9')
        {
            j = i;
            while (mas[j] >= '0' && mas[j] <= '9' || mas[j] == '.') {
                masToDoInt[k] = mas[j];
                j++;
                k++;
            }
            i=j;
            num = DoDouble(masToDoInt, k);
            pushDouble(num);
            k = 0;
            memset(masToDoInt, 0, sizeof(masToDoInt));
        }
        if (mas[i] == 'p') {
            pushDouble(M_E);
        }
        if (mas[i] == 'p')
        {
            pushDouble(M_PI);
        }
       if (mas[i] == '+'){
           pushDouble(  popDouble() + popDouble() );
       }
       else if (mas[i] == '-'){
           pushDouble(  -popDouble() + popDouble() );
       }
       else if (mas[i] == '*'){
           pushDouble(  popDouble() * popDouble() );
       }
       else if (mas[i] == '/'){
           double delimiter  = popDouble();
           if (delimiter == 0) {
               fprintf(stderr, "Division by zero!\n");
           }
           pushDouble(  popDouble() / delimiter);
       }
       else if (mas[i] == '^'){
           double st  = popDouble();
           double a = popDouble();
           double power = pow(a, st);
           pushDouble(  power );
       }
        else if(mas[i] == 'c')
        {
            double arg = 0;
            arg = popDouble();

            pushDouble( cos(arg) );
            
        }
        else if(mas[i] == 's')
        {
            double arg = 0;
            arg = popDouble();
            
            pushDouble( sin(arg) );
            
        }
    }
}
int main(int argc, char *argv[])
{
    int length = 0;
    int length2 = 0;
    if( argc < 2 ) {
        char mas[] = "1^2";
        char mas2[] = "sin(pi/2)cos(pi)";
        memset(str, 0 , sizeof(str));
        memset(doubles, 0,  sizeof(doubles));
        length = LengthOfMas(mas2);
        char* myStr = Parse(mas2, length);
        length2 = LengthOfMas(myStr);
        Count(myStr, length2);
        printf("%5.4lf\n", peekDouble());
    }
    else {
        for (int i = 1; i < argc; ++i) {
            memset(str, 0 , sizeof(str));
            memset(doubles, 0,  sizeof(doubles));
            int length = LengthOfMas(argv[i]);
            char *myStr2 = Parse(argv[i], length);
            length2 = LengthOfMas(myStr2);
            Count(myStr2, length2);
            printf("%5.4lf\n", peekDouble());
        }
    }
 
    return 0;
}

