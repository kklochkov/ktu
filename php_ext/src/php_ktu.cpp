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

#include <QString>
#include <KtuCurriculumn>

extern "C"
{
    #include <php.h>
    #include <php_ini.h>
    #include <zend_exceptions.h>
    #include "ext/standard/info.h"
}

#include "php_ktu.h"

static int le_php_ktu;
static const char *PHP_KTU_VERSION = "0.1";
static const char *PHP_KTU_EXTNAME = "php_ktu";
zend_class_entry *constants_factory_ce = 0;
static zend_object_handlers constants_factory_handlers;

typedef struct _constants_factory_object {
    zend_object std;
    KTU::ConstantsFactory *factory;
} constants_factory_object;

static const zend_function_entry php_ktu_functions[] = {
    PHP_FE(php_ktu_about_qt, NULL)
    {NULL, NULL, NULL}
};

static const zend_function_entry php_ktu_constants_factory_funcations[] = {
    PHP_ME(KtuConstantsFactory, __constructor, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(KtuConstantsFactory, className, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

zend_module_entry php_ktu_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_KTU_EXTNAME,
    php_ktu_functions,
    PHP_MINIT(php_ktu),
    PHP_MSHUTDOWN(php_ktu),
    PHP_RINIT(php_ktu),
    PHP_RSHUTDOWN(php_ktu),
    PHP_MINFO(php_ktu),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_KTU_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHP_KTU
    ZEND_GET_MODULE(php_ktu)
#endif

extern "C"
{
    static void constants_factory_object_dtor(void *object, zend_object_handle handle TSRMLS_DC)
    {
         constants_factory_object *intern = (constants_factory_object *)object;
         zend_object_std_dtor(&(intern->std) TSRMLS_CC);
         efree(object);
    }

    static zend_object_value constants_factory_object_new(zend_class_entry *ce TSRMLS_DC)
    {
        zend_object_value retval;
        constants_factory_object *intern = (constants_factory_object *)ecalloc(1, sizeof(constants_factory_object));
        intern->factory = &constantsFactory;
        zend_object_std_init(&(intern->std), ce TSRMLS_CC);
        zend_hash_copy(intern->std.properties, &ce->default_properties, (copy_ctor_func_t)zval_add_ref, NULL, sizeof(zval *));
        retval.handle = zend_objects_store_put(intern, constants_factory_object_dtor, NULL, NULL TSRMLS_CC);
        retval.handlers = &constants_factory_handlers;
        return retval;
    }

    PHP_MINIT_FUNCTION(php_ktu)
    {
        zend_class_entry ce;
        INIT_CLASS_ENTRY(ce, "KtuConstantsFactory", php_ktu_constants_factory_funcations);
        constants_factory_ce = zend_register_internal_class(&ce TSRMLS_CC);

        constants_factory_ce->create_object = constants_factory_object_new;
        memcpy(&constants_factory_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        constants_factory_handlers.clone_obj = NULL;
        constants_factory_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

        return SUCCESS;
    }

    PHP_MSHUTDOWN_FUNCTION(php_ktu)
    {
        /* uncomment this line if you have INI entries
        UNREGISTER_INI_ENTRIES();
        */
        return SUCCESS;
    }

    PHP_RINIT_FUNCTION(php_ktu)
    {
        return SUCCESS;
    }

    PHP_RSHUTDOWN_FUNCTION(php_ktu)
    {
        return SUCCESS;
    }

    PHP_MINFO_FUNCTION(php_ktu)
    {
        php_info_print_table_start();
        php_info_print_table_header(2, "php_ktu support", "enabled");
        php_info_print_table_end();

        /* Remove comments if you have entries in php.ini
        DISPLAY_INI_ENTRIES();
        */
    }

    PHP_FUNCTION(php_ktu_about_qt)
    {
        static const QString aboutQt = QString(
                "<h3>About Qt</h3>"
                "<p>This program uses Qt version %1.</p>"
                "<p>Qt is a C++ toolkit for cross-platform application "
                "development.</p>"
                "<p>Qt provides single-source portability across MS&nbsp;Windows, "
                "Mac&nbsp;OS&nbsp;X, Linux, and all major commercial Unix variants. "
                "Qt is also available for embedded devices as Qt for Embedded Linux "
                "and Qt for Windows CE.</p>"
                "<p>Qt is available under three different licensing options designed "
                "to accommodate the needs of our various users.</p>"
                "<p>Qt licensed under our commercial license agreement is appropriate "
                "for development of proprietary/commercial software where you do not "
                "want to share any source code with third parties or otherwise cannot "
                "comply with the terms of the GNU LGPL version 2.1 or GNU GPL version "
                "3.0.</p>"
                "<p>Qt licensed under the GNU LGPL version 2.1 is appropriate for the "
                "development of Qt applications (proprietary or open source) provided "
                "you can comply with the terms and conditions of the GNU LGPL version "
                "2.1.</p>"
                "<p>Qt licensed under the GNU General Public License version 3.0 is "
                "appropriate for the development of Qt applications where you wish to "
                "use such applications in combination with software subject to the "
                "terms of the GNU GPL version 3.0 or where you are otherwise willing "
                "to comply with the terms of the GNU GPL version 3.0.</p>"
                "<p>Please see <a href=\"http://qt.nokia.com/products/licensing\">qt.nokia.com/products/licensing</a> "
                "for an overview of Qt licensing.</p>"
                "<p>Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).</p>"
                "<p>Qt is a Nokia product. See <a href=\"http://qt.nokia.com/\">qt.nokia.com</a> "
                "for more information.</p>").arg(QLatin1String(QT_VERSION_STR));
        RETURN_STRING(qPrintable(aboutQt), 1);
    }

    PHP_METHOD(KtuConstantsFactory, __constructor)
    {
        php_set_error_handling(EH_THROW, zend_exception_get_default(TSRMLS_C) TSRMLS_CC);
        constants_factory_object *intern = (constants_factory_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
        php_set_error_handling(EH_NORMAL, NULL TSRMLS_CC);
    }

    PHP_METHOD(KtuConstantsFactory, className)
    {
        zval *object = getThis();
        constants_factory_object *intern = (constants_factory_object*)zend_object_store_get_object(object TSRMLS_CC);
        RETURN_STRING(typeid(intern->factory).name(), 1);
    }
}
