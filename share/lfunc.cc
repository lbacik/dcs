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
 
 

//-- 2.95
#include <ctype.h>
#include <malloc.h>
//--
#include <string.h>
#include <iostream>

int czyLiczba( const char *ciag )
{
	int i,wynik=1;
	for( i = 0; i < strlen( ciag ); i++ )
		if( !isdigit( ciag[i] )) {
			wynik=0;
			break;
		}
	return wynik;	
}



char* strupcase( const char* ciag )
{
	char *wynik = NULL;
	int i;

	if( ciag != NULL ) {

		wynik = strdup( ciag );
		for( i=0; i<strlen(wynik); i++ )
			wynik[i] = toupper( wynik[i] );
	}

	return wynik;
}


/*
 *
 * Funkcja usuwa "bia³e znaki" z pocz±tku i koñca ci±gu przekazanego 
 * jako parametr.
 *
 * Warto¶ci± zwracan± jest NOWY, poprawiany ci±g ( przydzielona 
 * zostaje mu pamiêæ )
 *
 */
char* clwhite( const char *ciag )
{
	char *tmp, *c = strdup( ciag );
	int i;
		
	i = 0;
	while(( i < strlen( c )) && ( isspace( c[i] ))) i++ ;
	
	tmp = &c[i];
	while(( strlen( c ) > 0 ) && ( isspace( c[ strlen( c )-1 ] )))
			c[ strlen( c )-1 ] = '\0';
		
	tmp = strdup( tmp );
	free( c );
	
	return tmp;	
}

/*
 * rozbija "ci±g" na dwa podci±gi ( pcs i pcb ) wg separatora
 * "sep".
 *
 * Je¿eli ci±g nie zawiera separatora funkcja zwraca warto¶æ
 * 0 ( false ) w przeciwnym razie warto¶ci± zwracan± jest
 * 1 ( true );
 *
 * /!\ Podci±gom pca i pcb funkcja przydziela pamiêæ!
 *
 */
int explode( const char *ciag, const char *sep, char *&pca, char *&pcb )
{
	char *tmp, *cwe = strdup( ciag );
	int err = 1;
	
	tmp = strstr( cwe, sep );
	
	if( tmp != NULL ) {

		tmp[0] = '\0';
		pca = clwhite( cwe );
		pcb = clwhite( &tmp[strlen(sep)] );
		
	} else {
	
		pca = clwhite( ciag );
		err = 0;
	}
	
	free( cwe );
	return err;
}


/*
 *	
 *
 *
 */
int explode2( const char *ciag, const char *sep0, const char *sep1,
		char *&A, char *&B, char *&C )
{
	char *tmp;
	int err = 0;
	
	explode( ciag, sep0, A, tmp );
	explode( tmp, sep1, B, C ); 
	
	free( tmp );
	return err;
}


/*
 * isSpace zwraca warto¶æ 0 je¿eli ci±g sk³ada siê z samych znaków bia³ych.
 *
 */
int isSpace( const char *ciag )
{
	int i = 0;
	
	if( ciag != NULL ) {
		
		i = strlen( ciag );
		while(( i > 0 ) && isspace( ciag[i-1] )) i--;
	}
	
	return i;
}
