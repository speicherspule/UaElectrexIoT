var opts = {
  angle: 0.15, // The span of the gauge arc
  lineWidth: 0.44, // The line thickness
  radiusScale: 1, // Relative radius
  pointer: {
    length: 0.6, // // Relative to gauge radius
    strokeWidth: 0.035, // The thickness
    color: '#000000' // Fill color
  },
  limitMax: false,     // If false, max value increases automatically if value > maxValue
  limitMin: false,     // If true, the min value of the gauge will be fixed
  colorStart: '#6FADCF',   // Colors
  colorStop: '#8FC0DA',    // just experiment with them
  strokeColor: '#E0E0E0',  // to see which ones work best for you
  generateGradient: true,
  highDpiSupport: true,     // High resolution support
  percentColors : [[0.0, "#a9d70b" ], [0.50, "#f9c802"], [1.0, "#ff0000"]],
};

var target_tension = document.getElementById('gauge_tension'); // your canvas element
var target_current = document.getElementById('gauge_current'); // your canvas element

var gauge_tension = new Gauge(target_tension).setOptions(opts); // create sexy gauge!
var gauge_current = new Gauge(target_current).setOptions(opts); // create sexy gauge!


gauge_tension.maxValue = 255; // set max gauge value
gauge_tension.setMinValue(0);  // Prefer setter over gauge.minValue = 0
gauge_tension.animationSpeed = 18; // set animation speed (32 is default value)


gauge_current.maxValue = 255; // set max gauge value
gauge_current.setMinValue(0);  // Prefer setter over gauge.minValue = 0
gauge_current.animationSpeed = 18; // set animation speed (32 is default value)



percentColors = [[0.0, "#a9d70b" ], [0.50, "#f9c802"], [1.0, "#ff0000"]];