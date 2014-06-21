/*
 * elecra  - symulator uk�ad�w cyfrowych.
 * Copyright (C) 2003/2005 �ukasz Bacik
 *
 * Niniejszy program jest wolnym oprogramowaniem; mo�esz go 
 * rozprowadza� dalej i/lub modyfikowa� na warunkach Powszechnej
 * Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
 * Oprogramowania - wed�ug wersji 2-giej tej Licencji lub kt�rej�
 * z p�niejszych wersji. 
 *
 * Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on 
 * u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej 
 * gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH 
 * ZASTOSOWA�. W celu uzyskania bli�szych informacji - Powszechna 
 * Licencja Publiczna GNU. 
 *
 * Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz 
 * Powszechnej Licencji Publicznej GNU (GNU General Public License);
 * je�li nie - napisz do Free Software Foundation, Inc., 675 Mass Ave,
 * Cambridge, MA 02139, USA.
 *
 */

/*
 * electra - digital circuits simulator.
 * Copyright (C) 2003/2005 �ukasz Bacik
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
 
 

#include <iostream>
#include "../share/temlista.h"
#include "../libelectra/types.h"

using namespace std;

void dbg_wypiszLEl( TLista<StDefEl*> *listaEl )
{
	TElement<StDefEl*> *el;
	TElement<char*> *elchar;

	if( listaEl != NULL ) {
	
		el = listaEl->first();
		while( el != NULL ) {
		
			cout << "id: ";
			if( el->wsk()->id != NULL ) 
				cout << el->wsk()->id;
			else	cout << "(null)";
			
			cout << ", typ: ";
			if( el->wsk()->typ != NULL )
				cout << el->wsk()->typ;
			else	cout << "(null)";
			
			cout << ", we: ";
			if( el->wsk()->listaWe != NULL ) {
				elchar = el->wsk()->listaWe->first();
				while( elchar != NULL ) {
					cout << elchar->wsk() << " ";
					elchar = elchar->nast();
				}
			} else cout << "(null)";
			cout << endl;
			el = el->nast();
		}
	} else cout << "lista element�w = NULLL" << endl;
}

void dbg_wypiszLDmg( TLista<TDmg*> *listaDmg )
{
	TElement<TDmg*> *elDmg = listaDmg->first();
		
	while( elDmg != NULL ) {
	
		cout << "DMG ";
		cout << " id: "	  << elDmg->wsk()->id; 
		if( elDmg->wsk()->id_des != NULL )
			cout << " des: "  << elDmg->wsk()->id_des;
		cout << " war: " << elDmg->wsk()->war << endl;
		
		elDmg = elDmg->nast();
	}
}

void dbg_wypiszLWe( TLista<char*> *lwe )
{

	TElement<char*> *elchar = lwe->first();

	while( elchar != NULL ){

		cout << "Wej��ie: " << elchar->wsk() << endl;
		elchar = elchar->nast();
	}
}


