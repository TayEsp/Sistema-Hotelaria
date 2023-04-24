

#ifndef RESERVA_H
#define RESERVA_H
#include "acomodacao.h"
#include "categoria.h"

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


typedef struct{
    int cod;
    int cod_cliente;
    int dia_chegada[3];
    int dia_saida[3];
    int acomodacao;
                }dados_reserva;

dados_reserva redefine_data(dados_reserva reserva, char* data, int tipo);

dados_acomodacao acomodacao_reserva(dados_acomodacao acomodacao, dados_categoria categoria, char* data_e, char* data_s, int i, char* sub_menu);

int verificacao_reserva(dados_acomodacao acomodacao, dados_reserva reserva, char* data_e, char* data_s);

int verificacao_cod_reserva(int cod);

int cadastro_reserva(dados_reserva reserva, char* data_i, char* data_s);

void sair_reserva();

/*
Funcao: para pesquisar uma especifica struct de reserva
Recebe como parametro: struct do tipo dados_reserva, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - codigo cliente; 3 - data; 4 - acomodacao); o indice para pesquisa
Devolve: uma struct do tipo dados_reserva (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_reserva consulta_reserva(dados_reserva reserva, char* data_entrada, char* data_saida, int i, int menu);

void menu_reserva();

int tam_do_array_reserva();

int verificacao_indice_reserva(int cod);

int exclusao_dados_reserva(int posicao_reserva);

void menu_reserva();

int salvar_reserva();

int inicializacao_reserva();

#endif /* RESERVA_H */