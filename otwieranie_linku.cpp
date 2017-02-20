#include <windows.h>
#include <iostream>

using namespace std;

void otwieranie_linku(const char ser[])
{


//cout<<ser;
    HWND hwnd;
//    char ser[]="www.cpp0x.pl";
    //INFO: definiujemy dwa klucze, gdyż 2 wartości musimy odczytać
HKEY klucz;
HKEY klucz2;

//INFO: otwarcie klucza funkcją RegOpenKeyEx
if( RegOpenKeyEx( HKEY_CLASSES_ROOT, "HTTP\\shell\\open\\ddeexec\\Application", 0, KEY_READ, & klucz ) != ERROR_SUCCESS );

CHAR wartosc[ 256 ]; //INFO: łańcuch znaków na odczytaną wartość
DWORD rozmiar; //INFO: rozmiar odczytanej wartości(w bajtach)
DWORD typ_danych = REG_SZ; //INFO: zmienna na typ danych
DWORD typ_danych2 = REG_BINARY;

//INFO: odczytanie wartości z klucza
if( RegQueryValueEx( klucz, "", 0, & typ_danych,( LPBYTE ) wartosc, & rozmiar ) != ERROR_SUCCESS );
//     MessageBox( 0, "Nie można odczytać wartości", "Błąd", MB_OK );

RegCloseKey( klucz ); //INFO: zamknięcie klucza który już nie będzie nam potrzebny
if( RegOpenKeyEx( HKEY_CLASSES_ROOT, "HTTP\\shell\\open\\command", 0, KEY_READ, & klucz2 ) != ERROR_SUCCESS );
//     MessageBox( 0, "Nie można otworzyć klucza", "Błąd", MB_OK );

char wartosc2[ 256 ]; //INFO: łańcuch znaków na odczytaną wartość
DWORD rozmiar2 = 256;
if( RegQueryValueEx( klucz2, "", 0, & typ_danych,( LPBYTE ) wartosc2, & rozmiar2 ) != ERROR_SUCCESS );
//     MessageBox( 0, "Nie można odczytać wartości", "Błąd", MB_OK );

//INFO: pokazanie wyników
//MessageBox( 0, wartosc2, "Adres do przeglądarki: ", MB_OK );
RegCloseKey( klucz2 );
string wartosc3 = wartosc2;
string pocz = "\"";
string kon = ".exe";
string::size_type a = wartosc3.find( pocz );
string::size_type b = wartosc3.find( kon );
char * wartosc4 = new char[ b + 5 ];
wartosc3.copy( wartosc4,b+5,a);
//cout<<"pocz"<<a<<endl<<"kon"<<b+5<<endl;
//cout<<wartosc3<<endl;
//cout<<wartosc4;
//cout<<ser;
    ShellExecute( hwnd, "open", wartosc4, ser, NULL, SW_SHOWNORMAL );
}
