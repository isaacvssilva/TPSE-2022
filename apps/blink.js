/*
 * =====================================================================================
 *
 *       Filename:  blink.js
 *
 *    Description:  Blink LED using sysfs in BBB | version JavaScript with Nodejs
 *
 *        Version:  1.0
 *        Created:  27/09/2022 16:21:23
 *       Revision:  none
 *       Compiler:  nodejs -v 14.20 in Beaglebone Black
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
 
const path = "/sys/class/leds/beaglebone:green:usr1/trigger";
var fs = require('fs');

fs.open(path, "rs", (err, fd)=>{
    if(err){
        console.log(err.message);
    }else{
        fs.writeFile(path, 'timer', function (err){
            if (err) throw err;
            console.log('Texto salvo!');
        });
    }
})
