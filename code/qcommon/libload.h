/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/

#ifndef LIBLOAD_H
#define LIBLOAD_H

#include <qcommon.h>
#include <q_shared.h>

typedef enum {

	LIBT_NONE,		//	empty handle
	LIBT_OLDAPI,	//	support for old modules - export vmMain()
	LIBT_NEWAPI		//	aviable only in c++		- export GetApi()

} libType_t;

//	handle of library module
typedef struct {

	libType_t	m_iType;


	char		m_chName[MAX_QPATH];		//	library name
	void*		m_pSearchPath;				//	hint for FS_ReadFileDir()

	void*		m_hLibrary;					//	handle of library


	/* --- FOR OLD API --- */

	intptr_t	( *m_pSystemCall )( intptr_t *parms );			//	from cl_cgame and sv_game
	intptr_t	( QDECL *m_pEntryPoint )( int callNum, ... );		//	vmMain


	/* --- FOR NEW API --- */

	//	will be placed later

} qlib_t;

void		InitiliazeLibLoad();
qlib_t*		LoadModule( const char* pchName );


#endif // LIBLOAD_H
