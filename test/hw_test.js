/**
 * Created by acomitevski on 27/11/14.
 */

'use strict';

var parport2 = require('../build/Release/parport2.node');

var port = new parport2(0x2000);

port.writeControl(32); // Set data byte to input
console.log('Data:', port.readData());
port.writeControl(0); // Set data byte to output
port.dataWrite(241);
