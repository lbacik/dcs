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
 *	analiza plików *.flt ( ISCAS89 )
 *
 *	
 *
 *
 *
 */


#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "../share/temlista.h"
#include "../share/lfunc.h"
#include "../libelectra/types.h"

/*							[FIXME]
 * funkcje biblioteki iscas89rozbij zostan± zast±pione ( kiedy? )
 * funkcjami biblioteki lfunc.
 *
 */
#include "iscas89rozbij.h"
//#include "iscas89Dmg.h"


const int	ERR_nS		= 500; // nie podano uszkodzenia
const int	ERR_nl		= 501; // niezrozumia³a linia
const int	ERR_neMEM	= 502; // brak pamiêci

	char *analizaISCAS89Dmg_err_mesg[] = {
		"Nie podano uszkodzenia",
		"Niezrozumia³a linia.",
		"Brak pamiêci." };

int I89Dmg_linia;

char* analizaISCAS89Dmg_err( int err )
{
	return analizaISCAS89Dmg_err_mesg[err];
}

int I89D_nrLinii( void )
{
	return I89Dmg_linia;
}


/*
 *
 * funkcja podiera dwa parametry:
 *
 * 	bufln 		- wska¼nik na ci±g ( JEDN¡ liniê )
 *      struktura	- wska¼nik na obiekt TLista<TDmg*>, w którym
 *      		  funkcja zapisuje wynik swojego dzia³ania 
 *      		  ( je¿eli nie zakoñczy siê b³êdem )
 *
 * Warto¶ci± zwracan± jest ZERO lub kod b³êdu.
 * 
 * Dzia³anie ( oraz zasady wykorzystania ) funkcji analizuj±cych zawartych
 * w bibliotece "parsery" zosta³y przedstawione w opisie biblioteki.
 *
 */
int analizaISCAS89Dmg( char *bufln, void *struktura )
{
	int err = 0, i;
	TDmg *sDmg;
	//static int linia = 0;
	char *c, *ca, *cb, *tmp;

	// rzutowanie na wska¼nik void
	TLista<TDmg*> *lDmg = (TLista<TDmg*>*)struktura;
	
	I89Dmg_linia++;
	
 	// wytnij komentarz	
	if(( c = strchr( bufln, '#' /*ZNAK_KOMENTARZA*/ )) != NULL ) 
		bufln[ c - bufln ] = '\0';

	c = bufln;

	// czy w linii s± jakie¶ znaki
	i = strlen( c );
	while(( i > 0 ) && ( isspace( c[i] ))) i--;

	if( i > 0 ) try {

		// utwórz nowy element listy wynikowej
		sDmg = new TDmg;
	
		// Rozbij ci±g wej¶ciowy wg separatora "->"
		// f. I89rozbij2 ( zdefiniowana w bibliotece iscasI89rozbij )
		// zwraca '1' je¿eli ci±g we. ( pierwszy argument ) zawiera 
		// separator ( arg. drugi ), w przeciwnym razie 0.
		
		if( I89rozbij2( c,"->",ca,tmp )){
			
			// sklejenie dynamiczne

			// ca  - to co z prawej strony separatora
			// tmp - to co z lewej 
			
			sDmg->id = ca;
			
			// teraz czytam id_dest
			
			if( !I89rozbij2( tmp,"/",cb,tmp ))
				throw ERR_nS;
		
			sDmg->id_des = cb;

			// /!\ UWAGA -warto¶æ/warto¶ci sklejenia odczytywane
			// s± w dalszej czê¶ci funkcji - aktualnie wskazuje
			// na reprezentujcy je ci±g wska¼nik 'tmp'.
		
		} else {

			// sklejenie statyczne
			
			// czytam id elementu

			if( !I89rozbij2( c,"/",ca,tmp ))
				throw ERR_nS;
			
			sDmg->id = ca;

			// dla sklejenia statycznego id_des = NULL	
			sDmg->id_des=NULL;
		}

		ca = cb = NULL;
		if( !I89rozbij2( tmp,"/",ca,cb )) ca = tmp;
		
		if( !czyLiczba( ca )) throw ERR_nl;
		sDmg->war = atoi( ca );
		if( lDmg->dodaj( sDmg ) == NULL ) throw ERR_neMEM;
		
		if( cb != NULL ) {
		
			if( !czyLiczba( cb )) throw ERR_nl;
			
			TDmg *sDmg2 = new TDmg;
			sDmg2->id = strdup( sDmg->id );
			
			if( sDmg->id_des != NULL )
				
				sDmg2->id_des = strdup( sDmg->id_des );
			
			else sDmg2->id_des = NULL;
			
			sDmg2->war = atoi( cb );
			
			if( lDmg->dodaj( sDmg2 ) == NULL ) throw ERR_neMEM;
		}
	}//try

	catch( int __ERROR__ ) { err = __ERROR__; }
		
	return err;
}
