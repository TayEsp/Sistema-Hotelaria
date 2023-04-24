#include "operador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_operador *p_operador = NULL;
int tam_operador = 0;

int inicializacao_operador(){

        //le primeiro o tamanho do array
        tam_operador = tamanho_arquivo_operador();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_operador>0){
        //criando um array para colocar os dados
        p_operador = (dados_operador *) malloc(tam_operador*sizeof(dados_operador));    
        for(int i=0;i<tam_operador;i++){    
            p_operador[i] = ler_arquivo_operador(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_operador[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_operador==-2){
            tam_operador=0;
            return -1;
        }else{
            tam_operador=0;
                }                                 
    return 0;
}

int verificacao_indice_operador(int cod) {

    int i;

    for (i = 0; i < tam_operador; i++) {
        if (cod == p_operador[i].cod) {
            return i;
        }
    }
    return -1;

}

int verificacao_cod_operador(int cod) {

    int i;

    for (i = 0; i < tam_operador; i++) {

        if (tam_operador - 1 == i) {
            continue;
        } else if (cod == p_operador[i].cod) {
            return i;
        }
    }

    return -1;
}

int salvar_operador() {

    return salvar_arquivo_operador(p_operador, tam_operador);
}

int exclusao_dados_operador(int posicao_operador) {

    int i;

    for (i = posicao_operador; i < tam_operador; i++) {

        p_operador[i] = p_operador[i + 1];
    }

    p_operador = (dados_operador *) realloc(p_operador, (tam_operador - 1) * sizeof (dados_operador));

    if (p_operador == NULL) {
        return 0;
    } else {

        tam_operador--;
        return 1;
    }
}

int cadastro_operador(dados_operador operador) {

    tam_operador++;
    int control_cod, i = 0;

    do {
        operador.cod = tam_operador + i;
        control_cod = verificacao_cod_operador(operador.cod);
        i++;
    } while (control_cod != -1);

    if (tam_operador == 1) {
        p_operador = (dados_operador *) malloc(tam_operador * sizeof (dados_operador));
    } else {
        p_operador = (dados_operador *) realloc(p_operador, tam_operador * sizeof (dados_operador));
    }

    p_operador[tam_operador - 1] = operador;

    return p_operador[tam_operador - 1].cod;
}

void alteracao_dados_operador(dados_operador operador, int tipo, int indice) {

    switch (tipo) {
        case 1:
            p_operador[indice].cod = operador.cod;
            break;

        case 2:
            strcpy(p_operador[indice].nome, operador.nome);
            break;

        case 3:
            strcpy(p_operador[indice].usuario, operador.usuario);
            break;

        case 4:
            strcpy(p_operador[indice].senha, operador.senha);
            break;

        case 5:
            strcpy(p_operador[indice].categoria, operador.categoria);
            break;

    };
}

int tam_do_array_operador() {

    return tam_operador;
}

dados_operador consulta_operador(dados_operador operador, int tipo, int i) {

    switch (tipo) {
        case 1:
            if (operador.cod == p_operador[i].cod) {
                return p_operador[i];
            }
            break;

        case 2:
            if (strstr(p_operador[i].nome, operador.nome) == NULL) {
            } else {
                return p_operador[i];
            }
            break;

        case 3:
            if (strstr(p_operador[i].usuario, operador.usuario) == NULL) {
            } else {
                return p_operador[i];
            }
            break;

        case 4:
            if (strstr(p_operador[i].nome, operador.nome) == NULL) {
            } else {
                return p_operador[i];
            }
            break;
            
        case 5:
            if (strstr(p_operador[i].senha, operador.senha) == NULL) {
            } else {
                return p_operador[i];
            }
            break;

        case 6:
            return p_operador[i];
        break;
    }
    operador.cod = -1;
    return operador;
}

void sair_operador(){
    free(p_operador);
    tam_operador=0;
}
