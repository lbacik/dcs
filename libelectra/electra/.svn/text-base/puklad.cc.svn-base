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
 *		Uk³ad + propagacja
 *
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../share/temlista.h"
#include "uklad.h"

#include "elements.h" // <-- to mi siê tu nie podoba
 		      //     jedyny powód: stabilizacja przerzutników w
		      //     metodzie puklad::przelicz()
		      
//#include "../../debug/debug.h"
extern void dbg_przeliczony( char *id, TPPS *p );

/*
 *
 *			FALA
 *
 */


//const int	CUT_FDB_Pro	= 0x1;
//const int	CUT_FDB_Fal	= 0x2;

	class TFala : public TLista<TPPS*> {

		private:
		
			TLista<TPPS*> *kolejka;
			TElement<TPPS*> *akt;
			int f_dbg; 
			
		public:
			TFala();
			~TFala(void);

			TElement<TPPS*>* aktualny() { return akt; };
			
			void czysc();

			/*
			 * dodaje elementy listy "l" do g³ównej listy
			 */
			void init( TLista<TPPS*> *l );

			/*
			 * Wywo³uje procedurê przekarzSygnal dla elementów
			 * bêd±cych na wyj¶ciach elementów listy "l" oraz
			 * dodaje te elementy wyj¶ciowe do kolejki.
			 * 
			 */
			void dodajl( TLista<TPPS*> *l );
			
			/*
			 * Dodaje elementy listy listaWy do kolejki
			 *
			 */
			void dodajDoKol( TLista<TPPS*> *listaWy );

			/*
			 * Wybiera element z kolejki
			 *
			 */
			TPPS* wybierzZKol( void );
			void przeliczKrok( void );

	};

TFala::TFala()
      :TLista<TPPS*>() {

	kolejka = new TLista<TPPS*>;
	akt = NULL;
	
}

TFala::~TFala() {

	delete kolejka;
}


void TFala::czysc() {
	   
	TLista<TPPS*>::czysc();
	kolejka->czysc();
	akt = NULL;
}

void TFala::dodajDoKol( TLista<TPPS*> *listaWy ) {

	TElement<TPPS*> *p;
	
	if( listaWy != NULL ) {
		
		p = listaWy->first();
		while( p != NULL ) {

			if( p->wsk() != NULL )
				kolejka->dodaj( p->wsk() );

			p = p -> nast();
		}
	}

}

TPPS* TFala::wybierzZKol( void ) {

	TElement<TPPS*> *p = kolejka->first();
	TPPS *wynik = NULL;
	
	while(( p != NULL ) && ( wynik == NULL )) {

	/*
	 * Najpierw próba wybrania elementu którego ilo¶æ wej¶æ
	 * równa jest ilo¶ci wyst±pieñ na li¶cie "kolejka" - to znaczy
	 * elementu z _kompletem_ sygna³ów wej¶ciowych.
	 * 
	 */
		
		if( kolejka->iloscWystapien( p->wsk()) 
			== p->wsk()->We()->ilosc() ) {
			 
			wynik = (p->wsk());
			kolejka->usunWEWsk( p->wsk() );
		}
			 
		p = p->nast();	
	} 

	/*
	 * Je¿eli akurat w kolejce nie ma elementu z ustalonymi wszystkimi
	 * stanami wej¶ciowymi to wybierany jest ( o ile istnieje )
	 * element pierwszy.
	 */
	if(( wynik == NULL ) && ( kolejka->first() != NULL ) &&
	   ( kolejka->first()->wsk() != NULL )) 
		wynik = kolejka->first()->wsk();

	return wynik;
}

void TFala::init( TLista<TPPS*> *l ) {

	TElement<TPPS*> *p=l->first();
	
	while( p != NULL ) {

		dodaj( p->wsk());
		p = p->nast();
	}

	akt = first();
}

void TFala::dodajl( TLista<TPPS*> *l )
{
	TElement<TPPS*> *p = l->first();

	while( p != NULL ) {

		p->wsk()->przekazSygnal();
		dodajDoKol( p->wsk()->Wy() );

		p = p->nast();
	}
}

void TFala::przeliczKrok( void ) {

	TPPS *p = NULL;
		
		if( akt->wsk() != NULL ) {

			akt->wsk()->przelicz();
			akt->wsk()->przekazSygnal();
			dodajDoKol( akt->wsk()->Wy() );
		}	
				
		if( akt->nast() == NULL ) {
			
			while(( p = wybierzZKol()) != NULL ) {
				
				if(( strstr( p->id(),IDLN ) != NULL ) ||
			   	   ( iloscWystapien( p ) < p->We()->ilosc())){
	
					dodaj( p );
					break;
					
				} 
				else 	kolejka->usunWEWsk( p );
					
			}
		}
		
		if( akt != NULL ) akt = akt->nast();
}


/*
 *
 *
 *
 *	Klasa PUklad
 *
 *
 *
 *
 *
 *
 *
 */


	class PUklad : public TUklad {

		private:

			// wska¼nik do obiektu zarz±dzaj±cego propagacj±
			TFala *fala;
			int 	f_dbg,	  // poziom debagowania
				f_dff; 	  // stabilizacja przerzutników
					  // 0 	- stabilizuj
					  // 1   - nie stabilizuj
			
			void ustawWe();
			/*
			 * ustawWe() "przenosi" warto¶ci z listy wej¶æ uk³adu
			 * na wej¶cia elementów listy elementów wej¶ciowych.
			 *
			 */
		
		public:
			void ustawWy();
			/*
			 * przenosi sygna³(y) z wyj¶æ elementów listy 
			 * elementów wyj¶ciowych na listê wyj¶æ uk³adu.
			 *
			 */
			
			
		//public:

			PUklad( char *nid );
			~PUklad( void );

			void dbg( int d );
			int dajNaWe( char *we );
			/*
			 * Ustawienie stanów na wej¶ciu uk³adu ( lista wej¶æ )
			 *
			 */
			
			char* pobierzWy( char* &wynik );
			/*
			 * Pobranie stanów z wyj¶æ uk³adu ( lista wyj¶æ )
			 * 
			 * /!\ Uwaga na prawid³owe ( wystarczaj±ce )
			 *     przydzielenie pamiêci dla zmiennej wynik !!!
			 *   
			 * Warto¶c zwracane to wska¼nik na ci±g "wynik".
			 *   
			 */
			 char* pobierzWe( char* &wynik );
			 char* pobierzDff( char* &wynik );

			void set_dff();
			void flag_dff( int );
			void przelicz();

	};

PUklad::PUklad( char *nid )
       :TUklad( nid ) {

	fala = new TFala;
	f_dbg = 0;
	f_dff = 0;

}

PUklad::~PUklad() {

	delete fala;
	
}

void PUklad::dbg( int d )
{
	f_dbg = d;
}

void PUklad::ustawWe() {

	TElement<TPPS*> *p=We()->first();
	int i = 0;

	while( p != NULL ) {

		// debugger dziwne rzeczy wipisuje dla
		// uk³adu z³o¿onego z poduk³adów i nie maj±cego
		// wej¶æ :( podej¿enie o BUGa mam tu...
		
		// warunki zosta³y dodane dla prawid³owego (?)
		// dzia³ania uk³adu z³o¿onego z poduk³±dów
		
		if(/*( p->wsk() != NULL ) && */
		   ( ewe()->At( i )->wsk()->We()->first() != NULL ))
			ewe()->At( i )->wsk()->We()->first()->war( p->war());
		i++;
		p = p->nast();
	}
}

void PUklad::ustawWy() {

	TElement<TPPS*> *p=ewy()->first();
	int i = 0;

	while( p != NULL ) {

		Wy()->At( i++ )->war( p->wsk()->Wy()->first()->war());
		p = p->nast();
	}
}

int PUklad::dajNaWe( char *we ) {

/*
 *
 *	[FIXME]	Ustawiæ warto¶æ zwracan±
 *
 */
	
	int i, err = 0, x;
	char *c;
	
	if( we != NULL ) {
		
		for( i=0; i < We()->ilosc(); i++ ) {

			if( i < strlen( we )) {
		
				c=strdup( &we[i] );
				c[1]='\0';
				x=atoi( c );
				free( c );
				We()->At( i )->war( x );

			} 
		}	
	}

	return err;
	
}

char* PUklad::pobierzWy( char* &wynik ) {

	TElement<TPPS*> *p = Wy()->first();
	int j = 0, i = Wy()->ilosc();
	
	while( p != NULL ) {

		if( j < i ) sprintf( &wynik[j++], "%d", p->war() );

		p = p->nast();
		
	}

	wynik[j]='\0';	
	return wynik;
	
}

char* PUklad::pobierzWe( char* &wynik ) {

	TElement<TPPS*> *p = We()->first();
	int j = 0, i = We()->ilosc();
	
	while( p != NULL ) {

		if( j < i ) sprintf( &wynik[j++], "%d", p->war() );

		p = p->nast();
		
	}

	wynik[j]='\0';	
	return wynik;	
}

char* PUklad::pobierzDff( char* &wynik ) {

	TElement<TPPS*> *p = el_dff()->first();
	int j = 0, i = el_dff()->ilosc();
	
	while( p != NULL ) {

		if( j < i ) sprintf( &wynik[j++], "%d", p->wsk()->Wy()->first()->war());

		p = p->nast();
		
	}

	wynik[j]='\0';	
	return wynik;
	
}

void PUklad::flag_dff( int f )
{
	f_dff = f;
}

void PUklad::set_dff()
{
	TElement<TPPS*> *el;
	
	el = el_dff()->first();
	while( el != NULL ) {

		((TDFF*)el->wsk())->setQ();
		el = el->nast();
	}

}

void PUklad::przelicz() {

	TPPS* p;
	TElement<TPPS*> *el;
	
	ustawWe();
	
	fala->dodajl( el_dff() );
	if(( p = fala->wybierzZKol() ) != NULL ) fala->dodaj( p ) ;
	fala->init( ewe() );

	while( fala->aktualny() != NULL ) { 

		p = fala->aktualny()->wsk();
		fala->przeliczKrok();
		
		//stabilizuj przerzutniki
		//if( f_dff == 0 ) set_dff(); // WIELKA ZAGADKA 
		//				- dlaczego to dzia³a³o w 
		//				v. 0.2-5 ?

		if( f_dbg & CUT_FDB_Pro ) //&& 
		   //( strstr( p->id(), IDLN ) == NULL ))
				dbg_przeliczony( id(), p );

	}
	fala->czysc();

	//stabilizuj przerzutniki
	if( f_dff == 0 ) set_dff();
	
	ustawWy();

}

/*
void TFala::dbg( char *c )
{
	TElement<TPPS*> *p;
	
	cout << c;
	cout << "il:" << ilosc();
	cout << ",K:" << kolejka->ilosc() << "(";
	p = kolejka->first();
	while( p != NULL ) {
		cout << p->wsk()->id();
		p = p->nast();
		if( p != NULL ) cout << ",";
	}
	cout << "),a:";
	if( akt != NULL ) cout << akt->wsk()->id();
	else		  cout << "(null)";

	cout << endl;
}

void TFala::dbg( char *c, char *wid )
{
	dbg( c );
	cout << "\twybrany z kolejki: " << wid << endl;
}

*/
