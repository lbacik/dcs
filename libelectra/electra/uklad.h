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

const char IDLN[] = "l#";

const int	CUT_FDB_Pro	= 0x1;
const int	CUT_FDB_Fal	= 0x2;
const int 	ERR_CUT_nuID	= 0x01; // id elementu nie jest unikalne
const int 	ERR_CUT_neMEM	= 0x02; // brak pamiêci

/*
	char *uklad_err_mesg[] = {
	     "id elementu nie jest unikalne",
	     "brak pamiêci." };
*/

char* uklad_err( int err );

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

