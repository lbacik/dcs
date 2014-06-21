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

	inite - tworzenie uk³adu

	Biblioteka powinna zawieraæ pe³ny interfejs do tworzenia uk³adów.
	

*/


//#include "libelectra.h"

#include <stdlib.h>
#include <string.h>

#include "../share/temlista.h"
#include "electra/pps.h"
#include "electra/elements.h"
#include "electra/dff.h"
#include "electra/fala.h"
#include "electra/uklad.h"
#include "electra/puklad.h"



const int ERR_INITE_nte 	= 0x01; // Niezrozumia³y typ elementu
const int ERR_INITE_ide		= 0x02; // identyfikator ju¿ istnieje
const int ERR_INITE_ID_OUT      = 0x03;

//const int ERR_INITE_JOIN_neDST	= 0x04; // 
//const int ERR_INITE_JOIN_neSRC  = 0x05; //

/*
const int ERR_INITE_bit 	= 0x22; // B³±d inicjacji elementu
const int ERR_INITE_nd  	= 0x23; // Niezrozumia³a definicja
//const int ERR_INITE_ische	= 0x04; // b³±d inicjacji 
const int ERR_INITE_nl		= 0x25; // nie liczba
const int ERR_INITE_jbz		= 0x26; // join - brak zrodel
const int ERR_INITE_bdu		= 0x27; // uklad->first() = NULL !!!
const int ERR_INITE_destne	= 0x28; // PPS dest nie istnieje!
const int ERR_INITE_bt		= 0x29; // brak typu
const int ERR_INITE_bi		= 0x2a; // brak id
const int ERR_INITE_bu		= 0x2b; // uklad->first()->wsk() == NULL !!!
const int ERR_INITE_ID_ne	= 0x2c; // PPS o podanym ID nie istnieje
const int ERR_INITE_ID_We_ne	= 0x2d; // Dla PPS o ID podane we nie istnieje.
const int ERR_INITE_lne		= 0x2e; // linia nie istnieje
const int ERR_INITE_bwu		= 0x2f; // b³êdna warto¶æ wymuszona
const int ERR_INITE_dest_jp	= 0x30; // dest by³ ju¿ ³±czony
const int ERR_INITE_src_jp	= 0x31; // src ju¿ po³±czony


const int ERR_INITE_bzn		= 0x33; // id zawiera z³y znak

const int ERR_INITE_newinout_what = 0x50; // z³a warto¶æ
const int ERR_INITE_ID_wyne	  = 0x53; //

const int ERR_OUT		  = 0x60;

const int ERR_INITE_srcne	= 0x100; // PPS src ( err - 0x100 )
//			       do 0x200	 //     nie istnieje ! 
*/
	char	*inite_err_mesg[] = {
		"Niezrozumia³y typ elementu.",
		"Element o takim identyfikatorze ju¿ istnieje.",
		"Nie istnieje element o takim identyfikatorze." 
	};

const int	SRC_INITE = 0;
const int	SRC_UKLAD = 1;

int ERR_SRC = SRC_INITE;

TLista<char*> *listaOut = NULL;

/*
int inite_err( int err ) {

	cerr << "*** ERROR INITE: "<< err;

	cerr.setf( ios::hex );
	cerr << " : 0x" << err << endl;
	cerr.setf( ios::dec );
	
	return ERR_inite;

}
*/

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
 *				PUklad	*uklad 	- wska¼nik do klasy PUklad
 *						( mo¿e zast±piæ id uk³adu ?)
 *
 */

int newDef( char *nid, char *typ, PUklad *uklad ) {

		int err = 0;

		if( !strcmp( "input", typ )) {
	
			if( uklad->dodaj( uklad->ewe(),new TLinia( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "output", typ )) {

			if( listaOut == NULL ) 
				listaOut = new TLista<char*>;
			listaOut->dodaj( nid );
				
		} else if( !strcmp( "not", typ )) {

			if( uklad->dodaj( uklad->El(), new TNegacja( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "or", typ )) {

			if(  uklad->dodaj( uklad->El(), new TOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "nor", typ )) {

			if( uklad->dodaj( uklad->El(), new TNOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "and", typ )) {

			if( uklad->dodaj( uklad->El(), new TAND( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "nand", typ )) {

			if( uklad->dodaj( uklad->El(), new TNAND( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "xor", typ )) {

			if( uklad->dodaj( uklad->El(), new TXOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "xnor", typ )) {

			if( uklad->dodaj( uklad->El(), new TXNOR( nid ))
					!= 0 ) err = ERR_INITE_ide;

		} else if( !strcmp( "dff", typ )) {

			if( uklad->dodaj( uklad->el_dff(), new TDFF( nid ))
					!= 0 ) err = ERR_INITE_ide;
		
		} else err = ERR_INITE_nte;

		return err;
	}


int defOut( PUklad *uklad )
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


int newJoin( char *idd, char *ids, PUklad *uklad, int is = 0 )
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


