#include "GoraZDlugaGrania.hh"
#include "Dron.hh"


/*!
 * \file 
 * \brief Definicje metod i funkcji pomocniczych  klasy GoraZDlugaGRania
 *
 *  Plik zawiera definicje metod i funkcji pomocniczych  klasy GoraZDlugaGrania.
 */

/*! 
*  Konstruktor parametryczny z wartościami domyślnymi klasy GoraZDlugaGrania
*/
GoraZDlugaGrania::GoraZDlugaGrania(const std::string & s1, const std::string & s2,
                const Wektor3D & SkalaBrylaTym, const Wektor3D & PolozenieTym) : BrylaGeometryczna(s1,s2,SkalaBrylaTym),
                Polozenie(PolozenieTym)
{} 

/*!
 * Tworzy zapis wierzchołków bryły geometrycznej reprezentującej górę z
 * długą granią.
 *
 * \pre Plik wzorcowy zawiera zapis współrzędnych wierzchołków wzorcowego prostapadłościanu.
 *      Zapis ich jest zgodny z formatem pozwalającym poprawnie zwizualizować prostopadłościan
 *      przez program gnuplot.
 *
 * \retval true - plik z wierzcholkami nowej bryły reprezentującej górę z długą granią
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
 */
bool GoraZDlugaGrania::Tworz() const
{
    std::ifstream  StrmWej(WezNazwePliku_BrylaWzorcowa());
    std::ofstream  StrmWyj(WezNazwePliku_BrylaFinalna());     
    
    if (!(OtworzonoPlik(StrmWej, WezNazwePliku_BrylaWzorcowa()))) {
        return false;
    }  
    assert(StrmWej.good());  

    if (!(OtworzonoPlik(StrmWyj, WezNazwePliku_BrylaFinalna()))) {
        return false;
    }        
    assert(StrmWyj.good());  

    Wektor3D Wierz;
    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz) {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz) {
           StrmWej>>Wierz;
           if(NiePrawidlowoWczytano(StrmWej)) return false;
           if (Wierz[Z] > 0.5) { // Tutaj realizowana jest deformacja
	            if (Wierz[X] < 0) Wierz[X] = fabs(Wierz[X]);
            }
            Wierz = Skaluj(Wierz);
            Wierz = TransformujPolozenie(Wierz);
            StrmWyj <<Wierz;
            if(NiePrawidlowoZapisano(StrmWyj)) return false;
        }   
         StrmWyj<<std::endl;        
    }
    return !StrmWyj.fail();
} 

/*!
* Metoda pozwalająca usunąc bryłe, wypełniając jej plik zerami
*
* \post wypełniony plik wyjściowy z bryłą zerami
*
* \retval true - plik wypełniony zerami 
 *                 został zapisany poprawnie.
 * \retval false - operacja nie powiodła się.
*/
bool GoraZDlugaGrania::Usun()const 
{
    std::ofstream  StrmWyj(WezNazwePliku_BrylaFinalna());     

    if (!(OtworzonoPlik(StrmWyj, WezNazwePliku_BrylaFinalna()))) {
        return false;
    }        
    assert(StrmWyj.good());  

    Wektor3D Wierz = { 0,0,0};
    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz) {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz) {
            StrmWyj <<Wierz;
            if(NiePrawidlowoZapisano(StrmWyj)) return false;
        }   
         StrmWyj<<std::endl;        
    }
    
    return !StrmWyj.fail();                    
}

/*!
* Transformuje Polozenie o zadany Wektor 
*
* \param[in] Wierz - Wektor Transforamcji 
*
* \return Zwraca Przetransformowane Polozenie 
*/
 Wektor3D GoraZDlugaGrania::TransformujPolozenie(const Wektor3D& Wierz) const
 {  
     Wektor3D WierzTym = Wierz + Polozenie;
     return WierzTym;
 }

/*Prostokat jest uznawany jako rzut przeszkody na plaszczyzne 2D a kolo jest uznawane jako rzut drona  
na plaszczyzne 2D(to koło ma promień połowy długości przekątnej korpusu drona)*/
 bool GoraZDlugaGrania::CzyZajete(const Dron& Dn)
 {
    Wektor2D WierzcholkiProstokata[ILOSC_WIERZ_PROSTOKATA];

     WierzcholkiProstokata[A] =  {Polozenie[X]-(WezSkale()[X]/2), Polozenie[Y] - (WezSkale()[Y]/2)};
     WierzcholkiProstokata[B] = {Polozenie[X]+(WezSkale()[X]/2), Polozenie[Y] - (WezSkale()[Y]/2)};
     WierzcholkiProstokata[C] = {Polozenie[X]+(WezSkale()[X]/2), Polozenie[Y] + (WezSkale()[Y]/2)};
     WierzcholkiProstokata[D] = {Polozenie[X]-(WezSkale()[X]/2), Polozenie[Y] + (WezSkale()[Y]/2)};

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

double GoraZDlugaGrania::ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki)const
 {
     Wektor2D WierzcholkiProstokata[ILOSC_WIERZ_PROSTOKATA];

     WierzcholkiProstokata[A] =  {Polozenie[X]-(WezSkale()[X]/2), Polozenie[Y] - (WezSkale()[Y]/2)};
     WierzcholkiProstokata[B] = {Polozenie[X]+(WezSkale()[X]/2), Polozenie[Y] - (WezSkale()[Y]/2)};
     WierzcholkiProstokata[C] = {Polozenie[X]+(WezSkale()[X]/2), Polozenie[Y] + (WezSkale()[Y]/2)};
     WierzcholkiProstokata[D] = {Polozenie[X]-(WezSkale()[X]/2), Polozenie[Y] + (WezSkale()[Y]/2)};

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