/**
 * \file allapotgep.h
 *
 * Ebben a fájlban találja az Allapotgep osztály kezdeti definícióját és két segédfüggvényt.
 *
 * A fájlt tetszés szerint módosíthatja, azzal a megkötéssel, hogy
 * nem hozhat létre globális függvényt és nem változtathatja az Allapotgep osztály
 * publikus interfészét.
 *
 * Új osztályokat, típusokat felvehet.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef ALLAPOTGEP_H
#define ALLAPOTGEP_H

#include <locale>
#include <iostream>
#include <exception>
#include <cstring>

#include "memtrace.h"

/**
 * Bázisok
 */
enum Bazis {
    Adenin, Citozin, Guanin, Timin
};

class Matrix{
    int sz;
    int m;
    int* tomb;
public:
    Matrix(int szel = 0, int mag = 0);

    Matrix& operator=(Matrix const& other);

    int& operator()(int i, int j);

    int const& operator()(int i, int j) const;

    ~Matrix();
};

class Allapot{
    bool x;
    char* state;
public:
    void setAllapot(char t, char* allapot);

    char* getAllapot();

    bool getBool();

    ~Allapot();

};

/**
 * Állapotgép publikus interfésze.
 * A privát részt szabadon változtathatja, de a publikus részt ne változtassa, ne bővítse!
 */
class Allapotgep {
    int alap;
    int allapotszam;
    Allapot* current = nullptr;
    Matrix konfig;
public:
    /**
     * Konfig fájl beolvasása. Ha a fájl nem létezik/nem lehet megnyitni eldobja a NEPTUN-kódot.
     * Újra felépíti az állapotgépet, a korábbit törli ha volt. Kezdő állapotba áll.
     * @param  fajlnév - fájl neve
     * @return -
     * @exception fájl megnyitási hiba esetén NEPTUN_KÓD
    */
    void konfigural(const char* fajlnev);

    /** Visszaadja melyik állapot aktív.
     * @return pointer az aktív állapot nevére
     */
    const char* aktualisallapot();

    /**
     * Elfogadó állapotban van-e az állapotgép.
     * @return true, ha elfogadó állapotban van
     */
    bool elfogad();

    /**
     * Az aktuális állapotnak és inputnak megfelelő következő állapotba léptet.
     * @param b - beérkező bázis, mint input
     */
    void atmenet(Bazis b);

    /**
     * Feldolgozza a paraméterként kapott bázissorozatot.
     * Visszaadja, hogy elfogadó állapotba került-e. (Nem áll vissza kezdő állapotba.)
     * @param b - input sorozatra mutató pointer
     * @param n - a sorozat hossza
     * @return tru, ha elfogadó állapotba került
    */
    bool feldolgoz(const Bazis *b, int n);

    /**
     * Kezdő állapotba visz.
     */
    void alaphelyzet();

    ~Allapotgep();
};

/**
 * Segédfüggvény, karakterből enummá konvertál.
 * @param  b - bázis 1 betűs jele
 * @return Bazis enum kontans
 */
inline Bazis cast(char b) {
    std::locale loc;
    char k = std::tolower(b, loc);
    Bazis ret;
    switch(k) {
        case 'a': ret = Adenin; break;
        case 'c': ret = Citozin; break;
        case 'g': ret = Guanin; break;
        case 't': ret = Timin; break;
        default: throw "Format!!"; break;
    }
    return ret;
}

/**
 * Segédfüggvény, Bazis konstansból karakterré konvertál.
 * @param b - bazis enum konstansa
 * @param upper - nagybetűs legyen-e
 * @return bázis 1 betűs jele
 */
inline char cast(Bazis b, bool upper = true) {
    char ret = '0';
    switch (b)
    {
        case Adenin: ret = 'a'; break;
        case Citozin: ret = 'c'; break;
        case Guanin: ret = 'g'; break;
        case Timin: ret = 't'; break;
        default: throw "Format!!"; break;
    }
    if(upper) {
        std::locale loc;
        ret = std::toupper(ret, loc);
    }
    return ret;
}

#endif
