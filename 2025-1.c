#include <stdio.h>

#define MAX_ANIMAIS 60
#define NUM_ABRIGOS 3

typedef struct
{
    int codigo;
    int tipo;
    char sexo;
    char idade;
    char tutor[50];
    int ocupado;

} Animal;

int proximoCodigo = 1;

void ler(Animal *a);
void registrar(Animal a, Animal dados[][NUM_ABRIGOS], int qtd[], int abrigo);
void mostrar(Animal dados[][NUM_ABRIGOS], int qtd[]);

void cadastrar(Animal dados[][NUM_ABRIGOS], int qtd[]);
void buscaAdocao(Animal dados[][NUM_ABRIGOS], int qtd[]);
void adotar(Animal dados[][NUM_ABRIGOS], int qtd[]);
void relatorio(Animal dados[][NUM_ABRIGOS], int qtd[]);

void exibirAnimal(Animal a);

int main()
{
    Animal dados[MAX_ANIMAIS][NUM_ABRIGOS];

    int qtd[NUM_ABRIGOS];

    int i, j;

    for(i = 0; i < MAX_ANIMAIS; i++)
    {
        for(j = 0; j < NUM_ABRIGOS; j++)
        {
            dados[i][j].ocupado = 0;
            dados[i][j].tutor[0] = '\0';
        }
    }

    for(j = 0; j < NUM_ABRIGOS; j++)
    {
        qtd[j] = 0;
    }

    int opcao;

    do
    {
        printf("\n===== ONG DE ANIMAIS =====\n");
        printf("1 - Cadastrar pet\n");
        printf("2 - Buscar pet para adocao\n");
        printf("3 - Adotar\n");
        printf("4 - Relatorio por abrigo\n");
        printf("5 - Mostrar todos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                cadastrar(dados, qtd);
                break;

            case 2:
                buscaAdocao(dados, qtd);
                break;

            case 3:
                adotar(dados, qtd);
                break;

            case 4:
                relatorio(dados, qtd);
                break;

            case 5:
                mostrar(dados, qtd);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

/* FUNCAO LER */
void ler(Animal *a)
{
    int idadeOpcao;

    a->codigo = proximoCodigo++;

    printf("\nTipo:\n");
    printf("1 - Gato\n");
    printf("2 - Cachorro pequeno\n");
    printf("3 - Cachorro medio\n");
    printf("4 - Cachorro grande\n");
    printf("Escolha: ");
    scanf("%d", &a->tipo);

    printf("Sexo (M/F): ");
    scanf(" %c", &a->sexo);

    printf("Idade:\n");
    printf("1 - Filhote\n");
    printf("2 - Adulto\n");
    printf("Escolha: ");
    scanf("%d", &idadeOpcao);

    if(idadeOpcao == 1)
        a->idade = 'F';
    else
        a->idade = 'A';

    printf("Tutor (digite SEM_TUTOR caso nao tenha): ");
    scanf("%s", a->tutor);

    a->ocupado = 1;
}

/* FUNCAO REGISTRAR */
void registrar(Animal a, Animal dados[][NUM_ABRIGOS], int qtd[], int abrigo)
{
    dados[qtd[abrigo]][abrigo] = a;
    qtd[abrigo]++;
}

/* FUNCAO MOSTRAR */
void mostrar(Animal dados[][NUM_ABRIGOS], int qtd[])
{
    int abrigo;
    int i;

    for(abrigo = 0; abrigo < NUM_ABRIGOS; abrigo++)
    {
        printf("\n=== ABRIGO %d ===\n", abrigo + 1);

        if(qtd[abrigo] == 0)
        {
            printf("Sem animais cadastrados.\n");
        }
        else
        {
            for(i = 0; i < qtd[abrigo]; i++)
            {
                exibirAnimal(dados[i][abrigo]);
            }
        }
    }
}

void cadastrar(Animal dados[][NUM_ABRIGOS], int qtd[])
{
    int abrigo;
    Animal animal;

    printf("Escolha o abrigo (1 a 3): ");
    scanf("%d", &abrigo);

    abrigo--;

    if(abrigo < 0 || abrigo >= NUM_ABRIGOS)
    {
        printf("Abrigo invalido.\n");
        return;
    }

    if(qtd[abrigo] >= MAX_ANIMAIS)
    {
        printf("Abrigo lotado.\n");
        return;
    }

    ler(&animal);
    registrar(animal, dados, qtd, abrigo);
    mostrar(dados, qtd);
}

void buscaAdocao(Animal dados[][NUM_ABRIGOS], int qtd[])
{
    int tipo;
    int abrigo;
    int i;
    int encontrou = 0;

    printf("Informe o tipo do animal: ");
    scanf("%d", &tipo);

    for(abrigo = 0; abrigo < NUM_ABRIGOS; abrigo++)
    {
        for(i = 0; i < qtd[abrigo]; i++)
        {
            if(dados[i][abrigo].tipo == tipo)
            {
                if(dados[i][abrigo].tutor[0] == 'S')
                {
                    exibirAnimal(dados[i][abrigo]);
                    encontrou = 1;
                }
            }
        }
    }

    if(encontrou == 0)
    {
        printf("Nenhum animal disponivel.\n");
    }
}

void adotar(Animal dados[][NUM_ABRIGOS], int qtd[])
{
    int codigo;
    int abrigo;
    int i;

    printf("Codigo do animal: ");
    scanf("%d", &codigo);

    for(abrigo = 0; abrigo < NUM_ABRIGOS; abrigo++)
    {
        for(i = 0; i < qtd[abrigo]; i++)
        {
            if(dados[i][abrigo].codigo == codigo)
            {
                if(dados[i][abrigo].tutor[0] != 'S')
                {
                    char resposta;

                    printf("Ja possui tutor (%s)\n",
                           dados[i][abrigo].tutor);

                    printf("Deseja alterar? (S/N): ");
                    scanf(" %c", &resposta);

                    if(resposta != 'S' && resposta != 's')
                    {
                        return;
                    }
                }

                printf("Novo tutor: ");
                scanf("%s", dados[i][abrigo].tutor);

                printf("Adocao registrada!\n");
                return;
            }
        }
    }

    printf("Codigo nao encontrado.\n");
}

void relatorio(Animal dados[][NUM_ABRIGOS], int qtd[])
{
    int abrigo;
    int i;

    int gatos = 0;
    int cachorros = 0;
    int filhotes = 0;
    int semTutor = 0;

    printf("Abrigo (1 a 3): ");
    scanf("%d", &abrigo);

    abrigo--;

    if(abrigo < 0 || abrigo >= NUM_ABRIGOS)
    {
        printf("Abrigo invalido.\n");
        return;
    }

    for(i = 0; i < qtd[abrigo]; i++)
    {
        if(dados[i][abrigo].tipo == 1)
            gatos++;
        else
            cachorros++;

        if(dados[i][abrigo].idade == 'F')
            filhotes++;

        if(dados[i][abrigo].tutor[0] == 'S')
            semTutor++;
    }

    printf("\n=== RELATORIO ===\n");
    printf("Gatos: %d\n", gatos);
    printf("Cachorros: %d\n", cachorros);
    printf("Filhotes: %d\n", filhotes);

    if(qtd[abrigo] > 0)
    {
        printf("Sem tutor: %.2f%%\n",
               (float)semTutor * 100 / qtd[abrigo]);
    }
}

void exibirAnimal(Animal a)
{
    printf("\nCodigo: %d\n", a.codigo);

    switch(a.tipo)
    {
        case 1:
            printf("Tipo: Gato\n");
            break;

        case 2:
            printf("Tipo: Cachorro pequeno\n");
            break;

        case 3:
            printf("Tipo: Cachorro medio\n");
            break;

        case 4:
            printf("Tipo: Cachorro grande\n");
            break;
    }

    printf("Sexo: %c\n", a.sexo);

    if(a.idade == 'F')
        printf("Idade: Filhote\n");
    else
        printf("Idade: Adulto\n");

    printf("Tutor: %s\n", a.tutor);
}