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
 *	analiza InSig
 *
 *      Wczytywanie ci±gów zer i jedynek.
 *	
 */

#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "../share/temlista.h"

const int insig_err_nz = 1;

/*
 * Wykorzystanie funkcji do analizy plików wymaga u¿ycia biblioteki readin. 
 * 
 * Sama funkja pobiera dwa argumenty:
 *
 * 	bufln      - to JEDNA linia analizowanego pliku ( bufora ).
 * 	struktura  - to wska¼nik na obiekt TLista<char*>, w którym
 * 	             zapisywane bêd± wyniki dzia³ania funkcji
 *
 * Ogólny schemat dza³ania ( i wykorzystania ) funkcji analizuj±cych 
 * biblioteki "parsery" zawarty zosta³ w opisia biblioteki.
 * 
 */

int analizaInSig( char *bufln, void *struktura )
{
	int err = 0, i, j;
	static int linia = 0;
	char *c, *tok, *tmp;

	// rzutowanie na wska¼nik void
	TLista<char*> *listaWe = (TLista<char*>*)struktura;

	linia++;
	
 	// wytnij komentarz	
	if(( c = strchr( bufln, '#' /*ZNAK_KOMENTARZA*/ )) != NULL ) 
		bufln[ c - bufln ] = '\0';

	c = bufln;

	// czy w linii s± jakie¶ znaki
	i = strlen( c );
	while(( i > 0 ) && ( isspace( c[i] ))) i--;

	if( i > 0 ) try {

		// zamie¿ ró¿ne bia³e znaki na spacje
		// oraz zlicz znaki nie-bia³e ( w zm. "j" )
		for( j = 0, i = 0; i < strlen( c ); i++ )
			if( isspace( c[i] )) c[i] = ' ';
			else j++;

		// przydziel pamiêæ dla ci±gu wynikowego
		tmp = (char*)malloc( j*sizeof(char)+1 );
		tmp[0]='\0';

		// ³±czenie znaków w jeden ci±g ( w tym momencie
		// ze znaków "bia³ych" ci±g zawiera ju¿ tylko spacje )
		tok = strtok( c, " " );
		while( tok != NULL ) {
			
			strcat( tmp,tok );
			tok = strtok( NULL, " " );
		}

		// Jeszcze sprawd¼my czy ci±g wynikowy sk³ada siê tylko z zer
		// i jedynek.
		for( i=0; i<strlen( tmp ); i++ )
			if(( tmp[i] != '0' ) && ( tmp[i] != '1' ))
				throw insig_err_nz;
		
		// OK, dodaj ci±g do listy.
		listaWe->dodaj( tmp );
	}
	catch( int __ERROR__ ){ err = __ERROR__; };

	return err;
}
