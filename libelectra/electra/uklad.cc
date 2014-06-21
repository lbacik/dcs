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
 
 
/*

	Uk�ad

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
const int 	ERR_CUT_neMEM	= 0x02; // brak pami�ci

	char *uklad_err_mesg[] = {
	     "id elementu nie jest unikalne",
	     "brak pami�ci." };

char* uklad_err( int err )
{
	return uklad_err_mesg[err];
}

/*
	Prosty przeka�nik sygna�u
	Klasa podstawowa linii, bramek, uk�ad�w.
	
	
*/

	class TPPS {

		private:

			// Identyfikator przeka�nika
			char * _id;
			
			// Lista wej�� i wyj��
			TLista<TPPS*> *_We, *_Wy;

			/*
			 * Lista We/Wy jest list� element�w: wska�nik + int.  
			 * Wska�nik na li�cie element�w odnosi si� ( wskazuje )
			 * element po��czony z danym wej�ciem/wyj�ciem,
			 * warto�� int okre�la warto�� na danym we/wy.
			 */

		public:

			TPPS( char* );
		        ~TPPS( void );

			/* Dost�p do prywatnych sk�adowych */
			
			char* id( void );  // Zwraca wska�nik na ci�g "_id".		
			TLista<TPPS*>* We( void );	// 
			TLista<TPPS*>* Wy( void );	//		

			/* metody WIRTUALNE */
			
			virtual void przelicz( void );

			/*
			 * przelicz() jest metod� abstrakcyjn� - powinna by� ona 
			 * zdeklarowana w KA�DEJ klasie pochodnej. 
			 * Metoda ma za zadanie zapewni� odpowiednie, dla rodzaju
			 * przeka�nika, obliczanie stan�w wyj�ciowych wg stan�w
			 * wej�ciowych. 
			 * 
			 */
			
			virtual void set( int, ... );

			/*
			 * set() to wirtualna metoda przeka�nika przeznaczona
			 * do ustawienia jego stanu pocz�tkowego. 
			 *
			 */
			
			virtual void reset( void );

			/*
			 * Metoda "zeruje" stany wszystkich wej�� i wyj��.
			 * Powinna by� pokryta w klasach pochodnych, w kt�rych
			 * s� zadeklarowane jakie� dodatkowe elementy 
			 * "pami�taj�ce".
			 * 
			 */

			/* metody zdeklarowane */
		
			void reset( TLista<TPPS*> *lista );
			
			/*
			 * Po prostu "reset" warto�ci element�w na przekazanej
			 * jako parametr li�cie.
			 *
			 */
			
			int odbierzSygnal( int, TPPS* );

			/*
			 * odbierzSygnal() - metoda sprawdza czy na li�cie wej��
			 * jest zapisany wska�nik do elementu wysty�aj�cego sygna�
			 * ( parametr TPPS* ), je�eli tak to warto�� przekazywanego
			 * sygna�u jest zapisywana na li�cie wej�� ( przy wska�niku
			 * nadawcy - patrz deklaracje TLista i TElement ).
			 * 
			 * Funkcja NIE przerywa dzia�ania po odnalezieniu pierwszego,
			 * r�wnego warto�ci parametru wej�ciowego, wska�nika na li�cie
			 * wej�� ukadu - przeszukiwanie jest kontynu�owane a� do 
			 * ko�ca listy.
			 * 
			 * Warto�� zwracana.
			 *
			 * Metoda zwraca 0 je�eli element "wysy�aj�cy" sygna� ( o 
			 * wska�niku przekazanym jako argument funkcji ) NIE znajduje
			 * si� na li�cie wej��.
			 *
			 * Medoda zwraca 1 je�eli wszystko jest tak jak by� powinno :)
			 *
			 * Metoda zwraca warto�� >1 je�eli element, na li�cie wej�� ma
			 * przypisany wska�nik do jednego i tego samego elementu w
			 * kilku miejscach ( na kilku pozycjach ).
			 * 
			 */
		
			void przekazSygnal( void ); 
		
			/* 
			 * przekarzSygnal() - metoda wywo�uje, dla wszystkich element�w do
			 * kt�rych wska�niki zapisane s� w li�cie wyj��, metod�
		     	 * odbierzSygnal ( tych element�w ).
			 * 
			 */

	};

TPPS::TPPS( char* nid ) {

	
	_We = new TLista<TPPS*>; // Poniewa� obie listy s� listami zawieraj�cymi 
	_Wy = new TLista<TPPS*>; // jedynie wska�niki do zadeklarowanych obiekt�w
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

	return _id;	// mo�e: return strdup( _id ); ??

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


/* Ka�dy element na li�cie sk�ada si� z dwu warto�ci: 
 *	1. wska�nika
 *	2. liczby
 * Funkcja reset przyr�wnuje warto� "liczby" wszystkich element�w do
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
 * Poniewa� w podstawowej klasie PPS wyzerowania wymagaj� tylko lista
 * wyj�� i lista wej��, wi�c poni�sza funkcja w zupe�no�ci wystarcza.
 * W klasach pochodnych ( bardziej skomplikowanych ) mo�e ona wymaga�
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
	TElement<TPPS*> *el=_We->first();  // je�eli _We = NULL to program pada

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
 *	Linie ��cz� wszystkie elementy uk�adu. Nie mo�liwe jest ( b��dne ) 
 *	po��czenie bezpo�rednie ( z pomini�ciem obiektu klasy TLinia ) 
 *	pomi�dzy dwoma, r�nymi od linii, elementami uk�adu.
 *
 *	Ka�da linia mo�e posiada� maksymalnie jedno wej�cie i dowolnie 
 *	wiele wyj�� ( dla ilo�ci wyj�� >1 linia staje si� rozp�ywem ).
 *
 *	Linie s� jedynymi elementami mog�cymi by� "uszkadzanymi".
 *	W celu pami�tania uszkodze� zdefiniowanych przez u�ytkownika
 *	w klasie TLinia zadeklarowano dodatkow� list� dmgList, zawiera
 *	ona wska�niki do element�w b�d�cych na wyj�ciu(ach) obiektu
 *	TLinia, oraz warto�ci wymuszone dla po��cze� z tymi elementami
 *	- czyli warto�ci "sklejenia".
 *	Dla uszkodzenia statycznego lista dmgList zawiera wska�niki do
 *	wszystkich element�w b�dacych na wyj�ciu(ach) obiektu TLinia
 *	z jednakow� ( poami�tan� dla ka�dego wyj�cia osobno ) warto�ci� 
 *	wymuszon�.
 */

	class TLinia : public TPPS {

		private:

			// lista uszkodze�
			TLista<TPPS*> *dmgList;

		public:

			TLinia( char *nid );
			~TLinia( void );

			void uszkodzenie( int war, TPPS *p );
			/*
			 * Deklaracja uszkodzenia dynamicznego.
			 * 
			 * Wymu� warto�� war na po��czeniu z elementem p.
			 * Dla p = NULL deklaracja jest traktowana jako
			 * deklaracja uszkodzenia statycznego.
			 *
			 */

			// Deklaracja uszkodzenia statycznego
			void uszkodzenie( int war );
			
			void napraw( TPPS *p );
			/*
			 * Naprawia uszkodzenie linii na po��czeniu z
			 * elementem p.
			 */
			
			// Napraw WSZYSTKIE uszkodzenia.
			void napraw( void );

			void przelicz( void );
			/*
			 * metoda propaguje sygna� z wej�cia linii na 
			 * wszystkie jej wyj�cia z zachowaniem "poprawki"
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

		// je�eli element znajduje si� ju� na li�cie uszkodze�
		// to tylko zmie� warto�� wymuszon�
		if(( dmg = dmgList->znajdzEWsk( p )) != NULL ) 	
			dmg->war( war );

		// je�eli element NIE znajduje si� na li�cie uszkodze�
		// a znajduje si� na li�cie wyj�� to dopisz go
		// ( zraz z warto�ci� wymuszon� ) do listy uszkodze�
		else if(( dmg = Wy()->znajdzEWsk( p )) != NULL ) 
			dmgList->dodaj( p, war );

		// Je�eli element NIE znajduje si� na li�cie uszkodze� i NIE
		// znajduje si� na li�cie wyj�� to w sumie jest ERROR... :(
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
		// usu� WSZYSTKIE uszkodzenia
		dmgList->czysc();
	else
		// Usuni�cie z listy uszkodze� elementu zawieraj�cego przekazany
		// jako argument wska�nik spowiduje "naprawienie" danego
		// uszkodzenia dynamicznego
		dmgList->usunWEWsk( p );
}

void TLinia::napraw( void )
{
	// napraw wszystkie uszkodzenia = usu� wszystkie elementy
	// z listy uszkodze� 
	napraw( NULL );
}

void TLinia::przelicz( void ) {

	TElement<TPPS*> *el = Wy()->first(), *dmg;
	int sygnal = 0;
	
	// je�eli jest co� na wej�ciu...
	if( We()->first() != NULL ) 
		sygnal = We()->first()->war();
	// pytanie: Czy brak elementu wej�ciowego ma by� ignorowany ?
	
	while( el !=NULL ) {

		// je�eli wska�nik do elementu na wyj�ciu jest zapisany
		// na li�cie uszkodze� to przepisz ( na dane wyj�cie )
		// warto�� wymuszon�
		if(( dmg = dmgList->znajdzEWsk( el->wsk())) != NULL ) 
			el->war( dmg->war());
		// w przeciwnym razie przepisz sygna�.
		else 	el->war( sygnal );
			
		el = el->nast(); 
	}
}


//-------------------------------------------------------------- TUKLAD ------

	class TUklad : public TPPS {

		private:

			// Deklaracja list zawieraj�cych elementy uk�adu
			TLista<TPPS*> 	*_el_we,  // elementy wej�ciowe
					*_el_wew, // elementy wewn�trzne
					*_el_wy,  // wska�niki do element�w
					          // wyj�ciowych
					*_lines,  // linie
					*_el_dff; // przeka�niki
					
			// Deklaracja listy list element�w
			TLista<TLista<TPPS*>*> *_llist; 
			
			// przydatne w trakcie tworzenia po��cze�
			// pomi�dzy elementami uk�adu
			int nrLinii;
			// Zwraca wska�nik ( NULL oznacza b��d ) do
			// utworzonego obiektu klasy TLinia o identyfikatorze
			// r�wnym z�o�eniu przekazanych do funkcji argument�w
			TPPS* makeLine( const char *idl, int nrl );

		public:

			TUklad( char *nid );
			~TUklad( void );
	
			/* metody zwracaj�ce wska�niki na listy */
			
			TLista<TPPS*>* ewe() 	{ return _el_we; }
			TLista<TPPS*>* ewy() 	{ return _el_wy; }
			TLista<TPPS*>* El() 	{ return _el_wew; }
			TLista<TPPS*>* lines() 	{ return _lines; }
			TLista<TPPS*>* el_dff()	{ return _el_dff; };

			// wywo�uje metod� reset obiektu PPS oraz 
			// wywo�uje metody reset wszystkich obiekt�w PPS do 
			// kt�rych wska�niki zapisane s� na li�cie _llist
			void reset( void );

			// Funkcja zwraca ERR_CUT_nuID je�eli na jakiejkolwiek z list
			// element�w uk�adu znajduje si� element o ID przekazanym
			// jako parametr. Je�li ID jest unikalne wtedy funkcja zwraca "0".
			int uniqueID( char *nid );

			// dodanie definicji elementu
			int dodaj( TLista<TPPS*> *lista, TPPS* p );
			
			// zwraca wska�nik do elementu o id przekazanym jako parametr.
			TPPS* podaj_wsk( char *sid );
		
			
			// Je�eli wska�nik p znajduje si� na kt�rej� z list
			// zapisanych w _llist to funkcja zwr�ci wska�nik do
			// listy kt�ra zawiera wska�nik p.
			TLista<TPPS*>* listaEl( TPPS* p );
			
			// ��czy elementy
			//int polacz( TPPS *src, int swy, TPPS *dest, int dwe );
			int polacz( TPPS *dest, TPPS *src, int isr = 0 );
			int polacz( TPPS *dest, TPPS *src );

			// Ustawienie stanu pocz�tkowego uk�adu
			// set_dff
			void set( int, ... );
			
	};



TUklad::TUklad( char *nid )
       :TPPS( nid ) {

	_el_we = new TLista<TPPS*>( FE_wywolajDestWsk );
	_el_wy = new TLista<TPPS*>; // <- lista wsk do element�w na li�cie 
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

		// Je�eli dodawany jest element do listy _el_wy to NIE
		// sprawdzana jest unikalno�� ID elementu.
		if( lista != ewy() )
			if(( err = uniqueID( p->id())) != 0 )
				throw ERR_CUT_nuID;
		
		// Je�eli operacja dodawania elementu do listy zwraca
		// wska�nik pusty to to oznacza problem
		if( lista->dodaj( p ) == NULL )
			throw ERR_CUT_neMEM;
		
		// Je�eli dodoawane jest wej�cie uk�adu to nale�y pami�ta�
		// o uaktualnieniu listy We(). Dodatkowo "deklarwane" jest
		// wej�cie elementu wej�ciowehgo
		if( lista == ewe())
			if(( We()->dodaj( NULL ) == NULL ) ||
			   ( p->We()->dodaj( NULL ) == NULL ))
				throw ERR_CUT_neMEM;

		// Je�eli dodawane jest wyj�cie uk�adu to aktualizowana jest
		// lista Wy() i "deklarowane" jest wyj�cie elementu 
		// wyj�ciowego ( w przypadku jego braku ).
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
	

		// Je�eli ��czone ma by� wyj�cie nr. 4 elementu �r�d�owego
		// kt�ry takiego wyj�cia NIE MA, to trzeba je stworzy�
		while( src->Wy()->At( isr ) == NULL )
			src->Wy()->dodaj( NULL );
	
		// sprawdzam src na wy( isr ) czy ma zadeklarowan� linie
		if(( line = src->Wy()->At( isr )->wsk()) == NULL ) {

			// Tworzymy linie
			if(( line = makeLine( IDLN, nrLinii )) == NULL )
				throw ERR_CUT_neMEM;
			
			//po��cz linie
			src->Wy()->At( isr )->wsk( line );
			line->We()->dodaj( src );

		} else if( dest->We()->znajdzEWsk( line ) != NULL ) {	
		//listaEl( line ) != NULL ) {
		/*
		 * Ten warunek "naprawia" b��d symulatora wersji <= 2.2.
		 * Sprawdzane jest czy linia maj�ca by� po��czona z 
		 * elementem docelowym nie jest ju� z nim po��czona w innym
		 * miejscu. Je�eli tak, wtedy tworzona jest inna, nowa,
		 * linia - ma to na celu zachowanie RӯNYCH ( unikalnych ) 
		 * wska�nik�w na wszystkich wej�ciach elementu docelowego.
		 *
		 */
			src = line;

			// Tworzymy linie
			if(( line = makeLine( IDLN, nrLinii )) == NULL )
				throw ERR_CUT_neMEM;
			
			//po��cz linie
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
