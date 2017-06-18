#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    char status[10];// Emprestado, Disponivel e Reservado
    CDD cdd;
    data DataCD;
    data DataBaixa;
    char MotivoB[10];// Extravio, Descarte e Doação
    char FormaA[6];// Compra e Doação
    char ExemplarP[3];// Sim e Não
}Livro;

typedef struct{
    char ISBN[9];
    char Nome[51];
    char Titulo[51];
    char Vol[4];
    char Num[4];
    data DataPul;
    char NumCha[8];
    char status[10];// Emprestado, Disponivel e Reservado
    Local Localizacao;
    int NumC;
    data DataCD;
    char FormaA[10];// Assinatura e Doação
    data DataBaixa;
    char MotivoB[10];// Extravio, Descarte e Doação
}Periodico;

typedef struct{
    char type[10]; // Livro e Periodico
    union{
        Livro L;
        Periodico P;
    };
} Acervo;

void Cadastro (GtkWidget *, GtkWidget *[]);

void Atualizar (GtkWidget *, GtkWidget *[]);

void Consultar(GtkWidget *, GtkWidget *[]);