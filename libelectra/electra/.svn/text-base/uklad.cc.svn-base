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

	Uk³ad

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "../../share/temlista.h"

const char IDLN[] = "l#";

const int	CUT_FDB_Pro	= 0x1;
const int	CUT_FDB_Fal	= 0x2;
const int 	ERR_CUT_nuID	= 0x01; // id elementu nie jest unikalne
const int 	ERR_CUT_neMEM	= 0x02; // brak pamiêci

	char *uklad_err_mesg[] = {
	     "id elementu nie jest unikalne",
	     "brak pamiêci." };

char* uklad_err( int err )
{
	return uklad_err_mesg[err];
}

/*
	Prosty przeka¼nik sygna³u
	Klasa podstawowa linii, bramek, uk³adów.
	
	
*/

	class TPPS {

		private:

			// Identyfikator przeka¼nika
			char * _id;
			
			// Lista wej¶æ i wyj¶æ
			TLista<TPPS*> *_We, *_Wy;

			/*
			 * Lista We/Wy jest list± elementów: wska¼nik + int.  
			 * Wska¼nik na li¶cie elementów odnosi siê ( wskazuje )
			 * element po³±czony z danym wej¶ciem/wyj¶ciem,
			 * warto¶æ int okre¶la warto¶æ na danym we/wy.
			 */

		public:

			TPPS( char* );
		        ~TPPS( void );

			/* Dostêp do prywatnych sk³adowych */
			
			char* id( void );  // Zwraca wska¼nik na ci±g "_id".		
			TLista<TPPS*>* We( void );	// 
			TLista<TPPS*>* Wy( void );	//		

			/* metody WIRTUALNE */
			
			virtual void przelicz( void );

			/*
			 * przelicz() jest metod± abstrakcyjn± - powinna byæ ona 
			 * zdeklarowana w KA¯DEJ klasie pochodnej. 
			 * Metoda ma za zadanie zapewniæ odpowiednie, dla rodzaju
			 * przeka¼nika, obliczanie stanów wyj¶ciowych wg stanów
			 * wej¶ciowych. 
			 * 
			 */
			
			virtual void set( int, ... );

			/*
			 * set() to wirtualna metoda przeka¼nika przeznaczona
			 * do ustawienia jego stanu pocz±tkowego. 
			 *
			 */
			
			virtual void reset( void );

			/*
			 * Metoda "zeruje" stany wszystkich wej¶æ i wyj¶æ.
			 * Powinna byæ pokryta w klasach pochodnych, w których
			 * s± zadeklarowane jakie¶ dodatkowe elementy 
			 * "pamiêtaj±ce".
			 * 
			 */

			/* metody zdeklarowane */
		
			void reset( TLista<TPPS*> *lista );
			
			/*
			 * Po prostu "reset" warto¶ci elementów na przekazanej
			 * jako parametr li¶cie.
			 *
			 */
			
			int odbierzSygnal( int, TPPS* );

			/*
			 * odbierzSygnal() - metoda sprawdza czy na li¶cie wej¶æ
			 * jest zapisany wska¼nik do elementu wysty³aj±cego sygna³
			 * ( parametr TPPS* ), je¿eli tak to warto¶æ przekazywanego
			 * sygna³u jest zapisywana na li¶cie wej¶æ ( przy wska¼niku
			 * nadawcy - patrz deklaracje TLista i TElement ).
			 * 
			 * Funkcja NIE przerywa dzia³ania po odnalezieniu pierwszego,
			 * równego warto¶ci parametru wej¶ciowego, wska¼nika na li¶cie
			 * wej¶æ ukadu - przeszukiwanie jest kontynu³owane a¿ do 
			 * koñca listy.
			 * 
			 * Warto¶æ zwracana.
			 *
			 * Metoda zwraca 0 je¿eli element "wysy³aj±cy" sygna³ ( o 
			 * wska¼niku przekazanym jako argument funkcji ) NIE znajduje
			 * siê na li¶cie wej¶æ.
			 *
			 * Medoda zwraca 1 je¿eli wszystko jest tak jak byæ powinno :)
			 *
			 * Metoda zwraca warto¶æ >1 je¿eli element, na li¶cie wej¶æ ma
			 * przypisany wska¼nik do jednego i tego samego elementu w
			 * kilku miejscach ( na kilku pozycjach ).
			 * 
			 */
		
			void przekazSygnal( void ); 
		
			/* 
			 * przekarzSygnal() - metoda wywo³uje, dla wszystkich elementów do
			 * których wska¼niki zapisane s± w li¶cie wyj¶æ, metodê
		     	 * odbierzSygnal ( tych elementów ).
			 * 
			 */

	};

TPPS::TPPS( char* nid ) {

	
	_We = new TLista<TPPS*>; // Poniewa¿ obie listy s± listami zawieraj±cymi 
	_Wy = new TLista<TPPS*>; // jedynie wska¼niki do zadeklarowanych obiektów
				 // PPS, dlatego NIE USTAWIONA jest flaga:
				 // FE_wywolajDestWsk klasy TLista.
	_id = strdup( nid );
	
}

TPPS::~TPPS( void ) {

	delete _We;
	delete _Wy;
	free( _id );
}

char* TPPS::id( void ) {

	return _id;	// mo¿e: return strdup( _id ); ??

}

TLista<TPPS*>* TPPS::We( void ) {

	return _We;

}

TLista<TPPS*>* TPPS::Wy( void ) {

	return _Wy;

}

void TPPS::przelicz( void )
{
}

void TPPS::set( int firstint, ... )
{
}


/* Ka¿dy element na li¶cie sk³ada siê z dwu warto¶ci: 
 *	1. wska¼nika
 *	2. liczby
 * Funkcja reset przyrównuje warto¶ "liczby" wszystkich elementów do
 * ZERA.
 */

void TPPS::reset( TLista<TPPS*> *lista )
{
	TElement<TPPS*> *el;

	el = lista->first();
	while( el != NULL ) {

		el->war( 0 );
		el = el->nast();
	}
		
}

/*
 * Poniewa¿ w podstawowej klasie PPS wyzerowania wymagaj± tylko lista
 * wyj¶æ i lista wej¶æ, wiêc poni¿sza funkcja w zupe³no¶ci wystarcza.
 * W klasach pochodnych ( bardziej skomplikowanych ) mo¿e ona wymagaæ
 * pokrycia.
 *
 */

void TPPS::reset( void )
{
	reset( We() );
	reset( Wy() );
}

int TPPS::odbierzSygnal( int syg, TPPS* p )
{
	int OK=0; 			  
	TElement<TPPS*> *el=_We->first();  // je¿eli _We = NULL to program pada

	while( el!=NULL && !OK ) {
	
		if( el->wsk() == p ) {
		
			el->war( syg );
			OK++;
		}
		
		el=el->nast();	
	}	

	return OK;		
}

void TPPS::przekazSygnal( void )
{
	TElement<TPPS*> *el=_Wy->first();

	while( el!=NULL ) {
	
		if( el->wsk() != NULL ) 
			el->wsk()->odbierzSygnal( el->war(), this );
		
		el = el->nast();
	}
}


//------------------------------------------------------- LINIA -----------------


/*
 *	Linie ³±cz± wszystkie elementy uk³adu. Nie mo¿liwe jest ( b³êdne ) 
 *	po³±czenie bezpo¶rednie ( z pominiêciem obiektu klasy TLinia ) 
 *	pomiêdzy dwoma, ró¿nymi od linii, elementami uk³adu.
 *
 *	Ka¿da linia mo¿e posiadaæ maksymalnie jedno wej¶cie i dowolnie 
 *	wiele wyj¶æ ( dla ilo¶ci wyj¶æ >1 linia staje siê rozp³ywem ).
 *
 *	Linie s± jedynymi elementami mog±cymi byæ "uszkadzanymi".
 *	W celu pamiêtania uszkodzeñ zdefiniowanych przez u¿ytkownika
 *	w klasie TLinia zadeklarowano dodatkow± listê dmgList, zawiera
 *	ona wska¼niki do elementów bêd±cych na wyj¶ciu(ach) obiektu
 *	TLinia, oraz warto¶ci wymuszone dla po³±czeñ z tymi elementami
 *	- czyli warto¶ci "sklejenia".
 *	Dla uszkodzenia statycznego lista dmgList zawiera wska¼niki do
 *	wszystkich elementów bêdacych na wyj¶ciu(ach) obiektu TLinia
 *	z jednakow± ( poamiêtan± dla ka¿dego wyj¶cia osobno ) warto¶ci± 
 *	wymuszon±.
 */

	class TLinia : public TPPS {

		private:

			// lista uszkodzeñ
			TLista<TPPS*> *dmgList;

		public:

			TLinia( char *nid );
			~TLinia( void );

			void uszkodzenie( int war, TPPS *p );
			/*
			 * Deklaracja uszkodzenia dynamicznego.
			 * 
			 * Wymu¶ warto¶æ war na po³±czeniu z elementem p.
			 * Dla p = NULL deklaracja jest traktowana jako
			 * deklaracja uszkodzenia statycznego.
			 *
			 */

			// Deklaracja uszkodzenia statycznego
			void uszkodzenie( int war );
			
			void napraw( TPPS *p );
			/*
			 * Naprawia uszkodzenie linii na po³±czeniu z
			 * elementem p.
			 */
			
			// Napraw WSZYSTKIE uszkodzenia.
			void napraw( void );

			void przelicz( void );
			/*
			 * metoda propaguje sygna³ z wej¶cia linii na 
			 * wszystkie jej wyj¶cia z zachowaniem "poprawki"
			 * na uszkodzenia.
			 */
	};

TLinia::TLinia( char *nid )
       : TPPS( nid ) {

	dmgList = new TLista<TPPS*>;

}

TLinia::~TLinia( void ) 
{
	delete dmgList;
}

void TLinia::uszkodzenie( int war, TPPS *p )
{
	TElement<TPPS*> *el = Wy()->first(), *dmg;
	
	if( p == NULL ) { // ----- uszkodzenie statyczne
		
		dmgList->czysc();
		while( el != NULL ) {
			
			dmgList->dodaj( el->wsk(), war );
			el = el->nast();
		}
	
	} else { 	  // ----- uszkodzenie dynamiczne

		// je¿eli element znajduje siê ju¿ na li¶cie uszkodzeñ
		// to tylko zmieñ warto¶æ wymuszon±
		if(( dmg = dmgList->znajdzEWsk( p )) != NULL ) 	
			dmg->war( war );

		// je¿eli element NIE znajduje siê na li¶cie uszkodzeñ
		// a znajduje siê na li¶cie wyj¶æ to dopisz go
		// ( zraz z warto¶ci± wymuszon± ) do listy uszkodzeñ
		else if(( dmg = Wy()->znajdzEWsk( p )) != NULL ) 
			dmgList->dodaj( p, war );

		// Je¿eli element NIE znajduje siê na li¶cie uszkodzeñ i NIE
		// znajduje siê na li¶cie wyj¶æ to w sumie jest ERROR... :(
	}
}

void TLinia::uszkodzenie( int war )
{
	// uszkodzenie statyczne - prosta sprawa
	uszkodzenie( war, NULL );
}

void TLinia::napraw( TPPS *p )
{
	if( p == NULL ) 
		// usuñ WSZYSTKIE uszkodzenia
		dmgList->czysc();
	else
		// Usuniêcie z listy uszkodzeñ elementu zawieraj±cego przekazany
		// jako argument wska¼nik spowiduje "naprawienie" danego
		// uszkodzenia dynamicznego
		dmgList->usunWEWsk( p );
}

void TLinia::napraw( void )
{
	// napraw wszystkie uszkodzenia = usuñ wszystkie elementy
	// z listy uszkodzeñ 
	napraw( NULL );
}

void TLinia::przelicz( void ) {

	TElement<TPPS*> *el = Wy()->first(), *dmg;
	int sygnal = 0;
	
	// je¿eli jest co¶ na wej¶ciu...
	if( We()->first() != NULL ) 
		sygnal = We()->first()->war();
	// pytanie: Czy brak elementu wej¶ciowego ma byæ ignorowany ?
	
	while( el !=NULL ) {

		// je¿eli wska¼nik do elementu na wyj¶ciu jest zapisany
		// na li¶cie uszkodzeñ to przepisz ( na dane wyj¶cie )
		// warto¶æ wymuszon±
		if(( dmg = dmgList->znajdzEWsk( el->wsk())) != NULL ) 
			el->war( dmg->war());
		// w przeciwnym razie przepisz sygna³.
		else 	el->war( sygnal );
			
		el = el->nast(); 
	}
}


//-------------------------------------------------------------- TUKLAD ------

	class TUklad : public TPPS {

		private:

			// Deklaracja list zawieraj±cych elementy uk³adu
			TLista<TPPS*> 	*_el_we,  // elementy wej¶ciowe
					*_el_wew, // elementy wewnêtrzne
					*_el_wy,  // wska¼niki do elementów
					          // wyj¶ciowych
					*_lines,  // linie
					*_el_dff; // przeka¼niki
					
			// Deklaracja listy list elementów
			TLista<TLista<TPPS*>*> *_llist; 
			
			// przydatne w trakcie tworzenia po³±czeñ
			// pomiêdzy elementami uk³adu
			int nrLinii;
			// Zwraca wska¼nik ( NULL oznacza b³±d ) do
			// utworzonego obiektu klasy TLinia o identyfikatorze
			// równym z³o¿eniu przekazanych do funkcji argumentów
			TPPS* makeLine( const char *idl, int nrl );

		public:

			TUklad( char *nid );
			~TUklad( void );
	
			/* metody zwracaj±ce wska¼niki na listy */
			
			TLista<TPPS*>* ewe() 	{ return _el_we; }
			TLista<TPPS*>* ewy() 	{ return _el_wy; }
			TLista<TPPS*>* El() 	{ return _el_wew; }
			TLista<TPPS*>* lines() 	{ return _lines; }
			TLista<TPPS*>* el_dff()	{ return _el_dff; };

			// wywo³uje metodê reset obiektu PPS oraz 
			// wywo³uje metody reset wszystkich obiektów PPS do 
			// których wska¼niki zapisane s± na li¶cie _llist
			void reset( void );

			// Funkcja zwraca ERR_CUT_nuID je¿eli na jakiejkolwiek z list
			// elementów uk³adu znajduje siê element o ID przekazanym
			// jako parametr. Je¿li ID jest unikalne wtedy funkcja zwraca "0".
			int uniqueID( char *nid );

			// dodanie definicji elementu
			int dodaj( TLista<TPPS*> *lista, TPPS* p );
			
			// zwraca wska¼nik do elementu o id przekazanym jako parametr.
			TPPS* podaj_wsk( char *sid );
		
			
			// Je¿eli wska¼nik p znajduje siê na której¶ z list
			// zapisanych w _llist to funkcja zwróci wska¼nik do
			// listy która zawiera wska¼nik p.
			TLista<TPPS*>* listaEl( TPPS* p );
			
			// £±czy elementy
			//int polacz( TPPS *src, int swy, TPPS *dest, int dwe );
			int polacz( TPPS *dest, TPPS *src, int isr = 0 );
			int polacz( TPPS *dest, TPPS *src );

			// Ustawienie stanu pocz±tkowego uk³adu
			// set_dff
			void set( int, ... );
			
	};



TUklad::TUklad( char *nid )
       :TPPS( nid ) {

	_el_we = new TLista<TPPS*>( FE_wywolajDestWsk );
	_el_wy = new TLista<TPPS*>; // <- lista wsk do elementów na li¶cie 
				    // el_wew.
	_el_wew = new TLista<TPPS*>( FE_wywolajDestWsk );
	_lines = new TLista<TPPS*>( FE_wywolajDestWsk );
	_el_dff = new TLista<TPPS*>( FE_wywolajDestWsk );

	_llist = new TLista<TLista<TPPS*>*>;
	_llist->dodaj( _el_we );	// do listy _llist *NIE* dodawana
	_llist->dodaj( _el_wew );	// jest lista _el_wy
	_llist->dodaj( _lines );
	_llist->dodaj( _el_dff );

	nrLinii = 0;
}

TUklad::~TUklad( void ) {

	delete _el_wew;
	delete _el_we;
	delete _el_wy;
	delete _lines;
	delete _el_dff;
	delete _llist;

}

void TUklad::reset( void )
{
	TElement<TLista<TPPS*>*> *elist;
	TElement<TPPS*>		 *el;
	
	TPPS::reset();

	elist = _llist->first();
	while( elist != NULL ) {
	
		el = elist->wsk()->first();
		while( el != NULL ) {
			
			el->wsk()->reset();
			el = el->nast();
		}
		
		elist = elist->nast();
	}
	
}

int TUklad::uniqueID( char *id )
{
	int wynik = 0;
	TElement<TPPS*> *p;
	TElement<TLista<TPPS*>*> *elist;
	
	elist = _llist->first();
	while(( elist != NULL  )&&( wynik == 0 )) {
		
		p = elist->wsk()->first();
		while( p != NULL ) {
			
			if( strcmp(p->wsk()->id(), id ) == 0 ) { 
				wynik = ERR_CUT_nuID;
				break;
			}
			p = p->nast();
		}
		elist = elist->nast();
	}
	return wynik;
}

int TUklad::dodaj( TLista<TPPS*> *lista, TPPS *p )
{
	int err = 0;
	try {

		// Je¿eli dodawany jest element do listy _el_wy to NIE
		// sprawdzana jest unikalno¶æ ID elementu.
		if( lista != ewy() )
			if(( err = uniqueID( p->id())) != 0 )
				throw ERR_CUT_nuID;
		
		// Je¿eli operacja dodawania elementu do listy zwraca
		// wska¼nik pusty to to oznacza problem
		if( lista->dodaj( p ) == NULL )
			throw ERR_CUT_neMEM;
		
		// Je¿eli dodoawane jest wej¶cie uk³adu to nale¿y pamiêtaæ
		// o uaktualnieniu listy We(). Dodatkowo "deklarwane" jest
		// wej¶cie elementu wej¶ciowehgo
		if( lista == ewe())
			if(( We()->dodaj( NULL ) == NULL ) ||
			   ( p->We()->dodaj( NULL ) == NULL ))
				throw ERR_CUT_neMEM;

		// Je¿eli dodawane jest wyj¶cie uk³adu to aktualizowana jest
		// lista Wy() i "deklarowane" jest wyj¶cie elementu 
		// wyj¶ciowego ( w przypadku jego braku ).
		if( lista == ewy())
			if(( Wy()->dodaj( NULL ) == NULL ) ||
			   (( p->Wy()->first() == NULL ) &&
			    ( p->Wy()->dodaj( NULL ) == NULL )))
				throw ERR_CUT_neMEM;
	}

	catch( int __ERROR__ ) { err = __ERROR__; }
	return err;
}

TPPS* TUklad::podaj_wsk( char* sid ) {

	TElement<TLista<TPPS*>*> *elist;
	TElement<TPPS*> *p;
	TPPS *wsk = NULL;
	int i,j;
	
	elist = _llist->first();
	while( elist != NULL ){
		
		p = elist->wsk()->first();
		while(( p!=NULL ) && ( strcmp( p->wsk()->id(), sid )))
			p = p->nast();
		if( p != NULL ) { 
			wsk = p->wsk();
			break;
		}
		elist = elist->nast();
	}
	
	return wsk;
}

TLista<TPPS*>* TUklad::listaEl( TPPS *p ) {

	TElement<TLista<TPPS*>*> *elist;
	TElement<TPPS*> *el;
	TLista<TPPS*> *wynik = NULL;
	
	elist = _llist->first();
	while( elist != NULL ){

		el = elist->wsk()->first();
		while(( el !=NULL ) && ( wynik == NULL )) {

			if( el->wsk() == p ) wynik = elist->wsk();
			el = el->nast();
		}
		if( wynik != NULL ) break;
		elist = elist->nast();
	}

	return wynik;
	
}

TPPS* TUklad::makeLine( const char *idl, int nrl )
{
	char *idl_tmp, snrlinii[10];
	TPPS *line;
	
	//konwersja nrLinii na snrlinii
	sprintf( snrlinii,"%d",nrl );
	idl_tmp = (char*)malloc( strlen( idl ) + strlen( snrlinii ) + 1 );
	idl_tmp[0] = '\0';
	strcat( idl_tmp, idl );
	strcat( idl_tmp, snrlinii );
	
	if(( line = new TLinia( idl_tmp )) != NULL ) 
		if(( dodaj( lines(), line )) != 0 ) 
			line = NULL;

	free( idl_tmp );	
	nrLinii++;
	return line;
}

int TUklad::polacz( TPPS *dest, TPPS *src, int isr )
{

	int err = 0;
	char snrlinii[10], *idl;
	TPPS *line;
	TElement<TPPS*> *el;
	
	try {
	

		// Je¿eli ³±czone ma byæ wyj¶cie nr. 4 elementu ¼ród³owego
		// który takiego wyj¶cia NIE MA, to trzeba je stworzyæ
		while( src->Wy()->At( isr ) == NULL )
			src->Wy()->dodaj( NULL );
	
		// sprawdzam src na wy( isr ) czy ma zadeklarowan± linie
		if(( line = src->Wy()->At( isr )->wsk()) == NULL ) {

			// Tworzymy linie
			if(( line = makeLine( IDLN, nrLinii )) == NULL )
				throw ERR_CUT_neMEM;
			
			//po³±cz linie
			src->Wy()->At( isr )->wsk( line );
			line->We()->dodaj( src );

		} else if( dest->We()->znajdzEWsk( line ) != NULL ) {	
		//listaEl( line ) != NULL ) {
		/*
		 * Ten warunek "naprawia" b³±d symulatora wersji <= 2.2.
		 * Sprawdzane jest czy linia maj±ca byæ po³±czona z 
		 * elementem docelowym nie jest ju¿ z nim po³±czona w innym
		 * miejscu. Je¿eli tak, wtedy tworzona jest inna, nowa,
		 * linia - ma to na celu zachowanie RÓ¯NYCH ( unikalnych ) 
		 * wska¼ników na wszystkich wej¶ciach elementu docelowego.
		 *
		 */
			src = line;

			// Tworzymy linie
			if(( line = makeLine( IDLN, nrLinii )) == NULL )
				throw ERR_CUT_neMEM;
			
			//po³±cz linie
			src->Wy()->dodaj( line );
			line->We()->dodaj( src );

		}
		
		/* Kto odbiera ? */		
		
		dest->We()->dodaj( line );
		line->Wy()->dodaj( dest );
	}

	catch( int __ERROR__ ) { err = __ERROR__; }
	
	return err;
}

int TUklad::polacz( TPPS *dest, TPPS *src )
{
	return polacz( dest, src, 0 );
}

void TUklad::set( int firstint, ... )
{
	va_list argp;
	char *s;
	int len_s, i = 0, x;
	TElement<TPPS*> *el;

	va_start( argp, firstint );
	s = va_arg( argp, char* );
	
	len_s = strlen( s );	

	el = el_dff()->first();
	while( el != NULL ) {

		if( i < len_s ) 
			
			switch( s[i++] ) {

				case '0' : x = 0; break;
				default  : x = 1;
			}
		
		else x = 0;
		
		//((TDFF*)el->wsk())->set( x );
		el->wsk()->set( x );
		el = el->nast();
	}
	
}
