// This program is part of a project that generates follow-up files for the PSPLIB benchmarks, 
// specifically for the J30 problem set. 
// The program calculates the sum of the durations and the greatest duration for each .dzn file, 
// and writes the results in two separate files: sum_durations.txt and mayor_duration.txt


#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <filesystem>
using namespace std;

const string path = "../";

void proc_sum_dur(string path_file, string name_file, ofstream& file_sum);
void proc_greater_dur(string path_file, string name_file, ofstream& file_sum);

int main()
{
	ofstream file_sum(path + "sum_durations.txt");
	if (!file_sum) {
		cerr << "Unable to open file " << path + "sum_durations.txt" << endl;
		exit(1);   // call system to stop
	}
	ofstream file_greater(path + "longer_durations.txt");
	if (!file_greater) {
		cerr << "Unable to open file " << path + "longer_durations.txt" << endl;
		exit(1);   // call system to stop
	}

	string path_file = path + "benchmarks/data/data_psplib/j30/";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + ".dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR1/j30/";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_all_prec.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR2/j30/";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_cycle.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR3/j30/";
	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_d.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR4/j30/";
	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			for (int k = 1; k <= 1; k++) {  // 4
				string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_" + to_string(k) + ".dzn";
				proc_sum_dur(path_file, name_file, file_sum);
				proc_greater_dur(path_file, name_file, file_greater);
			}
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR5/j30/";

	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_mayor_rr.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR6/j30/";
	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_and_rr_0.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR7/j30/";
	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rr_max.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	path_file = path + "benchmarks/data/data_psplib_follow_ups/MR8/j30/";
	for (int i = 1; i <= 48; i++) {  // 48
		for (int j = 1; j <= 10; j++) {  // 10
			string name_file = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_dur_0.dzn";
			proc_sum_dur(path_file, name_file, file_sum);
			proc_greater_dur(path_file, name_file, file_greater);
		}
	}

	file_sum.close();
	file_greater.close();
	system("pause");
	return 0;
}



void proc_sum_dur(string path_file, string name_file, ofstream& file_sum) {

	ifstream file_in(path_file + name_file);

	if (!file_in) {
		cout << path_file + name_file << " no se encuentra" << endl;
		return;
	}

	std::string s = "";
	getline(file_in, s);   // n_res
	getline(file_in, s);   // rc
	getline(file_in, s);   // n_tasks

	// Regular expressions to remove = ; [ ]
	std::regex word_regex("(\\w+)");

	// iterators
	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	++i;
	std::smatch match = *i;
	std::string match_str = match.str();
	int num_tasks = stoi(match_str);  // casting from string to int

	getline(file_in, s);   // d

	i = std::sregex_iterator(s.begin(), s.end(), word_regex);

	// Lines are read and written directly because they do not change
	// suc until a line that starts with suc 

	// Sum durations
	int suma = 0;
	for (int k = 0; k < num_tasks; k++) {
		++i;
		match = *i;
		match_str = match.str();
		suma = suma + stoi(match_str);
	}


	file_sum << name_file << " " << suma << endl;

	file_in.close();
}




void proc_greater_dur(string path_file, string name_file, ofstream& file_sum) {

	ifstream file_in(path_file + name_file);

	if (!file_in) {
		cout << path_file + name_file << " no se encuentra" << endl;
		return;
	}

	std::string s = "";
	getline(file_in, s);   // n_res
	getline(file_in, s);   // rc
	getline(file_in, s);   // n_tasks

	std::regex word_regex("(\\w+)");

	std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);
	++i;
	std::smatch match = *i;
	std::string match_str = match.str();
	int num_tasks = stoi(match_str);  // casting de string a int

	getline(file_in, s);   // d

	i = std::sregex_iterator(s.begin(), s.end(), word_regex);

	int mayor = 0;
	for (int k = 0; k < num_tasks; k++) {
		++i;
		match = *i;
		match_str = match.str();
		mayor = max(mayor, stoi(match_str));
	}


	file_sum << name_file << " " << mayor << endl;

	file_in.close();
}
