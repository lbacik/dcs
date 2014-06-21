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
#include <malloc.h>
//--
#include <string.h>
#include <iostream>
using namespace std;

#include "../share/temlista.h"
#include "electra/uklad.h"
//#include "electra/elements.h"
#include "electra/puklad.h"

#include "types.h"
#include "../share/lfunc.h"

int uklad_set_dff( PUklad *pUklad, char *s )
{
	int i, err = 0;

	for( i = 0; i < strlen( s ); i++ )
		if(( s[i] != '0' ) && ( s[i] != '1' )) {
			err = 1;
			break;
		}

	if( err == 0 ) pUklad->set( 0,s );
	
	return err;		
}

char* przelicz( PUklad* pUklad, char* we, int dbg )
{
	char *wy;
		
	pUklad->dajNaWe( we );
	pUklad->dbg( dbg );

	// poni¿sza linijka nie jest chyba tu na miejcu...
	if( dbg != 0 ) cout << endl; 
	
	pUklad->przelicz();
	
	wy=(char*)malloc( pUklad->Wy()->ilosc()+1);
	pUklad->pobierzWy( wy );
	
	return wy;	
}

void uklad_uszkodzenie( PUklad *pUklad, TDmg *dmg )
{
	TPPS *p, *des = NULL;
	TElement<TPPS*> *el;
	char *idd = NULL, *idd_des = NULL;
		
	idd = strupcase( dmg->id );
	idd_des = strupcase( dmg->id_des );
	
	p = pUklad->podaj_wsk( idd );
	if( idd_des != NULL )
		des = pUklad->podaj_wsk( idd_des );
	if( p != NULL ) {
		el = p->Wy()->first();
		while( el != NULL ) {
			if( el->wsk() != NULL )
				((TLinia*)el->wsk())->
					uszkodzenie( dmg->war, des );
			el = el->nast();
		}
	}

	free( idd );
	free( idd_des );
}

void uklad_napraw( PUklad *pUklad, TDmg *dmg )
{
	TPPS *p, *des = NULL;
	TElement<TPPS*> *el;
	char *idd = NULL, *idd_des = NULL;
	
	idd = strupcase( dmg->id );
	idd_des = strupcase( dmg->id_des );
	
	p = pUklad->podaj_wsk( idd );
	if( idd_des != NULL )
		des = pUklad->podaj_wsk( idd_des );
	if( p != NULL ) {
		el = p->Wy()->first();
		while( el != NULL ) {
			if( el->wsk() != NULL )
				((TLinia*)el->wsk())->napraw( des );
			el = el->nast();
		}
	}

	free( idd );
	free( idd_des );
}

