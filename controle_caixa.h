#ifndef CONTROLE_CAIXA_H
#define CONTROLE_CAIXA_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int cod;
        int data[3];
        int tipo; //1.Reserva, 2.Produtos, 0.Manual
        float valor;
        char fonte[300];
    } dados_lancamento;

    typedef struct {
        int cod;
        int data[3];
        float valor;
        char fonte[300];
    } dados_retirada;

    int inicializacao_caixa();
    int inicializacao_lancamento();
    int inicializacao_retirada();

    int cadastro_dados_lancamento(dados_lancamento lancamento, char *data);
    int cadastro_dados_retirada(dados_retirada retirada, char *data);

    void sair_caixa();

    dados_lancamento consulta_dados_lancamento(dados_lancamento lancamento, int tipo, int i);
    dados_retirada consulta_dados_retirada(dados_retirada retirada,int tipo, int i);
    float consulta_dados_caixa();

    int verificacao_status_dados_lancamento(int cod);
    int verificacao_status_dados_retirada(int cod);

    dados_lancamento redefine_data_lancamento(dados_lancamento lancamento, char* data);
    dados_retirada redefine_data_retirada(dados_retirada retirada, char* data);

    int tam_do_array_caixa();
    int tam_do_array_lancamento();
    int tam_do_array_retirada();

    int verificacao_indice_caixa();
    int verificacao_indice_lancamento(int cod);
    int verificacao_indice_retirada(int cod);

    int exclusao_dados_caixa();
    int exclusao_dados_lancamento(int posicao_lancamento);
    int exclusao_dados_retirada(int posicao_retirada);

    int verificacao_cod_lancamento(int cod);
    int verificacao_cod_retirada(int cod);

    int salvar_dados_caixa();
    
    //recebe: o valor que deve ser lancado no caixa, o tipo de lancamento (1.Reservas, 2.Produtos), codigo do produto ou reserva
    void menu_controle_caixa(float valor, int tipo, int cod);

#ifdef __cplusplus
}
#endif

#endif /* CONTROLE_CAIXA_H */

