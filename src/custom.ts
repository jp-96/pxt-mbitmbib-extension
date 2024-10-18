/**
 * Custom blocks
 * icon: a Unicode identifier for an icon from the Font Awesome icon set.
 *       http://fontawesome.io/icons
 */
//% block="Custom Blocks"
//% weight=100 color=#696969 icon="\uf1b2"
namespace custom {
    
    const CPREFIX_DEVICE_NAME = "BBC micro:bit" // for Microbit More Editor
    const CSERVICE_UUID_16 = 61445  // 0xF005 - scratch link

    /**
     * set bib number.
     * @param n bib number
     */
    //% block="bib %bib"
    //% blockId=set_bib_number
    //% bib.min=0 bib.max=999 bib.defl=999
    //% weight=100
    //% group="More"
    //% advanced=true
    export function setBibNumber(bib: number): void {
        let s = "00" + convertToText(Math.imul(Math.abs(bib), 1) % 1000)
        s = CPREFIX_DEVICE_NAME + " #" + s.substr(s.length - 3, 3)
        _resetAdvertising(s, CSERVICE_UUID_16)
    }

    //% block
    //% shim=custom::_resetAdvertising
    //% blockHidden=true
    export function _resetAdvertising(gapName: string, serviceUUID: number): void {
        console.log("_resetAdvertising: " + gapName + ", " + serviceUUID)
    }

}
