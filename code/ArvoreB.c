#include<stdlib.h>
#include<stdio.h>
#include "ArvoreB.h"

/**
 * Autor: Paulo Henrique
 */

void Inicializa(ApontadorPag *SistemaBancario){
    *SistemaBancario = NULL;
}

void Insere(TipoUsuario User, ApontadorPag *Ap, long int* comparaInsere){
    short Cresceu; /* Flag de controle para altura(Split) */
    TipoUsuario UserRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(User, *Ap, &Cresceu, &UserRetorno, &ApRetorno, comparaInsere);

    (*comparaInsere) ++;
    if(Cresceu){
        ApTemp = (ApontadorPag)malloc(sizeof(TipoPagina));
        ApTemp->NumItens = 1;
        ApTemp->Usuario[0] = UserRetorno;

        /* Novo referenciamento das pagina atual e pagina irmã (Com base no indice da vez */
        ApTemp->Pagina[1] = ApRetorno;
        ApTemp->Pagina[0] = *Ap;
        *Ap = ApTemp;
    }
}
void Ins(TipoUsuario User, ApontadorPag Ap, short *Cresceu, TipoUsuario *UserRetorno, ApontadorPag *ApRetorno, long int* comparaInsere){
    int i = 1;
    int j;
    ApontadorPag ApTemp;

    (*comparaInsere) ++;
    if(Ap == NULL){ /* Pagina nula -> Primeira inserção */
        *Cresceu = TRUE;
        (*UserRetorno) = User;
        (*ApRetorno) = NULL;
        return;
    }
    /* Ja achou a pagina candidata para a inserção do item. */
    /* Percorre a pagina para achar o lugar de inserção. */
    (*comparaInsere) += 2;
    while((i < Ap->NumItens) && (User.NumeroConta > Ap->Usuario[i-1].NumeroConta)){
        i++;
        (*comparaInsere) += 2;
    }


    /* Após caminhar na pagina, o Usuario a ser inserido é IGUAL ao da pagina */
    (*comparaInsere) ++;
    if(User.NumeroConta == Ap->Usuario[i-1].NumeroConta){
        printf("\nErro: Esse numero de conta ja esta em uso\n");
        *Cresceu = FALSE;
        return;
    }

    /* Caso o item inserido seja MENOR que o da pagina, correção do indice para inserção ordenada*/
    (*comparaInsere) ++;
    if(User.NumeroConta < Ap->Usuario[i-1].NumeroConta)
        i--;
    /* Chama Ins e percorre a pagina filha */
    Ins(User, Ap->Pagina[i], Cresceu, UserRetorno, ApRetorno,comparaInsere);

    (*comparaInsere) ++;
    if(!*Cresceu) /* Se Cresceu = False */
        return;
    /*Continuação da primeira chamada da função Ins */

    /* Pagina tem espaço --> Inserção na pagina */
    (*comparaInsere) ++;
    if(Ap->NumItens < MM){
        InsereNaPagina(Ap, *UserRetorno, *ApRetorno, comparaInsere);
        *Cresceu = FALSE;
        return;
    }

    /* Split: Pagina tem que ser dividida */
    ApTemp = (ApontadorPag)malloc(sizeof(TipoPagina)); /* Criação de uma nova pagina */
    ApTemp->NumItens = 0;
    ApTemp->Pagina[0] = NULL;

    (*comparaInsere) ++;
    if (i < M + 1){
        InsereNaPagina(ApTemp, Ap->Usuario[MM-1], Ap->Pagina[MM], comparaInsere); /*Primeiro utiliza a 1º pagina até encher a mesma */
        Ap->NumItens--;
        InsereNaPagina(Ap, *UserRetorno, *ApRetorno, comparaInsere);
    }
    else
        InsereNaPagina(ApTemp, *UserRetorno, *ApRetorno, comparaInsere);

    for(j = M + 2; j <= MM; j++){
        InsereNaPagina(ApTemp, Ap->Usuario[j-1], Ap->Pagina[j], comparaInsere);
        (*comparaInsere) ++;
    }

    Ap->NumItens = M;
    ApTemp->Pagina[0] = Ap->Pagina[M+1];
    *UserRetorno = Ap->Usuario[M];
    *ApRetorno = ApTemp;
}
void InsereNaPagina(ApontadorPag Ap, TipoUsuario User, ApontadorPag ApDir, long int* comparaInsere){
    short NaoAchouPosicao;  /* Flag de controle para inserção */
    int NItens;

    NItens = Ap->NumItens;

    /* Se o numero de Usuarios na pagina > 0, NaoAchouPosicao = True, senao NaoAchouPosicao = False. */
    NaoAchouPosicao = (NItens > 0);

    (*comparaInsere) ++;
    while(NaoAchouPosicao){   /* Enquanto NaoAchouPosicao é True */
        (*comparaInsere) ++;
        if (User.NumeroConta >= Ap->Usuario[NItens-1].NumeroConta){
            NaoAchouPosicao = FALSE;
            break;
        }
        /* Algoritmo de ordenação implícito */
        Ap->Usuario[NItens] = Ap->Usuario[NItens-1];
        Ap->Pagina[NItens+1] = Ap->Pagina[NItens];

        NItens--;
        (*comparaInsere) ++;
        if (NItens < 1)
            NaoAchouPosicao = FALSE;
        (*comparaInsere) ++;
    }

    Ap->Usuario[NItens] = User;
    Ap->Pagina[NItens+1] = ApDir;
    Ap->NumItens++;
}

int PesquisaConta(TipoUsuario Conta, ApontadorPag Ap, long int* comparaPesquisa){
    short i = 1;
    (*comparaPesquisa) ++;
    if (Ap == NULL){
        printf("\nEssa conta nao existe\n\n"); /* Numero de conta não existe na arvore */
        system("PAUSE");
        printf("\n");
        return 0;
    }
    (*comparaPesquisa) += 2;
    while (i < Ap->NumItens && Conta.NumeroConta > Ap->Usuario[i-1].NumeroConta){
        i++;
        (*comparaPesquisa) += 2;
    }

    (*comparaPesquisa) ++;
    if (Conta.NumeroConta == Ap->Usuario[i-1].NumeroConta){
        (*comparaPesquisa) ++;
        if(Conta.SenhaConta == Ap->Usuario[i-1].SenhaConta){
            /* Esse numero de conta de Usuario esta presente na arvore */
            return 1;
        }
        else{
            printf("\nSenha incorreta!\n\n");
            system("PAUSE");
            printf("\n");
            return 0;
        }
    }

    (*comparaPesquisa) ++;
    if (Conta.NumeroConta < Ap->Usuario[i-1].NumeroConta)
        PesquisaConta(Conta, Ap->Pagina[i-1], comparaPesquisa);
    else
        PesquisaConta(Conta, Ap->Pagina[i], comparaPesquisa);

    //return 0;
}
void VerConta(TipoUsuario Conta, ApontadorPag Ap){
    short i = 1;

    while (i < Ap->NumItens && Conta.NumeroConta > Ap->Usuario[i-1].NumeroConta)
        i++;

    if (Conta.NumeroConta == Ap->Usuario[i-1].NumeroConta){
        printf("\nNumero da conta: %d\n",Ap->Usuario[i-1].NumeroConta);
        printf("Nome do usuario: %s\n",Ap->Usuario[i-1].Nome);
        printf("Saldo atual: %.2f\n",Ap->Usuario[i-1].Dinheiro);
        return;
    }
    if (Conta.NumeroConta < Ap->Usuario[i-1].NumeroConta)
        VerConta(Conta, Ap->Pagina[i-1]);
    else
        VerConta(Conta, Ap->Pagina[i]);
}
int Saque(TipoUsuario Conta, ApontadorPag *Ap){
    short i=1;

    while (i < (*Ap)->NumItens && Conta.NumeroConta > (*Ap)->Usuario[i-1].NumeroConta)
        i++;

    if (Conta.NumeroConta == (*Ap)->Usuario[i-1].NumeroConta){
        /* verificar se é possivel fazer o saque */
        if(Conta.Dinheiro <= (*Ap)->Usuario[i-1].Dinheiro){
            (*Ap)->Usuario[i-1].Dinheiro = (*Ap)->Usuario[i-1].Dinheiro - Conta.Dinheiro;
            return 1;
        }
        else
            return 0;
    }
    if (Conta.NumeroConta < (*Ap)->Usuario[i-1].NumeroConta)
        Saque(Conta, &(*Ap)->Pagina[i-1]);
    else
        Saque(Conta, &(*Ap)->Pagina[i]);

    // return 0;
}
void Deposito(TipoUsuario Conta, ApontadorPag *Ap){
    short i = 1;

    while (i < (*Ap)->NumItens && Conta.NumeroConta > (*Ap)->Usuario[i-1].NumeroConta)
        i++;

    if (Conta.NumeroConta == (*Ap)->Usuario[i-1].NumeroConta){
        /* Para a realização do depósito não é necessário nenhuma verificação */
        (*Ap)->Usuario[i-1].Dinheiro = (*Ap)->Usuario[i-1].Dinheiro + Conta.Dinheiro;
        return;
    }
    if (Conta.NumeroConta < (*Ap)->Usuario[i-1].NumeroConta)
        Deposito(Conta, &(*Ap)->Pagina[i-1]);
    else
        Deposito(Conta, &(*Ap)->Pagina[i]);
}

void ImprimeArvore(ApontadorPag Pag){
    int n=0;
    ImprimeI(Pag, n);
}
void ImprimeI(ApontadorPag Pag, int nivel){
    int i;
    if(Pag == NULL)
        return;
    printf("Nivel %d : ", nivel);
    for(i=0; i< Pag->NumItens; i++)
        printf("%d ",Pag->Usuario[i].NumeroConta);

    putchar('\n');
    nivel++;
    for (i = 0; i <= Pag->NumItens; i++)
        ImprimeI(Pag->Pagina[i], nivel);
}

void Retira(TipoUsuario User, ApontadorPag *Ap, long int*comparaInsere, long int* comparaRetira){
    short Diminuiu; /* Flag de controle para altura(Split) */
    ApontadorPag Aux;

    Ret(User, Ap, &Diminuiu, comparaInsere, comparaRetira);

    (*comparaRetira) ++;
    if (Diminuiu && (*Ap)->NumItens == 0){  /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->Pagina[0];
        free(Aux);
    }
}
void Ret(TipoUsuario User, ApontadorPag *Ap, short *Diminuiu, long int* comparaInsere, long int* comparaRetira){
    int j, i=1;
    ApontadorPag Pag;

    (*comparaRetira) ++;
    if(*Ap == NULL){ /*Caso a arvore esteja vazia */
        printf("\nErro: Essa conta nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }
    Pag = *Ap;

    (*comparaRetira) += 2;
    while (i < Pag->NumItens && User.NumeroConta > Pag->Usuario[i-1].NumeroConta){
        i++;
        (*comparaRetira) += 2;
    }

    (*comparaRetira) ++;
    if (User.NumeroConta == Pag->Usuario[i-1].NumeroConta){

        (*comparaRetira) ++;
        if (Pag->Pagina[i-1] == NULL){   /* TipoPagina folha */
            Pag->NumItens--;

            /* Se o numero de itens na pagina < M, Diminuiu = True, senao Diminuiu = False. */
            *Diminuiu = (Pag->NumItens < M);

            for (j=i; j<= Pag->NumItens; j++){
                Pag->Usuario[j-1] = Pag->Usuario[j];
                Pag->Pagina[j] = Pag->Pagina[j+1];
                (*comparaRetira) ++;
            }
            return;
        }
        /* TipoPagina nao é folha: trocar com antecessor */
        Antecessor(*Ap, i, Pag->Pagina[i-1], Diminuiu, comparaInsere, comparaRetira);

        (*comparaRetira) ++;
        if (*Diminuiu) /* Se Diminuiu é True */
            Reconstitui(Pag->Pagina[i-1], *Ap, i-1, Diminuiu, comparaInsere, comparaRetira);
        return;
    }
    (*comparaRetira) ++;
    if (User.NumeroConta > Pag->Usuario[i-1].NumeroConta)
        i++;

    Ret(User, &Pag->Pagina[i-1], Diminuiu, comparaInsere, comparaRetira);

    (*comparaRetira) ++;
    if (*Diminuiu) /* Se Diminuiu é True */
        Reconstitui(Pag->Pagina[i-1], *Ap, i-1, Diminuiu, comparaInsere, comparaRetira);
}
void Antecessor(ApontadorPag Ap, int i, ApontadorPag ApPai, short *Diminuiu,long int* comparaInsere, long int* comparaRetira){

    (*comparaRetira) ++;
    if (ApPai->Pagina[ApPai->NumItens] != NULL){
        Antecessor(Ap, i, ApPai->Pagina[ApPai->NumItens], Diminuiu,comparaInsere,comparaRetira);
        (*comparaRetira) ++;
        if (*Diminuiu) /* Se Diminuiu é True */
            Reconstitui(ApPai->Pagina[ApPai->NumItens], ApPai, ApPai->NumItens, Diminuiu,comparaInsere, comparaRetira);
        return;
    }
    Ap->Usuario[i-1] = ApPai->Usuario[ApPai->NumItens-1];
    ApPai->NumItens--;

    /* Se o numero de itens na pagina < M, Diminuiu = True, senao Diminuiu = False. */
    *Diminuiu = (ApPai->NumItens < M);
}
void Reconstitui(ApontadorPag ApPag, ApontadorPag ApPai, int PosPai, short *Diminuiu, long int* comparaInsere, long int* comparaRetira){
    TipoPagina *Aux;
    int DispAux, j;

    (*comparaRetira) ++;
    if (PosPai < ApPai->NumItens){  /* Aux = TipoPagina a direita de ApPag */
        Aux = ApPai->Pagina[PosPai+1];
        DispAux = (Aux->NumItens - M+1) / 2;

        ApPag->Usuario[ApPag->NumItens] = ApPai->Usuario[PosPai];
        ApPag->Pagina[ApPag->NumItens + 1] = Aux->Pagina[0];
        ApPag->NumItens++;

        (*comparaRetira) ++;
        if(DispAux > 0){  /* Existe folga: transfere de Aux para ApPag */
            for (j=1; j<DispAux; j++){
                InsereNaPagina(ApPag, Aux->Usuario[j-1], Aux->Pagina[j], comparaInsere);
                (*comparaRetira) ++;
            }

            ApPai->Usuario[PosPai] = Aux->Usuario[DispAux-1];
            Aux->NumItens -= DispAux;

            for (j=0; j < Aux->NumItens; j++){
                Aux->Usuario[j] = Aux->Usuario[j+DispAux];
                (*comparaRetira) ++;
            }

            for (j=0; j <= Aux->NumItens; j++){
                Aux->Pagina[j] = Aux->Pagina[j+DispAux];
                (*comparaRetira) ++;
            }
            *Diminuiu = FALSE;
        }
        else{ /* Fusao: intercala Aux em ApPag e libera Aux */
            for (j=1; j<=M; j++){
                InsereNaPagina(ApPag, Aux->Usuario[j-1], Aux->Pagina[j],comparaInsere);
                (*comparaRetira) ++;
            }
            free(Aux);

            for (j = PosPai+1; j<ApPai->NumItens; j++){
                ApPai->Usuario[j-1] = ApPai->Usuario[j];
                ApPai->Pagina[j] = ApPai->Pagina[j+1];
                (*comparaRetira) ++;
            }

            ApPai->NumItens--;
            (*comparaRetira) ++;
            if (ApPai->NumItens >= M)
                *Diminuiu = FALSE;
        }
    }
    else{ /* Aux = TipoPagina a esquerda de ApPag */
        Aux = ApPai->Pagina[PosPai-1];
        DispAux = (Aux->NumItens - M+1) / 2;

        for (j = ApPag->NumItens; j >= 1; j--){
            ApPag->Usuario[j] = ApPag->Usuario[j-1];
            (*comparaRetira) ++;
        }
        ApPag->Usuario[0] = ApPai->Usuario[PosPai-1];

        for (j = ApPag->NumItens; j >= 0; j--){
            ApPag->Pagina[j+1] = ApPag->Pagina[j];
            (*comparaRetira) ++;
        }
        ApPag->NumItens++;

        (*comparaRetira) ++;
        if (DispAux > 0){ /* Existe folga: transf. de Aux para ApPag */
            for (j=1; j < DispAux; j++){
                InsereNaPagina(ApPag, Aux->Usuario[Aux->NumItens - j], Aux->Pagina[Aux->NumItens - j+1],comparaInsere);
                (*comparaRetira) ++;
            }

            ApPag->Pagina[0] = Aux->Pagina[Aux->NumItens - DispAux+1];
            ApPai->Usuario[PosPai-1] = Aux->Usuario[Aux->NumItens - DispAux];
            Aux->NumItens -= DispAux;
            *Diminuiu = FALSE;
        }
        else{ /* Fusao: intercala ApPag em Aux e libera ApPag */
            for (j=1; j <= M; j++){
                InsereNaPagina(Aux, ApPag->Usuario[j-1], ApPag->Pagina[j],comparaInsere);
                (*comparaRetira) ++;
            }
            free(ApPag);

            ApPai->NumItens--;
            (*comparaRetira) ++;
            if (ApPai->NumItens >= M)
                *Diminuiu = FALSE;
        }
    }
}

void Testa(ApontadorPag Pag){
    int i;
    if (Pag == NULL)
        return;
    for (i=0; i < Pag->NumItens; i++)
        TestaI(Pag->Pagina[i], Pag->Usuario[i].NumeroConta, FALSE);

    TestaI(Pag->Pagina[Pag->NumItens], Pag->Usuario[i].NumeroConta, TRUE);
}
void TestaI(ApontadorPag Pag, int pai, short direita){
    int i;
    int antecessor = 0;

    if (Pag == NULL)
        return;

    if (Pag->Usuario[0].NumeroConta > pai && direita == FALSE){
        printf("\nErro: filho %12d maior que pai %d\n", Pag->Usuario[0].NumeroConta, pai);
        return;
    }
    for (i=0; i < Pag->NumItens; i++){
        if (Pag->Usuario[i].NumeroConta <= antecessor){
            printf("\nErro: irmao %d maior que irmao a esquerda %d\n",
            Pag->Usuario[i].NumeroConta, antecessor);
            return;
        }
        antecessor = Pag->Usuario[i].NumeroConta;
    }
    for (i=0; i < Pag->NumItens; i++)
        TestaI(Pag->Pagina[i], Pag->Usuario[i].NumeroConta, FALSE);
    TestaI(Pag->Pagina[Pag->NumItens], Pag->Usuario[i].NumeroConta, TRUE);
}

int Altura(ApontadorPag Pag){
    int nivel = -1; /*Altura negativa, significa que a altura é nula */
    AlturaI(Pag,&nivel);
    return nivel;
}
void AlturaI(ApontadorPag Pag,int *nivel){
    if(Pag == NULL)
        return;
    (*nivel)++;
    /* A arvore é balanceada, então para saber a altura basta percorrê-la em uma direção apenas */
    AlturaI(Pag->Pagina[0],nivel);
}
