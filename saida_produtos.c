#include "saida_produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "produto.h"

dados_saida_produtos *p_saida_produtos = NULL;
int tam_saida_produtos = 0;

int inicializacao_saida_produtos(){
    
    int i;

    //le primeiro o tamanho do array
    tam_saida_produtos = tamanho_arquivo_saida_produtos();
    //caso tenha dados ler os dados e passar para o ponteiro do array
    if (tam_saida_produtos > 0) {
        //criando um array para colocar os dados
        p_saida_produtos = (dados_saida_produtos *) malloc(tam_saida_produtos * sizeof (dados_saida_produtos));
        for (i = 0; i < tam_saida_produtos; i++) {
            //p_saida_produtos[i] = ler_arquivo_saida_produtos(i);

            //para caso de erro ao abrir o arquivo para ler os array
            if (p_saida_produtos[i].cod == -1) {
                return -1;
            }
        }
    }        //para caso de erro ao abrir o arquivo para ler o tamanho do array
    else if (tam_saida_produtos == -2) {
        tam_saida_produtos = 0;
        return -1;
    } else {
        tam_saida_produtos = 0;
            }

    return 0;   
}

int cadastro_saida_produtos(dados_saida_produtos saida_produtos, char* opcao, int quantd[]) {

    tam_saida_produtos++; //somando mais um para o array
    int control_cod, i = 0, tam_quantd=0;
    dados_conta conta;

    //gerando um codigo para o checkin
    do {
        saida_produtos.cod = tam_saida_produtos + i;
        control_cod = verificacao_cod_saida_produtos(saida_produtos.cod);
        i++;
    }while (control_cod != -1);

    //condicao para o primeiro cadastro
    if (tam_saida_produtos == 1) {
        p_saida_produtos = (dados_saida_produtos *) malloc(tam_saida_produtos * sizeof (dados_saida_produtos));
    }        //para futuros cadastros
    else {
        p_saida_produtos = (dados_saida_produtos *) realloc(p_saida_produtos, tam_saida_produtos * sizeof (dados_saida_produtos));
    }
    
    //atribuindo o novo cadastro a ultima posicao do array
    p_saida_produtos[tam_saida_produtos - 1] = saida_produtos;
    
    //atribuido a conta ao novo cadastro
    char *token = strtok(opcao, ",");//abrindo o codigo dos produtos
    while(token!=NULL){
        conta.cod_produto = atoi(token);
        conta.quantidade = quantd[tam_quantd];    
        cadastro_conta_hospede(conta, tam_saida_produtos, tam_quantd);
        token=strtok(NULL,",");
        tam_quantd++;
                                        }

    salvar_saida_produtos();
    
    return p_saida_produtos[tam_saida_produtos - 1].cod;
};

void cadastro_conta_hospede(dados_conta conta, int i, int tam_quantd) {

    int control_cod;

    //condicao para o primeiro cadastro
    if (tam_saida_produtos == 1) {
        p_saida_produtos[i-1].p_conta = (dados_conta *) malloc(p_saida_produtos[i-1].tam_conta * sizeof (dados_conta));
    }        //para futuros cadastros
    else {
         p_saida_produtos[i-1].p_conta = (dados_conta *) realloc(p_saida_produtos[i-1].p_conta, p_saida_produtos[i-1].tam_conta * sizeof (dados_conta));
            }
    
    //atribuindo o novo cadastro a ultima posicao do array
    p_saida_produtos[i-1].p_conta[tam_quantd] = conta;

    return;
};

int verificacao_indice_saida_produtos(int cod){

    int i;

    for (i = 0; i < tam_saida_produtos; i++) {
        if (cod == p_saida_produtos[i].cod) {
            return i;
        }
    }
    return -1;

}

int exclusao_dados_saida_produtos(int posicao_saida_produtos) {

    int i;

    for (i = posicao_saida_produtos; i < tam_saida_produtos; i++) {
        //reposicionando os dados e excluindo o dado desejado
        p_saida_produtos[i] = p_saida_produtos[i + 1];
    }
    //redimencionando o array
    p_saida_produtos = (dados_saida_produtos *) realloc(p_saida_produtos, (tam_saida_produtos - 1) * sizeof (dados_saida_produtos));

    if (p_saida_produtos == NULL) {
        return 0;
    } else {
        //diminuindo o tamanho do array
        tam_saida_produtos--;
        return 1;
    }
}

void sair_saida_produtos() {
    tam_saida_produtos = 0;
    free(p_saida_produtos);
}

dados_saida_produtos consulta_saida_produtos(dados_saida_produtos saida_produtos, int i, int menu) {

    switch (menu) {
        case 1:
            if (p_saida_produtos[i].cod == saida_produtos.cod) {
                return p_saida_produtos[i];
            }
            break;
    }

    saida_produtos.cod = -1;
    return saida_produtos;
}


int tam_do_array_saida_produtos() {
    return tam_saida_produtos;
}

dados_saida_produtos saida_produtos_hospede(int cod_hospede){
int i, indice = 0;

    for (i = 0; i < tam_saida_produtos; i++) {
        if (p_saida_produtos[i].cod == cod_hospede){
            indice = i;
                                                            }
    }

    return p_saida_produtos[indice];
}

int verificacao_cod_saida_produtos(int cod){

    int i;
    
       for(i=0;i<tam_saida_produtos;i++){
           //para nao verificar o mesmo código
            if(tam_saida_produtos-1==i){
                continue;
                                    }
            else if(cod==p_saida_produtos[i].cod){
                    return i;
                                                }
                                        }
    return -1;                                    
}

int salvar_saida_produtos(){
    
    return salvar_arquivo_saida_produtos(p_saida_produtos, tam_saida_produtos);
}
