#include "BrylaGeometryczna.hh"
#include "Dron.hh"

/*!
 * \file 
 * \brief Definicje metod i funkcji pomocniczych klasy BrylaGeometryczna
 *
 *  Plik zawiera definicje metod i funkcji pomocniczych klasy BrylaGeometryczna.
 */
bool BrylaGeometryczna::CzyZajete(const Dron& Dn) {Dn.CzyTenDronJestAktywny();  return true;}

double BrylaGeometryczna::ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki) const
{Dn.CzyTenDronJestAktywny(); PunktySciezki[0]= PunktySciezki[0]; return 0.0;}
/*!
* Konstruktor Domyślny klasy BrylaGeometryczna.
*/
/*BrylaGeometryczna::BrylaGeometryczna() : Skala()
{
    NazwaPlikuBrylaWzorcowa = "brak";
    NazwaPlikuBrylaFinalna = "brak";
}*/

/*!
* Konstruktor parametryczny z wartościami domyślnymi klasy BrylaGeometryczna.
*/
BrylaGeometryczna::BrylaGeometryczna(const std::string & s1, const std::string & s2, const Wektor3D & SkalaTym) : NazwaPlikuBrylaWzorcowa(s1),
 NazwaPlikuBrylaFinalna(s2), Skala(SkalaTym)
{} 
            
/*!
* Metoda odpowiada za skalowanie odpowiedniego zadanego Wierzchołka 
* 
* \param[in] Wierz - Stała referncja do obiektu klasy Wektor3D, który zawiera skalowany WIerzchołek 
*
* \return Zwraca Przeskalowany wierzchołek
*/
Wektor3D BrylaGeometryczna::Skaluj(const Wektor3D& Wierz) const
{
    Wektor3D Wktr3DZeskalowany=Wierz*Skala;
    return Wktr3DZeskalowany;    
}
/*!
* Funkcja sprawdzajaca poprawność wczytanych danych 
*
* \param[in, out] StrmWej - Referncja do Strumienia Wejściowego
*
* \retval true jeśli wczytane dane są nieprawidłowe
* \retval false jeśli wczytane dane są prawidłowe
*/
bool NiePrawidlowoWczytano(const std::ifstream &StrmWej)
{   
    if(StrmWej.fail()){
        assert(!StrmWej.fail());                           
        return true;
           }
    return false;
}

/*!
* Funkcja sprawdzajaca poprawność zapisanych danych 
*
* \param[in, out] StrmWej - Referncja do Strumienia Wyjściowego
*
* \retval true jeśli zapisane dane są nieprawidłowe
* \retval false jeśli zapisane dane są prawidłowe
*/
bool NiePrawidlowoZapisano(const std::ofstream &StrmWyj)
{
    if(StrmWyj.fail()){
            assert(!StrmWyj.fail());                           
            return true;
    }
    else
        return false;
}
/*!
* \param[in] StrmWe - Referncja do obiektu klasy ifstream, który zaweira uchwyt do naszego pliku wejściowego
* \param[in] NazwaPliku - Referencja do obiektu klasy string, który zawiera nazwe pliku wejściowego
* 
* \retval true - Gdy operacja się powiedzie
* \retval false - Gdy operacja się nie powiedzie, stanie się to gdy plik nie zostanie prawidłowo otwarty
*/
bool OtworzonoPlik(const std::ifstream &StrmWe, const std::string &NazwaPliku)
{
    if (!StrmWe.is_open()) {
        std::cerr << std::endl
	    << " Blad otwarcia do odczytu pliku: " << NazwaPliku << std::endl
	    << std::endl;
        assert(!StrmWe.is_open());
        return false;
    }
    return true;
}

/*!
* \param[in] StrmWe - Referncja do obiektu klasy ifstream, który zawiera uchwyt do naszego pliku wyjściowego
* \param[in] NazwaPliku - Referencja do obiektu klasy string, który zawiera nazwe pliku wyjściowego
* 
* \retval true - Gdy operacja się powiedzie
* \retval false - Gdy operacja się nie powiedzie, stanie się to gdy plik nie zostanie prawidłowo otwarty
*/
bool OtworzonoPlik(const std::ofstream &StrmWy, const std::string &NazwaPliku)
{
    if (!StrmWy.is_open()) {
        std::cerr << std::endl
	    << " Blad otwarcia do odczytu pliku: " << NazwaPliku << std::endl
	    << std::endl;
        assert(!StrmWy.is_open());
        return false;
    }
    return true;
}

/*!
* Metoda wirtualna klasy BrylaGeometryczna która jest bezużyteczna w klasie BrylaGeometryczna, 
* klasy dziedziczone po BryleGeometrycznej z jej korzystaja 
*
*/
bool BrylaGeometryczna::Tworz()const
{
    return true;
}

/*!
* Metoda wirtualna klasy BrylaGeometryczna która jest bezużyteczna w klasie BrylaGeometryczna, 
* klasy dziedziczone po BryleGeometrycznej z jej korzystaja 
*
*/
bool BrylaGeometryczna::Usun()const
{
    return true;
}


