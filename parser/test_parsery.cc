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
 
 


#include <iostream>

#include "../share/temlista.h"
#include "../ReadIn/readin.h"
#include "../libelectra/types.h"
#include "parsery.h"

struct StUstaw {

	char *plik_I89, *plik_I89D, *plik_in;

};

void pomoc( char *nazwa )
{
	using namespace std;

	cout << "%%% Testuj±cy biblioteki parserów" << endl;
	cout << "%%% £ukasz Bacik 2004" << endl;
	cout << "U¿ycie: " << nazwa << " [-h|--help] [-f {plik}] [-d {plik}] "
	     << "[-i {plik}]" << endl;
	cout << "gdzie:" << endl;
	cout << "\t-f {plik} - plik bench ISCAS89." << endl;
	cout << "\t-d {plik} - plik flt ISCAS89." << endl;
	cout << "\t-i {plik} - plik in." << endl;
}

int analiza_arg( int argc, char *argv[], StUstaw &ustaw )
{
	int i, err = 0;
	
	for( i = 1; i < argc; i++ ) {

		if( !strcmp( argv[i],"-h" ) || !strcmp( argv[i],"--help" )){

			pomoc( argv[0] );
			exit(0);
			
		} else if( !strcmp( argv[i], "-f" )) {

			if( i < argc - 1 ) ustaw.plik_I89 = argv[++i];
			else err = 1;
			
		} else if( !strcmp( argv[i], "-d" )) {

			if( i < argc - 1 ) ustaw.plik_I89D = argv[++i];
			else err = 1;

		} else if( !strcmp( argv[i], "-i" )) {

			if( i < argc - 1 ) ustaw.plik_in = argv[++i];
			else err = 1;

		} else {
		
			std::cout << "*** Niezrozumia³y parametr: " << argv[i]
				  << std::endl;
			std::cout << "Spróbuj: --help" << std::endl;
			err = 1;
		}
	}
	return err;
}

int test_parserI89( char *plik )
{
	int err = 0;
	TLista<StDefEl*> *lista;
	
	lista = new TLista<StDefEl*>;
	if(( err = readin( 	0, 
				4096, 
				100, 
				plik, 
			  	(void*)lista, 
				&analizaISCAS89 
		)) == 0 )
		dbg_wypiszLEl( lista );
	
	delete lista;
	return err;
}

int test_parserI89D( char *plik )
{
	int err = 0;
	TLista<TDmg*> *lista;
	
	lista = new TLista<TDmg*>;
	if(( err = readin( 	0, 
				4096, 
				100, 
				plik, 
			  	(void*)lista, 
				&analizaISCAS89Dmg 
		)) == 0 )
		dbg_wypiszLDmg( lista );
	
	delete lista;
	return err;
}

int test_parserIn( char *plik )
{
	int err = 0;
	TLista<char*> *lista;
	
	lista = new TLista<char*>;
	if(( err = readin( 	0, 
				4096, 
				100, 
				plik, 
			  	(void*)lista, 
				&analizaInSig
		)) == 0 )
		dbg_wypiszLWe( lista );
	
	delete lista;
	return err;
}

int main( int argc, char *argv[] )
{
	int err = 0;
	StUstaw ustaw;

	ustaw.plik_I89 = ustaw.plik_I89D = ustaw.plik_in = NULL;

	if( argc < 1 ) pomoc( argv[0] );
	else 
	
		if(( err = analiza_arg( argc, argv, ustaw )) == 0 ) {

			if( ustaw.plik_I89 != NULL )
				err = test_parserI89( ustaw.plik_I89 );

			if(( ustaw.plik_I89D != NULL ) && ( err == 0 ))
				err = test_parserI89D( ustaw.plik_I89D );

			if(( ustaw.plik_in != NULL ) && ( err == 0 ))
				err = test_parserIn( ustaw.plik_in );
		}
	
	return err;
}

