#ifndef CHECKIN_H
#define CHECKIN_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "Reserva.h"

    typedef struct {
        int cod;
        float valor;
        int cod_hospede;
        int cod_reserva;
        int hora[2];
        int opcao_pagamento; // 1. saÃ­da, 2. entrada
        int diarias;
    } dados_checkin;
    
/*
Funcao: para cadastrar os dados da categoria no array de struct
Recebe como parametro: struct do tipo dados_checkin e a hora de chegada do checkin
Devolve: um inteiro (o codigo da categoria)
*/
int cadastro_checkin(dados_checkin checkin, char* hora);

/*
Funcao: para pesquisar uma especifica struct de checkin
Recebe como parametro: struct do tipo dados_checkin, o tipo de dado a ser pesquisado: (1 - codigo; 2 - cod_hospede)
Devolve: uma struct do tipo dados_categoria (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_checkin consulta_checkin(dados_checkin checkin, int i, int menu);

/*
Funcao: calcula o preco da diaria da reserva
Recebe como parametro: struct da reserva
Devolve: o preco da reserva
*/
float consulta_pagamento_checkin(dados_reserva p_reserva);

/*
Funcao: para pegar o valor do tamanho do array da checkin
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da categoria)
*/
int tam_do_array_checkin();

/*
Funcao: verificar o indice do checkin 
Recebe como parametro: o codigo da checkin (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
*/
int verificacao_indice_checkin(int cod);

/*
Funcao: para excluir uma checkin
Recebe como parametro: a posicao da struct que deseja excluir da checkin (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
*/
int exclusao_dados_checkin(int posicao_checkin);

/*
Funcao: para redefinir o horario de string para vetor de inteiros
Recebe como parametro: struct do tipo dados_checkin e a hora do checkin
Devolve: struct do dados_checkin
*/
dados_checkin redefine_horario_checkin(dados_checkin checkin, char* hora);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo da checkin
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
*/
int verificacao_cod_checkin(int cod);

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
*/
int inicializacao_checkin();

/*
Funcao: para salvar a struct da check-in no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
*/
int salvar_checkin();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
*/
void sair_checkin();

void menu_checkin();

#ifdef __cplusplus
}
#endif

#endif /* CHECKIN_H */

