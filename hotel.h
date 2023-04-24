#ifndef HOTEL_H
#define HOTEL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

typedef struct {
    int cod;
    char nome_fantasia[50];
    char razao_social[50];
    char inscricao_estadual[50];
    char cnpj[15];
    char endereco_completo[50];
    char telefone_hotel[15];
    char email_hotel[20];
    char nome_responsavel[50];
    char telefone_responsavel[20];    
    char check_in[20];
    char check_out[20];
    char margem_lucro[20];
} dados_hotel;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
 */
int inicializacao_hotel();

/*
Funcao: verificar o indice de hotel 
Recebe como parametro: o codigo da hotel (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
 */
int verificacao_indice_hotel(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo de hotel
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
 */
int verificacao_cod_hotel(int cod);

/*
Funcao: para excluir um hotel
Recebe como parametro: a posicao da struct que deseja excluir de hotel (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
 */
int exclusao_dados_hotel(int posicao_hotel);

/*
Funcao: para alterar os dados da struct de hotel
Recebe como parametro: struct do tipo dados_hotel, o tipo de dado a ser mudado:
(1 - codigo; 2 - nome; 3 - usuario; 4 - senha; 5 - categoria); a posicao da struct no array
Devolve: nada
 */
void alteracao_dados_hotel(dados_hotel hotel, int tipo, int indice);

/*
Funcao: para cadastrar os dados da hotel no array de struct
Recebe como parametro: struct do tipo dados_hotel
Devolve: um inteiro (o codigo da hotel)
 */
int cadastro_hotel(dados_hotel hotel);

/*
Funcao: para pegar o valor do tamanho do array de hotel
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da hotel)
 */
int tam_do_array_hotel();

/*
Funcao: para pesquisar uma especifica struct de hotel
Recebe como parametro: struct do tipo dados_hotel, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - nome; 3 - usuario; 4 - categoria; 5 - indice); o indice para pesquisa
Devolve: uma struct do tipo dados_hotel (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
 */
dados_hotel consulta_hotel(dados_hotel hotel, int tipo, int i);

/*
Funcao: para salvar a struct de hotel no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
 */
int salvar_hotel();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
 */

void sair_hotel();

void menu_hotel();

#endif