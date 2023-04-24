/* 
 * File:   fornecedor.c
 * Author: Tayna
 * 
 * Created on 14 de março de 2021, 14:54
 */

#include "fornecedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_fornecedor *p_fornecedor=NULL; //vetor do fornecedor
int tam_fornecedor=0;//tamanho do array;

int inicializacao_fornecedor(){

        //le primeiro o tamanho do array
        tam_fornecedor = tamanho_arquivo_fornecedor();       
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_fornecedor>0){
        //criando um array para colocar os dados
        p_fornecedor = (dados_fornecedor *) malloc(tam_fornecedor*sizeof(dados_fornecedor));    
        for(int i=0;i<tam_fornecedor;i++){    
            p_fornecedor[i] = ler_arquivo_fornecedor(i);
            
            //para caso de erro ao abrir o arquivo para ler o array
            if(p_fornecedor[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_fornecedor==-2){
            tam_fornecedor=0;
            return -1;
        }else{
            tam_fornecedor=0;
                }
                                           
    return 0;
}

int verificacao_indice_fornecedor(int cod){

    int i;

       for(i=0;i<tam_fornecedor;i++){
            if(cod==p_fornecedor[i].cod){
                return i;
                                        }
                                    }
    
    return -1;
}

int verificacao_cod_fornecedor(int cod){

    int i;
    
       for(i=0;i<tam_fornecedor;i++){
           //para nao verificar o mesmo código
            if(tam_fornecedor-1==i){
                continue;
                                    }
            else if(cod==p_fornecedor[i].cod){
                    return i;
                                                }
                                        }
    return -1;                                    
}


int exclusao_dados_fornecedor(int codigo){
    
    int i;

        for(i=codigo;i<tam_fornecedor-1;i++){
            //reposicionando os dados e excluindo o dado desejado
            p_fornecedor[i]=p_fornecedor[i+1];
                                    }
        //redimencionando o array                            
        p_fornecedor = (dados_fornecedor *) realloc(p_fornecedor, (tam_fornecedor-1)*sizeof(dados_fornecedor));
        if(p_fornecedor == NULL){ 
            return 0;
        }else{
            //diminuindo o tamanho do array
            tam_fornecedor--;
            return 1;
                }
    
}

int cadastro_fornecedor(dados_fornecedor fornecedor){

    tam_fornecedor++;//somando mais um para o array
    int control_cod, i=0;
    
    //gerando um codigo para o fornecedor
    do{
        fornecedor.cod=tam_fornecedor+i;
        control_cod = verificacao_cod_fornecedor(fornecedor.cod);
        i++;
        }
    while(control_cod!=-1);
    
    //quando for o primeiro cadastro
    if(tam_fornecedor==1){
        p_fornecedor = (dados_fornecedor *) malloc(tam_fornecedor*sizeof(dados_fornecedor));
                        }
    //para futuros cadastros
    else{
        p_fornecedor = (dados_fornecedor *) realloc(p_fornecedor, tam_fornecedor*sizeof(dados_fornecedor));
            }
    //atribuindo o novo cadastro a ultima posicao do array
    p_fornecedor[tam_fornecedor-1]=fornecedor;
    
    return p_fornecedor[tam_fornecedor-1].cod;
}

void alteracao_dados_fornecedor(dados_fornecedor fornecedor, int tipo, int indice){
    
    switch(tipo){
        case 1:
            p_fornecedor[indice].cod=fornecedor.cod;
        break;  
        
        case 2:
            strcpy(p_fornecedor[indice].nome_fantasia,fornecedor.nome_fantasia);
        break;
        
        case 3:
            strcpy(p_fornecedor[indice].razao_social,fornecedor.razao_social);
        break;
        
        case 4:
            strcpy(p_fornecedor[indice].incricao_est,fornecedor.incricao_est);
        break; 
                
        case 5:
            strcpy(p_fornecedor[indice].cnpj,fornecedor.cnpj);
        break;
        
        case 6:
            strcpy(p_fornecedor[indice].endereco,fornecedor.endereco);
        break;
        
        case 7:
            strcpy(p_fornecedor[indice].telefone,fornecedor.telefone);
        break;
        
        case 8:
            strcpy(p_fornecedor[indice].email,fornecedor.email);
        break;
        };
        
    return;
}

int tam_do_array_fornecedor(){

    return tam_fornecedor;
}

dados_fornecedor consulta_fornecedor(dados_fornecedor fornecedor, int tipo, int i){
    
    switch(tipo){
        case 1:
            if(p_fornecedor[i].cod==fornecedor.cod){
                return p_fornecedor[i];                                                 
                                                    } 
        break;
        
        case 2:
             if(strstr(p_fornecedor[i].nome_fantasia, fornecedor.nome_fantasia)!=NULL){
                return p_fornecedor[i];
                                                                                        }
        break;
        
        case 3:
            if(strstr(p_fornecedor[i].razao_social, fornecedor.razao_social)!=NULL){
                return p_fornecedor[i];
                                                                                    }
        break;
        
        case 4:
            if(strstr(p_fornecedor[i].incricao_est, fornecedor.incricao_est)!=NULL){
                return p_fornecedor[i];
                                                                                    }
        break;
        
        case 5:
            if(strstr(p_fornecedor[i].cnpj, fornecedor.cnpj)!=NULL){
                return p_fornecedor[i];
                                                                     }
        break;
        
        case 6:
            if(strstr(p_fornecedor[i].endereco, fornecedor.endereco)!=NULL){
                return p_fornecedor[i];
                                                                            }
        break;
        
        case 7:
            if(strstr(p_fornecedor[i].telefone, fornecedor.telefone)!=NULL){
                return p_fornecedor[i];
                                                                            }
        break;
        
        case 8:
            if(strstr(p_fornecedor[i].email, fornecedor.email)!=NULL){
                return p_fornecedor[i];                                                                            }
        break;
        }
    
    //igualando o codigo do produto a saida de nao encontrado
    fornecedor.cod=-1;
    return fornecedor;
}

int salvar_fornecedor(){
    
    return salvar_arquivo_fornecedor(p_fornecedor, tam_fornecedor);
}

void sair_fornecedor(){
    tam_fornecedor=0;
    free(p_fornecedor);
}
