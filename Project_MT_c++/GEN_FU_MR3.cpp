
// This program calculates the fu corresponding to MR3
// where the value of a duration is incremented.
// Specifically, it must be greater than the sum of all durations

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

	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR3/j30/J30";
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
	if (!in) {
		cerr << "Unable to open file " << file_name + ".dzn" << endl;
		exit(1);   // call system to stop
	}
	ofstream out(fu_name + "_fu_d.dzn");   // MR3
	if (!out) {
		cerr << "Unable to open file " << fu_name + "_fu_d.dzn" << endl;
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

		// I use iteratos
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

	int var_sum = 1;  // starts at 1 because it is strictly greater than the sum of all durations

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
		var_sum += stoi(match_str);
	}

	// Generate the output

	out << "d = [ ";

	for (int k = 0; k < num_tasks - 1; k++) {
		if (k == 0) {
			out << to_string(var_sum);
		}
		else {
			out << array_din_durations[k];   // add element by element
		}
		out << ", ";
	}

	// Write the last element and close
	out << array_din_durations[num_tasks-1] << " ];\n";

	// The rest of the lines are read and written directly because they don't change

	getline(in, s);
	while (in) {
		out << s + "\n";
		getline(in, s);
	}

	out.close();
	in.close();
}
