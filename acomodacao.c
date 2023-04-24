/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 22 de janeiro de 2021, 15:26
 */

#include "acomodacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_acomodacao *p_acomodacao=NULL; //vetor da acomodacao
int tam_acomodacao=0;//tamanho do array

int inicializacao_acomodacao(){

        //le primeiro o tamanho do array
        tam_acomodacao = tamanho_arquivo_acomodacao();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_acomodacao>0){
        //criando um array para colocar os dados
        p_acomodacao = (dados_acomodacao *) malloc(tam_acomodacao*sizeof(dados_acomodacao));    
        for(int i=0;i<tam_acomodacao;i++){    
            p_acomodacao[i] = ler_arquivo_acomodacao(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_acomodacao[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_acomodacao==-2){
            tam_acomodacao=0;
            return -1;
        }else{
            tam_acomodacao=0;
                }                                 
    return 0;
}

int verificacao_indice_acomodacao(int cod){

    int i;
       
    for(i=0;i<tam_acomodacao;i++){
        if(cod==p_acomodacao[i].cod){
        return i;
                                        }
                                    }            
    return -1;

}

int verificacao_cod_acomodacao(int cod){

    int i;
    
        for(i=0;i<tam_acomodacao;i++){
            //impede de verificar o mesmo código
            if(tam_acomodacao-1==i){
                continue;
                                    }
            else if(cod==p_acomodacao[i].cod){
                return i;
                                               }
                                        }
        
    return -1;                                    
}

int salvar_acomodacao(){

    return salvar_arquivo_acomodacao(p_acomodacao, tam_acomodacao);
}

int exclusao_dados_acomodacao(int posicao_acomodacao){

    int i;
    
        for(i=posicao_acomodacao;i<tam_acomodacao;i++){
            //reposicionando os dados e excluindo o dado desejado
            p_acomodacao[i]=p_acomodacao[i+1];
                                                        }
        //redimencionando o array
        p_acomodacao = (dados_acomodacao *) realloc(p_acomodacao, (tam_acomodacao-1)*sizeof(dados_acomodacao));
        
        if(p_acomodacao == NULL){
            return 0;
        }else{
            //diminuindo o tamanho do array
            tam_acomodacao--;
            return 1;
              }
}

int cadastro_acomodacao(dados_acomodacao acomodacao){

    tam_acomodacao++;//somando mais um para o array
    int control_cod, i=0;
    
    //gerando um codigo para a acomodacao
    do{
        acomodacao.cod=tam_acomodacao+i;
        control_cod = verificacao_cod_acomodacao(acomodacao.cod);
        i++;
        }
    while(control_cod!=-1);    
       
    //condicao para o primeiro cadastro
    if(tam_acomodacao==1){
        p_acomodacao = (dados_acomodacao *) malloc(tam_acomodacao * sizeof(dados_acomodacao));
                            }
    //para futuros cadastros
    else{
        p_acomodacao = (dados_acomodacao *) realloc(p_acomodacao, tam_acomodacao*sizeof(dados_acomodacao));
        }
    //atribuindo o novo cadastro a ultima posicao do array
    p_acomodacao[tam_acomodacao-1]=acomodacao;
        
    return p_acomodacao[tam_acomodacao-1].cod;
}

void alteracao_dados_acomodacao(dados_acomodacao acomodacao, int tipo, int indice){

    switch(tipo){
        case 1:
            p_acomodacao[indice].cod=acomodacao.cod;
        break;  
        
        case 2:
            strcpy(p_acomodacao[indice].descricao,acomodacao.descricao);
        break;
        
        case 3:
            strcpy(p_acomodacao[indice].facilidades,acomodacao.facilidades);
        break;
        
        case 4:
            p_acomodacao[indice].categoria=acomodacao.categoria;
        break; 
        
        case 5:
            p_acomodacao[indice].num_quarto=acomodacao.num_quarto;
        break;
        
                };
    
}

int tam_do_array_acomodacao(){

    return tam_acomodacao;
}

dados_acomodacao consulta_acomodacao(dados_acomodacao acomodacao, int tipo, int i){
    
    switch(tipo){
        case 1:
            if(acomodacao.cod==p_acomodacao[i].cod){
                return p_acomodacao[i];
                                                    }                                       
        break;
        
        case 2:
            if(strstr(p_acomodacao[i].descricao, acomodacao.descricao)==NULL){
            }else{
                return p_acomodacao[i];
                    }                                        
        break;
        
        case 3:
            if(strstr(p_acomodacao[i].facilidades, acomodacao.facilidades)==NULL){
            }else{
                return p_acomodacao[i];
                    }                                        
        break;
        
        case 4:
            if(acomodacao.categoria==p_acomodacao[i].categoria){
                return p_acomodacao[i];
                                                                }                                        
        break; 
        
        case 5:
            if(acomodacao.num_quarto==p_acomodacao[i].num_quarto){
                return p_acomodacao[i];
                                                                }                                        
        break;
        
        case 6:
            return p_acomodacao[i];
        break;
                }
    acomodacao.cod=-1;
    return acomodacao;
}

void sair_acomodacao(){
    tam_acomodacao=0;
    free(p_acomodacao);
}
