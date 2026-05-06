#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
using namespace std;

// const string path = "C:\\Users\\Sonia\\Desktop\\MT_2025\\";
const string path = "C:\\Users\\Sonia\\Desktop\\MT_constraints_2025\\MT_constraints_2025\\";
//const string path_out = "C:\\Users\\Sonia\\Desktop\\MT_2025\\";  // Para hacer pruebas envío la salida a otra carpeta
//const string path_out = "C:\\Users\\Sonia\\Desktop\\MT_2025\\pruebas\\";  // Para hacer pruebas envío la salida a otra carpeta
const string path_out = "C:\\Users\\Sonia\\Desktop\\MT_2026\\results\\";  

struct tPaths {
	string file[100];
	int cont = 0;
};

struct tMatrix {
	int value[76][12] = { 0 };
	string name[76] = { "" };
	int ncol = 0;
};


struct tMatrix_2 {
	std::vector<std::vector<int>> value; // int value[76][481] = { 0 };
	std::vector<std::string> name_row;   // string name_row[76] = { "" };
	std::vector<std::string> name_col;   // string name_col[481] = { "" };

	tMatrix_2() : value(76, std::vector<int>(481, 0)),
		name_row(76, ""), name_col(481, "") {}
};


// PROTOTYPES


void mutants_paths(tPaths& array_mzns, tMatrix& matrix, tMatrix_2& matrix_diff,
	tMatrix_2& matrix_MR1,
	tMatrix_2& matrix_MR2,
	tMatrix_2& matrix_MR3,
	tMatrix_2& matrix_MR4,
	tMatrix_2& matrix_MR5,
	tMatrix_2& matrix_MR6,
	tMatrix_2& matrix_MR7,
	tMatrix_2& matrix_MR8
);

void mayor_durations_dicc(ifstream& file_mayor, unordered_map<string, int>& dicc_mayor_durations);

void sum_durations_dicc(ifstream& file_in, unordered_map<string, int>& dicc_durations);
void sum_durations(unordered_map<string, int>& dicc_durations, string original_mzn_original_dnz, int& sum_1,
	string original_mzn_fu_dzn, int& sum_2,
	string mut_mzn_original_dzn, int& sum_1_mut,
	string mut_mzn_fu_dzn, int& sum_2_mut);


void results_dicc(ifstream& file_in, unordered_map<string, int>& dicc_results);
bool check_files_and_find_Os(unordered_map<string, int>& dicc_results,
	string original_mzn_original_dnz, int& O1,
	string original_mzn_fu_dzn, int& O2,
	string mut_mzn_original_dzn, int& O1_mut,
	string mut_mzn_fu_dzn, int& O2_mut,
	ofstream& log);


string extract_dzn(string file);
string extract_mzn(string file);

void process_all(tPaths& array_mzns, tPaths& array_dzn, tMatrix& matrix, tMatrix_2& matrix_diff,
	tMatrix_2& matrix_MR1,
	tMatrix_2& matrix_MR2,
	tMatrix_2& matrix_MR3,
	tMatrix_2& matrix_MR4,
	tMatrix_2& matrix_MR5,
	tMatrix_2& matrix_MR6,
	tMatrix_2& matrix_MR7,
	tMatrix_2& matrix_MR8);
bool process_MR1(ofstream& log, int O1, int O2, int O1_mut, int O2_mut, int sum_1, int sum_2, int sum_1_mut, int sum_2_mut);
bool process_MR2(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR3(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR4(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR5(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR6(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR7(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);
bool process_MR8(ofstream& log, int O1, int O2, int O1_mut, int O2_mut);



int main() {

	// In the array of mzns, the first is the original rcpsp.mzn code and then all the mutant (mzns).
	tPaths array_mzns;
	tMatrix matrix;
	tMatrix_2 matrix_diff, matrix_MR1, matrix_MR2, matrix_MR3, matrix_MR4, matrix_MR5, matrix_MR6, matrix_MR7, matrix_MR8;


	mutants_paths(array_mzns, matrix, matrix_diff, matrix_MR1, matrix_MR2, matrix_MR3, matrix_MR4,
		matrix_MR5, matrix_MR6, matrix_MR7, matrix_MR8);


	// In the dzns array, the first is the original dzn and then all the dzns generated as follow-up

	tPaths array_dzn;

	array_dzn.file[0] = ".dzn";   // Note: the first one is the original
	array_dzn.cont++;
	array_dzn.file[1] = "_fu_all_prec.dzn"; // MR1
	array_dzn.cont++;
	array_dzn.file[2] = "_fu_cycle.dzn"; // MR2
	array_dzn.cont++;
	array_dzn.file[3] = "_fu_d.dzn"; // MR3
	array_dzn.cont++;
	array_dzn.file[4] = "_fu_rc_1.dzn"; // MR4
	array_dzn.cont++;
	array_dzn.file[5] = "_fu_rc_mayor_rr.dzn";   // MR5
	array_dzn.cont++;
	array_dzn.file[6] = "_fu_rc_and_rr_0.dzn";  // MR6
	array_dzn.cont++;
	array_dzn.file[7] = "_fu_rr_max.dzn";  // MR7
	array_dzn.cont++;
	array_dzn.file[8] = "_fu_dur_0.dzn";  // MR8
	array_dzn.cont++;

	process_all(array_mzns, array_dzn, matrix, matrix_diff, matrix_MR1, matrix_MR2, matrix_MR3, matrix_MR4, matrix_MR5, matrix_MR6, matrix_MR7, matrix_MR8);

	system("pause");
	return 0;
}

void process_all(tPaths& array_mzns, tPaths& array_dzn, tMatrix& matrix, tMatrix_2& matrix_diff,
	tMatrix_2& matrix_MR1,
	tMatrix_2& matrix_MR2,
	tMatrix_2& matrix_MR3,
	tMatrix_2& matrix_MR4,
	tMatrix_2& matrix_MR5,
	tMatrix_2& matrix_MR6,
	tMatrix_2& matrix_MR7,
	tMatrix_2& matrix_MR8) {


	// I store the process files in the dicc_results dictionary, can be more than one file.
	unordered_map<string, int> dicc_results;


	std::vector<std::string> file_names;
	file_names.push_back("out_1.txt");
	file_names.push_back("out_2.txt");
	file_names.push_back("out_3.txt");

	ifstream file_results;
	for (int i = 0; i < file_names.size(); i++) {
		ifstream file_results(path + file_names.at(i));
		
		if (!file_results) { 
			cout << "Fichero " << file_names.at(i) << " no encontrado.  \n"; 
		}

		results_dicc(file_results, dicc_results);
		
		file_results.close();
	}



	// I save the file "sum_durations.txt" in the dictionary dicc_durations

	ifstream file_in(path + "sum_durations.txt");
	if (!file_in) {
		cout << " File sum_durations.txt not found. \n";
	}
	unordered_map<string, int> dicc_durations;
	sum_durations_dicc(file_in, dicc_durations);
	file_in.close();

	// I save the file "mayor_duration.txt" in the dictionary dicc_mayor_duration

	ifstream file_mayor(path + "longer_durations.txt");
	if (!file_mayor) {
		cout << " File longer_durations.txt not found. \n";
	}
	unordered_map<string, int> dicc_mayor_duration;
	mayor_durations_dicc(file_mayor, dicc_mayor_duration);
	file_mayor.close();




	ofstream mutants_killed(path_out + "V9_mutants_killed.csv");

	mutants_killed << "Mutant;O1!=O1_mut;MR1;MR2;MR3;MR4;MR5;MR6;MR7;MR8;Killed\n";

	ofstream mutants_killed_2(path_out + "V9_killed_different_outputs.csv");  // Matriz detallada de la columna O1!=O1_mut
	ofstream mutants_killed_MR1(path_out + "V9_killed_MR1.csv");
	ofstream mutants_killed_MR2(path_out + "V9_killed_MR2.csv");
	ofstream mutants_killed_MR3(path_out + "V9_killed_MR3.csv");
	ofstream mutants_killed_MR4(path_out + "V9_killed_MR4.csv");
	ofstream mutants_killed_MR5(path_out + "V9_killed_MR5.csv");
	ofstream mutants_killed_MR6(path_out + "V9_killed_MR6.csv");
	ofstream mutants_killed_MR7(path_out + "V9_killed_MR7.csv");
	ofstream mutants_killed_MR8(path_out + "V9_killed_MR8.csv");

	string s = "";
	ofstream log(path_out + "V9_process_MRs_log_2025.txt");

	int cont_log = 0;
	int cont_killed, cont_killed_2 = 0, cont_killed_MR1 = 0, cont_killed_MR2 = 0, cont_killed_MR3 = 0,
		cont_killed_MR4 = 0, cont_killed_MR5 = 0, cont_killed_MR6 = 0, cont_killed_MR7 = 0, cont_killed_MR8 = 0;
	int ncol_value = 0;

	for (int i = 1; i <= 48; i++) {  // 1 -- 48
		for (int j = 1; j <= 10; j++) {  // 1 -- 10
			matrix_diff.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + array_dzn.file[0] + ";";
			matrix_MR1.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_all_prec" + array_dzn.file[0] + ";";
			matrix_MR2.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_cycle" + array_dzn.file[0] + ";";
			matrix_MR3.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_d" + array_dzn.file[0] + ";";
			matrix_MR4.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_1" + array_dzn.file[0] + ";";
			matrix_MR5.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_mayor_rr" + array_dzn.file[0] + ";";
			matrix_MR6.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rc_and_rr_0" + array_dzn.file[0] + ";";
			matrix_MR7.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_rr_max" + array_dzn.file[0] + ";";
			matrix_MR8.name_col[ncol_value] = "J30_" + to_string(i) + "_" + to_string(j) + "_fu_dur_0" + array_dzn.file[0] + ";";


			cont_killed_2 = 0, cont_killed_MR1 = 0, cont_killed_MR2 = 0, cont_killed_MR3 = 0, cont_killed_MR4 = 0,
				cont_killed_MR5 = 0, cont_killed_MR6 = 0, cont_killed_MR7 = 0, cont_killed_MR8 = 0;

			for (size_t k = 0; k < array_mzns.cont; k++) {  //  k = 0  son el original y los mutantes
				for (size_t w = 1; w < array_dzn.cont; w++) {  // w = 1, ... son los dzns 

					string path_aux = "rcpsp.mzn--J30";

					string original_mzn_original_dnz = path_aux + "_" + to_string(i) + "_" + to_string(j) + array_dzn.file[0];
					string original_mzn_fu_dzn = path_aux + "_" + to_string(i) + "_" + to_string(j) + array_dzn.file[w];

					string mut_mzn_original_dzn = array_mzns.file[k] + "_" + to_string(i) + "_" + to_string(j) + array_dzn.file[0];
					string mut_mzn_fu_dzn = array_mzns.file[k] + "_" + to_string(i) + "_" + to_string(j) + array_dzn.file[w];

					cont_log++;
					log << cont_log << " \n";

					int O1 = -3, O2 = -3, O1_mut = -3, O2_mut = -3;
					// -2 is TIMEOUT
					// -1 is UNSATISFIABLE
					// a value >= 0 corresponds to the makespan

					if (check_files_and_find_Os(dicc_results,
						original_mzn_original_dnz, O1, original_mzn_fu_dzn, O2,
						mut_mzn_original_dzn, O1_mut, mut_mzn_fu_dzn, O2_mut, log)) {


						log << "O1 " << original_mzn_original_dnz << " = " << O1 << " \n"
							<< "O2 " << original_mzn_fu_dzn << " = " << O2 << " \n"
							<< "O1_mut " << mut_mzn_original_dzn << " = " << O1_mut << " \n"
							<< "O2_mut " << mut_mzn_fu_dzn << " = " << O2_mut << " \n";

						cont_killed = 0;

						cont_killed_2 = 0, cont_killed_MR1 = 0, cont_killed_MR2 = 0, cont_killed_MR3 = 0, cont_killed_MR4 = 0,
							cont_killed_MR5 = 0, cont_killed_MR6 = 0, cont_killed_MR7 = 0, cont_killed_MR8 = 0;


						if (O1 == O1_mut && O2 == O2_mut) {
							// log << "The results of the originals (O1 and O1_mut) and mutants are equal (O2 and O2_mut).";

						}
						else {

							// Mark as different. column "Exists difference"
							// matrix.value[k][9] = 1;
							// log << " Not equivalent: " << matrix.name[k] << endl;

							// If the original and the mutant have different results, the mutant is killed
							// Including insat (-1) and timeout (-2)
							if (O1 != O1_mut) {
								log << "O1 != O1_mut kills " << matrix.name[k] << "\n";
								matrix.value[k][0] = 1;
								matrix_diff.value[k][ncol_value] = 1;
								cont_killed++;
								cont_killed_2++;
							}

							// For MR1 I need the sums
							int sum_1 = -3, sum_2 = -3, sum_1_mut = -3, sum_2_mut = -3;

							sum_durations(dicc_durations, original_mzn_original_dnz, sum_1, original_mzn_fu_dzn, sum_2,
								mut_mzn_original_dzn, sum_1_mut, mut_mzn_fu_dzn, sum_2_mut);

							string mut_1 = extract_dzn(mut_mzn_original_dzn);
							string mut_2 = extract_dzn(mut_mzn_original_dzn);
							int dur_max_1 = dicc_mayor_duration.at(mut_1);
							int dur_max_2 = dicc_mayor_duration.at(mut_2);

							// Process MR1 if it corresponds to the fu (w==1) 
							//if (w == 1 && matrix.value[k][1] == 0) and if it has not been killed previously

							if (w == 1) {

								if (process_MR1(log, O1, O2, O1_mut, O2_mut, sum_1, sum_2, sum_1_mut, sum_2_mut)) {
									matrix.value[k][1] = 1;
									matrix_MR1.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR1++;

									log << "MR1 kills " << matrix.name[k] << endl;
									// ":  O1: " << O1 << ", O2: " << O2
									//	<< ", O1_mut: " << O1_mut << ", O2_mut: " << O2_mut << ", sum_1 " << sum_1
									//	<< ", sum_2 " << sum_2 << ", sum_1_mut " << sum_1_mut << ", sum_2_mut " << sum_2_mut << endl;
								}
							}


							//if (w == 2 && matrix.value[k][2] == 0) {
							if (w == 2) {

								if (process_MR2(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][2] = 1;
									matrix_MR2.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR2++;

									log << "MR2 kills " << matrix.name[k] << endl;
								}
							}

							//if (w == 3 && matrix.value[k][3] == 0) {
							if (w == 3) {

								if (process_MR3(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][3] = 1;
									matrix_MR3.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR3++;

									log << "MR3 kills " << matrix.name[k] << endl;
								}
							}

							//if (w == 4 && matrix.value[k][4] == 0) {
							if (w == 4) {

								if (process_MR4(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][4] = 1;
									matrix_MR4.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR4++;

									log << "MR4 kills " << matrix.name[k] << endl;
								}
							}
							if (w == 5) {

								if (process_MR5(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][5] = 1;
									matrix_MR5.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR5++;

									log << "MR5 kills " << matrix.name[k] << endl;
								}
							}

							if (w == 6) {

								if (process_MR6(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][6] = 1;
									matrix_MR6.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR6++;

									log << "MR6 kills " << matrix.name[k] << endl;
								}
							}
							if (w == 7) {

								if (process_MR7(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][7] = 1;
									matrix_MR7.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR7++;

									log << "MR7 kills " << matrix.name[k] << endl;
								}
							}
							if (w == 8) {

								if (process_MR8(log, O1, O2, O1_mut, O2_mut)) {
									matrix.value[k][8] = 1;
									matrix_MR8.value[k][ncol_value] = 1;

									cont_killed++;
									cont_killed_MR8++;

									log << "MR8 kills " << matrix.name[k] << endl;
								}
							}

						}
						if (cont_killed > 0) {
							matrix.value[k][9] = 1;  //  is the Killed column
						}
						// cont_killed_* are either 0 or 1
						if (cont_killed_2 > 0) {
							matrix_diff.value[k][480] = cont_killed_2;  //  is the Killed column
						}
						if (cont_killed_MR1 > 0) {
							matrix_MR1.value[k][480] = cont_killed_MR1;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR2 > 0) {
							matrix_MR2.value[k][480] = cont_killed_MR2;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR3 > 0) {
							matrix_MR3.value[k][480] = cont_killed_MR3;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR4 > 0) {
							matrix_MR4.value[k][480] = cont_killed_MR4;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR5 > 0) {
							matrix_MR5.value[k][480] = cont_killed_MR5;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR6 > 0) {
							matrix_MR6.value[k][480] = cont_killed_MR6;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR7 > 0) {
							matrix_MR7.value[k][480] = cont_killed_MR7;  //  It's the column of mutants killed by this MR
						}
						if (cont_killed_MR8 > 0) {
							matrix_MR8.value[k][480] = cont_killed_MR8;  //  It's the column of mutants killed by this MR
						}
					}
					log << "\n";
				}
			}

			ncol_value++; 

		}
	}

	// Transfer the matrix to the file V9_mutants_killed.csv
	
	for (int nrow = 0; nrow < 76; nrow++) {
		mutants_killed << matrix.name[nrow];

		for (int ncol = 0; ncol < 10; ncol++) { 
			mutants_killed << ";" << matrix.value[nrow][ncol];
		}
		mutants_killed << "\n";
	}

	// Transfer the matrix_MRx to the file V9_mutants_killed_diff_outputs.csv

	mutants_killed_2 << "Mutant;";
	mutants_killed_MR1 << "Mutant;";
	mutants_killed_MR2 << "Mutant;";
	mutants_killed_MR3 << "Mutant;";
	mutants_killed_MR4 << "Mutant;";
	mutants_killed_MR5 << "Mutant;";
	mutants_killed_MR6 << "Mutant;";
	mutants_killed_MR7 << "Mutant;";
	mutants_killed_MR8 << "Mutant;";

	for (int j = 0; j < 481; j++) {
		mutants_killed_2 << matrix_diff.name_col[j];
		mutants_killed_MR1 << matrix_MR1.name_col[j];
		mutants_killed_MR2 << matrix_MR2.name_col[j];
		mutants_killed_MR3 << matrix_MR3.name_col[j];
		mutants_killed_MR4 << matrix_MR4.name_col[j];
		mutants_killed_MR5 << matrix_MR5.name_col[j];
		mutants_killed_MR6 << matrix_MR6.name_col[j];
		mutants_killed_MR7 << matrix_MR7.name_col[j];
		mutants_killed_MR8 << matrix_MR8.name_col[j];
	}

	for (int nrow = 0; nrow < 76; nrow++) {
		mutants_killed_2 << matrix_diff.name_row[nrow];
		mutants_killed_MR1 << matrix_MR1.name_row[nrow];
		mutants_killed_MR2 << matrix_MR2.name_row[nrow];
		mutants_killed_MR3 << matrix_MR3.name_row[nrow];
		mutants_killed_MR4 << matrix_MR4.name_row[nrow];
		mutants_killed_MR5 << matrix_MR5.name_row[nrow];
		mutants_killed_MR6 << matrix_MR6.name_row[nrow];
		mutants_killed_MR7 << matrix_MR7.name_row[nrow];
		mutants_killed_MR8 << matrix_MR8.name_row[nrow];

		for (int ncol = 0; ncol < 481; ncol++) {
			mutants_killed_2 << ";" << matrix_diff.value[nrow][ncol];
			mutants_killed_MR1 << ";" << matrix_MR1.value[nrow][ncol];
			mutants_killed_MR2 << ";" << matrix_MR2.value[nrow][ncol];
			mutants_killed_MR3 << ";" << matrix_MR3.value[nrow][ncol];
			mutants_killed_MR4 << ";" << matrix_MR4.value[nrow][ncol];
			mutants_killed_MR5 << ";" << matrix_MR5.value[nrow][ncol];
			mutants_killed_MR6 << ";" << matrix_MR6.value[nrow][ncol];
			mutants_killed_MR7 << ";" << matrix_MR7.value[nrow][ncol];
			mutants_killed_MR8 << ";" << matrix_MR8.value[nrow][ncol];
		}
		mutants_killed_2 << "\n";
		mutants_killed_MR1 << "\n";
		mutants_killed_MR2 << "\n";
		mutants_killed_MR3 << "\n";
		mutants_killed_MR4 << "\n";
		mutants_killed_MR5 << "\n";
		mutants_killed_MR6 << "\n";
		mutants_killed_MR7 << "\n";
		mutants_killed_MR8 << "\n";
	}


}

bool process_MR1(ofstream& log, int O1, int O2, int O1_mut, int O2_mut, int sum_1, int sum_2, int sum_1_mut, int sum_2_mut) {

	if (O1_mut == -1) {     // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	if (O2_mut != sum_2_mut) {
		log << "This mutant can be killed with MR1, because O2_mut (" << O2_mut << ") es distinto que la suma de las duraciones (" << sum_2_mut << "). \n";
		return true;
	}

	// log << "This mutant cannot be killed with MR1. The sum of the durations (" << sum_2_mut << ") \n";
	return false;
}

bool process_MR2(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {   // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	if (O2_mut != -1) {    // If fu is finite (!= -1), then it can be killed
		log << "This mutant can be killed with MR2 because fu is finite or timeout (!= -1). \n";
		return true;
	}

	return false;
}

bool process_MR3(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	// O2_mut  must be finite

	if (O2_mut == -1) {   
		log << "This mutant can be killed with MR3 pq O2_mut == -1. \n";
		return true;
	}

	if (O2_mut == -2) {
		log << "This mutant can be killed with MR3 pq O2_mut es timeout. \n";
		return true;
	}

	if (O2_mut <= O1_mut) {    // Si O1_mut < O2_mut (menor estricto) NO se cumple, entonces se mata
		log << "This mutant can be killed with MR3 pq O2_mut <= O1_mut. \n";
		return true;
	}

	return false;
}

bool process_MR4(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	// Si O1 es finito entonces O2 must be finite
	if (O2_mut == -1) {    
		log << "This mutant can be killed with MR4 because O2_mut == -1. \n";
		return true;
	}

	if (O2_mut == -2) {    
		log << "This mutant can be killed with MR4 because O2_mut == -2. \n";
		return true;
	}

	if (O2_mut > O1_mut) {    // Si O2_mut <= O1_mut NO se cumple, entonces se mata
		log << "This mutant can be killed with MR4 because O2_mut > O1_mut. \n";
		return true;
	}

	return false;
}


bool process_MR5(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	if (O2_mut == -1) {
		return false;
	}

	if (O2_mut == -2) {
		return false;
	}
	
	// Since there are tasks with duration > 0, O2 must be > 0  
	// Additionally, O1 and O2 belong to R+ = { x in R | x > 0 }
	if (O2_mut == 0) {
		return true;
	}

	if (O2_mut < O1_mut) {
		log << "This mutant can be killed with MR5 because O2_mut < O1_mut. \n";
		return true;
	}

	return false;
}


bool process_MR6(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	if (O2_mut == -1) {
		log << "This mutant can be killed with MR6 pq O2_mut == -1. \n";
		return true;
	}

	if (O2_mut == -2) {
		log << "This mutant can be killed with MR6 pq O2_mut == -2. \n";
		return true;
	}

	if (O2_mut > O1_mut) {
		log << "This mutant can be killed with MR6 pq O2_mut > O1_mut. \n";
		return true;
	}

	return false;
}


bool process_MR7(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	
	if (O2_mut == -1) {
		log << "This mutant cannot be killed with MR7 because O2_mut == -1. \n";
		return false;
	}

	if (O2_mut == -2) {
		log << "This mutant cannot be killed with MR7 because O2_mut == -2. \n";
		return false;
	}
	

	if (O2_mut < O1_mut) {
		log << "This mutant can be killed with MR7 because O2_mut < O1_mut. \n";
		return true;
	}

	return false;
}


bool process_MR8(ofstream& log, int O1, int O2, int O1_mut, int O2_mut) {

	if (O1_mut == -1) {    // O1_mut must be finite (!= -1) 
		return false;
	}

	if (O1_mut == -2) {     // O1_mut must be finite (!= -2) 
		return false;
	}

	if (O2_mut == -1) {
		log << "This mutant can be killed with MR8 because O2_mut == -1. \n";
		return true;
	}

	if (O2_mut == -2) {
		log << "This mutant can be killed with MR8 because O2_mut == -2. \n";
		return true;
	}

	if (O2_mut > O1_mut) {
		log << "This mutant can be killed with MR8 because O2_mut > O1_mut. \n";
		return true;
	}

	return false;
}

string extract_dzn(string file) {
	// string.substr(size_t begin, size_t length)
	unsigned long int pos1 = file.find("--");
	string file_aux = file.substr(pos1 + 2, 60);  //

	return file_aux;
}


string extract_mzn(string file) {
	unsigned long int pos1 = file.find("/");
	unsigned long int pos2 = file.find("--");
	string file_aux = file.substr(pos1 + 1, pos2 - pos1 - 1);  //

	file_aux.pop_back();  // t
	file_aux.pop_back();  // u
	file_aux.pop_back();  // o
	file_aux.pop_back();  // .
	file_aux.pop_back();  // n
	file_aux.pop_back();  // z
	file_aux.pop_back();  // m
	file_aux.pop_back();  // .

	return file_aux;
}

void sum_durations_dicc(ifstream& file_in, unordered_map<string, int>& dicc_durations) {
	// The file sum_durations.txt contains the file name and its sum
	string aux;
	int sum;

	file_in >> aux >> sum;
	while (file_in) {
		dicc_durations[aux] = sum;
		file_in >> aux >> sum;
	}
}


void mayor_durations_dicc(ifstream& file_mayor, unordered_map<string, int>& dicc_mayor_durations) {

	string aux;
	int sum;

	file_mayor >> aux >> sum;
	while (file_mayor) {
		dicc_mayor_durations[aux] = sum;
		file_mayor >> aux >> sum;
	}
}


void sum_durations(unordered_map<string, int>& dicc_durations,
	string original_mzn_original_dnz, int& sum_1, string original_mzn_fu_dzn, int& sum_2,
	string mut_mzn_original_dzn, int& sum_1_mut, string mut_mzn_fu_dzn, int& sum_2_mut) {

	// Extraigo el fichero dzn

	original_mzn_original_dnz = extract_dzn(original_mzn_original_dnz);
	original_mzn_fu_dzn = extract_dzn(original_mzn_fu_dzn);
	mut_mzn_original_dzn = extract_dzn(mut_mzn_original_dzn);
	mut_mzn_fu_dzn = extract_dzn(mut_mzn_fu_dzn);


	if (dicc_durations.count(original_mzn_original_dnz) > 0) {
		sum_1 = dicc_durations.at(original_mzn_original_dnz);
	}
	else {
		cout << "1. The entry: " << original_mzn_original_dnz << " does NOT exist in the dicc_durations dictionary" << endl;
	}

	if (dicc_durations.count(original_mzn_fu_dzn) > 0) {
		sum_2 = dicc_durations.at(original_mzn_fu_dzn);

	}
	else {
		cout << "2. The entry: " << original_mzn_fu_dzn << " does NOT exist in the dicc_durations dictionary" << endl;
	}

	if (dicc_durations.count(mut_mzn_original_dzn) > 0) {
		sum_1_mut = dicc_durations.at(mut_mzn_original_dzn);
	}
	else {
		cout << "3. The entry: " << mut_mzn_original_dzn << " does NOT exist in the dicc_durations dictionary" << endl;
	}

	if (dicc_durations.count(mut_mzn_fu_dzn) > 0) {
		sum_2_mut = dicc_durations.at(mut_mzn_fu_dzn);
	}
	else {
		cout << "4. The entry: " << mut_mzn_fu_dzn << " does NOT exist in the dicc_durations dictionary" << endl;
	}
}


void results_dicc(ifstream& file_results, unordered_map<string, int>& dicc_results) {

	string s;
	int n;
	file_results >> s >> n;

	while (file_results) {
		unsigned long int pos1 = s.find("/");
		unsigned long int pos2 = s.find(".out");
		string aux = s.substr(pos1 + 1, pos2 - pos1 - 1);  //

		if (aux == "")
			cout << s << " -- " << n << endl;
		else {
			dicc_results[aux] = n;
		}

		file_results >> s >> n;
	}
}

bool check_files_and_find_Os(unordered_map<string, int>& dicc_results,
	string original_mzn_original_dnz, int& O1,
	string original_mzn_fu_dzn, int& O2,
	string mut_mzn_original_dzn, int& O1_mut,
	string mut_mzn_fu_dzn, int& O2_mut,
	ofstream& log) {

	bool result = true;

	if (dicc_results.count(original_mzn_original_dnz) > 0) {
		O1 = dicc_results.at(original_mzn_original_dnz);
	}
	else {
		log << original_mzn_original_dnz << " Not found. \n";
		result = false;
	}

	if (dicc_results.count(original_mzn_fu_dzn) > 0) {
		O2 = dicc_results.at(original_mzn_fu_dzn);
	}
	else {
		log << original_mzn_fu_dzn << " Not found. \n";
		result = false;
	}

	if (dicc_results.count(mut_mzn_original_dzn) > 0) {
		O1_mut = dicc_results.at(mut_mzn_original_dzn);
	}
	else {
		log << mut_mzn_original_dzn << " Not found. \n";
		result = false;
	}

	if (dicc_results.count(mut_mzn_fu_dzn) > 0) {
		O2_mut = dicc_results.at(mut_mzn_fu_dzn);
	}
	else {
		log << mut_mzn_fu_dzn << " Not found. \n";
		result = false;
	}

	return result;
}


void mutants_paths(tPaths& array_mzns, tMatrix& matrix, tMatrix_2& matrix_diff,
	tMatrix_2& matrix_MR1,
	tMatrix_2& matrix_MR2,
	tMatrix_2& matrix_MR3,
	tMatrix_2& matrix_MR4,
	tMatrix_2& matrix_MR5,
	tMatrix_2& matrix_MR6,
	tMatrix_2& matrix_MR7,
	tMatrix_2& matrix_MR8) {

	matrix_diff.name_col[480] = "Result\n";
	matrix_MR1.name_col[480] = "Result\n";
	matrix_MR2.name_col[480] = "Result\n";
	matrix_MR3.name_col[480] = "Result\n";
	matrix_MR4.name_col[480] = "Result\n";
	matrix_MR5.name_col[480] = "Result\n";
	matrix_MR6.name_col[480] = "Result\n";
	matrix_MR7.name_col[480] = "Result\n";
	matrix_MR8.name_col[480] = "Result\n";


	ifstream file_in(path + "mutants.txt");
	string aux = "";

	file_in >> aux;

	if (!file_in) {
		cout << "File mutants.txt not found  \n";
	}

	int i = 0;
	while (file_in) {
		array_mzns.file[array_mzns.cont] = aux + "--J30";
		array_mzns.cont++;

		aux.pop_back(); // n
		aux.pop_back(); // z
		aux.pop_back(); // m
		aux.pop_back(); // .

		matrix.name[i] = aux;
		matrix_diff.name_row[i] = aux;
		matrix_MR1.name_row[i] = aux;
		matrix_MR2.name_row[i] = aux;
		matrix_MR3.name_row[i] = aux;
		matrix_MR4.name_row[i] = aux;
		matrix_MR5.name_row[i] = aux;
		matrix_MR6.name_row[i] = aux;
		matrix_MR7.name_row[i] = aux;
		matrix_MR8.name_row[i] = aux;
		i++;

		file_in >> aux;
	}
	file_in.close();
}
