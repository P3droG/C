#include <stdio.h>

int InstalacaoNovoAparelho(int p, int ap, int totalAparelhos[3], int codigo[3][30], int servico[3][30])
{

    if (totalAparelhos[p - 1] >= 30)
    {
        printf("Limite máximo de aparelhos atingido para o prédio %d. Cadastro não realizado.\n", p);
        return 2;
    }
    for (int i = 0; i < totalAparelhos[p - 1]; i++)
    {
        if (codigo[p - 1][i] == ap)
        {
            printf("Código já existe nesse prédio. Cadastro não realizado.\n");
            return 1;
        }
    }
    codigo[p - 1][totalAparelhos[p - 1]] = ap;
    servico[p - 1][totalAparelhos[p - 1]] = 0;
    totalAparelhos[p - 1]++;
    printf("Aparelho cadastrado com sucesso.\n");
    return 0;
}

int SolicitarServico(int p, int ap, int problema, int totalAparelhos[3], int codigo[3][30], int servico[3][30])
{
    for (int i = 0; i < totalAparelhos[p - 1]; i++)
    {
        if (codigo[p - 1][i] == ap)
        {
            if (servico[p - 1][i] != 0)
            {
                return 1; // ja tem
            }
            servico[p - 1][i] = problema;
            return 0; // salvou
        }
    }
    return 2; // nao achou
}

int ServicoConcluido(int p, int ap, int totalAparelhos[3], int codigo[3][30], int servico[3][30])
{
    for (int i = 0; i < totalAparelhos[p - 1]; i++)
    {
        if (codigo[p - 1][i] == ap)
        {
            servico[p - 1][i] = 0;
            return 1; // removeu solicitação
        }
    }
    return 2; // nao achou
}
void ImprimirRelatorio(int totalAparelhos[3], int codigo[3][30], int servico[3][30])
{
    for (int p = 0; p < 3; p++)
    {
        for (int ap = 0; ap < totalAparelhos[p]; ap++)
        {
            if (servico[p][ap] != 0)
            {
                printf("Predio: %d", p + 1);
                printf("Codigo: %d", codigo[p][ap]);

                if (servico[p][ap] == 1)
                {
                    printf("Problema: Aparelho nao liga");
                }
                else if (servico[p][ap] == 2)
                {
                    printf("Problema: Aparelho liga mas nao resfria");
                }
                else
                {
                    printf("Problema: Vazamento de agua");
                }
            }
        }
    }

    for (int p = 0; p < 3; p++)
    {
        int contador = 0;
        for (int ap = 0; ap < totalAparelhos[p]; ap++)
        {
            if (servico[p][ap] != 0)
            {
                contador++;
            }
        }
        printf("Predio %d", p + 1);
        printf("Total de aparelhos: %d", totalAparelhos[p]);
        printf("Precisam de assistencia: %d", contador);
    }
}

int main()
{
    int totalAparelhos[3], codigo[3][30], servico[3][30];
    int ap, p, opcao, problema, resultado;

    for (p = 1; p <= 3; p++)
    {
        printf("Quantos aparelhos existem no prédio %d? ", p);
        scanf("%d", &totalAparelhos[p - 1]);
        for (ap = 1; ap <= totalAparelhos[p - 1]; ap++)
        {
            codigo[p - 1][ap - 1] = p * 100 + ap;
            servico[p - 1][ap - 1] = 0;
        }
    }
    while (1)
    {
        printf("[1] Instalar aparelho");
        printf("[2] Solicitar servico");
        printf("[3] Servico concluido");
        printf("[4] Imprimir relatorio");
        printf("[5] Sair");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Em qual prédio deseja cadastrar o aparelho? ");
            scanf("%d", &p);
            printf("Qual o código do aparelho? ");
            scanf("%d", &ap);
            InstalacaoNovoAparelho(p, ap, totalAparelhos, codigo, servico);
            break;
        case 2:
            printf("Em qual prédio deseja cadastrar o aparelho? ");
            scanf("%d", &p);
            printf("Qual o código do aparelho? ");
            scanf("%d", &ap);
            printf("Qual o problema identificado? ");
            scanf("%d", &problema);

            resultado = SolicitarServico(p, ap, problema, totalAparelhos, codigo, servico);
            if (resultado == 0)
            {
                printf("Servico solicitado com sucesso.");
            }
            else if (resultado == 1)
            {
                printf("Este aparelho ja possui uma solicitacao.\n");
            }
            else
            {
                printf("Erro, aparelho nao encontrado");
            }
            break;
        case 3:
            printf("Em qual prédio deseja cadastrar o aparelho? ");
            scanf("%d", &p);
            printf("Qual o código do aparelho? ");
            scanf("%d", &ap);
            resultado = ServicoConcluido(p, ap, totalAparelhos, codigo, servico);
            if (resultado == 1)
            {
                printf("Solicitação removida.");
            }
            else
            {
                printf("Erro, aparelho não encontrado");
            }
            break;
        case 4:
            ImprimirRelatorio(totalAparelhos, codigo, servico);
            break;
        case 5:
            return 0;
        }
    }
}