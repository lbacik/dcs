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

		Debug klasy uklad

*/

#include <stdlib.h>
#include <iostream>

#include "../../share/temlista.h"
#include "uklad.h"

using namespace std;

void dbg_wypiszLinie( TLinia *A ) {

	using namespace std;	

	cout << A->id() << " (" << A << ") ";
	
}

void dbg_wypiszWEWY( TLista<TPPS*> *l, int t ) {

	TElement<TPPS*> *p, *el;// = l->first();
	int i,j;

	using namespace std;	

	for( i = 0; i < l->ilosc(); i++ ) {
		
		p = l->At(i);

		for( j=0; j<t; j++ ) cout <<"\t";

		//-------------------------------------
		if( p->wsk() != NULL ) {	

			cout << p->wsk()->id();
			cout << " ( " << p->wsk() << " ) --> ";
				
			if( p->wsk()->Wy() != NULL ){
				
			    el = p->wsk()->Wy()->first();
			    while( el != NULL ) {		
						
				cout << el->wsk()->id() << " ";
				el=el->nast();
			   }
			}
			else cout << "(null)";
		}
		else cout << "(null)";
		//--------------------------------------
		
		cout << endl;
	}
}

void dbg_wypiszWE( TLista<TPPS*> *l, int t ) {

	TElement<TPPS*> *p, *el;// = l->first();
	int i,j;

	using namespace std;	
	
	for( i = 0; i < l->ilosc(); i++ ) {
		
		p = l->At(i);

		for( j=0; j<t; j++ ) cout <<"\t";

		//-------------------------------------
		if( p->wsk() != NULL ) {	

			cout << p->wsk()->id();
			cout << " ( " << p->wsk() << " ) <-- ";
				
			if( p->wsk()->We() != NULL ){
				
			    el = p->wsk()->We()->first();
			    while( el != NULL ) {		
						
				cout << el->wsk()->id() << " ";
				el=el->nast();
			   }
			}
			else cout << "(null)";
		}
		else cout << "(null)";
		//--------------------------------------
		
		cout << endl;
	}
}


void dbg_wypiszElement( TPPS* A, int t ) {

	TElement<TPPS*> *p;
	int i;

	using namespace std;	

	if( A != NULL ) {
		
		for( i=0; i<t; i++ ) cout <<"\t";
		cout << A->id() << " (" << A << ") " << endl;

		for( i=0; i<t; i++ ) cout <<"\t";
		cout << "WE ( " << A->We()->ilosc() << " ) " << endl;
		dbg_wypiszWE( A->We(), t+1);
	
		for( i=0; i<t; i++ ) cout <<"\t";
		cout << "WY ( " << A->Wy()->ilosc() << " ) " << endl;
		dbg_wypiszWEWY( A->Wy(), t+1);
	}
	cout << endl;
	
}

void dbg_wypiszListeEl( TLista<TPPS*> *l, int t ) {

	for( int i=0; i< l->ilosc(); i++ ) 
		dbg_wypiszElement( l->At(i)->wsk(),t );
}

void dbg_wypiszElementy2( TUklad *uklad ) {

	using namespace std;	
	
	cout << "Scheme: " << uklad->id() << " ( " << uklad << " )" << endl;
	cout << "We ( " << uklad->We()->ilosc() << " )" << endl;
	dbg_wypiszWE( uklad->We(),1);

	cout << "Wy ( " << uklad->Wy()->ilosc() << " )" << endl;
	dbg_wypiszWEWY( uklad->Wy(),1);

	cout << "Elementy we: ( " << uklad->ewe()->ilosc() << " )" << endl;
	dbg_wypiszListeEl( uklad->ewe(),1);
	
	cout << "Elementy wy: ( " << uklad->ewy()->ilosc() << " )" << endl;
	dbg_wypiszListeEl( uklad->ewy(),1);

	cout << "Elementy wewnêtrzne: ( "<< uklad->El()->ilosc()
		<< " ) " << endl;
	dbg_wypiszListeEl( uklad->El(),1);	
	dbg_wypiszListeEl( uklad->el_dff(),1);

}


