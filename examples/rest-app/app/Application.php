<?php
/**
 * @author Patsura Dmitry http://github.com/ovr <talk@dmtry.me>
 */

namespace RestApp;

use Owl\Router\Router;
use Owl\Router\Route;
use PDO;

class Application extends \Owl\Application
{
    /**
     * @return \Owl\Application
     */
    public function bootstrap()
    {
        $serviceManager = $this->di;

        $router = new Router();
        $router->add('/', ['module' => 'Api', 'controller' => 'Index', 'action' => 'index']);

        $router->add('/version', ['module' => 'Api', 'controller' => 'Index', 'action' => 'version']);
        $router->add('/ping', ['module' => 'Api', 'controller' => 'Index', 'action' => 'ping']);

        $router->add('/users', ['module' => 'Api', 'controller' => 'User', 'action' => 'list']);
        $router->add('/users/:id', ['module' => 'Api', 'controller' => 'User', 'action' => 'index']);
        $router->add('/users/:id', ['module' => 'Api', 'controller' => 'User', 'action' => 'create'], Route::POST);
        $router->add('/users/:id', ['module' => 'Api', 'controller' => 'User', 'action' => 'delete'], Route::DELETE);

        $serviceManager->set('router', $router);

        $driver = new \Owl\DBAl\Driver\Mysql(
            'mysql:host=127.0.0.1;dbname=phalcon-module-skeleton;port=49153',
            'root',
            'root',
            array(
                PDO::ATTR_PERSISTENT => true,
                PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES "UTF8"'
            )
        );
        $connection = new \Owl\DBAL\Connection(['driver' => $driver], $this->eventManager);
        $serviceManager->set('connection', $connection);

        $cache = new \Owl\Cache\Driver\Memcached();
        $serviceManager->set('cache', $cache);

        return $this;
    }
}
