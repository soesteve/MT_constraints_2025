// Este programa calcula los fu correspondiente a MR5
// donde se pone a 0 el primer valor de rc

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct tFiles {
	string nombre = "";
	string texto = "";
};


void procesa(string file_name, string fu_name);
void procesa_todos(string file_name, string fu_name);


int main() {


	string path_file = "C:\\Users\\Sonia\\Desktop\\MT_constraints_2025\\benchmarks\\data\\data_psplib\\j30\\J30";
	string path_fu = "C:\\Users\\Sonia\\Desktop\\MT_constraints_2025\\benchmarks\\data\\data_psplib_follow_ups\\MR5\\j30\\J30";
	procesa_todos(path_file, path_fu);

}

void procesa_todos(string path_file, string path_fu) {

	string s = "";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string path_file_aux = path_file + "_" + to_string(i) + "_" + to_string(j);
			string path_fu_aux = path_fu + "_" + to_string(i) + "_" + to_string(j);
			procesa(path_file_aux, path_fu_aux);
		}
	}
}


//----------------

// Función auxiliar para extraer números de una línea con formato tipo "[ 12, 13, 4, 12 ]"
vector<int> extraer_array(const string& linea) {
    vector<int> resultado;
    size_t ini = linea.find('[');
    size_t fin = linea.find(']');
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

// Función para extraer una fila de la matriz rr
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

void procesa(string file_name, string fu_name) {

    ifstream entrada(file_name + ".dzn");
    ofstream salida(fu_name + "_fu_1_rc_mayor_rr.dzn");

    string linea;
    vector<string> lineas_originales;
    vector<string> rr_lines;
    vector<int> primera_fila_rr;
    vector<int> rc;

    // Leer todo el archivo
    while (getline(entrada, linea)) {
        lineas_originales.push_back(linea);
    }

    // Procesar rc
    for (const string& l : lineas_originales) {
        if (l.find("rc") != string::npos) {
            rc = extraer_array(l);
        }
        if (l.find("rr") != string::npos) {  // primera línea
        // Todas las líneas
        //if (l.find("rr") != string::npos || (!rr_lines.empty() && l.find("|") != string::npos)) {
            rr_lines.push_back(l);
        }
    }

    // Obtener la primera fila completa unida
    string primera_fila_completa = rr_lines[0];
    if (primera_fila_completa.find('|') != string::npos && primera_fila_completa.find(']') == string::npos) {
        for (size_t i = 1; i < rr_lines.size(); ++i) {
            if (rr_lines[i].find('|') != string::npos) {
                primera_fila_completa += rr_lines[i];
            }
            else {
                break;
            }
        }
    }

    // Obtener el máximo de la primera fila
    primera_fila_rr = extraer_fila_rr(primera_fila_completa);
    int maximo = *max_element(primera_fila_rr.begin(), primera_fila_rr.end());

    // Sustituir el primer valor de rc
    if (!rc.empty()) {
        rc[0] = maximo;
    }

    // Escribir salida
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


/*
void procesa(string file_name, string fu_name) {

	ifstream in(file_name + ".dzn");
	ofstream out(fu_name + "_fu_1_rc_0.dzn");

	std::string s = "";

	// Las líneas se leen y escriben directamente pq no cambian 
	// hasta encontrar una línea que comienza con rc

	std::string prefix = "rc";

	// Trabajo con expresiones regulares para quitar = ; [ ]
	std::regex word_regex("(\\w+)");

	int num_rc = 0;
	std::getline(in, s);
	while (s.compare(0, prefix.size(), prefix) != 0) {

		// Necesito saber el número de n_res pero está pegado al ; final

		// Uso iteradores 
		std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
		std::smatch match = *i;
		std::string match_str = match.str();

		if (match_str.compare("n_res") == 0) {
			++i;
			match = *i;
			match_str = match.str();
			num_rc = stoi(match_str);  // casting de string a int
		}

		out << s << endl;
		std::getline(in, s);
	}

	// la línea que tengo en s es de la forma rc = [...]

	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	std::smatch match = *i;
	std::string match_str = match.str();

	string* array_din_rc = new string[num_rc];

	// Guardo los datos rc = [ ... ]; en un array dinámico array_din_rc

	for (int k = 0; k < num_rc; k++) {
		++i;
		match = *i;
		match_str = match.str();
		array_din_rc[k] = match_str;
	}

	// LAS SIGUIENTES DOS LÍNEAS LAS LEO  sobre string para escribirlas 
	// más tarde

	string s1, s2;
	std::getline(in, s1);  // n_tasks = 30;
	std::getline(in, s2);  // 	d = [ ... ];


	// Genero la salida

	out << "rc = [ 0, ";   // el primer elemento es 0

	for (int k = 1; k < num_rc - 1; k++) {  // copio los demás eementos
		out << array_din_rc[k];   // añado elemento a elemento
		out << ", ";
	}

	// Escribo el último elemento y cierro
	out << array_din_rc[num_rc - 1] << " ];\n";



	// El resto de líneas se leen y escriben directamente pq no cambian

	std::getline(in, s);
	while (in) {
		out << s + "\n";
		std::getline(in, s);
	}

	out.close();
	in.close();
}
*/

