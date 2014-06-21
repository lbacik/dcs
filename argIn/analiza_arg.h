/*
 * elecra  - symulator uk�ad�w cyfrowych.
 * Copyright (C) 2003/2005 �ukasz Bacik
 *
 * Niniejszy program jest wolnym oprogramowaniem; mo�esz go 
 * rozprowadza� dalej i/lub modyfikowa� na warunkach Powszechnej
 * Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
 * Oprogramowania - wed�ug wersji 2-giej tej Licencji lub kt�rej�
 * z p�niejszych wersji. 
 *
 * Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on 
 * u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej 
 * gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH 
 * ZASTOSOWA�. W celu uzyskania bli�szych informacji - Powszechna 
 * Licencja Publiczna GNU. 
 *
 * Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz 
 * Powszechnej Licencji Publicznej GNU (GNU General Public License);
 * je�li nie - napisz do Free Software Foundation, Inc., 675 Mass Ave,
 * Cambridge, MA 02139, USA.
 *
 */

/*
 * electra - digital circuits simulator.
 * Copyright (C) 2003/2005 �ukasz Bacik
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 */
 
 
/*


		     Analiza agrument�w linii polece�

	Analiza argument�w wywo�ania programu polega na wype�nieniu 
przekazanej do biblioteki struktury "TUstawienia" odpowiednimi warto�ciami
pobranymi z linii polece� programu.

	TODO

	[ ] Doda� rozr�znienie argumentu ( -co� ) od warto�ci ( cos ),
	    tak aby w wywo�aniu:
			prog -f -d 10
	    ( dla -f wymagaj�cego podania warto�ci ) - linia by�a 
	    rozpoznawana jako brak arg dla "-f" a nie "nieznany arg 10".



 */


//#include<string.h>
//#include<stdlib.h>

//b��dy

	const int ERR_LP_brak_wartosci	        = 0x0101;
        const int ERR_LP_bledna_wartosc         = 0x0102;
        const int ERR_LP_niezrozumialy_parametr = 0x0103;

	char *analiza_arg_err_mesg[] = 
	      { "Brak warto�ci dla parametru.",
		"Niew�a�ciwa warto�� parametru ( oczekiwano liczby ).",
		"Niezrozumia�y parametr." };

struct	TUstawienia {

	char *plikWe; 	// plik do kompilacji ( dla plik = NULL dane z cin )	
	char *plikDmg;
	char *plikSig;
	char *conf; 	// ??					<-- NIEUZYWANE
	char *log; 	// nazwa pliku log�w    		<-- NIEUZYWANE
	char *we;
	char *set_dff;
	unsigned int dlbuf,	// d�ugo�� bufora g��wnego 
	    	     dlbufln,	// d�ugo�� bufora linii
		     debug,	// poziom debugowania		<--    ???
		     logdebug,	// poziom logowania do pliku	<-- NIEUZYWANE
		     logtr,	// tryb logowania	 	<-- NIEUZYWANE
		     d1,	// wypisz ustawienia
		     d2,	// wypisz pami��
		     d3,	// wypisz propagacje ( tylko elem )
		     d4,	//     - " -         ( elem + linie )
		     d5,	// dbg fali
		     d6,	// elementy
		     d7,	// wej�cie
		     wait,      // po prostu czeka na Ctrl+C
		     clk,
		     CDdbg,	// wypisz Const & Dest
		     pr_reset,
		     pr_dff;
	
};

void clear_set( TUstawienia &ustawienia ) {

	ustawienia.plikWe  	= NULL;
	ustawienia.plikDmg	= NULL;
	ustawienia.plikSig	= NULL;
	ustawienia.conf  	= NULL;
	ustawienia.log		= NULL;        
	ustawienia.we		= NULL;
	ustawienia.set_dff	= NULL;
	ustawienia.clk		= 0;
	ustawienia.dlbuf 	= 1024 * 4;
	ustawienia.dlbufln	= 80;
	ustawienia.debug	= 2;
	ustawienia.logdebug	= 0;	
	ustawienia.logtr	= 0;
	ustawienia.d1		= 0;
	ustawienia.d2		= 0;
	ustawienia.d3		= 0;
	ustawienia.d4		= 0;
	ustawienia.d5		= 0;
	ustawienia.d6		= 0;
	ustawienia.d7		= 0;
	ustawienia.wait     	= 0;
	ustawienia.CDdbg	= 0;
	ustawienia.pr_reset	= 0;
	ustawienia.pr_dff	= 0;

}

/*
int analiza_arg_err( int e, char* arg ) {

	cerr << "*** ANALIZA ARG. ERROR!";

	switch( e ) {

		case ERR_LP_brak_wartosci : 
			cerr << "- Brak warto�ci dla argumentu : ";
			break;
					    
		case ERR_LP_bledna_wartosc : 
			cerr << "- Oczekiwano liczby : ";
			break;

		case ERR_LP_niezrozumialy_parametr :
			cerr << "- Niezrozumia�y parametr : "; 
			break;
					     
	}
	
	cerr << arg << endl;
	
	return ERR_analizaArg;
}

*/

char* analiza_arg_err( int err )
{
		char *wynik = NULL;
	//	wynik = (char*)malloc( 80*sizeof( char ));
	//	if( wynik != NULL ) {
	//	wynik[0] ='\0';
	//	strcpy( wynik,"[analiza_arg]");
		switch( err ) {

			case ERR_LP_brak_wartosci: 
				//strcat( wynik, analiza_arg_err_mesg[0] );
				wynik = analiza_arg_err_mesg[0];
				break;
			case ERR_LP_bledna_wartosc:
				//strcat( wynik, analiza_arg_err_mesg[1] );
				wynik = analiza_arg_err_mesg[1];
				break;
			case ERR_LP_niezrozumialy_parametr:
				//strcat( wynik, analiza_arg_err_mesg[2] );
				wynik = analiza_arg_err_mesg[2];
				break;
		}
	// }
	return wynik;
}

void pomoc( char *nazwa ) {

	//cout << "%%% electra " << __VER__ 
	//     << " http://www.electra.webpark.pl %%%" << endl;
	cout << endl << "%%% Symulator Uk�ad�w Cyfrowych %%%" 
	     << endl << endl;	
	//cout << "%%% �ukasz Bacik ( lukasz.bacik@wp.pl ) 2004 %%%" << endl;

	cout << "electra wersja "<< __VER__ << ", Copyright C 2005 �ukasz Bacik" << endl
	     << endl
	     << "Program electra wydawany jest ABSOLUTNIE BEZ �ADNEJ GWARANCJI!" << endl
	     << "To jest wolne oprogramowanie i mile widziane jest dalsze " << endl
	     << "rozpowszechnianie go przez ciebie na okre�lonych warunkach - " << endl
	     << "w celu uzyskania bli�szych szczeg��w zobacz http://luka.org.pl/electra" << endl << endl;
	
        cout << "Program mo�e pobiera� dane z stdin lub pliku" << endl; 
	cout << "U�ycie:" << endl;
	cout << "\t" << nazwa << " [opcje] " << endl;
	cout << "Opcje:" << endl;
	cout << "\t-h, --help       - ten ekran" << endl;
	cout << "\t--version        - podaje numer wersji programu" << endl;
	cout << "\t-f <nazwa_pliku> - plik bench ( opis uk�adu ) do parsowania"
	     << endl;
	cout << "\t-dmg <nazwa_pliku> - plik flt ( uszkodzenia uk�adu )"
	     << "[opcjonalnie]" << endl;
	cout << "\t-bu              - rozmiar bufora pliku" << endl;
	cout << "\t-bl              - rozmiar bufora linii" << endl;
	cout << "\t-we              - wej�cie dla symulowanego uk�adu" << endl;
	cout << endl;

	cout << "\t\tDane wej�ciowe mo�na podawa� jako ci�g w linii polece�,"
	     << endl << "\t\tnp: \"10 01\", lub \"1\"." << endl;
	cout << "\t\tWA�NE S� CUDZYS�OWY! Spacja jest separatorem danych"
	     << endl;
	cout << "\t\tdla 'kolejnych przebieg�w' uk�adu." << endl;
	cout << "\t\tW przypadku NIE podania �ADNYCH danych wej�ciowych" 
	<< endl << "\t\t( opcje: -we, -if, -clk, -dff ) program b�dzie czeka�"
	<< endl << "\t\tna dane wej�ciowe z std::in w formacie opcji \"-we\""
	<< endl << "\t\t( Ctrl+D - ko�czy wprowadzanie." << endl;

	cout << "\t-if              - dane wej�ciowe jako plik."<< endl;
	cout << "\t\tZOBACZ przyk�ady na stronie "
	     << "http://www.electra.webpark.pl" << endl;
	cout << "\t-dff {ciag}	    - stany pocz�tkowe przerzutnik�w" << endl;
	cout << "\t-clk {int}	    - liczba takt�w do przeliczenia" << endl;
	
	cout << endl
	     << " Poni�sze opcje s� przeznaczone do testowania programu: " 
	     << endl
	     << "\t-d1              - poka� ustawienia" << endl  
	     << "\t-d2              - poka� pami��" << endl
	     << "\t-d3              - poka� uszkodzenia" 
	     << endl
	     << "\t-d4              - poka� propagacj�" 
	     << endl
	     << "\t-d5              - propagacja (szczeg�y)" 
	     << endl
	     << "\t-d6              - elementy" 
	     << endl
	     << "\t-d7              - wej�cia"
	     << endl;

}

// funkcja, w odr�nieniu od f. plik_we, pobiera wska�nik na ci�g ( nie 
// wska�nik na struktur� ) co pozwala wykorzysta� j� dla ka�dego przypisania
// nazwy pliku do pola w strukturze

int set_dchar( int argc, char* argv[], int &i, char* &dchar ) {

	int err = 0;

	if( i < argc - 1 ) {				

		//ustawienia.plik = argv[++i];
		dchar = argv[++i];

	} else { 
	
		// B��d: brak warto�ci		
		err = ERR_LP_brak_wartosci;
	}

	return err;

}

/*
	Funkcja przypisuje polom liczbowym struktury TUstawienia warto�ci
 	z linii polece�. Sprawdzane jest czy warto�� dla tanego pola zosta�a
	wpisana w linii polece� po "parametrze" pola i czy jest to liczba.

	Gdyby ograniczy� ilo�� argument�w wej�ciowych sprawdzanie argv[] w
	celu stwierdzenia czy zawiera jeszcze jakie� dane musia�o by by�
	wykonywane poza funkcj�.

*/

int set_dint( int argc, char* argv[], int &i, 
	      unsigned int &dint, int min ) {

	int err = 0;

	if(( i < argc - 1 ) &&				
	   //( strspn( argv[++i],digit ) == strlen( argv[i] )) && 
	    ( czyLiczba( argv[++i] )) &&
	   (( dint = atoi( argv[i] )) >= min ));

	else err = ERR_LP_bledna_wartosc;

	return err;
}

int analizuj_arg( int argc, char* argv[], TUstawienia &ustawienia )
{
	int err = 0;
	char *tmp;
	
	clear_set( ustawienia );	
	
	for( int i = 1; i < argc; i++ ) {

		if( !strcmp( argv[i], "--help" ) || !strcmp( argv[i], "-h" )) {

			pomoc( argv[0] );
			exit(0);
		}

		if( !strcmp( argv[i], "--version" )) {

			cout << __VER__ << endl;
			exit(0);
			
		} 
		
		else if( !strcmp( argv[i], "-f" )) {
 
			err = set_dchar( argc, argv, i, ustawienia.plikWe );
		
		}

		else if( !strcmp( argv[i], "-dmg" )) {
		
			err = set_dchar( argc, argv, i, ustawienia.plikDmg );

		}

		else if( !strcmp( argv[i], "-we" ) || 
			  !strcmp( argv[i], "-in" )) {
		
			err = set_dchar( argc, argv, i, tmp );
			
            		//if( access( tmp, 4 ) == 0 )       //  [FIXME]
			
			//	ustawienia.plikSig = tmp; //  brak f. access 
							  //  w win
			//else 
            
			        ustawienia.we = tmp;

		}

		else if( !strcmp( argv[i], "-if" )) {

			err = set_dchar( argc, argv, i, tmp );
			ustawienia.plikSig = tmp;
		}

		else if( !strcmp( argv[i], "-clk" )) {

			err = set_dint( argc, argv, i, ustawienia.clk, 0 );

		}

		else if( !strcmp( argv[i], "-dff" )) {


			err = set_dchar( argc, argv, i, ustawienia.set_dff );
		}
		
		else if( !strcmp( argv[i], "-bu" )) {

			err = set_dint( argc, argv, i, ustawienia.dlbuf, 1 );

		}
		
		else if( !strcmp( argv[i], "-bl" )) {

			err = set_dint( argc, argv, i, ustawienia.dlbufln, 1 );

		}

		else if( !strcmp( argv[i], "-d1" )) {
			
			ustawienia.d1 = 1;

		}

		else if( !strcmp( argv[i], "-d2" )) {
			
			ustawienia.d2 = 1;

		}

		else if( !strcmp( argv[i], "-d3" )) {
			
			ustawienia.d3 = 1;

		}

		else if( !strcmp( argv[i], "-d4" )) {
			
			ustawienia.d4 = 1;

		}

		else if( !strcmp( argv[i], "-d5" )) {

			ustawienia.d5 = 1;
		}
	
		else if( !strcmp( argv[i], "-d6" )) {

			ustawienia.d6 = 1;
		}
	
		else if( !strcmp( argv[i], "-d7" )) {

			ustawienia.d7 = 1;
		}

 		else if( !strcmp( argv[i], "-wait" )) {
 		
		        ustawienia.wait = 1; 		
        	}
        
		else if( !strcmp( argv[i], "-dCD" )) {

			ustawienia.CDdbg = 1;
		}

		else if( !strcmp( argv[i], "--pr_dff" )) {

			ustawienia.pr_dff = 1;
		}

		else if( !strcmp( argv[i], "--pr_reset" )) {

			ustawienia.pr_reset = 1;
		}

		else {

			//B��d: niezrozumia�y parametr w linii polece�
			err = ERR_LP_niezrozumialy_parametr;

		}	

		//if( err != 0 ) err = analiza_arg_err( err, argv[i] );
	
	}
	return err;
}
