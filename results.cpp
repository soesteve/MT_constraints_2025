#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>
using namespace std;
// namespace fs = filesystem;

const string path = "C:\\Users\\Sonia\\Desktop\\MT_constraints_2025\\";
const string name = "out_1";
// const string name = "out_2";
// const string name = "out_3";


int procesar_fichero(const string& ruta) {
    ifstream fichero(ruta);
    if (!fichero.is_open()) return -2;

    string linea;
    bool tiene_respuesta = false;
    bool contiene_TIMEOUT = false;
    bool contiene_UNSAT = false;
    int ultimo_makespan = -7;

    // expresión regular para detectar líneas que contienen algo como: makespan = 123
    // R"( ... )" es una raw string en C++: permite escribir expresiones regulares sin tener que duplicar 
    // las barras invertidas (\\) ni escapar comillas u otros caracteres especiales.
    // regex normal("makespan\\s*=\\s*(\\d+)");  es equivalente a:
    // regex raw(R"(makespan\s*=\s*(\d+))");
    // `\s * `     Cero o más espacios en blanco(espacios, tabulaciones, etc.)                 
    // `=`         El signo igual literal                                                       
    // `(\d + )`   Un grupo de captura : uno o más dígitos(es decir, un número entero positivo) 

    regex patron_makespan(R"(makespan\s*=\s*(\d+))");
    
    // smatch es un alias de tipo (typedef) para std::match_results<std::string::const_iterator>
    // Se usa cuando trabajas con std::string y expresiones regulares (std::regex).
    // match para almacenar los resultados de la búsqueda con regex_search.
    // match[0] contendrá toda la coincidencia completa.
    // match[1] contendrá el número del makespan(capturado por(\d + )).

    smatch match;

    while (getline(fichero, linea)) {
        if (linea.find("==========") != string::npos) {
            tiene_respuesta = true;
        }
        if (linea.find("TIMEOUT") != string::npos) {
            contiene_TIMEOUT = true;
        }
        if (linea.find("=====UNSATISFIABLE=====") != string::npos) {
            contiene_UNSAT = true;
        }
        // regex_search(...) Busca (no necesariamente al inicio) 
        // una parte del texto que coincida con una expresión regular.
        if (regex_search(linea, match, patron_makespan)) {
            ultimo_makespan = stoi(match[1]);   // stoi(...) convierte ese string a entero
        }
    }

    fichero.close();

    if (contiene_TIMEOUT) return -2;
    if (contiene_UNSAT) return -1;
    if (!tiene_respuesta) return -2;
    return ultimo_makespan;
}




// search_makespan creada por proceso_2024:

// search_makespan devuelve:
// -2 es TIMEOUT o no ha finalizado, no tiene el OK
// -1 es UNSATISFIABLE
// un valor >= 0 corresponde al makespan

int search_makespan(const string name_in) {
    int makespan = -7;

    ifstream file_in(name_in);

    string s;
    getline(file_in, s);

    if (!file_in) {
        cout << "Fichero " << name_in << " no encontrado." << endl;
        return -8;
    }

    bool encontrado = false;
    while (file_in && !encontrado) {
        if (s.rfind("TIMEOUT", 0) == 0) {
            makespan = -2;
            encontrado = true;
        }
        if (s.rfind("makespan", 0) == 0) {

            // Uso iteradores y expresiones regulares
            // Trabajo con expresiones regulares para quitar = ; [ ]
            regex word_regex("(\\w+)");

            sregex_iterator i = sregex_iterator(s.begin(), s.end(), word_regex);

            // Avanzo 1 el iterador pq s tiene algo como: makespan = 167
            // y el = no lo guarda por ser expresi—n regular
            ++i;
            smatch match = *i;
            string match_str = match.str();
            makespan = stoi(match_str);  // casting de string a int
            encontrado = true;
        }
        if (s.rfind("=====UNSATISFIABLE=====", 0) == 0) {
            makespan = -1;
            encontrado = true;
        }
        getline(file_in, s);
    }
    file_in.close();
    return makespan;
}



int main() {
    string carpeta = path + name;
    
    ofstream salida(path + "resultados_proceso_2025_" + name + ".txt"); // procesar_fichero 2025
    //ofstream salida(path + "resultados_proceso_2024_" + name + ".txt"); // search_makespan 2024

    if (!salida.is_open()) {
        cerr << "No se pudo crear resultados.txt\n";
        return 1;
    }

    vector<filesystem::directory_entry> ficheros;

    try {
        for (const auto& entry : filesystem::directory_iterator(carpeta)) {
            if (entry.is_regular_file()) {
                ficheros.push_back(entry);
            }
        }

        // Ordenamos alfabéticamente por nombre de fichero
        sort(ficheros.begin(), ficheros.end(), [](const filesystem::directory_entry& a, const filesystem::directory_entry& b) {
            return a.path().filename().string() < b.path().filename().string();
            });

        for (const auto& entry : ficheros) {
            string nombre = entry.path().filename().string();
            string ruta_completa = entry.path().string();

            int resultado = procesar_fichero(ruta_completa);  // resultados_proceso_2025.txt
            //int resultado = search_makespan(ruta_completa);   // resultados_proceso_2024.txt
            
            salida << nombre << ' ' << resultado << '\n';
        }

    }
    catch (const exception& e) {
        cerr << "Error al procesar archivos: " << e.what() << '\n';
        return 1;
    }

    salida.close();
    cout << "Proceso completado.\n";
    system("pause");
    return 0;
}
