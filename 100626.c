typedef struct
{
    char nome[50];
    float peso, nota;
    int idade;
}pessoa;

void lerPessoa(pessoa *p)
{
    scanf("%s%f%f%d", p->nome, &p->peso, &p->nota, &p->idade);
}

void imprimirPessoa(pessoa p)
{
    printf("%s%f%f%d", p.nome, p.peso, p.nota, p.idade);
}
void imprimirGrupo(pessoa grupo[], int t)
{
    for(int i=0; i<t; i++)
    {
        imprimirPessoa(grupo[i]);
    }
}
int main()
{
    pessoa pessoa1, pessoa2, grupo[100];
    lerPessoa(&pessoa1);
    lerPessoa(&pessoa2);
    imprimirPessoa(pessoa1);
    imprimirPessoa(pessoa2);
    imprimirPessoa(grupo[0]);
    imprimirGrupo(grupo, 100);
}