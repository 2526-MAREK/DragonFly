#ifndef GORAZOSTRYMSZCZYTEM_HH
#define GORAZOSTRYMSZCZYTEM_HH

#include <iostream>
#include "BrylaGeometryczna.hh"

class Scena;
/*!
 * \file 
 * \brief Definicja klasy GoraZOstrymSzczytem
 *
 *  Plik zawiera definicję klasy GoraZOstrymSzczytem, która modeluje Gore Z ostrym Szczytem jako element powierzchni.
 *  Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometryczna.
 */

/*!
 * \brief Klasa modeluje pojęcie Gory z  Ostrym Szczytem
 * 
 * Klasa modeluje pojęcie Gory Z Ostrym Szczytem jako element powierzchni. Gora z OStrym szczytem powstaje
 * poprzez deformacje prostopadloscianu. Ta klasa jest klasą pochodną i jest ona specjalizacją klasy BrylaGeometryczna.  Jej atrybutami są: 
 * Polozenie, które określa położenie Bryły w trójwymiarze.
 * 
 */ 
class GoraZOstrymSzczytem : public BrylaGeometryczna
{
private:
/*! 
 * \brief Określa położenie Gory Z Ostrym Szczytem
 * 
 * Pole zawiera współrzędne trójwymiarowe położenia Gory Z OStrym Szczytem. 
 * 
 */
    Wektor3D Polozenie;
public:    
/*!
  * \brief Konstruktor parametryczny klasy GoraZOstrymSzczytem z wartościami domyślnymi
  */
GoraZOstrymSzczytem(const std::string & s1 = "brak", const std::string & s2 = "brak",
                const Wektor3D & SkalaBrylaTym ={0,0,0}, const Wektor3D & PolozenieTym = {0,0,0});    
/*!
 * \brief Tworzy bryłę reprezentującą Górę z Ostrym Szczytem.
 */                
virtual bool Tworz()const override ;   
/*!
 * \brief Usuwa bryłę reprezentującą Górę z Długą Grania.
 */                  
virtual bool Usun()const override; 
/*!
* \brief Tansformuje Polozenie o zadany Wektor
*/
  Wektor3D TransformujWierzcholek(const Wektor3D& Wierz) const;          
  /*!
* \brief Metoda pozwala dowiedziec się z jaka bryla pracujemy
*
* \return Zwraca Stały wskaźnik na char wskazujący na nazwe bryły
*/                                  
  virtual const char* NazwaPrzeszkody() const override {return "Gora z ostrym szczytem";}
  /*!
* \brief Metoda pozwalająca na dostęp do położenia bryły
* 
* \return Zwraca Polozenie bryły 
*/
  virtual  const Wektor3D& WezPolozeniePrzeszkody()  const override {return Polozenie;}
  virtual bool CzyZajete(const Dron& Dn) override;
  virtual double ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const override;
};

#endif