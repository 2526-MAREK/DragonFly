#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include<iomanip>
#include <fstream>
#include<istream>
#include <cassert>

#define MANIPULATORY_WYSWIETLAJACE std::setw(16) << std::fixed << std::setprecision(10) 

/*!
 * \file
 * \brief Definicja szablonu i metod klasy Wektor 
 *  
 *  Zawiera definicje szablonu i metod klasy Wektor
 *
 */

/*!
* \brief Typ wyliczeniowy dla współrzedych wektora x, y , Z 
* 
* Wartości tego typu służa jako identyfikatory współrzednych wektora(trójwymiarowego)
*/ 
enum wspolrzedne {X, Y, Z}; 

/*!
* \brief Szablon Klasy modeluje pojęcie Wektora.
* 
 * Szablon Klasy Wektor modeluje pojęcie Wektora którego rozmiar jest zależny od wartości podanej przy konkretyzacji szablonu klasy Wektor
*/

template<unsigned int Templ_Size>
class Wektor {
private:
/*!
  * \brief Tablica statyczna zawierająca współrzedne wektora 
  *
  * Pole szablonu klasy  Wektor zawierające Tablice statyczna z rozmiarem zależnym od podanej wartośći w trakcie konkretyzacji szablonu.
  * Tablica ta przechowuje Współrzedne Wektora 
  */
  double Wsp[Templ_Size]; 
  static int IloscAktualna;
  static int IloscOgolna;
public:
/*!
  * \brief Konstruktor Domyślny szablonu klasy Wektor
  */
  Wektor(); 
  /*!
  * \brief Konstruktor parametryczny szablonu klasy Wektor 
  */
  Wektor(const std::initializer_list<double> &rListaWsp);
  Wektor(const Wektor &Wktr);
  Wektor& operator=(const Wektor& Wktr);
 /*!
  * \brief Pozwala na dostęp do składowej prywatnej szablonu (Tablicy jednowymiarowej) za pomocą operatora przeciążonego '[]'
  * 
  * \param[in] lnd - Indeks odpowiedniej współrzednej Wektora
  * 
  * \pre lnd nie może być większe i równe Rozmiarowi Wektora podanego przy konkretyzacji Szablonu klasy Wektor
  * 
  * \post Użytkownik dostaje dostęp do odpowiedniej współrzednej Wektora
  * 
  * \return Odpowiednia współrzedną wektora
  */
  double operator [] (unsigned int lnd) const { assert(lnd < Templ_Size); return Wsp[lnd]; }
 /*!
  * \brief Pozwala na dostęp do składowej prywatnej szablonu (Tablicy jednowymiarowej) za pomocą operatora przeciążonego '[]'
  * 
  * \param[in] lnd - Indeks odpowiedniej współrzednej Wektora
  * 
  * \pre lnd nie może być większe i równe Rozmiarowi Wektora podanego przy konkretyzacji Szablonu klasy Wektor
  * 
  * \post Użytkownik dostaje dostęp do odpowiedniej współrzednej Wektora
  * 
  * \return Odpowiednia współrzedną wektora
  */
  double &operator [] (unsigned int lnd)  { assert(lnd < Templ_Size); return Wsp[lnd]; } 
  /*!
  * \brief Dodaje dwa Wektory 
  */
  Wektor operator+(const Wektor & Wierz) const;
   /*!
  * \brief Odejmuje dwa Wektory 
  */
  Wektor operator-(const Wektor & Wierz) const;
  Wektor operator*(const Wektor & Wierz) const;
  Wektor operator*(double liczba) const;
  double dlugosc() const;
  static int WezIloscAktualnaWektorow(){ return IloscAktualna;}
  static int WezIloscOgolnaWektorow(){return IloscOgolna;}
  /*!
  * \brief Destruktor Szablonu klasy Wektor
  */
  ~Wektor(); 
};

template <unsigned int Templ_Size>
int Wektor <Templ_Size>::IloscAktualna =0;

template <unsigned int Templ_Size>
int Wektor <Templ_Size>::IloscOgolna =0;

/*! 
*  Konstruktor Domyślny, który iniciajlizuje nowo tworzony obiekt szablonu klasy 
* Wektor. Wypełania każde pole klasy zerami.
*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor()
{
  ++IloscAktualna;
  ++IloscOgolna;
  for(double& Wspolrzedne: Wsp)
    Wspolrzedne = 0;  //Inicjalizacja całej tablicy zerami 
}

/*! 
*  Konstruktor parametryczny szablonu klasy Wektor, który Inicjalizuje obiekt szablonu klasy Wektor odpowiednimi argumentami podanymi przez użytkownika
* za pomocą listy inicjalizacyjnej, dzięki szablonowi initializer_list z biblioteki standardowej
* 
* \param[in] rListaWsp - Referencja do obietku szablonu klasy z biblioteki standardowej initilizer_list pozwala ona na inicjalizacje obiektu 
* szablonu klasy Wektor za pomocą listy inicjalizacyjnej 
* 
* \pre Ilośc inicjalizowanych współrzędnych do Wektora nie może być wieksza od Ilosci Podanego rozmiaru Wektora w konkretyzacji szablonu klasy
* 
* \post Zainicializowany obiekt szablonu klasy Wektor danymi przez użytkownika wartościami, jeśli użytkownik podał mniej wartośći niż 
* rozmiar Wektora podany przy konkretyzacji szablonu to wtedy reszta Wektora jest inicializowana jako wartość 0, umożliwa 
* to wywołanie Kontruktora domyślnego szablonu klasy Wektor[ : Wektor() ] za pomocą listy inicjalizacyjnej przed wywołaniem naszego konstruktora parametrycznego.
* 
*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor(const std::initializer_list<double> &rListaWsp) : Wektor() 
{
  assert(rListaWsp.size() <= Templ_Size);
  int Ind = -1;
  for(double Wsp_i : rListaWsp)
    Wsp[++Ind] = Wsp_i;
}

/*Konstruktor kopiujący szablonu  klasy Wektor*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor(const Wektor<Templ_Size> &Wktr)
{
  ++IloscAktualna;
  ++IloscOgolna;
  for(unsigned int Ind = 0; Ind<Templ_Size; ++Ind){
    Wsp[Ind] = Wktr[Ind];
  }
}

/*Przeciążenie operatora przypisania*/
template <unsigned int Templ_Size>
Wektor<Templ_Size> & Wektor<Templ_Size>::operator=(const Wektor<Templ_Size> &Wktr)
{
  if(this == &Wktr)
    return *this;

  for(unsigned int Ind = 0; Ind<Templ_Size; ++Ind){
    Wsp[Ind] = Wktr[Ind];
  }
   return *this;
}

/*!
  * \brief Przeciąża operator '<<' dla szablonu klasy Wektor i pozwala wyświetlić jego składowe 
  * 
  * Funkcja przeciążająca operator '<<' dla szablonu klasy Wektor. Wczytuje do strumienia
  * wyjściowego odpowiednie współrzedne wierzchołków i ustawia odpowiednie
  *  flagi( manipulatory: setw, fixed, setprecision) na strumień wyjściowy dla 
  * prawidłowości wczytywania do strumienia wyjściowego.
  *
  *  \param[in] StrmWy - Referncja na klase ostream 
  *  \param [in] Wktr - Referencja na obiekt szablonu klasy Wektor, który zawiera informacje o
  *  wierzchołkach Wektora
  *
  * \pre Obiekt Wktr musi mieć juz wcześniej zainicjowane współrzedne wierzchołków
  * prostokąta początkowego To przeciążenie tylko je wczytuje, a nie inicjalizuje.
  *
  * \post Prawidłowo wczytane Współrzędne wierzchołków prostokąta do strumienia wyjściowego
  *
  * \return Referncja na Obiekt (StrmWy) klasy ostream
  */
template <unsigned int Templ_Size>
std::ostream &operator<<(std::ostream &StrmWy, const Wektor<Templ_Size> &Wktr)
{
  for(unsigned int i=0;i<Templ_Size;++i)
    StrmWy << Wktr[i]<<" ";
  StrmWy<<std::endl;  
  return StrmWy;
}

 /*!
  *  Funkcje przeciążają operatory '-' dla szablonu klasy Wektor,
  * wywołując konstruktor szablonu klasy Wektor który przypisuje do 
  * obiektu odpowiednio składowe odjęte
  *
  * \param[in] Wierz - Stała Referencja na obiekt szablonu klasy Wektor zawierający
  * dane na temat wektora(współrzedne wektora)
  * 
  * \pre Obiekt wywołujący przeciążenie i obiekt przekazany przez
  *  referncje (Wierz) musi mieć dane na temat odejmowanych
  *  wektrów, a mianowicie wspólrzedne wektora.
  *  
  * \post Wypełniony obiekt odpowiednimi wartościami po wykonaniu
  * operacji odejmowania.
  *
  * \return Funkcja przeciązająca zwraca obiekt, do którego zostały
  * przypisane wykonane operacje odejmowania
  * na współrzednych wektora.
  */
template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator-(const Wektor<Templ_Size> & Wierz) const
{
  Wektor<Templ_Size> Wktr;
  for(int unsigned i=0;i<Templ_Size;++i)
    Wktr.Wsp[i] = Wsp[i]-Wierz[i];
  return Wktr;
}


/*!
  *  Funkcje przeciążają operatory '+' dla szablonu klasy Wektor,
  * wywołując konstruktor szablonu klasy Wektor który przypisuje do 
  * obiektu odpowiednio składowe dodane
  *
  * \param[in] Wierz - Stała Referencja na obiekt szablonu klasy Wektor zawierający
  * dane na temat wektora(współrzedne wektora)
  * 
  * \pre Obiekt wywołujący przeciążenie i obiekt przekazany przez
  *  referncje (Wierz) musi mieć dane na temat dodawanych
  *  wektrów, a mianowicie wspólrzedne wektora.
  *  
  * \post Wypełniony obiekt odpowiednimi wartościami po wykonaniu
  * operacji dodawania.
  *
  * \return Funkcja przeciązająca zwraca obiekt, do którego zostały
  * przypisane wykonane operacje dodawania
  * na współrzednych wektora.
  */
template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator+(const Wektor<Templ_Size> & Wierz) const
{
  Wektor<Templ_Size> Wktr;
  for(int unsigned i=0;i<Templ_Size;++i)
    Wktr.Wsp[i] = Wsp[i]+Wierz[i];
  return Wktr;
}

template <unsigned int Templ_Size>
double Wektor<Templ_Size>::dlugosc() const
{
  double dlugosc;
  for(int unsigned i=0;i<Templ_Size;++i)
    dlugosc += pow(Wsp[i], 2);
  return sqrt(dlugosc);
}


template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator*(const Wektor<Templ_Size> & Wierz) const
{
  Wektor<Templ_Size> Wktr;
  for(int unsigned i=0;i<Templ_Size;++i)
    Wktr.Wsp[i] = Wsp[i]*Wierz[i];
  return Wktr;
}

template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator*(double liczba) const
{
  Wektor<Templ_Size> Wktr;

  for(int unsigned i=0;i<Templ_Size;++i){
    Wktr.Wsp[i] = Wsp[i]*liczba;
  }
  return Wktr;
}

/*template <unsigned int Templ_Size>
bool Wektor<Templ_Size>::operator>(const Wektor<Templ_Size> & Wktr) const
{
  int TabPom[Templ_Size];
  for(int unsigned i=0;i<Templ_Size;++i){
    if(Wsp[i]>Wktr[i]) 
      TabPom[i]= 1;
    else
      TabPom[i] = 0;  
}
return false;  
}

template <unsigned int Templ_Size>
bool Wektor<Templ_Size>::operator<(const Wektor<Templ_Size> & Wktr) const
{
  for(int unsigned i=0;i<Templ_Size;++i){
    if(Wsp[i]<Wktr[i]) return true;
  }
return false;  
}*/
/*!
  * \brief Przeciążenie operatora '>>' dla szablony klasy Wektor pozwalające zapisywać dane do składowych szablonu klasy
  *  Przeciązenie operatora '>>' pozwalające zapisać współrzedne
  * wektora z strumienia wejściowego do obiektu przekazanego 
  * przez referencje.
  * 
  * \param[in] StrmWe - Referncja na obiekt klasy istream
  * \param[in] Wktr - Referncja na obiekt szablonu klasy Wektor
  *
  * \pre Wcześniej zainicjalizowany przez konstruktor domyślny 
  * obiekt szablonu klasy Wektor
  *
  * \post Prawidłowo zapisane dane o współrzednych wektora
  *  do obiektu szablonu klasy Wektor
  *
  * \return Funkcja zwraca obiekt klasy istream.
  */
template <unsigned int Templ_Size>
std::istream& operator>>(std::istream &StrmWe, Wektor<Templ_Size> &Wktr)
{
  for(int unsigned i=0;i<Templ_Size;++i)
    StrmWe>>Wktr[i];
  return StrmWe;
}

/*!
*Destruktor Szablonu klasy Wektor
*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::~Wektor(){ --IloscAktualna;}

#endif
