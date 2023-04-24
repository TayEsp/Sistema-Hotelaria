/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 22 de janeiro de 2021, 15:23
 */

#ifndef ACOMODACAO_H
#define ACOMODACAO_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif


typedef struct{
        int cod, categoria, num_quarto;
        char descricao[200], facilidades[200];      
                    }dados_acomodacao;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
*/
int inicializacao_acomodacao();

/*
Funcao: verificar o indice da acomodacao 
Recebe como parametro: o codigo da acomodacao (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
*/
int verificacao_indice_acomodacao(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo da acomodacao
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
*/
int verificacao_cod_acomodacao(int cod);

/*
Funcao: para excluir uma acomodacao
Recebe como parametro: a posicao da struct que deseja excluir da acomodacao (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
*/
int exclusao_dados_acomodacao(int posicao_acomodacao);

/*
Funcao: para alterar os dados da struct de categoria
Recebe como parametro: struct do tipo dados_categoria, o tipo de dado a ser mudado:
(1 - codigo; 2 - descricao; 3 - facilidade; 4 - categoria; 5 - numero quarto); a posicao da struct no array
Devolve: nada
*/
void alteracao_dados_acomodacao(dados_acomodacao acomodacao, int tipo, int indice);

/*
Funcao: para cadastrar os dados da acomodacao no array de struct
Recebe como parametro: struct do tipo dados_acomodacao
Devolve: um inteiro (o codigo da acomodacao)
*/
int cadastro_acomodacao(dados_acomodacao acomodacao);

/*
Funcao: para pegar o valor do tamanho do array da acomodacao
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da acomodacao)
*/
int tam_do_array_acomodacao();

/*
Funcao: para pesquisar uma especifica struct de acomodacao
Recebe como parametro: struct do tipo dados_acomodacao, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - descricao; 3 - facilidade; 4 - categoria; 5 - numero quarto; 6 - indice); o indice para pesquisa
Devolve: uma struct do tipo dados_acomodacao (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_acomodacao consulta_acomodacao(dados_acomodacao acomodacao, int tipo, int i);

/*
Funcao: para salvar a struct da acomodacao no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
*/
int salvar_acomodacao();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
*/
void sair_acomodacao();

void menu_acomodacao();

#endif