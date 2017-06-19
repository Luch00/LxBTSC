#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTLXBTSC_LIB)
#  define QTLXBTSC_EXPORT Q_DECL_EXPORT
# else
#  define QTLXBTSC_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTLXBTSC_EXPORT
#endif
