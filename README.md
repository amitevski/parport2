


 - Wolfgang Hackenberg

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

All other parts are unchanged and were written by Xavier Mendez.

## License

Parport.js ist released under the GPL, so Parport2.js is distributed under [GPLv3](http://www.gnu.org/licenses) as well. 

## Usage

```javascript
var par = require('parport2');

var port = new par.Port(0x2000);

port.writeControl(32); // Set data byte to input
console.log('Data:', port.readData());
port.writeControl(0); // Set data byte to output
port.dataWrite(241);
```

For low level access to the parallel port, root privileges are necessary.

Control bit 8 (byte value 32) will toggle between input and output mode of data byte.

## Compatibility

**Important:** Only work under Linux!

