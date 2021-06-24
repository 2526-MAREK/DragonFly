#include "Prostopadloscian.hh"

/*!
 * \file 
 * \brief Definicje metod i funkcji pomocniczych  klasy Prostopadloscian
 *
 *  Plik zawiera definicje metod i funkcji pomocniczych  klasy Prostopadloscian.
 */

/*!
* Konstruktor Domyślny klasy Prostopadloscian.
*/
/*Prostopadloscian::Prostopadloscian() : BrylaGeometryczna(), Polozenie()
{
  KatOrientacji_stopnie =0;
}*/
/*! 
*  Konstruktor parametryczny z wartościami domyślnymi klasy Prostopadloscian
*/
Prostopadloscian::Prostopadloscian(const std::string & s1, const std::string & s2,
                const Wektor3D & SkalaBrylaTym, const Wektor3D & PolozeniePrTym, double KatPocz) : BrylaGeometryczna(s1,s2,SkalaBrylaTym),
                Polozenie(PolozeniePrTym), KatOrientacji_stopnie(KatPocz)
{} 

/*!
* Dla przypadku, gdy prostopadloscian modeluje rotor drona, to ta transformacja realizuje przejście 
* od współrzędnych z układu lokalnego bryły do układu lokalnego drona
* 
* \param[in] Wierz - stała referencja do obiektu klasy Wektor3D, który zawiera informacje 
* o 3 współrzędnych: x, y i z - Wierzchołka transformowanego.
* 
* \return Zwraca przetransformowany Wierzchołek z układu lokalnego bryły do układu lokalnego drona.
*/
Wektor3D Prostopadloscian::TransfDoUklWspRodzica(const Wektor3D& Wierz) const
{
    Wektor3D Wktr3DTransakcji = Wierz + Polozenie;
    return Wktr3DTransakcji;
}


