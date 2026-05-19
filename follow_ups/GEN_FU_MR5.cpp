// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR5 based on the original .dzn files,
// and they contain a new set of resource capacities where 
// the new resource capacities are the maximum requirement of any task for that resource.


#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct tFiles {
	string nombre = "";
	string texto = "";
};


void proccess(string file_name, string fu_name);
void proccess_all(string file_name, string fu_name);


int main() {

	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR5/j30/J30";
	proccess_all(path_file, path_fu);

}

void proccess_all(string path_file, string path_fu) {

	string s = "";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string path_file_aux = path_file + "_" + to_string(i) + "_" + to_string(j);
			string path_fu_aux = path_fu + "_" + to_string(i) + "_" + to_string(j);
			proccess(path_file_aux, path_fu_aux);
		}
	}
}



// Auxiliary function to extract numbers from a line with format like "[ 12, 13, 4, 12 ]"
vector<int> extraer_array(const string& linea) {
	vector<int> resultado;
	size_t ini = linea.find('[');
	size_t fin = linea.find(']');
	// string::npos is a special constant that represents an invalid position.
	if (ini != string::npos && fin != string::npos) {
		string contenido = linea.substr(ini + 1, fin - ini - 1);
		stringstream ss(contenido);
		string numero;
		while (getline(ss, numero, ',')) {
			int valor = stoi(numero);
			resultado.push_back(valor);
		}
	}
	return resultado;
}

// Function to extract a row from the rr matrix
vector<int> extraer_fila_rr(const string& linea) {
	vector<int> fila;
	size_t ini = linea.find('|');
	if (ini != string::npos) {
		string contenido = linea.substr(ini + 1);
		stringstream ss(contenido);
		string numero;
		while (getline(ss, numero, ',')) {
			int valor = stoi(numero);
			fila.push_back(valor);
		}
	}
	return fila;
}

void proccess(string file_name, string fu_name) {

	ifstream entrada(file_name + ".dzn");
	ofstream salida(fu_name + "_fu_rc_mayor_rr.dzn");

	string linea;
	vector<string> lineas_originales;
	vector<string> rr_lines;
	vector<int> fila_rr;
	vector<int> rc;

	// Read the entire file
	while (getline(entrada, linea)) {
		lineas_originales.push_back(linea);
	}

	// Proccess rc
	for (const string& l : lineas_originales) {
		if (l.find("rc") != string::npos) {
			rc = extraer_array(l);
		}
		if (l.find("rr") != string::npos || (!rr_lines.empty() && l.find("|") != string::npos)) {
			rr_lines.push_back(l);
		}
	}

	// Get the maximum of the first row
	fila_rr = extraer_fila_rr(rr_lines[0]);
	int maxi0 = *max_element(fila_rr.begin(), fila_rr.end());
	if (maxi0 <= rc[0]) {
		rc[0] = maxi0;
	}
	else { cout << "Problema porque rc[0] " << rc[0] << " > " << maxi0 << " maximo1 "; }

	fila_rr = extraer_fila_rr(rr_lines[1]);
	int maxi1 = *max_element(fila_rr.begin(), fila_rr.end());
	if (maxi1 <= rc[1]) {
		rc[1] = maxi1;
	}
	else { cout << "Problema porque rc[1] " << rc[1] << " > " << maxi1 << " maximo2 "; }

	fila_rr = extraer_fila_rr(rr_lines[2]);
	int maxi2 = *max_element(fila_rr.begin(), fila_rr.end());
	if (maxi2 <= rc[2]) {
		rc[2] = maxi2;
	}
	else { cout << "Problema porque rc[2] " << rc[2] << " > " << maxi2 << " maximo3 "; }

	fila_rr = extraer_fila_rr(rr_lines[3]);
	int maxi3 = *max_element(fila_rr.begin(), fila_rr.end());
	if (maxi3 <= rc[3]) {
		rc[3] = maxi3;
	}
	else { cout << "Problema porque rc[3] " << rc[3] << " > " << maxi3 << " maximo4 "; }


	// Write the output
	for (const string& l : lineas_originales) {
		if (l.find("rc") != string::npos) {
			salida << "rc = [ ";
			for (size_t i = 0; i < rc.size(); ++i) {
				salida << rc[i];
				if (i < rc.size() - 1) salida << ", ";
			}
			salida << " ];" << endl;
		}
		else {
			salida << l << endl;
		}
	}

	entrada.close();
	salida.close();

}

