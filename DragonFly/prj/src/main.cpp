/*!
 * \file
 * \brief Funkcja main
 *
 * Główna funkcja programu
 */
#include"BrylaGeometryczna.hh"
#include "Macierz2x2.hh"
#include "InterfejsUzytkownika.hh"
#include "Scena.hh"

using namespace std;

int main()
{
  PzG::LaczeDoGNUPlota  Lacze;

  Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR4);

  Lacze.DodajNazwePliku("dat/przeszkoda1.dat");
  Lacze.DodajNazwePliku("dat/przeszkoda2.dat");
  Lacze.DodajNazwePliku("dat/przeszkoda3.dat");
  Lacze.DodajNazwePliku("dat/przeszkoda4.dat");

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.


  InterfejsUzytkownika IU;
  Wektor3D Wktr3D1 = {200,200,120};
  IU.UstawStrefeDzialaniaDrona(Wktr3D1);
  Lacze.UstawZakresX(0, Wktr3D1[X]);
  Lacze.UstawZakresY(0, Wktr3D1[Y]);
  Lacze.UstawZakresZ(0, Wktr3D1[Z]);


  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok
  
  Wektor3D Wktr3D2;
  Prostopadloscian Pr1(PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY__DRON1_KORPUS, Wktr3D1={SKALA_KORPUSU},Wktr3D2={0,0,2},0);
  Graniastoslup6 Gr1(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR1, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_LEWY_PRZEDNI},0);   
  Graniastoslup6 Gr2(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR3, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_PRAWY_PRZEDNI},0); 
  Graniastoslup6 Gr3(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR2, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_LEWY_TYLNY},0); 
  Graniastoslup6 Gr4(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR4, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_PRAWY_TYLNY},0); 
  
  Dron Dron1(true,1,Wktr3D1 ={20,20,0},0,Pr1,Gr1,Gr2,Gr3,Gr4);
  std::shared_ptr<Dron> WDron1 = std::make_shared<Dron>();
  *WDron1 = Dron1;

  Prostopadloscian Pr2(PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY__DRON2_KORPUS, Wktr3D1={SKALA_KORPUSU},Wktr3D2={0,0,2},0);
  Graniastoslup6 Gr5(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON2_ROTOR1, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_LEWY_PRZEDNI},0);   
  Graniastoslup6 Gr6(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON2_ROTOR3, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_PRAWY_PRZEDNI},0); 
  Graniastoslup6 Gr7(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON2_ROTOR2, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_LEWY_TYLNY},0); 
  Graniastoslup6 Gr8(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON2_ROTOR4, Wktr3D1={SKALA_ROTORA},Wktr3D2={TRANSLACJA_ROTOR_PRAWY_TYLNY},0); 

  Dron Dron2(false,2,Wktr3D1 ={90,170,0},0,Pr2,Gr5,Gr6,Gr7,Gr8);
  std::shared_ptr<Dron> WDron2 = std::make_shared<Dron>();
  *WDron2 = Dron2;

  std::list<std::shared_ptr<Dron>> LstDr;
  LstDr.push_back(WDron1);
  std::list<std::shared_ptr<ElementSceny>> LstEs;
  LstEs.push_back(WDron2);
  std::list<std::shared_ptr<BrylaGeometryczna>> Lst;

  Scena Sc(Dron1, Dron2, LstDr, LstEs, Lacze, Lst);

  Wktr3D1={20,80,60};
  Wktr3D2={100,90,0};
  Sc.UtworzGoraZDlugaGraniaIDodajGoNaListe(Wktr3D1, Wktr3D2);
  Wktr3D1={10,10,60};
  Wktr3D2={100,20,0};
  Sc.UtworzGoraZOstrymSzczytemIDodajGoNaListe(Wktr3D1, Wktr3D2);
  Wktr3D1={10,10,60};
  Wktr3D2={20,100,0};  
  Sc.UtworzGoraZOstrymSzczytemIDodajGoNaListe(Wktr3D1, Wktr3D2);
  Wktr3D1={50,60,15};
  Wktr3D2={140,105,0};
  Sc.UtworzPlaskowyzIDodajGoNaListe(Wktr3D1, Wktr3D2);

 /* if(!Sc.UtworzElementyPowierzchniNaScenie()){
    std::cout<<" Cos poszlo nie tak(Rysowanie Elementow na Scenie) !"<<std::endl;
    return -1;
  }*/

  if(!Dron2.Oblicz_i_Zapisz_WspGlbDrona()){
    std::cout<<" Cos poszlo nie tak(Rysowanie Drona 2) !"<<std::endl;
    return -1;
  }
  Lacze.Rysuj();
  
  if(!Dron1.Oblicz_i_Zapisz_WspGlbDrona()){
    std::cout<<" Cos poszlo nie tak(Rysowanie dron 1) !"<<std::endl;
    return -1;
  }
  Lacze.Rysuj();        // Teraz powinno pojawic sie okienko gnuplota
                        // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"
  int koniec;                        
  koniec =IU.Menu(Sc); 
  return koniec; 
}
