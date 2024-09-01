#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctype.h>
#include <string.h>


struct Autor{
    char sobrenome[100],nome[100];
    Autor *prox;
};

struct Autores{
    Autores *prox;

    Autor *autor;
};

struct Livros{
    char titulo[100];
    int ano,paginas;
    Livros *ant,*prox;

    Autores *autores;
};
struct Editora{
    char nomeEditora[100];
    Editora *prox;

    Livros *livros;
};

struct Descritor{
    Editora *ini,*fim;
    int quant;
};

struct RegLivro{
    char autores[300],titulo[300],editora[100];
    int ano,paginas;
};

Autores *criaCaixaAutores(Autor *pAutor);

void inicializar(Descritor &desc){
    desc.ini=desc.fim=NULL;
    desc.quant=0;
}

void textoParaBiario(void){
    RegLivro livro;

    FILE *ptrB=fopen("Livros.dat","wb");
    FILE *ptrT=fopen("livros.txt","r");

    if(ptrT==NULL)
        printf("Erro de Abertura\n");
    else{
        rewind(ptrB);
        fscanf(ptrT,"%[^|]|%[^|]|%[^|]|%d|%d\n",&livro.autores,&livro.titulo,&livro.editora,&livro.ano,&livro.paginas);
        while (!feof(ptrT)){
            fwrite(&livro,sizeof(RegLivro),1,ptrB);
            fscanf(ptrT,"%[^|]|%[^|]|%[^|]|%d|%d\n",&livro.autores,&livro.titulo,&livro.editora,&livro.ano,&livro.paginas);
        }
        fwrite(&livro,sizeof(RegLivro),1,ptrB);
        fclose(ptrT);
        fclose(ptrB);
    }
}

Editora* criaCaixa(char editora[]){
    Editora *novo=new Editora();

    strcpy(novo->nomeEditora,editora);
    novo->prox=NULL;
    novo->livros=NULL;

    return novo;
}

Editora* buscaEditora(Editora *aux,char editora[]){

    while(aux!=NULL && strcmp(aux->nomeEditora,editora)!=0)
        aux=aux->prox;
    return aux;
}

void inserirEditora(Descritor &desc,char editora[]){
    Editora *aux,*ant,*atual;

    if(buscaEditora(desc.ini,editora)==NULL){
        if(desc.ini==NULL){
           aux=criaCaixa(editora);
           desc.ini=aux;
            desc.fim=aux;
        }
        else{
            if(strcmp(desc.fim->nomeEditora,editora)<0){
                aux=criaCaixa(editora);
                desc.fim->prox=aux;
                desc.fim=aux;
            }
            else{
                if(strcmp(desc.ini->nomeEditora,editora)>0){
                    aux=criaCaixa(editora);
                    aux->prox=desc.ini;
                    desc.ini=aux;
                }
                else{
                    ant=desc.ini;
                    atual=desc.ini->prox;
                    while(strcmp(editora,atual->nomeEditora)>0){
                        ant=atual;
                        atual=atual->prox;
                    }
                    aux=criaCaixa(editora);
                    ant->prox=aux;
                    aux->prox=atual;
                }
            }
        }
        desc.quant++;
    }
}

Autor* buscaAutor(Autor* autor,char nome[],char sobrenome[]){
    Autor *aux;

    aux=autor;
    while (aux!=NULL && (strcmp(aux->nome,nome)!=0 || strcmp(aux->sobrenome,sobrenome)!=0))
        aux=aux->prox;
    return aux;
}

Autor* criaCaixaAutor(char nome[],char sobrenome[]){
    Autor *novo=new Autor();

    strcpy(novo->nome,nome);
    strcpy(novo->sobrenome,sobrenome);
    novo->prox=NULL;

    return novo;
}

Autor* insercaoDeAutor(Autor* autor,char nome[],char sobrenome[]){
    Autor *aux;

    if(buscaAutor(autor,nome,sobrenome)==NULL){
        aux=criaCaixaAutor(nome,sobrenome);
        if(autor==NULL)
            autor=aux;
        else{
            aux->prox=autor;
            autor=aux;
        }
    }
    return autor;
}

Autor* inserirAutor(Autor* autor,char nomeAutor[]){
    int i=0,tl=0,j;
    char nomeCompleto[100],nome[40],sobrenome[60];

    while(i<strlen(nomeAutor)){
        if(nomeAutor[i]==';')
            i+=2;
        else{
            tl=0;
            while(i<strlen(nomeAutor) && nomeAutor[i]!=';'){
                nomeCompleto[tl]=nomeAutor[i];
                i++;
                tl++;
            }
            if(tl>0 && nomeCompleto[0]!='\n'){
                nomeCompleto[tl]='\0';
                j=0;
                tl=0;
                while (nomeCompleto[j]!=','){
                    sobrenome[tl]=nomeCompleto[j];
                    j++;
                    tl++;
                }
                j+=2;
                sobrenome[tl]='\0';
                tl=0;
                while (j< strlen(nomeCompleto)){
                    nome[tl]=nomeCompleto[j];
                    j++;
                    tl++;
                }
                nome[tl]='\0';
                //printf("%s e %s\n",nome,sobrenome);
                autor=insercaoDeAutor(autor,nome,sobrenome);
            }
        }
    }
    return autor;
}

Autores *criaCaixaAutores(Autor *pAutor) {
    Autores *novo=new Autores();

    novo->autor=pAutor;
    novo->prox=NULL;

    return novo;
}

Livros* criaCaixaLivros(RegLivro regLivro){
    Livros *novo= new Livros();

    strcpy(novo->titulo,regLivro.titulo);
    novo->paginas=regLivro.paginas;
    novo->ano=regLivro.ano;

    novo->autores=NULL;
    novo->prox=NULL;
    novo->ant=NULL;

    return novo;
}

void inserirLivro(Descritor &desc,Autor *autor,RegLivro reglivro){
    Editora *aux;
    Livros *novo;
    Autores *novoA;

    aux= buscaEditora(desc.ini,reglivro.editora);
    novo= criaCaixaLivros(reglivro);

    if(aux->livros==NULL)
        aux->livros=novo;
    else{
        aux->livros->ant=novo;
        novo->prox=aux->livros;
        aux->livros= novo;
    }


    int i=0,tl=0,j;
    char nomeCompleto[100],nome[40],sobrenome[60],nomeAutor[200];
    Autor *aux2;


    strcpy(nomeAutor,reglivro.autores);
    while(i<strlen(nomeAutor)){
        if(nomeAutor[i]==';')
            i+=2;
        else{
            tl=0;
            while(i<strlen(nomeAutor) && nomeAutor[i]!=';'){
                nomeCompleto[tl]=nomeAutor[i];
                i++;
                tl++;
            }
            if(tl>0 && nomeCompleto[0]!='\n'){
                nomeCompleto[tl]='\0';
                j=0;
                tl=0;
                while (nomeCompleto[j]!=','){
                    sobrenome[tl]=nomeCompleto[j];
                    j++;
                    tl++;
                }
                j+=2;
                sobrenome[tl]='\0';
                tl=0;
                while (j< strlen(nomeCompleto)){
                    nome[tl]=nomeCompleto[j];
                    j++;
                    tl++;
                }
                nome[tl]='\0';
                aux2= buscaAutor(autor,nome,sobrenome);

                novoA=criaCaixaAutores(aux2);
                novoA->prox=aux->livros->autores;
                aux->livros->autores=novoA;
            }
        }
    }

}

void LimparTelaInicial(){
	int i , j;	
	for(i = 14;i<27;i++)
	{	for(j= 3;j<79;j++)
		{
			gotoxy(j,i);
			printf(" ");
		}
	}
}

void LimparTudo(){
	int i , j;	
	for(i = 1;i<100;i++)
	{	for(j= 1;j<100;j++)
		{
			gotoxy(j,i);
			printf(" ");
		}
	}	
}

Autor* binarioParaLista(Descritor &desc){
    RegLivro livro;
    Autor *listaAutor=NULL;

    FILE *ptrB= fopen("Livros.dat","rb");

    rewind(ptrB);
    fread(&livro,sizeof(RegLivro),1,ptrB);
    while (!feof(ptrB)){
        inserirEditora(desc,livro.editora);
        listaAutor=inserirAutor(listaAutor,livro.autores);
        inserirLivro(desc,listaAutor,livro);
        fread(&livro,sizeof(RegLivro),1,ptrB);

    }
    fclose(ptrB);
    return listaAutor;
}

void excluiAutoresRecursivo(Autores *autores){
    if(autores!=NULL){
        excluiAutoresRecursivo(autores->prox);
        delete(autores);
    }
}

Editora* buscaEditoraLivro(Descritor desc,char tituloLivro[]){ //refaz q eu n te ensinei essa merda tudo errado
    Editora *aux;
    Livros *ajud;
    int achou=0;

    aux=desc.ini;
    while(aux!=NULL && achou!=1){
        ajud=aux->livros;//inicialização n lemnro o nome da struct;
        while(ajud!=NULL && strcmp(ajud->titulo,tituloLivro)!=0)
            ajud=ajud->prox;
        if(ajud!=NULL)
            achou++;
        else
            aux=aux->prox;
    }
    return aux;
}

Livros* buscaLivroTitulo(Editora *editora,char tituloLivro[]){
    Livros *aux;

    aux=editora->livros;
    while(aux->titulo!=NULL && strcmp(aux->titulo,tituloLivro)!=0)
        aux=aux->prox;
    return aux;
}

void excluirBinario(char tituloLivro[]){
    RegLivro reg;

    FILE *ptrB=fopen("Livros.dat","rb+");
    FILE *ptrBnovo=fopen("Livro.dat","ab");

    rewind(ptrB);
    fread(&reg,sizeof(RegLivro),1,ptrB);
    while(!feof(ptrB)){
        if(strcmp(reg.titulo,tituloLivro)!=0)
            fwrite(&reg,sizeof(RegLivro),1,ptrBnovo);
        fread(&reg,sizeof(RegLivro),1,ptrB);
    }
    fclose(ptrB);
    fclose(ptrBnovo);
    remove("Livros.dat");
    rename("Livro.dat","Livros.dat");
}

void excluiLivros(Descritor &desc,char tituloLivro[]){
    Editora *aux1;
    Livros *aux2;

    aux1=buscaEditoraLivro(desc,tituloLivro);
    if(aux1==NULL)
        printf("Livro nao Encontrado");
    else{
        //excluir
        if(strcmp(aux1->livros->titulo,tituloLivro)==0){
            aux2=aux1->livros;
            aux1->livros=aux1->livros->prox;
            if(aux1->livros!=NULL)
                aux1->livros->ant=NULL;
            excluiAutoresRecursivo(aux2->autores);
            excluirBinario(tituloLivro);
            delete(aux2);
        }
        else{
            aux2=buscaLivroTitulo(aux1, tituloLivro);
            if(aux2->prox!=NULL)
                aux2->prox->ant =aux2->ant;
            aux2->ant->prox=aux2->prox;
            //printf("a\n");
            excluiAutoresRecursivo(aux2->autores);
            excluirBinario(tituloLivro);
            delete(aux2);
            printf("Livro Excluido");
        }
    }
}


void exibirEditora(Descritor desc){
    Livros *aux1;
    Autor *aux3;
    Autores *aux2;

    printf("\nEditora: ");

    while(desc.ini!=NULL){
        puts(desc.ini->nomeEditora);
        printf("Livros: \n");

        aux1=desc.ini->livros;
        while(aux1!=NULL){
            puts(aux1->titulo);

            aux2=aux1->autores;
            printf("Autores: \n");
            while (aux2!=NULL){
                printf("%s %s",aux2->autor->sobrenome,aux2->autor->nome);
                printf("\n");

                aux2=aux2->prox;
            }

            aux1=aux1->prox;
        }
        desc.ini=desc.ini->prox;
       // printf("\n");
        printf("\nEditora: ");
        
    }
}

Autores* buscaLivroAutor(Autor *autor,Autores *autores){
    Autores *aux1=autores;

    while(aux1!=NULL && aux1->autor!=autor)
        aux1=aux1->prox;
    return aux1;
}

void exibirAutor(Autor *autor,Editora *editora){
    Livros *aux2;
    Editora *aux1;

    while(autor!=NULL){
    	
        printf("\nAutor:%s %s",autor->sobrenome,autor->nome);

        aux1=editora;
        while(aux1!=NULL){
            aux2=aux1->livros;
            while(aux2!=NULL){
                if(buscaLivroAutor(autor,aux2->autores)!=NULL)
                    printf("\nTitulo: %s\nAno: %d\nPaginas: %d",aux2->titulo,aux2->ano,aux2->paginas);
                aux2=aux2->prox;
            }
            aux1=aux1->prox;
        }
        printf("\n");
        autor=autor->prox;
    }
}

void exibirAutoresSemLivros(Autor *autor,Editora *editora){
    Livros *aux2;
    Editora *aux1;
    Autor *aux3;

    int cont=0;
    //autor=insercaoDeAutor(autor,"leo","anholleto");
    while(autor!=NULL){
        aux1=editora;
        while(aux1!=NULL){
            aux2=aux1->livros;
            while(aux2!=NULL){
                if(buscaLivroAutor(autor,aux2->autores)!=NULL){
                    cont++;
                    //printf("%s %s\n",autor->sobrenome,autor->nome);
                }
                aux2=aux2->prox;
            }
            aux1=aux1->prox;
        }
        if(cont==0)
            printf("Autor: %s %s\n",autor->sobrenome,autor->nome);
        cont =0;
        autor=autor->prox;
    }
}

void exibiBinario(void){
    RegLivro reg;
    FILE *ptrB=fopen("Livros.dat","rb");

    rewind(ptrB);

    rewind(ptrB);
    fread(&reg,sizeof(RegLivro),1,ptrB);
    while (!feof(ptrB)){
        printf("\n%s \n",reg.titulo);
        fread(&reg,sizeof(RegLivro),1,ptrB);
    }

    fclose(ptrB);
}


