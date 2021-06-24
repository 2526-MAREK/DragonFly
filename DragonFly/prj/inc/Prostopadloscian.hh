#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include<algorithm>
#include "BrylaGeometryczna.hh"

/*!
 * \file 
 * \brief Definicja klasy Prostopadloscian
 *
 *  Plik zawiera definicję klasy Prostopadloscian, która modeluje Prostopadlośćian w 3 wymiarach.
 *  Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometrzyczna.
 */

/*!
 * \brief Klasa modeluje pojęcie Prostopadłościanu w 3 wymiarach
 * 
 * Klasa modeluje pojęcie Prostopadłościanu w 3 wymiarach.  Jej atrybutami są: 
 * Pole położenie, które określa położenie prostopadloscianu w trójwymiarowym układzie wsporzednych.
 * Pole KatOrientacji które określa kąt o jaki ma sie obrócić prostopadloscian, żeby polecieć w danym kierunku.
 * 
 */ 
class Prostopadloscian : public BrylaGeometryczna
{
private:
/*! 
 * \brief Określa położenie prostopadłościanu
 * 
 * Pole zawiera współrzędne trójwymiarowe położenia prostopadłościanu. 
 * 
 */
  Wektor3D Polozenie;
  /*!
 * \brief Określa kąt Orientacji położenia prostopadłościanu
 * 
 * Pole klasy zawiera kąt w stopniach, który pozwala określić w jakim kierunku ma się ustawić prostopadlościan.
 * 
 */
  double KatOrientacji_stopnie;
public:
/*!
* \brief Konstruktor Domyślny klasy Prostopadloscian
*/
 // Prostopadloscian();
/*!
  * \brief Konstruktor parametryczny klasy Prostopadloscian z wartościami domyślnymi
  */
Prostopadloscian(const std::string & s1 = "brak", const std::string & s2 = "brak",
                const Wektor3D & SkalaBrylaTym ={0,0,0}, const Wektor3D & PolozeniePrTym = {0,0,0}, double KatPocz = 0.0);
/*! 
* \brief Pozwala na dostęp do składowej prywatnej: Polozenie
*/                  
Wektor3D WezPolozenie() const {return Polozenie;} 
/*! 
* \brief Pozwala na dostęp do składowej prywatnej: KatOrientacji_stopnie 
*/    
double WezKatOrientacji_stopnie() const {return KatOrientacji_stopnie;}   
/*! 
* \brief Pozwala dodać nowy kat orientacji prostopadloscianu
*/  
void DodajStopienOrientacjiKorpusu(double KatOrientacjiKorpusu_stopnie) {KatOrientacji_stopnie = KatOrientacjiKorpusu_stopnie;}                          
/*!
* \brief Realizuje przejście od współrzednych z układu lokalnego bryły do układu lokalnego drona.
*/
  Wektor3D TransfDoUklWspRodzica(const Wektor3D& Wierz) const;
  /*!
* \brief Destruktor klasy Prostopadloscian
*/
  ~Prostopadloscian() {}; 
};

#endif
