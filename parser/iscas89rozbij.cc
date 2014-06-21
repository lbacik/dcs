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
 
 
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"../share/temlista.h"

const int	ERR_brak_no	=	10;
const int	ERR_mem		=	11;
const int	ERR_brak_nz	=	12;

/*
 *
 * Funkcja usuwa "bia³e znaki" z pocz±tku i koñca ci±gu przekazanego 
 * jako parametr.
 *
 * Warto¶ci± zwracan± jest NOWY, poprawiany ci±g ( przydzielona 
 * zostaje mu pamiêæ )
 *
 */

char* obbpk( char *ciag )
{
	char *tmp;
	int i;
	
	//i = strspn( ciag, biale );
	
	i = 0;
	while(( i < strlen( ciag )) && ( isspace( ciag[i] ))) i++ ;
	
	//if( i < strlen( ciag )) {
	
		tmp = &ciag[i];
		while( isspace( ciag[ strlen( ciag )-1 ] ))
				ciag[ strlen( ciag )-1 ] = '\0';
		
		tmp = strdup( tmp );

	//} else tmp = NULL;
	
	return tmp;
	
}

/*
 *
 * 
 */

int I89rozbij0( char* ciag, char* &ident, TLista<char*>* &lista )
{
	int err = 0, i, j;
	char *tmp, *nid;

	
	try {

		
		//i = strspn( ciag, biale );
		i=0;
		while( isspace( ciag[i] )) i++;
		ident = &ciag[i];
		if(( tmp = strchr( ciag, '(' )) == NULL )
			throw ERR_brak_no;
		tmp[0]='\0';
		
		if(( ident=strdup( ident )) == NULL )
			throw ERR_mem;
	
		ciag=&tmp[1];
		if(( tmp = strchr( ciag, ')' )) == NULL )
			throw ERR_brak_nz;
		tmp[0]='\0';

	}

	catch( int __ERR__ ) { err = __ERR__; }

	return err;
}

int I89rozbij1( char *ciag, char* &nid, char* &nDef )
{
	int err	= 0;
	char *ciag_we = strdup( ciag ), *tmp;
	
	if(( tmp = strchr( ciag_we, '=' )) != NULL ) {

		tmp[0] = '\0';
		nid = obbpk( ciag_we );
		nDef= strdup( &tmp[1] );
		
	} else err = 1;
	
	free( ciag_we );
	return err;
}


/*
 * rozbij2 rozbija "ci±g" na dwa podci±gi ( pcs ipcb ) wg separatora
 * "sep"
 */

int I89rozbij2( char *ciag, char *sep, char *&pca, char *&pcb )
{
	char *tmp, *cwe = strdup( ciag );
	int err = 1;
	
	tmp = strstr( cwe, sep );
	if( tmp != NULL ) {

		tmp[0]='\0';
		pca=obbpk( cwe );
		pcb=obbpk( &tmp[strlen(sep)] );
		
	} else err = 0;
	free( cwe );
	return err;
}


int sprID( char* id ) {

	int err = 0, i;
	
	for( i = 0; i < strlen( id ); i++ )
		if( isgraph( id[i] ));
		else {
			err = i;
			break;
		}

	return err;
}

