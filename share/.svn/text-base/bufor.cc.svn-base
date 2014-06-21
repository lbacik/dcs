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
 *				BUFOR
 *
 */


#include<stdlib.h>

	class TBufor {
	
	      public:
		
		char *pocz, *wsk_put, *wsk_get;
		int  dl;
		
	    

		TBufor( int );
		~TBufor();

		int putch( char );
		int getch( char& );
		
		void zeruj( void );
		int  iloscmiejsca( void );

	};


TBufor::TBufor( int ndl ) {

	dl=ndl;
	pocz=(char*)malloc( dl*sizeof( char ));
	zeruj();

}


TBufor::~TBufor() {

	free( pocz );

}


int TBufor::putch( char c ) {

	int err = 0;
	
	if( iloscmiejsca() > 0 ) (*wsk_put++) = c;
	else err = 1;
	
	return err;
	
}

int TBufor::getch( char &ch ) {

	ch=(*wsk_get);
	wsk_get++;
	return ( wsk_put - ( wsk_get-1 ) );

}

void TBufor::zeruj( void )
{
	
	wsk_put=wsk_get=pocz;
	
}

int  TBufor::iloscmiejsca( void )
{
     return ( dl - ( wsk_put - pocz ));	
} 

