#include "pxt.h"
#include "customlib.h"

namespace custom
{
    /**
     * Block definition from C++, no implementation for simulator
     * https://makecode.com/simshim
     */
    //% block
    int bar()
    {
        return (int)customlib::getDeviceRuntime();
    }

    //%
    int baz()
    {
        return (int)customlib::getDeviceRuntime() + 5;
    }

}