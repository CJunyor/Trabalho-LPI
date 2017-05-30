#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void Cadastro(int type, Acervo *p){
    if(type==1){
        fgets(p->L->ISBN,13,stdin);
        fgets(p->L->Nome,50,stdin);
        fgets(p->L->AutorP,30,stdin);
        fgets(p->L->OutrosA,3,stdin);
        fgets(p->L->Edicao,3,stdin);
        fgets(p->L->Ano,4,stdin);
        fgets(p->L->Editora,30,stdin);
        fgets(p->L->NumCha,12,stdin);
        fgets(p->L->cdd->Class,7,stdin);
        fgets(p->L->cdd->Comp,5,stdin);
        fgets(p->L->cdd->Ano,4,stdin);
        fgets(p->L->cdd->Vol,5,stdin);
        fgets(p->L->cdd->Exe,4,stdin);
        scanf("%i / %i / %i",&(p->L->DataCD->dia),&(p->L->DataCD->mes),&(p->L->DataCD->ano));
        scanf("%i",&p->L->FormaA);
        p->L->ExemplarP=1;
    }
    else{
        fgets(p->P->ISBN,8,stdin);
        fgets(p->P->Nome,50,stdin);
        fgets(p->P->Titulo,50,stdin);
        fgets(p->P->Vol,3,stdin);
        fgets(p->P->Num,3,stdin);
        scanf("%i / %i / %i",&(p->P->DataPul->dia),&(p->P->DataPul->mes),&(p->P->DataPul->ano));
        fgets(p->P->NumCha,7,stdin);
        fgets(p->P->Localizacao->Secao,10,stdin);
        fgets(p->P->Localizacao->Estante,4,stdin);
        fgets(p->P->Localizacao->Prateleira,4,stdin);
        scanf("%i",&(p->P->NumC));
        scanf("%i / %i / %i",&(p->P->DataCD->dia),&(p->P->DataCD->mes),&(p->P->DataCD->ano));
        scanf("%i",&(p->P->FormaA));
    }
}//fim cadastro



void Atualizar(int x, Acervo *p){
    if(x==1){
        scanf("%i / %i / %i",&(p->L->DataBaixa->dia),&(p->L->DataBaixa->mes),&(p->L->DataBaixa->ano));
        scanf("%i",&p->L->MotivoB);
    }
    else{
        scanf("%i / %i / %i",&(p->P->DataBaixa->dia),&(p->P->DataBaixa->mes),&(p->P->DataBaixa->ano));
        scanf("%i",&p->P->MotivoB);
    }
}//fim atualizar


void Consultar(char *str, int TConsu, Acervo *p){
    int i;
    if(TConsu==1){
        for(i=0;i<TAMMAX&&(p->type==1||p->type==2);i++){
            if(p->type==1)
                    if(strcmp(str,(p[i]->L->Nome))==0)
                        break;
            else
                    if(strcmp(str,(p[i]->P->Nome))==0)
                        break;
        }
    }
    else{
        for(i=0;i<TAMMAX&&(p->type==1||p->type==2);i++){
            if(p->type==1)
                    if(strcmp(str,(p[i]->L->AutorP))==0)
                        break;
            else
                    if(strcmp(str,(p[i]->P->Titulo))==0)
                        break;
        }
    }
}//fim consultar
