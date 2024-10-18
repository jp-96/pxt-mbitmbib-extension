#ifndef CUSTOMLIB_H
#define CUSTOMLIB_H

#include "pxt.h"

namespace customlib
{
    void resetAdvertising(const ManagedString &gapName, const uint16_t serviceUUID);
}

#endif // #ifndef CUSTOMLIB_H
