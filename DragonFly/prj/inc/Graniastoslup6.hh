#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include "BrylaGeometryczna.hh"

/*!
 * \file 
 * \brief Definicja klasy Graniastoslup6
 *
 *  Plik zawiera definicję klasy Graniastoslup6, która modeluje Graniastoslup w 3 wymiarach.
 *  Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometrzyczna.
 */

/*!
 * \brief Klasa modeluje pojęcie Graniastoslupa w 3 wymiarach
 * 
 * Klasa modeluje pojęcie Graniastoslupa w 3 wymiarach.  Jej atrybutami są: 
 * Pole położenie, które określa położenie Graniastoslupa w trójwymiarowym układzie wsporzednych.
 * Pole KatOrientacji które określa kąt o jaki ma sie obrócić Graniastoslup, żeby polecieć w danym kierunku.
 */
class Graniastoslup6 : public BrylaGeometryczna
{
private:
/*! 
 * \brief Określa położenie Graniastoslupa
 * 
 * Pole zawiera współrzędne trójwymiarowe położenia Graniastoslupa. 
 * 
 */
    Wektor3D Polozenie;
/*!
 * \brief Określa kąt Orientacji położenia Graniastoslupa
 * 
 * Pole klasy zawiera kąt w stopniach, który pozwala określić w jakim kierunku ma się ustawić
 *  Graniastoslup.
 * 
 */
    double KatOrientacji_stopnie;
public:
/*!
* \brief Konstruktor Domyślny klasy Graniastoslup6
*/
//Graniastoslup6();// : Polozenie() {KatOrientacji_stopnie = 0.0;}
/*!
* \brief Konstruktor parametryczny z wartościami domyślnymi klasy Graniastoslup6
*/
Graniastoslup6(const std::string & s1 = "brak", const std::string & s2 = "brak",
                const Wektor3D & SkalaBrylaTym ={0,0,0}, const Wektor3D & PolozenieGrTym = {0,0,0}, double KatPocz = 0.0); 
/*Graniastoslup6(const std::string & s1, const std::string & s2,
                const Wektor3D & SkalaBrylaTym, const Wektor3D & PolozenieGrTym, double KatPocz); */
/*! 
* \brief Pozwala na dostęp do składowej prywatnej: Polozenie
*/                
Wektor3D WezPolozenie() const {return Polozenie;}
/*! 
* \brief Pozwala Dodać nowe położenie graniastoslupa
*/                
void DodajPolozenieRotorow(const Wektor3D &Wktr3D){Polozenie = Wktr3D;}   
/*! 
* \brief Pozwala na dostęp do składowej prywatnej klasy: KatOreintacji_stopnie
*/  
double WezKatOrientacji_stopnie() const {return KatOrientacji_stopnie;}
/*! 
* \brief Pozwala dodać nowy kat orientacji graniastoslupa
*/  
void DodajStopienOrientacjiRotora(double KatOrientacjiRotora_stopnie) {KatOrientacji_stopnie = KatOrientacjiRotora_stopnie;}
/*! 
* \brief Pozwala dodać dana wartośc do Katu orietnacji graniastoslupa
*/  
void DodajStopienSkokuRotora(double KatSkokuRotora_stopnie) {KatOrientacji_stopnie += KatSkokuRotora_stopnie;}
/*! 
* \brief Pozwala odjąć dana wartośc od Katu orietnacji graniastoslupa
*/  
void OdejmijStopienSkokuRotora(double KatSkokuRotora_stopnie) {KatOrientacji_stopnie -= KatSkokuRotora_stopnie;}
/*!
* \brief Realizuje przejście od współrzednych z układu lokalnego bryły do układu lokalnego drona.
*/
    Wektor3D TransfDoUklWspRodzica(const Wektor3D& Wierz) const;      
/*!
* \brief Destruktor klasy Graniastoslup6
*/    
    ~Graniastoslup6() {}  
};

#endif