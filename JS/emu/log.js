"use strict";  // JS in strict mode
var g_logs = {}
var _cons = window.console;
var _noop = function() {};

window.log = {
  id: "root",
  css: "display: inline-block; color: #fff; font-weight: bold; padding: 2px 5px; border-radius: 3px; background-color: ",
  TRACE: 0, DEBUG: 1, INFO: 2, WARN: 3, ERROR: 4,
  setLevel: function(lvl) { 
    this.trace = lvl<=this.TRACE ? _cons.trace.bind(_cons, "%c"+this.id+"-T%c %s", this.css+"#088;", "") : _noop;
    this.debug = lvl<=this.DEBUG ? _cons.log.bind(_cons, "%c"+this.id+"-D%c %s", this.css+"#666;", "") : _noop;
    this.info = lvl<=this.INFO ? _cons.info.bind(_cons, "%c"+this.id+"-I%c %s", this.css+"#08c;", "") : _noop;
    this.warn = lvl<=this.WARN ? _cons.log.bind(_cons, "%c"+this.id+"-W%c %s", this.css+"#d90;", "") : _noop;
    this.error = lvl<=this.ERROR ? _cons.log.bind(_cons, "%c"+this.id+"-E%c %s", this.css+"#e06;", "") : _noop;
    this.logLevel = lvl;
  },
  getLogger: function(id){
    if (g_logs[id]) { 
      return g_logs[id]; 
    }
    g_logs[id] = {}; 
    var key; for (key in this){ g_logs[id][key] = this[key]; }
    g_logs[id].id = id;
    g_logs[id].setLevel(this.INFO);
    return g_logs[id];
  }, 
};
log.setLevel(log.DEBUG);


// References
// * https://github.com/akoidan/lines-logger#readme
// * https://stackoverflow.com/questions/13815640/a-proper-wrapper-for-console-log-with-correct-line-number
