#include <stdio.h>

int main(){
    int num, fatorial=1;
    scanf("%d", &num);
    for(int i=1; i<=num; i++){
        fatorial*=i;
    }
    printf("%d", fatorial);
}