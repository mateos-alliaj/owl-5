
namespace Owl\Router;

use Owl\Http\Request;

abstract class Route
{
    const GET = 1;

    const POST = 2;

    const DELETE = 3;

    const PUT = 4;

    const ALL = 7;

    public uri;

    public method = self::ALL;

    public parameters;
}
