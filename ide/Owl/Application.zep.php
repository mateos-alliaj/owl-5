<?php

namespace Owl;


class Application implements \Owl\ApplicationInterface, \Owl\DispatcherInterface
{
    /**
     * Latest Request
     *
     * @var \Owl\Http\RequestInterface
     */
    protected $request;

    /**
     * @var \Owl\Di\ContainerInterface
     */
    protected $di;

    /**
     * Current env, see ENV_* constants
     *
     * @var string
     */
    protected $env;

    /**
     * Count for dispatches
     */
    protected $currentLoop = 0;

    /**
     * @var \Owl\Event\Manager
     */
    protected $eventManager;

    /**
     * @var string
     */
    protected $defaultNamespace = "\\\\RestApp\\\\";

    /**
     * Handle parameters for exception catch
     *
     * @var array
     */
    protected $exceptionHandlerParameters = array("module" => "Api", "controller" => "Index", "action" => "exception");

    /**
     * Handle parameters for not found page
     *
     * @var array
     */
    protected $errorHandlerParameters = array("module" => "Api", "controller" => "Index", "action" => "error");


    /**
     * Latest Request
     *
     * @return \Owl\Http\RequestInterface 
     */
    public function getRequest() {}

    /**
     * @return \Owl\Di\ContainerInterface 
     */
    public function getDi() {}

    /**
     * Current env, see ENV_constants
     *
     * @return string 
     */
    public function getEnv() {}

    /**
     * @return string 
     */
    public function getDefaultNamespace() {}

    /**
     * Handle parameters for exception catch
     *
     * @param array $exceptionHandlerParameters 
     */
    public function setExceptionHandlerParameters($exceptionHandlerParameters) {}

    /**
     * Handle parameters for exception catch
     *
     * @return array 
     */
    public function getExceptionHandlerParameters() {}

    /**
     * Handle parameters for not found page
     *
     * @param array $errorHandlerParameters 
     */
    public function setErrorHandlerParameters($errorHandlerParameters) {}

    /**
     * Handle parameters for not found page
     *
     * @return array 
     */
    public function getErrorHandlerParameters() {}

    /**
     * @param mixed $di 
     * @param mixed $eventManager 
     * @param string $env 
     */
    public function __construct(\Owl\Di\ContainerInterface $di = null, Event\Manager $eventManager = null, $env = ApplicationInterface::ENV_PRODUCTION) {}

    /**
     * @param string $namespaceName 
     */
    public function setDefaultNamespace($namespaceName) {}

    /**
     * Dispatch the action
     *
     * @param mixed $parameters 
     * @param mixed $callParameters 
     * @param mixed $response 
     */
    public function dispatch($parameters, $callParameters = null, $response) {}

    /**
     * Handle Http Request
     *
     * @param mixed $request 
     * @param mixed $response 
     * @return \Owl\Http\ResponseInterface 
     */
    public function handle(\Owl\Http\RequestInterface $request, \Owl\Http\ResponseInterface $response = null) {}

}
