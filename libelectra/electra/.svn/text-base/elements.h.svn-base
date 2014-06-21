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

	Deklaracje elementów symulatora uk³adów cyfrowych >>electra<<.

*/


//----------------------------------------------------------- NEGACJA -------

	class TNegacja : public TPPS {

		public:

			TNegacja( char *nid ):TPPS( nid ){};
			void przelicz( void );
			/*
			 * Metoda przelicz tego elementu przepisuje
			 * na pierwsze wyj¶cie zanegowan± warto¶æ
			 * pierwszego wej¶cia.
			 *
			 * UWAGA. Wszystkie pozosta³e wej¶cia i wyj¶cia
			 * s± IGNOROWANE - obiekt TNegacja powinien
			 * posiadaæ dok³adnie jedno wej¶cie i dok³adnie
			 * jedno wyj¶cie.
			 *
			 */
	};		

//----------------------------------------------------------- OR -----------

	class TOR : public TPPS {

		public:
			TOR( char *nid ) : TPPS( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu równa sie sumie
			 * logicznej warto¶ci wszystkich wej¶æ.
			 *
			 */
	};

//----------------------------------------------------------- NOR -----------

	class TNOR : public TOR {

		public:
			TNOR( char *nid ) : TOR ( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu równa siê zanegowanej
			 * sumie logicznej wszystkich wej¶æ
			 *
			 */
	};

//------------------------------------------------------------- AND ---------

	class TAND : public TPPS {

		public:
			TAND( char *nid ) : TPPS( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu jest równa iloczynowi 
			 * logicznemu warto¶ci ze wszystkic wej¶æ
			 *
			 */
	};

//------------------------------------------------------------- NAND --------

	class TNAND : public TAND {

		public:
			TNAND( char *nid ) : TAND( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu równa siê zanegowanemu
			 * iloczynowi logicznemu warto¶ci na wszystkich 
			 * wej¶ciach
			 * 
			 */
	};

//---------------------------------------------------------------- XOR ------

	class TXOR : public TPPS {
	
		public:
			TXOR( char *nid ) : TPPS( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu jest równa sumie 
			 * modulo warto¶ci na wszystkich wej¶ciach.
			 *
			 */
	};

//--------------------------------------------------------------- XNOR -------

	class TXNOR : public TXOR {

		public:
			TXNOR( char *nid ) : TXOR( nid ) {};
			void przelicz( void );
			/*
			 * Warto¶æ na pierwszym wyj¶ciu jest równa negacji
			 * sumy modulo warto¶ci wszystkich wej¶æ.
			 *
			 */
	};


//---------------------------------------------------------------- DFF -------


/*
 * Deklaracja klasy przerzutnika synchronicznego typu "D". Przerztnik ten 
 * posiada jedno wej¶cie i jedno wyj¶cie - wej¶cie zagarowe jest ignorowane.
 * 
 * Sygna³ podany na wej¶cie przerzutnika jest przenoszony na jego wyj¶cie.
 * 
 */

class TDFF: public TPPS {

		int Q; // zmienna pomocnicza

	public:
		TDFF( char *nid ) : TPPS( nid ) { Q = 0; };

		void setQ( void );
		/*
		 * metoda przenosi warto¶æ ze zmiennej pomocniczej na pierwsze
		 * wyj¶cie przerzutnika.
		 * 
		 */

		void set( int, ... );
		/*
		 * Zainicjowanie przerzutnika ( ustawienie zmiennej Q oraz 
		 * warto¶ci na pierwszym wyj¶ciu ) warto¶ci± przekazanego
		 * do procedury argumentu.
		 * 
		 */

		void przelicz( void );
		/*
		 * Przenosi warto¶æ z pierwszego wej¶cia do zmiennej Q.
		 *
		 */

		void reset( void );
		/*
		 * wywo³uje pokrywan± metodê klasy TPPS i zeruje zmienn± Q.
		 *
		 */

};

