#ifndef SAIDA_PRODUTOS_H
#define SAIDA_PRODUTOS_H
#include "checkout.h"
#include "produto.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

    typedef struct{
        int cod_produto;
        int quantidade; 
    } dados_conta;    
   
    typedef struct {
        int cod;
        int status; // 1.nao pago, 2. Ja foi pago
        char CPF[20];
        int forma_pagamento; // 1. a vista, 2. anotar 
        float total;
        int tam_conta;
        dados_conta *p_conta;       
    } dados_saida_produtos;
    
int cadastro_saida_produtos(dados_saida_produtos saida_produtos, char* opcao, int quantd[]);
void sair_saida_produtos();
void cadastro_conta_hospede(dados_conta conta, int i, int tam_quantd);
dados_saida_produtos consulta_saida_produtos(dados_saida_produtos saida_produtos, int i, int menu);
int tam_do_array_saida_produtos();
int verificacao_indice_saida_produtos(int cod);
int exclusao_dados_saida_produtos(int posicao_saida_produtos);
int verificacao_cod_saida_produtos(int cod);
void nota_fiscal_saida_produtos(dados_saida_produtos p_saida_produtos);
dados_saida_produtos saida_produtos_hospede(int cod_hospede);
void menu_saida_produtos();
int inicializacao_saida_produtos();
int salvar_saida_produtos();

#endif /* SAIDA_PRODUTOS_H */