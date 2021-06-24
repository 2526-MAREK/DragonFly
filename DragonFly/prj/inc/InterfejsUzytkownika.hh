#ifndef INTERFEJS_UZYTKOWNIKA_HH
#define INTERFEJS_UZYTKOWNIKA_HH

#include <memory.h>
#include "Scena.hh"
//#include "Dron.hh"

class Dron;
class Scena;

/*!
 * \file 
 * \brief Definicja klasy InterfejstUzytkownika
 *
 *  Plik zawiera definicję klasy InterfejsUzytkownika, która modeluje pojęcie Interfejsu Uzytkownika do obslugi drona 
 */

/*!
* \brief Klasa modeluje pojęcie Interfejsu Użytkownika
*/
class InterfejsUzytkownika
{
private:
    double DlugoscLotuPionowego; //Domyślna wartość 
    double KierunekLotu_Stopnie;
    double DlugoscLotuPoziomego;
    Wektor3D WyznaczonaStrefaDzialania;
public:
    InterfejsUzytkownika() : WyznaczonaStrefaDzialania() {DlugoscLotuPionowego = 0;  KierunekLotu_Stopnie = 0 ; DlugoscLotuPoziomego=0; }
    inline void UstawStrefeDzialaniaDrona(const Wektor3D &StrefaDzialania) {WyznaczonaStrefaDzialania = StrefaDzialania;}
    inline double WezDlugoscLotuPionowego() const {return DlugoscLotuPionowego;}
    inline double WezKierunekLotu_Stopnie() const {return KierunekLotu_Stopnie; }
    inline double WezDlugoscLotuPoziomego() const {return DlugoscLotuPoziomego;}
    inline void ZmienDlugoscLotuPoziomego(double NowaDlugoscLotuPoziomego) {DlugoscLotuPoziomego = NowaDlugoscLotuPoziomego;}
    inline double WezWyznaczonaStrefaDzialania(int Ind) const {return WyznaczonaStrefaDzialania[Ind];};
    inline Wektor3D WezWyznaczonaStrefaDzialania() const {return WyznaczonaStrefaDzialania;};
    void CzyszczenieStrumieniaWejsciowego(std::istream &StrmWe) const;
    inline void KomunikatOBledzieTYPint() const {  std::cerr<<"Blad formatu wprowadzanej liczby, program tutaj"
" oczekuje tylko liczb calkowitych, mozesz powtorzyc wprowadzanie:"<<std::endl;}      
    inline void KomunikatOBledzieTYPchar() const {  std::cerr<<"Blad formatu wprowadzanej liczby, program tutaj"
" oczekuje tylko znaków, mozesz powtorzyc wprowadzanie:"<<std::endl;}   
    int Wczytaj() const;
    void WczytajSKALE(Wektor3D& SkalaElementow) const;
    void WczytajWSP(Wektor3D& WspolrzedneElementu) const;
    void WyswietlMenu();
    int WyborAktywnegoDrona(Scena& Sc);
    int ZadajParametryPrzelotu(Scena &Sc, PzG::LaczeDoGNUPlota& Lacze);
    int Menu(Scena &Sc);
    int PrzelotDrona(Dron &Dron, PzG::LaczeDoGNUPlota& Lacze);
    void WyswietlPolozenieAktywnegoDrona(const Scena &Sc);
    bool ZadajPytanieCzyTrasaPrzelotuJestOdpowiednia() const;
    int DodajElementPowierzchni(Scena& Sc) const;
    int UsunElementPowierzchni(Scena& Sc) const;
    void WyswietlRodzajePowierzchni() const;
    void WyswietlWszystkieAktywneElementyNaPowierzchni(Scena &Sc)const;
};

#endif