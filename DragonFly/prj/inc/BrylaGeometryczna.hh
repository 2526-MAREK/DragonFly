#ifndef BRYLAGEOMETRYCZNA_HH
#define BRYLAGEOMETRYCZNA_HH

#include <iostream>
#include <cmath>
#include "ElementSceny.hh"
#include "Wektor.hh"
#include "Wektor3D.hh"
#include "Wektor2D.hh"

//class Scena;
/*!
 * \file 
 * \brief Definicja klasy BrylaGeometryczna
 *
 *  Plik zawiera definicję klasy BrylaGeometryczna, która modeluje ogólne pojęcie BrylyGeometrycznej
 */

/*!
 * \brief Klasa modeluje pojęcie BrylyGeometrycznej
 * 
 * Klasa modeluje pojęcie BrylyGeometrycznej. Jest ona wykorzystywana jako klasa bazowa dla 
 * klas typu Graniastoslup i Prostopadloscian. Jej atrybutami są: pola zawierajace NazwePliku z Bryla wzorcowa
 * i Nazwe Pliku bryly Finalnej i ostatnim atrybutem tej klasy jest pole zawierające skale.
 * 
 */
class BrylaGeometryczna : public ElementSceny
{
private:
/*!
*  \brief Przechowuje Nazwe Pliku Bryly Wzorcowej
* 
* Pole przechowuje Nazwe Pliku Bryly wzorcowej w szablonie klasy string 
*/
    std::string NazwaPlikuBrylaWzorcowa;
/*!
*  \brief Przechowuje Nazwe Pliku Bryly Finalnej
* 
* Pole przechowuje Nazwe Pliku Bryly Finalnej w szablonie klasy string 
*/
    std::string NazwaPlikuBrylaFinalna;
/*!
*  \brief Zawiera współrzedne skali
* 
* Pole zawiera współrzedne skali.
*/
    Wektor3D Skala;
public:
/*!
* \brief Konstruktor Domyślny klasy BrylaGeometryczna
*/
//BrylaGeometryczna();
/*!
* \brief Konstruktor parametryczny z wartościami domyślnymi klasy BrylaGeometryczna
*/
BrylaGeometryczna(const std::string & s1 = "brak", const std::string & s2 = "brak",
                const Wektor3D & SkalaTym ={0,0,0});
/*!
* \brief Odpowiednio skladuje zadany Wierzchołek
*/                
    Wektor3D Skaluj(const Wektor3D& Wierz) const;
/*!
* \brief Pozwala na zmiane Skali BrylyGeometrycznej
*/     
    void ZmienSkale(const Wektor3D& Wktr) {Skala = Wktr;}
    const Wektor3D& WezSkale()const {return Skala;}
/*!
* \brief Pozwala na dostęp do NazwyPlikuBrylyWzorcowej
*/     
    inline const std::string& WezNazwePliku_BrylaWzorcowa() const {return NazwaPlikuBrylaWzorcowa;}
/*!
* \brief Pozwala na dostęp do NazwyPlikuBrylyFinalnej
*/     
    inline const std::string& WezNazwePliku_BrylaFinalna() const {return NazwaPlikuBrylaFinalna;}  
 /*!
* \brief Metoda bezuzyteczna w klasie Bryla Geometryczna
*/    
virtual bool Tworz()const;                     
/*!
* \brief Metoda bezuzyteczna w klasie Bryla Geometryczna
*/    
virtual bool Usun()const;   
/*!
* \brief Metoda pozwala dowiedziec się z jaka bryla pracujemy
*
* \return Zwraca Stały wskaźnik na char wskazujący na nazwe bryły
*/                  
virtual const char* NazwaPrzeszkody() const {return "Bryla geometryczna";}
/*!
* \brief Metoda pozwalająca na dostęp do położenia bryły
* 
* \return Zwraca Polozenie bryły 
*/
virtual const Wektor3D& WezPolozeniePrzeszkody() const {return Skala;}
virtual bool CzyZajete(const Dron& Dn) override;
virtual double ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const override;
/*!
* \brief wirtualny Destruktor klasy bryła geometryczna
*/    
    virtual ~BrylaGeometryczna() {}
};

/*! 
* \brief Funkcja pomocniczna, sprawdzająca czy udało się wczytac dane 
*/
bool NiePrawidlowoWczytano(const std::ifstream &StrmWej);
/*! 
* \brief Funkcja pomocniczna, sprawdzająca czy udało się zapisac dane 
*/
bool NiePrawidlowoZapisano(const std::ofstream &StrmWyj);
/*! 
* \brief Funkcja pomocniczna, sprawdzająca poprawność otwartego pliku wejściowego
*/
bool OtworzonoPlik(const std::ifstream &StrmWe, const std::string &NazwaPliku);
/*! 
* \brief Funkcja pomocniczna, sprawdzająca poprawność otwartego pliku wyjściowego
*/
bool OtworzonoPlik(const std::ofstream &StrmWy, const std::string &NazwaPliku);

#endif