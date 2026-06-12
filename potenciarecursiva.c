#include <stdio.h>

long pot(long base, long e){
    if(e==0){
        return 1;
    }

    if(e==1){
        return base;
    }
    return(base * pot(base, e-1));
}
int main(){
    long base, e;
    printf("Digite a base e o expoente\n");
    scanf("%ld %ld", &base, &e);
    printf("%ld\n", pot(base, e));
}