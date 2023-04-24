/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 22 de janeiro de 2021, 15:23
 */

#ifndef PRODUTO_H
#define PRODUTO_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

typedef struct{
        int cod, estoque, estoque_min;
        float preco_custo, preco_venda;
        char descricao[400], fornecedor[100];      
                    }dados_produto;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
*/
int inicializacao_produto();

/*
Funcao: verificar o indice da produto 
Recebe como parametro: o codigo da produto (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
*/
int verificacao_indice_produto(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo da produto
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
*/
int verificacao_cod_produto(int cod);

/*
Funcao: para excluir uma produto
Recebe como parametro: a posicao da struct que deseja excluir da produto(um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
*/
int exclusao_dados_produto(int posicao_produto);

/*
Funcao: para alterar os dados da struct de produto
Recebe como parametro: struct do tipo dados_produto, o tipo de dado a ser mudado:
(1 - codigo; 2 - descricao; 3 - estoque; 4 - estoque minimo; 5 - preco de custo; 6 - preco de venda); a posicao da struct no array
Devolve: nada
*/
void alteracao_dados_produto(dados_produto produto, int tipo, int indice);

/*
Funcao: para cadastrar os dados do produto no array de struct
Recebe como parametro: struct do tipo dados_produto
Devolve: um inteiro (o codigo do produto)
*/
int cadastro_produto(dados_produto produto);

/*
Funcao: para pegar o valor do tamanho do array do produto
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da produto)
*/
int tam_do_array_produto();

/*
Funcao: para pesquisar uma especifica struct de produto
Recebe como parametro: struct do tipo dados_produto, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - descricao; 3 - estoque; 4 - estoque minimo; 5 - preco de custo; 6 - preco de venda); o indice para pesquisa
Devolve: uma struct do tipo dados_produto (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_produto consulta_produto(dados_produto produto, int tipo, int i);

/*
Funcao: para salvar a struct da produto no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
*/
int salvar_produto();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
*/
void sair_produto();

/*
Funcao: compara o estoque de um produto com outro
Recebe como parametro: struct de dados_produto, indice do produto a ser comparador
Devolve: um inteiro (1 - caso o estoque seja maior ou igual, -1 - caso o estoque seja menor)
*/
int estoque_produto(dados_produto produto, int i);

void menu_produto();

#endif
