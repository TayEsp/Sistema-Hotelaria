#include "checkin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "acomodacao.h"
#include "categoria.h"
#include "checkin.h"
#include "Reserva.h"

dados_checkin *p_checkin = NULL;
int tam_checkin = 0;

int inicializacao_checkin() {

   //le primeiro o tamanho do array
        tam_checkin = tamanho_arquivo_checkin();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_checkin>0){
        //criando um array para colocar os dados
        p_checkin = (dados_checkin *) malloc(tam_checkin*sizeof(dados_checkin));    
        for(int i=0;i<tam_checkin;i++){    
            p_checkin[i] = ler_arquivo_checkin(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_checkin[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_checkin==-2){
            tam_checkin=0;
            return -1;
        }else{
            tam_checkin=0;
                }                                 
    return 0;  
}

int cadastro_checkin(dados_checkin checkin, char* hora) {

    tam_checkin++; //somando mais um para o array
    int control_cod, i = 0;

    //gerando um codigo para o checkin
    do {
        checkin.cod = tam_checkin + i;
        control_cod = verificacao_cod_checkin(checkin.cod);
        i++;
    }    while (control_cod != -1);

    //condicao para o primeiro cadastro
    if (tam_checkin == 1) {
        p_checkin = (dados_checkin *) malloc(tam_checkin * sizeof (dados_checkin));
    }        //para futuros cadastros
    else {
        p_checkin = (dados_checkin *) realloc(p_checkin, tam_checkin * sizeof (dados_checkin));
    }
    
    checkin = redefine_horario_checkin(checkin, hora);
    
    //atribuindo o novo cadastro a ultima posicao do array
    p_checkin[tam_checkin - 1] = checkin;
    
    //salvando o checkin automaticamente
    control_cod = salvar_checkin();
    
    if(control_cod<1){
        return -1;
                        }

    return p_checkin[tam_checkin - 1].cod;
};

int verificacao_indice_checkin(int cod) {

    int i;

    for (i = 0; i < tam_checkin; i++) {
        if (cod == p_checkin[i].cod) {
            return i;
        }
    }
    return -1;

}

int verificacao_cod_checkin(int cod){

    int i;

    for (i = 0; i < tam_checkin; i++) {
        //impede de verificar o mesmo cÃ³digo
        if (tam_checkin - 1 == i) {
            continue;
        } else if (cod == p_checkin[i].cod) {
            return i;
        }
    }

    return -1;
}

int exclusao_dados_checkin(int posicao_checkin){

    int i;

    for (i = posicao_checkin; i < tam_checkin; i++) {
        //reposicionando os dados e excluindo o dado desejado
        p_checkin[i] = p_checkin[i + 1];
    }
    //redimencionando o array
    p_checkin = (dados_checkin *) realloc(p_checkin, (tam_checkin - 1) * sizeof (dados_checkin));

    if (p_checkin == NULL) {
        return 0;
    } else {
        //diminuindo o tamanho do array
        tam_checkin--;
        return 1;
    }
}

void sair_checkin() {
    tam_checkin = 0;
    free(p_checkin);
}

dados_checkin consulta_checkin(dados_checkin checkin, int i, int menu){

    switch (menu) {
        case 1:
            if (p_checkin[i].cod == checkin.cod) {
                return p_checkin[i];
            }
            break;

        case 2:
            if (p_checkin[i].cod_hospede == checkin.cod_hospede) {
                return p_checkin[i];
            }
            break;
    }

    checkin.cod = -1;
    return checkin;
}

float consulta_pagamento_checkin(dados_reserva p_reserva){
    
    dados_categoria pesquisa_categoria, categoria;
    dados_acomodacao pesquisa_acomodacao, acomodacao;
    int tam, i, diarias;
    
    inicializacao_categoria();
    inicializacao_acomodacao();
    //buscando a acomodacao
    tam = tam_do_array_acomodacao();
    acomodacao.num_quarto = p_reserva.acomodacao;
    for(i=0;i<tam;i++){
        pesquisa_acomodacao = consulta_acomodacao(acomodacao, 5, i);
        
        if(pesquisa_acomodacao.cod!=-1){
            //buscando a categoria
            categoria.cod=pesquisa_acomodacao.categoria;
            tam = tam_do_array_categoria();
            for(i=0;i<tam;i++){
                pesquisa_categoria = consulta_categoria(categoria, 1, i, 0, 0);
                
                if(pesquisa_categoria.cod==-1){
                    break;
                                        }
                                }               
                break;
                                }
                        }
    
    //calculando o valor da diaria
    if(p_reserva.dia_saida>p_reserva.dia_chegada){
        diarias = ((p_reserva.dia_saida)-(p_reserva.dia_chegada));
    }else{
        diarias = ((p_reserva.dia_chegada)-(p_reserva.dia_saida));
    }
    
    sair_acomodacao();
    sair_categoria();
    
    return pesquisa_categoria.valor_diaria * diarias;
}

dados_checkin redefine_horario_checkin(dados_checkin checkin, char* hora){
    
    int i=0;
    char *token= strtok(hora, ":");
    
    while(token!=NULL){
        checkin.hora[i]=atoi(token);
        token=strtok(NULL,":");
        i++;
                        }
 
    return checkin;
};

int tam_do_array_checkin() {
    return tam_checkin;
}

int salvar_checkin(){
    return salvar_arquivo_checkin(p_checkin, tam_checkin);
}