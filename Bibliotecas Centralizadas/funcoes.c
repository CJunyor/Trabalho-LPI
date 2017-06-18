#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funcoes.h"

void Cadastro (GtkWidget *botao, GtkWidget *widgets[]){
	Acervo *p;
	char type[10];
	strcpy (type, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	if(!strcmp(type,"Livro"){
        strncpy((p->L).ISBN,gtk_entry_get_text(GTK_ENTRY(widgets[])),13);
        strncpy((p->L).Nome,gtk_entry_get_text(GTK_ENTRY(widgets[])),50);
        strncpy((p->L).AutorP,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
        strncpy((p->L).OutrosA,gtk_entry_get_text(GTK_ENTRY(widgets[])),3);
        strncpy((p->L).Edicao,gtk_entry_get_text(GTK_ENTRY(widgets[])),3);
        strncpy((p->L).Ano,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
        strncpy((p->L).Editora,gtk_entry_get_text(GTK_ENTRY(widgets[])),30);
        strncpy((p->L).NumCha,gtk_entry_get_text(GTK_ENTRY(widgets[])),12);
        strncpy((p->L).cdd.Class,gtk_entry_get_text(GTK_ENTRY(widgets[])),7);
        strncpy((p->L).cdd.Comp,gtk_entry_get_text(GTK_ENTRY(widgets[])),5);
        strncpy((p->L).cdd.Ano,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
        strncpy((p->L).cdd.Vol,gtk_entry_get_text(GTK_ENTRY(widgets[])),5);
        strncpy((p->L).cdd.Exe,gtk_entry_get_text(GTK_ENTRY(widgets[])),4);
	strncpy(data, gtk_entry_get_text(GTK_ENTRY(widgets[])), 8);
	gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->L).DataCD.ano), &((p->L).DataCD.mes), &((p->L).DataCD.dia));
	strcpy(p->L.FormaA, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
        strcpy(p->L.ExemplarP, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
    }
    else{
        strncpy((p->P).ISBN, gtk_entry_get_text(GTK_ENTRY(widgets[])), 8);
        strncpy((p->P).Nome, gtk_entry_get_text(GTK_ENTRY(widgets[])), 50);
        strncpy((p->P).Titulo, gtk_entry_get_text(GTK_ENTRY(widgets[])), 50);
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
    }

}
 
//=============================================================================================================================================== 
 
void Atualizar (GtkWidget *botao, GtkWidget *widgets[]){
	Acervo *p;
	char type[10];
	strcpy (type, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	if(!strcmp(type,"Livro"){
		gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->L).DataBaixa.ano), &((p->L).DataBaixa.mes), &((p->L).DataBaixa.dia));
		strncpy( (p->L).MotivoB, gtk_entry_get_text(GTK_ENTRY(widgets[])), 10);
    }
    else{
        gtk_calendar_get_date(GTK_CALENDAR(widgets[]), &((p->P).DataBaixa.ano), &((p->P).DataBaixa.mes), &((p->P).DataBaixa.dia));
		strncpy( (p->P).MotivoB, gtk_entry_get_text(GTK_ENTRY(widgets[])), 10);
    }
}

//================================================================================================================================================

void Consultar(GtkWidget *botao, GtkWidget *widgets[]){
	
	char nome[50];
	char TConsu[10];
	char TAcervo[10];
	strcpy(TConsu, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	strcpy(TAcervo, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widgets[])));
	
    if(!strcmp(TAcervo,"Livro")){
        if(!strcmp(TConsu,"Nome"){
            rotina_SQL_para_procurar_pelo_nome(nome);
			
	}
        else if(!strcmp(TConsu,"Autor"){
			rotina_SQL_para_procurar_pelo_nome_autor(nome);		
            
	}
	else{
			gtk_entry_set_text(GTK_ENTRY(widgets[]), "Parametros de Pesquisa Errados");
        }
    }
    else{
        if(!strcmp(TConsu,"Nome"){
            rotina_SQL_para_procurar_pelo_nome(nome);
			
	}
        else if(!strcmp(TConsu,"Titulo"){
			rotina_SQL_para_procurar_pelo_nome_titulo(nome);	
            
	}
	else{
		gtk_entry_set_text(GTK_ENTRY(widgets[]), "Parametros de Pesquisa Errados");
        }
    }
}
