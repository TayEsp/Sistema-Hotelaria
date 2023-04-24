#include "controle_caixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_lancamento *p_lancamento = NULL;
dados_retirada *p_retirada = NULL;
float montante_caixa = 0;
int tam_lancamento = 0;
int tam_retirada = 0;

int inicializacao_caixa() {

    int i;

    //lendo o total do caixa
    montante_caixa = ler_arquivo_caixa();
    
    // Lancamento 
    tam_lancamento = tamanho_arquivo_lancamento();
    //caso tenha dados ler os dados e passar para o ponteiro do array
    if (tam_lancamento > 0) {
        //criando um array para colocar os dados
        p_lancamento = (dados_lancamento *) malloc(tam_lancamento * sizeof (dados_lancamento));
        for (i = 0; i < tam_lancamento; i++) {
            p_lancamento[i] = ler_arquivo_lancamento(i);

            //para caso de erro ao abrir o arquivo para ler os array
            if (p_lancamento[i].cod == -1) {
                return -1;
            }
        }
    }//para caso de erro ao abrir o arquivo para ler o tamanho do array
    else if (tam_lancamento == -2) {
        tam_lancamento = 0;
        return -1;
    } else {
        tam_lancamento = 0;
    }

    // Retirada


    //le primeiro o tamanho do array
    tam_retirada = tamanho_arquivo_retirada();
    //caso tenha dados ler os dados e passar para o ponteiro do array
    if (tam_retirada > 0) {
        //criando um array para colocar os dados
        p_retirada = (dados_retirada *) malloc(tam_retirada * sizeof (dados_retirada));
        for (i = 0; i < tam_retirada; i++) {
            p_retirada[i] = ler_arquivo_retirada(i);

            //para caso de erro ao abrir o arquivo para ler os array
            if (p_retirada[i].cod == -1) {
                return -1;
            }
        }
    }//para caso de erro ao abrir o arquivo para ler o tamanho do array
    else if (tam_retirada == -2) {
        tam_retirada = 0;
        return -1;
    } else {
        tam_retirada = 0;
    }

    return 0;
}

int cadastro_dados_lancamento(dados_lancamento lancamento, char *data) {

    tam_lancamento++; //somando mais um para o array
    int control_cod, i = 0;

    //gerando um codigo para o checkin
    do {
        lancamento.cod = tam_lancamento + i;
        control_cod = verificacao_cod_lancamento(lancamento.cod);
        i++;
    } while (control_cod != -1);

    //condicao para o primeiro cadastro
    if (tam_lancamento == 1) {
        p_lancamento = (dados_lancamento *) malloc(tam_lancamento * sizeof (dados_lancamento));
    }//para futuros cadastros
    else {
        p_lancamento = (dados_lancamento *) realloc(p_lancamento, tam_lancamento * sizeof (dados_lancamento));
    }

    //definindo a data no formato de vetor
    lancamento = redefine_data_lancamento(lancamento, data);
    
    //somando o lancamento ao total no caixa
    montante_caixa = montante_caixa + lancamento.valor;
    
    //atribuindo o novo cadastro a ultima posicao do array
    p_lancamento[tam_lancamento - 1] = lancamento;

    return p_lancamento[tam_lancamento - 1].cod;

}

int cadastro_dados_retirada(dados_retirada retirada, char *data) {

    tam_retirada++; //somando mais um para o array
    int control_cod, i = 0;

    //gerando um codigo para o checkin
    do {
        retirada.cod = tam_retirada + i;
        control_cod = verificacao_cod_retirada(retirada.cod);
        i++;
    } while (control_cod != -1);

    //condicao para o primeiro cadastro
    if (tam_retirada == 1) {
        p_retirada = (dados_retirada *) malloc(tam_retirada * sizeof (dados_retirada));
    }//para futuros cadastros
    else {
        p_retirada = (dados_retirada *) realloc(p_retirada, tam_retirada * sizeof (dados_retirada));
    }

    //subtraindo o retirada ao total no caixa
    montante_caixa = montante_caixa - retirada.valor;
    
    //definindo a data no formato de vetor
    retirada = redefine_data_retirada(retirada, data);

    //atribuindo o novo cadastro a ultima posicao do array
    p_retirada[tam_retirada - 1] = retirada;

    return p_retirada[tam_retirada - 1].cod;

}

dados_lancamento redefine_data_lancamento(dados_lancamento lancamento, char* data){
    
    int i=0;
    char *token= strtok(data, "/");
    

        while(token!=NULL){
            lancamento.data[i]=atoi(token);
            token=strtok(NULL,"/");
            i++;
                            }

    return lancamento;
};

dados_retirada redefine_data_retirada(dados_retirada retirada, char* data){
    
    int i=0;
    char *token= strtok(data, "/");
    

        while(token!=NULL){
            retirada.data[i]=atoi(token);
            token=strtok(NULL,"/");
            i++;
                            }

    return retirada;
};

void sair_caixa() {
    tam_retirada = 0;
    tam_lancamento = 0;
    montante_caixa = 0;
    free(p_retirada);
    free(p_lancamento);
}

float consulta_dados_caixa() {
    
    return montante_caixa;
}

dados_lancamento consulta_dados_lancamento(dados_lancamento lancamento, int tipo, int i) {

    switch(tipo){
        case 1:
            if (p_lancamento[i].cod == lancamento.cod) {
                return p_lancamento[i];
                                                        }
        break;
        
        case 2:
            if (p_lancamento[i].data[0] == lancamento.data[0] && p_lancamento[i].data[1] == lancamento.data[1] && p_lancamento[i].data[2] == lancamento.data[2]) {
                return p_lancamento[i];
                                                        }
        break;
        
        case 3:
            if (p_lancamento[i].tipo == lancamento.tipo) {
                return p_lancamento[i];
                                                        }
        break;
        
        case 4:
            if(strstr(p_lancamento[i].fonte, lancamento.fonte)!=NULL){
                return p_lancamento[i];
                                                                        }
        break;
 
                    }
    lancamento.cod=-1;
    return lancamento;
}

dados_retirada consulta_dados_retirada(dados_retirada retirada,int tipo, int i) {

    switch(tipo){
        case 1:
            if(p_retirada[i].cod == retirada.cod) {
                return p_retirada[i];
                                                    }
        break;
        
        case 2:
            if(p_retirada[i].data[0] == retirada.data[0] && p_retirada[i].data[1] == retirada.data[1] && p_retirada[i].data[2] == retirada.data[2]) {
                return p_retirada[i];
                                                    }
        break;
        
        case 3:
            if(strstr(p_retirada[i].fonte, retirada.fonte)!=NULL){
                return p_retirada[i];
                                                                        }      
        break;
                    }
    retirada.cod=-1;
    return retirada;
}

int verificacao_status_dados_lancamento(int cod) {

    int status, i;

    for (i = 0; i < tam_lancamento; i++) {
        if (cod == p_lancamento[i].cod) {
            status = 1;
        }
    }

    return status;

}

int verificacao_status_dados_retirada(int cod) {

    int status, i;

    for (i = 0; i < tam_retirada; i++) {
        if (cod == p_retirada[i].cod) {
            status = 1;
        }
    }

    return status;

}

int exclusao_dados_lancamento(int posicao_lancamento) {
    int i;

    for (i = posicao_lancamento; i < tam_lancamento; i++) {
        //reposicionando os dados e excluindo o dado desejado
        p_lancamento[i] = p_lancamento[i + 1];
    }
    //redimencionando o array
    p_lancamento = (dados_lancamento *) realloc(p_lancamento, (tam_lancamento - 1) * sizeof (dados_lancamento));

    if (p_lancamento == NULL) {
        return 0;
    } else {
        //diminuindo o tamanho do array
        tam_lancamento--;
        return 1;
    }

}

int exclusao_dados_retirada(int posicao_retirada) {
    int i;

    for (i = posicao_retirada; i < tam_retirada; i++) {
        //reposicionando os dados e excluindo o dado desejado
        p_retirada[i] = p_retirada[i + 1];
    }
    //redimencionando o array
    p_retirada = (dados_retirada *) realloc(p_retirada, (tam_retirada - 1) * sizeof (dados_retirada));

    if (p_retirada == NULL) {
        return 0;
    } else {
        //diminuindo o tamanho do array
        tam_retirada--;
        return 1;
    }

}

int verificacao_cod_lancamento(int cod) {

    int i;

    for (i = 0; i < tam_lancamento; i++) {
        //impede de verificar o mesmo cÃƒÂ³digo
        if (tam_lancamento - 1 == i) {
            continue;
        } else if (cod == p_lancamento[i].cod) {
            return i;
        }
    }

    return -1;

}

int verificacao_cod_retirada(int cod) {

    int i;

    for (i = 0; i < tam_retirada; i++) {
        //impede de verificar o mesmo cÃƒÂ³digo
        if (tam_retirada - 1 == i) {
            continue;
        } else if (cod == p_retirada[i].cod) {
            return i;
        }
    }

    return -1;
}

int salvar_dados_caixa(){

    int control;
    
    control = salvar_arquivo_retirada(p_retirada, tam_retirada);
    
    if(control==1){
        control = salvar_arquivo_lancamento(p_lancamento, tam_lancamento);
        
        if(control==1){
        control = salvar_arquivo_caixa(montante_caixa);
                        }
                    }
    return control;
}


