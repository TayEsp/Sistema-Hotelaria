#include "hotel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_hotel *p_hotel = NULL;
int tam_hotel = 0;

int inicializacao_hotel() {

    //le primeiro o tamanho do array
        tam_hotel = tamanho_arquivo_hotel();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_hotel>0){
        //criando um array para colocar os dados
        p_hotel = (dados_hotel *) malloc(tam_hotel*sizeof(dados_hotel));    
        for(int i=0;i<tam_hotel;i++){    
            p_hotel[i] = ler_arquivo_hotel(i);
            
            //para caso de erro ao abrir o arquivo para ler o array
            if(p_hotel[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_hotel==-2){
            tam_hotel=0;
            return -1;
        }else{
            tam_hotel=0;
        }
                                           
    return 0;
}

int verificacao_indice_hotel(int cod) {

    int i;

    for (i = 0; i < tam_hotel; i++) {
        if (cod == p_hotel[i].cod) {
            return i;
        }
    }
    return -1;

}

int verificacao_cod_hotel(int cod) {

    int i;

    for (i = 0; i < tam_hotel; i++) {

        if (tam_hotel - 1 == i) {
            continue;
        } else if (cod == p_hotel[i].cod) {
            return i;
        }
    }

    return -1;
}

int salvar_hotel() {

    return salvar_arquivo_hotel(p_hotel, tam_hotel);
}

int exclusao_dados_hotel(int posicao_hotel) {

    int i;

    for (i = posicao_hotel; i < tam_hotel; i++) {

        p_hotel[i] = p_hotel[i + 1];
    }

    p_hotel = (dados_hotel *) realloc(p_hotel, (tam_hotel - 1) * sizeof (dados_hotel));

    if (p_hotel == NULL) {
        return 0;
    } else {

        tam_hotel--;
        return 1;
    }
}

int cadastro_hotel(dados_hotel hotel) {

    tam_hotel++;
    int control_cod, i = 0;

    do {
        hotel.cod = tam_hotel + i;
        control_cod = verificacao_cod_hotel(hotel.cod);
        i++;
    } while (control_cod != -1);

    if (tam_hotel == 1) {
        p_hotel = (dados_hotel *) malloc(tam_hotel * sizeof (dados_hotel));
    } else {
        p_hotel = (dados_hotel *) realloc(p_hotel, tam_hotel * sizeof (dados_hotel));
    }

    p_hotel[tam_hotel - 1] = hotel;

    return p_hotel[tam_hotel - 1].cod;
}

void alteracao_dados_hotel(dados_hotel hotel, int tipo, int indice) {

    switch (tipo) {
        case 1:
            p_hotel[indice].cod = hotel.cod;
            break;

        case 2:
            strcpy(p_hotel[indice].nome_fantasia, hotel.nome_fantasia);
            break;

        case 3:
            strcpy(p_hotel[indice].razao_social, hotel.razao_social);
            break;

        case 4:
            strcpy(p_hotel[indice].inscricao_estadual, hotel.inscricao_estadual);
            break;

        case 5:
            strcpy(p_hotel[indice].cnpj, hotel.cnpj);
            break;

        case 6:
            strcpy(p_hotel[indice].endereco_completo, hotel.endereco_completo);
            break;

        case 7:
            strcpy(p_hotel[indice].telefone_hotel, hotel.telefone_hotel);
            break;

        case 8:
            strcpy(p_hotel[indice].email_hotel, hotel.email_hotel);
            break;

        case 9:
            strcpy(p_hotel[indice].nome_responsavel, hotel.nome_responsavel);
            break;
            
        case 10:
            strcpy(p_hotel[indice].telefone_responsavel, hotel.telefone_responsavel);
            break;
            
             case 11: 
            strcpy(p_hotel[indice].check_in, hotel.check_in);
            break;
            
             case 12: 
            strcpy(p_hotel[indice].check_out, hotel.check_out);
            break;
            
             case 13: 
            strcpy(p_hotel[indice].margem_lucro, hotel.margem_lucro);
            break;            

    };
}

int tam_do_array_hotel() {

    return tam_hotel;
}

dados_hotel consulta_hotel(dados_hotel hotel, int tipo, int i) {

    switch (tipo) {
        case 1:
            if (hotel.cod == p_hotel[i].cod) {
                return p_hotel[i];
            }
            break;

        case 2:
            if (strstr(p_hotel[i].nome_fantasia, hotel.nome_fantasia) == NULL) {
            } else {
                return p_hotel[i];
            }
            break;

        case 3:
            if (strstr(p_hotel[i].cnpj, hotel.cnpj) == NULL) {
            } else {
                return p_hotel[i];
            }
            break;

        case 4:
            if (strstr(p_hotel[i].inscricao_estadual, hotel.inscricao_estadual) == NULL) {
            } else {
                return p_hotel[i];
            }
            break;

        case 5:
            return p_hotel[i];
            break;
    }
    hotel.cod = -1;
    return hotel;
}

void sair_hotel() {
    tam_hotel = 0;
    free(p_hotel);
}


