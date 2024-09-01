#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include "TAD.h"

void moldura (int li,int lf,int ci,int cf,int cor,int fundo)
{
	int i=0;
	textcolor(cor);
	textbackground(fundo);
	gotoxy(ci,li);
	printf("%c",201);
	gotoxy(ci,lf);
	printf("%c",200);
	gotoxy(cf,li);
	printf("%c",187);
	gotoxy(cf,lf);
	printf("%c",188);
	for(i=ci+1; i<cf; i++){
		gotoxy(i,li);
		
		 printf("%c",205);
		gotoxy(i,lf); 
		
		printf("%c",205);
	}
	for(i=li+1; i<lf; i++)
	{
		gotoxy(ci,i); printf("%c",186);
		gotoxy(cf,i); printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void criaMolde(){
	
	moldura(1,29,1,80,7,0);
	moldura(2,4,2,79,7,0);
	
	
	textcolor(7);
	gotoxy(35,3);
	printf("#[ BIBLIOTECA ]#");
	
	//moldura(5,7,2,79,7,0);
	//textcolor(7);
	//gotoxy(4,6);
	//printf("Campo de Informacoes de escolha: ");
	
	moldura(5,15,2,79,7,0);
	textcolor(7);
	gotoxy(37,6);
	printf("#[ MENU ]#");
	gotoxy(22,7);
	textcolor(7);
	printf("[======================================]");
	
	/*
	textcolor(7);
	gotoxy(4,12);
	printf("[A]-Exclusao de livro, por titulo");
	scanf()*/
	
	gotoxy(31,8);
	moldura(16,28,2,79,7,0);
	
	gotoxy(37,6);
	textcolor(7);
	textbackground(0);
}

int main (void){
	char op, livro[100];
	Descritor desc;
	inicializar(desc);
	Autor *autor;
	
	criaMolde();
	textoParaBiario();
	autor=binarioParaLista(desc);
	do{
		textcolor(7);
		gotoxy(4,8);
		printf("[A]-Exclusao de livro, por titulo");
		textcolor(7);
		gotoxy(4,9);
		printf("[B]-Exibir autor");
		textcolor(7);
		gotoxy(4,10);
		printf("[C]-Exibir autor sem livros");
		textcolor(7);
		gotoxy(4,11);
		printf("[D]-Exibir editoras");
		textcolor(7);
		gotoxy(4,12);
		printf("[E]-Exibir binario");
		textcolor(7);
		gotoxy(4,13);
		printf("[ESC]-sair");
		
		textcolor(7);
		gotoxy(50,9);
		printf("Opcao desejada: ");
		op = toupper(getche());
		switch(op){
			case 'A':
				textcolor(7);
				gotoxy(6,17);
				printf("Qual livro deseja excluir: ");
				gets(livro);
				textcolor(7);
				gotoxy(6,18);
				excluiLivros(desc, livro);
				getch();
				LimparTelaInicial();
				break;
			
			case 'B':
				LimparTudo();
				gotoxy(1,1);
				textcolor(7);
				exibirAutor(autor, desc.ini);
				getch();
				LimparTudo();
				break;
				
			case 'C':
				LimparTudo();
				gotoxy(1,1);
				//printf("ooo");
				textcolor(7);
				exibirAutoresSemLivros(autor, desc.ini);
				printf("ddd");
				getch();
				LimparTudo();
				break;
				
			case 'D':
				LimparTudo();
				gotoxy(1,1);
				exibirEditora(desc);
				getch();
				LimparTudo();
				break;
				
			case 'E':
				LimparTudo();
				gotoxy(1,1);
				exibiBinario();
				getch();
				LimparTudo();
				break;
		}	
		
		criaMolde();
		textcolor(7);
		gotoxy(66,9);
		printf(" ");
	}while(op!=27);
	
	textcolor(7);
	textbackground(0);
	gotoxy(1,30);
	return 0;
}
