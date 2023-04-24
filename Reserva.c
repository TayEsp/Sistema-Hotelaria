/* 
 * File:   Reserva.c
 * Author: Tayna
 * 
 * Created on 21 de fevereiro de 2021, 14:49
 */

#include "Reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "acomodacao.h"
#include "categoria.h"

dados_reserva *p_reserva=NULL;
int tam_reserva=0;

int inicializacao_reserva(){

        //le primeiro o tamanho do array
        tam_reserva = tamanho_arquivo_reserva();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_reserva>0){
        //criando um array para colocar os dados
        p_reserva = (dados_reserva *) malloc(tam_reserva*sizeof(dados_reserva));    
        for(int i=0;i<tam_reserva;i++){    
            p_reserva[i] = ler_arquivo_reserva(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_reserva[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_reserva==-2){
            tam_reserva=0;
            return -1;
        }else{
            tam_reserva=0;
                }                                 
    return 0;
}

int cadastro_reserva(dados_reserva reserva, char* data_i, char* data_s){

    tam_reserva++;//somando mais um para o array
    int control_cod, i=0;
    
    //gerando um codigo para a reserva
    do{
        reserva.cod=tam_reserva+i;
        control_cod = verificacao_cod_reserva(reserva.cod);
        i++;
        }
    while(control_cod!=-1); 
    
    //redefinindo a data
    reserva = redefine_data(reserva, data_i, 1);
    reserva = redefine_data(reserva, data_s, 2);
                        
    //condicao para o primeiro cadastro
    if(tam_reserva==1){
        p_reserva = (dados_reserva *) malloc(tam_reserva * sizeof(dados_reserva));
                        }
    //para futuros cadastros
    else{
        p_reserva = (dados_reserva *) realloc(p_reserva, tam_reserva*sizeof(dados_reserva));
        }
    //atribuindo o novo cadastro a ultima posicao do array
    p_reserva[tam_reserva-1]=reserva;
        
    return p_reserva[tam_reserva-1].cod;

};

int verificacao_indice_reserva(int cod){

    int i;
       
    for(i=0;i<tam_reserva;i++){
        if(cod==p_reserva[i].cod){
        return i;
                                        }
                                    }            
    return -1;

}

int verificacao_cod_reserva(int cod){

    int i;
    
        for(i=0;i<tam_reserva;i++){
            //impede de verificar o mesmo código
            if(tam_reserva-1==i){
                continue;
                                    }
            else if(cod==p_reserva[i].cod){
                return i;
                                               }
                                        }
        
    return -1;                                    
}

dados_reserva redefine_data(dados_reserva reserva, char* data, int tipo){
    
    int i=0;
    char *token= strtok(data, "/");
    
    if(tipo==1){
        while(token!=NULL){
            reserva.dia_chegada[i]=atoi(token);
            token=strtok(NULL,"/");
            i++;
                            }
                    }
    else if(tipo==2){
        while(token!=NULL){
            reserva.dia_saida[i]=atoi(token);
            token=strtok(NULL,"/");
            i++;
                            }
                    }
    
    return reserva;
};

int verificacao_reserva(dados_acomodacao acomodacao, dados_reserva reserva, char* data_e, char* data_s){
    
    reserva = redefine_data(reserva, data_e, 1);
    reserva = redefine_data(reserva, data_s, 2);
    
    if(acomodacao.cod!=0){
        reserva.acomodacao==acomodacao.num_quarto;
                        }
    
    for(int i=0; i<tam_reserva; i++){
        //comparando o ano    
        if((p_reserva[i].dia_chegada[2]==reserva.dia_chegada[2] || p_reserva[i].dia_saida[2]==reserva.dia_saida[2]) || p_reserva[i].acomodacao==reserva.acomodacao){
            //comparando o mes
            if(p_reserva[i].dia_chegada[1]==reserva.dia_chegada[1] && p_reserva[i].dia_saida[1]==reserva.dia_saida[1]){
                //comparando os dias
                if((reserva.dia_saida[0]>=p_reserva[i].dia_chegada[0] && reserva.dia_saida[0]<=p_reserva[i].dia_saida[0]) || (reserva.dia_chegada[0]>=p_reserva[i].dia_chegada[0] && reserva.dia_chegada[0]<=p_reserva[i].dia_saida[0])){
                    return -1;
                }else{                   
                    continue;                                                   
                        }
            }else{               
                continue;                              
                    }
        }else{
            continue;                              
                }
    }
    return 1;
}

dados_acomodacao acomodacao_reserva(dados_acomodacao acomodacao, dados_categoria categoria, char* data_e, char* data_s, int i, char* sub_menu){

    dados_categoria categoria_pesquisa;
    dados_acomodacao acomodacao_pesquisa;
    dados_reserva reserva;
    int tam, j, control;                 
    
    //verificando uma acomodacao com a categoria
    if(strchr(sub_menu,'2')!=NULL){
        tam = tam_do_array_categoria();
                
        for(j=0;j<tam;j++){
            categoria_pesquisa = consulta_categoria(categoria, 2, j, 0, 0);
            if(categoria_pesquisa.cod!=-1){
                acomodacao_pesquisa.categoria=categoria_pesquisa.cod;
                acomodacao_pesquisa = consulta_acomodacao(acomodacao_pesquisa, 4, i);
                break;
                                            }
                            }
        
        if(acomodacao_pesquisa.cod==-1){
            acomodacao_pesquisa.cod=-1;
            return acomodacao_pesquisa;
                                        }
                                    }
            
    //verficando uma acomodacao com a quantidade
    if(strchr(sub_menu,'3')!=NULL){
        tam = tam_do_array_categoria();
                
        for(i=0;i<tam;i++){
            categoria_pesquisa = consulta_categoria(categoria, 5, i, 0, 0);
            if(categoria_pesquisa.cod!=-1){
                acomodacao_pesquisa.categoria=categoria_pesquisa.cod;
                acomodacao_pesquisa = consulta_acomodacao(acomodacao_pesquisa, 4, i);
                break;
                                            }
                            }
        
        if(acomodacao_pesquisa.cod==-1){
            acomodacao_pesquisa.cod=-1;
            return acomodacao_pesquisa;
                                }
                                        }
    //verficando uma acomodacao com a facilidade        
    if(strchr(sub_menu,'4')!=NULL){        
            acomodacao_pesquisa = consulta_acomodacao(acomodacao, 3, i);
            
            if(acomodacao_pesquisa.cod==-1){
                acomodacao_pesquisa.cod=-1;
                return acomodacao_pesquisa;
                                    }
                                        }
    
    //verficando uma acomodacao com a data
    if(strchr(sub_menu,'1')!=NULL && tam_reserva>0){
        control = verificacao_reserva(acomodacao_pesquisa, reserva, data_e, data_s);
        if(control==-1){
                    acomodacao_pesquisa.cod=-1;
                    return acomodacao_pesquisa;
                }else{                   
                    acomodacao_pesquisa = consulta_acomodacao(acomodacao, 6, i);                                                   
                        }
                                        }
    
    return acomodacao_pesquisa;
};

int exclusao_dados_reserva(int posicao_reserva){

    int i;
    
        for(i=posicao_reserva;i<tam_reserva;i++){
            //reposicionando os dados e excluindo o dado desejado
            p_reserva[i]=p_reserva[i+1];
                                                        }
        //redimencionando o array
        p_reserva = (dados_reserva *) realloc(p_reserva, (tam_reserva-1)*sizeof(dados_reserva));
        
        if(p_reserva == NULL){
            return 0;
        }else{
            //diminuindo o tamanho do array
            tam_reserva--;
            return 1;
              }
}

void sair_reserva(){
    tam_reserva=0;
    free(p_reserva);
}

dados_reserva consulta_reserva(dados_reserva reserva, char* data_entrada, char* data_saida, int i, int menu){
    
    switch(menu){
        case 1:
            if(p_reserva[i].cod==reserva.cod){
                return p_reserva[i];
                                                }
        break;
        
        case 2:
            if(p_reserva[i].cod_cliente==reserva.cod_cliente){
                return p_reserva[i];
                                                            }
        break;
        
        case 3:
            reserva = redefine_data(reserva, data_entrada, 1);
            reserva = redefine_data(reserva, data_saida, 2);
            
            if(p_reserva[i].dia_chegada[0]==reserva.dia_chegada[0] && p_reserva[i].dia_chegada[1]==reserva.dia_chegada[1] && p_reserva[i].dia_chegada[2]==reserva.dia_chegada[2]){
                if(p_reserva[i].dia_saida[0]==reserva.dia_saida[0] && p_reserva[i].dia_saida[1]==reserva.dia_saida[1] && p_reserva[i].dia_saida[2]==reserva.dia_saida[2]){
                    return p_reserva[i];
            }
                }                                      
        break;
        
        case 4:
            if(p_reserva[i].acomodacao==reserva.acomodacao){
                return p_reserva[i];
                                                            }
        break;
    }
    
    reserva.cod=-1;
    return reserva;
}

int tam_do_array_reserva(){
    return tam_reserva;
}

int salvar_reserva(){
    return salvar_arquivo_reserva(p_reserva, tam_reserva);
}