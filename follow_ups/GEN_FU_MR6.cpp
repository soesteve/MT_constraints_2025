// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR6 based on the original .dzn files,
// and they contain a new set where values of rc and rr are set to 0.

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


void proccess(string file_name, string fu_name);
void proccess_all(string file_name, string fu_name);


int main() {

	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR6/j30/J30";
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
	ofstream out(fu_name + "_fu_rc_and_rr_0.dzn");

	std::string s = "";

	// Lines are read and written directly because they don't change
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
			num_rc = stoi(match_str);  // casting from string to int
		}

		out << s << endl;
		std::getline(in, s);
	}

	// Line in s is of the form rc = [...]

	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	std::smatch match = *i;
	std::string match_str = match.str();

	// Output

	out << "rc = [ ";

	for (int k = 0; k < num_rc - 1; k++) {
		out << "0, ";
	}

	// Write the last element and close
	out << "0 ];\n";

	// The next line is n_task
	std::getline(in, s);
	out << s + "\n";

	// The next line is d =
	std::getline(in, s);
	out << s + "\n";

	// The next lines are 
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


	// The rest of the lines are read and written directly because they don't change

	std::getline(in, s);
	while (in) {
		out << s + "\n";
		std::getline(in, s);
	}

	out.close();
	in.close();
}
