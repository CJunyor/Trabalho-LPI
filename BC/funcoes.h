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
    char FormaA[7];// Compra e Doação
    char ExemplarP[4];// Sim e Não
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
	char NumCha[50][31];
	char Exemplar[50][4];
	char Status[50][11];
}Nomes_Livros;

typedef struct {
	int n_col;
	char Nomes[50][101];
	char NumCha[50][31];
	char Secao[50][11];
    char Estante[50][5];
    char Prateleira[50][5];
	char Status[50][11];
}Nomes_Periodicos;

//void Cadastro (GtkWidget *, GtkWidget *[]);

//void Atualizar (GtkWidget *, GtkWidget *[]);

//void Consultar(GtkWidget *, GtkWidget *[]);

static int callback(void *, int , char **, char **);


void Login(GtkWidget *, GtkWidget *[]);

void on_Sair_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Cadastrar_Livro_Buttton_clicked(GtkWidget *);

void on_Proximo_Escolha_Cadastro_Button_clicked(GtkWidget *, GtkWidget *);

void on_gtk_fechar_sub_win(GtkWidget *, GtkWidget *);

void on_Buscar_Livro_Button_clicked(GtkWidget *, GtkBox *);

//void on_Confirmar_Resultado_Consulta_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Cadastrar_Livro_Button_clicked(GtkWidget *);


void on_Cadastrar_Cadastro_Livro_Button_clicked (GtkWidget *);

void on_Confirmar_Reserva_Button_clicked (GtkWidget *);

void on_Cadastrar_Usuario_Button_clicked(GtkWidget *);

void on_gtk_fechar_sub_win(GtkWidget *, GtkWidget *);

void Cadastro_Livro_Periodico(GtkWidget *);

static int Nomes_dos_Livros(void *, int, char **, char **);

static int Nomes_dos_Periodicos(void *, int , char **, char **);

void on_gtk_fechar_sub_win(GtkWidget *, GtkWidget *);
void on_Consultar_Acervo_Button_clicked(GtkWidget *);
