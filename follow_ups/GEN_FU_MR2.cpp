

// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the follow-ups corresponding to MR2 and,
// reads the original .dzn files, and creates new .dzn files 
// with modified precedence constraints (fu) to create a cycle 
// between pairs of tasks (t1 << t2 and t2 << t1) 

// t1 << t2 and t2 << t1, ... t{n-1} << tn and tn << t{n-1}
 
// In the file j30_1_1_fu_all_prec.dzn  we have the following precedence constraints:
// suc = [ { 2 }, 
        // { 1 }, 
        // { 4 }, 
        // { 3 }, 
        // { 6 }, 
        // { 5 }, 
        // .......
        // { 30 }, 
        // { 29 }]; 


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

void process(string file_name, string fu_name);
void process_all(string file_name, string fu_name);


int main() {
	
	string path_file = "../benchmarks/data/data_psplib/j30/J30";
	string path_fu = "../benchmarks/data/data_psplib_follow_ups/MR2/j30/J30";

	process_all(path_file, path_fu);
	return 0;
}

void process_all(string path_file, string path_fu) {
	string s = "";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string path_file_aux = path_file + "_" + to_string(i) + "_" + to_string(j);
			string path_fu_aux = path_fu + "_" + to_string(i) + "_" + to_string(j);
			process(path_file_aux, path_fu_aux);
		}
	}
}

void process(string file_name, string fu_name) {
	string aux = file_name + ".dzn";
	ifstream in(aux);
	ofstream out(fu_name + "_fu_cycle.dzn");   //  MR2

	std::string s = "";


	// Lines are read and written directly because they do not change
	// until a line starting with suc is found

	std::string prefix = "suc";
	int num_tasks = 0;
	getline(in, s);
	while (s.compare(0, prefix.size(), prefix) != 0) {

		// Number of tasks is needed but it is attached to the final ;

		// Trabajo con expresiones regulares para quitar = ; [ ]
		// I use regular expressions to extract = ; []
		// https://en.cppreference.com/w/cpp/regex
		std::regex word_regex("(\\w+)");

		// I use iterators
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

	/* If I build a single cycle of t1 << t2 and t2 << t1 it takes a long time
	out << "suc = [ { 2 }, " << endl;
	out << "        { 1 }, " << endl;
	for (size_t i = 4; i <= num_tasks; i++) {
		out << "        {  }, " << endl;
	}
	out << "        {  }" << "]; " << endl;
	*/

	// So I build more than one cycle
	//suc = [{ 2 },
	//{ 1 },
	//{ 4 },
	//{ 3 },
	//{ 6 },
	//{ 5 },
	//{ 8 },
	//{ 7 },
	//{ 10 },
	//{ 9 },
	//{ 12 },
	//{ 11 },
	//{ 14 },
	//{ 13 },
	//{ 16 },
	//{ 15 },
	//{ 18 },
	//{ 17 },
	//{ 20 },
	//{ 19 },
	//{ 22 },
	//{ 21 },
	//{ 24 },
	//{ 23 },
	//{ 26 },
	//{ 25 },
	//{ 28 },
	//{ 27 },
	//{ 30 },
	//{ 29 }];


	out << "suc = [ { 2 }, " << endl;
	for (size_t i = 2; i < num_tasks; i++) {
		if (i % 2 == 0) {
			out << "        { " << i-1 << " }, " << endl;
		}
		else {
			out << "        { " << i+1 << " }, " << endl;
		}
	}
	out << "        { " << num_tasks-1 << " }" << "]; " << endl;

	in.close();
}