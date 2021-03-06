<?php
/**
 * @author Patsura Dmitry <zaets28rus@gmail.com>
 */

namespace Owl\Tests;

use Owl\Application;
use Owl\Http\Request;
use Owl\Router\Router;

class ApplicationTest extends \PHPUnit_Framework_TestCase
{
    protected function createSmallApp($eventManager = null)
    {
        $serviceManager = new \Owl\Di\Container();

        $router = new Router();
        $router->add('/', ['controller' => 'Index', 'action' => 'index']);
        $router->add('/view/:id/', ['controller' => 'Index', 'action' => 'view']);

        $serviceManager->set('router', $router);

        return new Application($serviceManager, $eventManager);
    }

    public function testCreateSmallApp()
    {
        $application = $this->createSmallApp();

        $this->assertInstanceOf('Owl\Application', $application);
        $this->assertInstanceOf('Owl\ApplicationInterface', $application);
        $this->assertInstanceOf('Owl\Di\Container', $application->getDi());
        $this->assertInstanceOf('Owl\Di\ContainerInterface', $application->getDi());
        $this->assertSame(Application::ENV_PRODUCTION, $application->getEnv());
    }

    public function testHandle()
    {
        $application = $this->createSmallApp();
        $response = $application->handle(Request::createFromGlobals(), new \Owl\Http\Response\Json());

        $this->assertInstanceOf('Owl\Http\ResponseInterface', $response);
    }

    public function testDispatchEvents()
    {
        $dispatchAfterInitialize = false;
        $dispatchAfterAction = false;
        $dispatchBeforeExecuteRoute = false;
        $dispatchAfterExecuteRoute = false;
        $appAfterHandle = false;

        $eventManager = new \Owl\Event\Manager();
        $eventManager->listen('dispatch:afterInitialize', function ($app) use (&$dispatchAfterInitialize) {
            $dispatchAfterInitialize = true;
        });

        $eventManager->listen('dispatch:afterAction', function ($app) use (&$dispatchAfterAction) {
            $dispatchAfterAction = true;
        });

        $eventManager->listen('dispatch:beforeExecuteRoute', function ($app) use (&$dispatchBeforeExecuteRoute) {
            $dispatchBeforeExecuteRoute = true;
        });

        $eventManager->listen('dispatch:afterExecuteRoute', function ($app) use (&$dispatchAfterExecuteRoute) {
            $dispatchAfterExecuteRoute = true;
        });

        $eventManager->listen('app:afterHandle', function ($app) use (&$appAfterHandle) {
            $appAfterHandle = true;
        });


        $this->assertFalse($dispatchAfterInitialize);
        $this->assertFalse($dispatchAfterAction);
        $this->assertFalse($dispatchBeforeExecuteRoute);
        $this->assertFalse($dispatchAfterExecuteRoute);
        $this->assertFalse($appAfterHandle);

        $application = $this->createSmallApp($eventManager);
        $response = $application->handle(Request::createFromGlobals(), new \Owl\Http\Response\Json());

        $this->assertInstanceOf('Owl\Http\ResponseInterface', $response);
        $this->assertJson($response->getContent());
        $this->assertSame(200, $response->getStatusCode());

        $this->assertNotFalse($dispatchBeforeExecuteRoute);
        $this->assertNotFalse($dispatchAfterExecuteRoute);
        $this->assertNotFalse($dispatchAfterInitialize);
        $this->assertNotFalse($dispatchAfterAction);
        $this->assertNotFalse($appAfterHandle);
    }

    public function testIndexAction()
    {
        $application = $this->createSmallApp();
        $response = $application->handle(Request::createFromGlobals(), new \Owl\Http\Response\Json());


        $this->assertInstanceOf('Owl\Http\ResponseInterface', $response);
        $this->assertSame(200, $response->getStatusCode());

        $this->assertJson($response->getContent());

        $result = json_decode($response->getContent());
        $this->assertSame('indexAction', $result->action);
        $this->assertSame('value', $result->key);
        $this->assertEquals('1', $result->test);
    }

    public function testViewAction()
    {
        $application = $this->createSmallApp();
        $response = $application->handle(new Request([], [], ['REQUEST_URI' => '/view/1/'], [], [], []), new \Owl\Http\Response\Json());

        $this->assertInstanceOf('Owl\Http\ResponseInterface', $response);
        $this->assertSame(200, $response->getStatusCode());

        $this->assertJson($response->getContent());

        $result = json_decode($response->getContent());
        $this->assertSame('viewAction', $result->action);
        $this->assertSame('value', $result->key);
        $this->assertEquals('1', $result->test);
    }
}
