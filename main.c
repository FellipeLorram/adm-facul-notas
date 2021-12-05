#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char espacamento[15] = "---------------";
int idAluno = 1;

typedef struct A4{
char Nome[64];
float Av4;
char situacao[20];
_Bool flag;
}A4;

typedef struct Online{
char Nome[64];
float av1, av2, A1, A2, A3, media;
char situacao[20];
_Bool flag;
}Online;

typedef struct Presencial{
char Nome[64];
float av1, av2, av3, media;
char situacao[20];
_Bool flag;
}Presencial;

typedef struct MediasTiradas{
Presencial presencial;
Online online;
A4 av4;
}MediasTiradas;

typedef struct Aluno{
int id;
char Nome[20];
char Matricula[20];
MediasTiradas medias;
struct Aluno *next;
struct Aluno *previous;
}Aluno;

// FUNCOES

//Menus
int Menu();
int MenuCalcRapida();
int opcaoMenuAlunos();

//Caluclos
Presencial calculaPresencial();
Online calculaOnilne();
A4 calculaA4();

//Aluno
void listaDeAlunos(Aluno *primeiroAluno);
Aluno *cadastraAluno(Aluno *primeiroAluno);
Aluno *deletarAluno(Aluno *primeiroAluno);

//Historico
void historico(MediasTiradas medias);
void mediasAluno(MediasTiradas medias);

//Bd
void Salvar(Aluno *primeiroAluno);
Aluno *BuscarMemoria(Aluno *primeiroAluno);
Aluno *LerNaMemoria(Aluno *primeiroAluno, FILE *pArquivo);

//Memoria
void LimpaMemoria(Aluno *primeiroAluno);

int main(){

    int opcaoMenuInicial, opcaoMenusSeguintes;
    MediasTiradas medias;
    medias.av4.flag = false;
    medias.online.flag = false;
    medias.presencial.flag = false;

    Aluno *primeiroAluno = NULL;
    primeiroAluno = BuscarMemoria(primeiroAluno);
    Aluno *novoAluno = NULL;

    do{
        opcaoMenuInicial = Menu();
        if(opcaoMenuInicial == 1){
            do{
                opcaoMenusSeguintes = opcaoMenuAlunos();
                if(opcaoMenusSeguintes == 1){
                    if(primeiroAluno == NULL){
                        primeiroAluno = cadastraAluno(NULL);
                        novoAluno = primeiroAluno;
                        printf("\n\nAluno inserido!!\n");
                        system("pause");
                    }else{
                        novoAluno = cadastraAluno(novoAluno);
                        printf("Aluno inserido!!\n");
                        system("pause");
                    }
                }
                else if(opcaoMenusSeguintes == 2){
                    if(primeiroAluno != NULL) {
                        listaDeAlunos(primeiroAluno);
                        system("pause");
                    }
                    else{
                        printf("\nNao ha nenhum aluno cadastrado\n");
                        system("Pause");
                    }
                }else if(opcaoMenusSeguintes == 3){
                    if(primeiroAluno != NULL) {
                        primeiroAluno = deletarAluno(primeiroAluno);
                        printf("\nAluno Deletado!!\n");
                        system("pause");
                    }
                    else{
                        printf("\nNao ha nenhum aluno cadastrado\n");
                        system("Pause");
                    }
                }

            }while(opcaoMenusSeguintes!=4);
        }else if(opcaoMenuInicial == 2){
            do{
                opcaoMenusSeguintes = MenuCalcRapida();
                if(opcaoMenusSeguintes == 1){
                    medias.presencial = calculaPresencial();
                    system("pause");
                }else if(opcaoMenusSeguintes == 2){
                    medias.online = calculaOnilne();
                    system("pause");
                }else if(opcaoMenusSeguintes == 3){
                    medias.av4 = calculaA4();
                    system("pause");
                }
                else if(opcaoMenusSeguintes == 4){
                    historico(medias);
                    system("pause");
                }


            }while(opcaoMenusSeguintes != 5);
        }else if(opcaoMenuInicial == 3){
            system("cls");
            printf("\n\n\n\n\n\n                       TCHAU\n\n\n\n\n\n");
        }
    }while(opcaoMenuInicial != 3);

    Salvar(primeiroAluno);
    return 0;
}


// MENUS
int Menu(){
    system("cls");
    int opcao;

    printf("%s Bem Vindo %s\n\n", espacamento, espacamento);
    printf("(1) - Alunos ( EXTRA )\n(2) - Calculadora rapida de media.\n(3) - Sair.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);

    while(opcao < 1 || opcao > 3){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    return opcao;
}

int MenuCalcRapida(){
    system("cls");
    int opcao;

    printf("%s Bem Vindo %s\n", espacamento, espacamento);
    printf("(1) - A1, A2, A3.\n(2) - Disciplina online.\n(3) - AV4.\n(4) - Historico.\n(5) - Sair.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);

    while(opcao < 1 || opcao > 5){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    return opcao;
}

int opcaoMenuAlunos(){
    system("cls");
    int opcao;

    printf("%s Menu Alunos %s\n\n", espacamento, espacamento);
    printf("(1) - Cadastrar Aluno.\n(2) - Lista de Alunos.\n(3) - Deletar Aluno.\n(4) - Sair.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);

    while(opcao < 1 || opcao > 4){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    return opcao;
}


// CALCULOS
Presencial calculaPresencial(){

    system("cls");

    Presencial Mpresencial;
    int opcao;

    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", Mpresencial.Nome);

    Mpresencial.flag = true;

    printf("Disciplina Presencial.\n\n");

    //A1
    printf("O aluno realizou a A1?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1){
        printf("\nDigite a nota da A1: "); scanf("%f", &Mpresencial.av1);

        while(Mpresencial.av1<0 || Mpresencial.av1>10){
        printf("\nNota Invalida. Digite a nota da A1: ");
        scanf("%f", &Mpresencial.av1);
        }
    }else if(opcao == 2) Mpresencial.av1 = 0.00;

    //A2
    printf("\nO aluno realizou a A2?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);

    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }
    if(opcao == 1){

        printf("\nDigite a nota da A2: "); scanf("%f", &Mpresencial.av2);

        while(Mpresencial.av2 < 0 || Mpresencial.av2 > 10){

            printf("\nNota Invalida. Digite a nota da A2: "); scanf("%f", &Mpresencial.av2);

        }
    }else Mpresencial.av2 = 0.00;

    //A3
    printf("\nO aluno realizou a A3?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);

    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }
    if(opcao == 1){

        printf("\nDigite a nota da A3: "); scanf("%f", &Mpresencial.av3);

        while(Mpresencial.av3 < 0 || Mpresencial.av3 > 10){

            printf("\nNota Invalida. Digite a nota da A3: "); scanf("%f", &Mpresencial.av3);

        }
    }else Mpresencial.av3 = 0.00;

    if(Mpresencial.av2 > Mpresencial.av1 && Mpresencial.av3 > Mpresencial.av1){
        Mpresencial.media = (Mpresencial.av2 + Mpresencial.av3) / 2;
    }else if(Mpresencial.av1 > Mpresencial.av2 && Mpresencial.av3 > Mpresencial.av2){
        Mpresencial.media = (Mpresencial.av1 + Mpresencial.av3) / 2;
    }else{
        Mpresencial.media = (Mpresencial.av2 + Mpresencial.av1) / 2;
    }

    if(Mpresencial.media >= 6.00) strcpy(Mpresencial.situacao, "Aprovado");
    else strcpy(Mpresencial.situacao, "Reprovado");

    printf("\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", Mpresencial.av1, Mpresencial.av2, Mpresencial.av3, Mpresencial.media, Mpresencial.situacao);

    return Mpresencial;
};

Online calculaOnilne(){
    system("cls");
    printf("Disciplina Online.\n\n");
    Online online;
    online.flag = true;
    int opcao;
    _Bool fezA2 = true;
    _Bool fezA1 = false;

    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", online.Nome);

    //A1
    printf("O aluno realizou a A1?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1){
        system("cls");
        fezA1 = true;
        printf("Digite a nota da Av1: "); scanf("%f", &online.av1);

        while(online.av1<0 || online.av1>8){
        printf("\nNota Invalida. Digite a nota da av2: "); scanf("%f", &online.av1);
        }

        printf("\nDigite a nota da Av2: "); scanf("%f", &online.av2);

        while(online.av1<0 || online.av1>2){
        printf("\nNota Invalida. Digite a nota da Av2: "); scanf("%f", &online.av2);
        }

        online.A1 = (online.av1 + online.av2) / 2;

    }else if(opcao == 2){
        online.A1 = 0.00;
        online.av1 = 0.00;
        online.av2 = 0.00;
    }

    //A2
    system("cls");
    printf("\nO aluno realizou a A2?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1){
        system("cls");
        printf("Digite a nota da A2: "); scanf("%f", &online.av2);

        while(online.av2 < 0 || online.av2 > 10){
        printf("\nNota Invalida. Digite a nota da A2: "); scanf("%f", &online.av2);
        }
    }else if(opcao == 2) {
        online.av2 = 0.00;
        fezA2 = false;
    }

    //A3
    system("cls");
    printf("\nO aluno realizou a A3?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);

    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1){
        system("cls");
        printf("\nDigite a nota da A3: "); scanf("%f", &online.A3);

        while(online.A3<0 || online.A3>10){
        printf("\nNota Invalida. Digite a nota da A3: "); scanf("%f", &online.A3);
        }
    }else if(opcao == 2) online.A3 = 0.00;


    if(!fezA2){
        online.media = (online.av1 + online.A3) / 2;
    }else if(online.av2 > online.A3){
        online.media = (online.av1 + online.av2) / 2;
    }else{
        online.media = (online.av1 + online.A3) / 2;
    }

    if(!fezA1){

        strcpy(online.situacao, "Reprovado");
        printf("\nAv1: %.2f   Av2: %.2f\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s (NAO REALIZOU A A1!!)\n\n", online.av1, online.av2, online.A1, online.A2, online.A3, online.media, online.situacao);
        return online;
    }

    if(online.av1 < 5.0){
        strcpy(online.situacao, "Reprovado");
        printf("\nAv1: %.2f   Av2: %.2f\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s (NOTA DA A1 MENOR QUE 5.00!!)\n\n", online.av1, online.av2, online.A1, online.A2, online.A3, online.media, online.situacao);
        return online;
    }

    if(online.media >= 6.00) strcpy(online.situacao, "Aprovado");
    else strcpy(online.situacao, "Reprovado");

    printf("\nAv1: %.2f   Av2: %.2f\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", online.av1, online.av2, online.A1, online.A2, online.A3, online.media, online.situacao);

    return online;
}

A4 calculaA4(){
    system("cls");
    A4 av4;
    int opcao;
    av4.flag = true;
    printf("Disciplina A4.\n\n");

    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", av4.Nome);

    printf("O aluno realizou a Av4?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: "); scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        printf("\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1){
        printf("\nDigite a nota da Av4: "); scanf("%f", &av4.Av4);

        while(av4.Av4 <0 || av4.Av4>10){
        printf("\nNota Invalida. Digite a nota da Av4: "); scanf("%f", &av4.Av4);
        }
    }else if(opcao == 2) av4.Av4 = 0.00;

    if(av4.Av4 >= 7.00) strcpy(av4.situacao, "Aprovado");
    else strcpy(av4.situacao, "Reprovado");

    printf("\nAv4: %.2f\nSituacao: %s\n\n", av4.Av4, av4.situacao);

    return av4;
}

void historico(MediasTiradas medias){
    system("cls");
    printf("\n%sHistorico%s\n\n", espacamento, espacamento);

    printf("Materia Presencial.");

    if(medias.presencial.flag == true){
        printf("\nDisciplina: %s", medias.presencial.Nome);
        printf("\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", medias.presencial.av1, medias.presencial.av2, medias.presencial.av3, medias.presencial.media, medias.presencial.situacao);

    }else printf("\nNão foi calculada a media de nenhuma materia presencial apos reinicializacao\n");


    printf("\nMateria Online.");

    if(medias.online.flag == true){
        printf("\nDisciplina: %s", medias.online.Nome);
        printf("\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", medias.online.A1, medias.online.A2, medias.online.A3, medias.online.media, medias.online.situacao);

    }else printf("\nNao foi calculada a media de nenhuma materia online apos reinicializacao\n");

    printf("\nMateria Av4.");

    if(medias.av4.flag == true){
        printf("\nDisciplina: %s", medias.av4.Nome);
        printf("\nAv4: %.2f\nSituacao: %s\n\n", medias.av4.Av4, medias.av4.situacao);

    }else printf("\nNão foi calculada a media de nenhuma materia A4 apos reinicializacao\n\n");

}

void mediasAluno(MediasTiradas medias){
    printf("\n\nMateria Presencial.");

    if(medias.presencial.flag == true){
        printf("\nDisciplina: %s", medias.presencial.Nome);
        printf("\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", medias.presencial.av1, medias.presencial.av2, medias.presencial.av3, medias.presencial.media, medias.presencial.situacao);

    }else printf("\nNão foi calculada a media da materia presencial desse aluno\n");


    printf("\nMateria Online.");

    if(medias.online.flag == true){
        printf("\nDisciplina: %s", medias.online.Nome);
        printf("\nA1: %.2f\nA2: %.2f\nA3: %.2f\nMedia: %.2f\nSituacao: %s\n\n", medias.online.A1, medias.online.A2, medias.online.A3, medias.online.media, medias.online.situacao);

    }else printf("\nNão foi calculada a media da materia online desse aluno\n");

    printf("\nMateria Av4.");

    if(medias.av4.flag == true){
        printf("\nDisciplina: %s", medias.av4.Nome);
        printf("\nAv4: %.2f\nSituacao: %s\n\n", medias.av4.Av4, medias.av4.situacao);

    }else printf("\nNão foi calculada a media da materia Av4 desse aluno\n");

}

// ALUNO
Aluno *cadastraAluno(Aluno *primeiroAluno){
    system("cls");
    Aluno *novoAluno = malloc(sizeof(Aluno));
    int opcao;

    novoAluno->id = idAluno;
    idAluno++;

    novoAluno->medias.presencial.flag = false;
    novoAluno->medias.online.flag = false;
    novoAluno->medias.av4.flag = false;

    printf("%s Cadastro de Aluno %s\n", espacamento, espacamento);

    printf("\nDigite o nome do aluno: ");
    scanf(" %[^\n]s", novoAluno->Nome);

    printf("\n\nDigite a matricula do aluno: ");
    scanf(" %[^\n]s", novoAluno->Matricula);

    system("cls");
    printf("%s Cadastro de Aluno %s\n", espacamento, espacamento);
    printf("\n\nDeseja inserir materia presencial?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);

    while(opcao < 1 || opcao > 2){
        system("cls");
        printf("\n\nDeseja inserir materia presencial?\n(1) - Sim.\n(2) - Nao.\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1) novoAluno->medias.presencial = calculaPresencial();

    system("cls");
    printf("%s Cadastro de Aluno %s\n", espacamento, espacamento);

    printf("\n\nDeseja inserir materia online?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        system("cls");
        printf("\n\nDeseja inserir materia online?\n(1) - Sim.\n(2) - Nao.\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1) novoAluno->medias.online = calculaOnilne();

    system("cls");

    printf("%s Cadastro de Aluno %s\n", espacamento, espacamento);
    printf("\nDeseja inserir materia A4?\n(1) - Sim.\n(2) - Nao.\nDigite a opcao desejada: ");
    scanf("%i", &opcao);
    while(opcao < 1 || opcao > 2){
        system("cls");
        printf("\n\nDeseja inserir materia A4?\n(1) - Sim.\n(2) - Nao.\nOpcao invalida.\nDigite a opcao desejada: ");
        scanf("%i", &opcao);
    }

    if(opcao == 1) novoAluno->medias.av4 = calculaA4();


    novoAluno->next = NULL;
    novoAluno->previous = NULL;

    if(primeiroAluno != NULL){
        primeiroAluno->next = novoAluno;
        novoAluno->previous = primeiroAluno;
    }

    return novoAluno;
}

void listaDeAlunos(Aluno *primeiroAluno){
    system("cls");
    Aluno *temp = primeiroAluno;

    printf("%s Lista de Alunos %s\n", espacamento, espacamento);

    while(temp != NULL){
        printf("Id: %i", temp->id);
        printf("\nNome: %s", temp->Nome);
        printf("\nMatricula: %s", temp->Matricula);
        mediasAluno(temp->medias);
        printf("\n-------------------------\n");
        temp = temp->next;
    }

}

Aluno *deletarAluno(Aluno *primeiroAluno){
    Aluno *temp = primeiroAluno;
    Aluno *aSerDeletado;
    int id;

    printf("%s Deletar Aluno %s\n", espacamento, espacamento);

    listaDeAlunos(primeiroAluno);

    printf("\nDigite o id do cliente que vai ser deletado: ");
    scanf("%i", &id);

    while(id > idAluno){
        printf("\nId invalido\nDigite o id do cliente que vai ser deletado: ");
        scanf("%i", &id);
    }

    while(temp != NULL){
        if(temp->id == id){
            aSerDeletado = temp;
            break;
        }
        temp = temp->next;
    }

    if(primeiroAluno != NULL && aSerDeletado == primeiroAluno){
        if(primeiroAluno->next != NULL){
            aSerDeletado->next->previous = NULL;
            primeiroAluno = aSerDeletado->next;
        }else{
            primeiroAluno = NULL;
        }
    }else{
        if(aSerDeletado != NULL){
            if(aSerDeletado->previous != NULL){
                aSerDeletado->previous->next = aSerDeletado->next;
            }
            if(aSerDeletado->next != NULL){
                aSerDeletado->next->previous = aSerDeletado->previous;
            }
        }
    }
    if(aSerDeletado!=NULL){
        aSerDeletado = NULL;
        free(aSerDeletado);
    }

    return primeiroAluno;

}

//BANCO DE DADOS
void Salvar(Aluno *primeiroAluno){
    FILE *pArquivo;
    pArquivo = fopen("BancoDados.bin", "wb");

    if(pArquivo != NULL){
        Aluno *temp = primeiroAluno;
        Aluno *tempNext = NULL;
        Aluno *tempPre = NULL;

        while(temp != NULL){
            tempNext = temp->next;
            tempPre = temp->previous;

            temp->next = NULL;
            temp->previous = NULL;

            fseek(pArquivo, 0, SEEK_END);
            fwrite(temp, sizeof(Aluno), 1, pArquivo);

            temp->next = tempNext;
            temp->previous = tempPre;

            temp->next = NULL;
            temp->previous = NULL;

            temp = temp->next;
        }
        fclose(pArquivo);
        pArquivo = NULL;
    }

}

Aluno *LerNaMemoria(Aluno *primeiroAluno, FILE *pArquivo){
    size_t bytes;

    if(primeiroAluno == NULL){
        primeiroAluno = malloc(sizeof(Aluno));
        bytes = fread(primeiroAluno, sizeof(Aluno), 1, pArquivo);
        primeiroAluno->next = NULL;
        primeiroAluno->previous = NULL;
    }else{
        Aluno *temp = primeiroAluno;
        Aluno *novoAluno = malloc(sizeof(Aluno));

        while(temp->next != NULL){
            temp = temp->next;
        }
        bytes = fread(novoAluno, sizeof(Aluno), 1, pArquivo);
        temp->next = novoAluno;
        novoAluno->next = NULL;
        novoAluno->previous = temp;
    }
    return primeiroAluno;
}

Aluno *BuscarMemoria(Aluno *primeiroAluno){
    FILE *pArquivo;
    pArquivo = fopen("BancoDados.bin", "rb");

    if(pArquivo != NULL){
        LimpaMemoria(primeiroAluno);
        primeiroAluno = NULL;

        fseek(pArquivo, 0, SEEK_END);
        long TamanhoArquivo = ftell(pArquivo);
        rewind(pArquivo);

        int nEstruturas = (int)(TamanhoArquivo / (sizeof(Aluno)));

        for(int i = 0; i < nEstruturas; ++i){
            fseek(pArquivo, sizeof(Aluno) * i, SEEK_SET);
            primeiroAluno = LerNaMemoria(primeiroAluno, pArquivo);
        }
    }else printf("ERROR");

    return primeiroAluno;
}

//Limpar memoria
void LimpaMemoria(Aluno *primeiroAluno){

    Aluno *remove = primeiroAluno;
	Aluno *segura = NULL;

	while(remove != NULL) {
		segura = remove->next;
		free(remove);
		remove = segura;
	}
}
