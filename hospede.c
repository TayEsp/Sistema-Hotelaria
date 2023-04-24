#include "hospede.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_hospede *p_hospede = NULL;
int tam_hospede = 0;

int inicializacao_hospede(){

    //le primeiro o tamanho do array
        tam_hospede = tamanho_arquivo_hospede();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_hospede>0){
        //criando um array para colocar os dados
        p_hospede = (dados_hospede *) malloc(tam_hospede*sizeof(dados_hospede));    
        for(int i=0;i<tam_hospede;i++){    
            p_hospede[i] = ler_arquivo_hospede(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_hospede[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_hospede==-2){
            tam_hospede=0;
            return -1;
        }else{
            tam_hospede=0;
                }                                 
    return 0;
    
}

int verificacao_indice_hospede(int cod) {

    int i;

    for (i = 0; i < tam_hospede; i++) {
        if (cod == p_hospede[i].cod) {
            return i;
        }
    }
    return -1;

}

int verificacao_cod_hospede(int cod) {

    int i;

    for (i = 0; i < tam_hospede; i++) {

        if (tam_hospede - 1 == i) {
            continue;
        } else if (cod == p_hospede[i].cod) {
            return i;
        }
    }

    return -1;
}

int salvar_hospede() {

    return salvar_arquivo_hospede(p_hospede, tam_hospede);
}

int exclusao_dados_hospede(int posicao_hospede) {

    int i;

    for (i = posicao_hospede; i < tam_hospede; i++) {

        p_hospede[i] = p_hospede[i + 1];
    }

    p_hospede = (dados_hospede *) realloc(p_hospede, (tam_hospede - 1) * sizeof (dados_hospede));

    if (p_hospede == NULL) {
        return 0;
    } else {

        tam_hospede--;
        return 1;
    }
}

int cadastro_hospede(dados_hospede hospede) {

    tam_hospede++;
    int control_cod, i = 0;

    do {
        hospede.cod = tam_hospede + i;
        control_cod = verificacao_cod_hospede(hospede.cod);
        i++;
    } while (control_cod != -1);

    if (tam_hospede == 1) {
        p_hospede = (dados_hospede *) malloc(tam_hospede * sizeof (dados_hospede));
    } else {
        p_hospede = (dados_hospede *) realloc(p_hospede, tam_hospede * sizeof (dados_hospede));
    }

    p_hospede[tam_hospede - 1] = hospede;

    return p_hospede[tam_hospede - 1].cod;
}

void alteracao_dados_hospede(dados_hospede hospede, int tipo, int indice) {

    switch (tipo) {
        case 1:
            p_hospede[indice].cod = hospede.cod;
            break;

        case 2:
            strcpy(p_hospede[indice].nome, hospede.nome);
            break;

        case 3:
            strcpy(p_hospede[indice].endereco_completo, hospede.endereco_completo);
            break;

        case 4:
            strcpy(p_hospede[indice].cpf, hospede.cpf);
            break;

        case 5:
            strcpy(p_hospede[indice].telefone_hospede, hospede.telefone_hospede);
            break;

        case 6:
            strcpy(p_hospede[indice].email_hospede, hospede.email_hospede);
            break;

        case 7:
            strcpy(p_hospede[indice].sexo, hospede.sexo);
            break;

        case 8:
            strcpy(p_hospede[indice].estado_civil, hospede.estado_civil);
            break;

        case 9:
            strcpy(p_hospede[indice].data_nascimento, hospede.data_nascimento);
            break;

    };
}

int tam_do_array_hospede() {

    return tam_hospede;
}

dados_hospede consulta_hospede(dados_hospede hospede, int tipo, int i) {

    switch (tipo) {
        case 1:
            if (hospede.cod == p_hospede[i].cod) {
                return p_hospede[i];
            }
            break;

        case 2:
            if (strstr(p_hospede[i].nome, hospede.nome) == NULL) {
            } else {
                return p_hospede[i];
            }
            break;

        case 3:
            if (strstr(p_hospede[i].cpf, hospede.cpf) == NULL) {
            } else {
                return p_hospede[i];
            }
            break;

        case 4:
            if (strstr(p_hospede[i].sexo, hospede.sexo) == NULL) {
            } else {
                return p_hospede[i];
            }
            break;

        case 5:
            return p_hospede[i];
            break;
    }
    hospede.cod = -1;
    return hospede;
}

void sair_hospede() {
    tam_hospede = 0;
    free(p_hospede);
}