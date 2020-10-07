var opts = {
  angle: 0,
  // The span of the gauge arc
  lineWidth: 0.2,
  // The line thickness
  radiusScale: 0.85,
  // Relative radius
  pointer: {
    length: 0.6,
    // // Relative to gauge radius
    strokeWidth: 0.035,
    // The thickness
    color: '#FFFFFF' // Fill color

  },
  limitMax: false,
  // If false, max value increases automatically if value > maxValue
  limitMin: false,
  // If true, the min value of the gauge will be fixed
  colorStart: '#B30707',
  // Colors
  colorStop: '#B30707',
  // just experiment with them
  strokeColor: '#EEEEEE',
  // to see which ones work best for you
  generateGradient: true,
  highDpiSupport: true // High resolution support

};
var target_tension = document.getElementById('gauge_tension'); // your canvas element

var gauge_tension = new Gauge(target_tension).setOptions(opts); // create sexy gauge!

gauge_tension.maxValue = 500; // set max gauge value

gauge_tension.setMinValue(0); // Prefer setter over gauge.minValue = 0

gauge_tension.animationSpeed = 16; // set animation speed (32 is default value)
//# sourceMappingURL=gauge-functions.js.map


var target_current = document.getElementById('gauge_current'); // your canvas element

var gauge_current = new Gauge(target_current).setOptions(opts); // create sexy gauge!

gauge_current.maxValue = 500; // set max gauge value

gauge_current.setMinValue(0); // Prefer setter over gauge.minValue = 0

gauge_current.animationSpeed = 16; // set animation speed (32 is default value)
//# sourceMappingURL=gauge-functions.js.map