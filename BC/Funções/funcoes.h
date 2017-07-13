#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sqlite3.h"

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
    char Autor2[31];
	char Autor3[31];
	char Autor4[31];
    char Edicao[4];
    char Ano[5];
    char Editora[31];
    char NumCha[31];
    char status[10];// Emprestado, Disponivel e Reservado
    CDD cdd;
    data DataCD;
    data DataBaixa;
    char MotivoB[10];// Extravio, Descarte e Doação
    char FormaA[6];// Compra e Doação
    char ExemplarP[3];// Sim e Não
}Livro;

typedef struct{
    char ISSN[9];
    char Nome[51];
    char Titulo[51];
	char Editora[31];
    char Vol[4];
    char Num[4];
	char Ano[5];
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

typedef struct {
	int n_col;
	char Nomes[50][101];
	char Numcha[50][31];
	char Exemplar[50][4];
	char Status[50][11];
}Nomes_Livros;

void Cadastro (GtkWidget *, GtkWidget *[]);

void Atualizar (GtkWidget *, GtkWidget *[]);

void Consultar(GtkWidget *, GtkWidget *[]);

static int callback(void *, int , char **, char **);

void on_Buscar_Livro_Button_clicked(GtkWidget *botao, GtkWidget *widgets[]);

void on_Buscar_Periodico_Button_clicked(GtkWidget *botao, GtkWidget *widgets[]);

void on_Cadastrar_Usuario_Button_clicked(GtkWidget *botao, GtkWidget *widgets[]);
