#include <stdio.h>

int fatorial(int num){
    if(num==0) return 1;
    return(num * fatorial(num-1));
}
int main(){
    int num;
    scanf("%d", &num);
    printf("%d", fatorial(num));
}