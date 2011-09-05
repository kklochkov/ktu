/****************************************************************************
**
** Copyright (C) 2011 Kirill (spirit) Klochkov.
** Contact: klochkov.kirill@gmail.com
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#ifndef PHP_KTU_H
#define PHP_KTU_H

#define COMPILE_DL_PHP_KTU

extern zend_module_entry php_ktu_module_entry;
#define phpext_ktu_ptr &php_ktu_module_entry

#ifdef PHP_WIN32
#define PHP_KTU_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_KTU_API __attribute__ ((visibility("default")))
#else
#define PHP_KTU_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

extern "C"
{
    PHP_MINIT_FUNCTION(php_ktu);
    PHP_MSHUTDOWN_FUNCTION(php_ktu);
    PHP_RINIT_FUNCTION(php_ktu);
    PHP_RSHUTDOWN_FUNCTION(php_ktu);
    PHP_MINFO_FUNCTION(php_ktu);

    PHP_FUNCTION(php_ktu_about_qt);

    PHP_METHOD(KtuConstantsFactory, __constructor);
    PHP_METHOD(KtuConstantsFactory, className);
}

#ifdef ZTS
#define KTU_G(v) TSRMG(php_ktu_globals_id, php_zend_ktu_globals *, v)
#else
#define KTU_G(v) (php_ktu_globals.v)
#endif

#endif  /* PHP_KTU_H */
