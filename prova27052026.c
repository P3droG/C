#include <stdio.h>

//nao utilizar variaveis globais. Todos os dados devem ser passados por parâmetro para as funções. Para isso, utilize vetores e matrizes para armazenar os dados dos aparelhos e suas solicitações de serviço.
//O programa deve ser modularizado, ou seja, cada função deve realizar uma tarefa específica.
//cadastra dados iniciais (Perguntar quantos aparelhos existem em cada prédio. Registrar para cada prédio, todos seus aparelhos. Os códigos dos aparelhos nesta primeira etapa devem se gerados
//automaticamente. Estes aparelhos inicialmente não tem solicitação de serviço)

//1 Instalação de novo aparelho: Cadastra um novo aparelho dados o prédio e o código do aparelho. (o codigo agora é recebido como entrada) Não permitir códigos iguais em um mesmo prédio.
//No momento do cadastro o aparelho nao tem solicitação de serviço ainda)
//Para os demais parâmetros que forem necessários, explique cada um deles.
//Esta função deve retornar 0 para aparelho cadastrado normalmente, 1 para quando já existe este código no prédio e 2 para quando o limite máximo já foi atingido.
//Esta função deve receber como parâmetro o código do aparelho e o prédio em que foi instalado estes dois parâmetros devem ser passado por valor.
//se você quiser passar o código do aparelho e o prédio por referência, você pode usar ponteiros. Por exemplo, a função poderia ser definida como:

//explicando os demais parâmetros que foram necessários na funcao InstalacaoNovoAparelho:
//totalAparelhos: um vetor que armazena a quantidade de aparelhos cadastrados em cada prédio. Ele é necessário para verificar se o limite máximo de aparelhos foi atingido e para determinar a posição correta para cadastrar um novo aparelho.
//codigo: uma matriz que armazena os códigos dos aparelhos para cada prédio. Ele é necessário para verificar se o código do novo aparelho já existe no prédio e para armazenar o código do novo aparelho quando ele for cadastrado.
//serviço: uma matriz que armazena o status de solicitação de serviço para cada aparelho em cada prédio. Ele é necessário para inicializar o status de solicitação de serviço do novo aparelho como 0 (sem solicitação) quando ele for cadastrado.
// a funcao InstalacaoNovoAparelho recebe como parametro o código do aparelho e o prédio por valor? Sim, a função InstalacaoNovoAparelho recebe o código do aparelho e o prédio por valor. Isso significa que quando você chama a função, você passa os valores do código do aparelho e do prédio diretamente para a função, e a função trabalha com esses valores sem modificar as variáveis originais fora da função. Em qual linha? Na linha onde a função é definida, os parâmetros são declarados como int p e int ap, o que indica que eles são passados por valor. Por exemplo:
// Por exemplo, se você chamar a função assim: InstalacaoNovoAparelho(totalAparelhos, codigo, serviço), os valores de totalAparelhos, codigo e serviço são passados para a função, mas as variáveis originais fora da função não serão modificadas diretamente por esses parâmetros.
// e a explicação dos parametros
int InstalacaoNovoAparelho(int totalAparelhos[3], int codigo[3][30], int serviço[3][30]){
    int p, ap;
    printf("Em qual prédio deseja cadastrar o aparelho? ");
    scanf("%d", &p);
    if(totalAparelhos[p-1] >= 30){
        printf("Limite máximo de aparelhos atingido para o prédio %d. Cadastro não realizado.\n", p);
        return 2;
    }
    printf("Qual o código do aparelho? ");
    scanf("%d", &ap);
    for(int i=0; i<totalAparelhos[p-1]; i++){
        if(codigo[p-1][i] == ap){
            printf("Código já existe nesse prédio. Cadastro não realizado.\n");
            return 1;
        }
    }
    codigo[p-1][totalAparelhos[p-1]] = ap;
    serviço[p-1][totalAparelhos[p-1]] = 0; // Inicialmente sem solicitação de serviço
    totalAparelhos[p-1]++;
    printf("Aparelho cadastrado com sucesso.\n");
    return 0;
}

int main(){
    int totalAparelhos[3], codigo[3][30], serviço[3][30];
    for(int p=1; p<=3; p++){
        printf("Quantos aparelhos existem no prédio %d? ", p);
        scanf("%d", &totalAparelhos[p-1]);
        for(int ap=1; ap<=totalAparelhos[p-1]; ap++){
            codigo[p-1][ap-1] = p*100 + ap;
            serviço[p-1][ap-1] = 0;
        }
    }    
}