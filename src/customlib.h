#ifndef CUSTOMLIB_H
#define CUSTOMLIB_H

#include "pxt.h"

namespace customlib
{

    /**
     * device runtime
     */
    enum DEVICE_RUNTIME
    {
        /**
         * simulator
         */
        RUNTIME_SIMU = 0,
        /**
         * dal - micro:bit v1
         */
        RUNTIME_DAL = 1,
        /**
         * codal - micro:bit v2
         */
        RUNTIME_CODAL = 2,
    };

    /**
     * get device runtime
     * @returns DEVICE_RUNTIME
    */
    DEVICE_RUNTIME getDeviceRuntime();

}

#endif // #ifndef CUSTOMLIB_H