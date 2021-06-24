#include "Scena.hh"
#include "InterfejsUzytkownika.hh"
#include <list>
#include <memory>
/*!
 * \file 
 * \brief Definicje metod klasy Prostopadloscian
 *
 *  Plik zawiera definicje metod klasy Prostopadloscian.
 */

Scena::Scena(const Dron &Dron1,const Dron& Dron2, const std::list<std::shared_ptr<Dron>> &DronLstDr,
const std::list<std::shared_ptr<ElementSceny>>& DronLstEs, const PzG::LaczeDoGNUPlota &LaczeTym, std::list<std::shared_ptr<BrylaGeometryczna>>& LstTym) : 
LstDr(DronLstDr), LstEs(DronLstEs), Lacze(LaczeTym), Lst(LstTym),AktualnaLiczbaPrzeszkod(0),MaksPrzeszkodOsiagnieteWProgramie(0)
{
    TabDronow[0] = Dron1;
    TabDronow[1] = Dron2;
}

/*!
* Metoda Pozwala na dostęp do aktywnego drona, zwraca przez stała referncje Danego aktywnego Drona
*
* \return Przez stała referencja zwraca aktwywnego Drona, którego nie możemy modyfikować
*/
const Dron& Scena::WezAktywnegoDrona() const
{
    if(TabDronow[0].CzyTenDronJestAktywny())
        return TabDronow[0];
    else
        return TabDronow[1];
}

const Dron& Scena::WezNieAktywnegoDrona() const
{
    if(!TabDronow[0].CzyTenDronJestAktywny())
        return TabDronow[0];
    else
        return TabDronow[1];
}

/*!
* Metoda Pozwala na dostęp do aktywnego drona, zwraca przez stała referncje Danego aktywnego Drona
*
* \return Przez referencje zwraca aktwywnego Drona, którego możemy modyfikować
*/
Dron& Scena::UzyjAktywnegoDrona()
{
    if(TabDronow[0].CzyTenDronJestAktywny())
        return TabDronow[0];
    else
        return TabDronow[1];
}

/*bool Scena::UtworzElementyPowierzchniNaScenie() const
{
    for(const std::shared_ptr<BrylaGeometryczna> &Element : Lst){
        if(!Element->Tworz()) return false;
    }
    return true;
}*/

/*!
* Metoda usuwa przeszkode z listy i z sceny 
*
* \pre Lista musi mieć co najmniej jeden element 
*
* \post Usuniety element z listy i sceny
*
* \param[in] NumerElementuListy - Numer elementu, który ma zostać usunięty z listy
*
* \retval true jeśli usuniecie z sceny przeszkody udało się 
*
*  \retval false w przeciwnym wypadku 
*
*/

bool Scena::UsunElementzZListyISceny(int NumerElementuListy)
{ 
    assert(Lst.size()>0);
    int Licznik = 0;
    std::shared_ptr<BrylaGeometryczna> wskBrylaGeo;
     for (std::list<std::shared_ptr<BrylaGeometryczna>>::iterator Iter = Lst.begin();  Iter != Lst.end();  ++Iter) 
     {  
        if(Licznik == NumerElementuListy)
             wskBrylaGeo = *Iter;            
        ++Licznik;            
     }
     if(!wskBrylaGeo->Usun())
        return false;
     Lst.remove(wskBrylaGeo);
    NazwyWolnychPlikow.push_back(wskBrylaGeo->WezNazwePliku_BrylaFinalna());    
     Lacze.UsunNazwePliku(wskBrylaGeo->WezNazwePliku_BrylaFinalna());
     --AktualnaLiczbaPrzeszkod;
     Lacze.Rysuj();
     return true;
}

/*!
* Metoda tworzy plaskowyz na scenie i dodaje wskaznik na obiekt klasy Plaskowyz na liste 
*
* \param[in,out] Skala - stała referencja do obeiktu klasy Wektor3D, który przechowuje infromacje o skali przeszkody 
*
* \param[in,out] Polozenie - Stała referencja do obiektu klasy Wektor3D, który przechowuje informacje o położeniu przeszkody
*
* \retval true jeśli dodanie na scene przeszkody udało się 
*
*  \retval false w przeciwnym wypadku 
*/
bool Scena::UtworzPlaskowyzIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie)
{
    ZwiekszLiczbePrzeszkod();
    Plaskowyz PlaskoW(PLIK_WZORCOWEGO_SZESCIANU_NA_POWIERZCHNI,
    NazwyWolnychPlikow.size()>0 ? *NazwyWolnychPlikow.begin() : TworzNazwePlikuPrzeszkody(AktualnaLiczbaPrzeszkod), Skala,Polozenie); 
    if(NazwyWolnychPlikow.size()>0)
        NazwyWolnychPlikow.remove(*NazwyWolnychPlikow.begin());     
    Lacze.DodajNazwePliku(PlaskoW.WezNazwePliku_BrylaFinalna().c_str());     

    std::shared_ptr<Plaskowyz> wsk_Plaskowyz = std::make_shared<Plaskowyz>();
    *wsk_Plaskowyz = PlaskoW;
    std::shared_ptr<BrylaGeometryczna> wsk2_Plaskowyz = wsk_Plaskowyz;
    if(!wsk2_Plaskowyz->Tworz())
        return false;

   std::shared_ptr<ElementSceny> wskElementSceny = wsk_Plaskowyz;        
   DodajElementNaListeElementowSceny(wskElementSceny);         
    DodajElementNaListePrzeszkod(wsk2_Plaskowyz);
    Lacze.Rysuj();
    return true;
}

/*!
* Metoda tworzy Gore z Dluga Grania na scenie i dodaje wskaznik na obiekt klasy GoraZDlugaGrania na liste 
*
* \param[in,out] Skala - stała referencja do obeiktu klasy Wektor3D, który przechowuje infromacje o skali przeszkody 
*
* \param[in,out] Polozenie - Stała referencja do obiektu klasy Wektor3D, który przechowuje informacje o położeniu przeszkody
*
* \retval true jeśli dodanie na scene przeszkody udało się 
*
*  \retval false w przeciwnym wypadku 
*/
bool Scena::UtworzGoraZDlugaGraniaIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie)
{
  ZwiekszLiczbePrzeszkod();
  GoraZDlugaGrania GoraZDGrania(PLIK_WZORCOWEGO_SZESCIANU_NA_POWIERZCHNI,
  NazwyWolnychPlikow.size()>0 ? *NazwyWolnychPlikow.begin()  : TworzNazwePlikuPrzeszkody(AktualnaLiczbaPrzeszkod),Skala,Polozenie); 
  if(NazwyWolnychPlikow.size()>0)
        NazwyWolnychPlikow.remove(*NazwyWolnychPlikow.begin());     
  Lacze.DodajNazwePliku(GoraZDGrania.WezNazwePliku_BrylaFinalna().c_str());                    
  std::shared_ptr<GoraZDlugaGrania> wsk_GoraZDGrania = std::make_shared<GoraZDlugaGrania>();
  
  *wsk_GoraZDGrania = GoraZDGrania;
  std::shared_ptr<BrylaGeometryczna> wsk2_GoraZDGrania = wsk_GoraZDGrania;
    if(!wsk2_GoraZDGrania->Tworz())
        return false;

    std::shared_ptr<ElementSceny> wskElementSceny = wsk2_GoraZDGrania;        
   DodajElementNaListeElementowSceny(wskElementSceny);         
   DodajElementNaListePrzeszkod(wsk2_GoraZDGrania);
   Lacze.Rysuj();
   return true;
}

/*!
* Metoda tworzy Gore z Ostrym Szczytem na scenie i dodaje wskaznik na obiekt klasy GoraZOstrymSzczytem na liste 
*
* \param[in,out] Skala - stała referencja do obeiktu klasy Wektor3D, który przechowuje infromacje o skali przeszkody 
*
* \param[in,out] Polozenie - Stała referencja do obiektu klasy Wektor3D, który przechowuje informacje o położeniu przeszkody
*
* \retval true jeśli dodanie na scene przeszkody udało się 
*
*  \retval false w przeciwnym wypadku 
*/
bool Scena::UtworzGoraZOstrymSzczytemIDodajGoNaListe(const Wektor3D& Skala, const Wektor3D& Polozenie)
{
    ZwiekszLiczbePrzeszkod();
    GoraZOstrymSzczytem GoraZOSzczytem(PLIK_WZORCOWEGO_SZESCIANU_NA_POWIERZCHNI,
    NazwyWolnychPlikow.size()>0 ? *NazwyWolnychPlikow.begin() : TworzNazwePlikuPrzeszkody(AktualnaLiczbaPrzeszkod), Skala,Polozenie);
    if(NazwyWolnychPlikow.size()>0)
        NazwyWolnychPlikow.remove(*NazwyWolnychPlikow.begin());     
     Lacze.DodajNazwePliku(GoraZOSzczytem.WezNazwePliku_BrylaFinalna().c_str());        
    std::shared_ptr<GoraZOstrymSzczytem> wsk_GoraZOSzczytem = std::make_shared<GoraZOstrymSzczytem>();

    *wsk_GoraZOSzczytem = GoraZOSzczytem;
    std::shared_ptr<BrylaGeometryczna> wsk2_GoraZOSzczytem1 = wsk_GoraZOSzczytem;

    if(!wsk_GoraZOSzczytem->Tworz()){
        return false;
    }

        std::shared_ptr<ElementSceny> wskElementSceny = wsk2_GoraZOSzczytem1;        
   DodajElementNaListeElementowSceny(wskElementSceny);                 
    DodajElementNaListePrzeszkod(wsk2_GoraZOSzczytem1);
    Lacze.Rysuj();
    return true;
}

/*!
* Metoda tworzy nazwe pliku przeszkody według numeracji podanej w argumencie  metody
*
* \param[in] NrPrzeszkody - Numer przeszkody 
*
* \return Przez wartość nazwe pliku przeszkody przechowana w klasie string 
*/
std::string Scena::TworzNazwePlikuPrzeszkody(unsigned int NrPrzeszkody)
{
    std::ostringstream StrmWy;

    StrmWy<<"dat/przeszkoda"<<NrPrzeszkody<<".dat";
    return StrmWy.str();
}

/*!
* Metoda Usuwa "Nadmiarowe" pliki, które zostały stworzone w trakcie działania programu 
* W programie mamy 4 podstawowe pliki przeszkód , które nie są usuwane. Wszystkie pliki przeszkód 
* w ilości większej od 4 są usuwane po zakończeniu pracy programu.
*/
void Scena::UsunNadmiarowePlikiPrzeskod()
{   
    for(unsigned int Ind = 5; Ind<=MaksPrzeszkodOsiagnieteWProgramie;++Ind)    
        remove(TworzNazwePlikuPrzeszkody(Ind).c_str());
}

bool Scena::SprawdzCzyDronMozeLadowac(std::vector<Wektor3D>& PunktySciezki,InterfejsUzytkownika &IU, PzG::LaczeDoGNUPlota& Lacze)
{
    for(std::shared_ptr<ElementSceny>& Element : LstEs)    
    {
        while(Element->CzyZajete(WezAktywnegoDrona())){
            usleep(500000); //0.1s
            std::cout<<std::endl<<":( Ladowisko niedostepne!"<<std::endl;
            std::cout<<":( Wykryto element powierzchni typu: "<<Element->NazwaPrzeszkody()<<std::endl<<std::endl;
            double DlugoscWydluzeniaTrasy = Element->ObliczWydluzenieTrasyPrzelotu(WezAktywnegoDrona(), PunktySciezki);
            UzyjAktywnegoDrona().WydluzTraseLotu(WezAktywnegoDrona(), IU, PunktySciezki, Lacze, DlugoscWydluzeniaTrasy);
            std::cout<<"Lot został wydluzony."<<std::endl<<"Poszukiwanie wolnego ladowiska."<<std::endl<<std::endl;
            //Teraz musimy sprawdzic w tej danej bryle któ©a nie pozwala wyladaowac w jakiej odlegosci od wierzchokow bryly jest poloznie drona i dobrac odpowiednie
            //przedluzenie tej naszej trasy 
            //return false;
        }
    }
    return true;
}
/*Dron& Scena::UzyjNieAktywnegoDrona()
{
    if(!TabDronow[0].CzyTenDronJestAktywny())
        return TabDronow[0];
    else
        return TabDronow[1];
}*/

/*const Dron& Scena::WezNieAktywnegoDrona() const
{
    if(!TabDronow[0].CzyTenDronJestAktywny())
        return TabDronow[0];
    else
        return TabDronow[1];     
}*/

/*!
* MEtoda wykonuje Animacje lotu Drona
*
* \param[in] Lacze - Referencja do obiektu klasy LaczeDoGNUPLOTA, która pozwala na połączenie z programem GNUPLOT
* \param[in] IU - Referencja do obiektu klasy InterfejsUzytkownika, zawierający dane na temat planowanego lotu drona podane przez użytkownika
* 
* \return - Wartość -1 jeśli któraś z operacji lotu się nie powiedzie 
* \return - wartośc 1 jeśli wszystko się powiedzie 
*/
int Scena::AnimacjaLotuDrona(PzG::LaczeDoGNUPlota& Lacze,const InterfejsUzytkownika &IU)
{
  std::vector<Wektor3D> PunktySciezki;
  PunktySciezki.reserve(4);
  if(!UzyjAktywnegoDrona().PlanujPoczatkowaSciezke(IU, PunktySciezki, Lacze)){
    std::cout<<"Sproboj jeszcze raz !!!"<<std::endl;
    return -1;
  };
  std::cout<<std::endl<<"Realizacja przelotu ..."<<std::endl;
  if(!UzyjAktywnegoDrona().WykonajPionowyLot(IU.WezDlugoscLotuPionowego(), Lacze)) return -1;
  if(!UzyjAktywnegoDrona().WykonajZmianeOrientacji(IU.WezKierunekLotu_Stopnie(), Lacze)) return -1;
  if(!UzyjAktywnegoDrona().WykonajPoziomyLot(IU.WezDlugoscLotuPoziomego(),IU.WezKierunekLotu_Stopnie(), Lacze)) return -1;
  if(!SprawdzCzyDronMozeLadowac(PunktySciezki, const_cast<InterfejsUzytkownika&>(IU), Lacze)) return -1;
  if(!UzyjAktywnegoDrona().WykonajPionowyLot(-IU.WezDlugoscLotuPionowego(), Lacze)) return -1;
  std::cout<<std::endl<<"Dron wyladowal ..."<<std::endl<<std::endl;
  return 1;
}

void Scena::DodajDronaNaListeDronowIDodajNieAktywnegoDronaNaListePrzeszkod(const std::shared_ptr<Dron>& Dr1, const std::shared_ptr<Dron>& Dr2)
{
    LstDr.push_back(Dr1);    
    LstEs.pop_front();
    LstEs.push_front(Dr2);
    LstDr.pop_front();
}