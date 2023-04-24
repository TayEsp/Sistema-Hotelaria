#ifndef hospede_H
#define hospede_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

typedef struct {
    int cod;
    char nome[50];
    char endereco_completo[50];
    char cpf[15];
    char telefone_hospede[15];
    char email_hospede[20];
    char sexo[5];
    char estado_civil[20];    
    char data_nascimento[20];
} dados_hospede;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
 */
int inicializacao_hospede();

/*
Funcao: verificar o indice de hospede 
Recebe como parametro: o codigo da hospede (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
 */
int verificacao_indice_hospede(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo de hospede
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
 */
int verificacao_cod_hospede(int cod);

/*
Funcao: para excluir um hospede
Recebe como parametro: a posicao da struct que deseja excluir de hospede (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
 */
int exclusao_dados_hospede(int posicao_hospede);

/*
Funcao: para alterar os dados da struct de hospede
Recebe como parametro: struct do tipo dados_hospede, o tipo de dado a ser mudado:
(1 - codigo; 2 - nome; 3 - usuario; 4 - senha; 5 - categoria); a posicao da struct no array
Devolve: nada
 */
void alteracao_dados_hospede(dados_hospede hospede, int tipo, int indice);

/*
Funcao: para cadastrar os dados da hospede no array de struct
Recebe como parametro: struct do tipo dados_hospede
Devolve: um inteiro (o codigo da hospede)
 */
int cadastro_hospede(dados_hospede hospede);

/*
Funcao: para pegar o valor do tamanho do array de hospede
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da hospede)
 */
int tam_do_array_hospede();

/*
Funcao: para pesquisar uma especifica struct de hospede
Recebe como parametro: struct do tipo dados_hospede, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - nome; 3 - usuario; 4 - categoria; 5 - indice); o indice para pesquisa
Devolve: uma struct do tipo dados_hospede (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
 */
dados_hospede consulta_hospede(dados_hospede hospede, int tipo, int i);

/*
Funcao: para salvar a struct de hospede no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
 */
int salvar_hospede();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
 */
void sair_hospede();

void menu_hospede();

#endif