// emulib – micro SVG lib



// 
window.t4t = {
  svgNS: 'http://www.w3.org/2000/svg',
  svgs: {},
  load: function(id, xstep=1){ this.svgs[id] = document.getElementById(id).contentDocument; },
  updateText: function(query, val){ 
    for (const el of document.querySelectorAll(query)){ el.innerHTML = val; } 
    for (const el of document.querySelectorAll(query)){ el.innerHTML = val; } 
    for (key in t4t.svgs) { for (const el of t4t.svgs[key].querySelectorAll(query)){ el.innerHTML = val; } }
  },

  parseValue: function (str) {
    let prescale = 1
    let value = str.slice(0, -1)
    // todo regex remove unit
    switch (str.slice(-1)) {
      case 'G': prescale = 1e9; break;
      case 'M': prescale = 1e6; break;
      case 'k': prescale = 1e3; break;
      case 'm': prescale = 1e-3; break;
      case 'u': prescale = 1e-6; break;  // todo: add μ
      case 'n': prescale = 1e-9; break;
      default: value = str;
    }
    return (Number(value) * prescale)
  },

  askValue: function (query) {
    const el = document.querySelector(query)
    const newval = prompt('Please enter new Value', el.textContent)
    if (isNaN(this.parseValue(newval))) {
      el.textContent = 'NaN'
    } else {
      el.textContent = newval
    }
    this.updateText(query, newval)
  }
}


      // toggles 
      function toggleCollapse(ev) {
        query = ev.target.getAttribute("href")
        var els;
        if (query){ els = document.querySelectorAll(query); } 
        else { els = [ev.target.nextElementSibling]; }

        for (const el of els){
          if (el.style.maxHeight){ el.style.maxHeight = null; } 
          else { el.style.maxHeight = el.scrollHeight + "px"; }
        }
      }


document.addEventListener('DOMContentLoaded', function() {
      for (const el of document.querySelectorAll('.toggle-btn')){
        el.addEventListener('click', toggleCollapse);
        if (query){ els = document.querySelectorAll(query); } 
        else { els = [el.nextElementSibling]; }

        for (const tar of els){
          tar.style.maxHeight = "0";
          tar.style.paddingTop = "0";
          tar.style.paddingBottom = "0";
        }
      }
});




// matplotlib interfaces
mpl = {
  select: function(query){ return this.svg.querySelector(query); },
  load: function (id, xtick0=1, ytick0=1, xstep=1) { 
    this.svg = document.getElementById(id).contentDocument;
    this.svg.id = id
    t4t.load(id);
    var iTick0={'x': xtick0, 'y':ytick0}
    var scales={'xstep': xstep};
    for (const dim of ["x", "y"]){
      var t0val = parseFloat( this.svg.getElementById(dim+"tick_"+iTick0[dim]).querySelector("use").getAttribute(dim) )
      var t1 = this.svg.getElementById(dim+"tick_"+(iTick0[dim]+1))
      scales[dim+"0"] = t0val
      scales[dim+"scale"] = (parseFloat( t1.querySelector("use").getAttribute(dim) ) - t0val) / parseFloat( t1.querySelector("text").textContent )
    }
    t4t.svgs[this.svg.id].scales = scales
    t4t.svgs[this.svg.id].args = {}
    // console.log(scales)
    return scales
  },

  connectSlider: function(sliderID, updatefun, classid){
    svg = this.svg
    slider = document.getElementById(sliderID);
    slider.svgID = svg.id
    t4t.svgs[svg.id].args[classid] = parseFloat( slider.value )
    svg.args[classid] = parseFloat( slider.value )

    slider.addEventListener("input", function(ev){
      // console.log(this, svg.args)
      svg = t4t.svgs[ev.target.svgID]
      svg.args[classid] = parseFloat( ev.target.value )
      t4t.updateText("."+classid, ev.target.value)

      marks= (e=svg.getElementById("markers_1")) ? e.children[0].children : []
      path = (e=svg.getElementById("t4tPathG")) ? e.children[0] : null
      segs = path ? path.getAttribute('d').split(/\s*[LlVvHh]\s*/) : []
      combs = (e=svg.getElementById("LineCollection_1")) ? e.children : []
      for (var i = 0; i < Math.max(marks.length, segs.length); i++) {
        y = svg.scales.y0 + (updatefun(i*svg.scales.xstep, svg.args) * svg.scales.yscale)
        if(isNaN(y)) { y = svg.scales.y0; }
        if (marks.length) { marks[i].setAttribute('y', y) }
        if (segs.length) { segs[i] = segs[i].replace(/(?<=\d )(\d+(?:\.\d+))/, y) }
        if (combs.length) { var d = combs[i].getAttribute('d'); combs[i].setAttribute('d', d.replace(/[LlvVhH].+/, "V "+y)); }
      }
      if (path){ path.setAttribute('d', segs.join(" L ")) }
    })
  }


}





class SVG {
  constructor(id) { this.node = document.getElementById(id); }
  select(query) { return this(this.node.querySelector(query)); }
  create(tag) { var newnode = createElementNS("http://www.w3.org/2000/svg", tag); return newnode; }
  add(el) { this.node.appendChild(el);}
  attr(key, val){ if(val==null){ return this.node.getAttribute(key) }
                  else { this.node.setAttribute(key, val); return this; } }
  style(s){ this.node.setAttribute('style', s); return this; } 
  text(text){ if(val==null){ return this.node.innerHtml }
              else { this.node.innerHtml = text; return this; } }
  stroke(s){ this.node.setAttribute('stroke', s); return this; } 
  fill(f){ this.node.setAttribute('fill', f); return this; } 
  translate(x,y){ this.node.setAttribute('transform', `translate(${x},${y})`) }
  scale(x,y){ if(!y){y=x} this.node.setAttribute('transform', `scale(${x},${y})`) }
  rotate(a){ this.node.setAttribute('transform', `rotate(${a} ${this.cx()} ${this.cy()})`) }
  line(x_s, y_s, x_t, y_t) { this.node.setAttribute('d', `M${x_s} ${y_s} ${x_t} ${y_t}`) }
  path(d){ this.node.setAttribute('d', d) } 

  r(r){ return (r==null) ? this.node.r.animVal.value : this.node.setAttribute('r', r); }
  x(x){ return (x==null) ? this.node.getBBox().x : this.node.setAttribute('x', x); }
  y(y){ return (y==null) ? this.node.getBBox().y : this.node.setAttribute('y', y); }
  cx(x){ switch (this.node.tagName) {
    case 'circle': case 'ellipse': 
      return (x==null) ? this.node.cx.animVal.value : this.node.setAttribute('cx', x); break;
    case 'rect': return this.node.x.animVal.value + this.node.width.animVal.value / 2; break;
    default: box = this.node.getBBox(); return (box.x + box.width.animVal.value) / 2; 
  }}
  cy(y){ switch (this.node.tagName) {
    case 'circle': case 'ellipse': 
      return (y==null) ? this.node.cy.animVal.value : this.node.setAttribute('cy', y); break;
    case 'rect': return this.node.y.animVal.value + (this.node.height.animVal.value/2); break;
    default: box = this.node.getBBox(); return (box.y + box.height.animVal.value) / 2; 
  }}
  height(){ switch (this.node.tagName) { 
    case 'circle':  return this.node.r.animVal.value*2; break;
    case 'ellipse': return this.node.ry.animVal.value*2; break;
    case 'rect': this.node.height.animVal.value; break;
    default: return this.node.getBBox().height;
  }}
  width(){ switch (this.node.tagName) { 
    case 'circle':  return this.node.r.animVal.value*2; break;
    case 'ellipse': return this.node.rx.animVal.value*2; break;
    case 'rect': this.node.width.animVal.value; break;
    default: return this.node.getBBox().width;
  }}
  
}

//SVG_RE_TRANSLATE=/translate\(\s*([+-]?\d*(?:\.\d*)?),\s*([+-]?\d*(?:\.\d*)?)\)/
// return (x==null) ? this.node.getAttribute('transform').match(SVG_RE_TRANSLATE).slice(1, 3) :