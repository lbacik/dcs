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
 *	Definicja szablonu listy jednokierunkowej
 *
 *	 
 */

//#include<stdio.h>

const int FE_wywolajDestWsk = 0x01;

//--------------------------------------------------------------------------

	template<class T>
	class TElement {

 	      private:

		T	   _wsk; // wskaznik do typu 
	        int        _war; // warto¶æ pomocnicza
	        TElement *_nast; // wska¼nik do el. nastêpnego na li¶cie
		     			     	   
	      public:	
		
		TElement( T p, int w, TElement *n )
		{  
			_wsk=p; 
			_war=w; 
		   	_nast=n; 
		}
			   
		//~TElement();
		
		/* metody dostêpowe */
		
		T wsk()			{ return _wsk; 	}
		int war()		{ return _war; 	}
		TElement *nast( void )	{ return _nast; }

		T wsk( T p );
		int war( int nwar );
		TElement *nast( TElement *p );
	};

/*
template<class T>
TElement<T>::~TElement( void ) {

//	if(( _flagi & FE_wywolajDestWsk ) == FE_wywolajDestWsk )
//		delete _wsk;

}
*/

template<class T>
T TElement<T>::wsk( T p ) {

	return _wsk = p;
}

template<class T>
int TElement<T>::war( int nwar )
{
	_war=nwar;
	return _war;
}

template<class T>
TElement<T>* TElement<T>::nast( TElement<T> *p ) {

	_nast = p;
	return _nast;
}

//--------------------------------------------------------------------------

	template<class T>
	class TLista {
		
              	TElement<T> *wezel;
		
		// Flagi listy ( je¿eli ustawiona ):
		//	0x01	- Destruktor listy wywo³uje destruktor
		//		  klas do których wska¼niki przechowywane s±
		//		  w klasie TElement, w polu _wsk.
		int	_flagi;     		

	      public:	
		
		TLista( int nflagi );
		TLista( void );

		~TLista(); 

		TElement<T> *first( void ) { return wezel; }

		// dodaj()
		// Funkcja zwraca wska¼nik do nowego elementu listy lub 
		// NULL w przypadku b³êdu ( np.: brak pamiêci )	
		// dodaj  - dodaje na koncu listy
		// dodajp - dodaje na poczatku listy
		TElement<T>* dodaj( T nt, int i );
		TElement<T>* dodaj( T nt );
		TElement<T>* dodajp( T nt ); 

		// usun()
		// funkcja usuwa element ( je¿eli ustawiona jest flaga 0x01
		// to wywo³uje równie¿ destruktor dla klasy el->wsk ).
		// warto¶æ zwracana:
		// 	0 - je¿eli wszystko OK
		//	1 - je¿eli el nie istnieje na li¶cie
		int usun( TElement<T> *el );

		// usunWEWsk()
		// metoda, pos³uguj±c sie metod± znajdzEWsk() (opis poni¿ej),
		// usuwa z listy WSZYSTKIE elementy których pole _wsk = p.
		void usunWEWsk( T p );
		
		// procedura wywo³uje funkcjê usun( wezel ) dopóki 
		// wezel != NULL
		void czysc();
	      	
		// Funkcja zlicza elementy listy ( 0 = brak elementów )
		int ilosc();

		// Zwraca ilo¶æ elementów na li¶cie, których pole _wsk = p.
		int iloscWystapien( T p );
		
		// Funkcja zwraca wska¼nik do i-tego elementu na li¶cie,
		// je¿eli taki element nie istnieje funkcja zwróci NULL.
		// pierwszy element ma index = 0
		TElement<T>* At( int  i );

		// Zwraca wska¼nik do elementu którego pole _wsk = p
		TElement<T>* znajdzEWsk( T p );		

		// index elementu na li¶cie - pierwszy element ma index = 0.
		// UWAGA! Dla pustaj listy ( wêze³ = NULL ) metoda zwróci 
		// równie¿ 0!
		int index( TElement<T> *el );
	};

template<class T>
TLista<T>::TLista( int nflagi ) { 
		
	wezel = NULL; 
	_flagi = nflagi;

}

template<class T>
TLista<T>::TLista( void ) {

	//TLista::TLista( 0 );
	wezel = NULL;
	_flagi = 0;

}

template<class T>
TLista<T>::~TLista( void ) {

	czysc();
}

template<class T>
TElement<T>* TLista<T>::dodaj( T p, int i )
{
	TElement<T> *n, *el = wezel;

	n=new TElement<T>( p, i, NULL );
	if( n != NULL ) {

		if( el != NULL ){

			while( el->nast() != NULL ) el=el->nast();	
			el->nast( n );

		} else wezel=n;
	}	
	return n;
}

template<class T>
TElement<T>* TLista<T>::dodaj( T p )
{
	return dodaj( p, 0 );
}

template<class T>
TElement<T>* TLista<T>::dodajp( T p )
{
	TElement<T> *n, *el = wezel;

	n=new TElement<T>( p, 0, NULL );
	if( n != NULL ) {

		if( el != NULL ) n->nast( el );	 
		wezel=n;
	}	
	return n;
}

template<class T>
int TLista<T>::usun( TElement<T> *el )
{
	TElement<T> *p = wezel, *pop = NULL;
	int wynik = 1;

	while((p!=NULL ) && ( p!=el ))
	{
	        pop=p;
		p=p->nast();
	}

	if( p!=NULL ) 
	{
		if( pop!=NULL ) { pop->nast( p->nast()); }
		else wezel = p->nast();
		
		if((( _flagi & FE_wywolajDestWsk ) == FE_wywolajDestWsk ) 
		   && ( p->wsk() != NULL )) 
		   delete p->wsk(); 
		
		delete p;		

		wynik = 0;

	}// else element nie istnieje

	return wynik;
}

template<class T>
void TLista<T>::usunWEWsk( T p ) {

	TElement<T> *el;
	
	while(( el = znajdzEWsk( p )) != NULL )
		usun( el );

}

template<class T>
void TLista<T>::czysc()
{
	while( wezel != NULL ) 
	{ 
		usun( wezel );
	}
}

template<class T>
int TLista<T>::ilosc()
{
	int wynik = 0;
	TElement<T>* p = wezel;
	while( p != NULL )
	{
		wynik++;
		p = p->nast();
	}
	return wynik;
}
template<class T>
int TLista<T>::iloscWystapien( T p ) {

	int wynik = 0;
	TElement<T> *el = first();

	while( el != NULL ) {
		if( el->wsk() == p ) wynik++;
		el = el->nast();
	}
	return wynik;
}

template<class T>
TElement<T>* TLista<T>::At( int i )
{
   	TElement<T>* el=wezel;
	if( el !=NULL )
	{
		for( int j=0; j < i; j++ )
			if( el->nast()!=NULL ) el=el->nast();
			else { //przekroczony indeks 

				el=NULL;
				break;
			}	
	}
	return el;	 	 
}

template<class T>
TElement<T>* TLista<T>::znajdzEWsk( T p )
{
	TElement<T>* el = wezel;
	int jest=0;
	while( !jest && ( el!=NULL ))
	     if( el->wsk() == p ) jest=1;
	     else el=el->nast();
	return el;
}

template<class T>
int TLista<T>::index( TElement<T> *el )
{
	TElement<T> *tmp = wezel;
	int i = 0;
	while( tmp != NULL ) {
		if( tmp == el ) break;
		i++;
		tmp = tmp->nast();
	}
	return i;
}
