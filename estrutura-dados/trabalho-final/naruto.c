/*
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Estrutura de Dados - 2018/2
Aluno(a): Artur Filgueiras Scheiba Zorron
Matricula: 180013696
Turma: A
Versao do compilador: gcc version 7.3.0 (Ubuntu 7.3.0-27ubuntu1~18.04)
*/

// bibliotecas incluidas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "naruto.h"

// limpa a tela
void clear_screen() {
    system("clear");
}

// aloca um ninja
Ninja* ninja_create(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa) {
    Ninja* ninja = (Ninja*) malloc(sizeof(Ninja));
    ninja -> nome = (char*) malloc(sizeof(strlen(nome) * sizeof(char) + sizeof(char)));
    strcpy(ninja -> nome, nome);
    ninja -> elemento = (char*) malloc(sizeof(strlen(elemento) * sizeof(char) + sizeof(char)));
    strcpy(ninja -> elemento, elemento);
    ninja -> ninjutsu = ninjutsu;
    ninja -> genjutsu = genjutsu;
    ninja -> taijutsu = taijutsu;
    ninja -> defesa = defesa;
    return ninja;
}

// aloca um no da arvore
t_node* node_create() {
    t_node* node = (t_node*) malloc(sizeof(t_node));
    node -> left = NULL;
    node -> right = NULL;
    node -> ninja = NULL;
    return node;
}

// aloca uma arvore
t_node* tree_create(t_node* root, int height) {
    if (height > 0) {
        root -> left = node_create();
        root -> left = tree_create(root -> left, height - 1);
        root -> right = node_create();
        root -> right = tree_create(root -> right, height - 1);
    }
    return root;
}

// aloca um elemento da lista
t_element* element_create(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa) {
    t_element* element = (t_element*) malloc(sizeof(t_element));
    element -> next = NULL;
    element -> preview = NULL;
    element -> ninja = ninja_create(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
    return element;
}

// aloca uma lista
t_list* list_create() {
    t_list* list = (t_list*) malloc(sizeof(t_list));
    list -> first = NULL;
    list -> last = NULL;
    return list;
}

// da free em um ninja alocado
void ninja_free(Ninja* ninja) {
    free(ninja -> nome);
    free(ninja -> elemento);
    free(ninja);
}

// da free em uma arvore alocada
void tree_free(t_node* node) {
    if (node != NULL) {
        tree_free(node -> left);
        tree_free(node -> right);
        free(node);
    }
}

// da free em um elemento alocado
void element_free(t_element* element) {
    ninja_free(element -> ninja);
    free(element);
}

// da free em uma lista alocada
void list_free(t_list* list) {
    t_element* element;
    element = list -> first;
    while (element != NULL) {
        list -> first = list -> first -> next;
        element_free(element);
        element = list -> first;
    }
}

// printa a arvore em pre ordem
void tree_print_preorder(t_node* root) {
    if (root != NULL){
        printf("%s\n", root -> ninja -> nome);
        tree_print_preorder(root -> left);
        tree_print_preorder(root -> right);
    }
}

// promove a luta entre dois ninjas e retorna o ninja vencedor
Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int atributte) {
    switch (atributte) {
        case 1:
        if ((ninja_one -> ninjutsu) >= (ninja_two -> ninjutsu)) {
            return ninja_one;
        }
        else {
            return ninja_two;
        }
        break;
        case 2:
        if ((ninja_one -> genjutsu) >= (ninja_two -> genjutsu)) {
            return ninja_one;
        }
        else {
            return ninja_two;
        }
        break;
        case 3:
        if ((ninja_one -> taijutsu) >= (ninja_two -> taijutsu)) {
            return ninja_one;
        }
        else {
            return ninja_two;
        }
        break;
        case 4:
        if ((ninja_one -> defesa) >= (ninja_two -> defesa)) {
            return ninja_one;
        }
        else {
            return ninja_two;
        }
        break;
    }
}

// tela do resultado
void result_screen(Ninja* champion_ninja, Ninja* ninja_aux, Ninja* rival_ninja, int* etapa, int atributte, float bonus) {
    clear_screen();
    printf("%da Etapa: Resultado\n\n", *etapa);
    if (strcmp(champion_ninja -> nome, ninja_aux -> nome) == 0) {
        printf("Vitoria\n\n");
    }
    else {
        printf("Derrota\n\n");
    }
    switch (atributte) {
        case 1:
        printf("%s (Ninjutsu %d) x %s (Ninjutsu %d)", ninja_aux -> nome, ninja_aux -> ninjutsu, rival_ninja -> nome, rival_ninja -> ninjutsu);
        break;
        case 2:
        printf("%s (Genjutsu %d) x %s (Genjutsu %d)", ninja_aux -> nome, ninja_aux -> genjutsu, rival_ninja -> nome, rival_ninja -> genjutsu);
        break;
        case 3:
        printf("%s (Taijutsu %d) x %s (Taijutsu %d)", ninja_aux -> nome, ninja_aux -> taijutsu, rival_ninja -> nome, rival_ninja -> taijutsu);
        break;
        case 4:
        printf("%s (Defesa %d) x %s (Defesa %d)", ninja_aux -> nome, ninja_aux -> defesa, rival_ninja -> nome, rival_ninja -> defesa);
        break;
    }
    if (bonus != 1) {
        printf(" [x%.1f]", bonus);
    }
    printf("\n");
    printf("%s ganhou a batalha\n\n", champion_ninja -> nome);
    printf("Pressione Enter para prosseguir ");
    getchar();
    getchar();
}

// ----------------------------------------------------------------

// tela das batalhas com o ninja do usuario
Ninja* battle_screen(t_node* node, Ninja* user_ninja, int* etapa, int* blocked_atributte) {
    Ninja* rival_ninja;
    int ninjutsu_aux = user_ninja -> ninjutsu;
    int genjutsu_aux = user_ninja -> genjutsu;
    int taijutsu_aux = user_ninja -> taijutsu;
    int defesa_aux = user_ninja -> defesa;
    Ninja* ninja_aux = ninja_create(user_ninja -> nome, user_ninja -> elemento, user_ninja -> ninjutsu, user_ninja -> genjutsu, user_ninja -> taijutsu, user_ninja -> defesa);
    int atributte;
    float bonus = 1;
    int wrong_number = 0;
    if (node -> left -> ninja == user_ninja) {
        rival_ninja = node -> right -> ninja;
    }
    else {
        rival_ninja = node -> left -> ninja;
    }
    do {
        clear_screen();
        if (wrong_number == 1) {
            printf("Atributo Invalido\n\n");
        }
        printf("%da Etapa\n\n", *etapa);
        printf("Seu personagem: %s - %s\n", user_ninja -> nome, user_ninja -> elemento);
        if (strcmp(user_ninja -> elemento, "Fogo") == 0) {
            if (strcmp(rival_ninja -> elemento, "Vento") == 0) {
                bonus = 1.2;
            }
            else if (strcmp(rival_ninja -> elemento, "Agua") == 0) {
                bonus = 0.8;
            }
        }
        else if (strcmp(user_ninja -> elemento, "Vento") == 0) {
            if (strcmp(rival_ninja -> elemento, "Relampago") == 0) {
                bonus = 1.2;
            }
            else if (strcmp(rival_ninja -> elemento, "Fogo") == 0) {
                bonus = 0.8;
            }
        }
        else if (strcmp(user_ninja -> elemento, "Relampago") == 0) {
            if (strcmp(rival_ninja -> elemento, "Terra") == 0) {
                bonus = 1.2;
            }
            else if (strcmp(rival_ninja -> elemento, "Vento") == 0) {
                bonus = 0.8;
            }
        }
        else if (strcmp(user_ninja -> elemento, "Terra") == 0) {
            if (strcmp(rival_ninja -> elemento, "Agua") == 0) {
                bonus = 1.2;
            }
            else if (strcmp(rival_ninja -> elemento, "Relampago") == 0) {
                bonus = 0.8;
            }
        }
        else if (strcmp(user_ninja -> elemento, "Agua") == 0) {
            if (strcmp(rival_ninja -> elemento, "Fogo") == 0) {
                bonus = 1.2;
            }
            else if (strcmp(rival_ninja -> elemento, "Terra") == 0) {
                bonus = 0.8;
            }
        }
        ninja_aux -> ninjutsu = ninjutsu_aux * bonus;
        ninja_aux -> genjutsu = genjutsu_aux * bonus;
        ninja_aux -> taijutsu = taijutsu_aux * bonus;
        ninja_aux -> defesa = defesa_aux * bonus;
        if (bonus > 1) {
            printf("Supremacia Elemental: %s > %s\n", user_ninja -> elemento, rival_ninja -> elemento);
            printf("Todos os atributos foram multiplicados por x1.2\n\n");
        }
        else if (bonus > 0 && bonus < 1) {
            printf("Inferioridade Elemental: %s < %s\n", user_ninja -> elemento, rival_ninja -> elemento);
            printf("Todos os atributos foram multiplicados por x0.8\n\n");
        }
        switch (*blocked_atributte) {
            case 1:
                printf("X) XX       : XX\n");
                printf("2) Genjutsu : %d\n", ninja_aux -> genjutsu);
                printf("3) Taijutsu : %d\n", ninja_aux -> taijutsu);
                printf("4) Defesa   : %d\n\n", ninja_aux -> defesa);
            break;
            case 2:
                printf("1) Ninjutsu : %d\n", ninja_aux -> ninjutsu);
                printf("X) XX       : XX\n");
                printf("3) Taijutsu : %d\n", ninja_aux -> taijutsu);
                printf("4) Defesa   : %d\n\n", ninja_aux -> defesa);
            break;
            case 3:
                printf("1) Ninjutsu : %d\n", ninja_aux -> ninjutsu);
                printf("2) Genjutsu : %d\n", ninja_aux -> genjutsu);
                printf("X) XX       : XX\n");
                printf("4) Defesa   : %d\n\n", ninja_aux -> defesa);
            break;
            case 4:
                printf("1) Ninjutsu : %d\n", ninja_aux -> ninjutsu);
                printf("2) Genjutsu : %d\n", ninja_aux -> genjutsu);
                printf("3) Taijutsu : %d\n", ninja_aux -> taijutsu);
                printf("X) XX       : XX\n\n");
            break;
            default:
                printf("1) Ninjutsu : %d\n", ninja_aux -> ninjutsu);
                printf("2) Genjutsu : %d\n", ninja_aux -> genjutsu);
                printf("3) Taijutsu : %d\n", ninja_aux -> taijutsu);
                printf("4) Defesa   : %d\n\n", ninja_aux -> defesa);
            break;
        }
        printf("Seu adversario: %s - %s\n\n", rival_ninja -> nome, rival_ninja -> elemento);
        printf("Selecione um atributo: ");
        scanf("%d", &atributte);
        if (atributte == *blocked_atributte) {
            wrong_number = 1;
        }
        else if (atributte < 1) {
            wrong_number = 1;
        }
        else if (atributte > 4) {
            wrong_number = 1;
        }
        else {
            wrong_number = 0;
        }
    } while (wrong_number == 1);
    *blocked_atributte = atributte;
    node -> ninja = fight(ninja_aux, rival_ninja, atributte);
    result_screen(node -> ninja, ninja_aux, rival_ninja, etapa, atributte, bonus);
    return node -> ninja;
}

// ----------------------------------------------------------------

// procura o no-pai de dois nos os quais seus ninjas lutarao
void father_search(t_node* node, Ninja* user_ninja, int* etapa, int* blocked_atributte) {
    if (node != NULL) {
        if (node -> left != NULL) {
            if (node -> right != NULL) {
                if (node -> ninja == NULL) {
                    father_search(node -> left, user_ninja, etapa, blocked_atributte);
                    father_search(node -> right, user_ninja, etapa, blocked_atributte);
                    if (strcmp(node -> left -> ninja -> nome, user_ninja -> nome) == 0) {
                        node -> left -> ninja = user_ninja;
                        *etapa += 1;
                        node -> ninja = battle_screen(node, user_ninja, etapa, blocked_atributte);
                    }
                    else if (strcmp(node -> right -> ninja -> nome, user_ninja -> nome) == 0) {
                        node -> right -> ninja = user_ninja;
                        *etapa += 1;
                        node -> ninja = battle_screen(node, user_ninja, etapa, blocked_atributte);
                    }
                    else {
                        int random_atributte;
                        random_atributte = rand() % 4 + 1;
                        node -> ninja = fight(node -> left -> ninja, node -> right -> ninja, random_atributte);
                    }
                }
            }
        }
    }
}

// os nos-folhas da arvore recebem os ninjas da lista duplamente encadeada
void tree_list(t_node* root, t_list* list, t_element* element, int* found) {
    if (root != NULL) {
        if (*found == 0) {
            tree_list(root -> left, list, element, found);
        }
        if (*found == 0) {
            tree_list(root -> right, list, element, found);
        }
        if (root -> left == NULL) {
            if (root -> right == NULL) {
                if (root -> ninja == NULL) {
                    root -> ninja = element -> ninja;
                    *found = 1;
                }
            }
        }
    }
}

// logica das batalhas
void battles(t_list* list, Ninja* user_ninja) {
    t_element* element = list -> first;
    int found = 0;
    int etapa = 0;
    int i;
    int blocked_atributte = 0;
    t_node* root = node_create();
    root = tree_create(root, 4);
    for (i = 0; i < 16; i ++) {
        tree_list(root, list, element, &found);
        element = element -> next;
        found = 0;
    }
    father_search(root, user_ninja, &etapa, &blocked_atributte);
    printf("\nPrintando em Pre-Ordem\n\n");
    tree_print_preorder(root);
    printf("\n");
    printf("Pressione Enter para voltar ao menu: ");
    getchar();
    list_free(list);
    tree_free(root);
}

// encontra o ninja escolhido pelo usuario e retorna ele
Ninja* choosen_user_ninja(int choice, t_list* list) {
    t_element* element = list -> first;
    while (element -> posicao != choice) {
        element = element -> next;
    }
    return element -> ninja;
}

// cria uma lista duplamente encadeada com os ninjas escolhidos aleatoriamente do arquivo txt
t_list* ninjas_list(int* vetor) {
    char nome[20];
    char elemento[20];
    int ninjutsu;
    int genjutsu;
    int taijutsu;
    int defesa;
    t_list* list = list_create();
    int i;
    int j;
    int k;
    int l;
    FILE* file_ninjas;
    file_ninjas = fopen("ninjas.txt", "r");
    k = 0;
    for (i = 0; i < 16; i ++) {
        for (j = 0; j < vetor[k]; j ++) {
            l = 0;
            fscanf(file_ninjas, "%[^',']s", nome);
            fgetc(file_ninjas);
            fscanf(file_ninjas, "%[^',']s", elemento);
            while (elemento[l] != '\0') {
                elemento[l] = elemento[l + 1];
                l += 1;
            }
            fgetc(file_ninjas);
            fscanf(file_ninjas, "%d, %d, %d, %d", &ninjutsu, &genjutsu, &taijutsu, &defesa);
            fgetc(file_ninjas);
        }
        if (i == 0) {
            list -> first = element_create(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
            list -> last = list -> first;
        }
        else {
            list -> last -> next = element_create(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
            list -> last -> next -> preview = list -> last;
            list -> last = list -> last -> next;
        }
        list -> last -> posicao = i + 1;
        rewind(file_ninjas);
        k += 1;
    }
    fclose(file_ninjas);
    return list;
}

// coloca dentro do vetor valores aleatorios de 1 a 32 nao repetidos para depois pegarem os ninjas do arquivo txt nessas linhas
void random_numbers(int* vetor) {
    int random;
    int i;
    int j;
    int contador;
    i = 0;
    struct timespec seed;
    clock_gettime(CLOCK_REALTIME, &seed);
    srand(seed.tv_nsec);
    do {
        contador = 0;
        random = (rand() % 32) + 1;
        for (j = 0; j < 16; j ++) {
            if (vetor[j] == random) {
                contador ++;
            }
        }
        if (contador == 0) {
            vetor[i] = random;
            i ++;
        }
    } while (i < 16);
}

// tela para o usuario escolher o seu ninja
void choose_ninja() {
    int choice;
    int i;
    int back = 0;
    int vetor[16];
    int random_atributte;
    int wrong_number = 0;
    t_list* list;
    t_element* element;
    Ninja* user_ninja;
    random_numbers(vetor);
    list = ninjas_list(vetor);
    while (back == 0) {
        clear_screen();
        if (wrong_number == 1) {
            printf("Personagem Invalido\n\n");
        }
        printf("Escolha seu personagem\n\n");
        element = list -> first;
        for (i = 0; i < 16; i ++) {
            if (wrong_number == 0) {
                random_atributte = rand() % 4 + 1;
            }
            switch (random_atributte) {
                case 1:
                    printf("Personagem %d:\nNinjutsu: %d Genjutsu: ?? Taijutsu: ?? Defesa: ??\n\n", element -> posicao, element -> ninja -> ninjutsu);
                break;
                case 2:
                    printf("Personagem %d:\nNinjutsu: ?? Genjutsu: %d Taijutsu: ?? Defesa: ??\n\n", element -> posicao, element -> ninja -> genjutsu);
                break;
                case 3:
                    printf("Personagem %d:\nNinjutsu: ?? Genjutsu: ?? Taijutsu: %d Defesa: ??\n\n", element -> posicao, element -> ninja -> taijutsu);
                break;
                case 4:
                    printf("Personagem %d:\nNinjutsu: ?? Genjutsu: ?? Taijutsu: ?? Defesa: %d\n\n", element -> posicao, element -> ninja -> defesa);
                break;
            }
            element = element -> next;
        }
        printf("Pressione 0 para voltar ao Menu\n\n");
        printf("Qual personagem voce escolhe? ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                user_ninja = choosen_user_ninja(choice, list);
                battles(list, user_ninja);
                back = 1;
            break;
            case 0:
                back = 1;
            break;
            default:
                wrong_number = 1;
            break;
        }
    }
}

// tela de menu
void menu() {
    int choice;
    int exit = 0;
    while (exit == 0) {
        clear_screen();
        printf("Exame Chunin\n\n");
        printf("[1] Iniciar Exame\n");
        printf("[2] Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                choose_ninja();
            break;
            case 2:
                exit = 1;
            break;
        }
    }
}
