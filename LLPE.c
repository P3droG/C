#include <stdio.h>

#define NUM_SABORES 4
#define NUM_TAMANHOS 2
#define MAX_PEDIDOS 200

typedef struct
{
    int sabor;
    int tamanho;
    int quantidade;
    int localidade;
    int atendido;
    float valor_total;
} Pedidos;

typedef struct
{
    int estoque[NUM_SABORES][NUM_TAMANHOS];
    float preco[NUM_SABORES][NUM_TAMANHOS];
    float frete[3];
    Pedidos pedidos[MAX_PEDIDOS];
    int num_pedidos;
} Distribuidora;

// funções auxiliares

void imprimirSabor(int s)
{
    if (s == 0)
        printf("Guarana");
    else if (s == 1)
        printf("Laranja");
    else if (s == 2)
        printf("Limao");
    else
        printf("Cola");
}

void imprimirTamanho(int t)
{
    if (t == 0)
        printf("Latinha");
    else
        printf("Garrafa 2L");
}

void imprimirLocalidade(int l)
{
    if (l == 0)
        printf("Luzimangues");
    else if (l == 1)
        printf("Sul de Palmas");
    else
        printf("Norte de Palmas");
}

int lerSabor()
{
    int s;
    printf("Sabor (0=Guarana, 1=Laranja, 2=Limao, 3=Cola): ");
    scanf("%d", &s);
    return s;
}

int lerTamanho()
{
    int t;
    printf("Tamanho (0=Latinha, 1=Garrafa 2L): ");
    scanf("%d", &t);
    return t;
}

// funcoes principais

void zera(Distribuidora *dist) // zera estoque e o numero de pedidos
{
    for (int s = 0; s < NUM_SABORES; s++)
    {
        for (int t = 0; t < NUM_TAMANHOS; t++)
        {
            dist->estoque[s][t] = 0;
        }
    }
    dist->num_pedidos = 0;
}

// Aplica o preco pra cd sabor e tamanho e o frete de cd lugar
void leiturainicial(Distribuidora *dist)
{
    printf("===CADASTRO INICIAL===\n");
    for (int s = 0; s < NUM_SABORES; s++)

        for (int t = 0; t < NUM_TAMANHOS; t++)
        {
            imprimirSabor(s);
            printf(" - ");
            imprimirTamanho(t);
            printf(": R$ ");
            scanf("%f", &dist->preco[s][t]);
        }
    for (int f = 0; f < 3; f++)
    {
        imprimirLocalidade(f);
        printf(": R$ ");
        scanf("%f", &dist->frete[f]);
    }
}

// [1] Receber Carga
void receberCarga(Distribuidora *dist)
{
    int s, t, qntd;
    printf("Digite o sabor (0-Guarana, 1-Laranja, 2-Limao, 3-Cola): ");
    scanf("%d", &s);
    printf("Digite o tamanho (0-Lata, 1-Garrafa): ");
    scanf("%d", &t);
    printf("Quantidade recebida: ");
    scanf("%d", &qntd);
    dist->estoque[s][t] += qntd;

    for (int i = 0; i < dist->num_pedidos; i++) // verificando pendentes de atendimento
    {
        if (dist->pedidos[i].atendido == 0)
        {
            s = dist->pedidos[i].sabor;
            t = dist->pedidos[i].tamanho;
            qntd = dist->pedidos[i].quantidade;

            if (dist->estoque[s][t] >= qntd) // atendedendo se tiver estque suficiente
            {
                dist->estoque[s][t] -= qntd;
                dist->pedidos[i].atendido = 1;
                printf("Pedido #%d atendido: %d x ", i + 1, qntd);
                imprimirSabor(s);
                printf(" ");
                imprimirTamanho(t);
                printf("\n");
            }
        }
    }
}

void pedidoVarejo(Distribuidora *dist)
{
    int sabores[MAX_PEDIDOS];
    int tamanhos[MAX_PEDIDOS];
    int quantidades[MAX_PEDIDOS];
    int atendidas[MAX_PEDIDOS];
    int n = 0, opcao, s, t, qntd, i;
    float total = 0.0;

    printf("\n=== PEDIDO VAREJO ===\n");

    while (1)
    {
        printf("\n[1] Adicionar item  [0] Finalizar pedido\nOpcao: ");
        scanf("%d", &opcao);
        if (opcao == 0)
            break;

        s = lerSabor();
        t = lerTamanho();
        printf("Quantidade: ");
        scanf("%d", &qntd);
        sabores[n] = s;
        tamanhos[n] = t;
        quantidades[n] = qntd;

        if (dist->estoque[s][t] >= qntd)
        {
            atendidas[n] = qntd;
        }
        else
        {
            atendidas[n] = dist->estoque[s][t];
            printf("AVISO: apenas %d unidades de ", dist->estoque[s][t]);
            imprimirSabor(s);
            printf(" ");
            imprimirTamanho(t);
            printf(" em estoque.\n");
        }
        n++;
    }

    if (n == 0)
    {
        printf("Nenhum item adicionado.\n");
        return;
    }

    printf("\n--- Resumo do Pedido ---\n");
    for (i = 0; i < n; i++)
    {
        float subtotal = atendidas[i] * dist->preco[sabores[i]][tamanhos[i]];
        total += subtotal;
        imprimirSabor(sabores[i]);
        printf(" ");
        imprimirTamanho(tamanhos[i]);
        printf(": pedido %d, atendido %d - R$ %.2f\n",
               quantidades[i], atendidas[i], subtotal);
    }
    printf("TOTAL: R$ %.2f\n", total);

    printf("\n[1] Efetivar  [0] Cancelar\nOpcao: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        for (i = 0; i < n; i++)
            dist->estoque[sabores[i]][tamanhos[i]] -= atendidas[i];
        printf("Pedido efetivado!\n");
    }
    else
    {
        printf("Pedido cancelado.\n");
    }
}
int pedidoAtacado(Distribuidora *dist)
{
    int s, t, qntd, loc;
    float frete_valor, total;
    Pedidos p;

    if (dist->num_pedidos >= MAX_PEDIDOS)
        return 2;

    printf("\n=== PEDIDO ATACADO ===\n");
    s = lerSabor();
    t = lerTamanho();
    printf("Quantidade: ");
    scanf("%d", &qntd);
    printf("Localidade (0=Luzimangues, 1=Sul Palmas, 2=Norte Palmas): ");
    scanf("%d", &loc);

    if (qntd > 500)
        frete_valor = 0.0;
    else
        frete_valor = dist->frete[loc];

    total = qntd * dist->preco[s][t] + frete_valor;

    p.sabor = s;
    p.tamanho = t;
    p.quantidade = qntd;
    p.localidade = loc;
    p.valor_total = total;

    if (dist->estoque[s][t] >= qntd)
    {
        dist->estoque[s][t] -= qntd;
        p.atendido = 1;
    }
    else
    {
        p.atendido = 0;
    }

    if (frete_valor == 0.0)
        printf("Frete: GRATIS (mais de 500 itens)\n");
    else
    {
        printf("Frete para ");
        imprimirLocalidade(loc);
        printf(": R$ %.2f\n", frete_valor);
    }
    printf("Valor total: R$ %.2f\n", total);

    dist->pedidos[dist->num_pedidos] = p;
    dist->num_pedidos++;

    if (p.atendido == 1)
        return 0;
    else
        return 1;
}

// [2] Receber pedido
void receberPedido(Distribuidora *dist)
{
    int tipo, resultado;

    printf("\n=== RECEBER PEDIDO ===\n");
    printf("[1] Varejo\n[2] Atacado\nOpcao: ");
    scanf("%d", &tipo);

    if (tipo == 1)
    {
        pedidoVarejo(dist);
    }
    else if (tipo == 2)
    {
        resultado = pedidoAtacado(dist);
        if (resultado == 0)
            printf("Pedido ATENDIDO.\n");
        else if (resultado == 1)
            printf("Pedido NAO ATENDIDO (estoque insuficiente).\n");
        else if (resultado == 2)
            printf("Limite de pedidos atingido!\n");
        else
            printf("Dados invalidos!\n");
    }
    else
    {
        printf("Opcao invalida.\n");
    }
}

//[3] Editar valores
void editarValores(Distribuidora *dist)
{
    int opcao, s, t, loc;

    printf("\n=== EDITAR VALORES ===\n");
    printf("[1] Consultar preco\n[2] Editar preco\n[3] Consultar frete\n[4] Editar frete\nOpcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        s = lerSabor();
        t = lerTamanho();
        printf("Preco de ");
        imprimirSabor(s);
        printf(" ");
        imprimirTamanho(t);
        printf(": R$ %.2f\n", dist->preco[s][t]);
        break;

    case 2:
        s = lerSabor();
        t = lerTamanho();
        printf("Novo preco: R$ ");
        scanf("%f", &dist->preco[s][t]);
        printf("Preco atualizado!\n");
        break;

    case 3:
        printf("Frete Luzimangues:   R$ %.2f\n", dist->frete[0]);
        printf("Frete Sul de Palmas: R$ %.2f\n", dist->frete[1]);
        printf("Frete Norte Palmas:  R$ %.2f\n", dist->frete[2]);
        break;

    case 4:
        printf("Localidade (0=Luzimangues, 1=Sul, 2=Norte): ");
        scanf("%d", &loc);
        printf("Novo frete para ");
        imprimirLocalidade(loc);
        printf(": R$ ");
        scanf("%f", &dist->frete[loc]);
        printf("Frete atualizado!\n");
        break;
    }
}

//[4] Relatorio por sabor
void relatorioPorSabor(Distribuidora *dist)
{
    int s;
    printf("\n=== RELATORIO POR SABOR ===\n");
    s = lerSabor();
    imprimirSabor(s);
    printf("\n  Latinhas:    %d unidades\n", dist->estoque[s][0]);
    printf("  Garrafas 2L: %d unidades\n", dist->estoque[s][1]);
}

//[5] Relatorio geral
void relatorioGeral(Distribuidora *dist)
{
    int s, t, i;
    int total_latinhas = 0, total_garrafas = 0, total_geral = 0;
    int atendidos = 0, nao_atendidos = 0;

    printf("\n=== RELATORIO GERAL ===\n");

    for (s = 0; s < NUM_SABORES; s++)
        for (t = 0; t < NUM_TAMANHOS; t++)
            total_geral += dist->estoque[s][t];

    printf("\n--- Estoque por Sabor ---\n");
    for (s = 0; s < NUM_SABORES; s++)
    {
        int total_sabor = dist->estoque[s][0] + dist->estoque[s][1];
        float pct = 0.0;
        if (total_geral > 0)
            pct = (float)total_sabor / total_geral * 100.0;

        imprimirSabor(s);
        printf(": %d latinhas, %d garrafas | Total: %d (%.1f%%)\n",
               dist->estoque[s][0], dist->estoque[s][1], total_sabor, pct);

        total_latinhas += dist->estoque[s][0];
        total_garrafas += dist->estoque[s][1];
    }

    printf("\n--- Totais ---\n");
    printf("Total latinhas:  %d\n", total_latinhas);
    printf("Total garrafas:  %d\n", total_garrafas);

    for (i = 0; i < dist->num_pedidos; i++)
    {
        if (dist->pedidos[i].atendido == 1)
            atendidos++;
        else
            nao_atendidos++;
    }

    printf("\n--- Pedidos ---\n");
    printf("Atendidos:     %d\n", atendidos);
    printf("Nao atendidos: %d\n", nao_atendidos);

    if (nao_atendidos > 0)
    {
        printf("\n--- Pedidos Nao Atendidos ---\n");
        for (i = 0; i < dist->num_pedidos; i++)
        {
            if (dist->pedidos[i].atendido == 0)
            {
                printf("Pedido #%d: %d x ", i + 1, dist->pedidos[i].quantidade);
                imprimirSabor(dist->pedidos[i].sabor);
                printf(" ");
                imprimirTamanho(dist->pedidos[i].tamanho);
                printf(" | Local: ");
                imprimirLocalidade(dist->pedidos[i].localidade);
                printf(" | Valor: R$ %.2f\n", dist->pedidos[i].valor_total);
            }
        }
    }
}

// Função principal do programa
int main()
{
    Distribuidora dist;
    int opcao;

    zera(&dist);
    leiturainicial(&dist);

    while (1)
    {
        printf("\n=============================\n");
        printf("  DISTRIBUIDORA DE BEBIDAS   \n");
        printf("=============================\n");
        printf("[1] Receber carga\n");
        printf("[2] Receber pedido\n");
        printf("[3] Editar valores\n");
        printf("[4] Relatorio por sabor\n");
        printf("[5] Relatorio geral\n");
        printf("[0] Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            receberCarga(&dist);
            break;
        case 2:
            receberPedido(&dist);
            break;
        case 3:
            editarValores(&dist);
            break;
        case 4:
            relatorioPorSabor(&dist);
            break;
        case 5:
            relatorioGeral(&dist);
            break;
        case 0:
            printf("Encerrando...\n");
            return 0;
        default:
            printf("Opcao invalida!\n");
        }
    }
}
