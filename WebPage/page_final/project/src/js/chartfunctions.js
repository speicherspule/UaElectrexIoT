var chartColors = {
	red: 'rgb(255, 99, 132)',
	orange: 'rgb(255, 159, 64)',
	yellow: 'rgb(255, 205, 86)',
	green: 'rgb(75, 192, 192)',
	blue: 'rgb(54, 162, 235)',
	purple: 'rgb(153, 102, 255)',
	grey: 'rgb(201, 203, 207)'
};

function randomScalingFactor() {
	return (Math.random() > 0.5 ? 1.0 : -1.0) * Math.round(Math.random() * 100);
}

function onRefresh(chart,value) {
	chart.config.data.datasets.forEach(function(dataset) {
		dataset.data.push({
			x: Date.now(),
			y: value
		});
	});
}

var color = Chart.helpers.color;

var config_tens = {
	type: 'line',
	data: {
		datasets: [{
			label: 'label',
			hidden: false,
			backgroundColor: color(chartColors.red).alpha(0.5).rgbString(),
			borderColor: chartColors.red,
			fill: false,
			lineTension: 0,
			borderDash: [8, 4],
			data: []
		}]
	},
	options: {
		title: {
			display: false,
		},
		legend: {
			display: false
			},
		scales: {
			xAxes: [{
				type: 'realtime',
				realtime: {
					duration: 20000,
					refresh: 1000,
					delay: 2000,
					onRefresh: onRefresh
				}
			}],
			yAxes: [{
				ticks: {
					suggestedMin: 0,
                    suggestedMax: 50	
				},
				scaleLabel: {
					display: true,
					labelString: 'value'
				}
			}]
		},
		tooltips: {
			mode: 'nearest',
			intersect: false
		},
		hover: {
			mode: 'nearest',
			intersect: false
		}
	}
};

var config_curr = {
	type: 'line',
	data: {
		datasets: [{
			label: 'label',
			hidden: false,
			backgroundColor: color(chartColors.red).alpha(0.5).rgbString(),
			borderColor: chartColors.red,
			fill: false,
			lineTension: 0,
			borderDash: [8, 4],
			data: []
		}]
	},
	options: {
		title: {
			display: false,
		},
		legend: {
			display: false
			},
		scales: {
			xAxes: [{
				type: 'realtime',
				realtime: {
					duration: 20000,
					refresh: 1000,
					delay: 2000,
					onRefresh: onRefresh
				}
			}],
			yAxes: [{
				ticks: {
					suggestedMin: 0,
                    suggestedMax: 500	
				},
				scaleLabel: {
					display: true,
					labelString: 'value'
				}
			}]
		},
		tooltips: {
			mode: 'nearest',
			intersect: false
		},
		hover: {
			mode: 'nearest',
			intersect: false
		}
	}
};

window.onload = function() {
	var ctx_ten = document.getElementById('chart_Tension').getContext('2d');
	window.chart_Tension = new Chart(ctx_ten, config_tens);

	var ctx_curr = document.getElementById('chart_Current').getContext('2d');
	window.chart_Current = new Chart(ctx_curr, config_curr);

};


