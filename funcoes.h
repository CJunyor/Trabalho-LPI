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
    char ISBN[20];
    char Nome[100];
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
    char ISSN[20];
    char Nome[100];
    char Titulo[100];
	char Editora[31];
    char Vol[4];
    char Num[4];
	char Ano[5];
    data DataPul;
    char NumCha[20];
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
	char Exemplar[50][5];
	char Status[50][20];
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

typedef struct{
    int n_col;
    char Matricula[50][15];
    char Nome[50][55];
}Matric_Nome;

typedef struct {
    int n_col;
    int DiasAtraso[50];
    char nome[50][100];
    char DataEmprestimo[50][12];
	char NumCha[50][40];
}Atraso;

typedef struct {
    int n_col;
	char NumCha[50][40];
    char Nome[50][100];
}Reservas;

typedef struct{
	char NumCha[20];
    char Nome[51];
    char Matricula[15];
    char TipoUsuario[2];
    char RG[15];
    char OrgaoExpedidor[15];
    char CodEscola[10];
    char DataCadastro[13];
    char DataExpedicao[13];
    char DataSuspensao[13];
    int  Suspenso;
    int  NumDiasSuspensao;
    int  NumSuspensoes;
}Usuarios;

typedef struct{
    char Senha[21],T;
}STU;

//void Cadastro (GtkWidget *, GtkWidget *[]);

//void Atualizar (GtkWidget *, GtkWidget *[]);

//void Consultar(GtkWidget *, GtkWidget *[]);

// SQL

static int callback(void *, int , char **, char **);

static int Nomes_dos_Livros(void *, int, char **, char **);

static int Nomes_dos_Periodicos(void *, int , char **, char **);

static int ProcurarSenha(void *, int , char **, char **);

static int PegarString(void *, int , char **, char **);

static int Senha_e_Tipo(void *, int , char **, char **);

static int Contar(void *, int , char **, char **);

static int pegardata(void *, int , char **, char **);

static int Matric_e_Nome(void *, int , char **, char **);

static int Dados_Usuarios(void *, int , char **, char **);

static int Atraso_Funcao(void *, int , char **, char **);

static int Reservas_Funcao(void *, int , char **, char **);

static int NomeEscola(void *, int , char **, char **);

static int Atualizar_Funcao(void *, int , char **, char **);

//GTK

void Login(GtkWidget *, GtkWidget *[]);

void on_Sair_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Cadastrar_Livro_Button_clicked(GtkWidget *);

void on_Proximo_Escolha_Cadastro_Button_clicked(GtkWidget *, GtkWidget *);

void on_gtk_fechar_sub_win(GtkWidget *, GtkWidget *);

void on_Buscar_Livro_Button_clicked(GtkWidget *, GtkBox *);

void on_Cadastro_Livro_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Cadastro_Periodico_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Confirmar_Reserva_Button_clicked (GtkWidget *, GtkWidget *[]);

void on_Confirmar_Emprestimo_Button_clicked (GtkWidget *, GtkWidget *[]);

void on_Proximo_Usuario_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Confirmar_Cadastro_Usuario_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Consultar_Usuario_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_gtk_fechar_sub_win(GtkWidget *, GtkWidget *);

void on_Consultar_Acervo_Button_clicked(GtkWidget *);

void on_Usuario_Resultado_Button_clicked(GtkWidget *, GtkWidget *);

void on_Devolucao_Menu_Usuario_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Baixa_Reserva_Menu_Usuario_Button_clicked(GtkWidget *, GtkWidget *[]);

void Renovar_Emprestimo_Menu_Usuario_Button(GtkWidget *, GtkWidget *[]);

void on_Confirmar_Renovar_Emprestimo_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Exclusao_Livro_Button_clicked(GtkWidget *, GtkWidget *[]);

void on_Confirmar_Atualizacao_Livro_Button_clicked(GtkWidget *, GtkWidget *[]);