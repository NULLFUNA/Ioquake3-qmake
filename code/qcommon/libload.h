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
#include <../renderercommon/tr_public.h>

typedef enum {

	LIBT_NONE,		//	empty handle

	LIBT_CLIENT,	//	Load client module
	LIBT_SERVER,	//	Load server module
	LIBT_UI,		//	Load ui module

	LIBT_RENDER,	//	Load renderer

	LIBT_ZLIB,		//	Load zlib

} libType_t;

typedef struct {

	void*				m_hLib;
	libType_t			m_iLibType;

	/* --- FOR OLD-TYPE LIBRARIES --- */
	intptr_t			(*m_pSystemCall)( intptr_t *parms );
	intptr_t			(QDECL *m_pEntryPoint)( int callNum, ... );
	refexport_t*		m_pRef;
	byte*				m_pDataBase;
	/* ------------------------------ */



} qlib_t;


#endif // LIBLOAD_H
