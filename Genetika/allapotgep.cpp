/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>

#include "allapotgep.h"
#include "memtrace.h"

Matrix::Matrix(int szel, int mag){
    sz = szel * 4;
    m = mag;
    tomb = new int [sz * m];
    for (int i = 0; i < sz * m; i++){
        tomb[i] = 0;
    }
}

Matrix& Matrix::operator=(Matrix const& other){
    if (this != &other){
        delete[] tomb;

        sz = other.sz;
        m = other.m;
        tomb = new int [sz * m];
        for (int i = 0; i < sz * m; i++){
            tomb[i] = other.tomb[i];
        }
    }
    return *this;
}

int& Matrix::operator()(int i, int j){
    return tomb[i * sz + j];
}

int const& Matrix::operator()(int i, int j) const{
    return tomb[i * sz + j];
}

Matrix::~Matrix(){
    delete[] tomb;
}

void Allapot::setAllapot(char t, char* allapot){
    if (t == 'I')
        x = true;
    else
        x = false;
    state = new char [21];
    strcpy(state,allapot);
}

char* Allapot::getAllapot(){ return state; }

bool Allapot::getBool(){ return x; }

Allapot::~Allapot(){
    delete[] state;
}

void Allapotgep::konfigural(const char* fajlnev){
    if (current != nullptr){
        delete[] current;
    }
    std::ifstream file(fajlnev);
    if (!file){
        throw "X079FB";
    }

    char temp1;
    char temp2[21];
    char temp3[5];

    file >> alap;
    current = new Allapot [alap];
    for (int i = 0; i < alap; i++){
        file >> temp1;
        file >> temp2;
        current[i].setAllapot(temp1, temp2);
    }
    Matrix a(alap, alap);
    konfig = a;
    allapotszam = 0;

    for (int i = 0; i < alap; i++){
        for (int j = 0; j < 4*alap; j+=4){
            bool ciklus = true;
            int f = 0;
            file >> temp3;
            while (ciklus){
                switch(temp3[f]){
                    case 'A': konfig(i,j) = konfig(i,j) + 1; f++; break;
                    case 'C': konfig(i,j+1) = konfig(i,j+1) + 2; f++; break;
                    case 'G': konfig(i,j+2) = konfig(i,j+2) + 3; f++; break;
                    case 'T': konfig(i,j+3) = konfig(i,j+3) + 4; f++; break;
                    default: ciklus = false; break;
                }
            }
        }
    }
    file.close();
}

const char* Allapotgep::aktualisallapot(){
    return current[allapotszam].getAllapot();
}

bool Allapotgep::elfogad(){
    return current[allapotszam].getBool();
}

void Allapotgep::atmenet(Bazis b){
    char bazis = cast(b);
    int bazisnum = 0;
    switch(bazis){
        case 'A': bazisnum += 0; break;
        case 'C': bazisnum += 1; break;
        case 'G': bazisnum += 2; break;
        case 'T': bazisnum += 3; break;
        default: break;
    }
    if (konfig(allapotszam, (allapotszam * 4) + bazisnum) == 0){
        int ertek = bazisnum;
        if ((allapotszam * 4) + ertek >= 4*alap){
            ertek = -(allapotszam * 4);
        }
        while ((bazisnum+1) != konfig(allapotszam, (allapotszam * 4) + ertek)){
            ertek++;
            if ((allapotszam * 4) + ertek >= 4*alap){
                ertek = -(allapotszam * 4);
            }
        }
        allapotszam += (ertek-bazisnum) / 4;
    }
}

bool Allapotgep::feldolgoz(const Bazis *b, int n){
    for (int i = 0; i < n; i++){
        Allapotgep::atmenet(b[i]);
    }
    return Allapotgep::elfogad();
}

void Allapotgep::alaphelyzet(){
    allapotszam = 0;
}

Allapotgep::~Allapotgep(){
    delete[] current;
}