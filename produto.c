/* 
 * File:   produto.c
 * Author: Tayna
 * 
 * Created on 8 de março de 2021, 23:23
 */

#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_produto *p_produto=NULL; //vetor do produto
int tam_produto=0;//tamanho do array;

int inicializacao_produto(){

        //le primeiro o tamanho do array
        tam_produto = tamanho_arquivo_produto();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_produto>0){
        //criando um array para colocar os dados
        p_produto = (dados_produto *) malloc(tam_produto*sizeof(dados_produto));    
        for(int i=0;i<tam_produto;i++){    
            p_produto[i] = ler_arquivo_produto(i);
            
            //para caso de erro ao abrir o arquivo para ler o array
            if(p_produto[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_produto==-2){
            tam_produto=0;
            return -1;
        }else{
            tam_produto=0;
        }
                                           
    return 0;
}

int verificacao_indice_produto(int cod){

    int i;

       for(i=0;i<tam_produto;i++){
            if(cod==p_produto[i].cod){
                return i;
                                        }
                                    }
    
    return -1;
}

int verificacao_cod_produto(int cod){

    int i;
    
       for(i=0;i<tam_produto;i++){
           //para nao verificar o mesmo código
            if(tam_produto-1==i){
                continue;
                                    }
            else if(cod==p_produto[i].cod){
                    return i;
                                                }
                                        }
    return -1;                                    
}


int exclusao_dados_produto(int codigo){
    
    int i;

        for(i=codigo;i<tam_produto-1;i++){
            //reposicionando os dados e excluindo o dado desejado
            p_produto[i]=p_produto[i+1];
                                    }
        //redimencionando o array                            
        p_produto = (dados_produto *) realloc(p_produto, (tam_produto-1)*sizeof(dados_produto));
        if(p_produto == NULL){ 
            return 0;
        }else{
            //diminuindo o tamanho do array
            tam_produto--;
            return 1;
                }
    
}

int cadastro_produto(dados_produto produto){

    tam_produto++;//somando mais um para o array
    int control_cod, i=0;
    
    //gerando um codigo para o produto
    do{
        produto.cod=tam_produto+i;
        control_cod = verificacao_cod_produto(produto.cod);
        i++;
        }
    while(control_cod!=-1);
    
    //quando for o primeiro cadastro
    if(tam_produto==1){
        p_produto = (dados_produto *) malloc(tam_produto*sizeof(dados_produto));
                        }
    //para futuros cadastros
    else{
        p_produto = (dados_produto *) realloc(p_produto, tam_produto*sizeof(dados_produto));
            }
    //atribuindo o novo cadastro a ultima posicao do array
    p_produto[tam_produto-1]=produto;
    
    return p_produto[tam_produto-1].cod;
}

void alteracao_dados_produto(dados_produto produto, int tipo, int indice){
    
    switch(tipo){
        case 1:
            p_produto[indice].cod=produto.cod;
        break;  
        
        case 2:
            strcpy(p_produto[indice].descricao,produto.descricao);
        break;
        
        case 3:
           p_produto[indice].estoque=produto.estoque;
        break;
        
        case 4:
            p_produto[indice].estoque_min=produto.estoque_min;
        break; 
                
        case 5:
           p_produto[indice].preco_custo=produto.preco_custo;
        break;
        
        case 6:
           p_produto[indice].preco_venda=produto.preco_venda;
        break;
        
        case 7:
            strcpy(p_produto[indice].fornecedor,produto.fornecedor);
        break;
        };
        
    return;
}

int tam_do_array_produto(){

    return tam_produto;
}

dados_produto consulta_produto(dados_produto produto, int tipo, int i){
    
    switch(tipo){
        case 1:
            if(p_produto[i].cod==produto.cod){
                return p_produto[i];                                                 
                                                } 
        break;
        
        case 2:
             if(strstr(p_produto[i].descricao, produto.descricao)!=NULL){
                return p_produto[i];
                                                                            }
        break;
        
        case 3:
            if(p_produto[i].estoque==produto.estoque){
                return p_produto[i];                                                 
                                                        }
        break;
        
        case 4:
            if(p_produto[i].estoque_min==produto.estoque_min){
                return p_produto[i];                                                 
                                                                }
        break;
        
        case 5:
            if(p_produto[i].preco_custo==produto.preco_custo){
                return p_produto[i];                                                 
                                                                }
        break;
        
        case 6:
            if(p_produto[i].preco_venda==produto.preco_venda){
                return p_produto[i];                                                 
                                                                }
        break;
        
        case 7:
             if(strstr(p_produto[i].fornecedor, produto.fornecedor)!=NULL){
                return p_produto[i];
                                                                            }
        break;
        
        case 8:
                return p_produto[i];
        break;
        }
    
    //igualando o codigo do produto a saida de nao encontrado
    produto.cod=-1;
    return produto;
}

int salvar_produto(){
    
    return salvar_arquivo_produto(p_produto, tam_produto);
}

void sair_produto(){
    tam_produto=0;
    free(p_produto);
}

int estoque_produto(dados_produto produto, int i){

            if((p_produto[i].estoque)<produto.estoque){
                return -1;                                                 
                                                        }
            return 1;
}