#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void inputUser();
void render();
void locar();
int excluir();
int alterar();
void listar();
int busc();

typedef struct
{
	char nome[50];
	char sobre[50];
	int idade;
	char sex;
	char cpf[20];
	char rg[20];
	char end[100];
	char tel[15];
	char email[100];
} dados;

dados usuarios[1001];
int totp = 0; //identificar o total de usuarios lidos e renderizados até o momento da execução

int main(void) {
	setlocale(LC_ALL, "Portuguese");

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("\tCADASTROS DE USUÁRIOS\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

	char op;
	FILE *file;
	file = fopen("cadastros.txt", "a");

	//Verificando se o arquivo foi aberto corretamente, caso contrário finaliza o programa
	if (file == NULL){
		printf("Erro! Na criação do arquivo.\n");
		return 0;
	}

	fclose(file);

	locar(); //caso tenha cadastros no arquivo, a função coloca dentro do vetor

	while (free) {
		printf("-[ N ] Novo cadastro\n-[ E ] Excluir cadastro\n-[ A ] Alterar cadastro\n-[ P ] Procurar usuário\n-[ L ] Listar usuários\n-[ S ] Sair do programa\n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		printf("Digite a opcão: ");
		scanf("\n%c", &op);
		
		switch (op) {
			case 'N':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				inputUser(totp); //Função para ler o usuário
				totp++;
				render(); //Renderizar os elementos no arquivo
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			break;

			case 'E':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				int aux = excluir(); //Função que retorna 1 se achou e excluiu o usuário, se não retorna 0
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				if (aux == 1) {
					printf("Usuário excluído com sucesso!.\n");
				} else {
					printf("Erro! Usuário não encontrado.\n");
				}
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			break;

			case 'A':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				aux = alterar(); //Função de buscar pelo nome e alterar as informações
				if (aux == 1) {
					render();
					printf("Usuário editado com sucesso!.\n");
				} else {
					printf("Erro! Usuário não encontrado.\n");
				}
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			break;
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				busc(); //Função de buscar usuário pelo nome
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			case 'P':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				busc();
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			break;

			case 'L':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				listar(); //Listar usuário
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			break;

			case 'S':
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				printf("Programa Finalizado!.\n"); 						//Sair do Programa
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				fclose(file);
				return 0;
			break;

			default:
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				printf("Erro! Finalizando programa.\n");				//Sair do Programa
				printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
				fclose(file);
				return 0;
			break;
		}
	}
	return 0;
}

void inputUser(int pos) {	
	printf("Nome: ");
	scanf("\n%s", usuarios[pos].nome);
	
	printf("Sobrenome: ");
	scanf("\n%s", usuarios[pos].sobre);

	printf("Idade: ");
	scanf("\n%d", &usuarios[pos].idade);

	printf("Sexo [M/F]: ");
	scanf("\n%c", &usuarios[pos].sex);

	printf("CPF: ");
	scanf("\n%s", usuarios[pos].cpf);

	printf("RG: ");
	scanf("%s", usuarios[pos].rg);

	printf("Endereço: ");
	scanf("%s", usuarios[pos].end);
	
	printf("Telefone: ");
	scanf("\n%s", usuarios[pos].tel);	

	printf("Email: ");
	scanf("%s", usuarios[pos].email);

}

void render(void) {
	FILE *file;
	file = fopen("cadastros.txt", "w");

	for (int i = 0; i < totp; i++) {
		fprintf(file, "%s\n", usuarios[i].nome);
		fprintf(file, "%s\n", usuarios[i].sobre);
		fprintf(file, "%d\n", usuarios[i].idade);
		fprintf(file, "%c\n", usuarios[i].sex);
		fprintf(file, "%s\n", usuarios[i].cpf);
		fprintf(file, "%s\n", usuarios[i].rg);
		fprintf(file, "%s\n", usuarios[i].end);
		fprintf(file, "%s\n", usuarios[i].tel);
		fprintf(file, "%s\n", usuarios[i].email);
	}
	fclose(file);	
}

void locar(void) {
	FILE *file;
	file = fopen("cadastros.txt", "r");

	while (free) {
		fscanf(file, "%s\n%s\n%d\n%c\n%s\n%s\n%s\n%s\n%s", usuarios[totp].nome, usuarios[totp].sobre,&usuarios[totp].idade, &usuarios[totp].sex, usuarios[totp].cpf, usuarios[totp].rg, usuarios[totp].end, usuarios[totp].tel, usuarios[totp].email);
		if (feof(file)) {
			break;
		}
		totp++;
	}
	fclose(file);
}

int excluir(void) {
	int aux = 0;
	char del[50];

	printf("Nome do usuário a ser excluído: ");
	scanf("%s", del);	

	for (int i = 0; i <= totp; i++) {
		if (!strcmp(del, usuarios[i].nome)) {
			strcpy(usuarios[i].nome, usuarios[i+1].nome);
			strcpy(usuarios[i].sobre, usuarios[i+1].sobre);
			usuarios[i].idade = usuarios[i+1].idade;
			usuarios[i].sex = usuarios[i+1].sex;
			strcpy(usuarios[i].cpf, usuarios[i+1].cpf);
			strcpy(usuarios[i].rg, usuarios[i+1].rg);
			strcpy(usuarios[i].end, usuarios[i+1].end);
			strcpy(usuarios[i].tel, usuarios[i+1].tel);
			strcpy(usuarios[i].email, usuarios[i+1].email);

			totp--;
			render();
			aux = 1;
		}
	}
	return aux;
}

int alterar(void) {
	char alt[50];

	while (getchar() != '\n'); //Eliminar os "lixos" deixados pelos scanfs.
	printf("Nome do usário a ser editado: ");
	scanf("%s", alt);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

	for (int i = 0; i <= totp; i++) {
		if (!strcmp(alt, usuarios[i].nome)) {
			printf("Informações atuais do usuário:\n");
			printf("Nome: %s\n", usuarios[i].nome);
			printf("Sobrenome: %s\n", usuarios[i].sobre);
			printf("Idade: %d\n", usuarios[i].idade);
			printf("Sexo: %c\n", usuarios[i].sex);
			printf("Cpf: %s\n", usuarios[i].cpf);
			printf("Rg: %s\n", usuarios[i].rg);
			printf("Endereço: %s\n", usuarios[i].end);
			printf("Telefone: %s\n", usuarios[i].tel);
			printf("E-mail: %s\n", usuarios[i].email);
			printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			printf("Informe as novas alterações:\n");
			inputUser(i);
			return 1;
		}
	}
	return 0;
}

void listar() {

	for (int i = 0; i < totp; i++) {
		printf("-=-=-=-=-=-=-=- Usuário %d -=-=-=-=-=-=-=-\n", i+1);
		printf("Nome: %s\n", usuarios[i].nome);
		printf("Sobrenome: %s\n", usuarios[i].sobre);
		printf("Idade: %d\n", usuarios[i].idade);
		printf("Sexo: %c\n", usuarios[i].sex);
		printf("Cpf: %s\n", usuarios[i].cpf);
		printf("Rg: %s\n", usuarios[i].rg);
		printf("Endereço: %s\n", usuarios[i].end);
		printf("Telefone: %s\n", usuarios[i].tel);
		printf("E-mail: %s\n", usuarios[i].email);
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	}
}

int busc() {
	char nome[50];

	printf("Qual nome deseja procurar: ");
	scanf("%s", nome);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	
	for (int i = 0; i < totp; i++) {
		if (!strcmp(nome, usuarios[i].nome)) {
			printf("Informações do usuário: \n");
			printf("Nome: %s\n", usuarios[i].nome);
			printf("Sobrenome: %s\n", usuarios[i].sobre);
			printf("Idade: %d\n", usuarios[i].idade);
			printf("Sexo: %c\n", usuarios[i].sex);
			printf("Cpf: %s\n", usuarios[i].cpf);
			printf("Rg: %s\n", usuarios[i].rg);
			printf("Endereço: %s\n", usuarios[i].end);
			printf("Telefone: %s\n", usuarios[i].tel);
			printf("E-mail: %s\n", usuarios[i].email);
	}
}}
