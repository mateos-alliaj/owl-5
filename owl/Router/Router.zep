
namespace Owl\Router;

class Router implements RouterInterface
{
    protected basePath = "" {get, set};

    protected routers = [];

    public function add(string uri, string method = "GET")
    {

    }

    public function matchRequest(<Owl\Http\Request> request)
    {

    }

    public function match(string uri, string method = "GET") -> object|boolean
    {

    }
}
