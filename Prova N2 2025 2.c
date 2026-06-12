#include <stdio.h>
#include <string.h>

#define NUM_LOJAS       5
#define MAX_PEDIDOS     100
#define NUM_TIPOS       3
#define ESTOQUE_EXCESSO 1000

static const char *NOMES_TIPO[NUM_TIPOS] = {"Tenis", "Sapatilha", "Chinelo"};
typedef struct {
    int qtd[NUM_TIPOS];
    int atendido;
} Pedido;
typedef struct {
    Pedido pedidos[MAX_PEDIDOS];
    int    num_pedidos;
} LojaPedidos;
typedef struct {
    int estoque[NUM_TIPOS];
    int total_fabricado[NUM_TIPOS];
} Estoque;
int  receber_pedido(LojaPedidos lojas[], int loja_id,
                    int tens, int sap, int chin,
                    Estoque *est);
void fabricar_calcados(Estoque *est, LojaPedidos lojas[],
                       int tipo, int qtd);
void mostrar_pedidos_loja(LojaPedidos lojas[], int loja_id);
void mostrar_demanda(LojaPedidos lojas[]);
void relatorio_geral(Estoque *est, LojaPedidos lojas[]);
int  loja_em_espera(LojaPedidos lojas[], int loja_id);
void tentar_atender_pedidos(Estoque *est, LojaPedidos lojas[]);
int  estoque_suficiente(Estoque *est, int tens, int sap, int chin);
void baixar_estoque(Estoque *est, int tens, int sap, int chin);
void ler_estoque_inicial(Estoque *est);
void exibir_menu(void);
int receber_pedido(LojaPedidos lojas[], int loja_id,
                   int tens, int sap, int chin,
                   Estoque *est)
{
    if (loja_em_espera(lojas, loja_id)) {
        return 0;
    }
    int idx = lojas[loja_id].num_pedidos;
    if (idx >= MAX_PEDIDOS) {
        printf("  [!] Limite de pedidos da loja %d atingido.\n", loja_id + 1);
        return 0;
    }
    lojas[loja_id].pedidos[idx].qtd[0] = tens;
    lojas[loja_id].pedidos[idx].qtd[1] = sap;
    lojas[loja_id].pedidos[idx].qtd[2] = chin;
    lojas[loja_id].pedidos[idx].atendido = 0;
    lojas[loja_id].num_pedidos++;
    if (estoque_suficiente(est, tens, sap, chin)) {
        baixar_estoque(est, tens, sap, chin);
        lojas[loja_id].pedidos[idx].atendido = 1;
        return 1;
    }
    return 2;
}
void fabricar_calcados(Estoque *est, LojaPedidos lojas[],
                       int tipo, int qtd)
{
    if (tipo < 0 || tipo >= NUM_TIPOS || qtd <= 0) {
        printf("  [!] Tipo ou quantidade invalidos.\n");
        return;
    }
    est->estoque[tipo]         += qtd;
    est->total_fabricado[tipo] += qtd;
    printf("  Fabricados %d pares de %s. Estoque atual: %d\n",
           qtd, NOMES_TIPO[tipo], est->estoque[tipo]);

    tentar_atender_pedidos(est, lojas);
}
void mostrar_pedidos_loja(LojaPedidos lojas[], int loja_id)
{
    printf("\n  === Pedidos da Loja %d ===\n", loja_id + 1);
    int n = lojas[loja_id].num_pedidos;
    if (n == 0) {
        printf("  Nenhum pedido registrado.\n");
    } else {
        for (int i = 0; i < n; i++) {
            Pedido *p = &lojas[loja_id].pedidos[i];
            printf("  Pedido %02d: Tenis=%d  Sapatilha=%d  Chinelo=%d  [%s]\n",
                   i + 1,
                   p->qtd[0], p->qtd[1], p->qtd[2],
                   p->atendido ? "ATENDIDO" : "EM ESPERA");
        }
    }
    if (loja_em_espera(lojas, loja_id)) {
        printf("  STATUS: Loja %d esta aguardando atendimento do ultimo pedido.\n",
               loja_id + 1);
    } else {
        printf("  STATUS: Loja %d nao possui pedido pendente.\n", loja_id + 1);
    }
}
void mostrar_demanda(LojaPedidos lojas[])
{
    int demanda[NUM_TIPOS] = {0, 0, 0};
    for (int l = 0; l < NUM_LOJAS; l++) {
        int n = lojas[l].num_pedidos;
        for (int p = 0; p < n; p++) {
            if (!lojas[l].pedidos[p].atendido) {
                for (int t = 0; t < NUM_TIPOS; t++) {
                    demanda[t] += lojas[l].pedidos[p].qtd[t];
                }
            }
        }
    }
    printf("\n  === Demanda (pedidos em espera) ===\n");
    for (int t = 0; t < NUM_TIPOS; t++) {
        printf("  %-10s: %d pares\n", NOMES_TIPO[t], demanda[t]);
    }
}
void relatorio_geral(Estoque *est, LojaPedidos lojas[])
{
    printf("\n========================================\n");
    printf("          RELATORIO GERAL\n");
    printf("========================================\n");
    int total_fab = 0;
    for (int t = 0; t < NUM_TIPOS; t++) total_fab += est->total_fabricado[t];
    printf("\n  -- Percentual fabricado por tipo --\n");
    if (total_fab == 0) {
        printf("  Nenhum calcado foi fabricado ainda.\n");
    } else {
        for (int t = 0; t < NUM_TIPOS; t++) {
            double pct = (double)est->total_fabricado[t] / total_fab * 100.0;
            printf("  %-10s: %5.1f%%  (%d pares fabricados)\n",
                   NOMES_TIPO[t], pct, est->total_fabricado[t]);
        }
    }
    printf("\n  -- Estoque atual --\n");
    int total_estoque = 0;
    for (int t = 0; t < NUM_TIPOS; t++) total_estoque += est->estoque[t];
    if (total_estoque == 0) {
        printf("  *** NENHUM ESTOQUE ***\n");
    } else {
        for (int t = 0; t < NUM_TIPOS; t++) {
            printf("  %-10s: %d pares\n", NOMES_TIPO[t], est->estoque[t]);
        }
        if (total_estoque > ESTOQUE_EXCESSO) {
            printf("  *** ESTOQUE EXCESSIVO (%d pares no total) ***\n",
                   total_estoque);
        }
    }
    mostrar_demanda(lojas);
    printf("\n  -- Lojas em espera --\n");
    int alguma = 0;
    for (int l = 0; l < NUM_LOJAS; l++) {
        if (loja_em_espera(lojas, l)) {
            printf("  Loja %d\n", l + 1);
            alguma = 1;
        }
    }
    if (!alguma) printf("  Nenhuma loja em espera.\n");
    printf("\n  -- Todos os pedidos --\n");
    for (int l = 0; l < NUM_LOJAS; l++) {
        mostrar_pedidos_loja(lojas, l);
    }
    printf("\n========================================\n");
}
int loja_em_espera(LojaPedidos lojas[], int loja_id)
{
    int n = lojas[loja_id].num_pedidos;
    if (n == 0) return 0;
    return !lojas[loja_id].pedidos[n - 1].atendido;
}
int estoque_suficiente(Estoque *est, int tens, int sap, int chin)
{
    return (est->estoque[0] >= tens &&
            est->estoque[1] >= sap  &&
            est->estoque[2] >= chin);
}
void baixar_estoque(Estoque *est, int tens, int sap, int chin)
{
    est->estoque[0] -= tens;
    est->estoque[1] -= sap;
    est->estoque[2] -= chin;
}
void tentar_atender_pedidos(Estoque *est, LojaPedidos lojas[])
{
    for (int l = 0; l < NUM_LOJAS; l++) {
        int n = lojas[l].num_pedidos;
        if (n == 0) continue;

        Pedido *ultimo = &lojas[l].pedidos[n - 1];
        if (!ultimo->atendido) {
            int t = ultimo->qtd[0];
            int s = ultimo->qtd[1];
            int c = ultimo->qtd[2];
            if (estoque_suficiente(est, t, s, c)) {
                baixar_estoque(est, t, s, c);
                ultimo->atendido = 1;
                printf("  [*] Pedido da Loja %d ATENDIDO automaticamente!\n", l + 1);
            }
        }
    }
}
void ler_estoque_inicial(Estoque *est)
{
    printf("\n=== Estoque inicial ===\n");
    for (int t = 0; t < NUM_TIPOS; t++) {
        do {
            printf("  Informe a quantidade de pares de %s em estoque: ",
                   NOMES_TIPO[t]);
            scanf("%d", &est->estoque[t]);
            if (est->estoque[t] < 0)
                printf("  [!] Valor invalido. Digite um numero >= 0.\n");
        } while (est->estoque[t] < 0);
        est->total_fabricado[t] = 0;
    }
}
void exibir_menu(void)
{
    printf("\n+-------------------------------+\n");
    printf("|    FABRICA DE CALCADOS        |\n");
    printf("+-------------------------------+\n");
    printf("| [1] Receber pedido            |\n");
    printf("| [2] Fabricar calcados         |\n");
    printf("| [3] Pedidos de uma loja       |\n");
    printf("| [4] Mostrar demanda           |\n");
    printf("| [5] Relatorio geral           |\n");
    printf("| [0] Sair                      |\n");
    printf("+-------------------------------+\n");
    printf("  Opcao: ");
}
int main(void)
{
    Estoque     est;
    LojaPedidos lojas[NUM_LOJAS];
    memset(&est,  0, sizeof(est));
    memset(lojas, 0, sizeof(lojas));
    ler_estoque_inicial(&est);
    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
        case 1: {
            int loja, tens, sap, chin;
            printf("\n  Numero da loja (1-%d): ", NUM_LOJAS);
            scanf("%d", &loja);
            if (loja < 1 || loja > NUM_LOJAS) {
                printf("  [!] Loja invalida.\n");
                break;
            }
            loja--;
            printf("  Pares de Tenis   : "); scanf("%d", &tens);
            printf("  Pares de Sapatilha: "); scanf("%d", &sap);
            printf("  Pares de Chinelo : "); scanf("%d", &chin);
            if (tens < 0 || sap < 0 || chin < 0) {
                printf("  [!] Quantidades nao podem ser negativas.\n");
                break;
            }
            int ret = receber_pedido(lojas, loja, tens, sap, chin, &est);
            switch (ret) {
            case 0:
                printf("  Pedido NAO registrado: loja %d esta em espera.\n",
                       loja + 1);
                break;
            case 1:
                printf("  Pedido registrado e ATENDIDO com sucesso!\n");
                break;
            case 2:
                printf("  Pedido registrado. Loja %d ficou EM ESPERA"
                       " (estoque insuficiente).\n", loja + 1);
                break;
            }
            break;
        }
        case 2: {
            printf("\n  Tipo de calcado:\n");
            for (int t = 0; t < NUM_TIPOS; t++)
                printf("    [%d] %s\n", t + 1, NOMES_TIPO[t]);
            printf("  Opcao: ");
            int tipo; scanf("%d", &tipo);
            tipo--;
            if (tipo < 0 || tipo >= NUM_TIPOS) {
                printf("  [!] Tipo invalido.\n");
                break;
            }
            int qtd;
            printf("  Quantidade de pares a fabricar: ");
            scanf("%d", &qtd);
            if (qtd <= 0) {
                printf("  [!] Quantidade deve ser maior que zero.\n");
                break;
            }
            fabricar_calcados(&est, lojas, tipo, qtd);
            break;
        }
        case 3: {
            int loja;
            printf("\n  Numero da loja (1-%d): ", NUM_LOJAS);
            scanf("%d", &loja);
            if (loja < 1 || loja > NUM_LOJAS) {
                printf("  [!] Loja invalida.\n");
                break;
            }
            mostrar_pedidos_loja(lojas, loja - 1);
            break;
        }
        case 4:
            mostrar_demanda(lojas);
            break;
        case 5:
            relatorio_geral(&est, lojas);
            break;
        case 0:
            printf("\n  Encerrando o sistema. Ate logo!\n");
            break;
        default:
            printf("  [!] Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}
