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

#ifndef _ARVORE_H_
#define _ARVORE_H_

// struct dos ninjas
typedef struct {
    char* nome;
    char* elemento;
    int ninjutsu;
    int genjutsu;
    int taijutsu;
    int defesa;
} Ninja;

// struct dos nos
typedef struct node {
    struct node* left;
    struct node* right;
    Ninja* ninja;
} t_node;

// struct dos elementos
typedef struct element {
    struct element* next;
    struct element* preview;
    Ninja* ninja;
    int posicao;
} t_element;

// struct da lista
typedef struct {
    t_element* first;
    t_element* last;
} t_list;

void clear_screen();

Ninja* ninja_create(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa);

t_node* node_create();

t_node* tree_create(t_node* root, int height);

t_element* element_create(char* nome, char* elemento, int ninjutsu, int genjutsu, int taijutsu, int defesa);

t_list* list_create();

void ninja_free(Ninja* ninja);

void tree_free(t_node* tree);

void element_free(t_element* element);

void list_free(t_list* list);

void tree_print_preorder(t_node* root);

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int atributte);

void result_screen(Ninja* champion_ninja, Ninja* ninja_aux, Ninja* rival_ninja, int* etapa, int atributte, float bonus);

Ninja* battle_screen(t_node* node, Ninja* user_ninja, int* etapa, int* blocked_atributte);

void father_search(t_node* node, Ninja* user_ninja, int* etapa, int* blocked_atributte);

void tree_list(t_node* root, t_list* list, t_element* element_aux, int* found);

void battles(t_list* list, Ninja* user_ninja);

Ninja* choosen_user_ninja(int choice, t_list* list);

t_list* ninjas_list(int* vetor);

void random_numbers(int* vetor);

void choose_ninja();

void menu();

#endif
