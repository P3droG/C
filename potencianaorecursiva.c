#include <stdio.h>

int main(){
    int base, e, resultado;

    scanf("%d%d", &base, &e);
    resultado=base;
    for(int i=0; i<e; i++){
        resultado=base*resultado;
    }
    printf("%d", resultado);
}