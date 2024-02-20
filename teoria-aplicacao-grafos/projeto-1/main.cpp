/*
Aluno: Artur Filgueiras Scheiba Zorron
Matricula: 18/0013696
Disciplina: Teoria e Aplicacao de Grafos
Turma: A
Como compilar: g++ main.cpp && ./a.out
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

// bibilotecas uteis pro desenvolvimento

using namespace std;

int matrix[62][62]; // a matriz sera global por ser utilizada em diversas funcoes
int array[62]; // vai salvar quantas adjacencias tem cada vertice

void creatingMatrix() { // criando a matriz de adjacencia
	int i, j;
	for(i = 0; i < 62; i ++) {
        for(j = 0; j < 62; j ++) {
            matrix[i][j] = 0;
        }
    }
}

void updatingMatrix() { // atualizando a matriz com as adjacencias existentes
	int i, vertex1, vertex2;
	ifstream file; // declarando uma variavel que servira de ponteiro do arquivo
	file.open("dolphins.txt"); // abrindo o arquivo
	if (!file) {
		cerr << "Unable to open file dolhpins.txt"; // mensagem de erro caso o arquivo nao abra
		exit(1);
	}
	while (file >> i) {
		vertex1 = i;
		file >> i;
		vertex2 = i;
		matrix[vertex1 - 1][vertex2 - 1] = 1;
		matrix[vertex2 - 1][vertex1 - 1] = 1;
	}
    file.close();
}

void vertexDegree() { // calcula quantos adjacencias tem cada vertice e printa
	int i, j, counter;
	cout << endl << "graus de cada vertice" << endl << endl;
	for (i = 0; i < 62; i ++) {
		counter = 0;
		for (j = 0; j < 62; j ++) {
			if (matrix[i][j] == 1) {
				counter ++;
			}
		}
		array[i] = counter;
		cout << "vertice " << i + 1 << ": " << counter << endl;
	}
}

int linksCalculate(int vertex) { // funcao para achar quantas ligacoes os vertices adjacentes a um vertice principal fazem entre si
	vector <int> vector;
	int count = 0;
	for (int i = 0; i < 62; i ++) {
		if (matrix[vertex][i] == 1) {
			vector.push_back(i);
		}
	}
	for (int i = 0; i < vector.size(); i ++) {
		for (int j = 0; j < 62; j ++) {
			if (matrix[vector[i]][j] == 1) {
				for (int k = 0; k < vector.size(); k ++) {
					if (vector[k] == j && j != vertex) {
						count ++;
					}
				}
			}
		}
	}
	return count;
}

void clusteringCoefficient() { // funcao para achar os coeficientes de aglomeracao
	int i, degree, links;
	double sum = 0, d, cc;
	cout << endl << "coeficiente de aglomeracao dos vertices" << endl << endl;
	for (i = 0; i < 62; i ++) {
		degree = array[i];
		links = linksCalculate(i);
		d = degree * (degree - 1);
		cc = links;
		if (d) {
			cc = cc/d;
		}
		else {
			cc = 0;
		}
		sum += cc;
		cout << "vertice " << i + 1 << ": " << cc << endl;
	}
	cout << endl << "coeficiente de aglomeracao do grafo: " << sum / 62 << endl;
}

int main() {
    creatingMatrix();
	updatingMatrix();
	vertexDegree();
	clusteringCoefficient();
	return 0;
}