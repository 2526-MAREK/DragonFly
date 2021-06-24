#include "Dron.hh"
#include "InterfejsUzytkownika.hh"

/*!
 * \file 
 * \brief Definicje metod klasy Dron
 *
 *  Plik zawiera definicje metod klasy Dron.
 */

/*!
*  Konstruktor Domyślny klasy Dron
*/
Dron::Dron() : Polozenie(), KorpusDrona(),RotorDrona()
{
    DronAktywny = false;
    IndeksDrona = 0.0;
    KatOrientacji_stopnie =0.0;
}

const double Dron::DlugoscPojedynczegoKroku = 1; //wartosc domyslna =  1

/*!
* Konstruktor Parametryczny klasy Dron
*/
Dron::Dron(bool DronAktywnyTym,double IndeksDronaTym, const Wektor3D& Polozenietym, double KatOrientacji_tym,const Prostopadloscian &KorpusDronaTym, const Graniastoslup6 &Gr1,
const Graniastoslup6 &Gr2,const Graniastoslup6 &Gr3, const Graniastoslup6 &Gr4) : /*DronAktywny(DronAktywnyTym), IndeksDrona(IndeksDronaTym),*/ Polozenie(Polozenietym), KatOrientacji_stopnie(KatOrientacji_tym),
KorpusDrona(KorpusDronaTym)
{
    DronAktywny =DronAktywnyTym;
    IndeksDrona = IndeksDronaTym;
    RotorDrona[0] = Gr1;
    RotorDrona[1] = Gr2;
    RotorDrona[2] = Gr3;
    RotorDrona[3] = Gr4;
}

/*!
 * Dron zostaje przeniesiony do wskazanej pozycji. 
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy Metoda 
 * prywatnym klasy Dron: Oblicz_i_Zapisz_WspGlbKorpusu i Oblicz_i_Zapisz_WspGlbRotora
 * nie powiEdzie  się otwarcie jednego z plików,
 * z których korzystaja te funkcje lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool Dron::Oblicz_i_Zapisz_WspGlbDrona() const
{    
    if(!Oblicz_i_Zapisz_WspGlbKorpusu()) return false;
    for(unsigned int Ind = 0; Ind < ILOSC_ROTOROW; ++Ind){
        if(!Oblicz_i_Zapisz_WspGlbRotora(RotorDrona[Ind])) return false;
    }
    return true;
}

/*!
 *
 * Przelicza wartość kąta ze stopni na radiany.
 * \param[in] Kat_st - wartość kąta wyrażona w stopniach.
 * \return Wartość przeliczonego kąta wyrażona w radianach.
 */
double StopnieNaRadiany(double Kat_st)
{
  return Kat_st*M_PI/180;
}

/*!
 *
 * Transformuje współrzędne \p x i \p y dokonując obrót o zadany kąt.
 * \param[in] KatObrotu_st - kąt, o który ma być zrealizowany obrót.
 * \param[in,out] Wktr3D - Refeerecnja do obiektu klasy Wektor3D, która przechowuje dane o obracanym wektorze wokół osi OZ
 */
void ObrocWzgledemOsiOZ(double  KatObrotu_st, Wektor3D &Wktr3D )
{
  double Kat_rad = StopnieNaRadiany(KatObrotu_st);
  Macierz3x3 MacRotTym1 = {cos(Kat_rad), -sin(Kat_rad),0, sin(Kat_rad), cos(Kat_rad),0,0,0,1};
  
  Wktr3D= MacRotTym1*Wktr3D;
}

/*!
 *  MEtoda prywatna klasy Dron.Czyta z pliku wejściowego(BRYŁA_WZORCOWA) współrzędne wierzchołków bryły wzorcowej 
  korpusu(Prostopadlościanu), dokonuje  ich transformacji (skalowanie, translacja z układu bryły
   wzorcowej do układu drona i translacja z układu współrzednych drona do układu współrzednych scena)
 *  Zapisuje do drugiego pliku(PLIK_WLASCIWY__DRON_KORPUS) współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool Dron::Oblicz_i_Zapisz_WspGlbKorpusu() const
{
    std::ifstream  Plik_BrylaWzorcowa(KorpusDrona.WezNazwePliku_BrylaWzorcowa());    
    if (!(OtworzonoPlik(Plik_BrylaWzorcowa, KorpusDrona.WezNazwePliku_BrylaWzorcowa()))) {
        return false;
    }  
    assert(Plik_BrylaWzorcowa.good());

    std::ofstream  Plik_KorpusuDrona(KorpusDrona.WezNazwePliku_BrylaFinalna());
    Wektor3D BrylaWzorcowaWktr3D;
    while(OtworzonoPlik(Plik_KorpusuDrona, KorpusDrona.WezNazwePliku_BrylaFinalna())) //Dopoki udaje się otwierać plik
    {
        assert(Plik_KorpusuDrona.good());        
        for(unsigned int LicznikWierzcholkow = 0;LicznikWierzcholkow<ILOSC_WIERZ_LINII_TWORZACEJ;++LicznikWierzcholkow){
            if(!(Plik_BrylaWzorcowa >> BrylaWzorcowaWktr3D))//Nie udało się wczytać 
            {
                if(Plik_BrylaWzorcowa.fail()){
                    Plik_BrylaWzorcowa.close();
                    return true;
                }
                else{
                    assert(!Plik_KorpusuDrona.fail());        
                    return false;            
                }
            }
            ObrocWzgledemOsiOZ(KatOrientacji_stopnie, BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = KorpusDrona.Skaluj(BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = KorpusDrona.TransfDoUklWspRodzica(BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = TransfDoUklWspRodzica(BrylaWzorcowaWktr3D);
            Plik_KorpusuDrona << BrylaWzorcowaWktr3D;
            assert(LicznikWierzcholkow== ILOSC_WIERZ_LINII_TWORZACEJ-1 || !Plik_BrylaWzorcowa.fail());
        }
        Plik_KorpusuDrona <<std::endl;
    }
    return false;
}

/*!
 *  MEtoda prywatna klasy Dron.Czyta z pliku wejściowego(BRYŁA_WZORCOWA) współrzędne wierzchołków bryły wzorcowej 
*korpusu(GRaniastoslupa), dokonuje  ich transformacji (skalowanie, translacja z układu bryły
   wzorcowej do układu drona i translacja z układu współrzednych drona do układu współrzednych scena)
 *  Zapisuje do drugiego pliku(PLIK_WLASCIWY__DRON_ROTOR) współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  
 *  \param[in] - Referencja do obiektu klasy Graniastoslup, który przechowuje wszystkie informacje o danym Rotorze
 * 
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool Dron::Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup6& Rotor) const
{
    std::ifstream  Plik_BrylaWzorcowa(Rotor.WezNazwePliku_BrylaWzorcowa());    
    if (!(OtworzonoPlik(Plik_BrylaWzorcowa, Rotor.WezNazwePliku_BrylaWzorcowa()))) return false;
    assert(Plik_BrylaWzorcowa.good());

    std::ofstream  Plik_RotorDrona(Rotor.WezNazwePliku_BrylaFinalna());
    Wektor3D BrylaWzorcowaWktr3D;
    while(OtworzonoPlik(Plik_RotorDrona, Rotor.WezNazwePliku_BrylaFinalna())) //Dopoki udaje się otwierać plik
    {
        assert(Plik_RotorDrona.good());        
        for(unsigned int LicznikWierzcholkow = 0;LicznikWierzcholkow<ILOSC_WIERZ_LINII_TWORZACEJ;++LicznikWierzcholkow){
            if(!(Plik_BrylaWzorcowa >> BrylaWzorcowaWktr3D))//Nie udało się wczytać 
            {
                if(Plik_BrylaWzorcowa.fail()){
                    Plik_BrylaWzorcowa.close();
                    return true;
                }
                else{
                    assert(!Plik_RotorDrona.fail());        
                    return false;            
                }
            }
            ObrocWzgledemOsiOZ(Rotor.WezKatOrientacji_stopnie(), BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = Rotor.Skaluj(BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = Rotor.TransfDoUklWspRodzica(BrylaWzorcowaWktr3D);
            ObrocWzgledemOsiOZ(KatOrientacji_stopnie, BrylaWzorcowaWktr3D);
            BrylaWzorcowaWktr3D = TransfDoUklWspRodzica(BrylaWzorcowaWktr3D);
            Plik_RotorDrona << BrylaWzorcowaWktr3D;
            assert(LicznikWierzcholkow== ILOSC_WIERZ_LINII_TWORZACEJ-1 || !Plik_BrylaWzorcowa.fail());
        }
        Plik_RotorDrona <<std::endl;
    }
    return false;
}

/*!
* Transformacja ta relizuje przejście z układu wspórzednych drona do układu
* współrzędnych Scena 
*
* \param[in] Wierz - stała referencja do obiektu klasy Wektor3D, który zawiera informacje 
* o 3 współrzędnych: x, y i z - Wierzchołka transformowanego.
* 
* \return Zwraca przetransformowany Wierzchołek z układu lokalnego drona do układu lokalnego Sceny.
*/
Wektor3D Dron::TransfDoUklWspRodzica(const Wektor3D& Wierz) const
{
    Wektor3D Wktr3DTransakcji = Wierz + Polozenie;
    return Wktr3DTransakcji;
}

/*!
* Metoda wykonuje zmiane orientacji Drona
*
* \retval true jeśli operacja się powiedzie 
* \retval false jeśli NIe udało się zrealizować zmiany połozenia drona i zapisu do pliku
* 
*/
bool Dron::WykonajZmianeOrientacji(double KatOrientacjiDrona_stopnie, PzG::LaczeDoGNUPlota& Lacze)
{
    for (;KatOrientacjiDrona_stopnie>0 ? KatOrientacji_stopnie <= KatOrientacjiDrona_stopnie: KatOrientacji_stopnie >= KatOrientacjiDrona_stopnie;
    KatOrientacjiDrona_stopnie>0 ? KatOrientacji_stopnie += 5 : KatOrientacji_stopnie  -= 5) {
        ObrotRotorow();    
        if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;           
        usleep(100000);
        Lacze.Rysuj();
  }
  KatOrientacji_stopnie -= 5;
  return true;
}

bool Dron::WydluzTraseLotu(const Dron& Dn,InterfejsUzytkownika &IU, std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze,
 double DlugoscWydluzeniaTrasy)
{   
    IU.ZmienDlugoscLotuPoziomego(IU.WezDlugoscLotuPoziomego() +DlugoscWydluzeniaTrasy);
    Wektor3D PunktSciezki ={IU.WezDlugoscLotuPoziomego(),0,0};

  ObrocWzgledemOsiOZ(IU.WezKierunekLotu_Stopnie(), PunktSciezki);
  Wektor3D WktrTym = PunktySciezki[1];
  PunktSciezki = PunktSciezki + WktrTym; // Przemieszczamy nasza stworzona prosta do punktu najwyzszego zaplanowanej trasy 
  PunktySciezki[2] = PunktSciezki;    
  PunktSciezki[Z] = PunktSciezki[Z]-IU.WezDlugoscLotuPionowego();
  PunktySciezki[3] = PunktSciezki;

    /*Jeśli Zadana trasa przez użytkownika wykracza poza wyznaczony teren działania Drona*/  
  if(!((PunktySciezki[3][X]-((Dn.WezKorpusDrona().WezSkale()[X])/2)>0)&&(PunktySciezki[3][X]+((Dn.WezKorpusDrona().WezSkale()[X])/2)<IU.WezWyznaczonaStrefaDzialania(X)))
  ||!((PunktySciezki[3][Y]-((Dn.WezKorpusDrona().WezSkale()[Y])/2)>0)&&(PunktySciezki[3][Y]+((Dn.WezKorpusDrona().WezSkale()[Y])/2)<IU.WezWyznaczonaStrefaDzialania(Y)))){
      std::cout<<std::endl<<"Niestety wyznaczona Strefa dzialania Drona nie pozwala na zadana operacje lotu !!!"<<std::endl<<std::endl;
      std::cout<<"Dron zostaje cofniety do pozycji poczatkowej"<<std::endl;
      return WykonajPoziomyLot(IU.WezDlugoscLotuPoziomego()-DlugoscWydluzeniaTrasy,180+IU.WezKierunekLotu_Stopnie(),Lacze);
  }

   if(!(ZapiszDoPlikuTraseLotu(PunktySciezki))){
    return false;
   }

    Lacze.Rysuj();

    return WykonajPoziomyLot(DlugoscWydluzeniaTrasy,IU.WezKierunekLotu_Stopnie(),Lacze);
}
/*!
* Oblicza na podstawie parametrów zadanych przez użytkownika( tz KatSKretu_stopnie, Dlugosc LotuPoziomego i Dlugosc Lotu Pionowego) trase przelotu drona i
* Dodaje punkty tej trasy do konternera sekwencyjnego vector
*
* \param[in] PunktySciezki - Referencja do kontenera sekwencyjnego( vector), przechowuje on punkty planowanej ściezki 
* \param[in] PunktSciezki - Referncja do obiektu klasy Wektor3D, który zawiera infromacje na temat Jednego punktu ścieżki ( tz współrzedne trójwymiarowe)
* \param[in] IU - Referencja do obiektu klasy InterfejsUzytkownika, zawierający dane na temat planowanego lotu drona podane przez użytkownika
*/

void Dron::ObliczIDodajPunktySciezki(std::vector<Wektor3D>& PunktySciezki, Wektor3D &PunktSciezki,const InterfejsUzytkownika &IU)
{

  PunktSciezki = Polozenie; //Polozenie poczatkowe Drona 1 
  PunktySciezki.push_back(PunktSciezki);

  PunktSciezki[Z] = IU.WezDlugoscLotuPionowego(); // Drguie położenie drona po wystartowaniu z polozenia poczatkowego, tutaj mamy ustawiona stała wysokość lotu równa 80 
  PunktySciezki.push_back(PunktSciezki);

  Wektor3D WktrTym = PunktSciezki;
  PunktSciezki={IU.WezDlugoscLotuPoziomego(),0,0};
  ObrocWzgledemOsiOZ(IU.WezKierunekLotu_Stopnie(), PunktSciezki);
  PunktSciezki = PunktSciezki + WktrTym; // Przemieszczamy nasza stworzona prosta do punktu najwyzszego zaplanowanej trasy 
  PunktySciezki.push_back(PunktSciezki);
  PunktSciezki[Z] = PunktSciezki[Z]-IU.WezDlugoscLotuPionowego();
  PunktySciezki.push_back(PunktSciezki);

}
bool Dron::ZapiszDoPlikuTraseLotu(std::vector<Wektor3D>& PunktySciezki)
{
std::ofstream  StrmWy(PLIK_TRASY_PRZELOTU);

  if (!StrmWy.is_open()) {
    std::cerr << std::endl
	 << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << std::endl
	 << std::endl;
    return false;
  }
  std::vector<Wektor3D>::iterator Adres_PunktuSciezki = PunktySciezki.begin();  
  for(Adres_PunktuSciezki = PunktySciezki.begin(); Adres_PunktuSciezki != PunktySciezki.end(); ++Adres_PunktuSciezki)
  {
  StrmWy << *Adres_PunktuSciezki;
  }

  return !StrmWy.fail();
}
/*!
* Metoda planuje ścieżke lotu drona zadana przez użytkowanika, rysuje ją  w programie GNUPLOT i zapisuje do kontenera sekwencyjnego vector główne Punkty ścieżki trasy
*
* \param[in] IU - Referencja do obiektu klasy InterfejsUzytkownika, zawierający dane na temat planowanego lotu drona podane przez użytkownika
* \param[in] PunktySciezki - Referencja do kontenera sekwencyjnego( vector), przechowuje on punkty planowanej ściezki 
* \param[in] Lacze - Referencja do klasy LaczeDoGNUPLOTA, która pozwala na połączenie z programem GNUPLOT
*
* \retval true - Udało się otworzyć plik i zapisać do niego odpowiednie dane trasy przelotu lub jeśli użytkownikowi zadana ścieżka będzie odpowiadać 
* \retval false - Jeśli operacja zapisu do pliku nie powiedzie się lub jeśli użtykownik zada taką trase która nie będzie pozwalac na lot dronem
* (tz zada taką trase która będzie poza wyznaczonym terenem działania drona) lub jeśli użytkownikowi jednak nie będze odpowiadać zadana przez niego trasa.
*/
bool Dron::PlanujPoczatkowaSciezke(const InterfejsUzytkownika &IU, std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze)
{
  Wektor3D PunktSciezki;
  ObliczIDodajPunktySciezki(PunktySciezki, PunktSciezki,IU);
  
  /*Jeśli Zadana trasa przez użytkownika wykracza poza wyznaczony teren działania Drona*/  
  if(!((PunktSciezki[X]>0)&&(PunktSciezki[X]<IU.WezWyznaczonaStrefaDzialania(X)))||!((PunktSciezki[Y]>0)&&(PunktSciezki[Y]<IU.WezWyznaczonaStrefaDzialania(Y)))){
      std::cout<<std::endl<<"Niestety wyznaczona Strefa dzialania Drona nie pozwala na zadana operacje lotu !!!"<<std::endl<<std::endl;
      return false;
  }

  if(!(ZapiszDoPlikuTraseLotu(PunktySciezki)))
    return false;

  std::cout<<std::endl<<"Rysuje zaplanowana sciezke lotu ..." <<std::endl<<std::endl;  
  Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
  Lacze.Rysuj();
  
  if(IU.ZadajPytanieCzyTrasaPrzelotuJestOdpowiednia())
    return true;
   else
    return false;

  return true;
 }

/*!
*  Metoda Wykonuje Lot Drona, według zadanych parametrów
* 
* \param[in] Kierunek_WekJednostkowy - Referecnja do obiektu klasy Wektor3D, który zawiera dane o  Wektorze jednostkowym
* \param[in] DlugoscLotu - Wartość Dlugosci danego lotu
* \param[in] Lacze - Referencja do obiektu klasy LaczeDoGNUPLOTA, która pozwala na połączenie z programem GNUPLOT
*
* \pre Referencja Kierunek_WekJednostkowy do obiektu klasy Wektor3D musi zawierać dane tylko i wyłącznie o wektorze jednostkowym, nie może to być inny wektor niż
* Wektor jednostkowy
* \post Przeniesiony do odpowiednio zadanego miejsca dron, w między czasie wyświetla się w programie gnuplot animacja lotu
*
* \retval true - gdy operacja powiedzie się,
* \retval false - w przypadku przeciwnym.
*                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
*                 z których korzysta ta funkcja,
*                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
*/
bool Dron::WykonajLot(const Wektor3D &Kierunek_WekJednostkowy, double DlugoscLotu, PzG::LaczeDoGNUPlota& Lacze)
{
    //assert(fabs(Kierunek_WekJednostkowy.Dlugosc()-1)<BLAD_OBLICZEN);
    Wektor3D KierunekLotu_PojKrok = Kierunek_WekJednostkowy * DlugoscPojedynczegoKroku;
    Wektor3D PolozenieStartowe = Polozenie;
    double PozostalaDlugoscLotu = DlugoscLotu;

    PozostalaDlugoscLotu -= DlugoscPojedynczegoKroku;
    while(PozostalaDlugoscLotu > 0)
    {
 
        PrzesunDrona_WekTrans(KierunekLotu_PojKrok);    
        ObrotRotorow();    
        if(!Oblicz_i_Zapisz_WspGlbDrona()) return false;
        usleep(100000); //0.1s
        Lacze.Rysuj();
        PozostalaDlugoscLotu -= DlugoscPojedynczegoKroku;
    }
    ZmienPolozenieDrona(PolozenieStartowe + Kierunek_WekJednostkowy*DlugoscLotu);
    if(!Oblicz_i_Zapisz_WspGlbDrona()) return false;
    usleep(100000); //0.1s
    Lacze.Rysuj();
    return true;
}

/*!
* Metoda ustawia odpowiednie parametry lotu poziomego, operując na wektorach i wywołuje metode WykonajLot \link Dron.hh::WykonajLot WykonajLot \endlink,
* która wykonuje odpowiednio zadany lot
*
* \param[in] DlugoscLotu - Wartość Dlugosci Lotu
* \param[in] KatOrientacjiDrona_stopnie -Wartość Kata orientacji Drona w stopniach 
* \param[in] Lacze - Referencja do obiektu klasy LaczeDoGNUPLOTA, która pozwala na połączenie z programem GNUPLOT
* \retval true - gdy operacja powiedzie się,
* \retval false - w przypadku przeciwnym.
*                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
*                 z których korzysta ta funkcja,
*                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
*/
bool Dron::WykonajPoziomyLot(double DlugoscLotu,double KatOrientacjiDrona_stopnie, PzG::LaczeDoGNUPlota& Lacze)
{
    assert(DlugoscLotu>0);
    Wektor3D KierLotu = {1,0,0};

    KatOrientacji_stopnie = KatOrientacjiDrona_stopnie;
    ObrocWzgledemOsiOZ(KatOrientacji_stopnie, KierLotu);
    if(!WykonajLot(KierLotu, DlugoscLotu, Lacze)) return false;
    return true;
}

/*!
* Metoda ustawia odpowiednie parametry lotu pionowego(albo lot w góre albo lot w dół), operując na wektorze i wywołuje metodę 
* \link Dron.hh::WykonajLot WykonajLot \endlink
*
** \param[in] DlugoscLotu - Wartość Dlugosci Lotu
* \retval true - gdy operacja powiedzie się,
* \retval false - w przypadku przeciwnym.
*                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
*                 z których korzysta ta funkcja,
*                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
*/
bool Dron::WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota& Lacze)
{
    Wektor3D KierLotu={0,0, (DlugoscLotu > 0 ? 1.0 : -1.0)};
    
     if(!WykonajLot(KierLotu, fabs(DlugoscLotu), Lacze)) return false;
     if(KierLotu[Z]==-1.0){//jeśli skończył się lot w dół to usuwamy ściezke lotu
        std::cin.ignore(10000,'\n');
        Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        Lacze.Rysuj();
     }
    return true;
}

/*!
*  Metoda Dodaje Kat do KataOrientacji Rotora, co powoduje jego obrot wokół własnej osi w każdej kolejnej animacji 
*/
void Dron::ObrotRotorow()
{
 RotorDrona[0].DodajStopienSkokuRotora(SKOK_OBROTU_ROTOROW_stopnie);
 RotorDrona[1].OdejmijStopienSkokuRotora(SKOK_OBROTU_ROTOROW_stopnie);
 RotorDrona[2].OdejmijStopienSkokuRotora(SKOK_OBROTU_ROTOROW_stopnie);
 RotorDrona[3].DodajStopienSkokuRotora(SKOK_OBROTU_ROTOROW_stopnie);
}

/*Prostokat jest uznawany jako rzut przeszkody na plaszczyzne 2D a kolo jest uznawane jako rzut drona  
na plaszczyzne 2D(to koło ma promień połowy długości przekątnej korpusu drona)*/
 bool Dron::CzyZajete(const Dron& Dn)
 {
    Wektor2D WierzcholkiProstokata[ILOSC_WIERZ_PROSTOKATA];

     WierzcholkiProstokata[A] =  {Polozenie[X]-(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] - (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[B] = {Polozenie[X]+(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] - (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[C] = {Polozenie[X]+(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] + (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[D] = {Polozenie[X]-(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] + (KorpusDrona.WezSkale()[Y]/2)};
        
    Wektor2D WierzcholekKorpusu = {Dn.WezPolozenieDrona()[X]+Dn.WezKorpusDrona().WezSkale()[X],Dn.WezPolozenieDrona()[Y]+Dn.WezKorpusDrona().WezSkale()[Y]};
    Wektor2D PolowaPrzekatnejKorpusu = {WierzcholekKorpusu[X]-Dn.WezPolozenieDrona()[X], WierzcholekKorpusu[Y]-Dn.WezPolozenieDrona()[Y]};
     double PromienKola = PolowaPrzekatnejKorpusu.dlugosc()+DODATKOWA_DLUGOSC;     
    
    /*Najpierw Sprawdzmy czy połozenie koła nie jest przypadkiem w środku prostokąta*/
    if((WierzcholkiProstokata[D][X]<Dn.WezPolozenieDrona()[X])&&(WierzcholkiProstokata[A][X]<Dn.WezPolozenieDrona()[X])
    &&(WierzcholkiProstokata[B][X]>Dn.WezPolozenieDrona()[X])&&(WierzcholkiProstokata[C][X]>Dn.WezPolozenieDrona()[X])
    &&(WierzcholkiProstokata[A][Y]<Dn.WezPolozenieDrona()[Y])&&(WierzcholkiProstokata[B][Y]<Dn.WezPolozenieDrona()[Y])
    &&(WierzcholkiProstokata[D][Y]>Dn.WezPolozenieDrona()[Y])&&(WierzcholkiProstokata[C][Y]>Dn.WezPolozenieDrona()[Y])){//Polozenie kola jest w srodku prostokata
        return true;
    }
    else if((((Dn.WezPolozenieDrona()[X]+PromienKola)>=WierzcholkiProstokata[A][X])&&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[A][Y])
    &&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[A][X])&&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[D][Y]))||
    (((Dn.WezPolozenieDrona()[X]-PromienKola)<=WierzcholkiProstokata[B][X])&&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[B][Y])
    &&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[B][X])&&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[C][Y]))||
    (((Dn.WezPolozenieDrona()[Y]-PromienKola)<=WierzcholkiProstokata[C][Y])&&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[D][X])
    &&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[C][Y])&&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[C][X]))||
    (((Dn.WezPolozenieDrona()[Y]+PromienKola)>=WierzcholkiProstokata[A][Y])&&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[A][X])
    &&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[A][Y])&&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[B][X]))){ //jeśli położenie drona nie jest w srodku prostokata to może przecinac którys z bokow prostokata
        return true; //Ten warunek zrobiłem w ten sposb ze sprawdzam czy polozenie drona powiekszone o jego promien nie znajdzuje sie przypadkiem w srodku prostokata
    }          
    else //jeśli żaden punkt drona nie pokrywa się z przeszkodą to zwracamy false, pwoierzchnia do ladowania nie jest zajeta
        return false;
  return false;   
 }

 double Dron::ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const
 {
     Wektor2D WierzcholkiProstokata[ILOSC_WIERZ_PROSTOKATA];

    WierzcholkiProstokata[A] =  {Polozenie[X]-(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] - (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[B] = {Polozenie[X]+(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] - (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[C] = {Polozenie[X]+(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] + (KorpusDrona.WezSkale()[Y]/2)};
     WierzcholkiProstokata[D] = {Polozenie[X]-(KorpusDrona.WezSkale()[X]/2), Polozenie[Y] + (KorpusDrona.WezSkale()[Y]/2)};

    Wektor2D WierzcholekKorpusu = {Dn.WezPolozenieDrona()[X]+Dn.WezKorpusDrona().WezSkale()[X],Dn.WezPolozenieDrona()[Y]+Dn.WezKorpusDrona().WezSkale()[Y]};
    Wektor2D PolowaPrzekatnejKorpusu = {WierzcholekKorpusu[X]-Dn.WezPolozenieDrona()[X], WierzcholekKorpusu[Y]-Dn.WezPolozenieDrona()[Y]};
     double PromienKola = PolowaPrzekatnejKorpusu.dlugosc()+DODATKOWA_DLUGOSC;

    Wektor2D WktrTym;
     /*Najpierw Sprawdzmy czy połozenie koła nie jest przypadkiem w środku prostokąta*/
    if((WierzcholkiProstokata[D][X]<Dn.WezPolozenieDrona()[X])&&(WierzcholkiProstokata[A][X]<Dn.WezPolozenieDrona()[X])
    &&(WierzcholkiProstokata[B][X]>Dn.WezPolozenieDrona()[X])&&(WierzcholkiProstokata[C][X]>Dn.WezPolozenieDrona()[X])
    &&(WierzcholkiProstokata[A][Y]<Dn.WezPolozenieDrona()[Y])&&(WierzcholkiProstokata[B][Y]<Dn.WezPolozenieDrona()[Y])
    &&(WierzcholkiProstokata[D][Y]>Dn.WezPolozenieDrona()[Y])&&(WierzcholkiProstokata[C][Y]>Dn.WezPolozenieDrona()[Y])){//Polozenie kola jest w srodku prostokata
        /*Tworzymy wektor Polozenia Drona  z każdym wierzchołkiem prostokąta i szukamy najdluzszej odległosci i wybieramy ja jako Dlugosc wyzdluzenia trasy*/
        std::valarray<double> DlugosciWektorow(ILOSC_WIERZ_PROSTOKATA);
        for(unsigned int Ind = 0; Ind<ILOSC_WIERZ_PROSTOKATA; ++Ind){
            WktrTym = {Dn.WezPolozenieDrona()[X]-WierzcholkiProstokata[Ind][X], Dn.WezPolozenieDrona()[Y]-WierzcholkiProstokata[Ind][Y]};
            DlugosciWektorow[Ind] = WktrTym.dlugosc();
        }
        /*Zwracamy najdluzszy wektor i to bedzie nasze wydluzenie trasy*/
        return DlugosciWektorow.max();
    }

    WktrTym = {WierzcholkiProstokata[A][X]-WierzcholkiProstokata[C][X], WierzcholkiProstokata[A][Y]-WierzcholkiProstokata[C][Y]};
    double DlugoscPrzekatnejProstokata = WktrTym.dlugosc();

    /*Jesli dron nie jest w srodku przeszkody no to szukamy jego pozycji na przecieciu któregos z bokow prostokata*/
    //Przeciecie z odcinkiem AD
    if((((Dn.WezPolozenieDrona()[X]+PromienKola)>=WierzcholkiProstokata[A][X])&&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[A][Y])
     &&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[A][X])&&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[D][Y]))){
        return PrzeciecieDronaZOdcinkiemAD(DlugoscPrzekatnejProstokata, PunktySciezki[0],WierzcholkiProstokata,PromienKola);            
     }
     //Przeciecie z odcinkiem BC
     if((((Dn.WezPolozenieDrona()[X]-PromienKola)<=WierzcholkiProstokata[B][X])&&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[B][Y])
    &&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[B][X])&&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[C][Y]))) {
        return PrzeciecieDronaZOdcinkiemBC(DlugoscPrzekatnejProstokata, PunktySciezki[0],WierzcholkiProstokata,PromienKola);            
    }
    //Przeciecie z odcinkiem DC
    if((((Dn.WezPolozenieDrona()[Y]-PromienKola)<=WierzcholkiProstokata[C][Y])&&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[D][X])
    &&((Dn.WezPolozenieDrona()[Y])>=WierzcholkiProstokata[C][Y])&&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[C][X]))) {
        return PrzeciecieDronaZOdcinkiemDC(DlugoscPrzekatnejProstokata, PunktySciezki[0],WierzcholkiProstokata,PromienKola);            
    }
    //Przeciecie z odcinkiem AB
    if((((Dn.WezPolozenieDrona()[Y]+PromienKola)>=WierzcholkiProstokata[A][Y])&&((Dn.WezPolozenieDrona()[X])>=WierzcholkiProstokata[A][X])
    &&((Dn.WezPolozenieDrona()[Y])<=WierzcholkiProstokata[A][Y])&&((Dn.WezPolozenieDrona()[X])<=WierzcholkiProstokata[B][X]))){
        return PrzeciecieDronaZOdcinkiemAB(DlugoscPrzekatnejProstokata, PunktySciezki[0],WierzcholkiProstokata,PromienKola);            
    }
    return 0.0;
 }