#pragma once
#include <fstream>
#include <string>
using namespace std;

class Ubicacion {
private:
    char norte;
    char sur;
    char este;
    char oeste;
    string anillos[12];

public:
    Ubicacion();
    Ubicacion(char n, char s, char e, char o, string a[]);
    void setZona(char n, char s, char e, char o, string a[]);
    char getNorte();
    char getSur();
    char getEste();
    char getOeste();
    string* getAnillos(); // Corrección: Declaración correcta del método getAnillos
    void guardarArchivo(ofstream& fsalida);
    bool leerArchivo(ifstream& fentrada);
    bool eliminar(const string& nombreArchivo); // Corrección: Cambio de tipo de archivo fstream a string&
    bool modificar(const string& nombreArchivo, int nroReg, const Ubicacion& nuevaZona); // Corrección: Cambio de tipo de archivo fstream a string&
    bool buscar(const string& nombreArchivo, int nroReg, Ubicacion& zonaEncontrada); // Corrección: Cambio de tipo de archivo fstream a string&
    int getTamBytesRegistro();
};
