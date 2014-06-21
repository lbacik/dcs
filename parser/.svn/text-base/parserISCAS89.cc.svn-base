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
 
 

#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "../share/temlista.h"
#include "../share/lfunc.h"
#include "../libelectra/types.h"

#include "iscas89rozbij.h" // IDSpr()

const char ZNAK_KOMENTARZA = '#';

const int	ERR_ID		= 0x1;
const int	ERR_MEM 	= 0x2;
const int	ERR_KEYW	= 0x3;

	char *analizaISCAS89_err_mesg[] = 
	     { "Niew³a¶ciwt=y identyfikator.",
	       "Brak pamiêci.",
	       "Niezrozumia³a linia." };

int I89_linia = 0;

//TLista<StDefEl*> *listaEl = new TLista<StDefEl*>( FE_wywolajDestWsk );


char* analizaISCAS89_err( int err )
{
	char *wynik;

	switch( err ) {

		case ERR_ID:  	wynik = analizaISCAS89_err_mesg[0];
			      	break;
		case ERR_MEM: 	wynik = analizaISCAS89_err_mesg[1];
			      	break;
		case ERR_KEYW:  wynik = analizaISCAS89_err_mesg[2];
				break;
	}
	
	return wynik;
}

int I89_nrLinii( void )
{
	return I89_linia;
};

/*
int sprID( char* id ) {

	int err = 0, i;
	
	for( i = 0; i < strlen( id ); i++ )
		if( isgraph( id[i] ));
		else {
			err = i;
			break;
		}

	return err;
}
*/

int sprID2( char * ciag ) 
{
	int i,err = 0;
	if(( strlen( ciag ) == 0 ) || ( i = sprID( ciag )) > 0 ) {

		//cerr << "***ERROR:[sprID] niew³a¶ciwy atrybut!" << endl;
		err = 1;
	}
	return err;
}	

int keyword( char *word ) {

	int key = 0;

	if( strcmp( word, "INPUT" ) == 0  ) key = 1;
	if( strcmp( word, "OUTPUT" ) == 0 ) key = 2;

	return key;
}

int I89rozbij4( char* ciag, char* &ident, TLista<char*>* &lista )
{

	char *A, *B, *C, *tmp;
	int err = 0;
	
	A = B = C = tmp = NULL;

	if(( err = explode2( ciag, "(", ")", A, B, C )) == 0 ) {
	
		if( isSpace( A ) == 0 ) err = 1;
		else {
		
			ident = A;
			if( isSpace( C ) != 0 ) err = 3;
			else {
				if( C != NULL ) free( C );
				tmp = strtok( B, "," );
				while( tmp != NULL ) {

					C = strdup( tmp );
					lista->dodaj( C ); 
					tmp = strtok( NULL, "," );
				}
			}
		}
	}
	return err;
}

int analizaISCAS89( char *bufln, void *struktura ) {

	//static int linia = 0;
	int err = 0, i;
	TLista<char*> *lista;
	TElement<char*> *elchar;
	StDefEl *DefEl;
	char *c = NULL, *ident = NULL, *nid = NULL, *ndef = NULL;
	TLista<StDefEl*> *listaEl = (TLista<StDefEl*>*)struktura;

	// zmienna zawieraj±ca nr. linii
	I89_linia++;
	
	// wytnij komentarz	<- explode
	
	//if(( c = strchr( bufln, ZNAK_KOMENTARZA )) != NULL ) 
	//	bufln[ c - bufln ] = '\0';

	explode( bufln, "#", c, nid );
	if( nid != NULL ) free( nid );
	
	// je¿eli w linii s± jakie¶ znaki
	//i = strlen( c );
	//while(( i > 0 ) && ( isspace( c[i] ))) i--;
	//if( strspn( c, biale ) < strlen( c )) {
	/*****************************************/
	
	// Czy c zawiera jakie¶ znaki ?
	if( isSpace( c ) != 0 ) {
	
	try {
	
		//  *** To upper ***
		//for( i=0; i<strlen(c); i++ ) c[i]=toupper( c[i] );
		//------------------------------------------------		
	
		// wszystkie litery w ci±gu zmieñ na du¿e 
		nid = strupcase( c );
		free( c );
		c = nid;

		// Podziel ci±g na dwie czê¶ci wg znaku "="
		// ( je¿eli znak nieistnieje w ci±gu to funkcja zwróci
		// warto¶æ false )
		if( explode( c, "=", nid, ndef )) {

			free( c );  // je¿eli linia zawiera znak "="
			c = ndef;   // to w "nid" mamy identyfikator
			            // a w "c" definicjê 
			
		} else {
				    // W przeciwnym razie w nid mamy c	
			if ( nid != NULL ) { // ... a to niedobrze... 
				             // wiêc trzeba wyczy¶ciæ nid
				free( nid );
				nid = NULL;
			}
		}
	
		lista = new TLista<char*>; // lista elementów wej¶ciowych
		if(( err = I89rozbij4( c, ident, lista )) == 0 ) {

			c = clwhite( ident ); // kasuj bia³e znaki
			free( ident );        // z nazwy typu 
			ident = c;

			// Sprawdz poprawno¶æ identyfikatorów
			//---------------------------------------
			if( sprID2( ident ) != 0 ) 
				throw ERR_ID;
		
			// sprID lista
			elchar = lista->first();
			while( elchar != NULL ) {
				
				c = clwhite( elchar->wsk());
				free( elchar->wsk());
				elchar->wsk( c );
				
				if( sprID2( elchar->wsk()) != 0 )
					throw ERR_ID;
				elchar = elchar->nast();
			}
		 	//---------------------------------------
			
			// je¿eli nid = NULL to mamy doczynienia
			// alba z def wej¶æ albo def. wyj¶æ
			if( nid == NULL ) {
	
				if(( i = keyword( ident )) == 0 )
					throw ERR_KEYW;		

				elchar = lista->first();
				while( elchar != NULL ) {
				
					// dodaj do STRUKTURY WE/WY
					// o id = el->wsk();
				
					DefEl = new StDefEl;
					DefEl->listaWe = NULL;
					DefEl->id = strdup( elchar->wsk());
					switch( i ) {
					
						case 1: DefEl->typ = strdup( "input" );
							break;
						case 2: DefEl->typ = strdup( "output" );
					}
					
					listaEl->dodaj( DefEl, I89_linia );
					// zniszcz elchar ?
					elchar = elchar->nast();
				}
			

			} else {
			
		
				// sprID nid
				c = clwhite( nid );
				free( nid );
				nid = c;
			
				if( sprID2( nid ) != 0 )
					throw ERR_ID;
				
				// dodaj do STRUKTURY element
				// o id = nid, typie = ident 
				// i li¶cie wej¶c = lista
				
				DefEl = new StDefEl;
				DefEl->id = nid;
				
				/*	 	TO UPCASE ????		     */
				//for( i=0; i < strlen( ident ); i++ )
				//	ident[i]=tolower( ident[i] );
				//==========================================//
				
				nid = strupcase( ident );
				free( ident );
				
				DefEl->typ = nid;
				DefEl->listaWe = lista;
				listaEl->dodaj( DefEl, I89_linia );
			}
	
		}

	}

	catch( int __ERROR__ ) { 
		
		//cerr << "***ERROR:[analizaISCAS89] linia: " << linia 
		//     << " :: " << bufln << endl;
		err = __ERROR__; 
	}
	
	}
	
	return err;
}
