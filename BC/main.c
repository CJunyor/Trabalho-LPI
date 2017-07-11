#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sqlite3.h"
#include "funcoes.h"


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
	gchar escolha[11];
	static GtkWidget *Widgets_Cadastro[19];
	strncpy(escolha, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Texto_Combo_Box)), 10);
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
		g_signal_connect(Widgets_Cadastro[17], "clicked", G_CALLBACK (on_Cadastro_Livro_Button_clicked), Widgets_Cadastro[17]);
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
		g_signal_connect(Widgets_Cadastro[16], "clicked", G_CALLBACK (on_Cadastro_Periodico_Button_clicked), Widgets_Cadastro[16]);
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
	  
		gtk_widget_show_all(Widgets_Cadastro[0]);
		
	}
}

void on_Cadastro_Livro_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Cadastro[]){
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc, k=0;
	Acervo *p;
	char comandosql[500], Erro[100];
	GtkWidget *dialog;
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
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
        sprintf(Erro, "SQL error: %s", zErrMsg);
		dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog); 
		sqlite3_free(zErrMsg);
    }else{
		sprintf(comandosql, "SELECT NumChamada FROM Livros WHERE NumChamada='%s';", (p->L).NumCha);
		rc = sqlite3_exec(db, comandosql, Contar, &k, &zErrMsg);
		if( rc != SQLITE_OK ){
				sprintf(Erro, "SQL error: %s", zErrMsg);
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				sqlite3_free(zErrMsg);
		}else{
			if(k==0){
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
				if(!strcmp((p->L).Autor2,"")) strcat(comandosql,"NULL");
				else strcat(comandosql,(p->L).Autor2);
				strcat(comandosql,"','");
				if(!strcmp((p->L).Autor3,"")) strcat(comandosql,"NULL");
				else strcat(comandosql,(p->L).Autor3);
				strcat(comandosql,"','");
				if(!strcmp((p->L).Autor4,"")) strcat(comandosql,"NULL");
				else strcat(comandosql,(p->L).Autor4);
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
				
				rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
					sprintf(Erro, "SQL error: %s", zErrMsg);
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					sqlite3_free(zErrMsg);
				}else{
					strcpy(Erro, "Cadastro efetuado com sucesso!");
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Sucesso!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog);
					gtk_widget_destroy(Widgets_Cadastro[0]);	
				}
			}else{
				strcpy(Erro, "Esse livro já está cadastrado!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog);
				gtk_widget_destroy(Widgets_Cadastro[0]);
			}
		}
	}
    sqlite3_close(db);
	
	
}

void on_Cadastro_Periodico_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Cadastro[]){
	sqlite3 *db;
    char *zErrMsg = 0;
    int  rc, k=0;
	Acervo *p;
	char comandosql[500], Erro[100];
	GtkWidget *dialog;
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
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
        sprintf(Erro, "SQL error: %s", zErrMsg);
		dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog); 
		sqlite3_free(zErrMsg);
    }else{
		sprintf(comandosql, "SELECT NumChamada FROM Periodicos WHERE NumChamada='%s';", (p->P).NumCha);
		rc = sqlite3_exec(db, comandosql, Contar, &k, &zErrMsg);
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
		}else{
			if(k==0){
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
				
				rc = sqlite3_exec(db, comandosql, callback, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
					sprintf(Erro, "SQL error: %s", zErrMsg);
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					sqlite3_free(zErrMsg);
				}else{
					strcpy(Erro, "Cadastro efetuado com sucesso!");
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Sucesso!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog);
					gtk_widget_destroy(Widgets_Cadastro[0]);
				}
			}else{
				strcpy(Erro, "Esse periodico já está cadastrado!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Cadastro[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog);
				gtk_widget_destroy(Widgets_Cadastro[0]);
			}
		}
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
	GtkWidget *Widgets_Resultado[6];
	GtkTreeIter iter;
	GList *list;
	int  rc;
	char *zErrMsg = 0;
    char erro[100];
	char sql[500];
    Nomes_Livros *p;
	GtkWidget *dialog;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Resultado da Consulta do Livro.glade", NULL);
	
	Widgets_Resultado[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Resultado_Consulta_Livro"));
	Widgets_Resultado[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Lista_Livro"));
	Widgets_Resultado[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Chamada_Resultado_Entry"));
	Widgets_Resultado[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Proximo_Reserva_Livro_Button"));
	Widgets_Resultado[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Livro_TreeView"));
	Widgets_Resultado[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Erro"));
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
			gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Widgets_Resultado[4]),TRUE);
			if(p->n_col==0){
				sprintf(erro, "Nenhum livro foi encontrado com esse nome: %s", gtk_entry_get_text(GTK_ENTRY(list->data)) );
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Resultado[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				gtk_widget_destroy(Widgets_Resultado[0]);
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
			gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Widgets_Resultado[4]),TRUE);
			if(p->n_col==0){
				sprintf(erro, "Nenhum autor foi encontrado com esse nome: %s", gtk_entry_get_text(GTK_ENTRY(list->data)) );
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Resultado[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				gtk_widget_destroy(Widgets_Resultado[0]);
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
	    }
	   
	    sqlite3_close(db);
        //================================================================================================
	}
	
	g_signal_connect(Widgets_Resultado[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Resultado[0]);
		
	gtk_builder_connect_signals(builder, NULL);
 
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Resultado[0]);
}

G_MODULE_EXPORT void on_Buscar_Periodico_Button_clicked(GtkWidget *Button, GtkBox *box){
	sqlite3 *db;
	GtkBuilder *builder;
	GtkWidget *Widgets_Resultado[4];
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
	Widgets_Resultado[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Periodico_TreeView"));
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
				gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Widgets_Resultado[3]),TRUE);
				gtk_list_store_append (GTK_LIST_STORE(Widgets_Resultado[1]), &iter);
				gtk_list_store_set (GTK_LIST_STORE(Widgets_Resultado[1]), &iter,
									0, p->Nomes[i],
									1, p->NumCha[i],
									2, p->Secao[i],
									3, p->Status[i],
									4, p->Estante[i],
									5, p->Prateleira[i],
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
			gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Widgets_Resultado[3]),TRUE);
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

G_MODULE_EXPORT void on_Proximo_Reserva_Livro_Button_clicked(GtkWidget *Button, GtkEntry *Entrada){
	sqlite3 *db;
	int  rc, k=0;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	GtkWidget *dialog;
	GtkBuilder *builder;
	static GtkWidget *Widgets_Reservar[6];
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Tela de Reservar.glade", NULL);
	
	Widgets_Reservar[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Reserva_Livro"));
	Widgets_Reservar[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Chamada_Reservar_Entry"));
	Widgets_Reservar[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Reserva_Entry"));
	Widgets_Reservar[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Senha_Reserva_Entry"));
	Widgets_Reservar[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Reserva_Button"));
	Widgets_Reservar[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Reservar"));
	
	gtk_entry_set_text(GTK_ENTRY(Widgets_Reservar[1]), gtk_entry_get_text(Entrada));
	g_signal_connect(Widgets_Reservar[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Reservar[0]);
	g_signal_connect(Widgets_Reservar[4], "clicked", G_CALLBACK (on_Confirmar_Reserva_Button_clicked), Widgets_Reservar);
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Reservar[0]);
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
        sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
	    dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
	    gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
	    gtk_dialog_run(GTK_DIALOG(dialog));
	    gtk_widget_destroy(dialog); 
	    gtk_widget_destroy(Widgets_Reservar[0]);
	    sqlite3_close(db);
    }else{
		sprintf(sql,"SELECT NumChamada FROM Livros WHERE NumChamada='%s' UNION SELECT NumChamada FROM Periodicos WHERE NumChamada='%s';", gtk_entry_get_text(GTK_ENTRY(Entrada)), gtk_entry_get_text(GTK_ENTRY(Entrada)));
		rc = sqlite3_exec(db, sql, Contar, (void *) &k, &zErrMsg);	
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
		}else{
			printf("%i\n", k);
			if(k==0){
				strcpy(Erro, "Numero de chamada invalido!!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				gtk_widget_destroy(Widgets_Reservar[0]); 
				sqlite3_close(db);
			}
		}
	}
	
}

void on_Confirmar_Reserva_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Reservar[]){
	sqlite3 *db;
	int  rc;
	char *zErrMsg = 0;
	char sql[500], Senha[21], Erro[100];
	GtkWidget *dialog;
	//memset(Senha, '\0', 20);
	data x;
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      sprintf(Erro, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
	  dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
	  gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
	  gtk_dialog_run(GTK_DIALOG(dialog));
	  gtk_widget_destroy(dialog); 
	  sqlite3_close(db);
    }
	else{
		sprintf(sql,"SELECT Senha FROM SenhasUsuarios WHERE Matricula LIKE '%s';", gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[2])));
		rc = sqlite3_exec(db, sql, ProcurarSenha, (void *) Senha, &zErrMsg);
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s\n", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
		}else{
			if(!strcmp(Senha, gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[3])))){
				gtk_calendar_get_date(GTK_CALENDAR(Widgets_Reservar[5]), &x.ano, &x.mes, &x.dia);
				sprintf(sql,"INSERT INTO `Reservas` VALUES('%s','%s','%i-%i-%i','NULL','NULL');", gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[1])), gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[2])), x.ano, x.mes+1, x.dia);
				rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
					sprintf(Erro, "SQL error: %s\n", zErrMsg);
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					sqlite3_free(zErrMsg);
				}else{
					sprintf(sql,"BEGIN TRANSACTION; UPDATE Livros SET Status='Reservado' WHERE NumChamada='%s'; UPDATE Periodicos SET Status='Reservado' WHERE NumChamada='%s';ROLLBACK;", gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[2])),  gtk_entry_get_text(GTK_ENTRY(Widgets_Reservar[2])));
					rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
					if( rc != SQLITE_OK ){
						sprintf(Erro, "SQL error: %s", zErrMsg);
						dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
						gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
						gtk_dialog_run(GTK_DIALOG(dialog));
						gtk_widget_destroy(dialog); 
						sqlite3_free(zErrMsg);
					}else{
						strcpy(Erro, "Reserva feita com sucesso!");
						dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
						gtk_window_set_title(GTK_WINDOW(dialog), "Sucesso!");
						gtk_dialog_run(GTK_DIALOG(dialog));
						gtk_widget_destroy(dialog);
						gtk_widget_destroy(Widgets_Reservar[0]);
					}
				}
			}
			else{
				strcpy(Erro, "Matricula ou Senha Errados!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Reservar[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
			}
		}
	}	
    
	sqlite3_close(db);
}

G_MODULE_EXPORT void on_Proximo_Emprestimo_Livro_Button_clicked(GtkWidget *Button, GtkEntry *Entrada){
	sqlite3 *db;
	int  rc, k=0;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	GtkWidget *dialog;
	GtkBuilder *builder;
	static GtkWidget *Widgets_Emprestimo[7];
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Tela de Emprestimo.glade", NULL);
			
	Widgets_Emprestimo[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Emprestimo"));
	Widgets_Emprestimo[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Chamada_Emprestimo_Entry"));
	Widgets_Emprestimo[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Emprestimo_Entry"));
	Widgets_Emprestimo[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Senha_Emprestimo_Entry"));
	Widgets_Emprestimo[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Dias_Emprestimo_Combo_Box"));
	Widgets_Emprestimo[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Emprestimo_Button"));
	Widgets_Emprestimo[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Emprestimo"));
			
	gtk_entry_set_text(GTK_ENTRY(Widgets_Emprestimo[1]), gtk_entry_get_text(Entrada));
	g_signal_connect(Widgets_Emprestimo[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Emprestimo[0]);
	g_signal_connect(Widgets_Emprestimo[5], "clicked", G_CALLBACK (on_Confirmar_Emprestimo_Button_clicked), Widgets_Emprestimo);
	gtk_builder_connect_signals(builder, NULL);
		  
	g_object_unref(builder);
		  
	gtk_widget_show_all(Widgets_Emprestimo[0]);
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
        sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
	    dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
	    gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
	    gtk_dialog_run(GTK_DIALOG(dialog));
	    gtk_widget_destroy(dialog); 
	    gtk_widget_destroy(Widgets_Emprestimo[0]);
	    sqlite3_close(db);
    }else{
		sprintf(sql,"SELECT NumChamada FROM Livros WHERE NumChamada='%s' UNION SELECT NumChamada FROM Periodicos WHERE NumChamada='%s' UNION ALL SELECT NumChamada FROM EmprestimosRenovacoes WHERE NumChamada='%s' UNION ALL SELECT NumChamada FROM Reservas WHERE NumChamada='%s'", gtk_entry_get_text(GTK_ENTRY(Entrada)), gtk_entry_get_text(GTK_ENTRY(Entrada)), gtk_entry_get_text(GTK_ENTRY(Entrada)), gtk_entry_get_text(GTK_ENTRY(Entrada)));
		rc = sqlite3_exec(db, sql, Contar, (void *) &k, &zErrMsg);	
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
		}else{
			printf("%i\n", k);
			if(k==0){
				strcpy(Erro, "Numero de chamada invalido!!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				gtk_widget_destroy(Widgets_Emprestimo[0]); 
				sqlite3_close(db);
			}else if(k>1){
				strcpy(Erro, "Livro já foi emprestado ou está reservado!!");
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				gtk_widget_destroy(Widgets_Emprestimo[0]); 
				sqlite3_close(db);
			}
		}
	}
}

void on_Confirmar_Emprestimo_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Emprestimo[]){
	sqlite3 *db;
	int  rc, k=0,c;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	char DE[15];
	STU ST;
	GtkWidget *dialog;
	data x,y;
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
      sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
	  dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
	  gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
	  gtk_dialog_run(GTK_DIALOG(dialog));
	  gtk_widget_destroy(dialog); 
	  gtk_widget_destroy(Widgets_Emprestimo[0]);
	  sqlite3_close(db);
    }
	else{
		ST.T='I';
		sprintf(sql,"SELECT U.TipoUsuario, S.Senha FROM Usuarios AS U JOIN SenhasUsuarios AS S on U.Matricula=S.Matricula WHERE U.Matricula='%s';", gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[2])));
		rc = sqlite3_exec(db, sql, Senha_e_Tipo, (void *) &ST, &zErrMsg);
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
		}else if(!strcmp(ST.Senha, gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[3])))&&ST.T!='I'){
			k=0;
			sprintf(sql,"SELECT NumChamada FROM EmprestimosRenovacoes where Matricula='%s';", gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[2])));
			rc = sqlite3_exec(db, sql, Contar, (void *) &k, &zErrMsg);
			if( rc != SQLITE_OK ){
				sprintf(Erro, "SQL error: %s", zErrMsg);
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				sqlite3_free(zErrMsg);
			}else{
				if((k<3&&ST.T=='A')||(k<5&&ST.T=='P')){
					gtk_calendar_get_date(GTK_CALENDAR(Widgets_Emprestimo[6]), &x.ano, &x.mes, &x.dia);
					sscanf(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Widgets_Emprestimo[4])),"%i dias",&c);
					printf("%i\n", c);
					sprintf(sql,"SELECT DATE('%i-%02i-%02i','+%i day');", x.ano, x.mes+1, x.dia, c);
					rc = sqlite3_exec(db, sql, pegardata, (void *) DE, &zErrMsg);
					if( rc != SQLITE_OK ){
						sprintf(Erro, "SQL error: %s", zErrMsg);
						dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
						gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
						gtk_dialog_run(GTK_DIALOG(dialog));
						gtk_widget_destroy(dialog); 
						sqlite3_free(zErrMsg);
					}
					else{
						sprintf(sql,"INSERT INTO `EmprestimosRenovacoes` VALUES('%s','%s','%i-%02i-%02i','%i','1','%s','%s','NULL','NULL');", 
																				gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[1])), 
																				gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[2])),
																				x.ano, x.mes+1, x.dia,
																				c,
																				gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[3])),
																				DE);
						rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
						if( rc != SQLITE_OK ){
							sprintf(Erro, "SQL error: %s", zErrMsg);
							dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
							gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
							gtk_dialog_run(GTK_DIALOG(dialog));
							gtk_widget_destroy(dialog); 
							sqlite3_free(zErrMsg);
						}else{
							sprintf(sql,"BEGIN TRANSACTION; UPDATE Livros SET Status='Emprestado' WHERE NumChamada='%s'; UPDATE Periodicos SET Status='Emprestado' WHERE NumChamada='%s';ROLLBACK;", gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[1])), gtk_entry_get_text(GTK_ENTRY(Widgets_Emprestimo[1])));
							rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
							if( rc != SQLITE_OK ){
								sprintf(Erro, "SQL error: %s", zErrMsg);
								dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
								gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
								gtk_dialog_run(GTK_DIALOG(dialog));
								gtk_widget_destroy(dialog); 
								sqlite3_free(zErrMsg);
							}else{
								strcpy(Erro, "Emprestimo feito com sucesso!");
								dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
								gtk_window_set_title(GTK_WINDOW(dialog), "Sucesso!");
								gtk_dialog_run(GTK_DIALOG(dialog));
								gtk_widget_destroy(dialog);
								gtk_widget_destroy(Widgets_Emprestimo[0]);
							}
						}
					}
				}else{
					strcpy(Erro, "Usuario ultrapassou o numero de emprestimos!");
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					gtk_widget_destroy(Widgets_Emprestimo[0]);
				}
			}
		}else{
			strcpy(Erro, "Matricula ou Senha Errados!");
			dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Emprestimo[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
		}
	}	
    
	sqlite3_close(db);
}

G_MODULE_EXPORT void on_Cadastrar_Usuario_Button_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	GtkWidget *Janela_Cadastro_Usuario;
	static GtkWidget *Widgets_Usuario[14];
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Cadastro de Usuario.glade", NULL);
	
	Widgets_Usuario[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Usuario"));
	Widgets_Usuario[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_Entry"));
	Widgets_Usuario[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Entry"));
	Widgets_Usuario[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Escola_Combo_Box_Text"));
	Widgets_Usuario[4] = GTK_WIDGET(gtk_builder_get_object(builder, "RG_Entry"));
	Widgets_Usuario[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Tipo_Usuario_Combo_Box"));
	Widgets_Usuario[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Orgao_Expeditor_Entry"));
	Widgets_Usuario[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Expedicao_Calendar"));
	Widgets_Usuario[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Cadastro_Calendar"));
	Widgets_Usuario[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Proximo_Usuario_Button"));
		
	g_signal_connect(Widgets_Usuario[9], "clicked", G_CALLBACK (on_Proximo_Usuario_Button_clicked), Widgets_Usuario);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Usuario[0]);
}

void on_Proximo_Usuario_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Usuario[]){
	GtkBuilder *builder;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Cadastrar Usuario.glade", NULL);
	
	Widgets_Usuario[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro"));
	Widgets_Usuario[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Senha_Entry"));
	Widgets_Usuario[12] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Cadastro_Usuario_Button"));
	Widgets_Usuario[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Senha_Entry"));
	
	g_signal_connect(Widgets_Usuario[12], "clicked", G_CALLBACK (on_Confirmar_Cadastro_Usuario_Button_clicked), Widgets_Usuario);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Usuario[10]);
}

void on_Confirmar_Cadastro_Usuario_Button_clicked(GtkWidget *Button, GtkWidget *Widgets_Usuario[]){
	sqlite3 *db;
	int  rc, k=0;
	char *zErrMsg = 0;
	char sql[500], Erro[100], CodEscola[11];
	GtkWidget *dialog;
	data x,y;
	if(!strcmp(gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[11])),gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[13])))){
		rc = sqlite3_open("sisbib.db3", &db);
		if( rc ){
		  sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
		  dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		  gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		  gtk_dialog_run(GTK_DIALOG(dialog));
		  gtk_widget_destroy(dialog); 
		  sqlite3_close(db);
		}
		else{
			sprintf(sql,"SELECT Matricula FROM Usuarios WHERE Matricula='%s';", gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[2])));
			rc = sqlite3_exec(db, sql, Contar, (void *) &k, &zErrMsg);
			if( rc != SQLITE_OK ){
				sprintf(Erro, "SQL error: %s", zErrMsg);
				dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				sqlite3_free(zErrMsg);
			}else{
				if(k==0){
					sprintf(sql,"SELECT CodEscola FROM Escolas WHERE NomeEscola='%s';",gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Widgets_Usuario[3])));
					rc = sqlite3_exec(db, sql, PegarString,(void *) CodEscola, &zErrMsg);
					if( rc != SQLITE_OK ){
						sprintf(Erro, "SQL error: %s", zErrMsg);
						dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
						gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
						gtk_dialog_run(GTK_DIALOG(dialog));
						gtk_widget_destroy(dialog); 
						sqlite3_free(zErrMsg);
					}else{
						gtk_calendar_get_date(GTK_CALENDAR(Widgets_Usuario[7]), &x.ano, &x.mes, &x.dia);
						gtk_calendar_get_date(GTK_CALENDAR(Widgets_Usuario[8]), &y.ano, &y.mes, &y.dia);
						sprintf(sql,"INSERT INTO `Usuarios` VALUES('%s','%s','%c','%s','%s','%i-%02i-%02i','%s','%i-%02i-%02i','0','NULL','NULL','0','NULL','NULL');", 
																						gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[2])),
																						gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[1])),
																						gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Widgets_Usuario[5]))[0],
																						gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[4])),
																						gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[6])),
																						x.ano, x.mes+1, x.dia,
																						CodEscola,
																						y.ano, y.mes+1, y.dia);																				
						rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
						if( rc != SQLITE_OK ){
							sprintf(Erro, "SQL error: %s", zErrMsg);
							dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
							gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
							gtk_dialog_run(GTK_DIALOG(dialog));
							gtk_widget_destroy(dialog); 
							sqlite3_free(zErrMsg);
						}else{
							sprintf(sql,"INSERT INTO SenhasUsuarios VALUES('%s','%s');",gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[2])),gtk_entry_get_text(GTK_ENTRY(Widgets_Usuario[11])));
							rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
							if( rc != SQLITE_OK ){
								sprintf(Erro, "SQL error: %s", zErrMsg);
								dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
								gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
								gtk_dialog_run(GTK_DIALOG(dialog));
								gtk_widget_destroy(dialog); 
								sqlite3_free(zErrMsg);
							}else{
								strcpy(Erro, "Cadastro efetuado com sucesso!");
								dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
								gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
								gtk_dialog_run(GTK_DIALOG(dialog));
								gtk_widget_destroy(dialog);
								gtk_widget_destroy(Widgets_Usuario[0]);
								gtk_widget_destroy(Widgets_Usuario[10]);
							}
						}
					}
				}else{
					strcpy(Erro, "Essa matricula já foi cadastrada!");
					dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog);
					gtk_widget_destroy(Widgets_Usuario[0]);
					gtk_widget_destroy(Widgets_Usuario[10]);
				}
			}
		}
	}else{
		strcpy(Erro, "Senhas diferentes!");
		dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets_Usuario[10]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
}

G_MODULE_EXPORT void on_Consultar_Usuarios_Button_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	static GtkWidget *Consultar_Usuario[5];
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Consultar Usuário.glade", NULL);
	
	Consultar_Usuario[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Consultar_Usuario"));
	Consultar_Usuario[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Consultar_Usuario_CBT"));
	Consultar_Usuario[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Entry"));
	Consultar_Usuario[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Consultar_Usuario_Button"));
	
	g_signal_connect(Consultar_Usuario[3], "clicked", G_CALLBACK (on_Consultar_Usuario_Button_clicked), Consultar_Usuario);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Consultar_Usuario[0]);
}

void on_Consultar_Usuario_Button_clicked(GtkWidget *Button, GtkWidget *Consultar_Usuario[]){
	sqlite3 *db;
	int  rc, k=0;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	Matric_Nome x;
	GtkWidget *dialog;
	GtkBuilder *builder;
	GtkWidget *Usuario[5];
	GtkTreeIter iter;
	if(!strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(Consultar_Usuario[1])),"Nome")){
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Resultado da Consulta do Usuario.glade", NULL);
		Usuario[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Resultado_Usuario"));
		Usuario[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Resultado_Entry"));
		Usuario[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Usuario_Resultado_Button"));
		Usuario[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Nomes_Usuarios"));
		Usuario[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Nomes_Usuario_TreeView"));
		
		g_signal_connect(Usuario[2], "clicked", G_CALLBACK (on_Usuario_Resultado_Button_clicked), Usuario[1]);
	
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
  
		gtk_widget_show_all(Usuario[0]);
		
		rc = sqlite3_open("sisbib.db3", &db);
		if( rc ){
		  sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
		  dialog = gtk_message_dialog_new(GTK_WINDOW(Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		  gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		  gtk_dialog_run(GTK_DIALOG(dialog));
		  gtk_widget_destroy(dialog); 
		  sqlite3_close(db);
		  gtk_widget_destroy(Usuario[0]);
		}
		else{
			sprintf(sql,"SELECT Matricula, Nome FROM Usuarios WHERE Nome LIKE '%%%s%%';", gtk_entry_get_text(GTK_ENTRY(Consultar_Usuario[2])));
			x.n_col=0;
			rc = sqlite3_exec(db, sql, Matric_e_Nome, (void *) &x, &zErrMsg);
			if( rc != SQLITE_OK ){
				sprintf(Erro, "SQL error: %s", zErrMsg);
				dialog = gtk_message_dialog_new(GTK_WINDOW(Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				sqlite3_free(zErrMsg);
				gtk_widget_destroy(Usuario[0]);
			}else{
				gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Usuario[4]),TRUE);
				if(x.n_col==0){
					sprintf(Erro, "Nenhum Aluno foi encontrado com esse nome: %s", gtk_entry_get_text(GTK_ENTRY(Consultar_Usuario[2])) );
					dialog = gtk_message_dialog_new(GTK_WINDOW(Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					gtk_widget_destroy(Usuario[0]);
				}else{
					for(int i=0;i<x.n_col;i++){
						gtk_list_store_append (GTK_LIST_STORE(Usuario[3]), &iter);
						gtk_list_store_set (GTK_LIST_STORE(Usuario[3]), &iter,
											0, x.Matricula[i],
											1, x.Nome[i],
											-1);
					}
				}
			}
		}
		
	}else{
		on_Usuario_Resultado_Button_clicked(Consultar_Usuario[3], Consultar_Usuario[2]);
		fprintf(stdout,"MeuPau");
	}
}

void on_Usuario_Resultado_Button_clicked(GtkWidget *Button, GtkWidget *Entrada){
	sqlite3 *db;
	int  rc;
	char *zErrMsg = 0;
	char sql[500], Erro[100], Escola[60], numero[6];
	data DATA;
	Usuarios x;
	Atraso y;
	Reservas z;
	GtkWidget *dialog;
	GtkBuilder *builder;
	static GtkWidget *Menu_Usuario[23];
	GtkTreeIter iter;
	GtkTreePath *path;
	char num[3];
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Menu do Usuário.glade", NULL);
	Menu_Usuario[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Menu_Usuario"));
	Menu_Usuario[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Escola_Menu_Usuario_Entry"));
	Menu_Usuario[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_Menu_Usuario_Entry"));
	Menu_Usuario[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Matricula_Menu_Usuario_Entry"));
	Menu_Usuario[4] = GTK_WIDGET(gtk_builder_get_object(builder, "RG_Menu_Usuario_Entry"));
	Menu_Usuario[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Orgao_Exp_Menu_Usuario_Entry"));
	Menu_Usuario[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Suspenso_Menu_Usuario_Entry"));
	Menu_Usuario[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Exp_Menu_Usuario_Entry"));
	Menu_Usuario[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Num_Dias_Menu_Usuario_Entry"));
	Menu_Usuario[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Cadastro_Menu_Usuario_Entry"));
	Menu_Usuario[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Num_Sus_Menu_Usuario_Entry"));
	Menu_Usuario[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Supensao_Menu_Usuario_Entry"));
	Menu_Usuario[12] = GTK_WIDGET(gtk_builder_get_object(builder, "T_Usuario_Menu_Usuario_Entry"));
	Menu_Usuario[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Renovar_Emprestimo_Menu_Usuario_Button"));
	Menu_Usuario[14] = GTK_WIDGET(gtk_builder_get_object(builder, "Renovar_Reserva_Menu_Usuario_Button"));
	Menu_Usuario[15] = GTK_WIDGET(gtk_builder_get_object(builder, "Baixa_Reserva_Menu_Usuario_Button"));
	Menu_Usuario[16] = GTK_WIDGET(gtk_builder_get_object(builder, "Devolucao_Menu_Usuario_Button"));
	Menu_Usuario[17] = GTK_WIDGET(gtk_builder_get_object(builder, "Atualizar_Menu_Usuario_Button"));
	Menu_Usuario[18] = GTK_WIDGET(gtk_builder_get_object(builder, "Relatorio_Menu_Usuario_Button"));
	Menu_Usuario[19] = GTK_WIDGET(gtk_builder_get_object(builder, "Menu_Usuario_TreeView"));
	Menu_Usuario[20] = GTK_WIDGET(gtk_builder_get_object(builder, "Lista_Menu_Usuario"));
	Menu_Usuario[21] = GTK_WIDGET(gtk_builder_get_object(builder, "Devolucao_Menu_Usuario_Entry"));
	Menu_Usuario[22] = GTK_WIDGET(gtk_builder_get_object(builder, "Baixa_Menu_Usuario_Entry"));
	
	rc = sqlite3_open("sisbib.db3", &db);
	if( rc ){
	  sprintf(Erro, "Erro ao abrir banco de dados: %s", sqlite3_errmsg(db));
	  dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
	  gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
	  gtk_dialog_run(GTK_DIALOG(dialog));
	  gtk_widget_destroy(dialog); 
	  sqlite3_close(db);
	  gtk_widget_destroy(Menu_Usuario[0]);
	}
	else{
		sprintf(sql,"SELECT Nome, Matricula, TipoUsuario, RG, OrgaoExpedidor, CodEscola, DataCadastro, DataExpedicao, DataSuspensao, NumDiasSuspensao, NumSuspensoes FROM Usuarios WHERE Matricula='%s';", gtk_entry_get_text(GTK_ENTRY(Entrada)));
		rc = sqlite3_exec(db, sql, Dados_Usuarios, (void *) &x, &zErrMsg);
		if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
			gtk_widget_destroy(Menu_Usuario[0]);
		}else{
			sprintf(sql,"SELECT NomeEscola FROM Escolas WHERE CodEscola='%s';", x.CodEscola);
			rc = sqlite3_exec(db, sql, PegarString, (void *) Escola, &zErrMsg);
			if( rc != SQLITE_OK ){
				sprintf(Erro, "SQL error: %s", zErrMsg);
				dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
				gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy(dialog); 
				sqlite3_free(zErrMsg);
				gtk_widget_destroy(Menu_Usuario[0]);
			}else{
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[1]), Escola);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[2]), x.Nome);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[3]), gtk_entry_get_text(GTK_ENTRY(Entrada)));
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[4]), x.RG);
				
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[5]), x.OrgaoExpedidor);
				if(x.Suspenso){ 
					gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[6]), "Sim");
					sscanf(x.DataSuspensao, "%i-%i-%i", &DATA.ano, &DATA.mes, &DATA.dia);
					sprintf(x.DataSuspensao, "%i/%i/%i", DATA.dia, DATA.mes, DATA.ano);
				}
				else gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[6]), "Nao");
				
				sscanf(x.DataExpedicao, "%i-%i-%i", &DATA.ano, &DATA.mes, &DATA.dia);
				sprintf(x.DataExpedicao, "%i/%i/%i", DATA.dia, DATA.mes, DATA.ano);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[7]), x.DataExpedicao);
				
				sprintf(numero, "%i", x.NumDiasSuspensao);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[8]), numero);
				
				sscanf(x.DataCadastro, "%i-%i-%i", &DATA.ano, &DATA.mes, &DATA.dia);
				sprintf(x.DataCadastro, "%i/%i/%i", DATA.dia, DATA.mes, DATA.ano);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[9]), x.DataCadastro);
				
				sprintf(numero, "%i", x.NumSuspensoes);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[10]), numero);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[11]), x.DataSuspensao);
				gtk_entry_set_text(GTK_ENTRY(Menu_Usuario[12]), x.TipoUsuario);
				
				y.n_col=0;
				sprintf(sql,"SELECT L.NumChamada,L.Nome,E.DataEmprestimo, julianday(date('now')) - (julianday(E.DataEmprestimo)+E.NumDiasEmprestimo-1) AS DiasAtraso FROM EmprestimosRenovacoes AS E JOIN Livros AS L ON E.NumChamada = L.NumChamada JOIN Usuarios AS U ON E.Matricula = U.Matricula WHERE E.Matricula='%s';", x.Matricula);
				rc = sqlite3_exec(db, sql, Atraso_Funcao, (void *) &y, &zErrMsg);
				if( rc != SQLITE_OK ){
					sprintf(Erro, "SQL error: %s", zErrMsg);
					dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
					gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
					gtk_dialog_run(GTK_DIALOG(dialog));
					gtk_widget_destroy(dialog); 
					sqlite3_free(zErrMsg);
					gtk_widget_destroy(Menu_Usuario[0]);
				}else{
					gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Menu_Usuario[19]),TRUE);
					for(int i=0;i<y.n_col;i++){
						gtk_list_store_append (GTK_LIST_STORE(Menu_Usuario[20]), &iter);
						gtk_list_store_set (GTK_LIST_STORE(Menu_Usuario[20]), &iter,
											0, y.NumCha[i],
											1, y.nome[i],
											2, y.DataEmprestimo[i],
											3, y.DiasAtraso[i],
											4, y.DiasAtraso[i]*0.10,
											-1);
					}
					z.n_col=0;
					sprintf(sql,"SELECT Livros.NumChamada,Nome FROM Livros JOIN Reservas Where Livros.NumChamada=Reservas.NumChamada AND Reservas.Matricula='%s';", x.Matricula);
					rc = sqlite3_exec(db, sql, Reservas_Funcao, (void *) &z, &zErrMsg);
					if( rc != SQLITE_OK ){
						sprintf(Erro, "SQL error: %s", zErrMsg);
						dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
						gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
						gtk_dialog_run(GTK_DIALOG(dialog));
						gtk_widget_destroy(dialog); 
						sqlite3_free(zErrMsg);
						gtk_widget_destroy(Menu_Usuario[0]);
					}else{
						for(int i=0;i<z.n_col;i++){
							sprintf(num, "%i", i);
							path = gtk_tree_path_new_from_string (num);
							gtk_tree_model_get_iter (GTK_TREE_MODEL(GTK_LIST_STORE(Menu_Usuario[20])), &iter, path);
							gtk_tree_path_free (path);
							gtk_list_store_set (GTK_LIST_STORE(Menu_Usuario[20]), &iter, 5, z.NumCha[i], 6, z.Nome[i], -1);
						}
					}
				}
			}
		}
	}
	g_signal_connect(Menu_Usuario[16], "clicked", G_CALLBACK (on_Devolucao_Menu_Usuario_Button_clicked), Menu_Usuario);
	g_signal_connect(Menu_Usuario[15], "clicked", G_CALLBACK (on_Baixa_Reserva_Menu_Usuario_Button_clicked), Menu_Usuario);

	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Menu_Usuario[0]);

}

void on_Devolucao_Menu_Usuario_Button_clicked(GtkWidget *Button, GtkWidget *Menu_Usuario[]){
	sqlite3 *db;
	int  rc;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	GtkWidget *dialog;
	
	sprintf(sql,"DELETE FROM EmprestimosRenovacoes WHERE NumChamada = '%s';", gtk_entry_get_text(GTK_ENTRY(Menu_Usuario[21])));
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
	}else{
		strcpy(Erro, "Devolucao efetuada com sucesso!");
		dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	
}

void on_Baixa_Reserva_Menu_Usuario_Button_clicked(GtkWidget *Button, GtkWidget *Menu_Usuario[]){
	sqlite3 *db;
	int  rc;
	char *zErrMsg = 0;
	char sql[500], Erro[100];
	GtkWidget *dialog;
	
	sprintf(sql,"DELETE FROM Reservas WHERE NumChamada = '%s';", gtk_entry_get_text(GTK_ENTRY(Menu_Usuario[22])));
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
			sprintf(Erro, "SQL error: %s", zErrMsg);
			dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
			gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog); 
			sqlite3_free(zErrMsg);
	}else{
		strcpy(Erro, "Baixa da reserva efetuada com sucesso!");
		dialog = gtk_message_dialog_new(GTK_WINDOW(Menu_Usuario[0]), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, Erro);
		gtk_window_set_title(GTK_WINDOW(dialog), "Erro!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
}

void on_Relatorios_Button_clicked(GtkWidget *Button){
	//GtkBuilder *builder;
	//GtkWidget *Janela_
}

//==========================================================================================================================================
//Funçoes relacionadas ao controle de widgets

G_MODULE_EXPORT void on_gtk_fechar_sub_win(GtkWidget *Button, GtkWidget *Janela){
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

static int Dados_Usuarios(void *DU, int argc, char **argv, char **azColName){
    Usuarios *p=(Usuarios *) DU;
    strncpy(p->Nome, argv[0] ? argv[0] : "NULL", 50);
    strncpy(p->Matricula, argv[1] ? argv[1] : "NULL", 14);
    p->TipoUsuario[0] = argv[2][0];
    strncpy(p->RG, argv[3] ? argv[3] : "NULL", 14);
    strncpy(p->OrgaoExpedidor, argv[4] ? argv[4] : "NULL", 14);
    strncpy(p->CodEscola, argv[5] ? argv[5] : "NULL", 9);
    strncpy(p->DataCadastro, argv[6] ? argv[6] : "NULL", 12);
    strncpy(p->DataExpedicao, argv[7] ? argv[7] : "NULL", 12);
    strncpy(p->DataSuspensao, argv[8] ? argv[8] : "NULL", 12);
    sscanf(argv[9] ? argv[9] : "0", "%i", &p->Suspenso);
    sscanf(argv[10] ? argv[10] : "0", "%i", &p->NumDiasSuspensao);
    sscanf( argv[11] ? argv[11] : "0", "%i", &p->NumSuspensoes);
    return 0;
}

static int Reservas_Funcao(void *Dados, int argc, char **argv, char **azColName){
    Reservas *p=(Reservas *) Dados;
	strcpy(p->NumCha[p->n_col++], argv[0] ? argv[0] : "NULL");
    strcpy(p->Nome[p->n_col++], argv[1] ? argv[1] : "NULL");
    return 0;
}

static int Atraso_Funcao(void *Dados, int argc, char **argv, char **azColName){
    Atraso *p=(Atraso *) Dados;
	strcpy(p->NumCha[p->n_col], argv[0] ? argv[0] : "NULL");
    strcpy(p->nome[p->n_col], argv[1] ? argv[1] : "NULL");
    strcpy(p->DataEmprestimo[p->n_col], argv[2] ? argv[2] : "NULL");
    sscanf(argv[3] ? argv[3] : "0", "%i", &p->DiasAtraso[p->n_col++]);
    return 0;
}

static int Matric_e_Nome(void *Nome, int argc, char **argv, char **azColName){
    Matric_Nome *p=(Matric_Nome *) Nome;
    strcpy(p->Matricula[p->n_col], argv[0] ? argv[0] : "NULL" );
    strcpy(p->Nome[p->n_col++], argv[1] ? argv[1] : "NULL" );
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

static int ProcurarSenha(void *Senha, int argc, char **argv, char **azColName){
	char *S;
	S=(char *) Senha;
	strncpy(S, argv[0], 20);
	return 0;
}

static int pegardata(void *DATE, int argc, char **argv, char **azColName){
    char *s;
    s = (char *) DATE;
    strcpy(s, argv[0]);
    return 0;
}

static int PegarString(void *String, int argc, char **argv, char **azColName){
	char *S;
	S=(char *) String;
	strncpy(S, argv[0], 10);
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