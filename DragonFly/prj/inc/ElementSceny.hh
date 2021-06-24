#ifndef ELEMENTSCENY_HH
#define ELEMENTSCENY_HH

#define ILOSC_WIERZ_PROSTOKATA 4
#define DODATKOWA_DLUGOSC 5
#include <iostream>
#include <valarray>
#include "Wektor.hh"
#include "Wektor3D.hh"
#include "Wektor2D.hh"

class Dron;

enum WierzcholkiProstokata {A, B , C, D};

class ElementSceny
{
private:
//double WierzcholkiProstokatowElemSceny2D[ILOSC_WIERZ_PROSTOKATA];
public:  
//void DodajWierzcholkiProstokatowElemSceny2D() {for(unsigned int Ind=0;Ind<ILOSC_WIERZ_PROSTOKATA;++Ind) WierzcholkiProstokatowElemSceny2D[Ind]}
virtual bool CzyZajete(const Dron& Dn);
/*!
* \brief Metoda pozwala dowiedziec się z jaka bryla pracujemy
*
* \return Zwraca Stały wskaźnik na char wskazujący na nazwe bryły
*/                  
inline virtual const char* NazwaPrzeszkody() const {return "Element Sceny";}
virtual double ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const;
double PrzeciecieDronaZOdcinkiemAD(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata, double PromienKolaDrona) const;
double PrzeciecieDronaZOdcinkiemBC(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata, double PromienKolaDrona) const;
double PrzeciecieDronaZOdcinkiemDC(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata, double PromienKolaDrona) const;
double PrzeciecieDronaZOdcinkiemAB(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata, double PromienKolaDrona) const;
virtual ~ElementSceny() {}
};

#endif