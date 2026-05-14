#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include < iomanip >
using namespace std;

const int lines = 77;
const int cols = 11;

struct tMatrix_entrada {
	string data[lines][cols] = { "" };
	int num_lines = 0;
	int num_col = 0;
};

struct tMatrix_resultado {
	string data[6][9] = { "" };
	int num_lines = 0;
	int num_col = 0;
};


unordered_set<string> set_precedences = { 
	"mut-A2DV-1","mut-A2M-1", "mut-A2S-1", 
	"mut-F2E-1",
	"mut-LE2EQ-1",
	"mut-LE2GE-1",
	"mut-LE2GT-1",
	"mut-LE2LT-1",
	"mut-LE2NE-1" };
unordered_set<string> set_non_overlapping = {
	"mut-A2DV-2", "mut-A2DV-3", "mut-A2DV-4", 
	"mut-A2M-2", "mut-A2M-3", "mut-A2M-4",
	"mut-A2S-2", "mut-A2S-3", "mut-A2S-4"
	"mut-D2C-1", 
	"mut-E2F-1", 
	"mut-F2E-2", 
	"mut-GT2EQ-1", "mut-GT2LE-1", "mut-GT2LT-1", "mut-GT2NE-1",
	"mut-LE2EQ-2", "mut-LE2EQ-3",
	"mut-LE2GE-2", "mut-LE2GE-3",
	"mut-LE2GT-2", "mut-LE2GT-3",
	"mut-LE2LT-2", "mut-LE2LT-3",
	"mut-LE2NE-2", "mut-LE2NE-3",
	"mut-LT2EQ-1", "mut-LT2GE-1", "mut-LT2GT-1", "mut-LT2LE-1", "mut-LT2NE-1" };
unordered_set<string> set_cumulative = { "mut-C2D-1", "mut-C2D-2", "mut-CSWAP-1", "mut-F2E-3",
	"mut-GT2EQ-2", "mut-GT2EQ-3", "mut-GT2EQ-4",
	"mut-GT2LE-2", "mut-GT2LE-3", "mut-GT2LE-4",
	"mut-GT2LT-2", "mut-GT2LT-3", "mut-GT2LT-4",
	"mut-GT2NE-2", "mut-GT2NE-3", "mut-GT2NE-4",
	"mut-NE2EQ-1", "mut-NE2GT-1", "mut-NE2LE-1", "mut-NE2LT-1" };
unordered_set<string> set_makespan = { "mut-A2DV-5", "mut-A2M-5", "mut-A2S-5",
	"mut-EQ2GT-1", "mut-EQ2LE-1", "mut-EQ2LT-1", "mut-EQ2NE-1",
	"mut-F2E-4", 
	"mut-LE2EQ-4", "mut-LE2GE-4", "mut-LE2GT-4", "mut-LE2LT-4", "mut-LE2NE-4" };
unordered_set<string> set_parameters = { "mut-S2A-1", "mut-S2DV-1", "mut-S2M-1" };


int main() {

	// leer la matriz 
	ifstream file_in("../V9_mutants_killed.csv");
	if (!file_in.is_open()) {
		cout << "Fichero MT_2025V9_mutants_killed_2025.csv no encontrado" << endl;
		return 1;
	}
	ofstream file_out("../classByConstr.csv");
	if (!file_out.is_open()) {
		cout << "Fichero classByConstr.csv no se ha podido crear" << endl;
		return 1;
	}
	

	tMatrix_entrada me;
	tMatrix_resultado ms;



	// Leer cada línea del archivo
	string linea;
	int i;
	while (getline(file_in, linea)) {
		stringstream ss(linea);
		me.num_col = 0;
		i = 0;

		// Leer cada celda separada por ';'
		string celda;
		while (getline(ss, celda, ';')) {
			if ((i != 1) && (i != 10)) {
				me.data[me.num_lines][me.num_col] = celda;
				i++;
				me.num_col++;
			}
			else {
				i++;
			}
		}
		me.num_lines++;
	}



	ms.data[0][1] = "MR1";
	ms.data[0][2] = "MR2";
	ms.data[0][3] = "MR3";
	ms.data[0][4] = "MR4";
	ms.data[0][5] = "MR5";
	ms.data[0][6] = "MR6";
	ms.data[0][7] = "MR7";
	ms.data[0][8] = "MR8";
	ms.data[1][0] = "precedences";
	ms.data[2][0] = "non_overlapping";
	ms.data[3][0] = "cumulative";
	ms.data[4][0] = "makespan";
	ms.data[5][0] = "parameters";



	for (size_t i = 1; i < lines; i++) {  // salto la cabecera
		for (size_t j = 1; j < cols; j++) {   // salto el nombre del mutante
			if (me.data[i][j] == "1") {

				if (set_precedences.count(me.data[i][0])) {
					ms.data[1][j] = "1";
				}

				if (set_non_overlapping.count(me.data[i][0])) {
					ms.data[2][j] = "1";
				}

				if (set_cumulative.count(me.data[i][0])) {
					ms.data[3][j] = "1";
				}

				if (set_makespan.count(me.data[i][0])) {
					ms.data[4][j] = "1";
				}

				if (set_parameters.count(me.data[i][0])) {
					ms.data[5][j] = "1";
				}
			}
		}
	}



	for (size_t i = 0; i < 6; i++) {  // salto la cabecera
		for (size_t j = 0; j < 9; j++) {   // salto el nombre del mutante
			if (j == 0) {
				file_out << setw(15) << ms.data[i][j] << ";";
			}
			else {
				file_out << setw(5) << ms.data[i][j] << ";";
			}
		}
		file_out << endl;
	}


	system("pause");
	return 0;
}