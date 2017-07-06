#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sqlite3.h"
#include "funcoes.h"

GtkWidget *Widgets_Cadastro[19],*Widgets_Resultado[5],*Widgets_Reservar[6];


int main (int argc, char *argv[]){
	GtkBuilder *builder;
	GtkWidget *Widgets_Main[5];
	
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Login.glade", NULL);
	
	Widgets_Main[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Login"));
	Widgets_Main[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Usuario_Entry"));
	Widgets_Main[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Senha_Entry"));
	Widgets_Main[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Entrar_button"));
	Widgets_Main[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Messagem_Erro_Label"));
		
	
	g_signal_connect(Widgets_Main[3], "clicked", G_CALLBACK (Login), Widgets_Main);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Main[0]);

	gtk_main();

	return 0;
}

//=======================================================================================================================================================
//Funções dos botões

void Login(GtkWidget *Button, GtkWidget *Widgets_Main[]){
	GtkBuilder *builder;
	GtkWidget *Janela_Menu, *Sair_Button, *Cadastrar_Livro_Button, *Consultar_Acervo_Button;
	//GtkWidget *Consultar_Usuarios_Button, *Relatorios_Button;
	gchar login[20], senha[20];
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(Widgets_Main[1])));
	strcpy(senha, gtk_entry_get_text(GTK_ENTRY(Widgets_Main[2])));
	if(!strcmp(login, "")&& !strcmp(senha, "")){
		gtk_label_set_text(GTK_LABEL(Widgets_Main[4]), "");
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Menu.glade", NULL);
		
		Janela_Menu = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Menu"));
		Cadastrar_Livro_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Livro_Buttton"));
		/*
		Cadastrar_Livro_Buttton = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Livro_Buttton"));
		Consultar_Usuarios_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Consultar_Usuarios_Button"));
		Relatorios_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Relatorios_Button"));
		*/
		Widgets_Main[5]=Janela_Menu;
		
		Sair_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Sair_Button"));
		
		g_signal_connect(Janela_Menu, "destroy", G_CALLBACK (on_Sair_Button_clicked), Widgets_Main);
		g_signal_connect(Sair_Button, "clicked", G_CALLBACK (on_Sair_Button_clicked), Widgets_Main);
		g_signal_connect(Cadastrar_Livro_Button, "clicked", G_CALLBACK (on_Cadastrar_Livro_Button_clicked), Cadastrar_Livro_Button);
	
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
  
		gtk_widget_show_all(Janela_Menu);
		gtk_widget_hide(Widgets_Main[0]);
		
	}
	else{
		gtk_label_set_text(GTK_LABEL(Widgets_Main[4]), "Usuário ou Senha Incorretos");
	}
}

void on_Cadastrar_Livro_Button_clicked(GtkWidget *Button){
	
	GtkBuilder *builder;
	GtkWidget *Janela_Pre_Cadastrar_Livro, *Proximo_Escolha_Cadastro_Button, *Escolha_Cadastro_Combo_Box_Text;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Pre_Tela_Cadastrar_Livro.glade", NULL);
	
	Janela_Pre_Cadastrar_Livro = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Pre_Cadastrar_Livro"));
	Proximo_Escolha_Cadastro_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Proximo_Escolha_Cadastro_Button"));
	Escolha_Cadastro_Combo_Box_Text = GTK_WIDGET(gtk_builder_get_object(builder, "Escolha_Cadastro_Combo_Box_Text"));
	
	g_signal_connect(Janela_Pre_Cadastrar_Livro, "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Janela_Pre_Cadastrar_Livro);
	g_signal_connect(Proximo_Escolha_Cadastro_Button, "clicked", G_CALLBACK (on_Proximo_Escolha_Cadastro_Button_clicked), Escolha_Cadastro_Combo_Box_Text);
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Pre_Cadastrar_Livro);
	
}

void on_Proximo_Escolha_Cadastro_Button_clicked(GtkWidget *Button, GtkWidget *Texto_Combo_Box){
	gchar escolha[10];
	strcpy(escolha, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Texto_Combo_Box)));
	if(!strcmp(escolha, "Livro")){
		GtkBuilder *builder;
		//GtkWidget *Widgets_Cadastro[21];
		
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Cadastro de Livro.glade", NULL);
		
		Widgets_Cadastro[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Livro"));
		Widgets_Cadastro[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_do_Livro_Entry"));
		Widgets_Cadastro[2] = GTK_WIDGET(gtk_builder_get_object(builder, "ISBN_Entry"));
		Widgets_Cadastro[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Autor_Principal_Entry"));
		Widgets_Cadastro[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor_Entry"));
		Widgets_Cadastro[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor2_Entry"));
		Widgets_Cadastro[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor3_Entry"));
		Widgets_Cadastro[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Edicao_Entry"));
		Widgets_Cadastro[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Editora_Entry"));
		Widgets_Cadastro[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Classificacao_Cadastro_Livro_Entry"));
		Widgets_Cadastro[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Composicao_Cadastro_Livro_Entry"));
		Widgets_Cadastro[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Ano_Edicao_Cadastro_Livro_Entry"));
		Widgets_Cadastro[12] = GTK_WIDGET(gtk_builder_get_object(builder, "Volume_Cadastro_Livro_Entry"));
		Widgets_Cadastro[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Exemplar_Cadastro_Livro_Entry"));
		Widgets_Cadastro[14] = GTK_WIDGET(gtk_builder_get_object(builder, "Exemplar_Combo_Box_Text"));
		Widgets_Cadastro[15] = GTK_WIDGET(gtk_builder_get_object(builder, "Forma_Aquisicao_Cadastro_Livro_CBT"));
		Widgets_Cadastro[16] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar"));
		Widgets_Cadastro[17] = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Cadastro_Livro_Button"));
		Widgets_Cadastro[18] = GTK_WIDGET(gtk_builder_get_object(builder, "Observacao_Cadastro_Livro_Entry"));
		
		
		g_signal_connect(Widgets_Cadastro[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Cadastro[0]);
		g_signal_connect(Widgets_Cadastro[17], "clicked", G_CALLBACK (on_Cadastrar_Cadastro_Livro_Button_clicked), Widgets_Cadastro[17]);
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
	  
		gtk_widget_show_all(Widgets_Cadastro[0]);
	}
	else if(!strcmp(escolha, "Periódico")){
		GtkBuilder *builder;
		
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Cadastro de Periódico.glade", NULL);
		
		Widgets_Cadastro[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Periodico"));
		Widgets_Cadastro[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_do_Periodico_Entry"));
		Widgets_Cadastro[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Titulo_do_Periodico_Entry"));
		Widgets_Cadastro[3] = GTK_WIDGET(gtk_builder_get_object(builder, "ISSN_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Volume_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Num_Chamada_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Editora_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Copias_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Secao_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Estante_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Prateleira_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Ano_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[12] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Forma_Aquisicao_Cadastro_Periodico_CBT"));
		Widgets_Cadastro[14] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Publicacao"));
		Widgets_Cadastro[15] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Cadastro"));
		Widgets_Cadastro[16] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Cadastrar_Periodico_Button"));
		Widgets_Cadastro[17] = GTK_WIDGET(gtk_builder_get_object(builder, "Observacao_Cadastro_Periodico_Entry"));
		
		g_signal_connect(Widgets_Cadastro[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Cadastro[0]);
		g_signal_connect(Widgets_Cadastro[16], "clicked", G_CALLBACK (Cadastro_Livro_Periodico), Widgets_Cadastro[16]);
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
	  
		gtk_widget_show_all(Widgets_Cadastro[0]);
		
	}
}

void on_Cadastrar_Cadastro_Livro_Button_clicked (GtkWidget *Button){
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
	Acervo *p;
	char comandosql[500];
	p=(Acervo *) malloc(sizeof(Acervo));
	
	strncpy((p->L).Nome,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[1])),50);
	strncpy((p->L).ISBN,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[2])),13);
    strncpy((p->L).AutorP,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[3])),30);
	strncpy((p->L).Autor2,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[4])),30);
	strncpy((p->L).Autor3,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[5])),30);
	strncpy((p->L).Autor4,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[6])),30);
    strncpy((p->L).Edicao,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[7])),3);
    strncpy((p->L).Editora,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[8])),30);
    strncpy((p->L).cdd.Class,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[9])),7);
    strncpy((p->L).cdd.Comp,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[10])),5);
    strncpy((p->L).cdd.Ano,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[11])),4);
    strncpy((p->L).cdd.Vol, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[12])),5);
    strncpy((p->L).cdd.Exe,gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[13])),4);
	gtk_calendar_get_date(GTK_CALENDAR(Widgets_Cadastro[16]), &((p->L).DataCD.ano), &((p->L).DataCD.mes), &((p->L).DataCD.dia));
	strcpy(p->L.FormaA, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(Widgets_Cadastro[15])));
    strcpy(p->L.ExemplarP, gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(Widgets_Cadastro[14])));
	
	sprintf((p->L).NumCha ,"%s-%s-%s-%s-%s",(p->L).cdd.Class, (p->L).cdd.Comp, (p->L).cdd.Ano, (p->L).cdd.Vol, (p->L).cdd.Exe);
	
	strcpy(comandosql,"INSERT INTO `Livros` VALUES('");
	strcat(comandosql,(p->L).NumCha);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).cdd.Class);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).cdd.Comp);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).cdd.Ano);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).cdd.Vol);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).cdd.Exe);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).ISBN);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).Nome);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).AutorP);
	strcat(comandosql,"','");
	if(!strcmp((p->L).Autor2,""))
		strcat(comandosql,"NULL");
	else
		strcat(comandosql,(p->L).Autor2);
	strcat(comandosql,"','");
	if(!strcmp((p->L).Autor3,""))
		strcat(comandosql,"NULL");
	else
		strcat(comandosql,(p->L).Autor3);
	strcat(comandosql,"','");
	if(!strcmp((p->L).Autor4,""))
		strcat(comandosql,"NULL");
	else
		strcat(comandosql,(p->L).Autor4);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).Edicao);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).Editora);
	strcat(comandosql,"','");
	sprintf(comandosql, "%s%i-%i-%i", comandosql,((p->L).DataCD.ano), ((p->L).DataCD.mes)+1, ((p->L).DataCD.dia));
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).FormaA);
	strcat(comandosql,"','");
	strcat(comandosql,(p->L).ExemplarP);
	strcat(comandosql,"','NULL','NULL','NULL');");
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
      //return(0);
    }
    rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
		
		GtkBuilder *builder;
	    GtkWidget *Men;
	    builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Messagem de Sucesso.glade", NULL);
		Men = GTK_WIDGET(gtk_builder_get_object(builder, "Messagem_Sucesso"));
		gtk_widget_destroy(Widgets_Cadastro[0]);
		
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
		gtk_widget_show_all(Men);
		
	}
    sqlite3_close(db);
	
	
}

void Cadastro_Livro_Periodico(GtkWidget *Button){
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
	Acervo *p;
	char comandosql[500];
	p=(Acervo *) malloc(sizeof(Acervo));
	
	strncpy((p->P).Nome, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[1])), 50);
	strncpy((p->P).Titulo, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[2])), 50);
	strncpy((p->P).ISSN, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[3])), 8);
	strncpy((p->P).Vol, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[4])), 3);
	strncpy((p->P).NumCha, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[5])), 7);
	strncpy((p->P).Editora, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[6])), 30);
	sscanf(gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[7])), "%i", &(p->P).NumC);
	strncpy((p->P).Localizacao.Secao, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[8])), 10);
    strncpy((p->P).Localizacao.Estante, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[9])), 4);
    strncpy((p->P).Localizacao.Prateleira, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[10])), 4);
	strncpy((p->P).Ano, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[11])), 4);
    strncpy((p->P).Num, gtk_entry_get_text(GTK_ENTRY(Widgets_Cadastro[12])), 3);  
	strcpy((p->P.FormaA), gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(Widgets_Cadastro[13])));
	gtk_calendar_get_date(GTK_CALENDAR(Widgets_Cadastro[14]), &((p->P).DataPul.ano), &((p->P).DataPul.mes), &((p->P).DataPul.dia));  
	gtk_calendar_get_date(GTK_CALENDAR(Widgets_Cadastro[15]), &((p->P).DataCD.ano), &((p->P).DataCD.mes), &((p->P).DataCD.dia));
	
	strcpy(comandosql,"INSERT INTO `Periodicos` VALUES('");
	strcat(comandosql,(p->P).NumCha);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).ISSN);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Nome);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Titulo);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Editora);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Vol);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Num);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Ano);
	strcat(comandosql,"','");
	sprintf(comandosql, "%s%i-%i-%i", comandosql, ((p->P).DataPul.ano), ((p->P).DataPul.mes)+1, ((p->P).DataPul.dia));
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Localizacao.Secao);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Localizacao.Estante);
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).Localizacao.Prateleira);
	strcat(comandosql,"','");
	sprintf(comandosql, "%s%i", comandosql,(p->P).NumC);
	strcat(comandosql,"','");
	sprintf(comandosql, "%s%i-%i-%i", comandosql,((p->P).DataCD.ano), ((p->P).DataCD.mes)+1, ((p->P).DataCD.dia));
	strcat(comandosql,"','");
	strcat(comandosql,(p->P).FormaA);
	strcat(comandosql,"','NULL','NULL','NULL');");
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
      //return(0);
    }
    rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
		GtkBuilder *builder;
	    GtkWidget *Men;
	    builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Messagem de Sucesso.glade", NULL);
		Men = GTK_WIDGET(gtk_builder_get_object(builder, "Messagem_Sucesso"));
		gtk_widget_destroy(Widgets_Cadastro[0]);
		
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
		gtk_widget_show_all(Men);
	}
    sqlite3_close(db);
	
}

G_MODULE_EXPORT void on_Consultar_Acervo_Button_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	GtkWidget *Janela_Consulta_Acervo;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Consulta Acervo.glade", NULL);
	
	Janela_Consulta_Acervo = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Consulta_Acervo"));

	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Consulta_Acervo);
	
}

G_MODULE_EXPORT void on_Buscar_Livro_Button_clicked(GtkWidget *Button, GtkBox *box){
	sqlite3 *db;
	GtkBuilder *builder;
	GtkWidget *Janela_Resultado_Consulta_Livro, *Lista_Livro, *Numero_Chamada_Resultado_Entry, *Confirmar_Resultado_Consulta_Button;
	GtkTreeIter iter;
	GList *list;
	int  rc;
	char *zErrMsg = 0;
    char erro[100];
	char sql[500];
    Nomes_Livros *p;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Resultado da Consulta do Livro.glade", NULL);
	
	Janela_Resultado_Consulta_Livro = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Resultado_Consulta_Livro"));
	Lista_Livro = GTK_WIDGET(gtk_builder_get_object(builder, "Lista_Livro"));
	Numero_Chamada_Resultado_Entry = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Chamada_Resultado_Entry"));
	Confirmar_Resultado_Consulta_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Resultado_Consulta_Button"));
	
	Widgets_Resultado[0] = Janela_Resultado_Consulta_Livro;
	Widgets_Resultado[1] = Lista_Livro;
	Widgets_Resultado[2] = Numero_Chamada_Resultado_Entry;
	Widgets_Resultado[3] = Confirmar_Resultado_Consulta_Button;
	Widgets_Resultado[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Erro"));
	list = gtk_container_get_children(GTK_CONTAINER(box));
	
	if(!strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(list->data)), "Nome")){
		//SQL
	    rc = sqlite3_open("sisbib.db3", &db);
	    if( rc ){
			sprintf(erro, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			//return(0);
	    }
		
		list=list->next;
	    sprintf(sql,"SELECT Nome, NumChamada, ExemplarPrateleira, Status FROM Livros WHERE Nome LIKE '%%%s%%'",gtk_entry_get_text(GTK_ENTRY(list->data)));
	    p=(Nomes_Livros *)malloc(sizeof(Nomes_Livros));
	    p->n_col=0;
	    rc = sqlite3_exec(db, sql, Nomes_dos_Livros, (void *) p, &zErrMsg);
	    if( rc != SQLITE_OK ){
			sprintf(erro, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			//return 0;
	    }else{ 
			for(int i=0;i<p->n_col;i++){
				gtk_list_store_append (GTK_LIST_STORE(Widgets_Resultado[1]), &iter);
				gtk_list_store_set (GTK_LIST_STORE(Widgets_Resultado[1]), &iter,
									0, p->Nomes[i],
									1, p->NumCha[i],
									2, p->Exemplar[i],
									3, p->Status[i],
									-1);
		    }
	    }
	   
	    sqlite3_close(db);
        //================================================================================================
	}
	else{
		//SQL
	    rc = sqlite3_open("sisbib.db3", &db);
	    if( rc ){
			sprintf(erro, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			//return(0);
	    }
		list=list->next;
	    sprintf(sql,"SELECT Nome, NumChamada, ExemplarPrateleira FROM Livros WHERE AutorPrincipal LIKE '%%%s%%';", gtk_entry_get_text(GTK_ENTRY(list->data)));
	    p=(Nomes_Livros *)malloc(sizeof(Nomes_Livros));
	    p->n_col=0;
	    rc = sqlite3_exec(db, sql, Nomes_dos_Livros, (void *) p, &zErrMsg);
	    if( rc != SQLITE_OK ){
			sprintf(erro, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			//return 0;
	    }else{ 
			for(int i=0;i<p->n_col;i++){
				gtk_list_store_append (GTK_LIST_STORE(Widgets_Resultado[1]), &iter);
				gtk_list_store_set (GTK_LIST_STORE(Widgets_Resultado[1]), &iter,
									0, p->Nomes[i],
									1, p->NumCha[i],
									2, p->Exemplar[i],
									3, p->Status[i],
									-1);
		    }
	    }
	   
	    sqlite3_close(db);
        //================================================================================================
	}
	
	g_signal_connect(Janela_Resultado_Consulta_Livro, "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Janela_Resultado_Consulta_Livro);
	//g_signal_connect(Confirmar_Resultado_Consulta_Button, "clicked", G_CALLBACK (on_Confirmar_Resultado_Consulta_Button_clicked), Widgets_Resultado);
	
	gtk_builder_connect_signals(builder, NULL);
 
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Resultado_Consulta_Livro);
}

G_MODULE_EXPORT void on_Buscar_Periodico_Button_clicked(GtkWidget *Button, GtkBox *box){
	sqlite3 *db;
	GtkBuilder *builder;
	GtkWidget *Widgets_Resultado[3];
	GtkTreeIter iter;
	GList *list;
	int  rc;
	char *zErrMsg = 0;
    char erro[100];
	char sql[500];
    Nomes_Periodicos *p;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Resultado da Consulta do Periodico.glade", NULL);
	
	Widgets_Resultado[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Resultado_Consulta_Periodico"));
	Widgets_Resultado[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Lista_Periodico"));
	Widgets_Resultado[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Erro"));
	list = gtk_container_get_children(GTK_CONTAINER(box));
	if(!strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(list->data)), "Nome")){
		//SQL
	    rc = sqlite3_open("sisbib.db3", &db);
	    if( rc ){
			sprintf(erro, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			gtk_label_set_text(GTK_LABEL(Widgets_Resultado[2]), erro);
			sqlite3_close(db);
			//return(0);
	    }
		
		list=list->next;
	    sprintf(sql,"SELECT Nome, NumChamada, LocSecao, LocEstante, LocPrateleira, Status FROM Periodicos WHERE Nome LIKE '%%%s%%';", gtk_entry_get_text(GTK_ENTRY(list->data)));
	    p=(Nomes_Periodicos *)malloc(sizeof(Nomes_Periodicos));
	    p->n_col=0;
	    rc = sqlite3_exec(db, sql, Nomes_dos_Periodicos, (void *) p, &zErrMsg);
	    if( rc != SQLITE_OK ){
			sprintf(erro, "SQL error: %s\n", zErrMsg);
			gtk_label_set_text(GTK_LABEL(Widgets_Resultado[2]),erro);
			sqlite3_free(zErrMsg);
			//return 0;
	    }else{ 
			for(int i=0;i<p->n_col;i++){
				gtk_list_store_append (GTK_LIST_STORE(Widgets_Resultado[1]), &iter);
				gtk_list_store_set (GTK_LIST_STORE(Widgets_Resultado[1]), &iter,
									0, p->Nomes[i],
									1, p->NumCha[i],
									2, p->Secao[i],
									3, p->Estante[i],
									4, p->Prateleira[i],
									5, p->Status[i],
									-1);
		    }
	    }
	    sqlite3_close(db);
        //================================================================================================
	}
	else{
		//SQL
	    rc = sqlite3_open("sisbib.db3", &db);
	    if( rc ){
			sprintf(erro, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
			gtk_label_set_text(GTK_LABEL(Widgets_Resultado[2]), erro);
			sqlite3_close(db);
			//return(0);
	    }
		list=list->next;
	    sprintf(sql,"SELECT Nome, NumChamada, LocSecao, LocEstante, LocPrateleira, Status FROM Periodicos WHERE TituloEdicao LIKE '%%%s%%';", gtk_entry_get_text(GTK_ENTRY(list->data)));
	    p=(Nomes_Periodicos *)malloc(sizeof(Nomes_Periodicos));
	    p->n_col=0;
	    rc = sqlite3_exec(db, sql, Nomes_dos_Periodicos, (void *) p, &zErrMsg);
	    if( rc != SQLITE_OK ){
			sprintf(erro, "SQL error: %s\n", zErrMsg);
			gtk_label_set_text(GTK_LABEL(Widgets_Resultado[2]), erro);
			sqlite3_free(zErrMsg);
			//return 0;
	    }else{ 
			for(int i=0;i<p->n_col;i++){
				gtk_list_store_append (GTK_LIST_STORE(Widgets_Resultado[1]), &iter);
				gtk_list_store_set (GTK_LIST_STORE(Widgets_Resultado[1]), &iter,
									0, p->Nomes[i],
									1, p->NumCha[i],
									2, p->Secao[i],
									3, p->Estante[i],
									4, p->Prateleira[i],
									5, p->Status[i],
									-1);
		    }
	    }
	   
	    sqlite3_close(db);
        //================================================================================================
	}
	
	g_signal_connect(Widgets_Resultado[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Resultado[0]);
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Resultado[0]);
}

G_MODULE_EXPORT void on_Confirmar_Resultado_Consulta_Button_clicked(GtkWidget *Button, GtkEntry *Entrada){
	GtkBuilder *builder;
	GtkWidget *Janela_Reserva_Livro,*Numero_Chamada_Reservar_Entry, *NumCha;
	GtkWidget *Matricula_Reserva_Entry, *Senha_Reserva_Entry, *Confirmar_Reserva_Button, *Data_Calendar_Reservar;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Tela de Reservar.glade", NULL);
	
	Janela_Reserva_Livro = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Reserva_Livro"));
	Numero_Chamada_Reservar_Entry = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Chamada_Reservar_Entry"));
	Matricula_Reserva_Entry = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Reserva_Entry"));
	Senha_Reserva_Entry = GTK_WIDGET(gtk_builder_get_object(builder, "Senha_Reserva_Entry"));
	Confirmar_Reserva_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Reserva_Button"));
	Data_Calendar_Reservar = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Reservar"));
	
	
	Widgets_Reservar[0] = Janela_Reserva_Livro;
	Widgets_Reservar[1] = Numero_Chamada_Reservar_Entry;
	Widgets_Reservar[2] = Matricula_Reserva_Entry;
	Widgets_Reservar[3] = Senha_Reserva_Entry;
	Widgets_Reservar[4] = Confirmar_Reserva_Button;
	Widgets_Reservar[5] = Data_Calendar_Reservar;
	
	gtk_entry_set_text(GTK_ENTRY(Numero_Chamada_Reservar_Entry), gtk_entry_get_text(Entrada));
	g_signal_connect(Janela_Reserva_Livro, "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Janela_Reserva_Livro);
	g_signal_connect(Confirmar_Reserva_Button, "clicked", G_CALLBACK (on_Confirmar_Reserva_Button_clicked), Confirmar_Reserva_Button);
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Reserva_Livro);
	
}
void on_Confirmar_Reserva_Button_clicked(GtkWidget *Button){
	sqlite3 *db;
	int  rc;
	char *zErrMsg = 0;
	char sql[500];
	data x;
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
    }
	gtk_calendar_get_date(GTK_CALENDAR(Widgets_Reservar[5]), &x.ano, &x.mes, &x.dia);
	sprintf(sql,"INSERT INTO `Reservas` VALUES('%s','%s','%i-%i-%i','NULL','NULL');", gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[1])), gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[2])), x.ano, x.mes+1, x.dia);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
    }
		
    
	sqlite3_close(db);
}


void on_Consultar_Usuarios_Button_clicked(GtkWidget *Button){
	//GtkBuilder *builder;
	//GtkWidget *Janela_Menu, *Cadastrar_Livro_Buttton, *Consultar_Acervo_Button;
	//GtkWidget *Consultar_Usuarios_Button, *Relatorios_Button, *Sair_Button;
}

void on_Relatorios_Button_clicked(GtkWidget *Button){
	//GtkBuilder *builder;
	//GtkWidget *Janela_
}

G_MODULE_EXPORT void on_Cadastrar_Usuario_Button_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	GtkWidget *Janela_Cadastro_Usuario, *Nome_Entry, *Matricula_Entry, *Cadastrar_Usuario_Button;
	GtkWidget *Escola_Combo_Box_Text, *RG_Entry, *Tipo_Usuario_Combo_Box, *Widgets_Usuario[7];
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Cadastro de Usuario.glade", NULL);
	
	Widgets_Usuario[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Usuario"));
	Widgets_Usuario[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_Entry"));
	Widgets_Usuario[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Entry"));
	Widgets_Usuario[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Escola_Combo_Box_Text"));
	Widgets_Usuario[4] = GTK_WIDGET(gtk_builder_get_object(builder, "RG_Entry"));
	Widgets_Usuario[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Tipo_Usuario_Combo_Box"));
	Widgets_Usuario[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Usuario_Button"));
		
	//g_signal_connect(Widgets_Usuario[6], "clicked", G_CALLBACK (on_Cadastrar_Usuario_Button_clicked), Widgets_Usuario);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Usuario[0]);
}


//==========================================================================================================================================
//Funçoes relacionadas ao controle de widgets

G_MODULE_EXPORT void on_gtk_fechar_sub_win(GtkWidget *Button, GtkWidget *Janela)
{
    gtk_widget_destroy(Janela);	
}

void on_Sair_Button_clicked(GtkWidget *Button, GtkWidget *widgets[]){
	
	gtk_entry_set_text(GTK_ENTRY(widgets[1]), "");
	gtk_entry_set_text(GTK_ENTRY(widgets[2]), "");
	gtk_widget_show_all(widgets[0]);
	gtk_widget_destroy(widgets[5]);

}

G_MODULE_EXPORT void on_toggled (GtkCellRendererToggle *toggle, gchar *str_path, GtkListStore *Lista){
	gboolean boolean;
	GtkTreeIter iter;
	GtkTreePath *path = gtk_tree_path_new_from_string (str_path);

	gtk_tree_model_get_iter (GTK_TREE_MODEL (Lista), &iter, path);
	gtk_tree_model_get(GTK_TREE_MODEL(Lista), &iter, 4, &boolean, -1);
	gtk_list_store_set (Lista, &iter, 4, !boolean, -1);
	gtk_tree_path_free (path);
}

G_MODULE_EXPORT void on_toggled_periodico (GtkCellRendererToggle *toggle, gchar *str_path, GtkListStore *Lista){
	gboolean boolean;
	GtkTreeIter iter;
	GtkTreePath *path = gtk_tree_path_new_from_string (str_path);

	gtk_tree_model_get_iter (GTK_TREE_MODEL (Lista), &iter, path);
	gtk_tree_model_get(GTK_TREE_MODEL(Lista), &iter, 6, &boolean, -1);
	gtk_list_store_set (Lista, &iter, 6, !boolean, -1);
	gtk_tree_path_free (path);
}
G_MODULE_EXPORT void on_Data_Button_clicked(GtkWidget *Button, GtkWidget *Box_Calendario){
	gtk_widget_show(Box_Calendario);
}

G_MODULE_EXPORT void on_OK_Calendar_clicked(GtkWidget *Button, GtkWidget *Box_Calendario){
	gtk_widget_hide(Box_Calendario);
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

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}