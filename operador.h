#ifndef operador_H
#define operador_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

typedef struct {
    int cod;
    char nome[50];
    char usuario[20];
    char senha[15];
    char categoria[12];
} dados_operador;

/*
Funcao: para recuperar os dados do arquivo e passar para o sistema
Recebe como parametro: nada
Devolve: um inteiro (1 - caso tenha inicializado com sucesso; -1 - caso tenha dado erro ao abrir o arquivo) 
 */
int inicializacao_operador();

/*
Funcao: verificar o indice de operador 
Recebe como parametro: o codigo da operador (inteiro)
Devolve: a posicao da struct no array (um inteiro) 
 */
int verificacao_indice_operador(int cod);

/*
Funcao: verifica a existencia de um codigo igual
Recebe como parametro: o codigo de operador
Devolve: um inteiro (-1 - caso nao tenha um codigo igual; diferente de -1 - caso tenha um codigo igual) 
 */
int verificacao_cod_operador(int cod);

/*
Funcao: para excluir um operador
Recebe como parametro: a posicao da struct que deseja excluir de operador (um inteiro)
Devolve: um inteiro (0 - caso tenha dado erro ao realocar a memoria; 1 - caso tenha excluido com sucesso)
 */
int exclusao_dados_operador(int posicao_operador);

/*
Funcao: para alterar os dados da struct de operador
Recebe como parametro: struct do tipo dados_operador, o tipo de dado a ser mudado:
(1 - codigo; 2 - nome; 3 - usuario; 4 - senha; 5 - categoria); a posicao da struct no array
Devolve: nada
 */
void alteracao_dados_operador(dados_operador operador, int tipo, int indice);

/*
Funcao: para cadastrar os dados da operador no array de struct
Recebe como parametro: struct do tipo dados_operador
Devolve: um inteiro (o codigo da operador)
 */
int cadastro_operador(dados_operador operador);

/*
Funcao: para pegar o valor do tamanho do array de operador
Recebe como parametro: nada
Devolve: um inteiro (o tamanho da operador)
 */
int tam_do_array_operador();

/*
Funcao: para pesquisar uma especifica struct de operador
Recebe como parametro: struct do tipo dados_operador, o tipo de dado a ser pesquisado: 
(1 - codigo; 2 - nome; 3 - usuario; 4 - categoria; 5 - indice); o indice para pesquisa
Devolve: uma struct do tipo dados_operador (com o codigo positivo caso tenha achado; codigo igual a -1
caso nao tenha achado)
 */
dados_operador consulta_operador(dados_operador operador, int tipo, int i);

/*
Funcao: para salvar a struct de operador no arquivo
Recebe como parametro: nada
Devolve: um inteiro (0 - caso tenha dado erro; 1 - caso tenha salvo com sucesso)
 */
int salvar_operador();

/*
Funcao: para liberar a memoria alocada
Recebe como parametro: nada
Devolve: nada
 */
void sair_operador();

void menu_admin();
void menu_gerente();
void menu_recepcao();
void menu_operador();

dados_operador login_operador();

#endif