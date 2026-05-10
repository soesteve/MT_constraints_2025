
// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR1 based on the original .dzn files,
// and they contain a new set of precedence constraints where all tasks are arranged sequentially, 
// meaning that task 1 precedes task 2, task 2 precedes task 3, and so on, up to task n.
// t1 << t2 << t3 << ... << tn


// file j30_1_1_fu_all_prec.dzn we have the following precedence constraints:
// suc = [ { 2 }, 
//         { 3 }, 
//         { 4 }, 
//        ........
//         { 29 }, 
//         { 30 }, 
//         {  }]; 


#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <filesystem>
using namespace std;

void processes(string file_name, string fu_name);

struct tFiles {
	string nombre = "";
	string texto = "";
};

int main() {

	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR1/j30/J30";


	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string path_file_aux = path_file + "_" + to_string(i) + "_" + to_string(j);
			string path_fu_aux = path_fu + "_" + to_string(i) + "_" + to_string(j);
			processes(path_file_aux, path_fu_aux);
		}
	}
}

void processes(string file_name, string fu_name) {

	string aux = file_name + ".dzn";

	cout << "Intentando abrir: " << aux << endl;

	ifstream in(aux);
	if (!in.is_open()) {
		cerr << "Error al abrir el archivo: " << aux << endl;
		return;
	}
	
	ofstream out(fu_name + "_fu_all_prec.dzn"); 
	if(!out.is_open()) {
		cerr << "Error al crear el archivo: " << fu_name + "_fu_all_prec.dzn" << endl;
		return;
	}

	std::string s = "";


	// Lines are read and written directly because they do not change
	// until a line starting with suc is found

	std::string prefix = "suc";
	int num_tasks = 0;
	getline(in, s);
	while (s.compare(0, prefix.size(), prefix) != 0) {
		// Number of tasks is needed but it is attached to the final ;

		// I use regular expressions to extract = ; []
		std::regex word_regex("(\\w+)");

		// iterators
		std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
		std::smatch match = *i;
		std::string match_str = match.str();

		if (match_str.compare("n_tasks") == 0) {
			++i;
			match = *i;
			match_str = match.str();
			num_tasks = stoi(match_str);  // casting from string to int
		}

		out << s << endl;
		getline(in, s);
	}

	// Now I build the succession of precedences

	out << "suc = [ { 2 }, " << endl;
	for (size_t i = 3; i <= num_tasks; i++){
		out << "        { " << i << " }, " << endl;
	}
	out << "        {  }"  << "]; " << endl;

	in.close();
	out.close();
}
