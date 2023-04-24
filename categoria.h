/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 22 de janeiro de 2021, 17:10
 */

#ifndef CATEGORIA_H
#define CATEGORIA_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif



typedef struct{
    int cod, hospede[2];//Hospedes[Adultos, Criancas]
    char descricao[200], nome[20];
    float valor_diaria;
                }dados_categoria;

/*
Funcao: verificar o indice da categoria 
Recebe como parametro: o codigo da categoria (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
*/
int verificacao_indice_categoria(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo da categoria
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
*/
int verificacao_cod_categoria(int cod);

/*
Funcao: para excluir uma categoria
Recebe como parametro: a posicao da struct que deseja excluir da categoria (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
*/
int exclusao_dados_categoria(int codigo);

/*
Funcao: para cadastrar os dados da categoria no array de struct
Recebe como parametro: struct do tipo dados_categoria
Devolve: um inteiro (o codigo da categoria)
*/
int cadastro_categoria(dados_categoria categoria);

/*
Funcao: para alterar os dados da struct de categoria
Recebe como parametro: struct do tipo dados_categoria, o tipo de dado a ser mudado:
(1 - nome; 2 - codigo; 3 - descricao; 4 - valor diaria; 5 - hospedes); a posicao da struct no array
Devolve: nada
*/
void alteracao_dados_categoria(dados_categoria categoria, int tipo, int indice);

/*
Funcao: para pesquisar uma especifica struct de categoria
Recebe como parametro: struct do tipo dados_categoria, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - nome; 3 - descricao; 4 - valor diaria; 5 - hospedes);o indice para pesquisa; o valor da diaria 
(valor[0] - valor minimo; valor[1] - valor maximo); o tipo de pesquisa para o valor da diaria 
(1 - valor minimo ou igual; 2 - valor maximo ou igual; 3 - ambos)
Devolve: uma struct do tipo dados_categoria (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_categoria consulta_categoria(dados_categoria categoria, int tipo, int i, float valor[], int sub_menu);

/*
Funcao: para pegar o valor do tamanho do array da categoria
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da categoria)
*/
int tam_do_array_categoria();

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
*/
int inicializacao_categoria();

/*
Funcao: para salvar a struct da categoria no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
*/
int salvar_categoria();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
*/
void sair_categoria();

void menu_categoria();

#endif

