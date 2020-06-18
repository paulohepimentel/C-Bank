#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "ArvoreB.h"

#define N 10000 /* Numero de usuarios do programa BancoP&B */

/**
 * Autor: Paulo Henrique
 */

int main(){

	TipoUsuario Pessoa;
	TipoPagina* Banco;

	FILE *Arq;

	int vNumConta[N];   /* Vetor com os numeros das contas                      */
	int vSenhaConta[N]; /* Vetor com as senhas das contas: Senha = NumConta+1   */
	float vDinheiro[N]; /* Vetor randomico com os saldos das contas             */

    int NumC=0,NumS=0;        /* Utilizado para a realização das operações bancarias */
    TipoUsuario UserOperacao; /* Utilizado para a realização das operações bancarias */
    int NOperacao=0, ResultadoPesquisa=0;
    int Loop=0;

	int i=0; /* Contador */
	int c=0; /* Auxilia na leitura do arquivo */

    char NomePessoa[50], buffer[2];

    long int comparaInsere = 0;     /*                                                  */
    long int comparaRetira = 0;     /* Variáveis que contam as comparações em cada caso */
    long int comparaPesquisa = 0;   /*                                                  */

    int altura = 0;                 /* Conta a altura da arvore                             */
    int NumInser = 0;               /* Conta o numero de inserções                          */
    int ContaTransf = 0;            /* Auxilia na realização da operação de transferencia   */
    float ValorTransferencia = 0.0; /* Auxilia na realização da operação de transferencia   */
    float ValorSaque = 0.0;         /* Auxilia na realização da operação de saque           */
    float ValorDeposito = 0.0;      /* Auxilia na realização da operação de deposito        */
    short Operacao = 0;             /* Variavel que indica qual operação será realizada     */

	srand(time(NULL));
	Inicializa(&Banco);     /* Inicializa o Sistema Bancario */

/*-- GERAÇÃO DOS VETORES DE DADOS DOS USUARIOS ----------------------------*/

    /* 1º Passo >> Geração do vetor vNumConta */
    for(i=0; i<N; i++)
		vNumConta[i] = i+10001;

	/* 2º Passo >> Geração do vetor vSenhaConta */
    for(i=0; i<N; i++)
		vSenhaConta[i] = vNumConta[i]+1;

	/* 3º Passo >> Geração do vetor vDinheiro */
    for(i=0; i<N; i++)
		vDinheiro[i] = rand()%1000 + 0.50;

/*-- LEITURA DO ARQUIVO DE ENTRADA QUE CONTEM OS NOMES DOS USUARIOS -------*/

    i=0;

    Arq = fopen("Entrada.txt","r");
    if (Arq==NULL)
        return 0;
    else{
        strcpy(NomePessoa,"");
        do{
            c = fgetc(Arq);
            if(c!=EOF && c!='\n'){
                sprintf(buffer,"%c",c);
                strcat(NomePessoa, buffer);
            }
            else{
                if(strlen(NomePessoa)!= 0){
                    /* Atribuição final dos dados de usuarios obtidos a
                    estrutura final para a inserção da mesma na arvore */
                    strcpy(Pessoa.Nome,NomePessoa);
                    Pessoa.NumeroConta = vNumConta[i];
                    Pessoa.SenhaConta = vSenhaConta[i];
                    Pessoa.Dinheiro = vDinheiro[i];

                    Insere(Pessoa, &Banco, &comparaInsere);
                    NumInser++;
                    Testa(Banco);
                    i++;
                }
                strcpy(NomePessoa,"");
            }
        }while(c != EOF);
    }
    fclose(Arq);

    /*
    printf("\n Essa e a sua arvore \n\n");
    ImprimeArvore(Banco);
    */

    /*
    printf("\nNumero de comparacoes insercao: %ld \n", comparaInsere);
    comparaInsere = 0;
    */

    altura = Altura(Banco);
    printf("\n\nAltura da arvore: %d\n",altura);
    printf("Numero de insercoes: %d\n\n\n",NumInser);

    system("PAUSE");
    system("@cls||clear"); /* Limpa a tela */


/*-- UTILIZAÇÃO DAS OPERAÇÕES BANCARIAS -----------------------------------*/

    comeco: /* loop para a tela de login */

    printf("\n<------------------------------------------------->\n");
    printf("|                 $  C-Bank  $                    |\n");
    printf("|        ONDE VOCE E A NOSSA MAIOR RIQUEZA        |\n");
    printf("<------------------------------------------------->\n");

    printf("\nPara prosseguir entre com:\n");
    printf("\nNumero da conta: ");
    scanf("%d",&NumC);
    printf("Senha: ");
    scanf("%d",&NumS);

    UserOperacao.NumeroConta = NumC;
    UserOperacao.SenhaConta = NumS;

    /* A função PesquisaConta confere a respectiva senha, se a mesma for igual
    a da entrada, as operações referentes a conta são mostradas na tela, caso
    contrário uma mensagem de erro será exibida */
    ResultadoPesquisa = PesquisaConta(UserOperacao,Banco, &comparaPesquisa);

    /*
    printf("Numero de comparacoes para pesquisa: %ld\n",comparaPesquisa);
    comparaPesquisa = 0;
    */

   system("@cls||clear"); /* Limpa a tela */

    if(ResultadoPesquisa == 0){
        printf("\n\n");
        system("PAUSE");
        system("@cls||clear"); /* Limpa a tela */
        goto comeco;
    }
    else{
        inicio: /* loop para menu de operações */

        printf("\n\nBem vindo \nNumero da conta: %d\n",UserOperacao.NumeroConta);
        printf("\n\t   MENU DE OPERACOES\n\n");
        printf("  >> 1 - Ver os dados da sua conta\n");
        printf("  >> 2 - Realizar saque\n");
        printf("  >> 3 - Realizar deposito\n");
        printf("  >> 4 - Realizar transferencia\n");
        printf("  >> 5 - Excluir conta\n");

        printf("\nEntre com o numero da operacao desejada: ");
        scanf("%d",&NOperacao);
        printf("\n");

        system("@cls||clear"); /* Limpa a tela */

        /*--------------------------- BLOCO DE OPERAÇÕES --------------------------*/

        if (NOperacao == 1){
            printf("\nOperacao 1 selecionada >> Ver os dados da sua conta\n");
            VerConta(UserOperacao,Banco);
        }
        else if (NOperacao == 2){
            printf("\nOperacao 2 selecionada >> Realizar saque\n");
            printf("\nEntre com o valor que deseja sacar: ");
            scanf("%f",&ValorSaque);

            UserOperacao.Dinheiro = ValorSaque;
            Operacao = Saque(UserOperacao,&Banco);

            if(Operacao == 1)
                printf("\nOperacao aprovada. Saque realizado com sucesso!\n");
            else
                printf("\nNão foi possivel realizar o saque. Saldo insuficiente!\n");
        }
        else if (NOperacao == 3){
            printf("\nOperacao 3 selecionada >> Realizar deposito\n");
            printf("\nEntre com o valor que deseja depositar: ");
            scanf("%f",&ValorDeposito);

            UserOperacao.Dinheiro = ValorDeposito;
            Deposito(UserOperacao,&Banco);

            printf("\nDeposito realizado com sucesso!\n");
        }
        else if (NOperacao == 4){
            printf("\nOperacao 4 selecionada >> Realizar transferencia\n");
            printf("\nEntre com o valor que deseja transferir: ");
            scanf("%f",&ValorTransferencia);

            UserOperacao.Dinheiro = ValorTransferencia;

            /* Confere se o saldo possui a quantia que se deseja tranferir */
            Operacao = Saque(UserOperacao,&Banco);

            if(Operacao == 1){
                printf("Entre com o numero da conta para transferir esse valor: ");
                scanf("%d",&ContaTransf);

                UserOperacao.NumeroConta = ContaTransf;
                Deposito(UserOperacao,&Banco);

                printf("\nOperacao aprovada. Transferencia realizada com sucesso!\n");
            }
            else
                printf("\nNão foi possivel realizar a transferencia. Saldo insuficiente!\n");
        }
        else if (NOperacao == 5){
            printf("\nOperacao 5 selecionada >> Excluir conta\n");
            Retira(UserOperacao,&Banco,&comparaInsere,&comparaRetira);
            Testa(Banco);

            /*
            printf("Numero de comparacoes para retirada: %ld\n",comparaRetira);
            comparaRetira = 0;
            */

            printf("\nA sua conta foi excluida com sucesso\n");
            printf("\n------------------------------------------------------------\n");

            goto fim; /*Caso a operação 5 seja selecionada e a conta excluida */
        }
        else
            printf("Operacao invalida\n");

        /*-------------------------------------------------------------------------*/

        printf("\n------------------------------------------------------------\n");
        printf("Deseja realizar outra operacao? [1 para sim/0 para nao e sair]  ");
        scanf("%d",&Loop);
        if(Loop == 1){
            UserOperacao.NumeroConta = NumC;
            printf("\n");
            system("PAUSE");
            system("@cls||clear"); /* Limpa a tela */
            goto inicio; /* loop para menu de operações */
        }
        else{
            fim: /*Caso a operação 5 seja selecionada e a conta excluida */
            printf("\n");
            system("PAUSE");
            system("@cls||clear"); /* Limpa a tela */
            goto comeco; /* loop para a tela de login */
        }
    }
    return 0;
}
