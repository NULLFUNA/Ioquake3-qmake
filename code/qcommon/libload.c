/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/

#include <libload.h>

//	ui, cgame, qagame
#define MAX_LIBS 3
qlib_t	g_lLibs[MAX_LIBS];

cvar_t*	libload_oldapi;

void	InitiliazeLibLoad() {
	libload_oldapi = Cvar_Get("libload_oldapi", "0", CVAR_ARCHIVE | CVAR_LATCH );

	for( int i = 0; i < MAX_LIBS; i++ )
		g_lLibs->m_iType = LIBT_NONE;
}

qlib_t*	GetFreeHandle() {

	for( int i = 0; i < MAX_LIBS; i++ )
		if( g_lLibs[i].m_iType == LIBT_NONE )
			return &g_lLibs[i];

	return NULL;
}

qlib_t*		LoadModule( const char* pchName ) {

}


