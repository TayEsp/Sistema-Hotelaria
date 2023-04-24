#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "categoria.h"
#include "acomodacao.h"
#include "fornecedor.h"
#include "Reserva.h"
#include "arquivo.h"
#include "checkin.h"
#include "checkout.h"

void time_atual(){

    struct tm *data_hora_atual = set_time();
    
    printf("%d/%d/%d - ", data_hora_atual->tm_mday,
                       data_hora_atual->tm_mon+1,
                       data_hora_atual->tm_year+1900);

    printf("%d:%d",data_hora_atual->tm_hour
                  ,data_hora_atual->tm_min);
};

void menu_principal(){
    
    int menu, control_cod, i, control_senha=0;
    char senha[20];
    dados_operador operador;  
    
    control_cod = inicializacao_operador();
    
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            } 
                        }
    //pedindo o tamanho do aray para ver se é o primeiro acesso
    control_cod = tam_do_array_operador();
    //Condicao caso seja o primeiro acesso
    if(control_cod==0){
        printf("              Primeiro Cadastro\n");
        printf("                  Bem Vindxs\n  ");
        printf("Precisa-se fazer um cadastro de administrador:\n ");
           
        //Cadastrando os dados do operador    
        setbuf(stdin, NULL);//Ressetando o buffer
        printf("\nDigite o nome do operador: ");
        scanf("%[a-z A-Z 0-9 \b]s", operador.nome);
        setbuf(stdin, NULL);//Ressetando o buffer    
        printf("Digite o usuÃ¡rio do operador: ");
        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.usuario);  
        setbuf(stdin, NULL);//Ressetando o buffer    
        printf("Digite a senha: ");
        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.senha);
        setbuf(stdin, NULL);//Ressetando o buffer  
        //definindo o operador como administrador
        strcpy(operador.categoria,"admin");   
           
        //cadastrando o operador
        control_cod = cadastro_operador(operador);
        //salvando o operador
        salvar_operador();
        //definindo a o controle para conseguir acessar os menus
        control_senha=4;
        
        printf("\nO cÃ³digo de operador: %d", control_cod);
        setbuf(stdin, NULL);//Ressetando o buffer   
        printf("\nCadastro feito com sucesso!\n");
        printf("Aperte qualquer tecla para continuar...\n");
        getchar();
    //Condicao para os proximos acessos              
    }else{
        printf("       Bem Vindxs\n    ");
        time_atual();
        //laco para o login
        do{
            printf("\n ======== LOGIN ========\n");
            printf(" Digite seu login: ");    
            setbuf(stdin, NULL);//Ressetando o buffer 
            scanf("%[a-z A-Z 0-9 , . - \b]s", operador.usuario);

            //buscando o tam do operador
            control_cod = tam_do_array_operador();

            //consultando a existencia do login
            for(i=0;i<control_cod;i++){
                operador = consulta_operador(operador, 3, i);

                if(operador.cod!=-1){
                    break;
                                    }
                                        }
                if(operador.cod==-1){
                    system("clear||cls");
                    printf("\nUsuario Incorreto\n");
                    printf("Aperte qualquer tecla para continuar, ou digite 1 para sair...\n");
                    setbuf(stdin, NULL);//Ressetando o buffer 
                    control_cod = getchar();
                    if(control_cod==1){
                        operador.cod=-1;
                                        }
                    system("clear||cls");
                                       }
        }while(operador.cod==-1);
        
        //redefinindo as variaveis de controle 
        control_senha=0;
        control_cod==0;
        //consultando a existencia da senha
        do{
            printf(" Digite sua senha: ");   
            setbuf(stdin, NULL);//Ressetando o buffer 
            scanf("%[a-z A-Z 0-9 , . - \b]s", senha);
            
                if(strstr(senha, operador.senha)==NULL && control_senha<3){
                    system("clear||cls");
                    printf("Senha Incorreta");
                    printf("\nVoce tem mais %d tentativas\n", (3-control_senha));
                    control_senha++;
                    printf("Aperte qualquer tecla para continuar, ou digite 1 para sair...\n");
                    setbuf(stdin, NULL);//Ressetando o buffer 
                    control_cod = getchar();
                    system("clear||cls");
                    //caso a pessoa tenha decidido sair 
                    if(control_cod==1){
                        control_senha=4;
                                        }
                                                                            }
                else if(control_senha>=3){
                        system("clear||cls");
                        control_senha++;
                        printf("Chances esgotadas!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        setbuf(stdin, NULL);//Ressetando o buffer 
                        getchar();
                                            }
                else{
                    control_cod=1;
                        }       
            }while(control_senha<=3 && control_cod==0);
                }
    //encaminhando para o menu do operador
    if(control_senha<3){
        if(strstr(operador.categoria, "admin")!=NULL){
            menu_admin();
                                                       }
        else if(strstr(operador.categoria, "gerente")!=NULL){
            menu_gerente();
                                                               }
        else if(strstr(operador.categoria, "recepcao")!=NULL){
            menu_recepcao();
                                                               }
                            }
    return;
};

void menu_admin(){
    
    int menu;

    do{
        if(menu!=4){
        system("clear||cls");
        printf("      Bem Vindxs\n    ");
        time_atual();
        printf("\n ======== MENU ========\n"
               " == 1.Cadastro       ==\n"
               " == 2.Reservas       ==\n"
               " == 3.Transacoes     ==\n"
               " == 4.Sair           ==\n"
               " ======================\n");
        printf(" Digite sua opcao: ");
        scanf("%d", &menu);
        
        system("clear||cls");
               
            switch(menu){
                case 1:
                    printf(" =======================\n"
                           " == Deseja cadastrar: ==\n"
                           " == 1. Hotel          ==\n"
                           " == 2. Operador       ==\n"
                           " == 3. Hospede        ==\n"
                           " == 4. Acomodacao     ==\n"
                           " == 5. Categoria      ==\n"
                           " == 6. Produtos       ==\n"
                           " == 7. Fornecedor     ==\n"
                           " == 8. Sair           ==\n"
                           " =======================\n");
                    printf(" Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){
                        case 1:
                            menu_hotel();
                        break;  

                        case 2:
                           menu_operador();
                        break;

                        case 3:
                            menu_hospede();
                        break;

                        case 4:
                            menu_acomodacao();
                            menu=0;
                        break;

                        case 5:
                            menu_operador();
                            menu=0;
                        break;

                        case 6:
                            menu_produto();
                            menu=0;
                        break;

                        case 7:
                            menu_fornecedor();
                            menu=0;
                        break;
                        
                        case 8:
                           menu=0;
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;

                case 2:
                    menu_reserva();
                break;
                
                case 3:
                    printf(" ============================\n"
                           " == 1. Check-in            ==\n"
                           " == 2. Check-out           ==\n"
                           " == 3. Venda de produtos   ==\n"
                           " == 4. Controle de Caixa   ==\n"
                           " == 5. Contas              ==\n"
                           " == 6. Entrada de Produtos ==\n"
                           " == 7. Sair                ==\n"
                           " ============================\n");
                    printf(" Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){
                        case 1:
                            menu_checkin();
                        break;  

                        case 2:
                            menu_checkout();
                        break;

                        case 3:
                            menu_saida_produtos();
                        break;

                        case 4:
                            //menu_controle_caixa(0, 0);
                            menu=0;
                        break;

                        case 5:
                            //menu_contas();
                            menu=0;
                        break;

                        case 6:
                            //menu_entrada_produtos();
                            menu=0;
                        break;

                        case 7:
                            
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;
                
                case 4:
                    
                break;

                default:
                    printf("Opcao invalida");
                break;   
                        }
                    }
                
        }while(menu!=4);
        
    return;
}

void menu_gerente(){
    int menu;

    do{
        if(menu!=3){
        system("clear||cls");
        printf("      Bem Vindxs\n    ");
        time_atual();
        printf("\n ======== MENU ========\n"
               " == 1.Cadastro       ==\n"
               " == 2.Reservas       ==\n"
               " == 3.Transacoes     ==\n"
               " == 4.Sair           ==\n"
               " ======================\n");
        printf(" Digite sua opcao: ");
        scanf("%d", &menu);
        
        system("clear||cls");
               
            switch(menu){
                case 1:
                    printf("=========================\n"
                           "== Deseja cadastrar:   ==\n"
                           "== 1. Hospede          ==\n"
                           "== 2. Acomodacao       ==\n"
                           "== 3. Categoria        ==\n"
                           "== 4. Produtos         ==\n"
                           "== 5. Sair             ==\n"
                           "=========================\n");
                    printf("Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){

                        case 1:
                            menu_hospede();
                        break;

                        case 2:
                            menu_acomodacao();
                        break;

                        case 3:
                            menu_categoria();
                        break;

                        case 4:
                            menu_produto();
                            menu=0;
                        break;
                        
                        case 5:
                           menu=0;
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;

                case 2:
                    menu_reserva();
                break;
                
                case 3:
                    printf("============================\n"
                           "== 1. Check-in            ==\n"
                           "== 2. Check-out           ==\n"
                           "== 3. Venda de produtos   ==\n"
                           "== 4. Controle de Caixa   ==\n"
                           "== 5. Contas              ==\n"
                           "== 6. Entrada de Produtos ==\n"
                           "== 7. Sair                ==\n"
                           "============================\n");
                    printf("Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){
                        case 1:
                            menu_checkin();
                        break;  

                        case 2:
                            menu_checkout();
                        break;

                        case 3:
                            //menu_saida_produtos();
                        break;

                        case 4:
                            //menu_controle_caixa(0, 0);
                            menu=0;
                        break;

                        case 5:
                            //menu_contas();
                            menu=0;
                        break;

                        case 6:
                            //menu_entrada_produtos();
                            menu=0;
                        break;

                        case 7:
                            menu=0;
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;
                
                case 4:
                    
                break;

                default:
                    printf("Opcao invalida");
                break;   
                        }
                    }
                
        }while(menu!=4);
        
    return;
}

void menu_recepcao(){
    
    int menu;

    do{
        if(menu!=3){
        system("clear||cls");
        printf("     Bem Vindxs\n  ");
        time_atual();
        printf("\n ======== MENU ========\n"
               " == 1.Cadastro       ==\n"
               " == 2.Reservas       ==\n"
               " == 3.Transacoes     ==\n"
               " == 4.Sair           ==\n"
               " ======================\n");
        printf(" Digite sua opcao: ");
        scanf("%d", &menu);
        
        system("clear||cls");
               
            switch(menu){
                case 1:
                    printf("=========================\n"
                           "== Deseja cadastrar:   ==\n"
                           "== 1. Hospede          ==\n"
                           "== 2. Acomodacao       ==\n"
                           "== 3. Produtos         ==\n"
                           "== 4. Sair             ==\n"
                           "=========================\n");
                    printf("Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){

                        case 1:
                            menu_hospede();
                        break;

                        case 2:
                            menu_acomodacao();
                        break;

                        case 3:
                            menu_produto();
                            menu=0;
                        break;
                        
                        case 4:
                           menu=0;
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;

                case 2:
                    menu_reserva();
                break;
                
                case 3:
                    printf("============================\n"
                           "== 1. Check-in            ==\n"
                           "== 2. Check-out           ==\n"
                           "== 3. Venda de produtos   ==\n"
                           "== 4. Caixa               ==\n"
                           "== 5. Sair                ==\n"
                           "============================\n");
                    printf("Digite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){
                        case 1:
                            menu_checkin();
                        break;  

                        case 2:
                            menu_checkout();
                        break;

                        case 3:
                            menu_saida_produtos();
                        break;

                        case 4:
                            //menu_controle_caixa(0, 0);
                            menu=0;
                        break;

                        case 5:
                            menu=0;
                        break;

                        default:
                            printf("Opcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            menu=0;
                        break;
                                }
                break;
                
                case 4:
                    
                break;

                default:
                    printf("Opcao invalida");
                break;   
                        }
                    }
                
        }while(menu!=4);
        
    return;
}

//==========================================CADASTROS====================================================
void menu_fornecedor(){

    dados_fornecedor fornecedor, fornecedor_con;
    int menu, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, i;
    
    //inicializando o fornecedor
    control_cod = inicializacao_fornecedor();//funcao para ler o arquivo do fornecedor
    if(control_cod==-2){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados do fornecedor
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o nome fantasia da empresa: ");
                scanf("%[- , . a-z A-Z 0-9 \b]s", fornecedor.nome_fantasia);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a razao social da empresa: ");
                scanf("%[- , . a-z A-Z 0-9 \b]s", fornecedor.razao_social);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o numero da incricao estadual da empresa (ultilize - para o digito): ");
                scanf("%[- / . 0-9 \b]s", fornecedor.incricao_est);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o CNPJ da empresa (Ex: 99999999/9999-99): ");
                scanf("%[- / . 0-9 \b]s", fornecedor.cnpj);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o endereco da empresa(Ex: Rua tal, 99 - Bairro, cidade/ES - CEP:99999-999): ");
                scanf("%[- / : , . a-z A-Z 0-9 \b]s", fornecedor.endereco);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o telefone da empresa(Ex: 55 11 99999-9999): ");
                scanf("%[- + / ( ) 0-9 \b]s", fornecedor.telefone);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o email da empresa: ");
                scanf("%[- . _ @ a-z A-Z 0-9 \b]s", fornecedor.email);
                
                    
                control_cod = cadastro_fornecedor(fornecedor);
                printf("\nO cÃ³digo do fornecedor: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do fornecedor que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_fornecedor(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n 1. CÃ³digo"
                           "\n 2. Nome Fantasia"
                           "\n 3. Razao Social"
                           "\n 4. Inscricao Estadual"
                           "\n 5. CNPJ"
                           "\n 6. Endereco"
                           "\n 7. Telefone"
                           "\n 8. Email");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){
                    case 1:
                        do{
                            printf("Digite o novo cÃ³digo do fornecedor: ");
                            scanf("%d", &fornecedor.cod);
                            //Verificacao de codigos iguais
                                control_cod = verificacao_cod_fornecedor(fornecedor.cod);
                                }
                        while(control_cod!=-1);

                        alteracao_dados_fornecedor(fornecedor, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;    

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo nome fantasia do fornecedor: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.nome_fantasia);      

                        alteracao_dados_fornecedor(fornecedor, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a nova razao social do fornecedor: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.razao_social);      

                        alteracao_dados_fornecedor(fornecedor, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;

                    case 4:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a nova incricao estadual do fornecedor (ultilize - para o digito): ");
                        scanf("%[0-9 / - \b]s", fornecedor.incricao_est);     

                        alteracao_dados_fornecedor(fornecedor, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;

                    case 5:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo CNPJ do fornecedor (Ex: 99999999/9999-99): ");
                        scanf("%[0-9 / - \b]s", fornecedor.cnpj);     

                        alteracao_dados_fornecedor(fornecedor, 5, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 6:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o endereco do fonecedor(Ex: Rua tal, 99 - Bairro, cidade/ES - CEP:99999-999): ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.razao_social);    

                        alteracao_dados_fornecedor(fornecedor, 6, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();  
                    break;
                    
                    case 7:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo telefone do fornecedor(Ex: 55 11 99999-9999: ");
                        scanf("%[0-9 / - () \b]s", fornecedor.telefone);    

                        alteracao_dados_fornecedor(fornecedor, 7, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();  
                    break;
                    
                    case 8:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo email do fonecedor: ");
                        scanf("%[a-z A-Z 0-9 . - _ @ \b]s", fornecedor.email);    

                        alteracao_dados_fornecedor(fornecedor, 8, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();  
                    break;

                    default:
                        printf("\nOpcao nao valida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do fornecedor que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_fornecedor(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_fornecedor(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:        
            control_salvar = salvar_fornecedor();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do fornecedor\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar o fornecedor por:"
                        "\n 1. CÃ³digo"
                        "\n 2. Nome Fantasia"
                        "\n 3. Razao Social"
                        "\n 4. Inscricao Estadual"
                        "\n 5. CNPJ"
                        "\n 6. Endereco"
                        "\n 7. Telefone"
                        "\n 8. Email");
                printf("\nDigite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo do fornecedor que deseja consultar: ");
                        scanf("%d", &fornecedor.cod);
                    break;
                    
                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o nome fantasia do fornecedor: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.nome_fantasia);
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite a razao social do fornecedor: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.razao_social);
                    break;

                    case 4:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o numero da incricao estadual do fornecedor (ultilize - para o digito): ");
                        scanf("%[0-9 / - \b]s", fornecedor.incricao_est);                
                    break;

                    case 5:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o CNPJ do fornecedor (Ex: 99999999/9999-99): ");
                        scanf("%[0-9 / - \b]s", fornecedor.cnpj);              
                    break;

                    case 6:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o endereco do fonecedor(Ex: Rua tal, 99 - Bairro, cidade/ES - CEP:99999-999): ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", fornecedor.endereco);             
                    break;
                    
                    case 7:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o telefone do fonecedor(Ex: 55 11 99999-9999: ");
                        scanf("%[0-9 / - () \b]s", fornecedor.telefone);            
                    break;
                    
                    case 8:
                        setbuf(stdin, NULL);//Ressetando o buffer    
                        printf("Digite o email do fonecedor: ");
                        scanf("%[a-z A-Z 0-9 . - _ @ \b]s", fornecedor.email);
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===FORNECEDORES===\n");
            tam = tam_do_array_fornecedor();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            
            for(i=0;i<tam;i++){
                fornecedor_con = consulta_fornecedor(fornecedor, menu, i);  
                if(fornecedor_con.cod!=-1){
                printf("\nCÃ³digo: %d\n"
                       "Nome Fantasia: %s\n"
                       "Razao Social: %s\n"
                       "Inscricao Estadual: %s\n"
                       "CNPJ: %s\n"
                       "Endereco: %s\n"
                       "Telefone : %s\n"
                       "Email: %s\n", fornecedor_con.cod,
                                      fornecedor_con.nome_fantasia,
                                      fornecedor_con.razao_social,
                                      fornecedor_con.incricao_est,
                                      fornecedor_con.cnpj,
                                      fornecedor_con.endereco,
                                      fornecedor_con.telefone,
                                      fornecedor_con.email);
                control_cod++;
                                     }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("\nAperte qualquer tecla para continuar...\n");
            getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_fornecedor();
                    if(control_salvar==1){
                        menu=6;
                        sair_produto();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do fornecedor\n");
                            }             
                }else{
                    menu=6;
                    sair_fornecedor();
                        }            
            }else{
                sair_fornecedor();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;    
};

void menu_produto(){

    dados_produto produto, produto_con;
    int menu, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, i;
    
    //inicializando o produto
    control_cod = inicializacao_produto();//funcao para ler o arquivo do produto
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados do produto 
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a descricao do produto: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", produto.descricao);
                printf("Digite a quantidade de estoque do produto: ");
                scanf("%d", &produto.estoque);
                printf("Digite a quantidade de estoque minimo do produto: ");
                scanf("%d", &produto.estoque_min);
                printf("Digite o preco de custo do produto: ");
                scanf("%f", &produto.preco_custo);
                printf("Digite o preco de venda do produto: ");
                scanf("%f", &produto.preco_venda);
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite o nome do fornecedor do produto: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", produto.fornecedor);
  
                    
                control_cod = cadastro_produto(produto);
                printf("\nO cÃ³digo do produto: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do produto que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_produto(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n 1. CÃ³digo"
                           "\n 2. Descricao"
                           "\n 3. Estoque"
                           "\n 4. Estoque Minimo"
                           "\n 5. Preco de Custo"
                           "\n 6. Preco de Venda"
                           "\n 7. Fornecedor");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){
                    case 1:
                        do{
                            printf("Digite o novo cÃ³digo do produto: ");
                            scanf("%d", &produto.cod);
                            //Verificacao de codigos iguais
                                control_cod = verificacao_cod_produto(produto.cod);
                                }
                        while(control_cod!=-1);

                        alteracao_dados_produto(produto, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;    

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a nova descricao do produto: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", produto.descricao);      

                        alteracao_dados_produto(produto, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 3:
                        printf("Digite o novo estoque do produto: ");
                        scanf("%d", &produto.estoque);

                        alteracao_dados_produto(produto, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 4:
                        printf("Digite o novo estoque minimo do produto: ");
                        scanf("%d", &produto.estoque_min);

                        alteracao_dados_produto(produto, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;

                    case 5:
                        printf("Digite o novo preco de custo do produto: ");
                        scanf("%", &produto.preco_custo);

                        alteracao_dados_produto(produto, 5, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 6:
                        printf("Digite o novo preco de custo do produto: ");
                        scanf("%f", &produto.preco_venda);

                        alteracao_dados_produto(produto, 6, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 7:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo fornecedor do produto: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", produto.fornecedor);      

                        alteracao_dados_produto(produto, 7, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                    
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do produto que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_produto(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_produto(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
            control_salvar = salvar_produto();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do produto\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar o produto pela:\n"
                        "1.Codigo\n"
                        "2.Descricao\n"
                        "3.Estoque\n"
                        "4.Estoque Minimo\n"
                        "5.Preco de Custo\n"
                        "6.Preco de Venda\n"
                        "7.Fornecedor\n");
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo do produto que deseja consultar: ");
                        scanf("%d", &produto.cod);
                    break;

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a descricao do produto que deseja consultar: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", produto.descricao);
                    break;

                    case 3:
                        printf("Digite o estoque do produto que deseja consultar: ");
                        scanf("%d", &produto.estoque);
                    break;

                    case 4:
                        printf("Digite o estoque minimo do produto que deseja consultar: ");
                        scanf("%d", &produto.estoque_min);                 
                    break;

                    case 5:
                        printf("Digite o preco de custo do produto que deseja consultar: ");
                        scanf("%f", &produto.preco_custo);               
                    break;
                    
                    case 6:
                        printf("Digite o preco de venda do produto que deseja consultar: ");
                        scanf("%f", &produto.preco_venda);               
                    break;
                    
                    case 7:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o fornecedor do produto que deseja consultar: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", produto.fornecedor);
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===PRODUTOS===\n");
            tam = tam_do_array_produto();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            
            for(i=0;i<tam;i++){
                produto_con = consulta_produto(produto, menu, i);  
                if(produto_con.cod!=-1){
                printf("\nCÃ³digo: %d\n"
                       "Descricao: %s\n"
                       "Estoque: %d\n"
                       "Estoque Minimo: %d\n"
                       "Preco de Custo: %.2f\n"
                       "Preco de Venda: %.2f\n"
                       "Fornecedor: %s\n", produto_con.cod, 
                                           produto_con.descricao, 
                                           produto_con.estoque, 
                                           produto_con.estoque_min,
                                           produto_con.preco_custo,
                                           produto_con.preco_venda,
                                           produto_con.fornecedor);
                control_cod++;
                                     }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("\nAperte qualquer tecla para continuar...\n");
            getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_produto();
                    if(control_salvar==1){
                        menu=6;
                        sair_produto();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados da categoria\n");
                            }             
                }else{
                    menu=6;
                    sair_produto();
                        }            
            }else{
                sair_produto();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;    
};

void menu_categoria(){

    dados_categoria categoria, categoria_con;
    int menu=0, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, sub_menu, i;
    float consulta_valor[2]; 
    
    //inicializando a categoria
    control_cod = inicializacao_categoria();//funcao para ler o arquivo de categoria
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados da categoria    
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nDigite o nome da categoria: ");
                scanf("%[a-z A-Z 0-9 \b]s", categoria.nome);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a descricao da categoria: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", categoria.descricao);    
                printf("Digite o valor da diaria da categoria: ");
                scanf("%f", &categoria.valor_diaria);
                printf("Digite quantos adultos suporta: ");
                scanf("%d", &categoria.hospede[0]);
                printf("Digite quantos criancas suporta: ");
                scanf("%d", &categoria.hospede[1]);
                    
                control_cod = cadastro_categoria(categoria);
                printf("\nO cÃ³digo da categoria: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo da categoria que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_categoria(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n1. Nome"
                           "\n2. CÃ³digo"
                           "\n3. Descricao"
                           "\n4. Valor da Diaria"
                           "\n5. Quantidade de pessoas que suporta");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){
                    case 1:
                        printf("Digite o novo nome da categoria");
                        scanf("%[a-z A-Z 0-9 \b]s", categoria.nome);

                        alteracao_dados_categoria(categoria, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;    

                    case 2:
                        do{
                            printf("Digite o novo cÃ³digo da categoria: ");
                            scanf("%d", &categoria.cod);

                            //Verificacao de codigos iguais
                            control_cod = verificacao_cod_categoria(categoria.cod);
                            }
                        while(control_cod!=-1);

                        alteracao_dados_categoria(categoria, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a nova descricao da categoria: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", categoria.descricao);      

                        alteracao_dados_categoria(categoria, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 4:
                        printf("Digite o novo valor da diaria da categoria: ");
                        scanf("%f", &categoria.valor_diaria);

                        alteracao_dados_categoria(categoria, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 5:
                        printf("Digite quantos adultos a categoria suporta: ");
                        scanf("%d", &categoria.hospede[0]);
                        printf("Digite quantas criancas a categoria suporta: ");
                        scanf("%d", &categoria.hospede[1]);

                        alteracao_dados_categoria(categoria, 5, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo da categoria que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_categoria(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_categoria(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
            control_salvar = salvar_categoria();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados da categoria\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar a categoria pela:\n"
                        "1.Codigo\n"
                        "2.Nome\n"
                        "3.Descricao\n"
                        "4.Valor da diaria\n"
                        "5.Quantidade de Hospedes\n");
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo da categoria que deseja consultar: ");
                        scanf("%d", &categoria.cod);
                    break;

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o nome da categoria que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", categoria.nome);
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a descricao da categoria que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", categoria.descricao);
                    break;

                    case 4:
                        printf("Deseja procurar a categoria:\n"
                                "1.Por um valor minimo\n"
                                "2.Por um valor maximo\n"
                                "3.Ambos\n");
                        printf("Digite sua opcao: ");
                        scanf("%d", &sub_menu);

                        switch(sub_menu){ 
                            case 1:
                                printf("Digite um valor minimo da diaria da categoria que deseja consultar:");
                                scanf("%f", &consulta_valor[0]);
                            break;

                            case 2:
                                printf("Digite um valor maximo da diaria da categoria que deseja consultar:");
                                scanf("%f", &consulta_valor[1]);
                            break;

                            case 3:
                                printf("Digite um valor minimo da diaria da categoria que deseja consultar:");
                                scanf("%f", &consulta_valor[0]);
                                printf("Digite um valor maximo da diaria da categoria que deseja consultar:");
                                scanf("%f", &consulta_valor[1]);    
                            break;
                            
                            default:
                                printf("\nOpcao Invalida\n");
                                printf("Aperte qualquer tecla para continuar...\n");
                                getchar();
                            break;
                                              }                 
                    break;

                    case 5:
                        printf("Digite a quantidade de adultos da categoria que deseja consultar:");
                        scanf("%d", &categoria.hospede[0]);
                        printf("Digite a quantidade de criancas da categoria que deseja consultar:");
                        scanf("%d", &categoria.hospede[1]);                
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===CATEGORIAS===\n");
            tam = tam_do_array_categoria();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            for(i=0;i<tam;i++){
                categoria_con = consulta_categoria(categoria, menu, i, consulta_valor, sub_menu);  
                if(categoria_con.cod!=-1){
                printf("\nNome: %s\n"
                       "CÃ³digo: %d\n"
                       "Descricao: %s\n"
                       "Valor da Diaria: R$ %.2f\n"
                       "Adultos: %d\n"
                       "Criancas: %d\n", categoria_con.nome,
                                         categoria_con.cod, 
                                         categoria_con.descricao, 
                                         categoria_con.valor_diaria, 
                                         categoria_con.hospede[0],
                                         categoria_con.hospede[1]);
                control_cod++;
                                    }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nAperte qualquer tecla para continuar...\n");
                getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_categoria();
                    if(control_salvar==1){
                        menu=6;
                        sair_categoria();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados da categoria\n");
                            }             
                }else{
                    menu=6;
                    sair_categoria();
                        }            
            }else{
                sair_categoria();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;
};

void menu_acomodacao(){
    
    dados_categoria categoria;
    dados_acomodacao acomodacao, acomodacao_con;
    int menu=0, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, i;
    
    control_cod=inicializacao_categoria();//funcao para ler o arquivo de categoria    
    //verificando se os arquivos contem dados
    if(control_cod!=-1){
        control_cod=inicializacao_acomodacao();//funcao para ler o arquivo de acomodacao
                        }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua resposta: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }
    
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("    ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    switch(menu){
//CADASTRO DE DADOS
        case 1:             
                //Cadastrando os dados da acomodacao
                printf("Digite o numero do quarto da acomodacao: ");
                scanf("%d", &acomodacao.num_quarto);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a descricao da acomodacao: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.descricao);
                setbuf(stdin, NULL);//Ressetando o buffer       
                printf("Digite as facilidades que a acomodacao possui: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.facilidades);
                
                control_cod=-1;
                while(control_cod==-1){    
                    printf("Digite o cÃ³digo da categoria da acomodacao: ");
                    scanf("%d", &acomodacao.categoria);
               
                    //verificando cÃ³digo da categoria  
                    control_cod = verificacao_indice_categoria(acomodacao.categoria);
                
                    if(control_cod==-1){
                        printf("\nCÃ³digo nao existente\n");
                                        }
                                            }
                    setbuf(stdin, NULL);
                    control_cod = cadastro_acomodacao(acomodacao);
                    printf("\nO cÃ³digo da acomodacao: %d", control_cod);
                    printf("\nCadastro feito com sucesso!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar(); 
          
        break;
//ALTERACAO DE DADOS         
        case 2:
                cod_alteracao=-1;
                //Laco para verificacao de codigo
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo da acomodacao que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_acomodacao(cod_alteracao);

                    if(cod_alteracao==-1){
                        printf("CÃ³digo nao existente\n");
                        printf("Digite novamente ou digite -1 para sair\n");
                                            }
                                                }
                //condicao caso o usuario queira sair
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n1. CÃ³digo"
                           "\n2. Descricao"
                           "\n3. Facilidade"
                           "\n4. Categoria da acomodacao"
                           "\n5. Numero do quarto");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    switch(menu){    
                        case 1:
                            do{
                                printf("Digite o novo cÃ³digo da acomodacao: ");
                                scanf("%d", &acomodacao.cod);

                                //Verificacao de codigos iguais
                                control_cod = verificacao_cod_acomodacao(acomodacao.cod);
                                }
                            while(control_cod!=-1);

                        alteracao_dados_acomodacao(acomodacao, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();    

                        break;

                        case 2:
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a nova descricao da acomodacao: ");
                            scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.descricao);

                            alteracao_dados_acomodacao(acomodacao, 2, cod_alteracao);

                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("\nDados alterados com sucesso!\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar(); 
                        break;

                        case 3:
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite as novas facilidades da acomodacao: ");
                            scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.facilidades);

                            alteracao_dados_acomodacao(acomodacao, 3, cod_alteracao); 

                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("\nDados alterados com sucesso!\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar(); 
                        break;

                        case 4:
                            control_cod=-1;
                            while(control_cod==-1){    
                                printf("Digite o cÃ³digo da nova categoria da acomodacao: ");
                                scanf("%d", &acomodacao.categoria);               
                                //verificando cÃ³digo    
                                control_cod = verificacao_indice_categoria(cod_alteracao);                
                                if(control_cod==-1){
                                    printf("\nCÃ³digo nao existente\n");
                                                    }
                                                    }

                            alteracao_dados_acomodacao(acomodacao, 4, cod_alteracao);
                            printf("\nDados alterados com sucesso!\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar(); 
                        break;

                        case 5:
                            printf("Digite o novo numero do quarto da acomodacao: ");
                                scanf("%d", &acomodacao.num_quarto);

                            alteracao_dados_acomodacao(acomodacao, 5, cod_alteracao); 

                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("\nDados alterados com sucesso!\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar(); 
                        break;

                        default:
                            printf("\nOpcao Invalida\n");
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                        break;
                                        } 
                                    }                           
                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
                cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo da acomodacao que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado    
                    cod_alteracao = verificacao_indice_acomodacao(cod_alteracao); 
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_acomodacao(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
                //salvando os dados da acomodacao
                control_salvar = salvar_acomodacao();
                if(control_salvar==1){
                    //salvando os dados da categoria
                    control_salvar = salvar_categoria();
                }else{
                    printf("\nErro: ao salvar os dados da acomodacao\n");
                    if(control_salvar==-1){
                        printf("Erro na abertura do Arquivo!\n");
                                            }
                        }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar a acomodacao pela:\n"
                        "1.Codigo\n"
                        "2.Descricao\n"
                        "3.Facilidades\n"
                        "4.Categoria\n");
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
            system("clear||cls");//comando pra limpar a tela        
            switch(menu){
                case 1:
                    printf("Digite o cÃ³digo da acomodacao que deseja consultar: ");
                    scanf("%d", &acomodacao.cod);
                break;

                case 2:
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Digite a descricao da acomodacao que deseja consultar:");
                    scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.descricao);               
                break;

                case 3:
                setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Digite a facilidade da acomodacao que deseja consultar:");
                    scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.facilidades);             
                break;

                case 4:
                    printf("Digite o codigo categoria da acomodacao que deseja consultar:");
                    scanf("%d", &acomodacao.categoria);               
                break;
                
                case 5:
                    printf("Digite o quarto da acomodacao que deseja consultar:");
                    scanf("%d", &acomodacao.num_quarto); 
                break;    
                
                default:
                    printf("\nOpcao Invalida\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                break;    
                            }
            system("clear||cls");//comando pra limpar a tela
            printf("\n===ACOMODACOES===\n");
            tam = tam_do_array_acomodacao();//chamando a funcao de tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            for(i=0;i<tam;i++){
                //Procurando as structs que possuem as mesmas caracteristicas
                acomodacao_con = consulta_acomodacao(acomodacao, menu, i);
                if(acomodacao_con.cod!=-1){
                //Buscando o codigo da categoria e definindo o indice a procurar
                control_cod = verificacao_indice_categoria(acomodacao_con.categoria);
                //definindo o codigo da struct de categoria
                categoria.cod = acomodacao_con.categoria;
                //Buscando o nome da categoria
                categoria = consulta_categoria(categoria, 1, control_cod, 0, 0);
                printf("\nCÃ³digo: %d\n"
                       "NÃºmero do quarto: %d\n"
                       "Descricao: %s\n"
                       "Facilidades: %s\n"
                       "Categoria da acomodacao: %s\n", acomodacao_con.cod,
                                                        acomodacao_con.num_quarto,
                                                        acomodacao_con.descricao, 
                                                        acomodacao_con.facilidades, 
                                                        categoria.nome);
                control_cod++;
                                                    }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente");
                                }
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("\nAperte qualquer tecla para continuar...\n");
            getchar();  
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
            printf("\nDados nÃ£o salvos!");
            printf("\nDeseja Salvar?\n"
                    "1.Sim\n"
                    "2.Nao\n"
                    "Digite sua opcao: ");
            scanf("%d", &menu);
            system("clear||cls");//comando pra limpar a tela
            if(menu==1){
                control_salvar = salvar_acomodacao();
                if(control_salvar==1){
                        menu=6;
                        printf("\nDados salvos com sucesso!\n");
                        sair_acomodacao();
                        sair_categoria();                       
                    }else{
                    menu=0;
                    printf("\nErro: ao salvar os dados da acomodacao\n");
                        }
            }else{
                menu=6;
                sair_acomodacao();
                sair_categoria();
                    }
            
            }else{
                sair_acomodacao();
                sair_categoria();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);
    
    return;
};

void menu_operador(){

    dados_operador operador, operador_con;
    int menu=0, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, sub_menu, i;
    
    //inicializando o operador
    control_cod = inicializacao_operador();//funcao para ler o arquivo de operador
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados da operador    
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nDigite o nome do operador: ");
                scanf("%[a-z A-Z 0-9 \b]s", operador.nome);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o usuÃ¡rio do operador: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", operador.usuario);  
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a senha: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", operador.senha);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a categoria: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", operador.categoria);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                
                    
                control_cod = cadastro_operador(operador);
                printf("\nO cÃ³digo de operador: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do operador que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_operador(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n1. Nome"
                           "\n2. CÃ³digo"
                           "\n3. UsuÃ¡rio"
                           "\n4. Categoria");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){
                    case 1:
                        printf("Digite o novo nome do operador");
                        scanf("%[a-z A-Z 0-9 \b]s", operador.nome);

                        alteracao_dados_operador(operador, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;    

                    case 2:
                        do{
                            printf("Digite o novo cÃ³digo do operador: ");
                            scanf("%d", &operador.cod);

                            //Verificacao de codigos iguais
                            control_cod = verificacao_cod_operador(operador.cod);
                            }
                        while(control_cod!=-1);

                        alteracao_dados_operador(operador, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo usuÃ¡rio do operador: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.usuario);      

                        alteracao_dados_operador(operador, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 4:
                        printf("Digite a nova senha do operador: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.senha);

                        alteracao_dados_operador(operador, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do operador que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_operador(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_operador(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
            control_salvar = salvar_operador();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do operador\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar a operador pela:\n"
                        "1.Codigo\n"
                        "2.Nome\n"
                        "3.UsuÃ¡rio\n"
                        "4.Categoria\n" );
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo do operador que deseja consultar: ");
                        scanf("%d", &operador.cod);
                    break;

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o nome do operador que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.nome);
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o usuÃ¡rio do operador que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.usuario);
                    break;

                    case 4:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a categoria do operador que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", operador.categoria);                        
                    break;                   
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===OPERADORES===\n");
            tam = tam_do_array_operador();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            for(i=0;i<tam;i++){
                operador_con = consulta_operador(operador, menu, i);  
                if(operador_con.cod!=-1){
                printf("\nNome: %s\n"
                       "CÃ³digo: %d\n"
                       "UsuÃ¡rio: %s\n"
                       "Categoria: %s\n", operador_con.nome,
                                         operador_con.cod, 
                                         operador_con.usuario, 
                                         operador_con.categoria);
                control_cod++;
                                    }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nAperte qualquer tecla para continuar...\n");
                getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_operador();
                    if(control_salvar==1){
                        menu=6;
                        sair_operador();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do operador\n");
                            }             
                }else{
                    menu=6;
                    sair_operador();
                        }            
            }else{
                sair_operador();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;
};

void menu_hospede(){

    dados_hospede hospede, hospede_con;
    int menu=0, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, sub_menu, i;
    
    
    //inicializando o hospede
    control_cod = inicializacao_hospede();//funcao para ler o arquivo de hospede
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            } 
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados da hospede    
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nDigite o nome do hospede: ");
                scanf("%[a-z A-Z 0-9 \b]s", hospede.nome);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o endereÃ§o completo do hospede: ");
                scanf("%[- , . a-z A-Z 0-9 \b]s", hospede.endereco_completo);  
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o CPF: ");
                scanf("%[- , . a-z A-Z 0-9 \b]s", hospede.cpf);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o telefone: ");
                scanf("%[- , . a-z A-Z 0-9\b]s", hospede.telefone_hospede);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  printf("Digite o e-mail: ");
                scanf("%[@ - _ , . a-z A-Z 0-9 \b]s", hospede.email_hospede);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o sexo: ");
                scanf("%[a-z A-Z 0-9 \b]s", hospede.sexo);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  printf("Digite o estado civil: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.estado_civil);
                  setbuf(stdin, NULL);//Ressetando o buffer      
                  printf("Digite a data de nascimento: ");
                scanf("%[/ , . - a-z A-Z 0-9 \b]s", hospede.data_nascimento);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  
                  
                  
                control_cod = cadastro_hospede(hospede);
                printf("\nO cÃ³digo de hospede: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do hospede que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_hospede(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n1. Codigo"
                            "\n2. Nome"
                           "\n3. EndereÃ§o"
                           "\n4. CPF"
                           "\n5. Telefone"
                            "\n6. E-mail"
                            "\n7. Sexo"
                            "\n8. Estado civil"
                            "\n9. Data de nascimento");
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){                    
                     case 1:
                        do{
                            printf("Digite o novo codigo do hospede: ");
                            scanf("%d", &hospede.cod);

                            //Verificacao de codigos iguais
                            control_cod = verificacao_cod_hospede(hospede.cod);
                            }
                        while(control_cod!=-1);

                        alteracao_dados_hospede(hospede, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 2:
                        printf("Digite o novo nome do hospede");
                        scanf("%[a-z A-Z 0-9 \b]s", hospede.nome);

                        alteracao_dados_hospede(hospede, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;                     

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o novo endereÃ§o do hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.endereco_completo);      

                        alteracao_dados_hospede(hospede, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 4:
                        printf("Digite o novo CPF hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.cpf);

                        alteracao_dados_hospede(hospede, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 5:
                        printf("Digite o novo telefone hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.telefone_hospede);

                        alteracao_dados_hospede(hospede, 5, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 6:
                        printf("Digite o novo e-mail do hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.email_hospede);

                        alteracao_dados_hospede(hospede, 6, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 7:
                        printf("Digite o novo sexo do hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.sexo);

                        alteracao_dados_hospede(hospede, 7, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 8:
                        printf("Digite o novo estado civil do hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.estado_civil);

                        alteracao_dados_hospede(hospede, 8, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 9:
                        printf("Digite a nova data de nascimento do hospede: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.data_nascimento);

                        alteracao_dados_hospede(hospede, 9, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do hospede que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_hospede(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_hospede(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
            control_salvar = salvar_hospede();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do hospede\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar o  hospede pela:\n"
                        "1.Codigo\n"
                        "2.Nome\n"
                        "3.CPF \n");
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo do hospede que deseja consultar: ");
                        scanf("%d", &hospede.cod);
                    break;

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o nome do hospede que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.nome);
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o CPF do hospede que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hospede.cpf);
                    break;                               
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===HOSPEDES===\n");
            tam = tam_do_array_hospede();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            for(i=0;i<tam;i++){
                hospede_con = consulta_hospede(hospede, menu, i);  
                if(hospede_con.cod!=-1){
                printf("\nNome: %s\n"
                       "CÃ³digo: %d\n"
                       "EndereÃ§o completo: %s\n"
                       "CPF: %s\n"
                        "Telefone: %s\n"
                        "E-mail: %s\n"
                        "Sexo: %s\n"
                        "Estado civil: %s\n"
                        "Data de nascimento: %s\n", hospede_con.nome,
                                         hospede_con.cod, 
                                         hospede_con.endereco_completo, 
                                         hospede_con.cpf,
                        hospede_con.telefone_hospede, hospede_con.email_hospede, hospede_con.sexo,
                        hospede_con.estado_civil, hospede_con.data_nascimento);
                control_cod++;
                                    }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nAperte qualquer tecla para continuar...\n");
                getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_hospede();
                    if(control_salvar==1){
                        menu=6;
                        sair_hospede();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do hospede\n");
                            }             
                }else{
                    menu=6;
                    sair_hospede();
                        }            
            }else{
                sair_hospede();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;
};

void menu_hotel(){

    dados_hotel hotel, hotel_con;
    int menu=0, cod_alteracao=-1, control_cod=0, control_salvar=1;
    int tam, sub_menu, i;
    
    
    //inicializando o hotel
    control_cod = inicializacao_hotel();//funcao para ler o arquivo de hotel
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }   
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("   ");
    time_atual();
    printf("\n ======== MENU ========\n"
           " == 1. Cadastrar     ==\n"
           " == 2. Alterar Dados ==\n"
           " == 3. Excluir       ==\n"
           " == 4. Salvar        ==\n"
           " == 5. Consultar     ==\n"
           " == 6. Sair          ==\n"
           " ======================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){
//CADASTRO DE DADOS
        case 1:
            control_salvar=0;//ressetando o controle de salvamento                  
            //Cadastrando os dados da hotel    
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nDigite o nome fantasia do hotel: ");
                scanf("%[a-z A-Z 0-9 \b]s", hotel.nome_fantasia);
                setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a razÃ£o social hotel: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.razao_social);  
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite a inscricao estadual: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.inscricao_estadual);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o CNPJ: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.cnpj);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  printf("Digite o endereÃ§o completo: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.endereco_completo);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                printf("Digite o telefone do hotel: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.telefone_hotel);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  printf("Digite o e-mail do hotel: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.email_hotel);
                  setbuf(stdin, NULL);//Ressetando o buffer      
                  printf("Digite o nome do responsÃ¡vel: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.nome_responsavel);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                   printf("Digite o telefone do responsÃ¡vel: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.telefone_responsavel);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                   printf("Digite o horÃ¡rio de check-in: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.check_in);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                   printf("Digite o horÃ¡rio de check-out: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.check_out);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                   printf("Digite a margem de lucro de produtos vendidos: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.margem_lucro);
                  setbuf(stdin, NULL);//Ressetando o buffer    
                  
                  
                  
                control_cod = cadastro_hotel(hotel);
                printf("\nO cÃ³digo de hotel: %d", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer   
                printf("\nCadastro feito com sucesso!\n");
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();                                                       
            
        break;
//ALTERACAO DE DADOS         
        case 2:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do hotel que deseja alterar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando cÃ³digo    
                    cod_alteracao = verificacao_indice_hotel(cod_alteracao);
                
                if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    printf("\nQual dado deseja alterar:");
                    printf("\n1. Codigo"
                            "\n2. Nome Fantasia"
                           "\n3. RazÃ£o social"
                           "\n4. InscriÃ§Ã£o estadual"
                           "\n5. CNPJ"
                            "\n6. EndereÃ§o"
                            "\n7. Telefone"
                            "\n8. E-mail"
                            "\n9. Nome do responsÃ¡vel"
                            "\n10. Telefone do responsÃ¡vel"
                            "\n11. HorÃ¡rio de check-in"
                            "12. HorÃ¡rio de check-out"
                            "13. Margem de lucro de produtos vendidos"
                            );
                    printf("\nDigite sua opcao: ");
                    scanf("%d", &menu);

                    system("clear||cls");//comando pra limpar a tela
                switch(menu){                    
                     case 1:
                        do{
                            printf("Digite o novo codigo do hotel: ");
                            scanf("%d", &hotel.cod);

                            //Verificacao de codigos iguais
                            control_cod = verificacao_cod_hotel(hotel.cod);
                            }
                        while(control_cod!=-1);

                        alteracao_dados_hotel(hotel, 1, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 2:
                        printf("Digite o novo nome fantasia do hotel");
                        scanf("%[a-z A-Z 0-9 \b]s", hotel.nome_fantasia);

                        alteracao_dados_hotel(hotel, 2, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;                     

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a nova razÃ£o social do hotel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.razao_social);      

                        alteracao_dados_hotel(hotel, 3, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;

                    case 4:
                        printf("Digite a nova inscriÃ§Ã£o estadual: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.inscricao_estadual);

                        alteracao_dados_hotel(hotel, 4, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 5:
                        printf("Digite o novo CNPJ do hotel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.cnpj);

                        alteracao_dados_hotel(hotel, 5, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 6:
                        printf("Digite o novo endereÃ§o do hotel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.endereco_completo);

                        alteracao_dados_hotel(hotel, 6, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 7:
                        printf("Digite o novo telefone do hotel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.telefone_hotel);

                        alteracao_dados_hotel(hotel, 7, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 8:
                        printf("Digite o novo e-mail do hotel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.email_hotel);

                        alteracao_dados_hotel(hotel, 8, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 9:
                        printf("Digite o novo nome do responsÃ¡vel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.nome_responsavel);

                        alteracao_dados_hotel(hotel, 9, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 10:
                        printf("Digite o novo telefone do responsÃ¡vel: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.telefone_responsavel);

                        alteracao_dados_hotel(hotel, 10, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 11:
                        printf("Digite o novo horÃ¡rio de check-in: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.check_in);

                        alteracao_dados_hotel(hotel, 11, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 12:
                        printf("Digite o novo horÃ¡rio de check-out: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.check_out);

                        alteracao_dados_hotel(hotel, 12, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    case 13:
                        printf("Digite a nova margem de lucro de produtos vendidos: ");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.margem_lucro);

                        alteracao_dados_hotel(hotel, 13, cod_alteracao);

                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("\nDados alterados com sucesso!\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar(); 
                    break;
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                                    }

                break;
                
//EXCLUSAO DE DADOS                
        case 3:
            control_salvar=0;//ressetando o controle de salvamento
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o cÃ³digo do hotel que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_hotel(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_hotel(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }

        break;
//SALVAR        
        case 4:
            control_salvar = salvar_hotel();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do hotel\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
//CONSULTA        
        case 5:
                printf("\nDeseja consultar o  hotel pela:\n"
                        "1.Codigo\n"
                        "2.Nome fantasia\n"
                        "3.CNPJ\n");
                printf("Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela    
                switch(menu){
                    case 1:
                        printf("Digite o cÃ³digo do hotel que deseja consultar: ");
                        scanf("%d", &hotel.cod);
                    break;

                    case 2:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o nome do hotel que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.nome_fantasia);
                    break;

                    case 3:
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite o CPF do hotel que deseja consultar:");
                        scanf("%[a-z A-Z 0-9 , . - \b]s", hotel.cnpj);
                    break;                               
                    
                    default:
                        printf("\nOpcao Invalida\n");
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                             }
            system("clear||cls");//comando pra limpar a tela    
            printf("\n===HOTEL===\n");
            tam = tam_do_array_hotel();//chamando a funcao do tamanho para imprimir
            control_cod=0;//redefinindo o codigo de controle para controle da consulta
            for(i=0;i<tam;i++){
                hotel_con = consulta_hotel(hotel, menu, i);  
                if(hotel_con.cod!=-1){
                printf("\nNome fantasia: %s\n"
                       "CÃ³digo: %d\n"
                        "RazÃ£o social: %s\n"
                        "InscriÃ§Ã£o estadual: %s\n"
                        "CNPJ: %s\n"
                       "EndereÃ§o completo: %s\n"                       
                        "Telefone: %s\n"
                        "E-mail: %s\n"
                        "Nome do responsÃ¡vel: %s\n"
                        "Telefone do responsÃ¡vel: %s\n"
                        "HorÃ¡rio de check-in: %s\n"
                        "HorÃ¡rio de check-out: %s\n"
                        "Margem de lucro de produtos vendidos: %s\n", hotel_con.nome_fantasia,
                                         hotel_con.cod, 
                                         hotel_con.razao_social, 
                                         hotel_con.inscricao_estadual, hotel_con.cnpj, hotel_con.endereco_completo,
                        hotel_con.telefone_hotel, hotel_con.email_hotel, hotel_con.nome_responsavel,
                        hotel_con.telefone_responsavel, hotel_con.check_in, hotel_con.check_out, hotel_con.margem_lucro);
                control_cod++;
                                    }
                                }
            if(control_cod==0){
                printf("\nNÃ£o foi achado nenhum dado correspondente\n");
                                }
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nAperte qualquer tecla para continuar...\n");
                getchar();   
        break;        
        
//SAIR        
        case 6:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_hotel();
                    if(control_salvar==1){
                        menu=6;
                        sair_hotel();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do hotel\n");
                            }             
                }else{
                    menu=6;
                    sair_hotel();
                        }            
            }else{
                sair_hotel();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
    }
    }while(menu!=6);

    return;
};
//========================================== RESERVA ====================================================
void menu_reserva(){
    
    dados_reserva reserva, reserva_pesquisa;
    dados_categoria categoria, categoria_pesquisa;
    dados_acomodacao acomodacao, acomodacao_pesquisa;
    int control_cod=0, menu, i, tam, cod_alteracao, j, control_salvar=1, tipo=0;
    char sub_menu[8], data_entrada[11], data_saida[11];
    
    control_cod=inicializacao_categoria();//funcao para ler o arquivo de categoria    
    //verificando se os arquivos contem dados
    if(control_cod!=-1){
        control_cod=inicializacao_acomodacao();//funcao para ler o arquivo de acomodacao
                        }
    if(control_cod!=-1){
        control_cod=inicializacao_reserva();//funcao para ler o arquivo de reserva
                        }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua resposta: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }
    
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("     ");
    time_atual();
    printf("\n ========== Menu ===========\n"
           " == 1. Reservar           ==\n"
           " == 2. Consultar Reservas ==\n"
           " == 3. Cancelar Reserva   ==\n"
           " == 4. Salvar             ==\n"
           " == 5. Sair               ==\n"
           " ===========================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    system("clear||cls");//comando pra limpar a tela
    switch(menu){        
        case 1:
            control_salvar=0;
            printf("Deseja pesquisar a reserva por:\n"
                    "1. Data de reserva\n"
                    "2. Categoria da acomodacao\n"
                    "3. Quantidade de hospedes\n"
                    "4. Tipo de facilidade\n"
                    "Digite a ou as opcoes, separadas por ',': ");
            scanf("%s", sub_menu);
            
            if(strchr(sub_menu,'1')!=NULL){
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite a data de entrada da reserva, separando as datas com '/'. (EX: 02/04/2021): ");
                scanf("%[0-9 / \b]s", data_entrada);
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite a data de saida da reservada mesma forma: ");
                scanf("%[0-9 / \b]s", data_saida);               
                                            }
            
            if(strchr(sub_menu,'2')!=NULL){
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite o nome da categoria da acomodacao: ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", categoria.nome);
                                            }
            
            if(strchr(sub_menu,'3')!=NULL){
                printf("Digite a quantidade de adultos: ");
                scanf("%d", &categoria.hospede[0]);
                printf("Digite a quantidade de crianca: ");
                scanf("%d", &categoria.hospede[1]);
                                            }
            
            if(strchr(sub_menu,'4')!=NULL){
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite os tipos de facilidades separadas por ',': ");
                scanf("%[a-z A-Z 0-9 , . - \b]s", acomodacao.facilidades);
                                            }
            
            tam = tam_do_array_acomodacao();
            control_cod=0;
            system("clear||cls");//comando pra limpar a tela
            printf("===== ACOMODACOES DISPONIVEIS =====\n");
            for(i=0;i<tam;i++){
                acomodacao_pesquisa = acomodacao_reserva(acomodacao, categoria, data_entrada, data_saida, i, sub_menu);
                if(acomodacao_pesquisa.cod!=-1){
                //Buscando o codigo da categoria e definindo o indice a procurar
                cod_alteracao = verificacao_indice_categoria(acomodacao_pesquisa.categoria);
                //definindo o codigo da struct de categoria
                categoria_pesquisa.cod = acomodacao_pesquisa.categoria;
                //Buscando o nome da categoria
                categoria_pesquisa = consulta_categoria(categoria_pesquisa, 1, cod_alteracao, 0, 0);
                printf("\nCódigo: %d\n"
                       "Número do quarto: %d\n"
                       "Descricao: %s\n"
                       "Facilidades: %s\n"
                       "Categoria da acomodacao: %s\n"
                       "Preco da Diaria: R$ %.2f\n", acomodacao_pesquisa.cod,
                                                     acomodacao_pesquisa.num_quarto,
                                                     acomodacao_pesquisa.descricao, 
                                                     acomodacao_pesquisa.facilidades, 
                                                     categoria_pesquisa.nome,
                                                     categoria_pesquisa.valor_diaria);
                printf("==================================\n");
                control_cod++;
                                                    }
                                }
            if(control_cod==0){
                printf("\nNenhum quarto disponivel para essa pesquisa");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nAperte qualquer tecla para continuar...\n");
                getchar();
                
            }else{
                printf("\nEsses são os quartos disponiveis\n");
                printf("\nDigite o numero do quarto que deseja reservar, ou digite -1 para sair: ");
                scanf("%d", &reserva.acomodacao);
                if(reserva.acomodacao!=-1){
                    system("clear||cls");//comando pra limpar a tela
                    printf("Digite o código do cliente: ");
                    scanf("%d", &reserva.cod_cliente);
                    
                    if(strchr(sub_menu,'1')==NULL){
                        do{
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data de entrada da reserva, separando as datas com '/'. (EX: 02/04/2021): ");
                            scanf("%[0-9 / \b]s", data_entrada);
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data de saida da reservada mesma forma: ");
                            scanf("%[0-9 / \b]s", data_saida); 
                            
                            acomodacao.cod=0;
                            
                            control_cod = verificacao_reserva(acomodacao, reserva, data_entrada, data_saida);
                                
                            if(control_cod==-1){
                                printf("\nData nao disponivel\n");
                                                }
                                                
                        }while(control_cod==-1);
                                                    }

                    control_cod = cadastro_reserva(reserva, data_entrada, data_saida);
                    
                    printf("\nReserva efetuada com sucesso!\n");
                    printf("Código da reserva: %d\n", control_cod);
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("\nAperte qualquer tecla para continuar...\n");
                    getchar();
                                                }
                    }
        break;
//CONSULTA       
        case 2:
            printf("\nDeseja consultar por:"
                   "\n 1.Código da reserva"
                   "\n 2.Código do cliente"
                   "\n 3.Data de chegada e saida"
                   "\n 4.Quarto da Acomodacao"
                    "\nDigite sua Opcao: ");
            scanf("%d", &menu);
            
            switch(menu){
                case 1:
                    printf("Digite o código da reserva: ");
                    scanf("%d", &reserva.cod);
                break;
                
                case 2:
                    printf("Digite o código do cliente:");
                    scanf("%d", &reserva.cod_cliente);
                break;
                
                case 3:
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Digite a data de entrada da reserva, separando as datas com '/'. (EX: 02/04/2021): ");
                    scanf("%[0-9 / \b]s", data_entrada);
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Digite a data de saida da reservada mesma forma: ");
                    scanf("%[0-9 / \b]s", data_saida);
                break;
                
                case 4:
                    printf("Digite o numero do quarto da acomodacao:");
                    scanf("%d", &reserva.acomodacao);
                break;
                
                default:
                    printf("Opcao Invalida");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                break;
                            }
                
                tam = tam_do_array_reserva();
                control_cod=0;
                system("clear||cls");//comando pra limpar a tela
                printf("=========RESERVAS==========\n");
                for(i=0;i<tam;i++){
                    reserva_pesquisa = consulta_reserva(reserva, data_entrada, data_saida, i, menu);
                    if(reserva_pesquisa.cod!=-1){
                        printf("\n Código: %d\n"
                               " Número do quarto: %d\n"
                               " Código do cliente: %d\n",reserva_pesquisa.cod,
                                                          reserva_pesquisa.acomodacao,
                                                          reserva_pesquisa.cod_cliente);
                        printf(" Data de entrada: ");
                            for(j=0;j<3;j++){
                                printf("%d", reserva_pesquisa.dia_chegada[j]); 
                                if(j!=2){
                                    printf("/");
                                        }
                                                }
                        printf("\n");
                        printf(" Data de saida: ");
                            for(j=0;j<3;j++){
                                printf("%d", reserva_pesquisa.dia_saida[j]); 
                                if(j!=2){
                                    printf("/");
                                        }
                                                }
                        control_cod++;
                        printf("\n\n===========================\n");
                                                        }
                                }
            if(control_cod=0){
                printf("\nNão foi achado nenhum dado correspondente");
                                }
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("\nAperte qualquer tecla para continuar...\n");
            getchar();
                       
        break;
//CANCELAR RESERVA       
        case 3:
                control_salvar=0;
                cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o código da reserva que deseja cancelar: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado    
                    cod_alteracao = verificacao_indice_reserva(cod_alteracao); 
                    
                    if(cod_alteracao==-1){
                    printf("Código nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                            }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_reserva(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nCancelado com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }          
        break;
        
        case 4:
            control_salvar = salvar_reserva();
                if(control_salvar==1){
                     //ambos os dados foram salvos
                    printf("\nDados salvos com sucesso!\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                }else{
                    printf("\nErro: ao salvar os dados da reserva\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                            }
        break;
        
        case 5:
            if(control_salvar==0){
                printf("\nDados não salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                        control_salvar = salvar_reserva();
                        if(control_salvar==1){
                            menu=5;
                            sair_reserva();
                            sair_acomodacao();
                            sair_categoria();
                            printf("\nDados salvos com sucesso!\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                        }else{
                            menu=0;
                            printf("\nErro: ao salvar os dados da reserva\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                                }               
                }else{
                    menu=5;
                    sair_reserva();
                    sair_acomodacao();
                    sair_categoria();
                        }

                }else{
                    sair_reserva();
                    sair_acomodacao();
                    sair_categoria();
                        }
        break;
        
        default:
            printf("\nOpcao Invalida\n");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
        break;
                }   
    }while(menu!=5); 
    
    return;
}
//====================================================== TRANSACOES =========================================================
void menu_checkin(){
    
    dados_reserva reserva, reserva_pesquisa;
    dados_checkin checkin, checkin_pesquisa;
    dados_hospede hospede, hospede_pesquisa;
    int control_cod, menu, i, tam, cod_alteracao, control_salvar=1;
    char hora[6];
    float valor_diaria;
    
    control_cod = inicializacao_checkin();
    if(control_cod!=-1){
        control_cod = inicializacao_hospede();
                        }
    if(control_cod!=-1){
        control_cod = inicializacao_reserva();
                        }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            } 
                        }
    
    system("clear||cls");//comando pra limpar a tela
    do{
    printf(" ===========CHECK-IN===========\n"
           " == 1.Fazer check-in         ==\n"
           " == 2.Consutar               ==\n"
           " == 3.Excluir                ==\n"
           " == 4.Salvar                 ==\n"
           " == 5.Sair                   ==\n"
           " ==============================\n"
           " Digite sua opcao: ");
    scanf("%d", &menu);
    system("clear||cls");//comando pra limpar a tela
    switch(menu){
        case 1:
        control_salvar=0;
            do{
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Digite o número do CPF do cliente: ");
                scanf("%[0-9 - \b]s", hospede.cpf);

                tam = tam_do_array_hospede();
                for(i=0;i<tam;i++){
                    hospede_pesquisa = consulta_hospede(hospede, 3, i);

                    if(hospede_pesquisa.cod!=-1){
                        reserva.cod_cliente=hospede_pesquisa.cod;
                        tam = tam_do_array_reserva();
                        for(i=0;i<tam;i++){
                            reserva_pesquisa = consulta_reserva(reserva, 0, 0, i, 2);

                            if(reserva_pesquisa.cod!=-1){
                                checkin.cod_hospede=hospede_pesquisa.cod;
                                checkin.cod_reserva=reserva_pesquisa.cod;
                                //definindo a quantidade de diarias
                                if(reserva_pesquisa.dia_saida>reserva_pesquisa.dia_chegada){
                                    checkin.diarias = ((reserva_pesquisa.dia_saida)-(reserva_pesquisa.dia_chegada));
                                }else{
                                    checkin.diarias = ((reserva_pesquisa.dia_chegada)-(reserva_pesquisa.dia_saida));
                                }
                                break;
                                                            }
                                            }
                        break;
                                                    }
                                    }
                if(hospede_pesquisa.cod==-1){
                    system("clear||cls");//comando pra limpar a tela
                    printf("CPF não cadastrado\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                                                }

                if(reserva_pesquisa.cod==-1){
                    system("clear||cls");//comando pra limpar a tela
                    printf("Reserva não encontrada\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                                                }          

                }while(hospede.cod==-1 && reserva.cod==-1);

                setbuf(stdin, NULL);//Ressetando o buffer
                printf("\nDigite a hora de entrada do check-in ':'. (EX: 12:00): ");
                scanf("%[0-9 : \b]s", hora);

                printf("\nDeseja pagar no:\n"
                        "1. Check-Out\n"
                        "2. Check-In\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);

                switch(menu){
                    case 1:
                        checkin.opcao_pagamento=menu;
                        checkin.valor = consulta_pagamento_checkin(reserva);
                    break;

                    case 2:
                        checkin.opcao_pagamento=menu;
                    break;

                    default:
                        printf("Opcao Invalida\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;
                                }
                
                control_cod = cadastro_checkin(checkin, hora);
                
                system("clear||cls");//comando pra limpar a tela
                printf("Check-In feito com sucesso!\n");
                printf("Código do check-in: %d\n", control_cod);
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
                
                if(checkin.opcao_pagamento==2){
                    menu_controle_caixa(checkin.valor, 1, checkin.cod_reserva);
                                                }
        break;
        
        case 2: 
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Digite o CPF do cliente que deseja consultar o checkin: ");
            scanf("%[0-9 - \b]s", hospede.cpf);
            
            tam = tam_do_array_hospede();
                for(i=0;i<tam;i++){
                    hospede_pesquisa = consulta_hospede(hospede, 3, i);

                    if(hospede_pesquisa.cod!=-1){
                        tam = tam_do_array_checkin();
                        checkin.cod_hospede = hospede_pesquisa.cod; 
                        for(i=0;i<tam;i++){
                            checkin_pesquisa = consulta_checkin(checkin, 2, i);
                            
                            if(checkin_pesquisa.cod!=-1){
                                printf("Código: %d\n"
                                       "Código do Hospede: %d\n"
                                       "Código da Reserva: %d\n",checkin_pesquisa.cod
                                                                ,checkin_pesquisa.cod_hospede
                                                                ,checkin_pesquisa.cod_reserva);
                                printf("Hora check-in: %d:%d\n", checkin_pesquisa.hora[0], checkin_pesquisa.hora[1]);
                                if(checkin.opcao_pagamento==1){
                                    printf("Opcao de Pagamento: no check-out\n");
                                }else{
                                    printf("Opcao de Pagamento: no check-in\n");
                                }
                                printf("Diarias: %d", checkin_pesquisa.diarias);
                                
                                break;
                                                        }
                                            }
                        break;
                                                }
                                    }
        break;
        
        case 3:
            control_salvar=0;
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o codigo do checkin que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_checkin(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_checkin(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }
        break;
        
        case 4:
            control_salvar = salvar_checkin();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do check-in\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
        case 5:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_checkin();
                    if(control_salvar==1){
                        menu=5;
                        sair_checkin();
                        sair_hospede();
                        sair_reserva();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do check-in\n");
                            }             
                }else{
                    menu=5;
                    sair_checkin();
                    sair_hospede();
                    sair_reserva();
                        }            
            }else{
                sair_checkin();
                sair_hospede();
                sair_reserva();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;

                }
    }while(menu!=5);
        
    return;
};

void menu_checkout(){
    
    dados_checkout checkout, checkout_pesquisa;
    dados_checkin checkin, checkin_pesquisa;
    dados_hospede hospede, hospede_pesquisa;
    int control_cod=0, menu, i, tam, cod_alteracao, control_salvar=1;
    char *hora;
    
    control_cod = inicializacao_checkin();
    if(control_cod!=-1){
        control_cod = inicializacao_checkout();
                        }
    if(control_cod!=-1){
        control_cod = inicializacao_hospede();
                        }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            } 
                        }
    
    do{
    system("clear||cls");//comando pra limpar a tela
    printf(" ===========CHECK-OUT===========\n"
           " == 1.Fazer check-out         ==\n"
           " == 2.Consutar                ==\n"
           " == 3.Excluir                 ==\n"
           " == 4.Salvar                  ==\n"
           " == 5.Sair                    ==\n"
           " ===============================\n"
           " Digite sua opcao: ");
    scanf("%d", &menu);
    system("clear||cls");//comando pra limpar a tela
    switch(menu){
        case 1:
    control_salvar=0;
    do{
        setbuf(stdin, NULL);//Ressetando o buffer
        printf("Digite o número do CPF do cliente: ");
        scanf("%[0-9 - \b]s", hospede.cpf);
        
        tam = tam_do_array_hospede();
        for(i=0;i<tam;i++){
            hospede_pesquisa = consulta_hospede(hospede, 3, i);
            
            if(hospede_pesquisa.cod!=-1){
                checkin.cod_hospede=hospede_pesquisa.cod;                
                tam = tam_do_array_checkin();
                
                for(i=0;i<tam;i++){
                    checkin_pesquisa = consulta_checkin(checkin, i, 2);
                            
                    if(checkin_pesquisa.cod!=-1){
                        checkout.cod=checkin_pesquisa.cod;
                        checkout.cod_reserva=checkin_pesquisa.cod_reserva;
                        checkout.cod_hospede=checkin_pesquisa.cod_hospede;
                        for(i=0;i<3;i++){
                        checkout.hora[i]=checkin_pesquisa.hora[i];
                                        }
                        checkout.diarias=checkin_pesquisa.diarias;
                        checkout.valor=checkin_pesquisa.valor;
                        checkout.opcao_pagamento=checkin_pesquisa.opcao_pagamento;
                        break;
                                                }
                                    }
                                        }
                break;
                            }
        if(hospede_pesquisa.cod==-1){
            system("clear||cls");//comando pra limpar a tela
            printf("CPF não cadastrado\n");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
                                        }
        
        if(checkin.cod==-1){
            system("clear||cls");//comando pra limpar a tela
            printf("Check-in não encontrado\n");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
                                    }
                                       
        }while(hospede.cod==-1 || checkin.cod==-1);

        setbuf(stdin, NULL);//Ressetando o buffer
        printf("Digite a hora saida do check-out ':'. (EX: 11:00): ");
        scanf("%[0-9 : \b]s", hora);    
        
        cadastro_checkout(checkout, hora);

        system("clear||cls");//comando pra limpar a tela
        printf("Check-Out feito com sucesso!");
        setbuf(stdin, NULL);//Ressetando o buffer
        printf("\nAperte qualquer tecla para continuar...\n");
        getchar();
        
        if(checkout.opcao_pagamento==1){
            menu_controle_caixa(checkout.valor, 1, checkout.cod_reserva);
                                        }
        break;
        
        case 2: 
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Digite o CPF do cliente que deseja consultar o check-out: ");
            scanf("%[0-9 - \b]s", hospede.cpf);
            
            tam = tam_do_array_hospede();
                for(i=0;i<tam;i++){
                    hospede_pesquisa = consulta_hospede(hospede, 3, i);

                    if(hospede_pesquisa.cod!=-1){
                        tam = tam_do_array_checkout();
                        checkout.cod_hospede = hospede_pesquisa.cod; 
                        for(i=0;i<tam;i++){
                            checkout_pesquisa = consulta_checkout(checkout, 2, i);
                            
                            if(checkout_pesquisa.cod!=-1){
                                printf("Código: %d\n"
                                       "Código do Hospede: %d\n"
                                       "Código da Reserva: %d\n",checkout_pesquisa.cod
                                                                ,checkout_pesquisa.cod_hospede
                                                                ,checkout_pesquisa.cod_reserva);
                                printf("Hora check-in: %d:%d\n", checkout_pesquisa.hora[0], checkout_pesquisa.hora[1]);
                                if(checkout.opcao_pagamento==1){
                                    printf("Opcao de Pagamento: no check-out\n");
                                }else{
                                    printf("Opcao de Pagamento: no check-in\n");
                                }
                                printf("Diarias: %d", checkout_pesquisa.diarias);
                                
                                break;
                                                        }
                                            }
                        break;
                                                }
                                    }
        break;
        
        case 3:
            control_salvar=0;
            cod_alteracao=-1;
                while(cod_alteracao==-1){
                    printf("Digite o codigo do checkout que deseja excluir: ");
                    scanf("%d", &cod_alteracao);
                    //verificando o codigo digitado 
                    cod_alteracao = verificacao_indice_checkout(cod_alteracao);
                    
                    if(cod_alteracao==-1){
                    printf("CÃ³digo nao existente\n");
                    printf("Digite novamente ou digite -1 para sair\n");
                                        }
                                           }
                if(cod_alteracao!=-1){
                    control_cod = exclusao_dados_checkout(cod_alteracao);
                    if(control_cod==0){
                        printf("\nERRO: ao realocar a memoria!\n"); 
                    }else{
                        printf("\nExcluido com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }
                                        }
        break;
        
       
        case 4:
            control_salvar = salvar_checkout();
            if(control_salvar==1){
                //ambos os dados foram salvos
                printf("\nDados salvos com sucesso!\n");
                setbuf(stdin, NULL);//Ressetando o buffer
                printf("Aperte qualquer tecla para continuar...\n");
                getchar();
            }else{
                printf("\nErro: ao salvar os dados do check-out\n");
                if(control_salvar==-1){
                printf("Erro na abertura do Arquivo!\n");
                                        }
                    }
        break;
        
        case 5:
            if(control_salvar==0){
                printf("\nDados nÃ£o salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    control_salvar = salvar_checkout();
                    if(control_salvar==1){
                        menu=5;
                        sair_checkout();
                        sair_checkin();
                        sair_hospede();
                        printf("\nDados salvos com sucesso!\n");                       
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados do check-out\n");
                            }             
                }else{
                    menu=5;
                    sair_checkout();
                    sair_checkin();
                    sair_hospede();
                        }            
            }else{
                sair_checkout();
                sair_checkin();
                sair_hospede();
                    }
        break;
        
        default:
            printf("\nOpcao nao valida\n");
        break;
                    }
    }while(menu!=5);
        
    return;   
}

void menu_saida_produtos(){
    
    dados_produto produto, produto_pesquisa;
    dados_hospede hospede;
    dados_saida_produtos saida_produto;
    int tam, i, menu, control_cod, tam_quantd=0, quantd[50];
    float total=0;
    char opcao[50];
    
    control_cod = inicializacao_produto();
    if(control_cod!=-1){
        control_cod = inicializacao_hospede();
                        }
    if(control_cod!=-1){
        control_cod = inicializacao_saida_produtos();
                        }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua opcao: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            } 
                        }
    
    tam = tam_do_array_produto();
    
    system("clear||cls");//comando pra limpar a tela
    printf(" Lista de Produtos:\n\n");
    for(i=0;i<tam;i++){
        produto = consulta_produto(produto, 8, i);
        printf(" %d. %s\n", produto.cod, produto.descricao);
                        }
    setbuf(stdin, NULL);//Ressetando o buffer
    printf("\nDigite o codigo do/s produto/s que deseja, caso varios utilize ',': ");
    scanf("%[ , 0-9]s", opcao);
    
    system("clear||cls");//comando pra limpar a tela    
    char *token = strtok(opcao, ",");    
    if(token!=NULL){
        while(token!=NULL){
            do{
                produto.cod = atoi(token);
                for(i=0;i<tam;i++){
                    produto_pesquisa = consulta_produto(produto, 1, i);
                    if(produto_pesquisa.cod!=-1){
                        break;
                                                    }
                                    }
                printf("Digite a quantidade do produto %s: ", produto_pesquisa.descricao);
                scanf("%d", &quantd[tam_quantd]);
                
                //igualando a quantidade digitada pelo usuario
                produto_pesquisa.estoque=quantd[tam_quantd];
                //procurando o produto e comparando o estoque
                control_cod = verificacao_indice_produto(produto_pesquisa.cod);
                control_cod = estoque_produto(produto_pesquisa, control_cod);
                
                if(control_cod==-1){
                    system("clear||cls");//comando pra limpar a tela
                    printf("Estoque Insuficiente!\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                                    }
            }while(control_cod==-1);
            //calculando o preco do produto
            total = total + (quantd[tam_quantd]*produto_pesquisa.preco_venda);
            //mudando o estoque do produto
            control_cod = verificacao_indice_produto(produto_pesquisa.cod);
            alteracao_dados_produto(produto_pesquisa, 3, control_cod);
            tam_quantd++;
            token=strtok(NULL,",");
                            }
    //caso seja apenas um produto
    }else{
        do{
                produto.cod = atoi(token);
                for(i=0;i<tam;i++){
                    produto_pesquisa = consulta_produto(produto, 1, i);
                                    }
                printf("Digite a quantidade do produto %s: ", produto_pesquisa.descricao);
                scanf("%d", &quantd[tam_quantd]);
                
                //igualando a quantidade digitada pelo usuario
                produto_pesquisa.estoque=quantd[tam_quantd];
                //procurando o produto e comparando o estoque
                control_cod = verificacao_indice_produto(produto_pesquisa.cod);
                control_cod = estoque_produto(produto_pesquisa, control_cod);
                
                if(control_cod==-1){
                    system("clear||cls");//comando pra limpar a tela
                    printf("Estoque Insuficiente!\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                                    }
            }while(control_cod==-1);
            //calculando o preco do produto
            total = total + (quantd[tam_quantd]*produto_pesquisa.preco_venda);
            //mudando o estoque do produto
            control_cod = verificacao_indice_produto(produto_pesquisa.cod);
            alteracao_dados_produto(produto_pesquisa, 3, control_cod);
            tam_quantd++;
            token=strtok(NULL,",");   
    }
    system("clear||cls");//comando pra limpar a tela
    setbuf(stdin, NULL);//Ressetando o buffer
    printf("Digite o CPF do cliente: ");
    scanf("%[ - 0-9]s", saida_produto.CPF);
    
    printf("\nForma de pagamento:\n"
            " 1. A vista\n"
            " 2. Mandar para a conta\n"
            "Digite sua Opcao: ");
    scanf("%d", &menu);
    switch(menu){
        case 1:
            saida_produto.forma_pagamento=menu;
            saida_produto.tam_conta=tam_quantd;
            saida_produto.forma_pagamento=menu;
            saida_produto.status=1;
            saida_produto.total=total;
            //salvando a conta temporariamente para mandar para o caixa
            control_cod = cadastro_saida_produtos(saida_produto, opcao, quantd);
            
            menu_controle_caixa(total, 1, control_cod);
            
            //exluindo a conta da saida
            control_cod = verificacao_indice_saida_produtos(control_cod);
            exclusao_dados_saida_produtos(control_cod);
        break;
            
        case 2:
            system("clear||cls");//comando pra limpar a tela
            saida_produto.tam_conta=tam_quantd;
            saida_produto.forma_pagamento=menu;
            saida_produto.status=1;
            saida_produto.total=total;
            cadastro_saida_produtos(saida_produto, opcao, quantd);
            printf("Conta salva com sucesso!\n");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
        break;
            
        default:
            printf("Opcao Invalida");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
        break;
                }
}

void menu_controle_caixa(float valor, int tipo, int cod){

    dados_lancamento lancamento;
    dados_retirada retirada;
    dados_saida_produtos saida_produto;
    int control_cod=0, menu, control_salvar=1, parcelas, tam, i;
    char data[11];
   
    control_cod=inicializacao_caixa();//funcao para ler o arquivo de caixa
    if(control_cod==-1){    
        control_cod=inicializacao_saida_produtos();//funcao para ler o arquivo de caixa
                            }
    if(control_cod==-1){
        printf("\nERRO: ao abrir o arquivo\n");
        printf("Deseja continuar mesmo assim?\n"
               "1.Sim\n"
               "2.Nao\n"
               "Digite sua resposta: ");
        scanf("%d", &control_cod);
        
        if(control_cod==2){
            return;
                            }
                        }
    do{
    system("clear||cls");//comando pra limpar a tela
    printf("     ");
    time_atual();
    printf("\n ========== Menu ===========\n"
           " == 1. Pagamento          ==\n"
           " == 2. Retirada           ==\n"
           " == 3. Consulta           ==\n"
           " == 4. Salvar             ==\n"
           " == 5. Sair               ==\n"
           " ===========================\n\n");
    printf("Digite a opcao: ");
    scanf("%d", &menu);
    system("clear||cls");//comando pra limpar a tela
    
    switch(menu){   
        case 1:
            if(tipo==0){
                system("clear||cls");//comando pra limpar a tela
                printf("Deseja fazer o pagamento por:\n"
                        "1. Dinheiro\n"
                        "2. Crédito/Debito\n"
                        "Digite sua Opcao: ");
                scanf("%d", &menu);

                switch(menu){
                    case 1:
                        printf("Digite a quantia que deseja dar o lancamento: ");
                        scanf("%f", &lancamento.valor);
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a descricao desse pagamento: ");
                        scanf("%[ - , / a-z A-Z 0-9 ]s", lancamento.fonte);
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                        scanf("%[ / 0-9 ]s", data);
                        
                        cadastro_dados_lancamento(lancamento, data);
                        system("clear||cls");//comando pra limpar a tela
                        printf("Lancamento feito com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;

                    case 2:
                        printf("O pagamento é:\n"
                                "1. Credito\n"
                                "2. Debito\n"
                                "Digite sua Opcao: ");
                        scanf("%d", &menu);
                        
                        if(menu==1){
                            printf("Digite a quantia que deseja dar o lancamento: ");
                            scanf("%f", &lancamento.valor);
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a descricao desse pagamento: ");
                            scanf("%[ - , / a-z A-Z 0-9 ]s", lancamento.fonte);
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                            scanf("%[ / 0-9 ]s", data);
                            printf("Digite quantas parcelas deseja: ");
                            scanf("%d", &parcelas);
                            
                            //contas_pagar(parcelas, 1);
                            
                            system("clear||cls");//comando pra limpar a tela
                            printf("Lancamento feito com sucesso!\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                        }else{
                            printf("Digite a quantia que deseja dar o lancamento: ");
                            scanf("%f", &lancamento.valor);
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a descricao desse pagamento: ");
                            scanf("%[ - , / a-z A-Z 0-9 ]s", lancamento.fonte);
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                            scanf("%[ / 0-9 ]s", data);
                            
                            //contas_pagar(0, 2);
                            
                            system("clear||cls");//comando pra limpar a tela
                            printf("Lancamento feito com sucesso!\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                        }
                    break;
                                }
//caso o pagamento seja de reservas e produtos
            }else{
                system("clear||cls");//comando pra limpar a tela
                printf("Deseja fazer o pagamento por:\n"
                        "1. Dinheiro\n"
                        "2. Crédito/Debito\n"
                        "Digite sua Opcao: ");
                scanf("%d", &menu);

                switch(menu){
                    case 1:
                        printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                        scanf("%[ / 0-9 ]s", data);
                        lancamento.valor=valor;
                        lancamento.tipo=tipo;
                        //transformando o codigo do produto ou reserva na fonte
                        //itoa(cod, lancamento.fonte, 10);
                        cadastro_dados_lancamento(lancamento, data);
                        printf("Lancamento feito com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    break;

                    case 2:
                        printf("O pagamento é:\n"
                                "1. Credito\n"
                                "2. Debito\n"
                                "Digite sua Opcao: ");
                        scanf("%d", &menu);
                        
                        if(menu==1){
                            //itoa(cod, lancamento.fonte, 10);
                            lancamento.valor=valor;
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                            scanf("%[ / 0-9 ]s", data);
                            printf("Digite quantas parcelas deseja: ");
                            scanf("%d", &parcelas);
                            
                            //contas_pagar(lancamento, parcelas, 1);
                            
                            system("clear||cls");//comando pra limpar a tela
                            printf("Lancamento feito com sucesso!\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                        }else{
                            //itoa(cod, lancamento.fonte, 10);
                            lancamento.valor=valor;
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Digite a data desse lancamento. Ex: 09/04/2020: ");
                            scanf("%[ / 0-9 ]s", data);
                            
                            //contas_pagar(lancamento, 0, 2);
                            
                            system("clear||cls");//comando pra limpar a tela
                            printf("Lancamento feito com sucesso!\n");
                            setbuf(stdin, NULL);//Ressetando o buffer
                            printf("Aperte qualquer tecla para continuar...\n");
                            getchar();
                            }
                    break;
                                }
                }
        break;
        
        case 2:
            printf("Digite a quantia que deseja fazer a retirada: ");
            scanf("%f", &retirada.valor);
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Digite a descricao dessa retirada: ");
            scanf("%[ - , / a-z A-Z 0-9 ]s", retirada.fonte);
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Digite a data desse retirada. Ex: 09/04/2020: ");
            scanf("%[ / 0-9 ]s", data);
                        
            cadastro_dados_retirada(retirada, data);
            system("clear||cls");//comando pra limpar a tela
            printf("Retirada feita com sucesso!\n");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
           
        break;
    
        case 3:
            printf("Deseja consultar:\n"
                    "1. Lancamentos\n"
                    "2. Retiradas\n"
                    "Digite sua Opcao: ");
            scanf("%d", &menu);
            
            switch(menu){
                case 1:
                    printf("Deseja Consultar os lancamentos por:\n"
                            "1. Código\n"
                            "2. Data\n"
                            "3. Tipo de Lancamento\n"
                            "4. Descricao do lancamento\n"
                            "Digite sua opcao: ");
                    scanf("%d", &menu);
                break;
                
                case 2:
                    printf("Deseja Consultar as retiradas por:\n"
                            "1. Código\n"
                            "2. Data\n"
                            "3. Descricao da retirada\n"
                            "Digite sua opcao: ");
                    scanf("%d", &menu);
                break;
            
            }
        break;
            
        case 4:
            control_salvar = salvar_dados_caixa();
                if(control_salvar==1){
                    printf("\nDados salvos com sucesso!\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                }else{
                    printf("\nErro: ao salvar os dados do caixa\n");
                    setbuf(stdin, NULL);//Ressetando o buffer
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                            }
        break;
            
        case 5:
            if(control_salvar==0){
                printf("\nDados não salvos!");
                printf("\nDeseja Salvar?\n"
                        "1.Sim\n"
                        "2.Nao\n"
                        "Digite sua opcao: ");
                scanf("%d", &menu);
                system("clear||cls");//comando pra limpar a tela
                if(menu==1){
                    //control_salvar = salvar_dados_caixa();
                    if(control_salvar==1){
                        menu=5;
                        sair_caixa();
                        printf("\nDados salvos com sucesso!\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                    }else{
                        menu=0;
                        printf("\nErro: ao salvar os dados da categoria\n");
                        setbuf(stdin, NULL);//Ressetando o buffer
                        printf("Aperte qualquer tecla para continuar...\n");
                        getchar();
                            }             
                }else{
                    menu=5;
                    sair_caixa();
                        }            
            }else{
                sair_caixa();
                    }
        break;
            
        default:
            printf("Opcao Invalida");
            setbuf(stdin, NULL);//Ressetando o buffer
            printf("Aperte qualquer tecla para continuar...\n");
            getchar();
        break;            
    }
    
    }while(menu!=5);
    
}

int main(int argc, char** argv) {
    
    int tipo=0;
    
    while(tipo==0){
    system("clear||cls");//comando pra limpar a tela
    printf(" ==========================================\n");
    printf(" == Qual tipo de dados deseja manipular: ==\n"
           " ==               1.Texto                ==\n"
           " ==               2.Binario              ==\n"
           " ==========================================\n");
    printf(" Digite sua opcao: ");
    scanf("%d", &tipo);
    
    tipo = tipo_arquivo(tipo);     
    
    if(tipo==0){
        printf("\nDado incorreto\n");
        setbuf(stdin, NULL);//Ressetando o buffer
        printf("Aperte qualquer tecla para continuar...\n");
        getchar();
                }   
                    }
    
    system("clear||cls");
    menu_principal();
    system("clear||cls");
    printf("Obrigado por Utilizar esse Sistema!");
    
    return (EXIT_SUCCESS);
}