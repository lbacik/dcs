/*
 * elecra  - symulator uk³adów cyfrowych.
 * Copyright (C) 2003/2005 £ukasz Bacik
 *
 * Niniejszy program jest wolnym oprogramowaniem; mo¿esz go 
 * rozprowadzaæ dalej i/lub modyfikowaæ na warunkach Powszechnej
 * Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
 * Oprogramowania - wed³ug wersji 2-giej tej Licencji lub której¶
 * z pó¼niejszych wersji. 
 *
 * Niniejszy program rozpowszechniany jest z nadziej±, i¿ bêdzie on 
 * u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy¶lnej 
 * gwarancji PRZYDATNO¦CI HANDLOWEJ albo PRZYDATNO¦CI DO OKRE¦LONYCH 
 * ZASTOSOWAÑ. W celu uzyskania bli¿szych informacji - Powszechna 
 * Licencja Publiczna GNU. 
 *
 * Z pewno¶ci± wraz z niniejszym programem otrzyma³e¶ te¿ egzemplarz 
 * Powszechnej Licencji Publicznej GNU (GNU General Public License);
 * je¶li nie - napisz do Free Software Foundation, Inc., 675 Mass Ave,
 * Cambridge, MA 02139, USA.
 *
 */

/*
 * electra - digital circuits simulator.
 * Copyright (C) 2003/2005 £ukasz Bacik
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

	Procedury zapewniaj±ce wczytanie danych z pliku b±d¼ stdin.

*/


#include <iostream>
#include <fstream.h>
//-- 2.95
#include <string.h>
//--

#include "../share/bufor.h"
#include "readin.h"

const char ver[] = "0.3";
const char EOL = '\n';

int err_a = 0;

	char	*czytaj_dane_err_mesg[] =
		{ "B³ad wystapi³ w funkcji analizujacej.",
		  "Zbyt ma³y bufor linii!",
		  "Brak pamiêci na inicjacjê buforów.",
	  	  "Problem z plikiem wejsciowym..." };	

char* readin_err( int err )
{
	return czytaj_dane_err_mesg[err];
}

int err_analiza( void )
{
	return err_a;
}

char* readin_ver( void )
{
	return (char*)ver;
}


/* 
 * Przepisuje z bufora buf do bufln znaki a¿ do napotkania znaku koñca
 * linii ( dzia³anie prawid³owe ) lub zape³nienia bufora linii ( bufln )
 * - ERR_ReadIn_bl !!!
 *
 * Je¿eli bufor linii zosta³ pomy¶lnie wype³niony to wtedy wywo³ywana
 * jest funkcja analizuj±ca ów bufor.
 *
 */

int ladujbufln( TBufor *buf, TBufor *bufln, 
		void *struktura, int (*pfun)(char*, void*)) {

	char c; int err = 0;
 
	while(( buf->getch( c )) && ( err == 0 )) { 
		
		if( c != EOL ) {
			
			if(  bufln->putch( c ) != 0 )
				err = ERR_ReadIn_bl;
		} else {
		
			if(  bufln->putch('\0') != 0 )
				err = ERR_ReadIn_bl;
		}

		if(( c == EOL ) && ( err == 0 )) { 
			

			// Wywo³anie funkcji analizuj±cej
			
			char *tmp = strdup( bufln->pocz );
			if(( err_a = 
			
			    pfun( tmp, struktura )) != 0 )

				err = ERR_ReadIn_A;
					
			bufln->zeruj();	
		}
	}

	return err;

}

/*								[FIXME]
 * dane_z_pliku()
 * dane_z_stdin() - te dwie funkcje nale¿a³o by po³±czyæ w jedn±,
 * w koñcu plik ( ifstream ) to obiekt pochodny klasy std...
 *
 */
int dane_z_pliku( char *file, TBufor *buf, TBufor *bufln, 
		  void *struktura, int (*pfun)(char*, void*)) {

	int err = 0;
	char ch;
	ifstream We( file );

	if( !We ) {
	
		err = ERR_ReadIn_file; //Problem z plikiem

	} else {

		while( !err && !We.eof() ) {

			buf->zeruj();	
			while(( buf->iloscmiejsca() > 0 ) && 
					( We.get( ch ))) { 

				buf->putch( ch );
			}
			
			err = ladujbufln( buf, bufln, struktura, pfun );
		}
	}

	return err;

}

int dane_z_stdin( TBufor *buf, TBufor *bufln, 
		  void* struktura, int (*pfun)(char*, void*)) {

	int err = 0;
	char ch;
	
	while( !err && !std::cin.eof() ) {

		buf->zeruj();
		while(( buf->iloscmiejsca() > 0 ) && ( std::cin.get( ch ))) { 
			
			buf->putch( ch );

		}	
		err = ladujbufln( buf, bufln, struktura, pfun );
	}

	return err;
	
}

/*
 *	inicjacja buforów
 *	wywo³anie odpowiedniej procedury odczytuj±cej
 *	zniszczenie buforów
 *
 */
int readin( int flag, int size_buf, int size_bufln, char *file,
	    void *struktura, int (*pfun)( char*, void* ))
{
	int err = 0;
	TBufor *buf, *bufln;
	
	buf = new TBufor( size_buf );
	bufln = new TBufor( size_bufln );

	if(( buf == NULL ) || ( bufln == NULL ))
		err = ERR_ReadIn_Mem;
	else {

		if( file != NULL )

			err = dane_z_pliku( file, buf, bufln, 
					    struktura, pfun );
	
		else if(( flag & 1 ) == 1 )
		
			err = dane_z_stdin( buf, bufln, 
					    struktura, pfun );
	
	}

	delete buf;
	delete bufln;
	
	return err;

}
