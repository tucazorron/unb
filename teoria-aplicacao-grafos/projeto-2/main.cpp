/*
Alunos: Artur Filgueiras Scheiba Zorron & Guilherme Oliveira Loiola
Matricula: 18/0013696 & 17/0050335
Disciplina: Teoria e Aplicacao de Grafos
Turma: A
Como compilar: g++ main.cpp && ./a.out
*/

#include <iostream> // bibliotecas uteis no desenvolvimento
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int matrix[31][31]; // matriz de adajacencia
vector <int> topological_order; // vector que ira salvar a ordem topologica do grafo
vector <int> prerequisites(31, 0); // vector que salva os pre requisitos de uma materia
map <int, string> name; // map do nome da materia usando o numero identificador como chave
map <int, int> code; // map do codigo da materia usando o numero identificador como chave
map <int, int> weight; // map do peso da materia usando o numero identificador como chave

void system_clear() { // limpa a tela quando o programa comeca
    system("clear");
}

void creating_matrix() { // inicializando a matriz com "0"
    int i, j;
    for (i = 0; i < 31; i ++) {
        for (j = 0; j < 31; j ++) {
            matrix[i][j] = 0;
        }
    }
}

void creating_maps() { // criando elementos do tipo map para: nome da materia, codigo da materia e peso da materia pela chave unica da materia que foi um numero dado por mim
    int i1, i2, i3;
    string s1;
    ifstream file;
    file.open("materias-cic.txt");
    while (file >> i1 >> s1 >> i2 >> i3) {
        name[i1] = s1;
        code[i1] = i2;
        weight[i1] = i3;
    }
}

void updating_matrix() { // colocando "1" na matriz quando a materia da linha tranca a materia da coluna
    int i, j, vertex1, vertex2;
    ifstream file;
    file.open("pre-requisitos.txt");
    while (file >> i) {
		vertex1 = i;
		file >> i;
		vertex2 = i;
		matrix[vertex1 - 1][vertex2 - 1] = 1;
    }
    file.close();
}

void topological_sort() { // ordenando as materias de maneira topologica
    int i, j, l, counter, flag = 1, matrix_aux[31][31];
    for (i = 0; i < 31; i ++) {
        for (j = 0; j < 31; j ++) {
            matrix_aux[i][j] = matrix[i][j]; // copiando a matriz para uma matriz auxiliar a fim de nao modificar a original
        }
    }
    while (topological_order.size() < 31) {
        for (j = 0; j < 31; j ++) {
            counter = 0;
            for (i = 0; i < 31; i ++) {
                if (matrix_aux[i][j] == 1) {
                    counter ++;
                }
            }
            if (counter == 0) {
                topological_order.push_back(j + 1);
                for (l = 0; l < 31; l ++) {
                    matrix_aux[j][l] = 0;
                }
            }
        }
    }
}

int find_prerequisites() { // encontrando todos os pre requisitos das materias
    int i, j, flag = 0;
    for (i = 0; i < 31; i ++) {
        if (prerequisites[i] == 1) {
            for (j = 0; j < 31; j ++) {
                if (matrix[j][i] == 1 && prerequisites[j] == 0) {
                    prerequisites[j] = 1;
                    flag = 1;
                }
            }
        }
    }
    return flag;
}

void printing() { // funcao onde ocorrem todos os prints do programa
    int i, j, flag, sum_weights, sum_max1 = 0, sum_max2 = 0, name_max1, name_max2; // variaveis da funcao
    cout << "----------------------------------------------------------------" << endl << endl << "Lista de Matérias:" << endl << endl;
    for (i = 1; i <= 31; i ++) {
        cout << "Matéria " << i << endl << "Nome: " << name[i] << endl << "Código: " << code[i] << endl << "Peso: " << weight[i] << endl << endl; // printando materia, codigo, peso e chave identificadora
    }
    cout << "----------------------------------------------------------------" << endl << endl << "Ordenação Topológica pelos códigos das matérias:" << endl << endl;
    for (i = 0; i < 31; i ++) {
        cout << code[topological_order[i]] << " --> "; // printando a ordenacao topologicas das materias pelo codigo
    }
    cout << endl << endl;
    cout << "----------------------------------------------------------------" << endl << endl << "Matérias, seus respectivos pesos e seus pré-requisitos:" << endl << endl;
    for (i = 0; i < 31; i ++) {
        prerequisites.assign(31, 0);
        sum_weights = 0;
        cout << "Nome: " << name[i + 1] << " [" << weight[i + 1] << "]" << endl << "Pré-requisitos: ";
        for (j = 0; j < 31; j ++) {
            if (matrix[j][i] == 1 && prerequisites[j] == 0) {
                prerequisites[j] = 1; // inicializando o vector de pre requisitos com os pre requisitos imediatos
            }
        }
        do {
            flag = find_prerequisites();
        } while (flag);
        for (j = 0; j < 31; j ++) {
            if (prerequisites[j] == 1) {
                sum_weights += weight[j + 1]; // somando os pesos de todos os pre requisitos
                cout << name[j + 1] << " [" << weight[j + 1] << "], "; // printando os pre requisitos
            }
        }
        cout << endl << "Peso total: " << sum_weights << endl << endl; // printando o peso total
        if (sum_weights > sum_max2) { // trecho de codigo que rankeia os dois maiores caminhos
            if (sum_weights > sum_max1) {
                sum_max2 = sum_max1;
                name_max2 = name_max1;
                sum_max1 = sum_weights;
                name_max1 = i + 1;
            }
            else {
                sum_max2 = sum_weights;
                name_max2 = i + 1;
            }
        }
    }
    cout << "----------------------------------------------------------------" << endl << endl << "Maior e segundo maior caminho de matérias (com pesos):" << endl << endl;
    cout << "Matéria com maior caminho: " << name[name_max1] << " [" << sum_max1 << "]" << endl;
    cout << "Matéria com segundo maior caminho: " << name[name_max2] << " [" << sum_max2 << "]" << endl << endl;

}

int main() {
    system_clear();
    creating_matrix();
    creating_maps();
    updating_matrix();
    topological_sort();
    printing();
    return 0;
}