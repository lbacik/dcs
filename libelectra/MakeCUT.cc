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
 *
 *
 */


#include <stdlib.h>
#include <string.h>

#include "../share/temlista.h"
#include "electra/uklad.h"
#include "electra/elements.h"

#include "types.h"

const int ERR_mCut_neMem = 	0x1;

	char *MakeCut_err_mesg[] = 
	     { "Brak pamiêci." };

int MCUT_ERR = 0;
int MCUT_ERR2 = 0;
int MCUT_ERR_l = 0;

const int ERR_INITE_nte 	= 0x01; // Niezrozumia³y typ elementu
const int ERR_INITE_ide		= 0x02; // identyfikator ju¿ istnieje
const int ERR_INITE_ID_OUT      = 0x03;


	char	*inite_err_mesg[] = {
		"Niezrozumia³y typ elementu.",
		"Element o takim identyfikatorze ju¿ istnieje.",
		"Nie istnieje element o takim identyfikatorze." 
	};

const int	SRC_INITE = 0;
const int	SRC_UKLAD = 1;

int ERR_SRC = SRC_INITE;

TLista<char*> *listaOut = NULL;

char* inite_err( int err )
{
	char *wynik;

	switch( ERR_SRC ) {

		case SRC_INITE: wynik = inite_err_mesg[err];
				break;
		case SRC_UKLAD: wynik = uklad_err( err );
				break;
	}
	
	return wynik;
}

/*
 *	DefiniujElement
 *				char *typ 	- typ elementu
 *				char *id	- identyfikator
 *				TUklad	*uklad 	- wska¼nik do klasy TUklad
 *						( mo¿e zast±piæ id uk³adu ?)
 *
 */

int newDef( char *nid, char *typ, TUklad *uklad ) {

		int err = 0;

		if( !strcmp( "input", typ )) {
	
			if( uklad->dodaj( uklad->ewe(),new TLinia( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "output", typ )) {

			if( listaOut == NULL ) 
				listaOut = new TLista<char*>;
			listaOut->dodaj( nid );
				
		} else if( !strcmp( "NOT", typ )) {

			if( uklad->dodaj( uklad->El(), new TNegacja( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "OR", typ )) {

			if(  uklad->dodaj( uklad->El(), new TOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "NOR", typ )) {

			if( uklad->dodaj( uklad->El(), new TNOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "AND", typ )) {

			if( uklad->dodaj( uklad->El(), new TAND( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "NAND", typ )) {

			if( uklad->dodaj( uklad->El(), new TNAND( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "XOR", typ )) {

			if( uklad->dodaj( uklad->El(), new TXOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "XNOR", typ )) {

			if( uklad->dodaj( uklad->El(), new TXNOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "DFF", typ )) {

			if( uklad->dodaj( uklad->el_dff(), new TDFF( nid ))
					!= 0 ) err = ERR_INITE_ide;
		
		} else err = ERR_INITE_nte;

		return err;
	}


int defOut( TUklad *uklad )
{
	TElement<char*> *el;
	TPPS *pps;
	int err = 0;
	
	if( listaOut != NULL ) {
		
		el = listaOut->first();
		while( el != NULL && !err ) {

			if(( pps = uklad->podaj_wsk( el->wsk())) != NULL ){
		
				if(( err = uklad->dodaj( uklad->ewy(), pps )) != 0 )
					ERR_SRC = SRC_UKLAD;

			} else err = ERR_INITE_ID_OUT;
				
			free( el->wsk());
			el->wsk( NULL );
			el = el->nast();
		}
		delete listaOut;
		listaOut = NULL;
	}
	return err;
}


int newJoin( char *idd, char *ids, TUklad *uklad, int is = 0 )
{
	TPPS *des, *src;
	int err = 0;
	
	if(( des = uklad->podaj_wsk( idd )) != NULL ) {
		if(( src = uklad->podaj_wsk( ids )) != NULL ) {
			if(( err = uklad->polacz( des, src, is )) != 0 )
				ERR_SRC = SRC_UKLAD;
		} else err = ERR_INITE_ide;//JOIN_neSRC;
	} else err = ERR_INITE_ide;//JOIN_neDST;
			
	return err;
}



char* MakeCut_err( int err  )
{
	char *wynik;
	
	if( MCUT_ERR == 1 ) wynik = MakeCut_err_mesg[err];
	else 		   wynik = inite_err( err );
	
	return wynik;
}

int MakeCUT_err_linia( void )
{
	return MCUT_ERR_l;
};

int MakeCUT( TLista<StDefEl*> *pListaEl, TUklad *uklad )
{
//	PUklad *pUklad;
	TElement<StDefEl*> *pElDef;
	TElement<char*> *elchar;
	int err = 0;

	MCUT_ERR = 0;
	MCUT_ERR2 = 0;

	try{
		if( uklad == NULL ) {
			MCUT_ERR = 1;
			throw ERR_mCut_neMem;
		}

		// Definiujemy elementy
		pElDef = pListaEl->first();
		while( pElDef != NULL ) {

			if(( err = newDef( pElDef->wsk()->id, 
					   pElDef->wsk()->typ,
					   uklad )) != 0 )
				
				throw err;
						
			pElDef = pElDef->nast();
		}

		//dowi±zanie wyj¶æ
		defOut( uklad );
		
		// £±czymy elementy
		pElDef = pListaEl->first();
		while( pElDef != NULL ) {

			if( pElDef->wsk()->listaWe != NULL ){
			
				elchar = pElDef->wsk()->listaWe->first();
				while( elchar != NULL ) {
					if(( err = newJoin( pElDef->wsk()->id, 
						   elchar->wsk(), uklad )) != 0 )
					throw err;
					elchar = elchar->nast();
				}
			}
						
			pElDef = pElDef->nast();
		}
	}

	catch( int __ERROR__ ) {

		MCUT_ERR2 = __ERROR__;
		MCUT_ERR_l = pElDef->war();
		//delete pUklad;
		//pUklad = NULL;
	}
	
	return err;
}
