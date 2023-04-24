#include "checkout.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "acomodacao.h"
#include "categoria.h"
#include "checkin.h"
#include "Reserva.h"

dados_checkout *p_checkout = NULL;
int tam_checkout = 0;

int inicializacao_checkout() {

    //le primeiro o tamanho do array
        tam_checkout = tamanho_arquivo_checkout();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_checkout>0){
        //criando um array para colocar os dados
        p_checkout = (dados_checkout *) malloc(tam_checkout*sizeof(dados_checkout));    
        for(int i=0;i<tam_checkout;i++){    
            p_checkout[i] = ler_arquivo_checkout(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_checkout[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_checkout==-2){
            tam_checkout=0;
            return -1;
        }else{
            tam_checkout=0;
                }                                 
    return 0;
}

int cadastro_checkout(dados_checkout checkout, char* hora) {

    tam_checkout++; //somando mais um para o array
    int control_cod, i = 0;

    //gerando um codigo para o checkin
    do {
        checkout.cod = tam_checkout + i;
        control_cod = verificacao_cod_checkout(checkout.cod);
        i++;
    } while (control_cod != -1);

    //condicao para o primeiro cadastro
    if (tam_checkout == 1) {
        p_checkout = (dados_checkout *) malloc(tam_checkout * sizeof (dados_checkout));
    }//para futuros cadastros
    else {
        p_checkout = (dados_checkout *) realloc(p_checkout, tam_checkout * sizeof (dados_checkout));
    }

    checkout = redefine_horario_checkout(checkout, hora);

    //atribuindo o novo cadastro a ultima posicao do array
    p_checkout[tam_checkout - 1] = checkout;

    return p_checkout[tam_checkout - 1].cod;
};

int verificacao_indice_checkout(int cod) {

    int i;

    for (i = 0; i < tam_checkout; i++) {
        if (cod == p_checkout[i].cod) {
            return i;
        }
    }
    return -1;

}

int verificacao_cod_checkout(int cod) {

    int i;

    for (i = 0; i < tam_checkout; i++) {
        //impede de verificar o mesmo cÃƒÂ³digo
        if (tam_checkout - 1 == i) {
            continue;
        } else if (cod == p_checkout[i].cod) {
            return i;
        }
    }

    return -1;
}

int exclusao_dados_checkout(int posicao_checkout) {

    int i;

    for (i = posicao_checkout; i < tam_checkout; i++) {
        //reposicionando os dados e excluindo o dado desejado
        p_checkout[i] = p_checkout[i + 1];
    }
    //redimencionando o array
    p_checkout = (dados_checkout *) realloc(p_checkout, (tam_checkout - 1) * sizeof (dados_checkout));

    if (p_checkout == NULL) {
        return 0;
    } else {
        //diminuindo o tamanho do array
        tam_checkout--;
        return 1;
    }
}

void sair_checkout() {
    tam_checkout = 0;
    free(p_checkout);
}

dados_checkout consulta_checkout(dados_checkout checkout, int i, int menu) {

    switch (menu) {
        case 1:
            if (p_checkout[i].cod == checkout.cod) {
                return p_checkout[i];
            }
            break;

        case 2:
            if (p_checkout[i].cod_hospede == checkout.cod_hospede) {
                return p_checkout[i];
            }
            break;
    }

    checkout.cod = -1;
    return checkout;
}

dados_checkout checkout_por_reserva(int cod_reserva) {

    int i, indice = 0;

    for (i = 0; i < tam_checkout; i++) {
        if (p_checkout[i].cod == cod_reserva) {
            indice = i;
        }
    }
    return p_checkout[indice];
}

float consulta_pagamento_checkout(dados_checkout p_checkout, dados_reserva p_reserva) {

    dados_categoria p_categoria, categoria;
    dados_acomodacao p_acomodacao, acomodacao;
    int tam, i, diarias;

    //buscando a acomodacao
    tam = tam_do_array_acomodacao();
    acomodacao.num_quarto = p_reserva.acomodacao;
    for (i = 0; i < tam; i++) {
        p_acomodacao = consulta_acomodacao(acomodacao, 5, i);

        if (p_acomodacao.cod != -1) {
            //buscando a categoria
            categoria.cod = p_acomodacao.categoria;
            tam = tam_do_array_categoria();
            for (i = 0; i < tam; i++) {
                p_categoria = consulta_categoria(categoria, 1, i, 0, 0);

                if (p_categoria.cod == -1) {
                    break;
                }
            }
            break;
        }
    }

    p_checkout = checkout_por_reserva(p_checkout.cod_reserva);

    if (p_reserva.dia_saida > p_reserva.dia_chegada) {
        diarias = ((p_reserva.dia_saida)-(p_reserva.dia_chegada));
    } else {
        diarias = ((p_reserva.dia_chegada)-(p_reserva.dia_saida));
    }

    //return p_checkout.valor_pagamento = p_categoria.valor_diaria * diarias;
}

dados_checkout redefine_horario_checkout(dados_checkout checkout, char* hora) {

    int i = 0;
    char *token = strtok(hora, ":");

    while (token != NULL) {
        checkout.hora[i] = atoi(token);
        token = strtok(NULL, ":");
        i++;
    }

    return checkout;
};

int tam_do_array_checkout() {
    return tam_checkout;
}

int salvar_checkout() {
    return salvar_arquivo_checkout(p_checkout, tam_checkout);
}