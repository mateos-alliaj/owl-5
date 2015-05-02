<?php
/**
 * @author Ivanov Sergey <xufocoder@gmail.com>
 */

namespace Owl\Tests\Log;

use Owl\Log\Logger;

/**
 * Class LoggerTest
 */
class LoggerTest extends \PHPUnit_Framework_TestCase
{


    /**
     * @return array
     */
    protected function getLevels()
    {
        return [
            Logger::LEVEL_ALERT,
            Logger::LEVEL_CRITICAL,
            Logger::LEVEL_DEBUG,
            Logger::LEVEL_EMERGENCY,
            Logger::LEVEL_INFO,
            Logger::LEVEL_NOTICE,
            Logger::LEVEL_WARNING
        ];
    }

    public function testLoggerRecordLevels()
    {

        $logger = new Logger([]);

        $logger->alert('message');
        $logger->critical('message');
        $logger->debug('message');
        $logger->emergency('message');
        $logger->info('message');
        $logger->notice('message');
        $logger->warning('message');

        $records = $logger->getRecords();

        $this->assertTrue(Logger::getLevelTitle($records[0]->level) == 'alert');
        $this->assertTrue(Logger::getLevelTitle($records[1]->level) == 'critical');
        $this->assertTrue(Logger::getLevelTitle($records[2]->level) == 'debug');
        $this->assertTrue(Logger::getLevelTitle($records[3]->level) == 'emergency');
        $this->assertTrue(Logger::getLevelTitle($records[4]->level) == 'info');
        $this->assertTrue(Logger::getLevelTitle($records[5]->level) == 'notice');
        $this->assertTrue(Logger::getLevelTitle($records[6]->level) == 'warning');

    }

    public function testLoggerFilterAllLevels()
    {

        $logger = new Logger([
            [
                'class' => '\Owl\Log\Writer\DevNull'
            ]
        ]);

        $logger->alert('test');
        $logger->error('test');
        $logger->error('test');
        $logger->error('test');
        $logger->error('test');
        $logger->error('test');
        $logger->warning('test');

        $this->assertTrue(count($logger->getRecords()) == 7);

        $logger->commit();
        $writer = $logger->getWriter(0);

        $this->assertTrue(count($writer->getRecords()) == 7);

    }

    public function testLoggerFilterSeveralLevels()
    {

        $logger = new Logger([
            [
                'class' => '\Owl\Log\Writer\DevNull',
                'levels' => [Logger::LEVEL_ALERT]
            ]
        ]);

        $logger->alert('test');

        $logger->error('test');
        $logger->error('test');
        $logger->error('test');
        $logger->error('test');
        $logger->error('test');

        $this->assertTrue(count($logger->getRecords()) == 6);

        $logger->commit();

        $writer = $logger->getWriter(0);

        $this->assertTrue(count($writer->getRecords()) == 1);
    }
}