#include <stdio.h>

//prototipo
float media(float x, float y);
int compara(int x, int y);
void troca(int *x, int *y); 
int main(){ //função principal
    float m;
    int a=10, b=20;
    
    m=media(a, b);
    printf("Media = %.2f\n", m);

    printf("Compara = %d\n", compara(a, b));
    
    troca(&a, &b);

    printf("A = %d\n", a);
    printf("B = %d\n", b);
    return 0;
}

float media(float x, float y){ //função media
    return (x+y)/2;
}

int compara(int x, int y){ //função compara
    if(x==y){
        return 0;
    }
    else if(x>y){
        return 1;
    }
    else{
        return -1;
    }
}
void troca(int *x, int *y){ //função troca
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}