#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void Login(GtkWidget *, GtkWidget *[]);
void on_Sair_Button_clicked(GtkWidget *, GtkWidget *[]);
void on_Cadastrar_Livro_Buttton_clicked(GtkWidget *);
void on_Cadastrar_Usuario_Button_clicked(GtkWidget *);
void on_Proximo_Escolha_Cadastro_Button_clicked(GtkWidget *, GtkComboBoxText *);
void on_Cadastrar_Usuario_Button_clicked(GtkWidget *);

int main (int argc, char *argv[]){
	GtkBuilder *builder;
	GtkWidget *Widgets_Main[6];
	
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

void Login(GtkWidget *Button, GtkWidget *Widgets_Main[]){
	GtkBuilder *builder;
	GtkWidget *Janela_Menu, *Sair_Button;//*Cadastrar_Livro_Buttton, *Consultar_Acervo_Button;
	//GtkWidget *Consultar_Usuarios_Button, *Relatorios_Button;
	gchar login[20], senha[20];
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(Widgets_Main[1])));
	strcpy(senha, gtk_entry_get_text(GTK_ENTRY(Widgets_Main[2])));
	if(!strcmp(login, "Teste")&& !strcmp(senha, "123456")){
		gtk_label_set_text(GTK_LABEL(Widgets_Main[4]), "");
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Menu.glade", NULL);
		
		Janela_Menu = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Menu"));
		/*
		Cadastrar_Livro_Buttton = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Livro_Buttton"));
		Consultar_Usuarios_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Consultar_Usuarios_Button"));
		Relatorios_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Relatorios_Button"));
		*/
		Widgets_Main[5]=Janela_Menu;
		
		Sair_Button = GTK_WIDGET(gtk_builder_get_object(builder, "Sair_Button"));
		
		g_signal_connect(Janela_Menu, "destroy", G_CALLBACK (on_Sair_Button_clicked), Widgets_Main);
		g_signal_connect(Sair_Button, "clicked", G_CALLBACK (on_Sair_Button_clicked), Widgets_Main);
	
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
  
		gtk_widget_show_all(Janela_Menu);
		gtk_widget_hide(Widgets_Main[0]);
		
	}
	else{
		gtk_label_set_text(GTK_LABEL(Widgets_Main[4]), "Usuário ou Senha Incorretos");
	}
}

G_MODULE_EXPORT void on_Cadastrar_Livro_Buttton_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	GtkWidget *Janela_Pre_Cadastrar_Livro;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Pre_Tela_Cadastrar_Livro.glade", NULL);
	
	Janela_Pre_Cadastrar_Livro = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Pre_Cadastrar_Livro"));
		
	g_signal_connect(Janela_Pre_Cadastrar_Livro, "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Janela_Pre_Cadastrar_Livro);

	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Pre_Cadastrar_Livro);
	
}

G_MODULE_EXPORT void on_Proximo_Escolha_Cadastro_Button_clicked(GtkWidget *Button, GtkComboBoxText *Texto_Combo_Box){
	gchar escolha[10];
	strcpy(escolha, gtk_combo_box_text_get_active_text(Texto_Combo_Box));
	if(!strcmp(escolha, "Livro")){
		GtkBuilder *builder;
		GtkWidget *Widgets_Cadastro[16];
		
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Cadastro de Livro.glade", NULL);
		
		Widgets_Cadastro[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Livro"));
		Widgets_Cadastro[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_do_Livro_Entry"));
		Widgets_Cadastro[2] = GTK_WIDGET(gtk_builder_get_object(builder, "ISBN_Entry"));
		Widgets_Cadastro[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Num_Chamada_Entry"));
		Widgets_Cadastro[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Autor_Principal_Entry"));
		Widgets_Cadastro[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor_Entry"));
		Widgets_Cadastro[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor2_Entry"));
		Widgets_Cadastro[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Outro_Autor3_Entry"));
		Widgets_Cadastro[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Edicao_Entry"));
		Widgets_Cadastro[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Ano_Entry"));
		Widgets_Cadastro[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Editora_Entry"));
		Widgets_Cadastro[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Exemplar_Combo_Box_Text"));
		Widgets_Cadastro[12] = GTK_WIDGET(gtk_builder_get_object(builder, "Forma_Aquisicao_Cadastro_Livro_CBT"));
		Widgets_Cadastro[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar"));
		Widgets_Cadastro[14] = GTK_WIDGET(gtk_builder_get_object(builder, "Cadastrar_Cadastro_Livro_Button"));
		Widgets_Cadastro[15] = GTK_WIDGET(gtk_builder_get_object(builder, "Observacao_Cadastro_Livro_Entry"));
		g_signal_connect(Widgets_Cadastro[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Cadastro[0]);
		//g_signal_connect(Widgets_Cadastro[14], "clicked", G_CALLBACK (Cadastro_Livro_Periodico), Widgets_Cadastro);
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
	  
		gtk_widget_show_all(Widgets_Cadastro[0]);
	}
	else if(!strcmp(escolha, "Periódico")){
		GtkBuilder *builder;
		GtkWidget *Widgets_Cadastro[17];
		
		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "Cadastro de Periódico.glade", NULL);
		
		Widgets_Cadastro[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Cadastro_Periodico"));
		Widgets_Cadastro[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Nome_do_Periodico_Entry"));
		Widgets_Cadastro[2] = GTK_WIDGET(gtk_builder_get_object(builder, "ISSN_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Volume_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Num_Chamada_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Editora_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Copias_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[7] = GTK_WIDGET(gtk_builder_get_object(builder, "Secao_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[8] = GTK_WIDGET(gtk_builder_get_object(builder, "Estante_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[9] = GTK_WIDGET(gtk_builder_get_object(builder, "Prateleira_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[10] = GTK_WIDGET(gtk_builder_get_object(builder, "Ano_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[11] = GTK_WIDGET(gtk_builder_get_object(builder, "Numero_Cadastro_Periodico_Entry"));
		Widgets_Cadastro[12] = GTK_WIDGET(gtk_builder_get_object(builder, "Forma_Aquisicao_Cadastro_Periodico_CBT"));
		Widgets_Cadastro[13] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Publicacao"));
		Widgets_Cadastro[14] = GTK_WIDGET(gtk_builder_get_object(builder, "Data_Calendar_Cadastro"));
		Widgets_Cadastro[15] = GTK_WIDGET(gtk_builder_get_object(builder, "Confirmar_Cadastrar_Periodico_Button"));
		Widgets_Cadastro[16] = GTK_WIDGET(gtk_builder_get_object(builder, "Observacao_Cadastro_Periodico_Entry"));
		
		
		
		g_signal_connect(Widgets_Cadastro[0], "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Widgets_Cadastro[0]);
		//g_signal_connect(Widgets_Cadastro[15], "clicked", G_CALLBACK (Cadastro_Livro_Periodico), Widgets_Cadastro);
		gtk_builder_connect_signals(builder, NULL);
  
		g_object_unref(builder);
	  
		gtk_widget_show_all(Widgets_Cadastro[0]);
		
	}
}

G_MODULE_EXPORT void on_Consultar_Acervo_Button_clicked(GtkWidget *Button){
	GtkBuilder *builder;
	GtkWidget *Widgets_Consultar[7];
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Consulta Acervo.glade", NULL);
	
	Widgets_Consultar[0] = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Consulta_Acervo"));
	Widgets_Consultar[1] = GTK_WIDGET(gtk_builder_get_object(builder, "Escolha_Livro_Combo_Box_Text"));
	Widgets_Consultar[2] = GTK_WIDGET(gtk_builder_get_object(builder, "Buscar_Livro_Entry"));
	Widgets_Consultar[3] = GTK_WIDGET(gtk_builder_get_object(builder, "Buscar_Livro_Button"));
	Widgets_Consultar[4] = GTK_WIDGET(gtk_builder_get_object(builder, "Escolha_Periodico_Combo_Box_Text"));
	Widgets_Consultar[5] = GTK_WIDGET(gtk_builder_get_object(builder, "Buscar_Periodico_Entry"));
	Widgets_Consultar[6] = GTK_WIDGET(gtk_builder_get_object(builder, "Buscar_Periodico_Button"));
	
	//g_signal_connect(Widgets_Consultar[3], "clicked", G_CALLBACK (on_Buscar_Livro_Button_clicked), Widgets_Consultar);
	//g_signal_connect(Widgets_Consultar[6], "clicked", G_CALLBACK (on_Buscar_Periodico_Button_clicked), Widgets_Consultar);
	
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Widgets_Consultar[0]);
	
}

G_MODULE_EXPORT void on_Buscar_Livro_Button_clicked(GtkWidget *Button, GtkEntry *Entry){
	GtkBuilder *builder;
	GtkWidget *Janela_Resultado_Consulta_Acervo;

	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Resultado da Consulta do Livro.glade", NULL);
	
	Janela_Resultado_Consulta_Acervo = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Resultado_Consulta_Acervo"));
	g_signal_connect(Janela_Resultado_Consulta_Acervo, "destroy", G_CALLBACK (on_gtk_fechar_sub_win), Janela_Resultado_Consulta_Acervo);
	gtk_builder_connect_signals(builder, NULL);
  
	g_object_unref(builder);
  
	gtk_widget_show_all(Janela_Resultado_Consulta_Acervo);
}

G_MODULE_EXPORT void on_toggled (GtkCellRendererToggle *toggle, gchar *str_path, GtkListStore *Lista){
	gboolean boolean;
	GtkTreeIter iter;
	GtkTreePath *path = gtk_tree_path_new_from_string (str_path);

	gtk_tree_model_get_iter (GTK_TREE_MODEL (Lista), &iter, path);
	gtk_tree_model_get(GTK_TREE_MODEL(Lista), &iter, 14, &boolean, -1);
	gtk_list_store_set (Lista, &iter, 14, !boolean, -1);
	gtk_tree_path_free (path);
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
G_MODULE_EXPORT void on_Data_Button_clicked(GtkWidget *Button, GtkWidget *Box_Calendario){
	gtk_widget_show(Box_Calendario);
}
G_MODULE_EXPORT void on_OK_Calendar_clicked(GtkWidget *Button, GtkWidget *Box_Calendario){
	gtk_widget_hide(Box_Calendario);
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