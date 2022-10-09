var express = require("express");
var app = express();
var fs = require('fs');

/*PATH para algumas manipulacoes dos 4 LEDs internos */
var LED0 = "/sys/class/leds/beaglebone:green:usr0/brightness";
var LED1 = "/sys/class/leds/beaglebone:green:usr1/brightness";
var LED2 = "/sys/class/leds/beaglebone:green:usr2/brightness";
var LED3 = "/sys/class/leds/beaglebone:green:usr3/brightness";

var triggerLED0 = "/sys/class/leds/beaglebone:green:usr0/trigger";
var triggerLED1 = "/sys/class/leds/beaglebone:green:usr1/trigger";
var triggerLED2 = "/sys/class/leds/beaglebone:green:usr2/trigger";
var triggerLED3 = "/sys/class/leds/beaglebone:green:usr3/trigger";

/*Renderizacao da pagina inicial, todos os LEDs apagado */
app.get("/", function(req, res){
    res.sendFile(__dirname + "/index.html");
    fs.open(LED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED0, '0', function (err) {
                if (err) throw err;
            });
        }
    })
    fs.open(LED1, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED1, '0', function (err) {
                if (err) throw err;
            });
        }
    })
    fs.open(LED2, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED2, '0', function (err) {
                if (err) throw err;
            });
        }
    })
    fs.open(LED3, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED3, '0', function (err) {
                if (err) throw err;
            });
        }
    })

})

app.get("/usr0on", function(req, res){
    fs.open(LED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED0, '1', function (err) {
                if (err) throw err;
                console.log('led USR0 ligado!');
            });
        }
    })
})

app.get("/usr0off", function(req, res){
    fs.open(LED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED0, '0', function (err) {
                if (err) throw err;
                console.log('led USR0 apagado!');
            });
        }
    })
})

app.get("/usr1on", function(req, res){
    fs.open(LED1, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED1, '1', function (err) {
                if (err) throw err;
                console.log('led USR1 ligado!');
            });
        }
    })
})

app.get("/usr1off", function(req, res){
    fs.open(LED1, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED1, '0', function (err) {
                if (err) throw err;
                console.log('led USR1 apagado!');
            });
        }
    })
})

app.get("/usr2on", function(req, res){
    fs.open(LED2, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED2, '1', function (err) {
                if (err) throw err;
                console.log('led USR2 ligado!');
            });
        }
    })
})

app.get("/usr2off", function(req, res){
    fs.open(LED2, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED2, '0', function (err) {
                if (err) throw err;
                console.log('led USR2 apagado!');
            });
        }
    })
})

app.get("/usr3on", function(req, res){
    fs.open(LED3, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED3, '1', function (err) {
                if (err) throw err;
                console.log('led USR3 ligado!');
            });
        }
    })
})

app.get("/usr3off", function(req, res){
    fs.open(LED3, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(LED3, '0', function (err) {
                if (err) throw err;
                console.log('led USR3 apagado!');
            });
        }
    })
})

/*rota para o modo delay no LED USR0*/
app.get("/delayusr0", function(req, res){
    fs.open(triggerLED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED0, 'timer', function (err) {
                if (err) throw err;
                console.log('modo delay USR0!');
            });
        }
    })
})

/*rota para o modo delay no LED USR1*/
app.get("/delayusr1", function(req, res){
    fs.open(triggerLED1, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED1, 'timer', function (err) {
                if (err) throw err;
                console.log('modo delay USR1!');
            });
        }
    })
})

/*rota para o modo delay no LED USR2*/
app.get("/delayusr2", function(req, res){
    fs.open(triggerLED2, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED2, 'timer', function (err) {
                if (err) throw err;
                console.log('modo delay USR2!');
            });
        }
    })
})

/*rota para o modo delay no LED USR3*/
app.get("/delayusr3", function(req, res){
    fs.open(triggerLED3, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED3, 'timer', function (err) {
                if (err) throw err;
                console.log('modo delay USR3!');
            });
        }
    })
})
/*rota para o modo heartbeat no LED USR0*/
app.get("/heartbeat0", function(req, res){
    fs.open(triggerLED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED0, 'heartbeat', function (err) {
                if (err) throw err;
                console.log('Heartbeat USR0 ligado!');
            });
        }
    })
})
/*rota para o modo heartbeat no LED USR1*/
app.get("/heartbeat1", function(req, res){
    fs.open(triggerLED1, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED1, 'heartbeat', function (err) {
                if (err) throw err;
                console.log('Heartbeat USR1 ligado!');
            });
        }
    })
})

/*rota para o modo heartbeat no LED USR2*/
app.get("/heartbeat2", function(req, res){
    fs.open(triggerLED0, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED2, 'heartbeat', function (err) {
                if (err) throw err;
                console.log('Heartbeat USR2 ligado!');
            });
        }
    })
})

/*rota para o modo heartbeat no LED USR3*/
app.get("/heartbeat3", function(req, res){
    fs.open(triggerLED3, "w", (err, fd) => {
        if (err) {
            console.log(err.message);
        } else {
            fs.writeFile(triggerLED3, 'heartbeat', function (err) {
                if (err) throw err;
                console.log('Heartbeat USR3 ligado!');
            });
        }
    })
})

app.listen(8080);
//console.log('server started on port: 8080');
