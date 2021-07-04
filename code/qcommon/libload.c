/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/

#include <libload.h>
#include <../sys/sys_loadlib.h>
qlib_t			g_libServer;
qlib_t			g_libClient;
qlib_t			g_libUI;
qlib_t			g_libRender;


qlib_t*		QLoadLibrary( libType_t iType ) {
	refimport_t	ri;

	void *hLib;
	void (*pLibEntry)(intptr_t (*syscallptr)(intptr_t, ...));
	intptr_t (*pMain)(intptr_t, ...);
	const char*	pchPath = Sys_DefaultInstallPath();


	switch ( iType ) {

		case 	LIBT_CLIENT:
			hLib = Sys_LoadLibrary( va( "%s/bin/" LIB_PREFIX "cgame" DLL_EXT, pchPath ) );
		break;

		case 	LIBT_SERVER:
			hLib = Sys_LoadLibrary( va( "%s/bin/" LIB_PREFIX "qagame" DLL_EXT, pchPath ) );
		break;

		case 	LIBT_UI:
			hLib = Sys_LoadLibrary( va( "%s/bin/" LIB_PREFIX "ui" DLL_EXT, pchPath ) );
		break;

		case 	LIBT_RENDER:
			hLib = Sys_LoadLibrary( va( "%s/bin/" LIB_PREFIX "render1" DLL_EXT, pchPath ) );
		break;

		case 	LIBT_ZLIB:
			hLib = Sys_LoadLibrary( va( "%s/bin/" LIB_PREFIX "zlib-qt" DLL_EXT, pchPath ) );
		break;

		default:
		break;
	}

	if( !hLib ) {
		Com_Error( ERR_FATAL, "QLoadLibrary(): file isn't exsists\nSearching in: %s/bin/", pchPath );
	}


	if( iType == LIBT_CLIENT ||
		iType == LIBT_SERVER ||
		iType == LIBT_UI) {

		pLibEntry = Sys_LoadFunction( hLib, "dllEntry" );
		pMain = Sys_LoadFunction( hLib, "vmMain" );

	}
}

void		QFreeLibrary( qlib_t* pLib ) {
	Sys_UnloadDll( pLib->m_hLib );
}
