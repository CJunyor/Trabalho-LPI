#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funcoes.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void Cadastro (GtkWidget *botao, GtkWidget *widgets[]){
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;
	Acervo *p;
	char type[10],comandosql[500];
	memset(pR->tabela[cont][i], '\0', 500);
	strcpy (type, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	if(!strcmp(type,"Livro"){
		strncpy((p->L).NumCha,gtk_entry_get_text(GTK_ENTRY(widgets[])),12);
        strncpy((p->L).ISBN,gtk_entry_get_text(GTK_ENTRY(widgets[])),13);
        strncpy((p->L).Nome,gtk_entry_get_text(GTK_ENTRY(widgets[])),50);
        strncpy((p->L).AutorP,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
		strncpy((p->L).Autor2,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
		strncpy((p->L).Autor3,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
		strncpy((p->L).Autor4,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
        strncpy((p->L).Edicao,gtk_entry_get_text(GTK_ENTRY(widgets[])),3);
        strncpy((p->L).Ano,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
        strncpy((p->L).Editora,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
        strncpy((p->L).cdd.Class,gtk_entry_get_text(GTK_ENTRY(widgets[])),7);
        strncpy((p->L).cdd.Comp,gtk_entry_get_text(GTK_ENTRY(widgets[])),5);
        strncpy((p->L).cdd.Ano,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
        strncpy((p->L).cdd.Vol,gtk_entry_get_text(GTK_ENTRY(widgets[])),5);
        strncpy((p->L).cdd.Exe,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
		strncpy(data, gtk_entry_get_text(GTK_ENTRY(widgets[])), 8);
		gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->L).DataCD.ano), &((p->L).DataCD.mes), &((p->L).DataCD.dia));
		strcpy(p->L.FormaA, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
        strcpy(p->L.ExemplarP, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
		
		strcpy(comandosql,"INSERT INTO `Livros` VALUES('");
		strcat(comandosql,(p->L).Numcha);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).cdd.Class);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).cdd.Comp);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).cdd.Ano);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).cdd.Vol);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).cdd.Exe);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).ISBN);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).ISBN);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).Nome);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).AutorP);
		strcat(comandosql,"',");
		if(!strcmp((p->L).Autor2,"")
			strcat(comandosql,"NULL");
		else
			strcat(comandosql,(p->L).Autor2);
		strcat(comandosql,"',");
		if(!strcmp((p->L).Autor3,"")
			strcat(comandosql,"NULL");
		else
			strcat(comandosql,(p->L).Autor3);
		strcat(comandosql,"',");
		if(!strcmp((p->L).Autor4,"")
			strcat(comandosql,"NULL");
		else
			strcat(comandosql,(p->L).Autor4);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).Edicao);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).Editora);
		strcat(comandosql,"',");
		sprintf(comandosql, "%s%i-%i-%i", comandosql,((p->L).DataCD.ano), ((p->L).DataCD.mes), ((p->L).DataCD.dia));
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).FormaA);
		strcat(comandosql,"',");
		strcat(comandosql,(p->L).ExemplarP);
		strcat(comandosql,"','NULL','NULL');");
    }
    else{
        strncpy((p->P).ISSN, gtk_entry_get_text(GTK_ENTRY(widgets[])), 8);
        strncpy((p->P).Nome, gtk_entry_get_text(GTK_ENTRY(widgets[])), 50);
        strncpy((p->P).Titulo, gtk_entry_get_text(GTK_ENTRY(widgets[])), 50);
		strncpy((p->P).Editora, gtk_entry_get_text(GTK_ENTRY(widgets[])), 30);
        strncpy((p->P).Vol, gtk_entry_get_text(GTK_ENTRY(widgets[])), 3);
        strncpy((p->P).Num, gtk_entry_get_text(GTK_ENTRY(widgets[])), 3);
		gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->P).DataPul.ano), &((p->P).DataPul.mes), &((p->P).DataPul.dia)
        strncpy((p->P).NumCha, gtk_entry_get_text(GTK_ENTRY(widgets[])), 7);
        strncpy((p->P).Localizacao.Secao, gtk_entry_get_text(GTK_ENTRY(widgets[])), 10);
        strncpy((p->P).Localizacao.Estante, gtk_entry_get_text(GTK_ENTRY(widgets[])), 4);
        strncpy((p->P).Localizacao.Prateleira, gtk_entry_get_text(GTK_ENTRY(widgets[])), 4);
        sscanf(gtk_entry_get_text(GTK_ENTRY(widgets[])), "%i", &((p->P).NumC));
		strncpy(data, gtk_entry_get_text(GTK_ENTRY(widgets[])), 8);
		gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->P).DataCD.ano), &((p->P).DataCD.mes), &((p->P).DataCD.dia));
        strcpy((p->P.FormaA), gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
		
		stpcpy(comandosql,"INSERT INTO Periodicos ")
		strcat(comandosql,(p->P).Numcha);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).ISSN);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Nome);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Titulo);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Editora);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Vol);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Num);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Ano);
		strcat(comandosql,"',");
		sprintf(comandosql, "%s%i-%i-%i", comandosql,((p->P).DataCD.ano), ((p->P).DataCD.mes), ((p->P).DataCD.dia));
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Localizacao.Secao);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Localizacao.Estante);
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).Localizacao.Prateleira);
		strcat(comandosql,"',");
		sprintf(comandosql, "%s%i", comandosql,((p->P).NumC);
		strcat(comandosql,"',");
		sprintf(comandosql, "%s%i-%i-%i", comandosql, ((p->P).DataPul.ano), ((p->P).DataPul.mes), ((p->P).DataPul.dia));
		strcat(comandosql,"',");
		strcat(comandosql,(p->P).FormaA);
		strcat(comandosql,"','NULL','NULL');");
    }
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
      return(0);
   }
   rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);
}
 
//=============================================================================================================================================== 
 
void Atualizar (GtkWidget *botao, GtkWidget *widgets[]){
	data DataBaixa;
	char MotivoB[10];
	char type[10], comandosql[300];
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;
	memset(pR->tabela[cont][i], '\0', 300);
	strcpy (type, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	if(!strcmp(type,"Livro"){
		strcpy(comandosql,"UPDATE Livros SET DataBaixa = ");
		gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &DataBaixa.ano, &DataBaixa.mes, &DataBaixa.dia);
		sprintf(comandosql, "%s %i-%i-%i AND SET MotivoBaixa = ");
		strncpy(MotivoB, gtk_entry_get_text(GTK_ENTRY(widgets[])), 10);
		strncat(comandosql,(MotivoB);
		strncat(comandosql,"WHERE NumCha=NumChamada;");
		
		rc = sqlite3_open("sisbib.db3", &db);
		if( rc ){
		fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(0);
		}
		rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);	
    }
    else{
		strcpy(comandosql,"UPDATE Periodicos SET DataBaixa = ");
        gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &DataBaixa.ano, &DataBaixa.mes, &DataBaixa.dia);
		sprintf(comandosql, "%s %i-%i-%i AND SET MotivoBaixa= ");
		strncpy(MotivoB, gtk_entry_get_text(GTK_ENTRY(widgets[])), 10);
		strncat(comandosql,(MotivoB);
		strncat(comandosql,"WHERE NumCha=NumChamada;");
		
		rc = sqlite3_open("sisbib.db3", &db);
		if( rc ){
		fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(0);
		}
		rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
    }
}

//================================================================================================================================================

void Consultar(GtkWidget *botao, GtkWidget *widgets[]){
	
	char string[50];
	char TConsu[10];
	char TAcervo[10];
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;
	char comandosql[100];
	memset(comandosql, '\0', 100);
	strncpy(string, gtk_entry_get_text(GTK_ENTRY(widgets[])), 50);
	strcpy(TConsu, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	strcpy(TAcervo, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
    if(!strcmp(TAcervo,"Livro")){
        if(!strcmp(TConsu,"Nome"){
            stpcpy(comandosql,"SELECT * FROM Livros WHERE Nome LIKE '%");
			strcat(comandosql, string);
			strcat(comandosql,"%' ;");
			
			rc = sqlite3_open("sisbib.db3", &db);
			if( rc ){
			fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(0);
			}
			rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			}
		else if(!strcmp(TConsu,"Autor"){
			stpcpy(comandosql,"SELECT * FROM Livros WHERE AutorPrincipal LIKE '%");
			strcat(comandosql, string);
			strcat(comandosql,"%' ;");
			
			rc = sqlite3_open("sisbib.db3", &db);
			if( rc ){
			fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(0);
			}
			rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			}		
            
		}
		else{
			gtk_entry_set_text(GTK_ENTRY(widgets[]), "Parametros de Pesquisa Errados");
		}
    }
    else{
        if(!strcmp(TConsu,"Nome"){
            stpcpy(comandosql,"SELECT * FROM Periodicos WHERE Nome LIKE '%");
			strcat(comandosql, string);
			strcat(comandosql,"%' ;");
			
			rc = sqlite3_open("sisbib.db3", &db);
			if( rc ){
			fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(0);
			}
			rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			};
			
		}
        else if(!strcmp(TConsu,"Titulo"){
			stpcpy(comandosql, "SELECT * FROM Periodicos WHERE TituloEdicao LIKE '%");
			strcat(comandosql, string);
			strcat(comandosql, "%' ;");
			
			rc = sqlite3_open("sisbib.db3", &db);
			if( rc ){
			fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return(0);
			}
			rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			};	
            
		}
		else{
			gtk_entry_set_text(GTK_ENTRY(widgets[]), "Parametros de Pesquisa Errados");
        }
	}
}