//Agenda feita por mim em um trabalho de Técnicas de Programação no 2º Período

#include <stdio.h>
#include <string.h>

typedef struct {
    char ddd[4];
    char numero[20];
} Telefone;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char rua[100];
    int numero;
    char complemento[50];
    char bairro[50];
    char cep[15];
    char cidade[50];
    char estado[50];
    char pais[50];
} Endereco;

typedef struct {
    char nome[51];
    char email[251];
    Endereco endereco;
    Telefone telefone;
    Data aniversario;
    char observacoes[251];
} Contato;

// Declaracao dos prototipos
void inserePessoa();
void removePessoa(const char *nome);
void buscaPorNome(const char *nome);
void buscaPorMesAniversario(int mes);
void buscaPorDiaMesAniversario(int dia, int mes);
void imprimeAgendaSimples();
void imprimeAgendaCompleta();
void salvarAgenda();
void carregarAgenda();

// Variaveis globais
Contato agenda[100];
int totalContatos = 0;

// Funcao para salvar a agenda em um arquivo
void salvarAgenda() {
    FILE *arquivo = fopen("agenda.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar a agenda.\n");
        return;
    }

    fwrite(&totalContatos, sizeof(int), 1, arquivo);
    fwrite(agenda, sizeof(Contato), totalContatos, arquivo);
    fclose(arquivo);
    printf("Agenda salva com sucesso!\n");
}

// Funcao para carregar a agenda de um arquivo
void carregarAgenda() {
    FILE *arquivo = fopen("agenda.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de agenda encontrado.\n");
        return;
    }

    fread(&totalContatos, sizeof(int), 1, arquivo);
    fread(agenda, sizeof(Contato), totalContatos, arquivo);
    fclose(arquivo);
    printf("Agenda carregada com sucesso!\n");
}

// Funcao para inserir pessoa na agenda
void inserePessoa() {
    if (totalContatos >= 100) {
        printf("Agenda cheia!\n");
        return;
    }

    Contato novoContato;

    printf("Nome: ");
    fgets(novoContato.nome, sizeof(novoContato.nome), stdin);
    novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';

    printf("Email: ");
    fgets(novoContato.email, sizeof(novoContato.email), stdin);
    novoContato.email[strcspn(novoContato.email, "\n")] = '\0';

    printf("Rua: ");
    fgets(novoContato.endereco.rua, sizeof(novoContato.endereco.rua), stdin);
    novoContato.endereco.rua[strcspn(novoContato.endereco.rua, "\n")] = '\0';

    printf("Numero: ");
    scanf("%d", &novoContato.endereco.numero);
    getchar(); // Limpa o buffer

    printf("Complemento: ");
    fgets(novoContato.endereco.complemento, sizeof(novoContato.endereco.complemento), stdin);
    novoContato.endereco.complemento[strcspn(novoContato.endereco.complemento, "\n")] = '\0';

    printf("Bairro: ");
    fgets(novoContato.endereco.bairro, sizeof(novoContato.endereco.bairro), stdin);
    novoContato.endereco.bairro[strcspn(novoContato.endereco.bairro, "\n")] = '\0';

    printf("CEP: ");
    fgets(novoContato.endereco.cep, sizeof(novoContato.endereco.cep), stdin);
    novoContato.endereco.cep[strcspn(novoContato.endereco.cep, "\n")] = '\0';

    printf("Cidade: ");
    fgets(novoContato.endereco.cidade, sizeof(novoContato.endereco.cidade), stdin);
    novoContato.endereco.cidade[strcspn(novoContato.endereco.cidade, "\n")] = '\0';

    printf("Estado: ");
    fgets(novoContato.endereco.estado, sizeof(novoContato.endereco.estado), stdin);
    novoContato.endereco.estado[strcspn(novoContato.endereco.estado, "\n")] = '\0';

    printf("Pais: ");
    fgets(novoContato.endereco.pais, sizeof(novoContato.endereco.pais), stdin);
    novoContato.endereco.pais[strcspn(novoContato.endereco.pais, "\n")] = '\0';

    printf("DDD: ");
    fgets(novoContato.telefone.ddd, sizeof(novoContato.telefone.ddd), stdin);
    novoContato.telefone.ddd[strcspn(novoContato.telefone.ddd, "\n")] = '\0';

    printf("Numero de telefone: ");
    fgets(novoContato.telefone.numero, sizeof(novoContato.telefone.numero), stdin);
    novoContato.telefone.numero[strcspn(novoContato.telefone.numero, "\n")] = '\0';

    printf("Data de aniversario (dia mes ano): ");
    scanf("%d %d %d", &novoContato.aniversario.dia, &novoContato.aniversario.mes, &novoContato.aniversario.ano);
    getchar(); // Limpa o buffer

    printf("Observacoes: ");
    fgets(novoContato.observacoes, sizeof(novoContato.observacoes), stdin);
    novoContato.observacoes[strcspn(novoContato.observacoes, "\n")] = '\0';

    agenda[totalContatos++] = novoContato;
    printf("Contato inserido com sucesso!\n");
}

// Funcao para remover pessoa da agenda
void removePessoa(const char *nome) {
    for (int i = 0; i < totalContatos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            for (int j = i; j < totalContatos - 1; j++) {
                agenda[j] = agenda[j + 1];
            }
            totalContatos--;
            printf("Contato removido com sucesso!\n");
            return;
        }
    }
    printf("Contato nao encontrado!\n");
}

// Funcao para buscar pessoa por nome
void buscaPorNome(const char *nome) {
    for (int i = 0; i < totalContatos; i++) {
        if (strstr(agenda[i].nome, nome) != NULL) {
            printf("Nome: %s\n", agenda[i].nome);
            printf("Email: %s\n", agenda[i].email);
            printf("Telefone: (%s) %s\n", agenda[i].telefone.ddd, agenda[i].telefone.numero);
            printf("Aniversario: %02d/%02d/%04d\n", agenda[i].aniversario.dia, agenda[i].aniversario.mes, agenda[i].aniversario.ano);
            printf("Observacoes: %s\n", agenda[i].observacoes);
            return;
        }
    }
    printf("Contato nao encontrado!\n");
}

// Funcao para buscar pessoas por mes de aniversario
void buscaPorMesAniversario(int mes) {
    int encontrado = 0;
    for (int i = 0; i < totalContatos; i++) {
        if (agenda[i].aniversario.mes == mes) {
            printf("Nome: %s\n", agenda[i].nome);
            printf("Aniversario: %02d/%02d/%04d\n", agenda[i].aniversario.dia, agenda[i].aniversario.mes, agenda[i].aniversario.ano);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum contato encontrado para o mes %d.\n", mes);
    }
}

// Funcao para buscar pessoas por dia e mes de aniversario
void buscaPorDiaMesAniversario(int dia, int mes) {
    int encontrado = 0;
    for (int i = 0; i < totalContatos; i++) {
        if (agenda[i].aniversario.dia == dia && agenda[i].aniversario.mes == mes) {
            printf("Nome: %s\n", agenda[i].nome);
            printf("Aniversario: %02d/%02d/%04d\n", agenda[i].aniversario.dia, agenda[i].aniversario.mes, agenda[i].aniversario.ano);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum contato encontrado para a data %02d/%02d.\n", dia, mes);
    }
}

// Funcao para imprimir a agenda simples
void imprimeAgendaSimples() {
    for (int i = 0; i < totalContatos; i++) {
        printf("Nome: %s\n", agenda[i].nome);
        printf("Telefone: (%s) %s\n", agenda[i].telefone.ddd, agenda[i].telefone.numero);
    }
}

// Funcao para imprimir a agenda completa
void imprimeAgendaCompleta() {
    for (int i = 0; i < totalContatos; i++) {
        printf("Nome: %s\n", agenda[i].nome);
        printf("Email: %s\n", agenda[i].email);
        printf("Rua: %s\n", agenda[i].endereco.rua);
        printf("Numero: %d\n", agenda[i].endereco.numero);
        printf("Complemento: %s\n", agenda[i].endereco.complemento);
        printf("Bairro: %s\n", agenda[i].endereco.bairro);
        printf("CEP: %s\n", agenda[i].endereco.cep);
        printf("Cidade: %s\n", agenda[i].endereco.cidade);
        printf("Estado: %s\n", agenda[i].endereco.estado);
        printf("Pais: %s\n", agenda[i].endereco.pais);
        printf("Telefone: (%s) %s\n", agenda[i].telefone.ddd, agenda[i].telefone.numero);
        printf("Aniversario: %02d/%02d/%04d\n", agenda[i].aniversario.dia, agenda[i].aniversario.mes, agenda[i].aniversario.ano);
        printf("Observacoes: %s\n", agenda[i].observacoes);
    }
}

// Funcao principal
int main() {
    int opcao, dia, mes;
    char nome[51];

    carregarAgenda();

    while (1) {
        printf("\n---- Menu ----\n");
        printf("1 - Inserir pessoa\n");
        printf("2 - Remover pessoa\n");
        printf("3 - Buscar por nome\n");
        printf("4 - Buscar por mes de aniversario\n");
        printf("5 - Buscar por dia e mes de aniversario\n");
        printf("6 - Imprimir agenda simples\n");
        printf("7 - Imprimir agenda completa\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserePessoa();
                break;
            case 2:
                printf("Digite o nome para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removePessoa(nome);
                break;
            case 3:
                printf("Digite o nome para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscaPorNome(nome);
                break;
            case 4:
                printf("Digite o mes de aniversario para buscar: ");
                scanf("%d", &mes);
                getchar();  // Limpa o buffer
                buscaPorMesAniversario(mes);
                break;
            case 5:
                printf("Digite o dia e o mes de aniversario para buscar: ");
                scanf("%d %d", &dia, &mes);
                getchar();  // Limpa o buffer
                buscaPorDiaMesAniversario(dia, mes);
                break;
            case 6:
                imprimeAgendaSimples();
                break;
            case 7:
                imprimeAgendaCompleta();
                break;
            case 8:
                salvarAgenda();
                return 0;
            default:
                printf("Opcao invalida!\n");
        }
    }
}
