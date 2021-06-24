#include "ElementSceny.hh"
#include "Dron.hh"

bool ElementSceny::CzyZajete(const Dron& Dn)
{
Dn.CzyTenDronJestAktywny(); 
return false; 
}

double ElementSceny::ObliczWydluzenieTrasyPrzelotu(const Dron& Dn, std::vector<Wektor3D>& PunktySciezki) const
{Dn.CzyTenDronJestAktywny(); PunktySciezki[0]= PunktySciezki[0]; return 0.0;}

double ElementSceny::PrzeciecieDronaZOdcinkiemAD(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata,
 double PromienKolaDrona) const
{
  //PUNKT D
        if((PunktSciezki[X]<=WierzcholkiProstokata[D][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))
            return DlugoscPrzekatnejProstokata; 
        //PUNKT C
        if((PunktSciezki[X]>=WierzcholkiProstokata[C][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[C][Y]))         
            return PromienKolaDrona;
        //PUNKT B
        if((PunktSciezki[X]>=WierzcholkiProstokata[B][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[B][Y]))                     
            return PromienKolaDrona;
        //PUNKT A
        if((PunktSciezki[X]<=WierzcholkiProstokata[A][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return DlugoscPrzekatnejProstokata; 
        //MIEDZY PUNKTEM D I C
        if((PunktSciezki[X]>=WierzcholkiProstokata[D][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[C][X])&&
        (PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM A I B    
        if((PunktSciezki[X]>=WierzcholkiProstokata[A][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[B][X])&&
        (PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM B I C
        if((PunktSciezki[Y]>=WierzcholkiProstokata[B][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[C][Y])&&
        (PunktSciezki[X]>=WierzcholkiProstokata[B][X]))                     
            return PromienKolaDrona;            
        //MIEDZY PUNKTEM A I D
        if((PunktSciezki[Y]>=WierzcholkiProstokata[A][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[D][Y])&&
        (PunktSciezki[X]<=WierzcholkiProstokata[A][X]))          
            return DlugoscPrzekatnejProstokata; 
    return 0.0;                                   
}

double ElementSceny::PrzeciecieDronaZOdcinkiemBC(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata,
 double PromienKolaDrona) const
{
  //PUNKT D
        if((PunktSciezki[X]<=WierzcholkiProstokata[D][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))
            return PromienKolaDrona;
        //PUNKT C
        if((PunktSciezki[X]>=WierzcholkiProstokata[C][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[C][Y]))         
            return DlugoscPrzekatnejProstokata; 
        //PUNKT B
        if((PunktSciezki[X]>=WierzcholkiProstokata[B][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[B][Y]))                     
            return DlugoscPrzekatnejProstokata; 
        //PUNKT A
        if((PunktSciezki[X]<=WierzcholkiProstokata[A][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM D I C
        if((PunktSciezki[X]>=WierzcholkiProstokata[D][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[C][X])&&
        (PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM A I B    
        if((PunktSciezki[X]>=WierzcholkiProstokata[A][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[B][X])&&
        (PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM B I C
        if((PunktSciezki[Y]>=WierzcholkiProstokata[B][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[C][Y])&&
        (PunktSciezki[X]>=WierzcholkiProstokata[B][X]))                     
            return DlugoscPrzekatnejProstokata;                
        //MIEDZY PUNKTEM A I D
        if((PunktSciezki[Y]>=WierzcholkiProstokata[A][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[D][Y])&&
        (PunktSciezki[X]<=WierzcholkiProstokata[A][X]))          
            return PromienKolaDrona;   
    return 0.0;                                                        
}
double ElementSceny::PrzeciecieDronaZOdcinkiemDC(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata,
 double PromienKolaDrona) const
{
  //PUNKT D
        if((PunktSciezki[X]<=WierzcholkiProstokata[D][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))
            return DlugoscPrzekatnejProstokata; 
        //PUNKT C
        if((PunktSciezki[X]>=WierzcholkiProstokata[C][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[C][Y]))         
            return DlugoscPrzekatnejProstokata; 
        //PUNKT B
        if((PunktSciezki[X]>=WierzcholkiProstokata[B][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[B][Y]))                     
            return PromienKolaDrona;
        //PUNKT A
        if((PunktSciezki[X]<=WierzcholkiProstokata[A][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM D I C
        if((PunktSciezki[X]>=WierzcholkiProstokata[D][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[C][X])&&
        (PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))                     
            return DlugoscPrzekatnejProstokata;                
        //MIEDZY PUNKTEM A I B    
        if((PunktSciezki[X]>=WierzcholkiProstokata[A][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[B][X])&&
        (PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM B I C
        if((PunktSciezki[Y]>=WierzcholkiProstokata[B][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[C][Y])&&
        (PunktSciezki[X]>=WierzcholkiProstokata[B][X]))                     
            return PromienKolaDrona;            
        //MIEDZY PUNKTEM A I D
        if((PunktSciezki[Y]>=WierzcholkiProstokata[A][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[D][Y])&&
        (PunktSciezki[X]<=WierzcholkiProstokata[A][X]))          
            return PromienKolaDrona;
    return 0.0;                                               
}
double ElementSceny::PrzeciecieDronaZOdcinkiemAB(double DlugoscPrzekatnejProstokata, Wektor3D PunktSciezki, Wektor2D *WierzcholkiProstokata, 
double PromienKolaDrona) const
{
  //PUNKT D
        if((PunktSciezki[X]<=WierzcholkiProstokata[D][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))
            return PromienKolaDrona;
        //PUNKT C
        if((PunktSciezki[X]>=WierzcholkiProstokata[C][X])&&(PunktSciezki[Y]>=WierzcholkiProstokata[C][Y]))         
            return PromienKolaDrona;
        //PUNKT B
        if((PunktSciezki[X]>=WierzcholkiProstokata[B][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[B][Y]))                     
            return DlugoscPrzekatnejProstokata+PromienKolaDrona; 
        //PUNKT A
        if((PunktSciezki[X]<=WierzcholkiProstokata[A][X])&&(PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return DlugoscPrzekatnejProstokata+PromienKolaDrona; 
        //MIEDZY PUNKTEM D I C
        if((PunktSciezki[X]>=WierzcholkiProstokata[D][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[C][X])&&
        (PunktSciezki[Y]>=WierzcholkiProstokata[D][Y]))                     
            return PromienKolaDrona;
        //MIEDZY PUNKTEM A I B    
        if((PunktSciezki[X]>=WierzcholkiProstokata[A][X])&&(PunktSciezki[X]<=WierzcholkiProstokata[B][X])&&
        (PunktSciezki[Y]<=WierzcholkiProstokata[A][Y]))                     
            return DlugoscPrzekatnejProstokata+PromienKolaDrona;                
        //MIEDZY PUNKTEM B I C
        if((PunktSciezki[Y]>=WierzcholkiProstokata[B][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[C][Y])&&
        (PunktSciezki[X]>=WierzcholkiProstokata[B][X]))                     
            return PromienKolaDrona;            
        //MIEDZY PUNKTEM A I D
        if((PunktSciezki[Y]>=WierzcholkiProstokata[A][Y])&&(PunktSciezki[Y]<=WierzcholkiProstokata[D][Y])&&
        (PunktSciezki[X]<=WierzcholkiProstokata[A][X]))          
            return PromienKolaDrona;
    return 0.0;                                               
}