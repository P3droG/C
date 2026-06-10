#include <stdio.h>
void main(){
    int x, vet[3];
    lerInt(&x);
    lerVetor(vet, 3);
    void imprime(int a){
        printf("%d\n", a);
    }
    void lerInt(int*a){
        scanf("%d", a);
    }
}