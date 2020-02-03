var seriesOptions = [
  { strokeStyle: 'rgba(255, 0, 0, 1)', fillStyle: 'rgba(255, 0, 0, 0.1)', lineWidth: 3 }, //Tension
  { strokeStyle: 'rgba(0, 255, 0, 1)', fillStyle: 'rgba(0, 255, 0, 0.1)', lineWidth: 3 }, //Current
];

var tension_data = new TimeSeries();
var current_data = new TimeSeries();

function init_smoothie() {

  // Initialize an empty TimeSeries for each CPU.
  var chart_tension = new SmoothieChart({responsive: true,millisPerPixel: 20, grid: { strokeStyle: '#555555', lineWidth: 1, millisPerLine: 1000, verticalSections: 4 },maxValue:255,minValue:0});
  chart_tension.addTimeSeries(tension_data,seriesOptions[0]);
  chart_tension.streamTo(document.getElementById("chart_tension"), 0);

  var chart_current = new SmoothieChart({responsive: true,millisPerPixel: 20, grid: { strokeStyle: '#555555', lineWidth: 1, millisPerLine: 1000, verticalSections: 4 },maxValue:255,minValue:0});
  chart_current.addTimeSeries(current_data,seriesOptions[1]);
  chart_current.streamTo(document.getElementById("chart_current"), 0);
 
}

function addValueTension(time,value) {
    tension_data.append(time,value);
}

function addValueCurrent(time,value) {
    current_data.append(time,value);
}
