/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 09 de janeiro de 2021, 17:22
 */

#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "acomodacao.h"
#include "categoria.h"
#include "produto.h"
#include "Reserva.h"
#include "fornecedor.h"
#include "operador.h"
#include "hospede.h"
#include "hotel.h"
#include "checkin.h"
#include "checkout.h"
#include "saida_produtos.h"
#include "controle_caixa.h"

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

/*Funcao de tempo*/
struct tm *set_time();

/*
Funcao: para controle do tipo de dados a ser usado 
Recebe como parametro: um inteiro (O tipo de dado: 1 - Texto; 2 - Binario)
Devolve: um inteiro (0 - caso tenha escolhido uma opcao invalida; 1 - caso tenha mudado com sucesso) 
*/
int tipo_arquivo(int tipo);

//CATEGORIA
/*
Funcao: para ler o arquivo da categoria
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da categoria
*/
dados_categoria ler_arquivo_categoria(int i);

/*
Funcao: para ler no arquivo o tamanho do array da categoria 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_categoria();

/*
Funcao: para salvar o array de struct da categoria no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_categoria(dados_categoria *p_categoria, int tam_categoria);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_categoria_binario(dados_categoria *p_categoria, int tam_categoria);
int salvar_arquivo_categoria_texto(dados_categoria *p_categoria, int tam_categoria);
int tamanho_arquivo_categoria_binario();
int tamanho_arquivo_categoria_texto();
dados_categoria ler_arquivo_categoria_binario(int i);
dados_categoria ler_arquivo_categoria_texto(int i);

//ACOMODACAO
/*
Funcao: para salvar o array de struct da acomodacao no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_acomodacao(dados_acomodacao *p_acomodacao, int tam_acomodacao);

/*
Funcao: para ler o arquivo da acomodacao
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da categoria
*/
dados_acomodacao ler_arquivo_acomodacao(int i);

/*
Funcao: para ler no arquivo o tamanho do array da acomodacao
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_acomodacao();

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_acomodacao_binario(dados_acomodacao *p_acomodacao, int tam_acomodacao);
int salvar_arquivo_acomodacao_texto(dados_acomodacao *p_acomodacao, int tam_acomodacao);
int tamanho_arquivo_acomodacao_binario();
int tamanho_arquivo_acomodacao_texto();
dados_acomodacao ler_arquivo_acomodacao_binario(int i);
dados_acomodacao ler_arquivo_acomodacao_texto(int i);

//RESERVA
/*
Funcao: para salvar o array de struct da reserva no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_reserva(dados_reserva *p_reseva, int tam_reserva);

/*
Funcao: para ler o arquivo da reserva
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da reserva
*/
dados_reserva ler_arquivo_reserva(int i);

/*
Funcao: para ler no arquivo o tamanho do array da reserva
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_reserva();


/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_reserva_binario(dados_reserva *p_reserva, int tam_reserva);
int salvar_arquivo_reserva_texto(dados_reserva *p_reserva, int tam_reserva);
int tamanho_arquivo_reserva_binario();
int tamanho_arquivo_reserva_texto();
dados_reserva ler_arquivo_reserva_binario(int i);
dados_reserva ler_arquivo_reserva_texto(int i);

//PRODUTO
/*
Funcao: para salvar o array de struct da produto no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_produto(dados_produto *p_produto, int tam_produto);

/*
Funcao: para ler o arquivo da produto
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da produto
*/
dados_produto ler_arquivo_produto(int i);

/*
Funcao: para ler no arquivo o tamanho do array da produto
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_produto();

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_produto_binario(dados_produto *p_produto, int tam_produto);
int salvar_arquivo_produto_texto(dados_produto *p_produto, int tam_produto);
int tamanho_arquivo_produto_binario();
int tamanho_arquivo_produto_texto();
dados_produto ler_arquivo_produto_binario(int i);
dados_produto ler_arquivo_produto_texto(int i);

//FORNECEDOR
/*
Funcao: para salvar o array de struct do fornecedor no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_fornecedor(dados_fornecedor *p_fornecedor, int tam_fornecedor);

/*
Funcao: para ler o arquivo do fornecedor
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados do fornecedor
*/
dados_fornecedor ler_arquivo_fornecedor(int i);

/*
Funcao: para ler no arquivo o tamanho do array do fornecedor
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_fornecedor();

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_fornecedor_binario(dados_fornecedor *p_fornecedor, int tam_fornecedor);
int salvar_arquivo_fornecedor_texto(dados_fornecedor *p_fornecedor, int tam_fornecedor);
int tamanho_arquivo_fornecedor_binario();
int tamanho_arquivo_fornecedor_texto();
dados_fornecedor ler_arquivo_fornecedor_binario(int i);
dados_fornecedor ler_arquivo_fornecedor_texto(int i);

//OPERADOR
/*
Funcao: para salvar o array de struct do operador no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_operador(dados_operador *p_operador, int tam_operador);

/*
Funcao: para ler o arquivo do operador
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da produto
*/
dados_operador ler_arquivo_operador(int i);

/*
Funcao: para ler no arquivo o tamanho do array do operador
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_operador();

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_operador_binario(dados_operador *p_operador, int tam_operador);
int salvar_arquivo_operador_texto(dados_operador *p_operador, int tam_operador);
int tamanho_arquivo_operador_binario();
int tamanho_arquivo_operador_texto();
dados_operador ler_arquivo_operador_binario(int i);
dados_operador ler_arquivo_operador_texto(int i);

//HOSPEDE
/*
Funcao: para ler o arquivo do hospede
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hospede
*/
dados_hospede ler_arquivo_hospede(int i);

/*
Funcao: para ler no arquivo o tamanho do array da hospede 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_hospede();

/*
Funcao: para salvar o array de struct da hospede no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_hospede(dados_hospede *p_hospede, int tam_hospede);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_hospede_binario(dados_hospede *p_hospede, int tam_hospede);
int salvar_arquivo_hospede_texto(dados_hospede *p_hospede, int tam_hospede);
int tamanho_arquivo_hospede_binario();
int tamanho_arquivo_hospede_texto();
dados_hospede ler_arquivo_hospede_binario(int i);
dados_hospede ler_arquivo_hospede_texto(int i);

//HOTEL
/*
Funcao: para ler o arquivo do hotel
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
dados_hotel ler_arquivo_hotel(int i);

/*
Funcao: para ler no arquivo o tamanho do array da hotel 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_hotel();

/*
Funcao: para salvar o array de struct da hotel no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_hotel(dados_hotel *p_hotel, int tam_hotel);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_hotel_binario(dados_hotel *p_hotel, int tam_hotel);
int salvar_arquivo_hotel_texto(dados_hotel *p_hotel, int tam_hotel);
int tamanho_arquivo_hotel_binario();
int tamanho_arquivo_hotel_texto();
dados_hotel ler_arquivo_hotel_binario(int i);
dados_hotel ler_arquivo_hotel_texto(int i);

//CHECK-IN
/*
Funcao: para ler o arquivo do check-in
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
dados_checkin ler_arquivo_checkin(int i);

/*
Funcao: para ler no arquivo o tamanho do array da checkin 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_checkin();

/*
Funcao: para salvar o array de struct da checkin no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_checkin(dados_checkin *p_checkin, int tam_checkin);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_checkin_binario(dados_checkin *p_checkin, int tam_checkin);
int salvar_arquivo_checkin_texto(dados_checkin *p_checkin, int tam_checkin);
int tamanho_arquivo_checkin_binario();
int tamanho_arquivo_checkin_texto();
dados_checkin ler_arquivo_checkin_binario(int i);
dados_checkin ler_arquivo_checkin_texto(int i);

//CHECK-OUT
/*
Funcao: para ler o arquivo do check-in
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
dados_checkout ler_arquivo_checkout(int i);

/*
Funcao: para ler no arquivo o tamanho do array da checkin 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_checkout();

/*
Funcao: para salvar o array de struct da checkin no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_checkout(dados_checkout *p_checkout, int tam_checkout);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_checkout_binario(dados_checkout *p_checkout, int tam_checkout);
int salvar_arquivo_checkout_texto(dados_checkout *p_checkout, int tam_checkout);
int tamanho_arquivo_checkout_binario();
int tamanho_arquivo_checkout_texto();
dados_checkout ler_arquivo_checkout_binario(int i);
dados_checkout ler_arquivo_checkout_texto(int i);

//SAIDA_PRODUTOS
/*
Funcao: para ler o arquivo do saida produtos
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da saida produtos
*/
dados_saida_produtos ler_arquivo_saida_produtos(int i);

/*
Funcao: para ler no arquivo o tamanho do array da saida_produtos 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_saida_produtos();

/*
Funcao: para salvar o array de struct da saida produtos no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_saida_produtos(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_saida_produtos_binario(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos);
int salvar_arquivo_saida_produtos_texto(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos);
int tamanho_arquivo_saida_produtos_binario();
int tamanho_arquivo_saida_produtos_texto();
dados_saida_produtos ler_arquivo_saida_produtos_binario(int i);
dados_saida_produtos ler_arquivo_saida_produtos_texto(int i);

//CAIXA
/*
Funcao: para ler o arquivo do check-in
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
float ler_arquivo_caixa();

/*
Funcao: para salvar o array de struct da checkin no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_caixa(float valor_caixa);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_caixa_binario(float valor_caixa);
int salvar_arquivo_caixa_texto(float valor_caixa);
float ler_arquivo_caixa_binario();
float ler_arquivo_caixa_texto();

//CAIXA LANCAMENTO
/*
Funcao: para ler o arquivo do lancamento
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
dados_lancamento ler_arquivo_lancamento(int i);

/*
Funcao: para ler no arquivo o tamanho do array da checkin 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_lancamento();

/*
Funcao: para salvar o array de struct da checkin no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_lancamento(dados_lancamento *p_lancamento, int tam_lancamento);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_lancamento_binario(dados_lancamento *p_lancamento, int tam_lancamento);
int salvar_arquivo_lancamento_texto(dados_lancamento *p_lancamento, int tam_lancamento);
int tamanho_arquivo_lancamento_binario();
int tamanho_arquivo_lancamento_texto();
dados_lancamento ler_arquivo_lancamento_binario(int i);
dados_lancamento ler_arquivo_lancamento_texto(int i);

//CAIXA RETIRADA
/*
Funcao: para ler o arquivo do retirada
Recebe como parametro: um numero inteiro (qual posicao da lista deseja acessar)
Devolve: uma struct com os dados da hotel
*/
dados_retirada ler_arquivo_retirada(int i);

/*
Funcao: para ler no arquivo o tamanho do array da checkin 
Recebe como parametro: nada
Devolve: um numero inteiro (o tamanho do array)
*/
int tamanho_arquivo_retirada();

/*
Funcao: para salvar o array de struct da retirada no arquivo 
Recebe como parametro: o ponteiro do array da struct e um inteiro (tam do array)
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso) 
*/
int salvar_arquivo_retirada(dados_retirada *p_retirada, int tam_retirada);

/*As funcoes abaixo funcionam da mesma forma que suas chamadas gerais*/
int salvar_arquivo_retirada_binario(dados_retirada *p_retirada, int tam_retirada);
int salvar_arquivo_retirada_texto(dados_retirada *p_retirada, int tam_retirada);
int tamanho_arquivo_retirada_binario();
int tamanho_arquivo_retirada_texto();
dados_retirada ler_arquivo_retirada_binario(int i);
dados_retirada ler_arquivo_retirada_texto(int i);

#endif /* ARQUIVO_H */