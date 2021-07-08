#ifndef BASERENDER_GLOBAL_H
#define BASERENDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASERENDER_LIBRARY)
#  define BASERENDER_EXPORT Q_DECL_EXPORT
#else
#  define BASERENDER_EXPORT Q_DECL_IMPORT
#endif

#endif // BASERENDER_GLOBAL_H