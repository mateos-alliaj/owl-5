
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Owl_Application) {

	ZEPHIR_REGISTER_CLASS(Owl, Application, owl, application, owl_application_method_entry, 0);

	/**
	 * Latest Request
	 *
	 * @var \Owl\Http\RequestInterface
	 */
	zend_declare_property_null(owl_application_ce, SL("request"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Owl\Di\ContainerInterface
	 */
	zend_declare_property_null(owl_application_ce, SL("di"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Current env, see ENV_* constants
	 *
	 * @var string
	 */
	zend_declare_property_null(owl_application_ce, SL("env"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Count for dispatches
	 */
	zend_declare_property_long(owl_application_ce, SL("currentLoop"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var \Owl\Event\Manager
	 */
	zend_declare_property_null(owl_application_ce, SL("eventManager"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_string(owl_application_ce, SL("defaultNamespace"), "\\RestApp\\", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Handle parameters for exception catch
	 *
	 * @var array
	 */
	zend_declare_property_null(owl_application_ce, SL("exceptionHandlerParameters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Handle parameters for not found page
	 *
	 * @var array
	 */
	zend_declare_property_null(owl_application_ce, SL("errorHandlerParameters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	owl_application_ce->create_object = zephir_init_properties_Owl_Application;

	zend_class_implements(owl_application_ce TSRMLS_CC, 1, owl_applicationinterface_ce);
	zend_class_implements(owl_application_ce TSRMLS_CC, 1, owl_dispatcherinterface_ce);
	return SUCCESS;

}

/**
 * Latest Request
 */
PHP_METHOD(Owl_Application, getRequest) {


	RETURN_MEMBER(this_ptr, "request");

}

/**
 */
PHP_METHOD(Owl_Application, getDi) {


	RETURN_MEMBER(this_ptr, "di");

}

/**
 * Current env, see ENV_constants
 */
PHP_METHOD(Owl_Application, getEnv) {


	RETURN_MEMBER(this_ptr, "env");

}

/**
 */
PHP_METHOD(Owl_Application, getDefaultNamespace) {


	RETURN_MEMBER(this_ptr, "defaultNamespace");

}

/**
 * Handle parameters for exception catch
 */
PHP_METHOD(Owl_Application, setExceptionHandlerParameters) {

	zval *exceptionHandlerParameters_param = NULL;
	zval *exceptionHandlerParameters = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exceptionHandlerParameters_param);

	zephir_get_arrval(exceptionHandlerParameters, exceptionHandlerParameters_param);


	zephir_update_property_this(this_ptr, SL("exceptionHandlerParameters"), exceptionHandlerParameters TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Handle parameters for exception catch
 */
PHP_METHOD(Owl_Application, getExceptionHandlerParameters) {


	RETURN_MEMBER(this_ptr, "exceptionHandlerParameters");

}

/**
 * Handle parameters for not found page
 */
PHP_METHOD(Owl_Application, setErrorHandlerParameters) {

	zval *errorHandlerParameters_param = NULL;
	zval *errorHandlerParameters = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &errorHandlerParameters_param);

	zephir_get_arrval(errorHandlerParameters, errorHandlerParameters_param);


	zephir_update_property_this(this_ptr, SL("errorHandlerParameters"), errorHandlerParameters TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Handle parameters for not found page
 */
PHP_METHOD(Owl_Application, getErrorHandlerParameters) {


	RETURN_MEMBER(this_ptr, "errorHandlerParameters");

}

PHP_METHOD(Owl_Application, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *env = NULL;
	zval *di = NULL, *eventManager = NULL, *env_param = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &di, &eventManager, &env_param);

	if (!di) {
		di = ZEPHIR_GLOBAL(global_null);
	}
	if (!eventManager) {
		eventManager = ZEPHIR_GLOBAL(global_null);
	}
	if (!env_param) {
		ZEPHIR_INIT_VAR(env);
		ZVAL_STRING(env, "production", 1);
	} else {
		zephir_get_strval(env, env_param);
	}


	zephir_update_property_this(this_ptr, SL("di"), di TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("env"), env TSRMLS_CC);
	if (Z_TYPE_P(eventManager) == IS_NULL) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, owl_event_manager_ce);
		if (zephir_has_constructor(_0 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		zephir_update_property_this(this_ptr, SL("eventManager"), _0 TSRMLS_CC);
	} else {
		zephir_update_property_this(this_ptr, SL("eventManager"), eventManager TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Owl_Application, setDefaultNamespace) {

	zval *namespaceName_param = NULL;
	zval *namespaceName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &namespaceName_param);

	zephir_get_strval(namespaceName, namespaceName_param);


	zephir_update_property_this(this_ptr, SL("defaultNamespace"), namespaceName TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Dispatch the action
 */
PHP_METHOD(Owl_Application, dispatch) {

	zend_bool _14;
	zval *_13 = NULL;
	zend_class_entry *_5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *callParameters = NULL, *response = NULL, *handlerClass, *controller, *result = NULL, *action, *e = NULL, *module, *_0 = NULL, *_1, *_2, *_3 = NULL, *_4 = NULL, *_6, *_7, *_8 = NULL, *_9, *_10, *_11, *_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &parameters, &callParameters, &response);

	ZEPHIR_SEPARATE_PARAM(response);
	if (!callParameters) {
		callParameters = ZEPHIR_GLOBAL(global_null);
	}


	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("currentLoop") TSRMLS_CC));
	ZEPHIR_OBS_VAR(handlerClass);
	zephir_read_property_this(&handlerClass, this_ptr, SL("defaultNamespace"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(module);
	if (zephir_array_isset_string_fetch(&module, parameters, SS("module"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_CONCAT_VS(_0, module, "\\");
		zephir_concat_self(&handlerClass, _0 TSRMLS_CC);
	}
	zephir_array_fetch_string(&_1, parameters, SL("controller"), PH_NOISY | PH_READONLY, "owl/Application.zep", 114 TSRMLS_CC);
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SVS(_0, "Controller\\", _1, "Controller");
	zephir_concat_self(&handlerClass, _0 TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("currentLoop"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_2, 3)) {
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "World was crashed", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, response, "setcontent", NULL, 0, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 500);
		ZEPHIR_CALL_METHOD(NULL, response, "setstatuscode", NULL, 0, _3);
		zephir_check_call_status();
		RETURN_MM_BOOL(0);
	}

	/* try_start_1: */

		if (!(zephir_class_exists(handlerClass, 1 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_3);
			object_init_ex(_3, owl_exception_ce);
			ZEPHIR_INIT_LNVAR(_0);
			ZEPHIR_CONCAT_SVS(_0, "Class handler: '", handlerClass, "' is not exists");
			ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 6, _0);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_3, "owl/Application.zep", 125 TSRMLS_CC);
			goto try_end_1;

		}
		ZEPHIR_INIT_VAR(controller);
		zephir_fetch_safe_class(_4, handlerClass);
			_5 = zend_fetch_class(Z_STRVAL_P(_4), Z_STRLEN_P(_4), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(controller, _5);
		if (zephir_has_constructor(controller TSRMLS_CC)) {
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("request"), PH_NOISY_CC);
			_7 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(NULL, controller, "__construct", NULL, 0, _6, response, _7);
			zephir_check_call_status_or_jump(try_end_1);
		}
		if (!(zephir_instance_of_ev(controller, owl_mvc_controllerinterface_ce TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_3);
			object_init_ex(_3, owl_exception_ce);
			ZEPHIR_INIT_VAR(_8);
			ZVAL_STRING(_8, "Handle must be instance of ControllerInterface", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 6, _8);
			zephir_check_temp_parameter(_8);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_3, "owl/Application.zep", 130 TSRMLS_CC);
			goto try_end_1;

		}
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "dispatch:afterInitialize", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, _9, "emit", NULL, 0, _3, this_ptr);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_NVAR(_3);
		zephir_array_fetch_string(&_10, parameters, SL("action"), PH_NOISY | PH_READONLY, "owl/Application.zep", 135 TSRMLS_CC);
		zephir_camelize(_3, _10);
		ZEPHIR_INIT_VAR(action);
		ZEPHIR_CONCAT_VS(action, _3, "Action");
		if (!((zephir_method_exists(controller, action TSRMLS_CC)  == SUCCESS))) {
			ZEPHIR_INIT_NVAR(_8);
			object_init_ex(_8, owl_exception_ce);
			ZEPHIR_INIT_VAR(_11);
			ZEPHIR_CONCAT_SVSVS(_11, "Action '", action, "' is not exists on '", handlerClass, "'");
			ZEPHIR_CALL_METHOD(NULL, _8, "__construct", NULL, 6, _11);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_8, "owl/Application.zep", 138 TSRMLS_CC);
			goto try_end_1;

		}
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_8);
		ZVAL_STRING(_8, "dispatch:afterAction", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, _12, "emit", NULL, 0, _8, this_ptr);
		zephir_check_temp_parameter(_8);
		zephir_check_call_status_or_jump(try_end_1);
		if (Z_TYPE_P(callParameters) == IS_NULL) {
			ZEPHIR_CALL_METHOD_ZVAL(&result, controller, action, NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
		} else {
			ZEPHIR_INIT_VAR(_13);
			zephir_create_array(_13, 2, 0 TSRMLS_CC);
			zephir_array_fast_append(_13, controller);
			zephir_array_fast_append(_13, action);
			ZEPHIR_INIT_NVAR(result);
			ZEPHIR_CALL_USER_FUNC_ARRAY(result, _13, callParameters);
			zephir_check_call_status_or_jump(try_end_1);
		}
		_14 = Z_TYPE_P(result) == IS_OBJECT;
		if (_14) {
			_14 = zephir_instance_of_ev(result, owl_http_responseinterface_ce TSRMLS_CC);
		}
		if (_14) {
			ZEPHIR_CPY_WRT(response, result);
		} else {
			ZEPHIR_CALL_METHOD(NULL, response, "setcontent", NULL, 0, result);
			zephir_check_call_status_or_jump(try_end_1);
		}
		RETVAL_ZVAL(response, 1, 0);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_LONG(_3, 500);
			ZEPHIR_CALL_METHOD(NULL, response, "setstatuscode", NULL, 0, _3);
			zephir_check_call_status();
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("exceptionHandlerParameters"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_13);
			zephir_create_array(_13, 1, 0 TSRMLS_CC);
			zephir_array_update_string(&_13, SL("exception"), &e, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "dispatch", NULL, 7, _6, _13, response);
			zephir_check_call_status();
		}
	}
	RETVAL_ZVAL(response, 1, 0);
	RETURN_MM();

}

/**
 * Handle Http Request
 */
PHP_METHOD(Owl_Application, handle) {

	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *request, *response = NULL, *matchedRoute = NULL, *router = NULL, *_0, *_1 = NULL, *_2, *_3, *_4, *_5 = NULL, *_6 = NULL, *_8, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &request, &response);

	if (!response) {
		ZEPHIR_CPY_WRT(response, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(response);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "app:beforeHandle", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _0, "emit", NULL, 0, _1, this_ptr);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (Z_TYPE_P(response) == IS_NULL) {
		ZEPHIR_INIT_NVAR(response);
		object_init_ex(response, owl_http_response_ce);
		ZEPHIR_CALL_METHOD(NULL, response, "__construct", NULL, 8);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_ZVAL_NREF(_2);
	ZVAL_LONG(_2, 0);
	zephir_update_property_this(this_ptr, SL("currentLoop"), _2 TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "dispatch:beforeExecuteRoute", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _2, "emit", NULL, 0, _1, this_ptr);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("di"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "router", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&router, _3, "get", NULL, 0, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&matchedRoute, router, "matchrequest", NULL, 0, request);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "dispatch:afterExecuteRoute", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _4, "emit", NULL, 0, _1, this_ptr);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("request"), request TSRMLS_CC);
	if (zephir_is_true(matchedRoute)) {
		if (zephir_instance_of_ev(matchedRoute, owl_router_http_staticroute_ce TSRMLS_CC)) {
			ZEPHIR_OBS_VAR(_6);
			zephir_read_property(&_6, matchedRoute, SL("parameters"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_NULL(_1);
			ZEPHIR_CALL_METHOD(&_5, this_ptr, "dispatch", &_7, 0, _6, _1, response);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(response, _5);
		} else {
			ZEPHIR_OBS_NVAR(_6);
			zephir_read_property(&_6, matchedRoute, SL("parameters"), PH_NOISY_CC);
			ZEPHIR_OBS_VAR(_8);
			zephir_read_property(&_8, matchedRoute, SL("uriParameters"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_5, this_ptr, "dispatch", &_7, 7, _6, _8, response);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(response, _5);
		}
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 404);
		ZEPHIR_CALL_METHOD(NULL, response, "setstatuscode", NULL, 9, _1);
		zephir_check_call_status();
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("errorHandlerParameters"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_NULL(_1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "dispatch", &_7, 7, _9, _1, response);
		zephir_check_call_status();
	}
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("eventManager"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "app:afterHandle", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, _9, "emit", NULL, 0, _1, this_ptr);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETVAL_ZVAL(response, 1, 0);
	RETURN_MM();

}

static zend_object_value zephir_init_properties_Owl_Application(zend_class_entry *class_type TSRMLS_DC) {

		zval *_1 = NULL;
	zval *_0, *_2;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("errorHandlerParameters"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1);
			zephir_create_array(_1, 3, 0 TSRMLS_CC);
			add_assoc_stringl_ex(_1, SS("module"), SL("Api"), 1);
			add_assoc_stringl_ex(_1, SS("controller"), SL("Index"), 1);
			add_assoc_stringl_ex(_1, SS("action"), SL("error"), 1);
			zephir_update_property_this(this_ptr, SL("errorHandlerParameters"), _1 TSRMLS_CC);
		}
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("exceptionHandlerParameters"), PH_NOISY_CC);
		if (Z_TYPE_P(_2) == IS_NULL) {
			ZEPHIR_INIT_NVAR(_1);
			zephir_create_array(_1, 3, 0 TSRMLS_CC);
			add_assoc_stringl_ex(_1, SS("module"), SL("Api"), 1);
			add_assoc_stringl_ex(_1, SS("controller"), SL("Index"), 1);
			add_assoc_stringl_ex(_1, SS("action"), SL("exception"), 1);
			zephir_update_property_this(this_ptr, SL("exceptionHandlerParameters"), _1 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

