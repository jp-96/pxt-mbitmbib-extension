/**
 * tests go here; this will not be compiled when this package is used as an extension.
 */
// bar
input.onButtonPressed(Button.A, function () {
    a = custom.bar()
})
// baz
input.onButtonPressed(Button.B, function () {
    a = custom.baz()
})
let a = 0
a = -1
basic.showString("B")
basic.forever(function () {
    if (0 <= a) {
        basic.showNumber(a)
    }
    basic.pause(100)
})
