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
 *	Program testuj±cy budowê uk³adu
 *
 *
 *
 */

#include <iostream>
#include "../share/temlista.h"
#include "../ReadIn/readin.h"
#include "types.h"
#include "../parser/parsery.h"
#include "electra/uklad.h"
#include "electra/elements.h"
#include "electra/puklad.h"
#include "electra/ukdbg.h"
#include "MakeCUT.h"

int main( int argc, char* argv[] )
{
	
	TLista<StDefEl*> *lista;
	PUklad *puklad;
	int err = 0;

	if( argc != 2 ) {

		using namespace std;
		
		cout << "%% Test budowy uk³ady" << endl;
		cout << "U¿ycie: " << argv[0] << " plik_bench_ISCAS89 " << endl;
		exit(0);
	}

	lista = new TLista<StDefEl*>;
	if(( err = readin( 0, 4096, 80, argv[1], 
		          (void*)lista, 
			  &analizaISCAS89 )) == 0 ) {

		puklad = new PUklad( "scheme" );
		if(( err = MakeCUT( lista, puklad )) ==  0 ) {

			dbg_wypiszElementy2( puklad );

		}
	}

	return err;
}
