#include <stdio.h>

#define AN 60
#define AB 3

typedef struct
{
    int codigo;
    int tipo;
    char sexo;
    char idade[10];
    char tutor[20];
} Animais;

int main()
{
    Animais dados[AN][AB];
    int opcao;
    int i, j;
    int qntd[AB];

    for (i = 0; i < AN; i++)
    {
        for (j = 0; i < AB; i++)
        {
            dados[i][j].ocupado = 0;
            dados[i][j].tutor[0] = '\0';
        }
    }

    for (j = 0; j < AB; j++)
    {
        qntd[j] = 0;
    }

    printf("\n===== ONG DE ANIMAIS =====\n");
    printf("1 - Cadastrar pet\n");
    printf("2 - Buscar pet para adocao\n");
    printf("3 - Adotar\n");
    printf("4 - Relatorio por abrigo\n");
    printf("5 - Mostrar todos\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        cadastrar();
        break;

    case 2:
        buscapet();
        break;

    case 3:
        adotar();
        break;

    case 4:
        relatorioParcial();
        break;

    case 5:
        relatorioTotal();
        break;
    }
}
