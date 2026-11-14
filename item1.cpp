#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

class Estudiante {
private:
    string nombre;
    int anioNacimiento;
    double gpa;
    double presupuesto;

public:
    
    Estudiante(string nombre = "NN", int anioNacimiento = 0,
               double gpa = 0, double presupuesto = 0)
        : nombre(nombre), anioNacimiento(anioNacimiento),
          gpa(gpa), presupuesto(presupuesto) {}

    // Getters
    string getNombre() const { return nombre; }
    int getAnioNacimiento() const { return anioNacimiento; }
    double getGpa() const { return gpa; }
    double getPresupuesto() const { return presupuesto; }

    
    void setNombre(const string& n) { nombre = n; }
    void setAnioNacimiento(int a) { anioNacimiento = a; }
    void setGpa(double g) { gpa = g; }
    void setPresupuesto(double p) { presupuesto = p; }

    
    double indiceUniversidad() const {
        return abs(gpa - 3) * presupuesto;
    }

    void mostrar() const {
        cout << nombre
             << " | Anio: " << anioNacimiento
             << " | GPA: " << gpa
             << " | Presupuesto: " << presupuesto
             << " | Indice U: " << indiceUniversidad() << endl;
    }
};

class GestorEstudiantes {
private:
    vector<Estudiante> estudiantes;

public:
    bool estaVacio() const { return estudiantes.empty(); }
    int cantidad() const { return (int)estudiantes.size(); }

    
    void insertarAlFinal(const Estudiante& e) {
        estudiantes.push_back(e);
    }

    bool insertarEnIndice(int indice, const Estudiante& e) {
        if (indice < 0 || indice > cantidad()) return false;
        estudiantes.insert(estudiantes.begin() + indice, e);
        return true;
    }

    bool eliminarUltimo() {
        if (estudiantes.empty()) return false;
        estudiantes.pop_back();
        return true;
    }

    bool eliminarEnIndice(int indice) {
        if (estudiantes.empty()) return false;
        if (indice < 0 || indice >= cantidad()) return false;
        estudiantes.erase(estudiantes.begin() + indice);
        return true;
    }

    bool actualizar(int indice, const Estudiante& nuevo) {
        if (indice < 0 || indice >= cantidad()) return false;
        estudiantes[indice] = nuevo;
        return true;
    }
-
    void ordenarPorAnio() {
        stable_sort(estudiantes.begin(), estudiantes.end(),
            [](const Estudiante& a, const Estudiante& b) {
                return a.getAnioNacimiento() < b.getAnioNacimiento();
            });
    }
    void ordenarPorGpa() {
        stable_sort(estudiantes.begin(), estudiantes.end(),
            [](const Estudiante& a, const Estudiante& b) {
                return a.getGpa() < b.getGpa();
            });
    }
    void ordenarPorPresupuesto() {
        stable_sort(estudiantes.begin(), estudiantes.end(),
            [](const Estudiante& a, const Estudiante& b) {
                return a.getPresupuesto() < b.getPresupuesto();
            });
    }
    void ordenarPorIndice() {
        stable_sort(estudiantes.begin(), estudiantes.end(),
            [](const Estudiante& a, const Estudiante& b) {
                return a.indiceUniversidad() < b.indiceUniversidad();
            });
    }

    void imprimir() const {
        cout << "Estudiantes en el vector: " << cantidad() << endl;
        if (estudiantes.empty()) {
            cout << "  (vector vacio)" << endl;
            return;
        }
        for (int i = 0; i < cantidad(); i++) {
            cout << "  [" << i << "] ";
            estudiantes[i].mostrar();
        }
    }
};



string leerTexto(const string& msg) {
    string linea;
    cout << msg;
    getline(cin, linea);
    return linea;
}

int leerEntero(const string& msg) {
    while (true) {
        string linea;
        cout << msg;
        if (!getline(cin, linea)) return 0;
        try {
            size_t pos;
            int v = stoi(linea, &pos);
            if (pos == linea.size()) return v;
        } catch (...) {}
        cout << "Entrada invalida, intente de nuevo." << endl;
    }
}

double leerDecimal(const string& msg) {
    while (true) {
        string linea;
        cout << msg;
        if (!getline(cin, linea)) return 0;
        try {
            size_t pos;
            double v = stod(linea, &pos);
            if (pos == linea.size()) return v;
        } catch (...) {}
        cout << "Entrada invalida, intente de nuevo." << endl;
    }
}

Estudiante leerEstudiante() {
    string nombre = leerTexto("Nombre: ");
    int anio = leerEntero("Anio de nacimiento: ");
    double gpa = leerDecimal("GPA: ");
    double presupuesto = leerDecimal("Presupuesto: ");
    return Estudiante(nombre, anio, gpa, presupuesto);
}

// ---------- Opciones del menu ----------
void opcionInsertar(GestorEstudiantes& g) {
    cout << "\n1. Al final\n2. En un indice especifico\n";
    int donde = leerEntero("Opcion: ");
    int indice = 0;
    if (donde == 2) indice = leerEntero("Indice: ");
    else if (donde != 1) { cout << "Opcion invalida." << endl; return; }

    cout << "\n1. Por defecto (NN,0,0,0)\n2. Con datos\n";
    int modo = leerEntero("Opcion: ");
    Estudiante e;                       
    if (modo == 2) e = leerEstudiante();
    else if (modo != 1) { cout << "Opcion invalida." << endl; return; }

    if (donde == 1) {
        g.insertarAlFinal(e);
        cout << "Estudiante insertado al final." << endl;
    } else if (g.insertarEnIndice(indice, e)) {
        cout << "Estudiante insertado en el indice " << indice << "." << endl;
    } else {
        cout << "Indice fuera de rango. No se inserto." << endl;
    }
}

void opcionEliminar(GestorEstudiantes& g) {
    if (g.estaVacio()) {
        cout << "No se elimina: el vector esta vacio." << endl;
        return;
    }
    cout << "\n1. Eliminar el ultimo\n2. Eliminar por indice\n";
    int op = leerEntero("Opcion: ");
    if (op == 1) {
        g.eliminarUltimo();
        cout << "Ultimo estudiante eliminado." << endl;
    } else if (op == 2) {
        int indice = leerEntero("Indice: ");
        if (g.eliminarEnIndice(indice))
            cout << "Estudiante del indice " << indice << " eliminado." << endl;
        else
            cout << "Indice fuera de rango. No se elimino." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}

void opcionActualizar(GestorEstudiantes& g) {
    if (g.estaVacio()) {
        cout << "No hay estudiantes para actualizar." << endl;
        return;
    }
    int indice = leerEntero("Indice del estudiante a actualizar: ");
    if (indice < 0 || indice >= g.cantidad()) {
        cout << "Indice fuera de rango." << endl;
        return;
    }
    Estudiante nuevo = leerEstudiante();
    g.actualizar(indice, nuevo);
    cout << "Estudiante actualizado." << endl;
}

void opcionOrdenar(GestorEstudiantes& g) {
    cout << "\n1. Por anio de nacimiento\n2. Por GPA\n3. Por presupuesto"
         << "\n4. Por indice universidad\n";
    int op = leerEntero("Opcion: ");
    switch (op) {
        case 1: g.ordenarPorAnio();        break;
        case 2: g.ordenarPorGpa();         break;
        case 3: g.ordenarPorPresupuesto(); break;
        case 4: g.ordenarPorIndice();      break;
        default: cout << "Opcion invalida." << endl; return;
    }
    cout << "Lista ordenada de forma ascendente." << endl;
}

int main() {
    GestorEstudiantes estudiantes;      
    int opcion;
    do {
        cout << "\n===== MENU ESTUDIANTES =====\n"
             << "1. Insertar estudiante\n"
             << "2. Eliminar estudiante\n"
             << "3. Actualizar estudiante\n"
             << "4. Ordenar estudiantes\n"
             << "5. Imprimir estudiantes\n"
             << "0. Salir\n";
        opcion = leerEntero("Opcion: ");
        switch (opcion) {
            case 1: opcionInsertar(estudiantes);   break;
            case 2: opcionEliminar(estudiantes);   break;
            case 3: opcionActualizar(estudiantes); break;
            case 4: opcionOrdenar(estudiantes);    break;
            case 5: estudiantes.imprimir();        break;
            case 0: cout << "Fin del programa." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
    return 0;
}