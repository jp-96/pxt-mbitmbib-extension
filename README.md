
> Open this page at GitHub Pages: [https://jp-rad.github.io/pxt-ubit-extension/](https://jp-rad.github.io/pxt-ubit-extension/)

## Creating Extensions

Extensions are PXT’s dynamic/static library mechanism for extending a target, such as the pxt-micro:bit:

* [MakeCode extensions](https://makecode.com/extensions)

### Use this template

* open the repository on github.  
[https://github.com/jp-rad/pxt-ubit-extension](https://github.com/jp-rad/pxt-ubit-extension)
* click **Use this template**.  
[Here - https://github.com/jp-rad/pxt-ubit-extension/generate](https://github.com/jp-rad/pxt-ubit-extension/generate)
* settings for your new repository.  
Settings > Actions > General > Workflow permissions: **Read and write permissions**  
Settings > Pages > branch: **master**

## Use as Extension

This repository can be added as an **extension** in MakeCode.

* open [https://makecode.microbit.org/](https://makecode.microbit.org/)
* click on **New Project**
* click on **Extensions** under the gearwheel menu
* search for **https://github.com/jp-rad/pxt-ubit-extension** and import

## Edit this project ![Build status badge](https://github.com/jp-rad/pxt-ubit-extension/workflows/MakeCode/badge.svg)

To edit this repository in MakeCode.

* open [https://makecode.microbit.org/](https://makecode.microbit.org/)
* click on **Import** then click on **Import URL**
* paste **https://github.com/jp-rad/pxt-ubit-extension** and click import

## Blocks preview

<!--
This image shows the blocks code from the last commit in master.
This image may take a few minutes to refresh.

![A rendered view of the blocks](https://github.com/jp-rad/pxt-ubit-extension/raw/master/.github/makecode/blocks.png)
-->
![A rendered view of the blocks](https://github.com/jp-rad/pxt-ubit-extension/raw/master/.github/statics/blocks.png)


### Blocks embed

[https://makecode.microbit.org/blocks-embed](https://makecode.microbit.org/blocks-embed)

Copy the following text at the bottom of your README.md file.

```

<script src="https://cdn.jsdelivr.net/gh/jp-rad/pxt-ubit-extension@0.5.0/.github/statics/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", [ "custom=github:jp-rad/pxt-ubit-extension", ]);</script>

```

### `blocks`

**Example1**

```blocks
custom.foo(4, "Hello", MyEnum.One)

```


**Example2**

```blocks
input.onButtonPressed(Button.A, function () {
    basic.showNumber(custom.baz())
})
input.onButtonPressed(Button.B, function () {
    basic.showNumber(custom.bar())
})

```

## Downloaded HEX file to Use as Extension

Released HEX file can be imported as an **extension** in MakeCode.

* open [https://github.com/jp-rad/pxt-ubit-extension/releases](https://github.com/jp-rad/pxt-ubit-extension/releases)
* download HEX file
* open [https://makecode.microbit.org/](https://makecode.microbit.org/)
* click on **New Project**
* click on **Extensions** under the gearwheel menu
* click on **Import File**
* select downloaded HEX file and click on **Go ahead!**


#### Metadata (used for search, rendering)

* for PXT/microbit

<script src="https://cdn.jsdelivr.net/gh/jp-rad/pxt-ubit-extension@0.5.0/.github/statics/gh-pages-embed.js"></script>
<script>makeCodeRender("{{ site.makecode.home_url }}", [ "custom=github:jp-rad/pxt-ubit-extension", ]);</script>
