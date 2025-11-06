#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int UKURAN = 10;

void cetakGaris(char karakter = '=', int lebar = 60);
void tampilkanMatriks(double matrix[UKURAN][UKURAN], string label);
void tampilkanVektor(double arr[UKURAN], string label);
void hitungDekomposisiLU(double M_A[UKURAN][UKURAN], double M_L[UKURAN][UKURAN], double M_U[UKURAN][UKURAN]);
void substitusiMaju(double M_L[UKURAN][UKURAN], double v_b[UKURAN], double v_y[UKURAN]);
void substitusiMundur(double M_U[UKURAN][UKURAN], double v_y[UKURAN], double v_x[UKURAN]);

int main() {
    system("cls");

    cetakGaris();
    cout << "      PROGRAM PENYELESAIAN SISTEM PERSAMAAN LINEAR\n";
    cout << "                 METODE FAKTORISASI LU\n";
    cetakGaris();

    double matriks_A[UKURAN][UKURAN], matriks_L[UKURAN][UKURAN], matriks_U[UKURAN][UKURAN];
    double vektor_b[UKURAN], vektor_y[UKURAN], solusi_x[UKURAN];
    double v; 

    cout << "\nMasukkan nilai v untuk vektor b: ";
    cin >> v;

    // b = [1, 0, 0, 0, v, 0, 0, 0, 0, -1]^T
    double temp_b[UKURAN] = {1, 0, 0, 0, v, 0, 0, 0, 0, -1};
    for (int i = 0; i < UKURAN; i++) {
        vektor_b[i] = temp_b[i];
    }

    // Generate matriks A secara acak
    for (int baris = 0; baris < UKURAN; baris++) {
        for (int kolom = 0; kolom < UKURAN; kolom++) {
            matriks_A[baris][kolom] = rand() % 10;
        }
    }

    tampilkanMatriks(matriks_A, "Matriks A");
    tampilkanVektor(vektor_b, "Vektor b");

    cout << "\nProses faktorisasi LU\n";
    hitungDekomposisiLU(matriks_A, matriks_L, matriks_U);

    tampilkanMatriks(matriks_L, "Matriks L");
    tampilkanMatriks(matriks_U, "Matriks U");

    cout << "\nMenyelesaikan Ly = b\n";
    substitusiMaju(matriks_L, vektor_b, vektor_y);
    tampilkanVektor(vektor_y, "Vektor y");

    cout << "\nMenyelesaikan Ux = y\n";
    substitusiMundur(matriks_U, vektor_y, solusi_x);

    cetakGaris('=', 30);
    cout << "\n         HASIL AKHIR\n";
    cetakGaris('=', 30);
    tampilkanVektor(solusi_x, "Solusi x");

    return 0;
}

void cetakGaris(char karakter, int lebar) {
    for (int idx = 0; idx < lebar; idx++)
        cout << karakter;
    cout << endl;
}

void tampilkanMatriks(double matrix[UKURAN][UKURAN], string label) {
    cout << "\n" << label << ":\n";
    cetakGaris('-', 93);
    for (int baris = 0; baris < UKURAN; baris++) {
        cout << "| ";
        for (int kolom = 0; kolom < UKURAN; kolom++) {
            cout << setw(8) << fixed << setprecision(2) << matrix[baris][kolom] << " ";
        }
        cout << "|\n";
    }
    cetakGaris('-', 93);
}

void tampilkanVektor(double arr[UKURAN], string label) {
    cout << "\n" << label << ":\n";
    cetakGaris('-', 8);
    for (int idx = 0; idx < UKURAN; idx++) {
        cout << "|"
             << setw(6) << fixed << setprecision(2) << arr[idx]
             << "|\n";
    }
    cetakGaris('-', 8);
}

void hitungDekomposisiLU(double M_A[UKURAN][UKURAN], double M_L[UKURAN][UKURAN], double M_U[UKURAN][UKURAN]) {
    for (int i = 0; i < UKURAN; i++) {
        for (int j = 0; j < UKURAN; j++) {
            M_L[i][j] = 0.0;
            M_U[i][j] = 0.0;
        }
        M_L[i][i] = 1.0;
    }

    for (int i = 0; i < UKURAN; i++) {
        for (int j = i; j < UKURAN; j++) {
            double total = 0.0;
            for (int p = 0; p < i; p++) {
                total += M_L[i][p] * M_U[p][j];
            }
            M_U[i][j] = M_A[i][j] - total;
        }

        for (int j = i + 1; j < UKURAN; j++) {
            double total = 0.0;
            for (int p = 0; p < i; p++) {
                total += M_L[j][p] * M_U[p][i];
            }
            if (M_U[i][i] != 0.0) {
                M_L[j][i] = (M_A[j][i] - total) / M_U[i][i];
            }
        }
    }
}

void substitusiMaju(double M_L[UKURAN][UKURAN], double v_b[UKURAN], double v_y[UKURAN]) {
    for (int i = 0; i < UKURAN; i++) {
        double total = 0.0;
        for (int j = 0; j < i; j++) {
            total += M_L[i][j] * v_y[j];
        }
        v_y[i] = v_b[i] - total;
    }
}

void substitusiMundur(double M_U[UKURAN][UKURAN], double v_y[UKURAN], double v_x[UKURAN]) {
    for (int i = UKURAN - 1; i >= 0; i--) {
        double total = 0.0;
        for (int j = i + 1; j < UKURAN; j++) {
            total += M_U[i][j] * v_x[j];
        }
        if (M_U[i][i] != 0.0)
            v_x[i] = (v_y[i] - total) / M_U[i][i];
        else
            v_x[i] = 0.0;
    }
}

