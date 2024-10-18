
/**
* Use this file to define custom functions and blocks.
* Read more at https://makecode.microbit.org/blocks/custom
*/

enum MyEnum {
    //% block="one-1"
    One,
    //% block="two-2"
    Two
}

/**
 * Custom blocks
 * icon: a Unicode identifier for an icon from the Font Awesome icon set.
 *       http://fontawesome.io/icons
 */
//% block="Custom Blocks"
//% weight=100 color=#696969 icon="\uf1b2"
namespace custom {
    /**
     * TODO: describe your function here
     * @param n describe parameter here, eg: 5
     * @param s describe parameter here, eg: "Hello"
     * @param e describe parameter here
     */
    //% block
    export function foo(n: number, s: string, e: MyEnum): void {
        // Add code here
    }

    /**
     * Using C++ in addition to the simulator implementation
     * Read more at https://makecode.com/simshim
     * @returns device runtime
     */
    //% block
    //% shim=custom::baz
    export function baz(): number {
        // implementation for simulator
        return DEVICE_RUNTIME.RUNTIME_SIMU + 5;
    }

}
