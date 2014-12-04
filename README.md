


 - Wolfgang Hackenberg
 - Aco Mitevski

===

# Parport2.JS

Parport2.js is a Node.JS addon you can use to **access,
control and communicate with parallel ports**.
It uses kernel macros inb and outb to
provide a **low-level** interface to the parallel port under **Linux**.

    npm install parport2

This addon is an adaption of Xavier Mendez's parport addon
(https://npmjs.org/package/parport).

## Changes

 * Matheus Neder's parallel-port library was replaced by an own implementation providing the same API.
 * Built-Scripts were changed to include the new library.
 * switched from v8u to [nan](https://github.com/rvagg/nan) as v8u did not support node 0.11 properly
 * BREAKING: instead of `new parport2.Port(0x200)` you can just call `new parport2(0x200)` 

All other parts are unchanged and were written by Xavier Mendez.

## License

Parport.js ist released under the GPL, so Parport2.js is distributed under [GPLv3](http://www.gnu.org/licenses) as well.

## Usage

```javascript
var parport2 = require('parport2');

var port = new parport2(0x2000);

port.writeControl(32); // Set data byte to input
console.log('Data:', port.readData());
port.writeControl(0); // Set data byte to output
port.writeData(241);
```

For low level access to the parallel port, root privileges are necessary.

Control bit 8 (byte value 32) will toggle between input and output mode of data byte.

## Compatibility

**Important:** Only works under Linux!

