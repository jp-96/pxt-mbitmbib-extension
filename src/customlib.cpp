#include "pxt.h"
#include "customlib.h"

namespace customlib
{

#if MICROBIT_CODAL // micro:bit v2

    /**
     * for micro:bit v2
     */
    DEVICE_RUNTIME getDeviceRuntime()
    {
        return DEVICE_RUNTIME::RUNTIME_CODAL;
    }

#else // micro:bit v1

    /**
     * for micro:bit v1
     */
    DEVICE_RUNTIME getDeviceRuntime()
    {
        return DEVICE_RUNTIME::RUNTIME_DAL;
    }

#endif // MICROBIT_CODAL

}