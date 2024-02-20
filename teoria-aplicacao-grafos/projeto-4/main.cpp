#include <iostream> // bibliotecas uteis no desenvolvimento
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int schedules[4][5]; // matriz dos horarios
map <int, string> name; // map do nome da materia usando a id como chave
map <int, int> weight; // map do peso da materia usando a id como chave
map <int, int> semester; // map do semestre da materia usando a id como chave
map <int, int> code; // map do codigo da materia usando a id como chave
vector <int> subjects; // vector das materias que serao analisadas no momento

void system_clear() { // limpa a tela
    system("clear");
}

void initializing_matrix() { // inicializa a matriz com zeros
    int i, j;
    for (i = 0; i < 4; i ++) {
        for (j = 0; j < 5; j ++) {
            schedules[i][j] = 0;
        }
    }
}

void creating_maps() { // criando elementos do tipo map para: nome da materia, semestre da materia, codigo da materia e peso da materia utilizando a id como chave
    int i1, i2, i3, i4;
    string s1;
    ifstream file;
    file.open("subjects.txt");
    while (file >> i1 >> s1 >> i2 >> i3 >> i4) {
        name[i1] = s1;
        semester[i1] = i2;
        code[i1] = i3;
        weight[i1] = i4;
    }
    file.close();
}

void printing_matrix(int counter) { // printando as grades horarias
    int i, j;
    cout << endl << "    " << counter << "º Semestre" << endl << endl;
    cout << "    |           | Segunda   | Terça     | Quarta    | Quinta    | Sexta     |" << endl;
    for (i = 0; i < 4; i ++) {
        if (i == 0) {
            cout << "    | 08h - 10h |";
        }
        else if (i == 1) {
            cout << "    | 10h - 12h |";
        }
        else if (i == 2) {
            cout << "    | 14h - 16h |";
        }
        else if (i == 3) {
            cout << "    | 16h - 18h |";
        }
        for (j = 0; j < 5; j ++) {
            if (schedules[i][j] == 0) {
                cout << " xxxxxxxxx |";   
            }
            else {
                cout << " " << code[schedules[i][j]] << "    |";
            }
        }
        cout << endl;
    }
    initializing_matrix();
}

void graph_coloring() { // fazendo a coloracao do grafo sendo as materias os vertices, as arestas o semestre e a cor o horario
    int i, j, counter = 1;
    while (counter <= 9) {
        for (i = 0; i < 36; i ++) {
            if (semester[i + 1] == counter) {
                subjects.push_back(i + 1); // coloca no vector todas as materias do mesmo semestre, analisando cada semestre de uma vez
            }
        }
        while (subjects.size() > 0) { // aloca materias em horarios ate que todas estejam alocadas
            for (i = 0; i < subjects.size(); i ++) {
                if (weight[subjects[i]] == 6) { // verifica primeiro materias de 6 creditos
                    j = 0;
                    while (j < 4) {
                        if (schedules[j][0] == 0) { // aloca materia de seis creditos na segunda quarta sexta
                            schedules[j][0] = subjects[i];
                            schedules[j][2] = subjects[i];
                            schedules[j][4] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else {
                            j ++;
                        }
                    }
                }
            }
            for (i = 0; i < subjects.size(); i ++) {
                if (weight[subjects[i]] == 4) { // verifica materia de quatro creditos
                    j = 0;
                    while (j < 4) {
                        if (schedules[j][1] == 0) { // tenta alocar primeiro na terca e quinta
                            schedules[j][1] = subjects[i];
                            schedules[j][3] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else if (schedules[j][0] == 0) { // caso nao de certo, tenta alocar na segunda e quarta
                            schedules[j][0] = subjects[i];
                            schedules[j][2] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else {
                            j ++;
                        }
                    }
                }
            }
            for (i = 0; i < subjects.size(); i ++) {
                if (weight[subjects[i]] == 2) { // tenta alocar materia de dois creditos em qualquer dia
                    j = 0;
                    while (j < 4) {
                        if (schedules[j][0] == 0) {
                            schedules[j][0] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else if (schedules[j][1] == 0) {
                            schedules[j][1] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else if (schedules[j][2] == 0) {
                            schedules[j][1] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else if (schedules[j][3] == 0) {
                            schedules[j][1] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else if (schedules[j][4] == 0) {
                            schedules[j][1] = subjects[i];
                            subjects.erase(subjects.begin() + i);
                            j = 4;
                        }
                        else {
                            j ++;
                        }
                    }
                }
            }
        }
        printing_matrix(counter);
        counter ++;
    }
}

int main() {
    system_clear();
    cout << endl << "    Grade Horária de cada Semestre de Ciência da Computação:" << endl << endl;
    initializing_matrix();
    creating_maps();
    graph_coloring();
    cout << endl << endl;
    return 0;
}