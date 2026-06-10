#include <stdio.h>

typedef struct
{
    char nome[100];
    int idade, sala;
}cliente;

int CadastrarCliente()
{
    scanf("%s%d%d", cliente.nome, &cliente.idade, &cliente.sala);
    return 0;
}

void ClienteIndice()
{

}

void ClienteNome()
{

}

void ClienteTodos()
{

}

int EditarCliente()
{

}

int main()
{
    int A;
    switch(A)
    {
        case 1:
            CadastrarCliente();
            break;
        case 2:
            ClienteIndice();
            break;
        case 3:
            ClienteNome();
            break;
        case 4:
            ClienteTodos();
            break;
        case 5:
            EditarCliente();
            break;
    }
}