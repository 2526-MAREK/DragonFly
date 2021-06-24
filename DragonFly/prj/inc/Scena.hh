#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory.h>
#include<memory>
#include<list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <typeinfo>
#include "Dron.hh"
#include"GoraZDlugaGrania.hh"
#include"GoraZOstrymSzczytem.hh"
#include"Plaskowyz.hh"
#define PLIK_WZORCOWEGO_SZESCIANU_NA_POWIERZCHNI "bryly_wzorcowe/szescian_na_powierzchni.dat"
#define PLIK_WLASCIWY__PRZESZKODA1 "dat/przeszkoda1.dat"
#define PLIK_WLASCIWY__PRZESZKODA2 "dat/przeszkoda2.dat"
#define PLIK_WLASCIWY__PRZESZKODA3 "dat/przeszkoda3.dat"
#define PLIK_WLASCIWY__PRZESZKODA4 "dat/przeszkoda4.dat"

class Dron;

#define ILOSC_DRONOW 2

/*!
 * \file 
 * \brief Definicja klasy Scena
 *
 *  Plik zawiera definicję klasy Scena, która modeluje pojęcie Sceny na której jest Dron.
 */

/*!
 * \brief Klasa modeluje pojęcie Sceny
 * 
 * Klasa modeluje pojęcie Sceny.  Jej atrybutami są: 
 * Pole TabDronow, które jest statyczna tablica dronów, której rozmiar jest zależny od tego ile 
 * użytkownik chce mieć dronów na Scenie.
 * Pole Lacze, które pozwala połączyc się z programem gnuplot
 * 
 */ 
class Scena
{
private:    
/*! \brief Zawiera Wszystkie dotępne drony w programie 
  * Pole, które jest statyczna tablica dronów, której rozmiar jest zależny od tego ile 
  * użytkownik chce mieć dronów na Scenie.
  */
  Dron TabDronow[ILOSC_DRONOW];
  std::list<std::shared_ptr<Dron>> LstDr;
  std::list<std::shared_ptr<ElementSceny>> LstEs;
  /*! \brief Pozwala połączyc się z programem GnuPlot
  * Pole, które pozwala połączyc się z programem gnuplot
  */
  PzG::LaczeDoGNUPlota Lacze;
  /*!
  * \brief Przechowuje na liscie wskazniki do typu BrylaGeometryczna
  * Pole przechowujące wskazniki na typ BrylaGeometryczna na liscie co pozwala na niejawne rzutowanie w górę i dostęp do metod klas pochodnych
  */
  std::list<std::shared_ptr<BrylaGeometryczna>> Lst;
  /*!
  * \brief Przechowuje na liscie nazwy wolnych plikow
  *
  * Pole przechowujące na liście nazwy wolnych plików, które stały się "wolne" po usunięciu przeszkody ze Sceny. Te
  * wolne pliki możemy wykorzystać do tworzenia następnych przeszkód
  */
  std::list<std::string> NazwyWolnychPlikow;
  /*!
  * \brief Określa ilość aktualnych przeszkod na scenie
  *
  * Pole określa ilośc aktualnych przeszkod na scenie.
  */
  unsigned int AktualnaLiczbaPrzeszkod;
  /*!
  * \brief Określa maksymalna ilość przeszkód jaka pojawiła się na scenie
  *
  * Pole Okrereśla maksymalną ilość przeszkód jaka pojawiła się na scenie. Pole potrzebne do 
  * usuwania nadmiarowych plikow stworzonych w programie po zakonczeniu dzialania programu. Program posiada
  * 4 podstawowe pliki, które nie sa usuwane, a reszta plików czyli wieksza od 4 jest usuwana, program je
  * traktuje jakos "nadmiarowe"
  */
  unsigned int MaksPrzeszkodOsiagnieteWProgramie; 
public:
/*!
* \brief Konstruktor Domyślny klasy Scena
*/
  Scena() : TabDronow(), LstDr(), LstEs(), Lacze(), Lst(), NazwyWolnychPlikow(),AktualnaLiczbaPrzeszkod(0), MaksPrzeszkodOsiagnieteWProgramie(0) {};
  /*!
* \brief Konstruktor parametryczny klasy Scena
*/
  Scena(const Dron &Dron1,const Dron& Dron2, const std::list<std::shared_ptr<Dron>> &DronLstDr,
  const std::list<std::shared_ptr<ElementSceny>>& DronLstEs, const PzG::LaczeDoGNUPlota &LaczeTym, std::list<std::shared_ptr<BrylaGeometryczna>>& LstTym);
  /*!
* \brief Pozwala na dostęp do konkretnego drona 
*
* MEtoda pozwala na dostęp do konkretnego drona przez podanie w argumencie indeksu potrzebnego drona 
*
* \param[in] Ind - Indeks konkretnego Drona
*
* \post Ind musi być mniejszy od Stałej zdefiniowanej ILOSC_DRONOW 
*
* \return Zwraca konkretnego drona przez referencje, co pozwala wywyoływać metody klasy DRon
*/  
 inline Dron& WezDrona(int Ind){assert(Ind < ILOSC_DRONOW); return TabDronow[Ind];}
  Wektor3D WezPolozenieDrona(int Ind) const {assert(Ind < ILOSC_DRONOW); return TabDronow[Ind].WezPolozenieDrona();}
/*!
* \brief Pozwala na dostęp do Aktywnego Drona
*
* MEtoda pozwala na dostęp do Aktywnego Drona
*/    
  const Dron& WezAktywnegoDrona() const;
  const Dron& WezNieAktywnegoDrona() const;
  //const Dron& WezNieAktywnegoDrona() const;
/*!
* \brief Pozwala Użyć aktywnego Drona
*/   
  Dron& UzyjAktywnegoDrona();
  //Dron& UzyjNieAktywnegoDrona();
const std::list<std::shared_ptr<BrylaGeometryczna>>& WezListe() const {return Lst;}    
/*!
* \brief Pozwala Użyć Lacza Do GnuPlota
*/   
  PzG::LaczeDoGNUPlota& UzyjLacza(){return Lacze;}
/*!
* \brief Pozwala dodać element na liste 
*
* \param[in, out] LstTym - Inteligenty wskaznik na typ BrylaGeometryczna
*/  
  inline void DodajElementNaListePrzeszkod(std::shared_ptr<BrylaGeometryczna> &LstTym) { Lst.push_back(LstTym);}
  inline void DodajDronaNaListeDronow(std::shared_ptr<Dron> &LstTym) { LstDr.push_back(LstTym);}
  inline void DodajElementNaListeElementowSceny(std::shared_ptr<ElementSceny> &LstTym) { LstEs.push_back(LstTym);}
  bool SprawdzCzyDronMozeLadowac(std::vector<Wektor3D>& PunktySciezki,InterfejsUzytkownika &IU, PzG::LaczeDoGNUPlota& Lacze);
  /*!    
* \brief Animacja LotuDrona
*/
int AnimacjaLotuDrona(PzG::LaczeDoGNUPlota& Lacze,const InterfejsUzytkownika &IU);
/*!
* \brief Pozwala na dostęp do pierwszego elementu listy
*
* \return Referencja do Inteligentnego wskaźnika typu BrylaGeometryczna, który wskazuje na początek listy
*/  
  inline const std::shared_ptr<BrylaGeometryczna>& WezPierwszyElementListy() const {  return *Lst.begin();}
  //bool UtworzElementyPowierzchniNaScenie() const;
/*!
* \brief Tworzy Plaskowyz i dodaje go na liste i scene
*/  
  bool UtworzPlaskowyzIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie);
/*!
* \brief Tworzy Gore z dluga grania i dodaje ja na liste i scene
*/   
  bool UtworzGoraZDlugaGraniaIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie);
/*!
* \brief Tworzy Gore z ostrym szczytem i dodaje ja na liste i scene
*/   
  bool UtworzGoraZOstrymSzczytemIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie);
/*!
* \brief Usuwa wybrany element z listy 
*/   
  bool UsunElementzZListyISceny(int NumerElementuListy);
/*!
* \brief Tworzy nazwe pliku przeszkody
*/   
  std::string TworzNazwePlikuPrzeszkody(unsigned int NrPrzeszkody);
/*!
* \brief Zwieksza Liczbe przeszkod na scenie
*/   
  inline void ZwiekszLiczbePrzeszkod(){++AktualnaLiczbaPrzeszkod;}
  /*!
* \brief Pozwala na dostęp do aktualnej liczby przeszkod na scenie
*
* \return aktualna liczbe przeszkod na scenie.
*/ 
  inline unsigned int WezAktualnaLiczbePrzeszkod()const {return AktualnaLiczbaPrzeszkod;}
/*!
* \brief Pozwala na dostęp do maksymalnej liczby przeszkod osiągniętej w programie 
*
* \return Maksymalna liczbe przeszkod osiągnięta w programie.
*/   
  inline unsigned int WezMaksPrzeszkodOsiagnieteWProgramie() const { return MaksPrzeszkodOsiagnieteWProgramie;}
/*!
* \brief Usuwa "Nadmiarowe" pliki stworzone w trakcie pracy programu 
*/   
  void UsunNadmiarowePlikiPrzeskod();
/*!
* \brief Sprawdza czy aktualna liczba przeszkod jest ta najwieksza osiągniętą w programie
*/   
  inline void SprawdzMaksymalnaIloscPrzeszkodOsiagnietaWProgramie() { 
    if(AktualnaLiczbaPrzeszkod>MaksPrzeszkodOsiagnieteWProgramie) MaksPrzeszkodOsiagnieteWProgramie = AktualnaLiczbaPrzeszkod;}
void DodajDronaNaListeDronowIDodajNieAktywnegoDronaNaListePrzeszkod(const std::shared_ptr<Dron>& Dr1, const std::shared_ptr<Dron>& Dr2);   
/*!
* \brief Destruktor klasy Scena
*/     
  ~Scena() {}
};

#endif