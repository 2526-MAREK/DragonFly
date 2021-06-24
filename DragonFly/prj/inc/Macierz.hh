#ifndef MACIERZ_HH
#define MACIERZ_HH


#include <iostream>
#include <math.h>
#include "Wektor.hh"
#include "Wektor3D.hh"

/*!
 * \file
 * \brief Definicja szablonu i metod klasy Macierz
 *
 * Zawiera definicję szablonu i metod klasy Macierz. 
 * 
 */

/*!
 * \brief Szablon Klasy modeluje pojęcie macierzy kwadratowej
*  
* Szablon klasy Macierz modeluje pojęcie Macierzy kwadratowej której rozmiar jest zależny od wartości podanej przy konkretyzacji szablonu klasy Macierz
 *
 */
template<unsigned int Templ_Size>
class Macierz {
private:  
/*!
  * \brief Tablica statyczna zawierająca wartości macierzy kwadratowej 
  *
  * Pole szablonu klasy Macierz zawierające Tablice statyczna z rozmiarem zależnym od podanej wartośći w trakcie konkretyzacji szablonu.
  * Tablica ta przechowuje wartości macierzy Kwadratowej
  */
  double Tab[Templ_Size][Templ_Size]; 
public:
/*!
  * \brief Konstruktor Domyślny szablonu klasy Macierz 
  */
  Macierz(); 
  /*!
  * \brief Konstruktor parametryczny szablonu klasy Macierz 
  */
  Macierz(const std::initializer_list<double> &rListaWsp);
  /*!
  * \brief Pozwala na dostęp do składowej prywatnej szablonu (Tablicy dwu-wymiarowej) za pomocą operatora przeciążonego '()'
  * 
  * \param[in] Wie - Indeks odpowiedniego wiersza Macierzy Kwadratowej
  * \param[in] Kol - Indeks odpowiedniej kolumny Macierz Kwadratowej
  * 
  * \pre Wie i Kol nie mogą być większe i równe Rozmiarowi macierzy Kwadratowej podanego przy konkretyzacji Szablonu klasy Macierz 
  * 
  * \post Użytkownik dostaje dostęp do odpowiedniej wartości macierzy Kwadratowej 
  * 
  * \return Odpowiednia wartość macierzy 
  */
  double operator () (unsigned int Wie,unsigned int Kol) const { assert((Wie < Templ_Size)||(Kol < Templ_Size)); return Tab[Wie][Kol]; }
  /*!
  * \brief Pozwala na dostęp do składowej prywatnej szablonu (Tablicy dwu-wymiarowej) za pomocą operatora przeciążonego '()'
  * 
  * \param[in] Wie - Indeks odpowiedniego wiersza Macierzy Kwadratowej
  * \param[in] Kol - Indeks odpowiedniej kolumny Macierz Kwadratowej
  * 
  * \pre Wie i Kol nie mogą być większe i równe Rozmiarowi macierzy Kwadratowej podanego przy konkretyzacji Szablonu klasy Macierz 
  * 
  * \post Użytkownik dostaje dostęp do odpowiedniej wartości macierzy Kwadratowej 
  * 
  * \return Odpowiednia wartość macierzy 
  */
  double& operator () (unsigned int Wie,unsigned int Kol) { assert((Wie < Templ_Size)||(Kol < Templ_Size)); return Tab[Wie][Kol]; }
  /*!
  * \brief Mnoży macierz przez wektor
  */
  Wektor<Templ_Size> operator *(const Wektor<Templ_Size> &Wktr) const;
  /*!
  * \brief Mnoży macierz przez macierz
  */
  Macierz<Templ_Size> operator *(const Macierz<Templ_Size> &MacRot) const; 
  /*!
  * \brief Destruktor klasy Macierz
  */
 //inline void UstawMacRotZ_Radiany(double KatRadiany); : Macierz(cos(KatRadiany), -sin(KatRadiany),0, sin(Kat_rad), cos(Kat_rad),0,0,0,1) {}
  ~Macierz(); 
};

/*! 
*  Konstruktor Domyślny, który iniciajlizuje nowo tworzony obiekt szablonu klasy 
* Macierz. Wypełania każde pole klasy zerami.
*/
template <unsigned int Templ_Size>
Macierz<Templ_Size>::Macierz()
{
    /*Inicjalizuje tablice i dane zerami*/
    for(double* ElemTab: Tab)
      *ElemTab = 0;
}

/*! 
*  Konstruktor parametryczny szablonu klasy Macierz, który Inicjalizuje obiekt szablonu klasy Macierz odpowiednimi argumentami podanymi przez użytkownika
* za pomocą listy inicjalizacyjnej, dzięki szablonowi initializer_list z biblioteki standardowej
* 
* \param[in] rListaWsp - Referencja do obietku szablonu klasy z biblioteki standardowej initilizer_list pozwala ona na inicjalizacje obiektu 
* szablonu klasy Macierz za pomocą listy inicjalizacyjnej 
* 
* \pre Ilośc inicjalizowanych wartośći do macierzy nie może być wieksza od Ilosci Podanego rozmiaru macierzy kwadratowej w konkretyzacji szablonu klasy
* 
* \post Zainicializowany obiekt szablonu klasy Macierz danymi przez użytkownika wartościami, jeśli użytkownik podał mniej wartośći niż 
* rozmiar macierzy kwadratowej podany przy konkretyzacji szablonu to wtedy reszta macierzy jest inicializowana jako wartość 0, umożliwa 
* to wywołanie Kontruktora domyślnego szablonu klasy Macierz[ : Macierz() ] za pomocą listy inicjalizacyjnej przed wywołaniem naszego konstruktora parametrycznego.
* 
*/
template <unsigned int Templ_Size>
Macierz<Templ_Size>::Macierz(const std::initializer_list<double> &rListaWsp) : Macierz() 
{
  assert(rListaWsp.size() <= Templ_Size*Templ_Size);

  double Tab_tymczas[Templ_Size*Templ_Size];
  int Ind = -1;
  for(double Wsp_i : rListaWsp)
    Tab_tymczas[++Ind] = Wsp_i;

  Ind = -1;    
  for(int unsigned Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(int unsigned Ind2=0;Ind2<Templ_Size;++Ind2)
      Tab[Ind1][Ind2] = Tab_tymczas[++Ind];
  }
}


/*!
  *  Funkcja przeciązająca operator '*'(mnozenia), która 
  * korzysta z obiektu szablonu klasy macierzy i obiektu szablonu klasy 
  * Wektor i je przemnaża 
  * 
  * \param[in] Wktr- Referncja na obiekt szablon klasy Wektor zawierący
  * informacje o współrzędnych Wektora
  *
  * 
  * \pre Obiekt szablonu klasy Wektor musi mieć wcześniej zainicjalizowane dane 
  * o współrzednych Wektora
  * 
  * \pre obiekt szablonu klasy Macierz musi mieć zainicjalizwoane wczesniej dane 
  * o wartościach macierzy kwadratowej 
  *
  * \post Prawidłowo przemnożony dany Wektor i Macierz 
  *
  *  \return Metoda zwraca przez wartość Obiekt szablonu klasy Wektor zainicjalizowany 
  * odpowiednimi wartościami 
  */
template <unsigned int Templ_Size>
Wektor<Templ_Size> Macierz<Templ_Size>::operator *(const Wektor<Templ_Size> &Wktr) const
{
  Wektor<Templ_Size> Wek;
  for(unsigned int Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(unsigned int Ind2 = 0;Ind2<Templ_Size;++Ind2){
      Wek[Ind1] = Wek[Ind1] + Wktr[Ind2]*Tab[Ind1][Ind2];
    }
  }
  return Wek;
}

/*!
  *  Funkcja przeciązająca operator '*'(mnozenia), która 
  * korzysta z obiektu szablonu klasy macierzy i drugiego obiektu szablonu klasy Macierz
  * i je przemnażą. 
  * 
  * \param[in] MacRot- Referncja na obiekt szablon klasy Macierz zawierący
  * informacje o wartościach macierzy kwadratowej
  * 
  * \pre obiekty szablonu klasy Macierz musza mieć zainicjalizwoane wczesniej dane 
  * o wartościach macierzy kwadratowej 
  *
  * \post Prawidłowo przemnożone dane dwie Macierze Kwadratowe 
  *
  *  \return Metoda zwraca przez referencje Obiekt szablonu klasy Macierz zainicjalizowany 
  * odpowiednimi wartościami 
  */
template <unsigned int Templ_Size>
Macierz<Templ_Size> Macierz<Templ_Size>::operator *(const Macierz<Templ_Size> &MacRot) const
{
  Macierz<Templ_Size> MacRotTym;
  for(unsigned int Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(unsigned int Ind2 = 0;Ind2<Templ_Size;++Ind2){
      for(unsigned int Ind3 =0; Ind3<Templ_Size;++Ind3)
        MacRotTym.Tab[Ind1][Ind2] += MacRot.Tab[Ind1][Ind3]*Tab[Ind3][Ind2];
    }
  }
  return MacRotTym;
}

/*! 
 *  \brief Funkcja wyświetla na standardowe wyjście zawartość Macierzy Kwadratowej
 *
  * Funkcja przeciążająca operator '<<' dla szablonu klasy Macierz. Wczytuje do strumienia
  * wyjściowego zawartość Macierzy kwadratowej. Funkcja wyświetla Zawartość Macierzy Kwadratowej 
  *
  *  \param[in] StrmWy - Referncja na klase ostream 
  *  \param[in] MacRot - Referencja na obiekt szablonu klasy Macierz , który zawiera informacje o 
  * wartościach zawartych w macierzy 
  *
  *  \pre Obiekt MacRot musi mieć juz wcześniej zainicjowane wartośći Macierzy
  * 
  * \post Wyświetlenie zawartości macierzy do strumienia wyjściowego
  *
  * \return Referncja na Obiekt (StrmWy) klasy ostream
  */

template <unsigned int Templ_Size>
std::ostream &operator<<(std::ostream &StrmWy, const Macierz<Templ_Size> &MacRot)
{
  for(unsigned int Ind1= 0; Ind1<Templ_Size;++Ind1)
  {
    for(unsigned int Ind2= 0; Ind2<Templ_Size;++Ind2)
    {
      StrmWy<<MacRot(Ind1, Ind2);
    }
  }
  return StrmWy;
}

/*!
* Destruktor szablonu klasy Macierz 
*/ 
template <unsigned int Templ_Size>
Macierz<Templ_Size>::~Macierz(){}

#endif
