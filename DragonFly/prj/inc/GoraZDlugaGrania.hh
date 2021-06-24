#ifndef GORAZDLUGAGRANIA_HH
#define GORAZDLUGAGRANIA_HH

#include <iostream>
#include "BrylaGeometryczna.hh"

//class Scena;

/*!
 * \file 
 * \brief Definicja klasy GoraZDlugaGrania 
 *
 *  Plik zawiera definicję klasy GoraZDlugaGrania, która modeluje Gore Z Dluga Grania jako element powierzchni.
 *  Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometryczna.
 */

/*!
 * \brief Klasa modeluje pojęcie Gory z  Dluga Grania
 * 
 * Klasa modeluje pojęcie Gory Z Dluga Grania jako element powierzchni. Gora Z Dluga Grania powstaje
 * poprzez deformacje prostopadloscianu. Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometryczna.  Jej atrybutami są: 
 * Polozenie, które określa położenie Bryły w trójwymiarze.
 */ 
class GoraZDlugaGrania : public BrylaGeometryczna
{
private:
/*! 
 * \brief Określa położenie Gory Z Dluga Grania
 * 
 * Pole zawiera współrzędne trójwymiarowe położenia Gory Z Dluga Grania. 
 * 
 */
    Wektor3D Polozenie;
public:
/*!
  * \brief Konstruktor parametryczny klasy GoraZDlugaGrania z wartościami domyślnymi
  */
GoraZDlugaGrania(const std::string & s1 = "brak", const std::string & s2 = "brak",
                const Wektor3D & SkalaBrylaTym ={0,0,0}, const Wektor3D & PolozenieTym = {0,0,0});  
/*!
 * \brief Tworzy bryłę reprezentującą Górę z Długą Grania.
 */                  
virtual bool Tworz()const override; 
/*!
 * \brief Usuwa bryłę reprezentującą Górę z Długą Grania.
 */                  
virtual bool Usun()const override; 
/*!
* \brief Tansformuje Polozenie o zadany Wektor
*/
  Wektor3D TransformujPolozenie(const Wektor3D& Wierz) const;      
  /*!
* \brief Metoda pozwala dowiedziec się z jaka bryla pracujemy
*
* \return Zwraca Stały wskaźnik na char wskazujący na nazwe bryły
*/          
  virtual const char* NazwaPrzeszkody() const override {return "Gora z dluga grania";}
  /*!
* \brief Metoda pozwalająca na dostęp do położenia bryły
* 
* \return Zwraca Polozenie bryły 
*/
  virtual const Wektor3D& WezPolozeniePrzeszkody() const override {return Polozenie;}
  virtual bool CzyZajete(const Dron& Dn) override;
  virtual double ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const override;
};

#endif
