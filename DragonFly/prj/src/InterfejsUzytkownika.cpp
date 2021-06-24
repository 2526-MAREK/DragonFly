#include "InterfejsUzytkownika.hh"

/*!
 * \file 
 * \brief Definicje metod klasy InterfejsUzytkownika
 *
 *  Plik zawiera definicje metod klasy InterfejsUzytkownika. Klasa ta została stworzona z głównym przeznaczeniem do komunikacji z użytkownkiem.
 */

void InterfejsUzytkownika::CzyszczenieStrumieniaWejsciowego(std::istream &StrmWe) const
{
     char ch;

    StrmWe.clear(); //czyścimy stan strumienia z błędnych bitów aby obiekt StrmWe klasy istream mógł prawidłowo "wyczyśćic" strumien wejściowy
    while( (ch = StrmWe.get()) != '\n'){
        continue; //mogłoby się obyć bez continue 
  }
}

int  InterfejsUzytkownika::WyborAktywnegoDrona(Scena& Sc)
{
    std::cout<<"Wybor aktywnego drona"<<std::endl<<std::endl;

        if(Sc.WezDrona(0).CzyTenDronJestAktywny()){
        std::cout<<" 1 - Polozenie (x,y):  "<<Sc.WezDrona(0).WezPolozenieDrona()[X]<<" "<<Sc.WezDrona(0).WezPolozenieDrona()[Y]<<"   <-- Dron aktywny"<<std::endl;
        std::cout<<" 2 - Polozenie (x,y):  "<<Sc.WezDrona(1).WezPolozenieDrona()[X]<<" "<<Sc.WezDrona(1).WezPolozenieDrona()[Y]<<std::endl<<std::endl;
        }
        if(Sc.WezDrona(1).CzyTenDronJestAktywny()){
        std::cout<<" 1 - Polozenie (x,y):  "<<Sc.WezDrona(0).WezPolozenieDrona()[X]<<" "<<Sc.WezDrona(0).WezPolozenieDrona()[Y]<<std::endl;
        std::cout<<" 2 - Polozenie (x,y):  "<<Sc.WezDrona(1).WezPolozenieDrona()[X]<<" "<<Sc.WezDrona(1).WezPolozenieDrona()[Y]<<"   <-- Dron aktywny"<<std::endl<<std::endl;
        }

    std::cout<<"Wprowadz numer aktywnego drona> ";
    int DronAktywny;
    std::cin>>DronAktywny;

  std::shared_ptr<Dron> WDronAktywny = std::make_shared<Dron>();
  std::shared_ptr<Dron> WDronNieAktywny = std::make_shared<Dron>();
    if(DronAktywny ==1)
    {
      if((Sc.WezAktywnegoDrona().WezIndeksDrona()==1)) 
      {
      }// nie rob nic ten sam dron byl przed chwila aktywny
      else 
      {
        Sc.WezDrona(0).WlaczAktywnoscDrona();
        Sc.WezDrona(1).WylaczAktywnoscDrona();
        *WDronAktywny = Sc.WezAktywnegoDrona();
        *WDronNieAktywny = Sc.WezNieAktywnegoDrona();
        Sc.DodajDronaNaListeDronowIDodajNieAktywnegoDronaNaListePrzeszkod(WDronAktywny , WDronNieAktywny);
      } 

    }
    else if(DronAktywny ==2)
    {
      if((Sc.WezAktywnegoDrona().WezIndeksDrona()==2)) {

      }// nie rob nic ten sam dron byl przed chwila aktywny
      else 
      {
        Sc.WezDrona(1).WlaczAktywnoscDrona();
        Sc.WezDrona(0).WylaczAktywnoscDrona();
        *WDronAktywny = Sc.WezAktywnegoDrona();
        *WDronNieAktywny = Sc.WezNieAktywnegoDrona();
        Sc.DodajDronaNaListeDronowIDodajNieAktywnegoDronaNaListePrzeszkod(WDronAktywny , WDronNieAktywny);
      } 

    }
    return 0;
}

void InterfejsUzytkownika::WyswietlPolozenieAktywnegoDrona(const Scena& Sc)
{
    std::cout<<std::endl<<"Polozenie Drona aktywnego (x,y): "<<Sc.WezAktywnegoDrona().WezPolozenieDrona()[X]<<" "
    <<Sc.WezAktywnegoDrona().WezPolozenieDrona()[Y]<<std::endl<<std::endl;
}
int InterfejsUzytkownika::ZadajParametryPrzelotu(Scena &Sc, PzG::LaczeDoGNUPlota& Lacze)
{
    DlugoscLotuPionowego = 80; 

  std::cout<<"Podaj kierunek lotu (kat w stopniach)> ";
  std::cin>>KierunekLotu_Stopnie;
  std::cout<<"Podaj dlugosc lotu> ";
  std::cin>>DlugoscLotuPoziomego;

  return Sc.AnimacjaLotuDrona(Lacze, *this);

}

void InterfejsUzytkownika::WyswietlMenu()
{
  std::cout<<"a - wybierz aktywnego drona"<<std::endl;
  std::cout<<"p - zadaj parametry przelotu"<<std::endl;
  std::cout<<"d - dodaj element powierzchni "<<std::endl;
  std::cout<<"u - usun element powierzchni "<<std::endl;
  std::cout<<"m - wyswietl menu"<<std::endl<<std::endl;
  std::cout<<"k - koniec dzialania programu"<<std::endl<<std::endl;

  std::cout<<"Aktualna ilosc obiektow Wektor3D: "<<Wektor3D::WezIloscAktualnaWektorow()<<std::endl;
  std::cout<<"  Laczna ilosc obiektow Wektor3D: "<<Wektor3D::WezIloscOgolnaWektorow()<<std::endl<<std::endl;

  std::cout<<"Twoj wybor? (m-menu) > ";
}

int  InterfejsUzytkownika::Menu(Scena &Sc)
{
  Sc.SprawdzMaksymalnaIloscPrzeszkodOsiagnietaWProgramie();
  WyswietlPolozenieAktywnegoDrona(Sc);

  WyswietlMenu();

  char wybor;
  int koniec;
  while(std::cin>>wybor){
    std::cout<<std::endl;
    switch(wybor)
    {
      case 'a':
      {
        koniec = WyborAktywnegoDrona(Sc);
        break;
      }
      case 'p':
      {
        koniec = ZadajParametryPrzelotu(Sc, Sc.UzyjLacza());
        break;
      }
      case 'd':
      {
          koniec = DodajElementPowierzchni(Sc);
        break;
      }
      case 'u':
      {
        if((Sc.WezListe().size())>0)
          koniec = UsunElementPowierzchni(Sc);
        else 
          std::cout<<"Na Scenie i liście nie ma elemntów do usunięcia !!!"<<std::endl;            
        break;
      }
      case 'm':
      {
        koniec = Menu(Sc);
        break;
      }
      case 'k':
      {
        if(Sc.WezMaksPrzeszkodOsiagnieteWProgramie()>4)
          Sc.UsunNadmiarowePlikiPrzeskod();
        std::cout<<"Koniec dzialania programu Dragonfly"<<std::endl;
        exit(0);
        break;  
      }
      default:
      {
        std::cout<<"Proszę wybrać odpowiednia litere: "<<std::endl<<std::endl;
      koniec = Menu(Sc);
      }
    }
    if(koniec == -1) std::cout<<" Cos poszlo nie tak !"<<std::endl<<std::endl;
    Sc.SprawdzMaksymalnaIloscPrzeszkodOsiagnietaWProgramie();
    WyswietlPolozenieAktywnegoDrona(Sc);
    WyswietlMenu();
  }
  CzyszczenieStrumieniaWejsciowego(std::cin);
  koniec = Menu(Sc);
  return koniec;
}

/* Funkcje pomocnicza,Zadaje pytanie użytkownikowi czy trasa przleotu jest odpwoeidnia*/
bool InterfejsUzytkownika::ZadajPytanieCzyTrasaPrzelotuJestOdpowiednia() const
{
  std::cout<<"Czy zadana trasa przelotu jest odpowiednia?"<<std::endl;
  std::cout<<"t - Tak"<<std::endl; 
  std::cout<<"n - Nie"<<std::endl; 
  std::cout<<"Twoj Wybor> ";

  char ch;
  std::cin>>ch;
  if(ch == 't') 
    return true; 
  if(ch == 'n') 
    return false;
  else{
    std::cout<<"Wybrano nie wlasciwa opcje !!!"<<std::endl<<std::endl;  
    return false;  
  }
}

int InterfejsUzytkownika::Wczytaj() const
{ 
    int wybor;  
    while(!(std::cin>>wybor)){//Nie udało się wczytać                                                                                                                     
        CzyszczenieStrumieniaWejsciowego(std::cin);
        KomunikatOBledzieTYPint();
         std::cout<<std::endl<<"Wprowadz numer typu elementu> ";
    }
    return wybor;
}
void InterfejsUzytkownika::WczytajSKALE(Wektor3D& SkalaElementow) const
{
  while(!(std::cin>>SkalaElementow)){//Nie udało się wczytać                                                                                                                     
        CzyszczenieStrumieniaWejsciowego(std::cin);
        KomunikatOBledzieTYPint();
        std::cout<<std::endl<<"Wprowadz skale: OX OY OZ> ";
    }
}
void InterfejsUzytkownika::WczytajWSP(Wektor3D& WspolrzedneElementu) const
{
  while(!(std::cin>>WspolrzedneElementu[X]>>WspolrzedneElementu[Y])){//Nie udało się wczytać                                                                                                                     
        CzyszczenieStrumieniaWejsciowego(std::cin);
        KomunikatOBledzieTYPint();
        std::cout<<std::endl<<"Wprowadz wspolrzedne: x y> ";       
    }
}

void InterfejsUzytkownika::WyswietlRodzajePowierzchni() const 
{
  std::cout<<"Wybierz rodzaj powierzchniowego elementu "<<std::endl<<std::endl;
  std::cout<<"1 - Gora z ostrym szczytem"<<std::endl;
  std::cout<<"2 - Gora z grania"<<std::endl;
  std::cout<<"3 - Plaskowyz"<<std::endl<<std::endl;
  std::cout<<"Wprowadz numer typu elementu> ";
}
int InterfejsUzytkownika::DodajElementPowierzchni(Scena& Sc) const
{
  WyswietlRodzajePowierzchni();
  int wybor = Wczytaj();
   if(!(wybor>=1)&&(wybor<=3))
    {
      std::cout<<"Prosze wybrac liczbe z przedzialu 1-3 !!!"<<std::endl<<std::endl;
      wybor = Wczytaj();
    }

  std::cout<<std::endl<<"Podaj skale wzdluz kolejnych osi OX, OY, OZ."<<std::endl;
  std::cout<<"Wprowadz skale: OX OY OZ> ";
  Wektor3D SkalaElementow;
  WczytajSKALE(SkalaElementow);
  
  std::cout<<std::endl<<"Podaj wspolrzedne srodka podstawy x,y."<<std::endl;
  std::cout<<"Wprowadz wspolrzedne: x y> ";
  Wektor3D WspolrzedneElementu;
  WczytajWSP(WspolrzedneElementu);

   /*Jeśli Zadana trasa przez użytkownika wykracza poza wyznaczony teren działania Drona*/  
  if(!(((WspolrzedneElementu[X]-SkalaElementow[X])>0)&&((WspolrzedneElementu[X]+SkalaElementow[X])<WezWyznaczonaStrefaDzialania(X)))||
  !(((WspolrzedneElementu[Y]-SkalaElementow[Y])>0)&&((WspolrzedneElementu[Y]+SkalaElementow[Y])<WezWyznaczonaStrefaDzialania(Y)))){
      std::cout<<std::endl<<"Niestety wyznaczona Strefa dzialania Drona nie pozwala na umiejscowienie przeszkody w tym miejscu !!!"<<std::endl<<std::endl;
      return -1;
  }
  
  switch(wybor)
  {
    case 1:
    {
      if(!Sc.UtworzGoraZOstrymSzczytemIDodajGoNaListe(SkalaElementow, WspolrzedneElementu))
        return -1;
      break;
    }
    case 2:
    {
      if(!Sc.UtworzGoraZDlugaGraniaIDodajGoNaListe(SkalaElementow, WspolrzedneElementu))
        return -1;
      break;
    }
    case 3:
    {
      if(!Sc.UtworzPlaskowyzIDodajGoNaListe(SkalaElementow, WspolrzedneElementu))
        return -1;
      break;
    }
  }
  std::cout<<std::endl<<"Element został dodany do sceny."<<std::endl;
  return 0;
}

int InterfejsUzytkownika::UsunElementPowierzchni(Scena& Sc) const
{
  WyswietlWszystkieAktywneElementyNaPowierzchni(Sc);
  long unsigned int wybor = Wczytaj();
   if(!(wybor>=1)&&(wybor<=Sc.WezListe().size()))
    {
      std::cout<<"Prosze wybrac liczbe z listy poniżej: !!!"<<std::endl<<std::endl;
      wybor = Wczytaj();
    }
    if(!Sc.UsunElementzZListyISceny(wybor-1))
      return -1;
    std::cout<<std::endl<<"Element zostal usuniety"<<std::endl<<std::endl;
  return 0;    
}
void InterfejsUzytkownika::WyswietlWszystkieAktywneElementyNaPowierzchni(Scena& Sc)const
{
  std::cout<<"Wybierz element powierzchni do usuniecia: "<<std::endl;
  int i = 1;
  for(const std::shared_ptr<BrylaGeometryczna>& Element : Sc.WezListe()){
    std::cout<<i<<" - ("<<Element->WezPolozeniePrzeszkody()[X]<<", "<<Element->WezPolozeniePrzeszkody()[Y]<<") "<<Element->NazwaPrzeszkody()<<std::endl;
    ++i;
  }
  std::cout<<std::endl<<"Podaj numer elementu> ";
}
