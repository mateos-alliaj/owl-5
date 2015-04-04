
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/variables.h"


ZEPHIR_INIT_CLASS(Owl_Application) {

	ZEPHIR_REGISTER_CLASS(Owl, Application, owl, application, owl_application_method_entry, 0);

	zend_declare_property_null(owl_application_ce, SL("request"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(owl_application_ce, SL("response"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(owl_application_ce, SL("di"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(owl_application_ce, SL("env"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_string(owl_application_ce, SL("ENV_PRODUCTION"), "production" TSRMLS_CC);

	zend_declare_class_constant_string(owl_application_ce, SL("ENV_DEVELOPMENT"), "development" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Owl_Application, getRequest) {


	RETURN_MEMBER(this_ptr, "request");

}

PHP_METHOD(Owl_Application, getResponse) {


	RETURN_MEMBER(this_ptr, "response");

}

PHP_METHOD(Owl_Application, getDi) {


	RETURN_MEMBER(this_ptr, "di");

}

PHP_METHOD(Owl_Application, getEnv) {


	RETURN_MEMBER(this_ptr, "env");

}

PHP_METHOD(Owl_Application, __construct) {

	zval *env = NULL;
	zval *di = NULL, *env_param = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &di, &env_param);

	if (!di) {
		di = ZEPHIR_GLOBAL(global_null);
	}
	if (!env_param) {
		ZEPHIR_INIT_VAR(env);
		ZVAL_STRING(env, "production", 1);
	} else {
		zephir_get_strval(env, env_param);
	}


	zephir_update_property_this(this_ptr, SL("di"), di TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("env"), env TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Handle Http Request
 */
PHP_METHOD(Owl_Application, handle) {

	zend_class_entry *_9;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *response = NULL, *matchedRoute = NULL, *router = NULL, *_0, *_1 = NULL, *handlerClass, *controller, *result = NULL, *action, *_2, *_3, *_4, *_5, *_6, *_7, *_8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &request, &response);

	if (!response) {
		ZEPHIR_CPY_WRT(response, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(response);
	}


	if (Z_TYPE_P(response) == IS_NULL) {
		ZEPHIR_INIT_NVAR(response);
		object_init_ex(response, owl_http_response_ce);
		if (zephir_has_constructor(response TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, response, "__construct", NULL);
			zephir_check_call_status();
		}
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "router", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&router, _0, "get", NULL, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&matchedRoute, router, "matchrequest", NULL, request);
	zephir_check_call_status();
	if (zephir_is_true(matchedRoute)) {
		ZEPHIR_OBS_VAR(_2);
		zephir_read_property(&_2, matchedRoute, SL("parameters"), PH_NOISY_CC);
		zephir_array_fetch_string(&_3, _2, SL("module"), PH_NOISY | PH_READONLY, "owl/Application.zep", 46 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_4);
		zephir_read_property(&_4, matchedRoute, SL("parameters"), PH_NOISY_CC);
		zephir_array_fetch_string(&_5, _4, SL("controller"), PH_NOISY | PH_READONLY, "owl/Application.zep", 46 TSRMLS_CC);
		ZEPHIR_INIT_VAR(handlerClass);
		ZEPHIR_CONCAT_SSVSVS(handlerClass, "\\RestApp", "\\", _3, "\\Controller\\", _5, "Controller");
		ZEPHIR_OBS_VAR(_6);
		zephir_read_property(&_6, matchedRoute, SL("parameters"), PH_NOISY_CC);
		zephir_array_fetch_string(&_7, _6, SL("action"), PH_NOISY | PH_READONLY, "owl/Application.zep", 47 TSRMLS_CC);
		ZEPHIR_INIT_VAR(action);
		ZEPHIR_CONCAT_VS(action, _7, "Action");
		ZEPHIR_INIT_VAR(controller);
		zephir_fetch_safe_class(_8, handlerClass);
		_9 = zend_fetch_class(Z_STRVAL_P(_8), Z_STRLEN_P(_8), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(controller, _9);
		if (zephir_has_constructor(controller TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, controller, "__construct", NULL);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD_ZVAL(&result, controller, action,  NULL);
		zephir_check_call_status();
		zephir_var_dump(&result TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 404);
		ZEPHIR_CALL_METHOD(NULL, response, "setcode", NULL, _1);
		zephir_check_call_status();
	}
	RETVAL_ZVAL(response, 1, 0);
	RETURN_MM();

}

