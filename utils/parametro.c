#include <stdio.h>
#include <locale.h>

int soma(){
    static int s = 0;
    if(s == 10)
        return 1;
    s++;
    return 1 + soma();
}

int main(void)
{
    
    printf("Soma %d\n", soma());
    return 0;
}