#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include<vector>
#include <unistd.h>
#include <memory.h>
#include "Macierz.hh"
#include "Macierz3x3.hh"
#include "Wektor2D.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

#define ILOSC_ROTOROW 4
#define ILOSC_WIERZ_LINII_TWORZACEJ 4
#define  SKALA_ROTORA  8,8,2  
#define  SKALA_KORPUSU  10,8,4
#define PLIK_WZORCOWEGO_SZESCIANU       "bryly_wzorcowe/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_KORPUSU_DRONA1             "dat/korpus_drana1.dat"
#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"
#define PLIK_WLASCIWY__DRON1_KORPUS  "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "dat/PlikWlasciwy_Dron1_Rotor4.dat"
#define PLIK_WLASCIWY__DRON2_KORPUS  "dat/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1  "dat/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2  "dat/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3  "dat/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4  "dat/PlikWlasciwy_Dron2_Rotor4.dat"
#define TRANSLACJA_ROTOR_LEWY_PRZEDNI   5,4,5
#define TRANSLACJA_ROTOR_PRAWY_PRZEDNI  5,-4,5
#define TRANSLACJA_ROTOR_LEWY_TYLNY    -5,4,5
#define TRANSLACJA_ROTOR_PRAWY_TYLNY   -5,-4,5  
#define SKOK_OBROTU_ROTOROW_stopnie  10
 #define SKOK_OBROTU_ROTOROW_stopnie  10

class InterfejsUzytkownika;
/*!
 * \file 
 * \brief Definicja klasy Dron
 *
 *  Plik zawiera definicję klasy Dron, która modeluje pojęcie drona w 3 wymiarze.
 */

/*!
 * \brief Klasa modeluje pojęcie Drona w 3 wymiarach
 * 
 * Klasa modeluje pojęcie Drona w 3 wymiarach.  Jej atrybutami są: 
 * Pole położenie, które określa położenie Drona w trójwymiarowym układzie wsporzednych.
 * Pole KatOrientacji które określa kąt o jaki ma sie obrócić Dron, żeby polecieć w danym kierunku.
 * Pole KorupsDrona, które definiuje Korpus jako prostopadloscian
 * Pole RotorDrona , które jest tablica statyczna a jej rozmiar jest zależny od tego ile chcemy 
 * w dronie Rotorów. To pole definiuje RotorDrona jako Graniastoslup
 */ 
class Dron : public ElementSceny
{
private:
/*! \brief Określa czy dany Dron jest aktywny
*
* Pole określa czy dany dron jest aktywny, Dron jest aktywnym Dronem jeśli to pole przymuje wartość true, a jeśli jest dronem nieaktywnym przyjumuje wartość false.
*
**/
  bool DronAktywny;
/*! \brief Określa Indeks Drona
*
* Pole określa Indeks danego drona, pozwala na rozróznianie Dronów w programie
*
*/  
  double IndeksDrona;    
/*! \brief Określa położenie Drona
* Pole określa położenie Drona, zawiera współrzędne trójwymiarowe położenia Drona.
*/
    Wektor3D Polozenie;
  /*!
 * \brief Określa kąt Orientacji położenia Drona
 * 
 * Pole klasy zawiera kąt w stopniach, który pozwala określić w jakim kierunku ma się ustawić Dron.
 * 
 */
    double KatOrientacji_stopnie;
  /*!
 * \brief Definiuje Korpus Drona jako Prostopadłościan
 * 
 * Pole klasy definiuje Korpus Drona jako Prostopadłościan.
 * 
 */    
    Prostopadloscian KorpusDrona;
/*!
 * \brief Definiuje RotorDrona jako Graniastoslupy
 * 
 * Pole klasy definiuje RotorDrona jako Graniastoslupy. Jest tablica statyczna, której 
 * rozmiar jest zależny od tego ile Rotorów ma posiadać Dron.
 * 
 */      
    Graniastoslup6 RotorDrona[ILOSC_ROTOROW];
    /*!
* \brief Określa Dlugość pojedynczego kroku drona
*
* Pole klasy zawiera Dlugosc pojedynczego kroku drona, który określa jak daleko dron posunie się w jednym kroku
*/
    const static double DlugoscPojedynczegoKroku;
    /*!
    * \brief  Transformuje cały korpus.     
    */
    bool Oblicz_i_Zapisz_WspGlbKorpusu() const;
    /*!
    * \brief  Transformuje cały jeden Rotor.     
    */
    bool Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup6& Rotor) const;
/*!    
* \brief Pozwala na zmiane polozenia Drona
*/     
    inline void ZmienPolozenieDrona(const Wektor3D &NowePolozenie) {Polozenie = NowePolozenie;}
/*!    
* \brief Pozwala na dostep do KatOrientacji Drona
*/         
    inline double WezKatOrientacyjny_st() const {return KatOrientacji_stopnie;}
/*!    
* \brief Pozwala Przesunac Drona o zadany Wektor trójwymiarowy
*/         
    inline void PrzesunDrona_WekTrans(const Wektor3D &WktrTrans) {Polozenie = Polozenie+WktrTrans;}
protected:
/*!
* \brief Realizuje przejście od współrzędnych lokalnych drona do współrzędnych globalnych sceny 
*/
    Wektor3D TransfDoUklWspRodzica(const Wektor3D& Wierz) const;            
public:
/*!
* \brief Konstruktor domyślny klasy Dron
*/
Dron();
/*!
* \brief Konstruktor parametryczny klasy Dron
*/
    Dron(bool DronAktywnyTym, double IndeksDrona, const Wektor3D& Polozenietym, double KatOrientacji_tym,const Prostopadloscian &KorpusDronaTym, const Graniastoslup6 &Gr1,const Graniastoslup6 &Gr2,
const Graniastoslup6 &Gr3, const Graniastoslup6 &Gr4);
/*!
* \brief Pozwala sprawdzić czy dany Dron jest aktywny
*
* Metoda pozwala sprawdzić czy dany Dron jest aktywny.
*
* \retval true jeśli Dany dron jest aktywny
* \retval false jeśli Dany dron jest nieaktywny
*/
inline bool CzyTenDronJestAktywny() const {if(DronAktywny) {return true;}else return false;}
/*!
* \brief Pozwala Ustawić Danego Drona jako aktywnego
*
* Metoda pozwala Ustawić Danego Drona jako aktywnego. Aktywny czyli w tej chwili wykonuje operacje lotu.
*/
inline void WlaczAktywnoscDrona() {DronAktywny = true;}
/*!
* \brief Pozwala Ustawić Danego Drona jako Nieaktywnego
*
* Metoda pozwala Ustawić Danego Drona jako Nieaktywnego. Nieaktywny czyli w tej chwili nie wykonuje operacje lotu.
*/
inline void WylaczAktywnoscDrona() {DronAktywny = false;}
/*!
* \brief Pozwala na dostęp do Indesku Drona
*
* Metoda pozwala na dostęp do pola prywatnego klasy Dron: Do ineksu Drona
*
* \return zwraca idneks Drona
*/
inline double WezIndeksDrona() const {return IndeksDrona;}
/*!    
* \brief Ustawia dron w żądanej pozycji 
*/
    bool Oblicz_i_Zapisz_WspGlbDrona() const;
/*!    
* \brief Daje dostęp do Polozenie Drona
*/
    inline Wektor3D WezPolozenieDrona() const { return Polozenie;}
    const Prostopadloscian& WezKorpusDrona() const {return KorpusDrona;}
/*!    
* \brief Wykonuje Lot Drona
*/    
    bool WykonajLot(const Wektor3D &Kierunek_WekJednostkowy, double DlugoscLotu, PzG::LaczeDoGNUPlota& Lacze);
/*!    
* \brief Planuje Początkową trase Drona, zażądana przez użytkownika
*/        
    bool PlanujPoczatkowaSciezke(const InterfejsUzytkownika &IU, std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze);
/*!    
* \brief Ustawia odpowiednie parametry do Lotu Pionowego Drona
*/        
    bool WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota& Lacze);
/*!    
* \brief Wykonuje Zmianę orientacji Drona
*/        
    bool WykonajZmianeOrientacji(double KatOrientacjiDrona_stopnie, PzG::LaczeDoGNUPlota& Lacze);
/*!    
* \brief Ustawia odpowiednie parametry do Lotu Poziomego Drona
*/         
    bool WykonajPoziomyLot(double DlugoscLotu,double KatOrientacjiDrona_stopnie, PzG::LaczeDoGNUPlota& Lacze);
/*!    
* \brief Dokonuje obrotu rotorow drona
*/         
    void ObrotRotorow();
/*!
* \brief Oblicza i Dodaje punkty Sciezki do kontenera sekwencyjnego vector
*/    
    void ObliczIDodajPunktySciezki(std::vector<Wektor3D>& PunktySciezki, Wektor3D &PunktSciezki, const InterfejsUzytkownika &IU);
    virtual bool CzyZajete(const Dron& Dn) override;
/*!
* \brief Metoda pozwala dowiedziec się z jaka bryla pracujemy
*
* \return Zwraca Stały wskaźnik na char wskazujący na nazwe bryły
*/                  
virtual const char* NazwaPrzeszkody() const {return "Dron";}    
virtual double ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const override;
bool ZapiszDoPlikuTraseLotu(std::vector<Wektor3D>& PunktySciezki);
bool WydluzTraseLotu(const Dron& Dn,InterfejsUzytkownika &IU, std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze, double DlugoscWydluzeniaTrasy);
/*!    
* \brief Destruktor klasy Dron
*/        
    ~Dron() {}
};

/*!
 *  \brief Funkcja pomocnicza - Dokonuje obrotu wokół osi OZ.
 */
void ObrocWzgledemOsiOZ(double  KatObrotu_st, Wektor3D &Wktr3D );
/*!
 * \brief Funkcja pomocnicza - Przelicza wartość kąta ze stopni na radiany.
 */
double StopnieNaRadiany(double Kat_st);
#endif