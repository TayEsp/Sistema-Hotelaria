#ifndef CHECKOUT_H
#define CHECKOUT_H
#include "Reserva.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int cod;
        int hora[2];
        float valor;
        int cod_hospede;
        int cod_reserva;
        int diarias;
        int opcao_pagamento; // 1. saiÂ­da, 2. entrada
    } dados_checkout;

    int cadastro_checkout(dados_checkout checkout, char* hora);
    void sair_checkout();
    int salvar_checkout();
    dados_checkout consulta_checkout(dados_checkout checkout, int i, int menu);
    dados_checkout checkout_por_reserva(int cod_reserva);
    float consulta_pagamento_checkout(dados_checkout p_checkout, dados_reserva p_reserva);
    int tam_do_array_checkout();
    int verificacao_indice_checkout(int cod);
    int exclusao_dados_checkout(int posicao_checkout);
    dados_checkout redefine_horario_checkout(dados_checkout checkout, char* hora);
    int verificacao_cod_checkout(int cod);
    int inicializacao_checkout();
    void menu_checkout();

#ifdef __cplusplus
}
#endif

#endif /* CHECKOUT_H */

