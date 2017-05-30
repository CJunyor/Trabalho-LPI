#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia,mes,ano;
}data;

typedef struct{
    char Secao[11];
    char Estante[5];
    char Prateleira[5];
}Local;

typedef struct {
    char Class[8];
    char Comp[6];
    char Ano[5];
    char Vol[6];
    char Exe[5];
}CDD;

typedef struct {
    char ISBN[14];
    char Nome[51];
    char AutorP[31];
    char OutrosA[4];
    char Edicao[4];
    char Ano[5];
    char Editora[31];
    char NumCha[13];
    int status;// 1 - emprestado 2 - disponivel 3 - reservado
    CDD cdd;
    data DataCD;
    data DataBaixa;
    int MotivoB;//1 - extravio 2 - descarte 3 - doação
    int FormaA;//1 - compra 2 - doação
    int ExemplarP;//1 - Sim 0 - Não
}Livro;

typedef struct{
    char ISBN[9];
    char Nome[51];
    char Titulo[51];
    char Vol[4];
    char Num[4];
    data DataPul;
    char NumCha[8];
    int status;// 1 - emprestado 2 - disponivel 3 - reservado
    Local Localizacao;
    int NumC;
    data DataCD;
    int FormaA;//1 - assinatura 2 - doação
    data DataBaixa;
    int MotivoB;//1 - extravio 2 - descarte 3 - doação
}Periodico;

typedef struct{
    int type;//1-Livro 2-Periodico
    union{
        Livro L;
        Periodico P;
    };
} Acervo;

int Cadastro(int type, Acervo *p);

int Atualizar(int x, Acervo *p);

int Consultar(char *str,int TConsu,Acervo *p);
