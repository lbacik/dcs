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

const char IDLN[] = "l#";

const int	CUT_FDB_Pro	= 0x1;
const int	CUT_FDB_Fal	= 0x2;
const int 	ERR_CUT_nuID	= 0x01; // id elementu nie jest unikalne
const int 	ERR_CUT_neMEM	= 0x02; // brak pami�ci

/*
	char *uklad_err_mesg[] = {
	     "id elementu nie jest unikalne",
	     "brak pami�ci." };
*/

char* uklad_err( int err );

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

