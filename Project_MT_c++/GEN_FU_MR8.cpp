// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR8 based on the original .dzn files,
// where the first value of rc is set to 0

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
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR8/j30/J30";
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
	if (!in) {
		cerr << "Unable to open file " << file_name + ".dzn" << endl;
		exit(1);   // call system to stop
	}
	ofstream out(fu_name + "_fu_dur_0.dzn");   // MR8
	if (!out) {
		cerr << "Unable to open file " << fu_name + "_fu_dur_0.dzn" << endl;
		exit(1);   // call system to stop
	}

	std::string s = "";

	// The lines are read and written directly because they don't change
	// until a line that begins with d is found.

	std::string prefix = "d";

	// I work with regular expressions to remove = ; [ ]
	std::regex word_regex("(\\w+)");

	int num_tasks = 0;
	std::getline(in, s);
	while (s.compare(0, prefix.size(), prefix) != 0) {

		// I need to know the number of tasks but it's stuck to the final ;

		// iteratos
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
		std::getline(in, s);
	}

	// The line I have in s is of the form d = [...]

	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	std::smatch match = *i;
	std::string match_str = match.str();

	string* array_din_durations = new string[num_tasks];

	// I store the data d = [ ... ]; in a dynamic array array_din_durations
	// and at the same time I calculate the sum
	for (int k = 0; k < num_tasks; k++) {
		++i;
		match = *i;
		match_str = match.str();
		array_din_durations[k] = match_str;
	}

	array_din_durations[0] = "0";  // set the first value of rc to 0

	// Generate the output

	out << "d = [ ";

	for (int k = 0; k < num_tasks - 1; k++) {
		out << array_din_durations[k];   // add element by element
		out << ", ";
	}

	// Write the last element and close
	out << array_din_durations[num_tasks - 1] << " ];\n";

	// The rest of the lines are read and written directly because they don't change

	getline(in, s);
	while (in) {
		out << s + "\n";
		getline(in, s);
	}

	out.close();
	in.close();
}
