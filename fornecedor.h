/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 22 de janeiro de 2021, 15:23
 */

#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

typedef struct{
        int cod;
        char nome_fantasia[100];
        char razao_social[100];
        char incricao_est[12];
        char cnpj[17];
        char endereco[100];
        char telefone[17];
        char email[50];
                    }dados_fornecedor;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
*/
int inicializacao_fornecedor();

/*
Funcao: verificar o indice da fornecedor
Recebe como parametro: o codigo da fornecedor (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
*/
int verificacao_indice_fornecedor(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo da fornecedor
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
*/
int verificacao_cod_fornecedor(int cod);

/*
Funcao: para excluir um fornecedor
Recebe como parametro: a posicao da struct que deseja excluir do fornecedor(um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
*/
int exclusao_dados_fornecedor(int posicao_fornecedor);

/*
Funcao: para alterar os dados da struct de fornecedor
Recebe como parametro: struct do tipo dados_fornecedor, o tipo de dado a ser mudado:
(1 - codigo; 2 - nome fantasia; 3 - razao social; 4 - incricao social; 5 - CNPJ; 6 - endereco;
7 - telefone; 8 - email); a posicao da struct no array
Devolve: nada
*/
void alteracao_dados_fornecedor(dados_fornecedor fornecedor, int tipo, int indice);

/*
Funcao: para cadastrar os dados da fornecedor no array de struct
Recebe como parametro: struct do tipo dados_fornecedor
Devolve: um inteiro (o codigo da fornecedor)
*/
int cadastro_fornecedor(dados_fornecedor fornecedor);

/*
Funcao: para pegar o valor do tamanho do array do fornecedor
Recebe como parametro: nada
Devolve: um inteiro (o tamanho do fornecedor)
*/
int tam_do_array_fornecedor();

/*
Funcao: para pesquisar uma especifica struct de fornecedor
Recebe como parametro: struct do tipo dados_fornecedor, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - nome fantasia; 3 - razao social; 4 - incricao social; 5 - CNPJ; 6 - endereco;
7 - telefone; 8 - email); o indice para pesquisa
Devolve: uma struct do tipo dados_fornecedor (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
*/
dados_fornecedor consulta_fornecedor(dados_fornecedor fornecedor, int tipo, int i);

/*
Funcao: para salvar a struct do fornecedor no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
*/
int salvar_fornecedor();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
*/
void sair_fornecedor();

void menu_fornecedor();

#endif

