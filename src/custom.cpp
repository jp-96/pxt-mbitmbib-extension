#include "pxt.h"
#include "customlib.h"

namespace MbitMore
{
    //%
    void _resetAdvertising(String gapName, int serviceUUID)
    {
        customlib::resetAdvertising(MSTR(gapName), (uint16_t)serviceUUID);
    }

}
