/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "categoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

dados_categoria *p_categoria=NULL; //vetor da categoria
int tam_categoria=0;//tamanho do array

int inicializacao_categoria(){

        //le primeiro o tamanho do array
        tam_categoria = tamanho_arquivo_categoria();
        //caso tenha dados ler os dados e passar para o ponteiro do array
        if(tam_categoria>0){
        //criando um array para colocar os dados
        p_categoria = (dados_categoria *) malloc(tam_categoria*sizeof(dados_categoria));    
        for(int i=0;i<tam_categoria;i++){    
            p_categoria[i] = ler_arquivo_categoria(i);
            
            //para caso de erro ao abrir o arquivo para ler os array
            if(p_categoria[i].cod==-1){
                return -1;
                                        }
                                         }
                                }
        //para caso de erro ao abrir o arquivo para ler o tamanho do array
        else if(tam_categoria==-2){
            tam_categoria=0;
            return -1;
        }else{
            tam_categoria=0;
                }                                 
    return 0;
}

int verificacao_indice_categoria(int cod){

    int i;

       for(i=0;i<tam_categoria;i++){
            if(cod==p_categoria[i].cod){
                return i;
                                        }
                                    }
    
    return -1;
}

int verificacao_cod_categoria(int cod){

    int i;
    
       for(i=0;i<tam_categoria;i++){
           //para nao verificar o mesmo código
            if(tam_categoria-1==i){
                continue;
                                    }
            else if(cod==p_categoria[i].cod){
                    return i;
                                                }
                                        }
      
    return -1;                                    
}


int exclusao_dados_categoria(int codigo){
    
    int i;

        for(i=codigo;i<tam_categoria-1;i++){
            //reposicionando os dados e excluindo o dado desejado
            p_categoria[i]=p_categoria[i+1];
                                    }
        //redimencionando o array                            
        p_categoria = (dados_categoria *) realloc(p_categoria, (tam_categoria-1)*sizeof(dados_categoria));
        if(p_categoria == NULL){ 
            return 0;
        }else{
            //diminuindo o tamanho do array
            tam_categoria--;
            return 1;
                }
    
}

int cadastro_categoria(dados_categoria categoria){

    tam_categoria++;//somando mais um para o array
    int control_cod, i=0;
    
    //gerando um codigo para a categoria
    do{
        categoria.cod=tam_categoria+i;
        control_cod = verificacao_cod_categoria(categoria.cod);
        i++;
        }
    while(control_cod!=-1);
    
    //quando for o primeiro cadastro
    if(tam_categoria==1){
        p_categoria = (dados_categoria *) malloc(tam_categoria*sizeof(dados_categoria));
                        }
    //para futuros cadastros
    else{
        p_categoria = (dados_categoria *) realloc(p_categoria, tam_categoria*sizeof(dados_categoria));
            }
    //atribuindo o novo cadastro a ultima posicao do array
    p_categoria[tam_categoria-1]=categoria;
    
    return p_categoria[tam_categoria-1].cod;
}

void alteracao_dados_categoria(dados_categoria categoria, int tipo, int indice){
    
    switch(tipo){
        case 1:
            strcpy(p_categoria[indice].nome,categoria.nome);
        break;  
        
        case 2:
            p_categoria[indice].cod=categoria.cod;
        break;
        
        case 3:
           strcpy(p_categoria[indice].descricao,categoria.descricao);
        break;
        
        case 4:
            p_categoria[indice].valor_diaria=categoria.valor_diaria;
        break; 
                
        case 5:
            p_categoria[indice].hospede[1]=categoria.hospede[1];
            p_categoria[indice].hospede[2]=categoria.hospede[2];
        break;
        };

    return;
}

int tam_do_array_categoria(){

    return tam_categoria;
}

dados_categoria consulta_categoria(dados_categoria categoria, int tipo, int i, float valor[], int sub_menu){
    
    switch(tipo){
        case 1:
            if(p_categoria[i].cod==categoria.cod){
                return p_categoria[i];
                                                    } 
        break;
        
        case 2:
            if(strcmp(p_categoria[i].nome, categoria.nome)==0){
                return p_categoria[i];
                                                                }
        break;
        
        case 3:
            if(strstr(p_categoria[i].descricao, categoria.descricao)==NULL){
            }else{
                return p_categoria[i];
                    }
        break;
        
        case 4:
            switch(sub_menu){
                case 1:
                    if(valor[0]<=p_categoria[i].valor_diaria){
                        return p_categoria[i];
                                                            }
                    
                break;
                    
                case 2:
                    if(valor[1]>=p_categoria[i].valor_diaria){
                        return p_categoria[i];
                                                            }
                break;
                    
                case 3:
                    if(valor[1]>=p_categoria[i].valor_diaria && valor[0]<=p_categoria[i].valor_diaria){
                        return p_categoria[i];
                                                                                                        }
                    break;
                            }
        break;
        
        case 5:
            if(p_categoria[i].hospede[0]==categoria.hospede[0] && p_categoria[i].hospede[1]==categoria.hospede[1]){
                return p_categoria[i];
            }
        break;
        }
    categoria.cod=-1;
    
    return categoria;
}

int salvar_categoria(){
    
    return salvar_arquivo_categoria(p_categoria, tam_categoria);
}

void sair_categoria(){
    tam_categoria=0;
    free(p_categoria);
}