#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sqlite3.h"
#include "funcoes.h"

//SELECT NumChamada, NC_ClassCDD, NC_Composicao, NC_AnoEdicao, NC_Volome, NC_Exemplar, ISBN, Nome, AutorPrincipal, OutroAutor1, OutroAutor2, OutroAutor3, Edicao, FormaAquisicao, ExemplarPrateleira WHERE NumChamada='%s';
//SELECT U.TipoUsuario, S.Senha FROM Usuarios as U Join SenhasUsuarios as S on U.Matricula=S.Matricula where U.Matricula like 2222222222;
//SELECT Nome, Matricula, TipoUsuario, RG, OrgaoExpedidor, CodEscola,DataCadastro,DataExclusao,DataExpedicao,DataSuspensao,NumDiasSuspensao,NumSuspensoes FROM Usuarios WHERE Nome LIKE '%a%';
static int pegardata(void *DATE, int argc, char **argv, char **azColName){
    char *s;
    s = (char *) DATE;
    strcpy(s, argv[0]);
    return 0;
}

static int Contar(void *k, int argc, char **argv, char **azColName){
    int *n;
    n = (int *)k;
    (*n)++;
    return 0;
}

static int Senha_e_Tipo(void *ST, int argc, char **argv, char **azColName){
    STU *S;
    S = (STU *) ST;
    S->T = argv[0][0];
    strncpy(S->Senha, argv[1], 20);
    return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int Nomes_dos_Livros(void *pNomes, int argc, char **argv, char **azColName){
	Nomes_Livros *itens;
	itens = (Nomes_Livros *) pNomes;
	strncpy(itens->Nomes[itens->n_col], argv[0] ? argv[0] : "NULL", 100);
	strncpy(itens->NumCha[itens->n_col], argv[1] ? argv[1] : "NULL", 30);
	strncpy(itens->Exemplar[itens->n_col], argv[2] ? argv[2] : "NULL", 3);
	strncpy(itens->Status[itens->n_col++], argv[3] ? argv[3] : "NULL", 10);
	return 0;

}

static int Nomes_dos_Periodicos(void *pNomes, int argc, char **argv, char **azColName){
	Nomes_Periodicos *itens;
	itens = (Nomes_Periodicos *) pNomes;
	strncpy(itens->Nomes[itens->n_col], argv[0] ? argv[0] : "NULL", 100);
	strncpy(itens->NumCha[itens->n_col], argv[1] ? argv[1] : "NULL", 30);
	strncpy(itens->Secao[itens->n_col], argv[2] ? argv[2] : "NULL", 11);
	strncpy(itens->Estante[itens->n_col], argv[3] ? argv[3] : "NULL", 5);
	strncpy(itens->Prateleira[itens->n_col], argv[4] ? argv[4] : "NULL", 5);
	strncpy(itens->Status[itens->n_col++], argv[5] ? argv[5] : "NULL", 10);
	return 0;
}


//=============================================================================================================================================== 
 
//========================================================================================================================================================