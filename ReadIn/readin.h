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
 *
 *			ReadIn
 */

/*

	Procedury zapewniaj�ce wczytanie danych z pliku b�d� stdin.

*/

const int ERR_ReadIn_A		= 0x1; //B��d w procedurze analizuj�cej 
const int ERR_ReadIn_bl		= 0x2; //Brak pami�ci (zwi�ksz bufor linii)
const int ERR_ReadIn_Mem	= 0x3; //Nie mo�na zainicjowa� bufor�w 
const int ERR_ReadIn_file	= 0x4; //Problem z plikiem wej�ciowym

/* funkcja zwraca komunikat o b��dzie */
char* readin_err( int err );

/* funkcja zwraca numer b��du zwr�cony przez funkcj� analizuj�c� */
int err_analiza( void );

/* wersja */
char* readin_ver( void );


/* Tego tu NIE B�DZIE!
 * 
 * 							[FIXME]
 * 							
 * deklaracja zosta�a zawarta w tym pliku nag��wkowym ze wzgl�du
 * na u�ycie funkcji w programie g��wnym. 
 * 
 */
int ladujbufln( TBufor *buf, TBufor *bufln, 
		void *struktura, int (*pfun)(char*, void*));

/*
 *	
 *
 */
int readin( int flag,                     // flagi  0 - czytaj tylko
		                          //            z pliku
					  //        1 - je�eli plik = NULL
					  //            to czytaj z stdin
	    int size_buf,                 // rozmiar bufora pliku 
	    int size_bufln,               // rozmiar bufora linii
	    char *file,                   // nazwa pliku ( lub NULL )
	    void *struktura,              // wska�nik na struktur� do 
	    				  // wype�nienia przez 
					  // f. analizuj�c�
	    int (*pfun)(char*, void*));   // wska�nik na f. analizuj�c�

