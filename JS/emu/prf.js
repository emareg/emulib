"use strict";            // JS in strict mode
var g_prfs = {}          // holds all profiler instances
const CFG_PRECISION = 3  // Number of decimal places for seconds

window.prf = {
  id: "root",
  start: function() { this.t_start = performance.now(); },
  stop: function() { 
    var dt = performance.now() - this.t_start;
    this.t_min = dt < this.t_min ? dt : this.t_min;
    this.t_max = this.t_max < dt ? dt : this.t_max;
    this.t_total += dt;
    this.nSamples += 1;
  },
  reset: function() { 
    this.t_start = 0.0;
    this.t_total = 0.0;
    this.t_min = 10000.0;
    this.t_max = 0.0; 
    this.nSamples = 0;
  },
  print: function() { 
    var avg = Number(this.t_total / this.nSamples).toFixed(CFG_PRECISION);
    var min = Number(this.t_min).toFixed(CFG_PRECISION);
    var max = Number(this.t_max).toFixed(CFG_PRECISION);
    console.log("%s-Profile: %i calls, (min ≤ avg ≤ max) = %ss ≤ %ss ≤ %ss", this.id, this.nSamples, min, avg, max)
  },
  getProfiler: function(id){
    if (g_prfs[id]) { 
      return g_prfs[id]; 
    }
    g_prfs[id] = Object.assign({}, this);
    g_prfs[id].id = id;
    g_prfs[id].reset()
    return g_prfs[id];
  }, 
};
if (!prf.t_start){ prf.reset(); }  // reset the root profiler
