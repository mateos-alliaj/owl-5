
namespace Owl\Log;


use Owl\Log\FormatterInterface;
use Owl\Log\Formatter\Line;
use Owl\Log\Exception\InvalidWriterException;
use Owl\Log\Exception\InvalidFormatterException;

abstract class AbstractWriter implements WriterInterface
{
    /**
     * Writer log levels
     */
    protected levels = [] {
        get, set
    };

    /**
     * Writer records
     */
    protected records = [];

    /**
     * Writer options
     */
    protected options = [] {
        get, set
    };

    /**
     * Writer formatter
     */
    protected formatter;

    /**
     * Records limit to commit them to writers
     */
    protected recordsInterval = 1000
    {
        get
    };

    public function __destruct()
    {
        if (count(this->records) > 0 ) {
            this->push();
        }
    }

    /**
     * @inheritdoc
     */
    public function getOption(string option)
    {
        if !isset(this->options[option]) {
            throw new InvalidWriterException("Option " . option . " is not exists");
        }
        return this->options[option];
    }

    protected function defaultFormatter() -> <FormatterInterface> {
        return new Line;
    }

    /**
     * @inheritdoc
     */
    public function getFormatter() -> <FormatterInterface>
    {
        if (this->formatter === null){
            let this->formatter = this->defaultFormatter();
        }

        return this->formatter;
    }

    public function setFormatter(var formatter)
    {
        if typeof formatter == "object" && is_subclass_of(formatter, "Owl\Log\FormatterInterface") {
            let this->formatter = formatter;
        }

        if typeof formatter == "string" {
            if !class_exists (formatter) {
                throw new InvalidFormatterException("Formatter class is not exits");
            }
            let this->formatter = new {formatter}();
        }
    }

    protected function format(array record) -> string
    {
       return this->getFormatter()->format(
            record[0],
            record[1],
            record[2],
            isset(record[3]) ? record[3] : []
        );
    }

    protected function filterRecords(array records) -> array
    {
        // @TODO: filter by levels
        return records;
    }

    /**
     * @inheritdoc
     */
    public function commit(array records) -> void
    {
        let this->records += $this->filterRecords(records);

        if (count(this->records) >= this->recordsInterval) {
            this->push();
        }
    }

    /**
     * @inheritdoc
     */
    public function push() -> void
    {
        var record;

        for record in this->records {
            let record = this->format(record);
            this->write( record );
        }

        let this->records = [];
    }

    /**
     * Write record
     */
    protected function write(string record) -> void;
}