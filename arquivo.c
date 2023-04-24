/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 8 de janeiro de 2021, 13:57
 */

#include "arquivo.h"
#include "saida_produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int tipo_de_arquivamento = 0;

int tipo_arquivo(int tipo) {

    if (tipo == 1) {//arquivo de texto
        tipo_de_arquivamento = tipo;
    } else if (tipo == 2) {//arquivo binario
        tipo_de_arquivamento = tipo;
    } else {//caso a pessoa coloque uma opcao invalida vai para binario
        tipo_de_arquivamento = 2;
        return 0;
    }
    return 1;
}

struct tm *set_time() {

    struct tm *data_hora_atual;
    time_t segundos;

    time(&segundos);

    data_hora_atual = localtime(&segundos);

    return data_hora_atual;
};

//=====================================ARQUIVOS_CATEGORIA==========================================================

int salvar_arquivo_categoria(dados_categoria *p_categoria, int tam_categoria) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_categoria_texto(p_categoria, tam_categoria);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_categoria_binario(p_categoria, tam_categoria);
    }
}

int salvar_arquivo_categoria_binario(dados_categoria *p_categoria, int tam_categoria) {

    FILE *p_arquivo_categoria;
    p_arquivo_categoria = fopen("arquivos\\categoria.bin", "wb");
    int salvo;

    if (p_arquivo_categoria == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_categoria, sizeof (int), 1, p_arquivo_categoria);

    //salvando o array
    salvo = fwrite(p_categoria, sizeof (dados_categoria), tam_categoria, p_arquivo_categoria);

    fclose(p_arquivo_categoria);

    if (salvo == tam_categoria) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_categoria_texto(dados_categoria *p_categoria, int tam_categoria) {

    FILE *p_arquivo_categoria;
    p_arquivo_categoria = fopen("arquivos\\categoria_text.txt", "w");

    if (p_arquivo_categoria == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_categoria, "%d\n\n", tam_categoria);

    for (int i = 0; i < tam_categoria; i++) {
        fprintf(p_arquivo_categoria, "%d;", p_categoria[i].cod);
        fprintf(p_arquivo_categoria, "%s;", p_categoria[i].nome);
        fprintf(p_arquivo_categoria, "%s;", p_categoria[i].descricao);
        fprintf(p_arquivo_categoria, "%.2f;", p_categoria[i].valor_diaria);
        fprintf(p_arquivo_categoria, "%d;", p_categoria[i].hospede[0]); //Adultos
        fprintf(p_arquivo_categoria, "%d\n", p_categoria[i].hospede[1]); //Criancas
    }
    fclose(p_arquivo_categoria);

    return 1;
}

int tamanho_arquivo_categoria() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_categoria_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_categoria_binario();
    }
}

int tamanho_arquivo_categoria_binario() {

    FILE *p_arquivo_tam_categoria;
    p_arquivo_tam_categoria = fopen("arquivos\\categoria.bin", "a+b");
    int control, tam_categoria;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_categoria == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_categoria);

    //lendo o tamanho do array
    control = fread(&tam_categoria, sizeof (int), 1, p_arquivo_tam_categoria);

    fclose(p_arquivo_tam_categoria);

    if (control != 1) {
        return -1;
    }

    return tam_categoria;

}

int tamanho_arquivo_categoria_texto() {

    FILE *p_arquivo_categoria;
    p_arquivo_categoria = fopen("arquivos\\categoria_text.txt", "a+");
    int tam_categoria, control;

    if (p_arquivo_categoria == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_categoria);

    control = fscanf(p_arquivo_categoria, "%d", &tam_categoria);

    fclose(p_arquivo_categoria);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_categoria;

}

dados_categoria ler_arquivo_categoria(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_categoria_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_categoria_binario(i);
    }
}

dados_categoria ler_arquivo_categoria_binario(int i) {

    dados_categoria categoria;

    FILE *p_arquivo_categoria;
    p_arquivo_categoria = fopen("arquivos\\categoria.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_categoria == NULL) {
        categoria.cod = -1;
        return categoria;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_categoria);

    //ultrapassando o tam_categoria
    fseek(p_arquivo_categoria, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_categoria, (i) * sizeof (dados_categoria), SEEK_CUR);
    }
    //lendo o array
    fread(&categoria, sizeof (dados_categoria), 1, p_arquivo_categoria);

    fclose(p_arquivo_categoria);

    return categoria;
}

dados_categoria ler_arquivo_categoria_texto(int i) {

    dados_categoria categoria;

    FILE *p_arquivo_categoria;
    p_arquivo_categoria = fopen("arquivos\\categoria_text.txt", "a+");

    if (p_arquivo_categoria == NULL) {
        categoria.cod = -1;
        return categoria; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_categoria);

    //ultrapassando o tam_categoria
    fseek(p_arquivo_categoria, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_categoria, "%d", &categoria.cod);
        fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_categoria, "%[^;]s", categoria.nome);
        fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_categoria, "%[^;]s", categoria.descricao);
        fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_categoria, "%f", &categoria.valor_diaria);
        fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_categoria, "%d", &categoria.hospede[0]); //Adultos
        fseek(p_arquivo_categoria, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_categoria, "%d", &categoria.hospede[1]); //Criancas
        i--;
    }

    fclose(p_arquivo_categoria);

    return categoria;
}

//================================================ARQUIVOS_ACOMODACAO=============================================

int salvar_arquivo_acomodacao(dados_acomodacao *p_acomodacao, int tam_acomodacao) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_acomodacao_texto(p_acomodacao, tam_acomodacao);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_acomodacao_binario(p_acomodacao, tam_acomodacao);
    }
}

int salvar_arquivo_acomodacao_binario(dados_acomodacao *p_acomodacao, int tam_acomodacao) {

    FILE *p_arquivo_acomodacao;
    p_arquivo_acomodacao = fopen("arquivos\\acomodacao.bin", "wb");
    int salvo;

    if (p_arquivo_acomodacao == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_acomodacao, sizeof (int), 1, p_arquivo_acomodacao);

    //salvando o array
    salvo = fwrite(p_acomodacao, sizeof (dados_acomodacao), tam_acomodacao, p_arquivo_acomodacao);

    fclose(p_arquivo_acomodacao);

    if (salvo == tam_acomodacao) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_acomodacao_texto(dados_acomodacao *p_acomodacao, int tam_acomodacao) {

    FILE *p_arquivo_acomodacao;
    p_arquivo_acomodacao = fopen("arquivos\\acomodacao_text.txt", "w");

    if (p_arquivo_acomodacao == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_acomodacao, "%d\n\n", tam_acomodacao);

    for (int i = 0; i < tam_acomodacao; i++) {
        fprintf(p_arquivo_acomodacao, "%d;", p_acomodacao[i].cod);
        fprintf(p_arquivo_acomodacao, "%d;", p_acomodacao[i].num_quarto);
        fprintf(p_arquivo_acomodacao, "%s;", p_acomodacao[i].descricao);
        fprintf(p_arquivo_acomodacao, "%s;", p_acomodacao[i].facilidades);
        fprintf(p_arquivo_acomodacao, "%d\n", p_acomodacao[i].categoria);\
                                            }
    fclose(p_arquivo_acomodacao);

    return 1;
}

int tamanho_arquivo_acomodacao() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_acomodacao_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_acomodacao_binario();
    }
}

int tamanho_arquivo_acomodacao_binario() {

    FILE *p_arquivo_tam_acomodacao;
    p_arquivo_tam_acomodacao = fopen("arquivos\\acomodacao.bin", "a+b");
    int control, tam_acomodacao;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_acomodacao == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_acomodacao);

    //lendo o tamanho do array
    control = fread(&tam_acomodacao, sizeof (int), 1, p_arquivo_tam_acomodacao);

    fclose(p_arquivo_tam_acomodacao);

    if (control != 1) {
        return -1;
    }

    return tam_acomodacao;

}

int tamanho_arquivo_acomodacao_texto() {

    FILE *p_arquivo_acomodacao;
    p_arquivo_acomodacao = fopen("arquivos\\acomodacao_text.txt", "a+");
    int tam_acomodacao, control;

    if (p_arquivo_acomodacao == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_acomodacao);

    control = fscanf(p_arquivo_acomodacao, "%d", &tam_acomodacao);

    fclose(p_arquivo_acomodacao);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_acomodacao;

}

dados_acomodacao ler_arquivo_acomodacao(int i) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_acomodacao_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_acomodacao_binario(i);
    }
}

dados_acomodacao ler_arquivo_acomodacao_binario(int i) {

    dados_acomodacao acomodacao;

    FILE *p_arquivo_acomodacao;
    p_arquivo_acomodacao = fopen("arquivos\\acomodacao.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_acomodacao == NULL) {
        acomodacao.cod = -1;
        return acomodacao;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_acomodacao);

    //ultrapassando o tam_categoria
    fseek(p_arquivo_acomodacao, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_acomodacao, (i) * sizeof (dados_acomodacao), SEEK_CUR);
    }
    //lendo o array
    fread(&acomodacao, sizeof (dados_acomodacao), 1, p_arquivo_acomodacao);

    fclose(p_arquivo_acomodacao);

    return acomodacao;
}

dados_acomodacao ler_arquivo_acomodacao_texto(int i) {

    dados_acomodacao acomodacao;

    FILE *p_arquivo_acomodacao;
    p_arquivo_acomodacao = fopen("arquivos\\acomodacao_text.txt", "a+");

    if (p_arquivo_acomodacao == NULL) {
        acomodacao.cod = -1;
        return acomodacao; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_acomodacao);

    //ultrapassando o tam_acomodacao e o \n
    fseek(p_arquivo_acomodacao, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_acomodacao, 1 * sizeof (char), SEEK_SET);

    //lendo o arquivo na posicao desejada
    while (i + 1 > 0) {
        fscanf(p_arquivo_acomodacao, "%d", &acomodacao.cod);
        fseek(p_arquivo_acomodacao, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_acomodacao, "%d", &acomodacao.num_quarto);
        fseek(p_arquivo_acomodacao, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_acomodacao, "%[^;]s", acomodacao.descricao);
        fseek(p_arquivo_acomodacao, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_acomodacao, "%[^;]s", acomodacao.facilidades);
        fseek(p_arquivo_acomodacao, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_acomodacao, "%d", &acomodacao.categoria);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_acomodacao);

    return acomodacao;
}

//=========================================ARQUIVOS_RESERVA=======================================================

int salvar_arquivo_reserva(dados_reserva *p_reserva, int tam_reserva) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_reserva_texto(p_reserva, tam_reserva);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_reserva_binario(p_reserva, tam_reserva);
    }
}

int salvar_arquivo_reserva_binario(dados_reserva *p_reserva, int tam_reserva) {

    FILE *p_arquivo_reserva;
    p_arquivo_reserva = fopen("arquivos\\reserva.bin", "wb");
    int salvo;

    if (p_arquivo_reserva == NULL) {
        return -1; //saida de erro
    }

    //salvando o tamanho do array
    fwrite(&tam_reserva, sizeof (int), 1, p_arquivo_reserva);

    //salvando o array
    salvo = fwrite(p_reserva, sizeof (dados_reserva), tam_reserva, p_arquivo_reserva);

    fclose(p_arquivo_reserva);

    if (salvo == tam_reserva) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_reserva_texto(dados_reserva *p_reserva, int tam_reserva) {

    FILE *p_arquivo_reserva;
    p_arquivo_reserva = fopen("arquivos\\reserva_text.txt", "w");

    if (p_arquivo_reserva == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_reserva, "%d\n\n", tam_reserva);

    for (int i = 0; i < tam_reserva; i++) {
        fprintf(p_arquivo_reserva, "%d;", p_reserva[i].cod);
        fprintf(p_arquivo_reserva, "%d;", p_reserva[i].cod_cliente);
        //lacos para grava a data no arquivo (pois a data é em formato de vetor)
        for (int j = 0; j < 3; j++) {
            fprintf(p_arquivo_reserva, "%d", p_reserva[i].dia_chegada[j]);
            if (j != 2) {
                fprintf(p_arquivo_reserva, "/");
            } else {
                fprintf(p_arquivo_reserva, ";");
            }
        }
        for (int j = 0; j < 3; j++) {
            fprintf(p_arquivo_reserva, "%d", p_reserva[i].dia_saida[j]);
            if (j != 2) {
                fprintf(p_arquivo_reserva, "/");
            } else {
                fprintf(p_arquivo_reserva, ";");
            }
        }
        fprintf(p_arquivo_reserva, "%d;", p_reserva[i].acomodacao);
    }
    fclose(p_arquivo_reserva);

    return 1;
}

int tamanho_arquivo_reserva() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_reserva_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_reserva_binario();
    }
}

int tamanho_arquivo_reserva_binario() {

    FILE *p_arquivo_tam_reserva;
    p_arquivo_tam_reserva = fopen("arquivos\\reserva.bin", "a+b");
    int control, tam_reserva;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_reserva == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_reserva);

    //lendo o tamanho do array
    control = fread(&tam_reserva, sizeof (int), 1, p_arquivo_tam_reserva);

    fclose(p_arquivo_tam_reserva);

    if (control != 1) {
        return -1;
    }

    return tam_reserva;

}

int tamanho_arquivo_reserva_texto() {

    FILE *p_arquivo_reserva;
    p_arquivo_reserva = fopen("arquivos\\reserva_text.txt", "a+");
    int tam_reserva, control;

    if (p_arquivo_reserva == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_reserva);

    control = fscanf(p_arquivo_reserva, "%d", &tam_reserva);

    fclose(p_arquivo_reserva);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_reserva;

}

dados_reserva ler_arquivo_reserva(int i) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_reserva_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_reserva_binario(i);
    }
}

dados_reserva ler_arquivo_reserva_binario(int i) {

    dados_reserva reserva;

    FILE *p_arquivo_reserva;
    p_arquivo_reserva = fopen("arquivos\\acomodacao.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_reserva == NULL) {
        reserva.cod = -1;
        return reserva; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_reserva);

    //ultrapassando o tam_categoria
    fseek(p_arquivo_reserva, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_reserva, (i) * sizeof (dados_reserva), SEEK_CUR);
    }
    //lendo o array
    fread(&reserva, sizeof (dados_reserva), 1, p_arquivo_reserva);

    fclose(p_arquivo_reserva);

    return reserva;
}

dados_reserva ler_arquivo_reserva_texto(int i) {

    dados_reserva reserva;

    FILE *p_arquivo_reserva;
    p_arquivo_reserva = fopen("arquivos\\reserva_text.txt", "a+");

    if (p_arquivo_reserva == NULL) {
        reserva.cod = -1;
        return reserva; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_reserva);

    //ultrapassando o tam_reserva e o \n
    fseek(p_arquivo_reserva, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_SET);

    //lendo o arquivo na posicao desejada
    while (i + 1 > 0) {
        fscanf(p_arquivo_reserva, "%d", &reserva.cod);
        fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_reserva, "%d", &reserva.cod_cliente);
        fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        for (int j; j < 3; j++) {
            fscanf(p_arquivo_reserva, "%d", &reserva.dia_chegada[j]);
            fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        }
        fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        for (int j; j < 3; j++) {
            fscanf(p_arquivo_reserva, "%d", &reserva.dia_saida[j]);
            fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        }
        fseek(p_arquivo_reserva, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_reserva, "%d", &reserva.acomodacao);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_reserva);

    return reserva;
}

//=========================================ARQUIVOS_PRODUTO======================================================
int salvar_arquivo_produto(dados_produto *p_produto, int tam_produto) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_produto_texto(p_produto, tam_produto);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_produto_binario(p_produto, tam_produto);
    }
}

int salvar_arquivo_produto_binario(dados_produto *p_produto, int tam_produto) {

    FILE *p_arquivo_produto;
    p_arquivo_produto = fopen("arquivos\\produto.bin", "wb");
    int salvo;

    if (p_arquivo_produto == NULL) {
        return -1; //saida de erro
    }

    //salvando o tamanho do array
    fwrite(&tam_produto, sizeof (int), 1, p_arquivo_produto);

    //salvando o array
    salvo = fwrite(p_produto, sizeof (dados_produto), tam_produto, p_arquivo_produto);

    fclose(p_arquivo_produto);

    if (salvo == tam_produto) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_produto_texto(dados_produto *p_produto, int tam_produto) {

    FILE *p_arquivo_produto;
    p_arquivo_produto = fopen("arquivos\\produto_text.txt", "w");

    if (p_arquivo_produto == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_produto, "%d\n\n", tam_produto);

    for (int i = 0; i < tam_produto; i++) {
        fprintf(p_arquivo_produto, "%d;", p_produto[i].cod);
        fprintf(p_arquivo_produto, "%s;", p_produto[i].descricao);
        fprintf(p_arquivo_produto, "%d;", p_produto[i].estoque);
        fprintf(p_arquivo_produto, "%d;", p_produto[i].estoque_min);
        fprintf(p_arquivo_produto, "%.2f;", p_produto[i].preco_custo);
        fprintf(p_arquivo_produto, "%.2f;", p_produto[i].preco_venda);\
    fprintf(p_arquivo_produto, "%s\n", p_produto[i].fornecedor);
    }
    fclose(p_arquivo_produto);

    return 1;
}

int tamanho_arquivo_produto() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_produto_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_produto_binario();
    }
}

int tamanho_arquivo_produto_binario() {

    FILE *p_arquivo_tam_produto;
    p_arquivo_tam_produto = fopen("arquivos\\produto.bin", "a+b");
    int control, tam_produto;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_produto == NULL) {
        return -2;
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_produto);

    //lendo o tamanho do array
    control = fread(&tam_produto, sizeof (int), 1, p_arquivo_tam_produto);

    fclose(p_arquivo_tam_produto);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_produto;
}

int tamanho_arquivo_produto_texto() {

    FILE *p_arquivo_produto;
    p_arquivo_produto = fopen("arquivos\\produto_text.txt", "a+");
    int tam_produto, control;

    if (p_arquivo_produto == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_produto);

    control = fscanf(p_arquivo_produto, "%d", &tam_produto);

    if (control != 1) {
        return -1;
    }

    fclose(p_arquivo_produto);

    return tam_produto;
}

dados_produto ler_arquivo_produto(int i) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_produto_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_produto_binario(i);
    }
}

dados_produto ler_arquivo_produto_binario(int i) {

    dados_produto produto;

    FILE *p_arquivo_produto;
    p_arquivo_produto = fopen("arquivos\\produto.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_produto == NULL) {
        produto.cod = -1;
        return produto; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_produto);

    //ultrapassando o tam_produto
    fseek(p_arquivo_produto, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_produto, (i) * sizeof (dados_produto), SEEK_CUR);
    }
    //lendo o array
    fread(&produto, sizeof (dados_produto), 1, p_arquivo_produto);

    fclose(p_arquivo_produto);

    return produto;
}

dados_produto ler_arquivo_produto_texto(int i) {

    dados_produto produto;

    FILE *p_arquivo_produto;
    p_arquivo_produto = fopen("arquivos\\produto_text.txt", "a+");

    if (p_arquivo_produto == NULL) {
        produto.cod = -1;
        return produto; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_produto);

    //ultrapassando o tam_produto e o \n
    fseek(p_arquivo_produto, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_SET);

    //lendo o arquivo na posicao desejada
    while (i + 1 > 0) {
        fscanf(p_arquivo_produto, "%d", &produto.cod);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%[^;]s", produto.descricao);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%d", &produto.estoque);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%d", &produto.estoque_min);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%f", &produto.preco_custo);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%f", &produto.preco_venda);
        fseek(p_arquivo_produto, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_produto, "%[^; \n]s", produto.fornecedor);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_produto);

    return produto;
}

//===========================================ARQUIVOS_FORNECEDOR==================================================
int salvar_arquivo_fornecedor(dados_fornecedor *p_fornecedor, int tam_fornecedor) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_fornecedor_texto(p_fornecedor, tam_fornecedor);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_fornecedor_binario(p_fornecedor, tam_fornecedor);
    }
}

int salvar_arquivo_fornecedor_binario(dados_fornecedor *p_fornecedor, int tam_fornecedor) {

    FILE *p_arquivo_fornecedor;
    p_arquivo_fornecedor = fopen("arquivos\\fornecedor.bin", "wb");
    int salvo;

    if (p_arquivo_fornecedor == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_fornecedor, sizeof (int), 1, p_arquivo_fornecedor);

    //salvando o array
    salvo = fwrite(p_fornecedor, sizeof (dados_fornecedor), tam_fornecedor, p_arquivo_fornecedor);

    fclose(p_arquivo_fornecedor);

    if (salvo == tam_fornecedor) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_fornecedor_texto(dados_fornecedor *p_fornecedor, int tam_fornecedor) {

    FILE *p_arquivo_fornecedor;
    p_arquivo_fornecedor = fopen("arquivos\\fornecedor_text.txt", "w");

    if (p_arquivo_fornecedor == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_fornecedor, "%d\n\n", tam_fornecedor);

    for (int i = 0; i < tam_fornecedor; i++) {
        fprintf(p_arquivo_fornecedor, "%d;", p_fornecedor[i].cod);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].nome_fantasia);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].razao_social);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].incricao_est);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].cnpj);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].endereco);
        fprintf(p_arquivo_fornecedor, "%s;", p_fornecedor[i].telefone);
        fprintf(p_arquivo_fornecedor, "%s\n", p_fornecedor[i].email);
    }
    fclose(p_arquivo_fornecedor);

    return 1;
}

int tamanho_arquivo_fornecedor() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_fornecedor_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_fornecedor_binario();
    }
}

int tamanho_arquivo_fornecedor_binario() {

    FILE *p_arquivo_tam_fornecedor;
    p_arquivo_tam_fornecedor = fopen("arquivos\\fornecedor.bin", "a+b");
    int control, tam_fornecedor;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_fornecedor == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_fornecedor);

    //lendo o tamanho do array
    control = fread(&tam_fornecedor, sizeof (int), 1, p_arquivo_tam_fornecedor);

    fclose(p_arquivo_tam_fornecedor);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_fornecedor;
}

int tamanho_arquivo_fornecedor_texto() {

    FILE *p_arquivo_fornecedor;
    p_arquivo_fornecedor = fopen("arquivos\\fornecedor_text.txt", "a+");
    int tam_fornecedor, control;

    if (p_arquivo_fornecedor == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_fornecedor);

    control = fscanf(p_arquivo_fornecedor, "%d", &tam_fornecedor);

    fclose(p_arquivo_fornecedor);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_fornecedor;

}

dados_fornecedor ler_arquivo_fornecedor(int i) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_fornecedor_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_fornecedor_binario(i);
    }
}

dados_fornecedor ler_arquivo_fornecedor_binario(int i) {

    dados_fornecedor fornecedor;

    FILE *p_arquivo_fornecedor;
    p_arquivo_fornecedor = fopen("arquivos\\fornecedor.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_fornecedor == NULL) {
        fornecedor.cod = -1;
        return fornecedor;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_fornecedor);

    //ultrapassando o tam_fornecedor
    fseek(p_arquivo_fornecedor, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_fornecedor, (i) * sizeof (dados_fornecedor), SEEK_CUR);
    }
    //lendo o array
    fread(&fornecedor, sizeof (dados_fornecedor), 1, p_arquivo_fornecedor);

    fclose(p_arquivo_fornecedor);

    return fornecedor;
}

dados_fornecedor ler_arquivo_fornecedor_texto(int i) {

    dados_fornecedor fornecedor;

    FILE *p_arquivo_fornecedor;
    p_arquivo_fornecedor = fopen("arquivos\\fornecedor_text.txt", "a+");

    if (p_arquivo_fornecedor == NULL) {
        fornecedor.cod = -1;
        return fornecedor; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_fornecedor);

    //ultrapassando o tam_fornecedor e o \n
    fseek(p_arquivo_fornecedor, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_fornecedor, "%d", &fornecedor.cod);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.nome_fantasia);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.razao_social);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.incricao_est);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.cnpj);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.endereco);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^;]s", fornecedor.telefone);
        fseek(p_arquivo_fornecedor, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_fornecedor, "%[^\n]s", fornecedor.email);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_fornecedor);

    return fornecedor;
}

//===========================================ARQUIVOS_CHECK-IN===================================================
int salvar_arquivo_checkin(dados_checkin *p_checkin, int tam_checkin) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_checkin_texto(p_checkin, tam_checkin);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_checkin_binario(p_checkin, tam_checkin);
    }
}

int salvar_arquivo_checkin_binario(dados_checkin *p_checkin, int tam_checkin) {

    FILE *p_arquivo_checkin;
    p_arquivo_checkin = fopen("arquivos\\checkin.bin", "wb");
    int salvo;

    if (p_arquivo_checkin == NULL) {
        return -1; //saida de erro
    }

    //salvando o tamanho do array
    fwrite(&tam_checkin, sizeof (int), 1, p_arquivo_checkin);

    //salvando o array
    salvo = fwrite(p_checkin, sizeof (dados_checkin), tam_checkin, p_arquivo_checkin);

    fclose(p_arquivo_checkin);

    if (salvo == tam_checkin) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_checkin_texto(dados_checkin *p_checkin, int tam_checkin) {

    FILE *p_arquivo_checkin;
    p_arquivo_checkin = fopen("arquivos\\checkin_text.txt", "w");

    if (p_arquivo_checkin == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_checkin, "%d\n\n", tam_checkin);

    for (int i = 0; i < tam_checkin; i++) {
        fprintf(p_arquivo_checkin, "%d;", p_checkin[i].cod);
        fprintf(p_arquivo_checkin, "%d;", p_checkin[i].cod_hospede);
        fprintf(p_arquivo_checkin, "%d;", p_checkin[i].cod_reserva);
        fprintf(p_arquivo_checkin, "%d:", p_checkin[i].hora[0]);
        fprintf(p_arquivo_checkin, "%d;", p_checkin[i].hora[1]);
        fprintf(p_arquivo_checkin, "%d;", p_checkin[i].opcao_pagamento);
        fprintf(p_arquivo_checkin, "%.2f;", p_checkin[i].opcao_pagamento);
        fprintf(p_arquivo_checkin, "%d\n", p_checkin[i].diarias);
    }
    fclose(p_arquivo_checkin);

    return 1;
}

int tamanho_arquivo_checkin() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_checkin_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_checkin_binario();
    }
}

int tamanho_arquivo_checkin_binario() {

    FILE *p_arquivo_tam_checkin;
    p_arquivo_tam_checkin = fopen("arquivos\\checkin.bin", "a+b");
    int control, tam_checkin;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_checkin == NULL) {
        return -2;
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_checkin);

    //lendo o tamanho do array
    control = fread(&tam_checkin, sizeof (int), 1, p_arquivo_tam_checkin);

    fclose(p_arquivo_tam_checkin);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_checkin;
}

int tamanho_arquivo_checkin_texto() {

    FILE *p_arquivo_checkin;
    p_arquivo_checkin = fopen("arquivos\\checkin_text.txt", "a+");
    int tam_checkin, control;

    if (p_arquivo_checkin == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkin);

    control = fscanf(p_arquivo_checkin, "%d", &tam_checkin);

    if (control != 1) {
        return -1;
    }

    fclose(p_arquivo_checkin);

    return tam_checkin;
}

dados_checkin ler_arquivo_checkin(int i) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_checkin_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_checkin_binario(i);
    }
}

dados_checkin ler_arquivo_checkin_binario(int i) {

    dados_checkin checkin;

    FILE *p_arquivo_checkin;
    p_arquivo_checkin = fopen("arquivos\\checkin.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_checkin == NULL) {
        checkin.cod = -1;
        return checkin; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkin);

    //ultrapassando o tam_produto
    fseek(p_arquivo_checkin, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_checkin, (i) * sizeof (dados_checkin), SEEK_CUR);
    }
    //lendo o array
    fread(&checkin, sizeof (dados_checkin), 1, p_arquivo_checkin);

    fclose(p_arquivo_checkin);

    return checkin;
}

dados_checkin ler_arquivo_checkin_texto(int i) {

    dados_checkin checkin;

    FILE *p_arquivo_checkin;
    p_arquivo_checkin = fopen("arquivos\\checkin_text.txt", "a+");

    if (p_arquivo_checkin == NULL) {
        checkin.cod = -1;
        return checkin; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkin);

    //ultrapassando o tam_produto e o \n
    fseek(p_arquivo_checkin, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_SET);

    //lendo o arquivo na posicao desejada
    while (i + 1 > 0) {
        fscanf(p_arquivo_checkin, "%d", &checkin.cod);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.cod_hospede);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.cod_reserva);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.hora[0]);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.hora[1]);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.opcao_pagamento);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%f", &checkin.valor);
        fseek(p_arquivo_checkin, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkin, "%d", &checkin.diarias);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_checkin);

    return checkin;
}

//============================================ARQUIVOS_CHECK-OUT===================================================

int salvar_arquivo_checkout(dados_checkout *p_checkout, int tam_checkout) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_checkout_texto(p_checkout, tam_checkout);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_checkout_binario(p_checkout, tam_checkout);
    }
}

int salvar_arquivo_checkout_binario(dados_checkout *p_checkout, int tam_checkout) {

    FILE *p_arquivo_checkout;
    p_arquivo_checkout = fopen("arquivos\\checkout.bin", "wb");
    int salvo;

    if (p_arquivo_checkout == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_checkout, sizeof (int), 1, p_arquivo_checkout);

    //salvando o array
    salvo = fwrite(p_checkout, sizeof (dados_checkout), tam_checkout, p_arquivo_checkout);

    fclose(p_arquivo_checkout);

    if (salvo == tam_checkout) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_checkout_texto(dados_checkout *p_checkout, int tam_checkout) {

    FILE *p_arquivo_checkout;
    p_arquivo_checkout = fopen("arquivos\\checkout_text.txt", "w");

    if (p_arquivo_checkout == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_checkout, "%d\n\n", tam_checkout);

    for (int i = 0; i < tam_checkout; i++) {
        fprintf(p_arquivo_checkout, "%d;", p_checkout[i].cod);
        fprintf(p_arquivo_checkout, "%d;", p_checkout[i].cod_hospede);
        fprintf(p_arquivo_checkout, "%d;", p_checkout[i].cod_reserva);
        fprintf(p_arquivo_checkout, "%d:", p_checkout[i].hora[0]);
        fprintf(p_arquivo_checkout, "%d;", p_checkout[i].hora[1]);
        fprintf(p_arquivo_checkout, "%d;", p_checkout[i].opcao_pagamento);
        fprintf(p_arquivo_checkout, "%.2f;", p_checkout[i].valor);
        fprintf(p_arquivo_checkout, "%d\n", p_checkout[i].diarias);
    }
    fclose(p_arquivo_checkout);

    return 1;
}

int tamanho_arquivo_checkout() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_checkout_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_checkout_binario();
    }
}

int tamanho_arquivo_checkout_binario() {

    FILE *p_arquivo_tam_checkout;
    p_arquivo_tam_checkout = fopen("arquivos\\checkout.bin", "a+b");
    int control, tam_checkout;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_checkout == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_checkout);

    //lendo o tamanho do array
    control = fread(&tam_checkout, sizeof (int), 1, p_arquivo_tam_checkout);

    fclose(p_arquivo_tam_checkout);

    if (control != 1) {
        return -1;
    }

    return tam_checkout;

}

int tamanho_arquivo_checkout_texto() {

    FILE *p_arquivo_checkout;
    p_arquivo_checkout = fopen("arquivos\\checkout_text.txt", "a+");
    int tam_checkout, control;

    if (p_arquivo_checkout == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkout);

    control = fscanf(p_arquivo_checkout, "%d", &tam_checkout);

    fclose(p_arquivo_checkout);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_checkout;

}

dados_checkout ler_arquivo_checkout(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_checkout_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_checkout_binario(i);
    }
}

dados_checkout ler_arquivo_checkout_binario(int i) {

    dados_checkout checkout;

    FILE *p_arquivo_checkout;
    p_arquivo_checkout = fopen("arquivos\\checkout.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_checkout == NULL) {
        checkout.cod = -1;
        return checkout;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkout);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_checkout, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_checkout, (i) * sizeof (dados_checkout), SEEK_CUR);
    }
    //lendo o array
    fread(&checkout, sizeof (dados_checkout), 1, p_arquivo_checkout);

    fclose(p_arquivo_checkout);

    return checkout;
}

dados_checkout ler_arquivo_checkout_texto(int i) {

    dados_checkout checkout;

    FILE *p_arquivo_checkout;
    p_arquivo_checkout = fopen("arquivos\\checkout_text.txt", "a+");

    if (p_arquivo_checkout == NULL) {
        checkout.cod = -1;
        return checkout; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_checkout);

    //ultrapassando o tam_checkout
    fseek(p_arquivo_checkout, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_checkout, "%d", &checkout.cod);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.cod_hospede);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.cod_reserva);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.hora[0]);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.hora[1]);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.opcao_pagamento);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%f", &checkout.valor);
        fseek(p_arquivo_checkout, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_checkout, "%d", &checkout.diarias);
        i--; //variavel para ir lendo ate a posicao desejada
    }

    fclose(p_arquivo_checkout);

    return checkout;
}

//=========================================ARQUIVOS_OPERADOR======================================================

int salvar_arquivo_operador(dados_operador *p_operador, int tam_operador) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_operador_texto(p_operador, tam_operador);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_operador_binario(p_operador, tam_operador);
    }
}

int salvar_arquivo_operador_binario(dados_operador *p_operador, int tam_operador) {

    FILE *p_arquivo_operador;
    p_arquivo_operador = fopen("arquivos\\operador.bin", "wb");
    int salvo;

    if (p_arquivo_operador == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_operador, sizeof (int), 1, p_arquivo_operador);

    //salvando o array
    salvo = fwrite(p_operador, sizeof (dados_operador), tam_operador, p_arquivo_operador);

    fclose(p_arquivo_operador);

    if (salvo == tam_operador) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_operador_texto(dados_operador *p_operador, int tam_operador) {

    FILE *p_arquivo_operador;
    p_arquivo_operador = fopen("arquivos\\operador_text.txt", "w");

    if (p_arquivo_operador == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_operador, "%d\n\n", tam_operador);

    for (int i = 0; i < tam_operador; i++) {
        fprintf(p_arquivo_operador, "%d;", p_operador[i].cod);
        fprintf(p_arquivo_operador, "%s;", p_operador[i].nome);
        fprintf(p_arquivo_operador, "%s;", p_operador[i].usuario);
        fprintf(p_arquivo_operador, "%s;", p_operador[i].senha);
        fprintf(p_arquivo_operador, "%s\n", p_operador[i].categoria);
    }
    fclose(p_arquivo_operador);

    return 1;
}

int tamanho_arquivo_operador() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_operador_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_operador_binario();
    }
}

int tamanho_arquivo_operador_binario() {

    FILE *p_arquivo_tam_operador;
    p_arquivo_tam_operador = fopen("arquivos\\operador.bin", "a+b");
    int control, tam_operador;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_operador == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_operador);

    //lendo o tamanho do array
    control = fread(&tam_operador, sizeof (int), 1, p_arquivo_tam_operador);

    fclose(p_arquivo_tam_operador);

    if (control != 1) {
        return -1;
    }

    return tam_operador;
}

int tamanho_arquivo_operador_texto() {

    FILE *p_arquivo_operador;
    p_arquivo_operador = fopen("arquivos\\operador_text.txt", "a+");
    int tam_operador, control;

    if (p_arquivo_operador == NULL) {
        return -1; //saida de erro da abertura do arquivo
                                        }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_operador);

    control = fscanf(p_arquivo_operador, "%d", &tam_operador);

    fclose(p_arquivo_operador);

    if (control != 1) {
        return -2; //caso ele n tenha lido nenhum dado
                        }

    return tam_operador;
}

dados_operador ler_arquivo_operador(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_operador_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_operador_binario(i);
    }
}

dados_operador ler_arquivo_operador_binario(int i) {

    dados_operador operador;

    FILE *p_arquivo_operador;
    p_arquivo_operador = fopen("arquivos\\operador.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_operador == NULL) {
        operador.cod = -1;
        return operador;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_operador);

    //ultrapassando o tam_operador
    fseek(p_arquivo_operador, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_operador, (i) * sizeof (dados_operador), SEEK_CUR);
    }
    //lendo o array
    fread(&operador, sizeof (dados_operador), 1, p_arquivo_operador);

    fclose(p_arquivo_operador);

    return operador;
}

dados_operador ler_arquivo_operador_texto(int i) {

    dados_operador operador;

    FILE *p_arquivo_operador;
    p_arquivo_operador = fopen("arquivos\\operador_text.txt", "a+");

    if (p_arquivo_operador == NULL) {
        operador.cod = -1;
        return operador; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_operador);

    //ultrapassando o tam_operador
    fseek(p_arquivo_operador, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_operador, "%d", &operador.cod);
        fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_operador, "%[^;]s", operador.nome);
        fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_operador, "%[^;]s", operador.usuario);
        fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_operador, "%[^;]s", operador.senha);
        fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_operador, "%[^;]s", operador.categoria);
        fseek(p_arquivo_operador, 1 * sizeof (char), SEEK_CUR);
        i--;
    }

    fclose(p_arquivo_operador);

    return operador;
}

//=============================================ARQUIVOS_HOSPEDE==================================================

int salvar_arquivo_hospede(dados_hospede *p_hospede, int tam_hospede) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_hospede_texto(p_hospede, tam_hospede);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_hospede_binario(p_hospede, tam_hospede);
    }
}

int salvar_arquivo_hospede_binario(dados_hospede *p_hospede, int tam_hospede) {

    FILE *p_arquivo_hospede;
    p_arquivo_hospede = fopen("arquivos\\hospede.bin", "wb");
    int salvo;

    if (p_arquivo_hospede == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_hospede, sizeof (int), 1, p_arquivo_hospede);

    //salvando o array
    salvo = fwrite(p_hospede, sizeof (dados_hospede), tam_hospede, p_arquivo_hospede);

    fclose(p_arquivo_hospede);

    if (salvo == tam_hospede) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_hospede_texto(dados_hospede *p_hospede, int tam_hospede) {

    FILE *p_arquivo_hospede;
    p_arquivo_hospede = fopen("arquivos\\hospede_text.txt", "w");

    if (p_arquivo_hospede == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_hospede, "%d\n\n", tam_hospede);

    for (int i = 0; i < tam_hospede; i++) {
        fprintf(p_arquivo_hospede, "%d;", p_hospede[i].cod);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].nome);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].endereco_completo);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].cpf);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].telefone_hospede);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].email_hospede);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].sexo);
        fprintf(p_arquivo_hospede, "%s;", p_hospede[i].estado_civil);
        fprintf(p_arquivo_hospede, "%s\n", p_hospede[i].data_nascimento);
    }
    fclose(p_arquivo_hospede);

    return 1;
}

int tamanho_arquivo_hospede() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_hospede_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_hospede_binario();
    }
}

int tamanho_arquivo_hospede_binario() {

    FILE *p_arquivo_tam_hospede;
    p_arquivo_tam_hospede = fopen("arquivos\\hospede.bin", "a+b");
    int control, tam_hospede;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_hospede == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_hospede);

    //lendo o tamanho do array
    control = fread(&tam_hospede, sizeof (int), 1, p_arquivo_tam_hospede);

    fclose(p_arquivo_tam_hospede);

    if (control != 1) {
        return -1;
    }

    return tam_hospede;

}

int tamanho_arquivo_hospede_texto() {

    FILE *p_arquivo_hospede;
    p_arquivo_hospede = fopen("arquivos\\hospede_text.txt", "a+");
    int tam_hospede, control;

    if (p_arquivo_hospede == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hospede);

    control = fscanf(p_arquivo_hospede, "%d", &tam_hospede);

    fclose(p_arquivo_hospede);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_hospede;

}

dados_hospede ler_arquivo_hospede(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_hospede_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_hospede_binario(i);
    }
}

dados_hospede ler_arquivo_hospede_binario(int i) {

    dados_hospede hospede;

    FILE *p_arquivo_hospede;
    p_arquivo_hospede = fopen("arquivos\\hospede.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_hospede == NULL) {
        hospede.cod = -1;
        return hospede;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hospede);

    //ultrapassando o tam_hospede
    fseek(p_arquivo_hospede, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_hospede, (i) * sizeof (dados_hospede), SEEK_CUR);
    }
    //lendo o array
    fread(&hospede, sizeof (dados_hospede), 1, p_arquivo_hospede);

    fclose(p_arquivo_hospede);

    return hospede;
}

dados_hospede ler_arquivo_hospede_texto(int i) {

    dados_hospede hospede;

    FILE *p_arquivo_hospede;
    p_arquivo_hospede = fopen("arquivos\\hospede_text.txt", "a+");

    if (p_arquivo_hospede == NULL) {
        hospede.cod = -1;
        return hospede; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hospede);

    //ultrapassando o tam_hospede
    fseek(p_arquivo_hospede, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_hospede, "%d", &hospede.cod);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.nome);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.endereco_completo);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.cpf);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.telefone_hospede);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.email_hospede);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.sexo);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^;]s", hospede.estado_civil);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hospede, "%[^\n]s", hospede.data_nascimento);
        fseek(p_arquivo_hospede, 1 * sizeof (char), SEEK_CUR);
        i--;
    }

    fclose(p_arquivo_hospede);

    return hospede;
}

//============================================ARQUIVOS_HOTEL======================================================
int salvar_arquivo_hotel(dados_hotel *p_hotel, int tam_hotel) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_hotel_texto(p_hotel, tam_hotel);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_hotel_binario(p_hotel, tam_hotel);
    }
}

int salvar_arquivo_hotel_binario(dados_hotel *p_hotel, int tam_hotel) {

    FILE *p_arquivo_hotel;
    p_arquivo_hotel = fopen("arquivos\\hotel.bin", "wb");
    int salvo;

    if (p_arquivo_hotel == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_hotel, sizeof (int), 1, p_arquivo_hotel);

    //salvando o array
    salvo = fwrite(p_hotel, sizeof (dados_hotel), tam_hotel, p_arquivo_hotel);

    fclose(p_arquivo_hotel);

    if (salvo == tam_hotel) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_hotel_texto(dados_hotel *p_hotel, int tam_hotel) {

    FILE *p_arquivo_hotel;
    p_arquivo_hotel = fopen("arquivos\\hotel_text.txt", "w");

    if (p_arquivo_hotel == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_hotel, "%d\n\n", tam_hotel);

    for (int i = 0; i < tam_hotel; i++) {
        fprintf(p_arquivo_hotel, "%d;", p_hotel[i].cod);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].nome_fantasia);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].inscricao_estadual);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].cnpj);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].endereco_completo);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].telefone_hotel);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].email_hotel);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].nome_responsavel);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].telefone_responsavel);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].check_in);
        fprintf(p_arquivo_hotel, "%s;", p_hotel[i].check_out);
        fprintf(p_arquivo_hotel, "%s\n", p_hotel[i].margem_lucro);
    }
    fclose(p_arquivo_hotel);

    return 1;
}

int tamanho_arquivo_hotel() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_hotel_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_hotel_binario();
    }
}

int tamanho_arquivo_hotel_binario() {

    FILE *p_arquivo_tam_hotel;
    p_arquivo_tam_hotel = fopen("arquivos\\hotel.bin", "a+b");
    int control, tam_hotel;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_hotel == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_hotel);

    //lendo o tamanho do array
    control = fread(&tam_hotel, sizeof (int), 1, p_arquivo_tam_hotel);

    fclose(p_arquivo_tam_hotel);

    if (control != 1) {
        return -1;
    }

    return tam_hotel;

}

int tamanho_arquivo_hotel_texto() {

    FILE *p_arquivo_hotel;
    p_arquivo_hotel = fopen("arquivos\\hotel_text.txt", "a+");
    int tam_hotel, control;

    if (p_arquivo_hotel == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hotel);

    control = fscanf(p_arquivo_hotel, "%d", &tam_hotel);

    fclose(p_arquivo_hotel);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_hotel;

}

dados_hotel ler_arquivo_hotel(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_hotel_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_hotel_binario(i);
    }
}

dados_hotel ler_arquivo_hotel_binario(int i) {

    dados_hotel hotel;

    FILE *p_arquivo_hotel;
    p_arquivo_hotel = fopen("arquivos\\hotel.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_hotel == NULL) {
        hotel.cod = -1;
        return hotel;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hotel);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_hotel, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_hotel, (i) * sizeof (dados_hotel), SEEK_CUR);
    }
    //lendo o array
    fread(&hotel, sizeof (dados_hotel), 1, p_arquivo_hotel);

    fclose(p_arquivo_hotel);

    return hotel;
}

dados_hotel ler_arquivo_hotel_texto(int i) {

    dados_hotel hotel;

    FILE *p_arquivo_hotel;
    p_arquivo_hotel = fopen("arquivos\\hotel_text.txt", "a+");

    if (p_arquivo_hotel == NULL) {
        hotel.cod = -1;
        return hotel; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_hotel);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_hotel, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_hotel, "%d", &hotel.cod);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.nome_fantasia);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.inscricao_estadual);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.cnpj);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.endereco_completo);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.telefone_hotel);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.email_hotel);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.nome_responsavel);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.telefone_responsavel);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.check_in);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^;]s", hotel.check_out);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_hotel, "%[^\n]s", hotel.margem_lucro);
        fseek(p_arquivo_hotel, 1 * sizeof (char), SEEK_CUR);
        i--;
    }

    fclose(p_arquivo_hotel);

    return hotel;
}

//============================================ARQUIVOS_SAIDA_PRODUTOS======================================================
int salvar_arquivo_saida_produtos(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_saida_produtos_texto(p_saida_produtos, tam_saida_produtos);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_saida_produtos_binario(p_saida_produtos, tam_saida_produtos);
    }
}

int salvar_arquivo_saida_produtos_binario(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos) {

    FILE *p_arquivo_saida_produtos;
    p_arquivo_saida_produtos = fopen("arquivos\\saida_produtos.bin", "wb");
    int salvo;

    if (p_arquivo_saida_produtos == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_saida_produtos, sizeof (int), 1, p_arquivo_saida_produtos);

    //salvando o array
    salvo = fwrite(p_saida_produtos, sizeof (dados_saida_produtos), tam_saida_produtos, p_arquivo_saida_produtos);

    fclose(p_arquivo_saida_produtos);

    if (salvo == tam_saida_produtos) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_saida_produtos_texto(dados_saida_produtos *p_saida_produtos, int tam_saida_produtos) {

    FILE *p_arquivo_saida_produtos;
    p_arquivo_saida_produtos = fopen("arquivos\\saida_produtos_text.txt", "w");

    if (p_arquivo_saida_produtos == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_saida_produtos, "%d\n\n", tam_saida_produtos);

    for (int i = 0; i < tam_saida_produtos; i++) {
        fprintf(p_arquivo_saida_produtos, "%d;", p_saida_produtos[i].cod);
        fprintf(p_arquivo_saida_produtos, "%d;", p_saida_produtos[i].status);
        fprintf(p_arquivo_saida_produtos, "%s;", p_saida_produtos[i].CPF);
        fprintf(p_arquivo_saida_produtos, "%d;", p_saida_produtos[i].forma_pagamento);
        fprintf(p_arquivo_saida_produtos, "%.2f;", p_saida_produtos[i].total);
        fprintf(p_arquivo_saida_produtos, "%d\n", p_saida_produtos[i].tam_conta);
        for(int j=0; j<p_saida_produtos[i].tam_conta; j++){
            fprintf(p_arquivo_saida_produtos, "%d;", p_saida_produtos[i].p_conta[j].cod_produto);
            fprintf(p_arquivo_saida_produtos, "%d", p_saida_produtos[i].p_conta[j].quantidade);
            
            if(j!=(p_saida_produtos[i].tam_conta)-1){
                fprintf(p_arquivo_saida_produtos, ";");
                                                    }
                                                            }
        fprintf(p_arquivo_saida_produtos, "\n\n");
                                                    }
    fclose(p_arquivo_saida_produtos);

    return 1;
}

int tamanho_arquivo_saida_produtos() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_saida_produtos_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_saida_produtos_binario();
    }
}

int tamanho_arquivo_saida_produtos_binario(){

    FILE *p_arquivo_tam_saida_produtos;
    p_arquivo_tam_saida_produtos = fopen("arquivos\\saida_produtos.bin", "a+b");
    int control, tam_saida_produtos;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_saida_produtos == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_saida_produtos);

    //lendo o tamanho do array
    control = fread(&tam_saida_produtos, sizeof (int), 1, p_arquivo_tam_saida_produtos);

    fclose(p_arquivo_tam_saida_produtos);

    if (control != 1) {
        return -1;
    }

    return tam_saida_produtos;

}

int tamanho_arquivo_saida_produtos_texto() {

    FILE *p_arquivo_saida_produtos;
    p_arquivo_saida_produtos = fopen("arquivos\\saida_produtos_text.txt", "a+");
    int tam_saida_produtos, control;

    if (p_arquivo_saida_produtos == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_saida_produtos);

    control = fscanf(p_arquivo_saida_produtos, "%d", &tam_saida_produtos);

    fclose(p_arquivo_saida_produtos);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_saida_produtos;

}

dados_saida_produtos ler_arquivo_saida_produtos(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_saida_produtos_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_saida_produtos_binario(i);
    }
}

dados_saida_produtos ler_arquivo_saida_produtos_binario(int i) {

    dados_saida_produtos saida_produtos;

    FILE *p_arquivo_saida_produtos;
    p_arquivo_saida_produtos = fopen("arquivos\\saida_produtos.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_saida_produtos == NULL) {
        saida_produtos.cod = -1;
        return saida_produtos;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_saida_produtos);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_saida_produtos, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_saida_produtos, (i) * sizeof (dados_saida_produtos), SEEK_CUR);
    }
    //lendo o array
    fread(&saida_produtos, sizeof (dados_saida_produtos), 1, p_arquivo_saida_produtos);

    fclose(p_arquivo_saida_produtos);

    return saida_produtos;
}

dados_saida_produtos ler_arquivo_saida_produtos_texto(int i) {

    dados_saida_produtos saida_produtos;

    FILE *p_arquivo_saida_produtos;
    p_arquivo_saida_produtos = fopen("arquivos\\saida_produtos_text.txt", "a+");

    if (p_arquivo_saida_produtos == NULL) {
        saida_produtos.cod = -1;
        return saida_produtos; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_saida_produtos);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_saida_produtos, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0){
        free(saida_produtos.p_conta);
        fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.cod);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.status);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_saida_produtos, "%s", saida_produtos.CPF);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.forma_pagamento);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_saida_produtos, "%f", &saida_produtos.total);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.tam_conta);
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        saida_produtos.p_conta = (dados_conta *) malloc(saida_produtos.tam_conta * sizeof (dados_conta));
        for(int j=0;j<saida_produtos.tam_conta;j++){
            fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.p_conta[j].cod_produto);
            fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
            fscanf(p_arquivo_saida_produtos, "%d", &saida_produtos.p_conta[j].quantidade);
            fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
                                                    }
        fseek(p_arquivo_saida_produtos, 1 * sizeof (char), SEEK_CUR);
        i--;
                        }

    fclose(p_arquivo_saida_produtos);

    return saida_produtos;
}

//=======================================ARQUIVOS_CAIXA_LANCAMENTOS===============================================
int salvar_arquivo_lancamento(dados_lancamento *p_lancamento, int tam_lancamento) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_lancamento_texto(p_lancamento, tam_lancamento);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_lancamento_binario(p_lancamento, tam_lancamento);
    }
}

int salvar_arquivo_lancamento_binario(dados_lancamento *p_lancamento, int tam_lancamento) {

    FILE *p_arquivo_lancamento;
    p_arquivo_lancamento = fopen("arquivos\\lancamento.bin", "wb");
    int salvo;

    if (p_arquivo_lancamento == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_lancamento, sizeof (int), 1, p_arquivo_lancamento);

    //salvando o array
    salvo = fwrite(p_lancamento, sizeof (dados_lancamento), tam_lancamento, p_arquivo_lancamento);

    fclose(p_arquivo_lancamento);

    if (salvo == tam_lancamento) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_lancamento_texto(dados_lancamento *p_lancamento, int tam_caixa_lancamento) {

    FILE *p_arquivo_lancamento;
    p_arquivo_lancamento = fopen("arquivos\\caixa_text.txt", "w");

    if (p_arquivo_lancamento == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_lancamento, "%d\n", tam_caixa_lancamento);

    for (int i = 0; i < tam_caixa_lancamento; i++) {
        fprintf(p_arquivo_lancamento, "%d;", p_lancamento[i].cod);
        //lacos para grava a data no arquivo (pois a data é em formato de vetor)
        for (int j = 0; j < 3; j++){
            fprintf(p_arquivo_lancamento, "%d", p_lancamento[i].data[j]);
            if (j != 2) {
                fprintf(p_arquivo_lancamento, "/");
            } else {
                fprintf(p_arquivo_lancamento, ";");
            }
        }
        fprintf(p_arquivo_lancamento, "%.2f;", p_lancamento[i].valor);
        fprintf(p_arquivo_lancamento, "%d;", p_lancamento[i].tipo);
        fprintf(p_arquivo_lancamento, "%s", p_lancamento[i].fonte);
    }
    fclose(p_arquivo_lancamento);

    return 1;
}

int tamanho_arquivo_lancamento() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_lancamento_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_lancamento_binario();
    }
}

int tamanho_arquivo_lancamento_binario() {

    FILE *p_arquivo_tam_lancamento;
    p_arquivo_tam_lancamento = fopen("arquivos\\lancamento.bin", "a+b");
    int control, tam_lancamento;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_lancamento == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_lancamento);

    //lendo o tamanho do array
    control = fread(&tam_lancamento, sizeof (int), 1, p_arquivo_tam_lancamento);

    fclose(p_arquivo_tam_lancamento);

    if (control != 1) {
        return -1;
    }

    return tam_lancamento;

}

int tamanho_arquivo_lancamento_texto() {

    FILE *p_arquivo_lancamento;
    p_arquivo_lancamento = fopen("arquivos\\lancamento_text.txt", "a+");
    int tam_lancamento, control;

    if (p_arquivo_lancamento == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_lancamento);

    control = fscanf(p_arquivo_lancamento, "%d", &tam_lancamento);

    fclose(p_arquivo_lancamento);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_lancamento;

}

dados_lancamento ler_arquivo_lancamento(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_lancamento_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_lancamento_binario(i);
    }
}

dados_lancamento ler_arquivo_lancamento_binario(int i) {

    dados_lancamento lancamento;

    FILE *p_arquivo_lancamento;
    p_arquivo_lancamento = fopen("arquivos\\lancamento.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_lancamento == NULL) {
        lancamento.cod = -1;
        return lancamento;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_lancamento);

    //ultrapassando o tam_hotel
    fseek(p_arquivo_lancamento, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_lancamento, (i) * sizeof (dados_lancamento), SEEK_CUR);
    }
    //lendo o array
    fread(&lancamento, sizeof (dados_lancamento), 1, p_arquivo_lancamento);

    fclose(p_arquivo_lancamento);

    return lancamento;
}

dados_lancamento ler_arquivo_lancamento_texto(int i) {

    dados_lancamento lancamento;

    FILE *p_arquivo_lancamento;
    p_arquivo_lancamento = fopen("arquivos\\lancamento_text.txt", "a+");

    if (p_arquivo_lancamento == NULL) {
        lancamento.cod = -1;
        return lancamento; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_lancamento);

    //ultrapassando o tam_lancamento
    fseek(p_arquivo_lancamento, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_lancamento, "%d", &lancamento.cod);
        fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_CUR);
        for (int j; j < 3; j++) {
            fscanf(p_arquivo_lancamento, "%d", &lancamento.data[j]);
            fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_CUR);
        }
        fscanf(p_arquivo_lancamento, "%f", &lancamento.valor);
        fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_lancamento, "%d", &lancamento.tipo);
        fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_lancamento, "%[^\n]s", &lancamento.fonte);
        fseek(p_arquivo_lancamento, 1 * sizeof (char), SEEK_CUR);
        
        i--;
    }

    fclose(p_arquivo_lancamento);

    return lancamento;
}

//=====================================ARQUIVO CAIXA_RETIRADA=====================================================
int salvar_arquivo_retirada(dados_retirada *p_retirada, int tam_retirada) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_retirada_texto(p_retirada, tam_retirada);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_retirada_binario(p_retirada, tam_retirada);
    }
}

int salvar_arquivo_retirada_binario(dados_retirada *p_retirada, int tam_retirada) {

    FILE *p_arquivo_retirada;
    p_arquivo_retirada = fopen("arquivos\\retirada.bin", "wb");
    int salvo;

    if (p_arquivo_retirada == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    //salvando o tamanho do array
    fwrite(&tam_retirada, sizeof (int), 1, p_arquivo_retirada);

    //salvando o array
    salvo = fwrite(p_retirada, sizeof (dados_retirada), tam_retirada, p_arquivo_retirada);

    fclose(p_arquivo_retirada);

    if (salvo == tam_retirada) {
        //caso tenha salvado tudo com sucesso
        return 1;
    } else {
        //caso tenha dado algum erro
        return 0;
    }
}

int salvar_arquivo_retirada_texto(dados_retirada *p_retirada, int tam_caixa_retirada) {

    FILE *p_arquivo_retirada;
    p_arquivo_retirada = fopen("arquivos\\retirada_text.txt", "w");

    if (p_arquivo_retirada == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_retirada, "%d\n", tam_caixa_retirada);

    for (int i = 0; i < tam_caixa_retirada; i++) {
        fprintf(p_arquivo_retirada, "%d;", p_retirada[i].cod);
        //lacos para grava a data no arquivo (pois a data é em formato de vetor)
        for (int j = 0; j < 3; j++){
            fprintf(p_arquivo_retirada, "%d", p_retirada[i].data[j]);
            if (j != 2) {
                fprintf(p_arquivo_retirada, "/");
            } else {
                fprintf(p_arquivo_retirada, ";");
            }
        }
        fprintf(p_arquivo_retirada, "%f;", p_retirada[i].valor);
        fprintf(p_arquivo_retirada, "%s", p_retirada[i].fonte);
    }
    fclose(p_arquivo_retirada);

    return 1;
}

int tamanho_arquivo_retirada() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return tamanho_arquivo_retirada_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return tamanho_arquivo_retirada_binario();
    }
}

int tamanho_arquivo_retirada_binario() {

    FILE *p_arquivo_tam_retirada;
    p_arquivo_tam_retirada = fopen("arquivos\\retirada.bin", "a+b");
    int control, tam_retirada;

    //verificando se o arquivo foi aberto
    if (p_arquivo_tam_retirada == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_tam_retirada);

    //lendo o tamanho do array
    control = fread(&tam_retirada, sizeof (int), 1, p_arquivo_tam_retirada);

    fclose(p_arquivo_tam_retirada);

    if (control != 1) {
        return -1;
    }

    return tam_retirada;

}

int tamanho_arquivo_retirada_texto() {

    FILE *p_arquivo_retirada;
    p_arquivo_retirada = fopen("arquivos\\retirada_text.txt", "a+");
    int tam_retirada, control;

    if (p_arquivo_retirada == NULL) {
        return -2; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_retirada);

    control = fscanf(p_arquivo_retirada, "%d", &tam_retirada);

    fclose(p_arquivo_retirada);

    if (control != 1) {
        return -1; //caso ele n tenha lido nenhum dado
    }

    return tam_retirada;

}

dados_retirada ler_arquivo_retirada(int i) {


    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_retirada_texto(i);
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_retirada_binario(i);
    }
}

dados_retirada ler_arquivo_retirada_binario(int i) {

    dados_retirada retirada;

    FILE *p_arquivo_retirada;
    p_arquivo_retirada = fopen("arquivos\\retirada.bin", "a+b");

    //verificando se o arquivo foi aberto
    if (p_arquivo_retirada == NULL) {
        retirada.cod = -1;
        return retirada;
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_retirada);

    //ultrapassando o tam_retirada
    fseek(p_arquivo_retirada, 1 * sizeof (int), SEEK_SET);

    //andando pelo array ate a posicao desejada
    if (i > 0) {
        fseek(p_arquivo_retirada, (i) * sizeof (dados_retirada), SEEK_CUR);
    }
    //lendo o array
    fread(&retirada, sizeof (dados_retirada), 1, p_arquivo_retirada);

    fclose(p_arquivo_retirada);

    return retirada;
}

dados_retirada ler_arquivo_retirada_texto(int i) {

    dados_retirada retirada;

    FILE *p_arquivo_retirada;
    p_arquivo_retirada = fopen("arquivos\\retirada_text.txt", "a+");

    if (p_arquivo_retirada == NULL) {
        retirada.cod = -1;
        return retirada; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_retirada);

    //ultrapassando o tam_lancamento
    fseek(p_arquivo_retirada, 1 * sizeof (int), SEEK_SET);
    fseek(p_arquivo_retirada, 1 * sizeof (char), SEEK_SET);

    while (i + 1 > 0) {
        fscanf(p_arquivo_retirada, "%d", &retirada.cod);
        fseek(p_arquivo_retirada, 1 * sizeof (char), SEEK_CUR);
        for (int j; j < 3; j++) {
            fscanf(p_arquivo_retirada, "%d", &retirada.data[j]);
            fseek(p_arquivo_retirada, 1 * sizeof (char), SEEK_CUR);
        }
        fscanf(p_arquivo_retirada, "%f", &retirada.valor);
        fseek(p_arquivo_retirada, 1 * sizeof (char), SEEK_CUR);
        fscanf(p_arquivo_retirada, "%[^\n]s", &retirada.fonte);
        fseek(p_arquivo_retirada, 1 * sizeof (char), SEEK_CUR);
        
        i--;
    }

    fclose(p_arquivo_retirada);

    return retirada;
}

//===========================================ARQUIVO CAIXA=======================================================
int salvar_arquivo_caixa(float valor_caixa) {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return salvar_arquivo_caixa_texto(valor_caixa);
    }
        //BINARIO    
    else if (tipo_de_arquivamento == 2) {
        return salvar_arquivo_caixa_binario(valor_caixa);
    }
}

int salvar_arquivo_caixa_binario(float valor_caixa) {

    FILE *p_arquivo_caixa;
    p_arquivo_caixa = fopen("arquivos\\caixa.bin", "wb");

    if (p_arquivo_caixa == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }

    fwrite(&valor_caixa, sizeof (float), 1, p_arquivo_caixa);

    fclose(p_arquivo_caixa);

    return 1;
}

int salvar_arquivo_caixa_texto(float valor_caixa) {

    FILE *p_arquivo_caixa;
    p_arquivo_caixa = fopen("arquivos\\caixa_text.txt", "w");

    if (p_arquivo_caixa == NULL) {
        return -1; //saida de erro da abertura do arquivo
    }
    fprintf(p_arquivo_caixa, "%f\n", valor_caixa);

    fclose(p_arquivo_caixa);

    return 1;
}

float ler_arquivo_caixa() {

    //TEXTO
    if (tipo_de_arquivamento == 1) {
        return ler_arquivo_caixa_texto();
    }
        //BINARIO
    else if (tipo_de_arquivamento == 2) {
        return ler_arquivo_caixa_binario();
    }
}

float ler_arquivo_caixa_binario() {

    FILE *p_arquivo_caixa;
    p_arquivo_caixa = fopen("arquivos\\caixa.bin", "a+b");
    int control;
    float valor_caixa;

    //verificando se o arquivo foi aberto
    if (p_arquivo_caixa == NULL) {
        return -2.0; //saida de erro da abertura do arquivo
    }
    //para voltar ao comeco do arquivo
    rewind(p_arquivo_caixa);

    //lendo o tamanho do array
    control = fread(&valor_caixa, sizeof (float), 1, p_arquivo_caixa);

    fclose(p_arquivo_caixa);

    if(control != 1){
        return -1.0;
                        }

    return valor_caixa;

}

float ler_arquivo_caixa_texto() {

    FILE *p_arquivo_caixa;
    p_arquivo_caixa = fopen("arquivos\\caixa_text.txt", "a+");
    float valor_caixa;
    int control;

    if (p_arquivo_caixa == NULL) {
        return -2.0; //saida de erro da abertura do arquivo
    }
    //voltando o ponteiro do arquivo para o inicio do arquivo
    rewind(p_arquivo_caixa);

    control = fscanf(p_arquivo_caixa, "%f", &valor_caixa);

    fclose(p_arquivo_caixa);

    if (control != 1) {
        return -1.0; //caso ele n tenha lido nenhum dado
    }

    return valor_caixa;

}