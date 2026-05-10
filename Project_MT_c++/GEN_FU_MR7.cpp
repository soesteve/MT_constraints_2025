// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR7 based on the original .dzn files,
// where all values of rr are set to the maximum possible value depending on rc 

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
using namespace std;

const int n_tasks = 30;

struct tFiles {
	string nombre = "";
	string texto = "";
};


void proccess(string file_name, string fu_name);
void proccess_all(string file_name, string fu_name);


int main() {

	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR7/j30/J30";
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

void proccess(string file_name, string fu_name) {

	ifstream in(file_name + ".dzn");
	ofstream out(fu_name + "_fu_rr_max.dzn");

	std::string s = "";

	// Lines by line they are read and written directly because they don't change
	// until a line that begins with rc is found.

	std::string prefix = "rc";

	// I work with regular expressions to remove = ; [ ]
	std::regex word_regex("(\\w+)");

	int num_rc = 0;
	std::getline(in, s);
	while (s.compare(0, prefix.size(), prefix) != 0) {

		// I need to know the number of n_res but it is attached to the final ;

		// iterators 
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

	// Line in s is of the form rc = [...] 

	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	std::smatch match = *i;
	std::string match_str = match.str();

	string* array_din_rc = new string[num_rc];

	// I store the data d = [ ... ]; in a dynamic array array_din_rc
	// and at the same time I am building the sum
	for (int k = 0; k < num_rc; k++) {
		++i;
		match = *i;
		match_str = match.str();
		array_din_rc[k] = match_str;
	}

	// Generate the output	

	out << "rc = [ ";

	for (int k = 0; k < num_rc - 1; k++) {
		out << array_din_rc[k] << ", ";
	}

	// Write the last value of rc without the comma and space at the end and close the bracket
	out << array_din_rc[num_rc - 1] << " ];\n";

	// Next line is n_tasks
	std::getline(in, s);
	out << s + "\n";

	// Next line is d =
	std::getline(in, s);
	out << s + "\n";

	// The following lines are 
	// rr =
	//  |
	//  |
	//  |
	std::getline(in, s);
	std::getline(in, s);
	std::getline(in, s);
	std::getline(in, s);

	out << "rr = [| ";
	for (size_t i = 0; i < n_tasks-1; i++) {
		out << array_din_rc[0] << ", ";
	}
	out << array_din_rc[0] << "\n";

	out << "      | ";
	for (size_t i = 0; i < n_tasks-1; i++) {
		out << array_din_rc[1] << ", ";
	}
	out << array_din_rc[1] << "\n";

	out << "      | ";
	for (size_t i = 0; i < n_tasks-1; i++) {
		out << array_din_rc[2] << ", ";
	}
	out << array_din_rc[2] << "\n";
	

	out << "      | ";
	for (size_t i = 0; i < n_tasks - 1; i++) {
		out << array_din_rc[3] << ", ";
	}
	out << array_din_rc[3] << "|];\n";



	// The rest of the lines are read and written directly because they don't change

	std::getline(in, s);
	while (in) {
		out << s + "\n";
		std::getline(in, s);
	}

	out.close();
	in.close();
}
