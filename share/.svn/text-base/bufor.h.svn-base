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
 *				BUFOR
 *
 *	Pro¶ciutka klasa maj±ca za zadanie implementacjê podstawowych
 *	funkcji obs³ugi bufora.
 * 
 * 						£ukasz Bacik 2004
 */


	class TBufor {
	
	      public:
		
		char *pocz, 	// pocz±tek bufora
		     *wsk_put,  // wskazuja na pierwsze wolne miejsce
		     *wsk_get;  // wskazuje nastêpny znak do pobrania
		int  dl;	// wielko¶æ bufora

		TBufor( int );	// parametrem konstruktora jest wielko¶æ
				// bufora
		~TBufor();

		int putch( char ); // wstaw do bufora znak, zwróæ pozosta³±
				   // wielko¶æ bufora
		int getch( char& );// pobierz z bufora znak, zwróæ pozosta³±
				   // ilo¶æ znaków do pobrania w buforze
		void zeruj( void );// "zeruj" bufor - wska¼niki wsk_*  = pocz
		int  iloscmiejsca( void );// zwraca ilo¶æ wolnego miejsca w 
					  // buforze - identycznie jak 
					  // f. putch()				           
	};

