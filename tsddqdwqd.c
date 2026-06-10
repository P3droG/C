#include <stdio.h>

// A função recebe um parâmetro por valor (uma cópia)
void dobrarValor(int num) {
    num = num * 2;
    printf("Valor dentro da função: %d\n", num);
}

int main() {
    int x = 10;
    
    dobrarValor(x);
    
    // O valor original em 'main' não foi alterado
    printf("Valor original em main: %d\n", x);
    
    return 0;
}
