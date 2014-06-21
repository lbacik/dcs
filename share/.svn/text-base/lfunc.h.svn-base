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
 
 

int czyLiczba( const char *ciag );
char* strupcase( const char* ciag );

/*
 *
 * Funkcja usuwa "bia³e znaki" z pocz±tku i koñca ci±gu przekazanego 
 * jako parametr.
 *
 * Warto¶ci± zwracan± jest NOWY, poprawiany ci±g ( przydzielona 
 * zostaje mu pamiêæ )
 *
 */
char* clwhite( const char *ciag );

/*
 * rozbija "ci±g" na dwa podci±gi ( pcs i pcb ) wg separatora
 * "sep".
 *
 * Je¿eli ci±g nie zawiera separatora funkcja zwraca warto¶æ
 * 0 ( false ) w przeciwnym razie warto¶ci± zwracan± jest
 * 1 ( true );
 *
 * /!\ Podci±g± pca i pcb funkcja przydziela pamiêæ!
 *
 */
int explode( const char *ciag, const char *sep, char *&pca, char *&pcb );
/*
 *	
 *
 *
 */
int explode2( const char *ciag, const char *sep0, const char *sep1,
		char *&A, char *&B, char *&C );

/*
 * isSpace zwraca warto¶æ 0 je¿eli ci±g sk³ada siê z samych znaków bia³ych.
 *
 */
int isSpace( const char *ciag );

