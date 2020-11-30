#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/* Ponizej dodaje polskie znaki, _x to ziet */
const unsigned char _a=165;
const unsigned char _c=134;
const unsigned char _e=169;
const unsigned char _l=136;
const unsigned char _n=228;
const unsigned char _o=162;
const unsigned char _s=152;
const unsigned char _x=171;
const unsigned char _z=190;
const unsigned char _A=164;
const unsigned char _C=143;
const unsigned char _E=168;
const unsigned char _L=157;
const unsigned char _N=227;
const unsigned char _O=224;
const unsigned char _S=151;
const unsigned char _X=141;
const unsigned char _Z=189;

class wektor
{
    public:
        long double x;
        long double y;
        long double z;

    // iloczyn wektorowy
    wektor operator*(wektor drugi)
    {
        wektor wynik;
        wynik.x=(y*(drugi.z))-(z*(drugi.y));
        wynik.y=(z*(drugi.x))-(x*(drugi.z));
        wynik.z=(x*(drugi.y))-(y*(drugi.x));
        return wynik;
    }

    void wczytaj_wektor(void)
    {
        cout<<"X: ";
        cin>>x;
        cout<<"Y: ";
        cin>>y;
        cout<<"Z: ";
        cin>>z;
    }
};

int main()
{
    int co_ile, liczba_iteracji;
    wektor predkosc, pole_ele, pole_mag, polozenie, iloczyn_z_pol_mag;
    long double masa, ladunek, krok_czasowy;
    string lokalizacja;
    fstream outPut;
    char znak_koniec;

    // komunikacja
    cout<<"Podaj wektor nat"<<_e<<_z<<"enia pola elektrycznego w [N/C]."<<endl;
    pole_ele.wczytaj_wektor();

    cout<<"Podaj wektor indukcji magnetycznej w [T]."<<endl;
    pole_mag.wczytaj_wektor();

    cout<<"Podaj po"<<_l<<"o"<<_z<<"enie pocz"<<_a<<"tkowe w [m]."<<endl;
    polozenie.wczytaj_wektor();

    cout<<"Podaj pr"<<_e<<"dko"<<_s<<_c<<" pocz"<<_a<<"tkow"<<_a<<" w [m/s]."<<endl;
    predkosc.wczytaj_wektor();

    cout<<"Podaj mas"<<_e<<" w [kg]."<<endl;
    cout<<"Masa: ";
    cin>>masa;

    cout<<"Podaj "<<_l<<"adunek w [C]."<<endl;
    cout<<_L<<"adunek: ";
    cin>>ladunek;

    cout<<"Podaj krok czasowy w [s]."<<endl;
    cout<<"Krok czasowy: ";
    cin>>krok_czasowy;

    cout<<"Podaj liczb"<<_e<<" iteracji. (na przyk"<<_l<<"ad: 10000)"<<endl;
    cout<<"Liczba iteracji: ";
    cin>>liczba_iteracji;

    cout<<"Podaj, co ile iteracji ma nast"<<_a<<"pi"<<_c<<" zapisywanie do pliku: ";
    cin>>co_ile;

    cout<<"Podaj nazw"<<_e<<" pliku wyj"<<_s<<"ciowego. (np. moje_wyniki.txt)."<<endl;
    cout<<"Nazwa pliku wyj"<<_s<<"ciowego: "<<endl;

    while(1){
        cin>>lokalizacja;
        lokalizacja="wyniki/"+lokalizacja;
        outPut.open(lokalizacja.c_str(),ios::out);
        if(outPut.good()) break;
        cout<<"Plik, nie otworzy"<<_l<<" si"<<_e<<" prawid"<<_l<<"owo. Czy na pewno masz folder \"wyniki\"?"<<endl<<"Kolejna pr"<<_o<<"ba - nazwa pliku wyj"<<_s<<"ciowego: ";
    }

    outPut<<"Obliczenia wykonywane dla danych: "<<endl;
    cout<<"Masa: "<<masa<<" kg\n"<<_L<<"adunek: "<<ladunek<<" C\nLiczba iteracji: "<<liczba_iteracji<<"\nKrok czasowy: "<<krok_czasowy<<" s"<<endl<<"============================"<<endl;

    // glowna petla
    for (int i=0;i<=liczba_iteracji;i++)
    {
        // zapis do pliku
        cout.precision(6);
        if (i%co_ile==0){
            outPut<<"\tNumer iteracji: "<<i<<endl;
            outPut<<fixed<<" Po"<<_l<<"o"<<_z<<"enie: "<<"[ "<<polozenie.x<<" ; "<<polozenie.y<<" ; "<<polozenie.z<<" ]"<<" m" ;
            outPut<<endl;
            outPut<<fixed<<" Pr"<<_e<<"dko"<<_s<<_c<<": "<<"[ "<<predkosc.x<<" ; "<<predkosc.y<<" ; "<<predkosc.z<<" ]"<<" m/s" ;
            outPut<<endl<<endl;
        }

        // obliczenia
        polozenie.x=polozenie.x+(predkosc.x*krok_czasowy);
        polozenie.y=polozenie.y+(predkosc.y*krok_czasowy);
        polozenie.z=polozenie.z+(predkosc.z*krok_czasowy);

        iloczyn_z_pol_mag=(predkosc*pole_mag);
        predkosc.x=predkosc.x+(((ladunek*(pole_ele.x+iloczyn_z_pol_mag.x))/masa)*krok_czasowy);
        predkosc.y=predkosc.y+(((ladunek*(pole_ele.y+iloczyn_z_pol_mag.y))/masa)*krok_czasowy);
        predkosc.z=predkosc.z+(((ladunek*(pole_ele.z+iloczyn_z_pol_mag.z))/masa)*krok_czasowy);
    }

    outPut.close();
    cout<<"Zapis danych zako"<<_n<<"czony.";
    cin>>znak_koniec;
    return 0;
    //fsdafsa
}
