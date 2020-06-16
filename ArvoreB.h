#ifndef ARVOREB_H_INCLUDED

#define M 2
#define MM (M*2)
#define FALSE 0
#define TRUE  1
/**
 * Autor: Paulo Henrique
*/

/* Definição da estrutura TipoUsuario */
typedef struct TipoUsuario{
    char Nome[50];   /* Nome do usuario obtido atraves do arquivo de entrada */
    int NumeroConta; /* Numero da conta, foi gerado um vetor com numeros entre 1 e 10001 */
    int SenhaConta;  /* Senha para acessar a conta, Senha = NumeroConta+1(Exemplo: Conta 103 - Senha 104) */
    float Dinheiro;  /* Quantia ficticia de cada usuario, gerada randomicamente */
}TipoUsuario;

/* Definição basica convencional da arvore B */
typedef struct TipoPagina* ApontadorPag;
typedef struct TipoPagina{
    short NumItens;
    TipoUsuario Usuario[MM];
    ApontadorPag Pagina[MM+1];
}TipoPagina;

/* Inicializa o Sistema Bancario */
void Inicializa(ApontadorPag *SistemaBancario);

/* Funções responáveis pelas inserções na arvore */
void Insere(TipoUsuario User, ApontadorPag *Ap, long int* comparaInsere);
void Ins(TipoUsuario User, ApontadorPag Ap, short *Cresceu, TipoUsuario *UserRetorno,  ApontadorPag *ApRetorno, long int* comparaInsere);
void InsereNaPagina(ApontadorPag Ap, TipoUsuario User, ApontadorPag ApDir, long int* comparaInsere);

/* Função responsavel pela pesquisa de uma chave. Se a função retornar 1, a lista de operações referentes a conta são mostradas */
int PesquisaConta(TipoUsuario x, ApontadorPag Ap, long int* comparaPesquisa);

/* Funções referentes as operações ádrões de um caixa eletrônico convencional */
void VerConta(TipoUsuario Conta, ApontadorPag Ap);
int Saque(TipoUsuario Conta, ApontadorPag *Ap);
void Deposito(TipoUsuario Conta, ApontadorPag *Ap);

/* Funções responsaveis por imprimir a arvore, imprime tendo o Numero da Conta como chave */
void ImprimeArvore(ApontadorPag p);
void ImprimeI(ApontadorPag p, int nivel);

/* Funções responáveis pelas remoções na arvore */
void Retira(TipoUsuario User, ApontadorPag *Ap, long int* comparaInsere,long int* comparaRetira);
void Ret(TipoUsuario User, ApontadorPag *Ap, short *Diminuiu, long int* comparaInsere,long int* comparaRetira);
void Antecessor(ApontadorPag Ap, int i, ApontadorPag ApPai, short *Diminuiu,long int* comparaInsere, long int* comparaRetira);
void Reconstitui(ApontadorPag ApPag, ApontadorPag ApPai, int PosPai, short *Diminuiu, long int* comparaInsere, long int* comparaRetira);

void Testa(ApontadorPag Pag);
void TestaI(ApontadorPag Pag, int pai, short direita);

/* Funções responáveis pelo calculo da altura da arvore */
void AlturaI(ApontadorPag Pag,int *nivel);
int Altura(ApontadorPag);

#endif // ARVOREB_H_INCLUDED

