#include <iostream>
#include <fstream>
#include <string>
#include "Zona.h"

using namespace std;

// Implementación de los métodos de la clase Zona

Ubicacion::Ubicacion() {}

Ubicacion::Ubicacion(char n, char s, char e, char o, string a[]) {
    norte = n;
    sur = s;
    este = e;
    oeste = o;
    for (int i = 0; i < 12; ++i) {
        anillos[i] = a[i];
    }
}

char Ubicacion::getNorte() {
    return norte;
}

char Ubicacion::getSur() {
    return sur;
}

char Ubicacion::getEste() {
    return este;
}

char Ubicacion::getOeste() {
    return oeste;
}

string* Ubicacion::getAnillos() {
    return anillos;
}

void Ubicacion::guardarArchivo(ofstream& fsalida) {
    fsalida.write(reinterpret_cast<const char*>(&norte), sizeof(norte));
    fsalida.write(reinterpret_cast<const char*>(&sur), sizeof(sur));
    fsalida.write(reinterpret_cast<const char*>(&este), sizeof(este));
    fsalida.write(reinterpret_cast<const char*>(&oeste), sizeof(oeste));
    for (int i = 0; i < 12; ++i) {
        int size = anillos[i].size();
        fsalida.write(reinterpret_cast<const char*>(&size), sizeof(size));
        fsalida.write(anillos[i].c_str(), size);
    }
}

bool Ubicacion::leerArchivo(ifstream& fentrada) {
    fentrada.read(reinterpret_cast<char*>(&norte), sizeof(norte));
    fentrada.read(reinterpret_cast<char*>(&sur), sizeof(sur));
    fentrada.read(reinterpret_cast<char*>(&este), sizeof(este));
    fentrada.read(reinterpret_cast<char*>(&oeste), sizeof(oeste));
    for (int i = 0; i < 12; ++i) {
        int size;
        fentrada.read(reinterpret_cast<char*>(&size), sizeof(size));
        char* buffer = new char[size + 1];
        fentrada.read(buffer, size);
        buffer[size] = '\0';
        anillos[i] = string(buffer);
        delete[] buffer;
    }
    return true;
}

bool Ubicacion::eliminar(const string& nombreArchivo) {
    if (remove(nombreArchivo.c_str()) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Ubicacion::modificar(const string& nombreArchivo, int nroReg, const Ubicacion& nuevaZona) {
    fstream archivo(nombreArchivo, ios::in | ios::out | ios::binary);
    if (!archivo.is_open()) {
        return false; // No se pudo abrir el archivo
    }

    // Calcular la posición del registro a modificar
    int pos = nroReg * getTamBytesRegistro();

    // Ir a la posición del registro
    archivo.seekp(pos);

    // Escribir la nueva zona en el archivo
    nuevaZona.guardarArchivo(archivo);

    archivo.close();
    return true;
}

bool Ubicacion::buscar(const string& nombreArchivo, int nroReg, Ubicacion& zonaEncontrada) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        return false; // No se pudo abrir el archivo
    }

    // Calcular la posición del registro a buscar
    int pos = nroReg * getTamBytesRegistro();

    // Ir a la posición del registro
    archivo.seekg(pos);

    // Leer la zona desde el archivo
    zonaEncontrada.leerArchivo(archivo);

    archivo.close();
    return true;
}

int Ubicacion::getTamBytesRegistro() {
    int tamRegistro = sizeof(norte) + sizeof(sur) + sizeof(este) + sizeof(oeste);
    for (int i = 0; i < 12; ++i) {
        tamRegistro += sizeof(int); // tamaño de la cadena de anillos
        tamRegistro += anillos[i].size();
    }
    return tamRegistro;
}
