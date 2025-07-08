#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

// procesar_fichero creada por proceso_2025
int procesar_fichero(const std::string& ruta) {
    std::ifstream fichero(ruta);
    if (!fichero.is_open()) return -2;

    std::string linea;
    bool contiene_OK = false;
    bool contiene_TIMEOUT = false;
    bool contiene_UNSAT = false;
    int ultimo_makespan = -7;

    std::regex patron_makespan(R"(makespan\s*=\s*(\d+))");
    std::smatch match;

    while (std::getline(fichero, linea)) {
        if (linea.find("OK") != std::string::npos) {
            contiene_OK = true;
        }
        if (linea.find("TIMEOUT") != std::string::npos) {
            contiene_TIMEOUT = true;
        }
        if (linea.find("=====UNSATISFIABLE=====") != std::string::npos) {
            contiene_UNSAT = true;
        }
        if (std::regex_search(linea, match, patron_makespan)) {
            ultimo_makespan = std::stoi(match[1]);
        }
    }

    fichero.close();

    if (!contiene_OK) return -2;
    if (contiene_TIMEOUT) return -2;
    if (contiene_UNSAT) return -1;
    return ultimo_makespan;
}




// search_makespan creada por proceso_2024:

// search_makespan devuelve:
// -2 es TIMEOUT o no ha finalizado, no tiene el OK
// -1 es UNSATISFIABLE
// un valor >= 0 corresponde al makespan

int search_makespan(const std::string name_in) {
    int makespan = -7;

    std::ifstream file_in(name_in);

    std::string s;
    std::getline(file_in, s);

    if (!file_in) {
        std::cout << "Fichero " << name_in << " no encontrado." << std::endl;
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
            std::regex word_regex("(\\w+)");

            std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), word_regex);

            // Avanzo 1 el iterador pq s tiene algo como: makespan = 167
            // y el = no lo guarda por ser expresi—n regular
            ++i;
            std::smatch match = *i;
            std::string match_str = match.str();
            makespan = stoi(match_str);  // casting de string a int
            encontrado = true;
        }
        if (s.rfind("=====UNSATISFIABLE=====", 0) == 0) {
            makespan = -1;
            encontrado = true;
        }
        getline(file_in, s);
    }
    /*
       if (!encontrado) {
           cout << name_in << " no encontrado." << endl;
       }
    */
    file_in.close();
    return makespan;
}



int main() {

    std::string carpeta = "C:\\Users\\Sonia\\Desktop\\MT_2025\\out_20250620";
    
    std::ofstream salida("C:\\Users\\Sonia\\Desktop\\MT_2025\\resultados_proceso_2025_out_20250620.txt"); // procesar_fichero
    //std::ofstream salida("C:\\Users\\Sonia\\Desktop\\MT_2025\\resultados_proceso_2024_out_20250620.txt"); // search_makespan

    if (!salida.is_open()) {
        std::cerr << "No se pudo crear resultados.txt\n";
        return 1;
    }

    std::vector<fs::directory_entry> ficheros;

    try {
        for (const auto& entry : fs::directory_iterator(carpeta)) {
            if (entry.is_regular_file()) {
                ficheros.push_back(entry);
            }
        }

        // Ordenamos alfabéticamente por nombre de fichero
        std::sort(ficheros.begin(), ficheros.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
            return a.path().filename().string() < b.path().filename().string();
            });

        for (const auto& entry : ficheros) {
            std::string nombre = entry.path().filename().string();
            std::string ruta_completa = entry.path().string();

            int resultado = procesar_fichero(ruta_completa);  // resultados_proceso_2025.txt
            //int resultado = search_makespan(ruta_completa);   // resultados_proceso_2024.txt
            
            salida << nombre << ' ' << resultado << '\n';
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error al procesar archivos: " << e.what() << '\n';
        return 1;
    }

    salida.close();
    std::cout << "Proceso completado. Revisa resultados.txt.\n";
    return 0;
}
