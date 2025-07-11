// Este programa calcula los fu correspondiente a MR6
// donde se pone a 0 todo los valores de rc y rr

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
using namespace std;

struct tFiles {
	string nombre = "";
	string texto = "";
};


void procesa(string file_name, string fu_name);
void procesa_todos(string file_name, string fu_name);


int main() {

	string path_file = "data_psplib\\j30\\J30";
	string path_fu = "data_psplib_follow_ups\\MR6\\j30\\J30";
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

void procesa(string file_name, string fu_name) {

	ifstream in(file_name + ".dzn");
	ofstream out(fu_name + "_fu_rc_and_rr_0.dzn");

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

	// Genero la salida

	out << "rc = [ ";

	for (int k = 0; k < num_rc - 1; k++) {
		out << "0, ";
	}

	// Escribo el último elemento y cierro
	out << "0 ];\n";

	// la siguiente línea es n_task
	std::getline(in, s);
	out << s + "\n";

	// la siguiente línea es d =
	std::getline(in, s);
	out << s + "\n";

	// las siguiente líneas son 
	// rr =
	//  |
	//  |
	//  |
	std::getline(in, s);
	std::getline(in, s);
	std::getline(in, s);
	std::getline(in, s);

	out << "rr = [| 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
	out << "      | 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
	out << "      | 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n";
	out << "      | 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 |];\n";


	// El resto de líneas se leen y escriben directamente pq no cambian

	std::getline(in, s);
	while (in) {
		out << s + "\n";
		std::getline(in, s);
	}

	out.close();
	in.close();
}
