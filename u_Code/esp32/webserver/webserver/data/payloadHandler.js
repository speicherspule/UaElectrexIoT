/*
*Dictionary for TIG Process Values
*/
var ID4 = {
	"name": "TIG Pré-Gas",
	"unit": "s"
};
var ID5 = {
	name: "TIG Istart",
	unit: "A"
};
var ID6 = {
	name: "TIG UpSlope",
	unit: "s"
};
var ID7 = {
	name: "TIG Inominal",
	unit: "A"
};
var ID8 = {
	name: "TIG Ibase",
	unit: "%"
};
var ID9 = {
	name: "TIG Pulse Width",
	unit: "%"
};
var ID10 = {
	name: "TIG Pulse Frequency",
	unit: "Hz"
};
var ID11 = {
	name : "TIG DownSlope",
	unit : "s"
};
var ID12 = {
	name: "TIG Iend",
	unit: "A"
};
var ID13 = {
	name: "TIG PostGas",
	unit: "s"
};
var ID15 = {
	name: "TIG Spot Time",
	unit: "s"
};
/*
*Dictionary for MMA Process Values
*/
var ID16 = {
	name: "MMA Hotstart",
	unit: "%"
};
var ID17 = {
	name: "MMA Hotstart Time",
	unit: "s"
};
var ID18 = {
	name: "MMA Inominal",
	unit: "A"
};
var ID19 = {
	name: "MMA Arcforce",
	unit: "A"
};
var ID20 = {
	name: "MMA Ibase",
	unit: "%"
};
var ID21 = {
	name: "MMA Pulse Width",
	unit: "%"
};
var ID22 = {
	name: "MMA Pulse Frequency",
	unit: "Hz"
};
obj2 = {27: "999", 28: "999"}

function handler(obj){
	if(  JSON.stringify(obj) === JSON.stringify(obj2) ){
		doSend(0xAC)
	}
	
	Object.keys(obj).forEach(function (key){
		switch(key){
		case "1":
			 				
			if(obj["1"] == 0x00){	//tighf
				ledON("IDtighf");
				ledOFF("IDliftig");
				ledOFF("IDmma");
				ledOFF("IDpulse");
				table("tig");
			}

			if(obj["1"] == 0x01){	//tighf pulse
				ledON("IDtighf");
				ledOFF("IDliftig");
				ledOFF("IDmma");
				ledON("IDpulse");
				table("tig");
			}

			if(obj["1"] == 0x02){	//tiglightarc 
				ledOFF("IDtighf");
				ledON("IDliftig");
				ledOFF("IDmma");
				ledOFF("IDpulse");
				table("tig");
			}		

			if(obj["1"] == 0x03){	//tiglightarc pulse 
				ledOFF("IDtighf");
				ledON("IDliftig");
				ledOFF("IDmma");
				ledON("IDpulse");
				table("tig");
			}

			if(obj["1"] == 0x04){	//mma
				ledOFF("IDtighf");
				ledOFF("IDliftig");
				ledON("IDmma");
				ledOFF("IDpulse");
				table("mma");


			}

			if(obj["1"] == 0x05){	//mma pulse
				ledOFF("IDtighf");
				ledOFF("IDliftig");
				ledON("IDmma");
				ledON("IDpulse");
				table("mma");
			}				
			break;

		case "2":
			if(obj["2"] == 0x00){	//mma
			//o que faz?	
			}
			if(obj["2"] == 0x01){	//2t
				ledON("ID2t");
				ledOFF("ID4t");
				ledOFF("IDspot");
			}
			if(obj["2"] == 0x02){	//4t
				ledOFF("ID2t");
				ledON("ID4t");
				ledOFF("IDspot");
			}
			if(obj["2"] == 0x03){	//spot
				ledOFF("ID2t");
				ledOFF("ID4t");
				ledON("IDspot");
			}
			break;

		case "3":
			if(obj["3"] == 0x00){	//refrig off
				ledOFF("IDgas");
				ledOFF("IDwater");	
			}
			if(obj["3"] == 0x01){	//ref gas
				ledON("IDgas");
				ledOFF("IDwater");
			}
			if(obj["3"] == 0x02){	//ref water
				ledOFF("IDgas");
				ledON("IDwater");
			}	
			break;

		case "4":
			var n = obj["4"];
			n = parseInt(n);
			document.getElementById('IDPar1').textContent = ID4.name;
			document.getElementById('IDVal1').textContent = (n*0.1).toFixed(1)+" "+ ID4.unit;

			break;

		case "5":
			document.getElementById('IDPar2').textContent = ID5.name;
			document.getElementById('IDVal2').textContent = obj["5"]+" "+ ID5.unit;
			break;	
		
		case "6":
			var n = obj["6"];
			n = parseInt(n);
			document.getElementById('IDPar3').textContent = ID6.name;
			document.getElementById('IDVal3').textContent = (n*0.1).toFixed(1)+" "+ID6.unit;
			break;

		case "7":
			document.getElementById('IDPar4').textContent = ID7.name;
			document.getElementById('IDVal4').textContent = obj["7"]+" "+ ID7.unit;
			break;

		case "8":
			document.getElementById('IDPar5').textContent = ID8.name;
			document.getElementById('IDVal5').textContent = obj["8"]+" "+ ID8.unit;
			break;

		case "9":
			document.getElementById('IDPar6').textContent = ID9.name;
			document.getElementById('IDVal6').textContent = obj["9"]+" "+ ID9.unit;
			break;

		case "10":
			document.getElementById('IDPar7').textContent = ID10.name;
			document.getElementById('IDVal7').textContent = obj["10"]+" "+ ID10.unit;
			break;
		case "11":
			var n = obj["11"];
			n = parseInt(n);		
			document.getElementById('IDPar8').textContent = ID11.name;
			document.getElementById('IDVal8').textContent = (n*0.1).toFixed(1)+" "+ ID11.unit;		
			break;
		case "12":
			document.getElementById('IDPar9').textContent = ID12.name;
			document.getElementById('IDVal9').textContent = obj["12"]+" "+ ID12.unit;			
			break;
		case "13":
			var n = obj["13"];
			n = parseInt(n);		
			document.getElementById('IDPar10').textContent = ID13.name;
			document.getElementById('IDVal10').textContent = (n*0.1).toFixed(1)+" "+ ID13.unit;			
			break;
		case "14":
			/*if(obj["14"] == 0x00){
				ledOFF("IDdynamics");	
			}
			if(obj["14"] == 0x01){
				ledON("IDdynamics");	
			}*/
			break;				
		
		case "15":
			var n = obj["15"];
			n = parseInt(n);		
			document.getElementById('IDPar11').textContent = ID15.name;
			document.getElementById('IDVal11').textContent = (n*0.1).toFixed(1)+" "+ ID15.unit;	
			break;
		case "16":
			document.getElementById('IDPar1').textContent = ID16.name;
			document.getElementById('IDVal1').textContent = obj["16"]+" "+ ID16.unit;	
			break;
		case "17":
			var n = obj["17"];
			n = parseInt(n);		
			document.getElementById('IDPar2').textContent = ID17.name;
			document.getElementById('IDVal2').textContent = (n*0.1).toFixed(1)+" "+ ID17.unit;			
			break;
		case "18":
			document.getElementById('IDPar3').textContent = ID18.name;
			document.getElementById('IDVal3').textContent = obj["18"]+" "+ ID18.unit;			
			break;
		case "19":
			document.getElementById('IDPar4').textContent = ID19.name;
			document.getElementById('IDVal4').textContent = obj["19"]+" "+ ID19.unit;			
			break;	
		case "20":
			document.getElementById('IDPar5').textContent = ID20.name;
			document.getElementById('IDVal5').textContent = obj["20"]+" "+ ID20.unit;
			break;
		case "21":
			document.getElementById('IDPar6').textContent = ID21.name;
			document.getElementById('IDVal6').textContent = obj["21"]+" "+ ID21.unit;		
			break;
		case "22":
			var n = obj["22"];
			n = parseInt(n);
			document.getElementById('IDPar7').textContent = ID22.name;
			document.getElementById('IDVal7').textContent = (n*0.1).toFixed(1)+" "+ID22.unit;			
			break;
		case "23":
			
				if(obj["23"] == 0x00){	//soldadura inactiva
					document.getElementById('IDgraph').src = "graph.jpg";
				}
				if(obj["23"] == 0x01){	//pregas
					document.getElementById('IDgraph').src = "pregas.jpg";
				}
				if(obj["23"] == 0x02){	//temporizaçao de HF
					document.getElementById('IDgraph').src = ".jpg";
				}
				if(obj["23"] == 0x03){	//istart
					document.getElementById('IDgraph').src = "istart.jpg";
				}					
				if(obj["23"] == 0x04){	//temporizaçao de rampa de subida
					document.getElementById('IDgraph').src = "upslope.jpg";
				}
				if(obj["23"] == 0x05){	//i nominal
					document.getElementById('IDgraph').src = "ip.jpg";
				}	
				if(obj["23"] == 0x06){	//i nominal pulsada
					document.getElementById('IDgraph').src = ".jpg";
				}	
				if(obj["23"] == 0x07){	//ibase
					document.getElementById('IDgraph').src = "ib.jpg";
				}	
				if(obj["23"] == 0x08){	//temporizao de rampa de descida
					document.getElementById('IDgraph').src = "downslope.jpg";
				}
				if(obj["23"] == 0x09){	//corrente final
					document.getElementById('IDgraph').src = "ifinal.jpg";
				}
				if(obj["23"] == 0x0A){	//temporizaçao de post gas
					document.getElementById('IDgraph').src = ".jpg";
				}			
				if(obj["23"] == 0x0B){	//espera de libertaçao de gatilho
					document.getElementById('IDgraph').src = "postgas.jpg";
				}	
			break;
		case "24":
	
			break;																									
		case "26":

			if(obj["15"] == 0x00){	//erro 0 no errors
				ledOFF("IDrefrig"); 
				ledOFF("IDtemp");
				ledOFF("IDvrd");
			}
			if(obj["15"] == 0x01){	//erro 1 Erro de alarme de temperatura 
				ledOFF("IDrefrig");
				ledON("IDtemp");
				ledOFF("IDvrd");
			}
			if(obj["15"] == 0x02){	//erro 2 Erro de alarme de falta de água
				ledON("IDrefrig");
				ledOFF("IDtemp");
				ledOFF("IDvrd");
			}

			if(obj["15"] == 0x05){	//Erro de falta de fase 
				//devia piscar aqui o led de on/off
			}							
			break;

		case "26":
			break;		

	case "27": 		//tension tension
		var n = obj["27"];
		n = parseInt(n);

		gauge_tension.set(parseInt(obj["27"])); // set actual value
		document.getElementById('LabelTension').textContent = (n*0.1).toFixed(1)+ " V";
		break;
	
	case "28": 	//value current
		gauge_current.set(parseInt(obj["28"])); // set actual value
		document.getElementById('LabelCurrent').textContent = obj["28"]+ " A";
		break;	

	default: 
   	 	console.log('Not supported');
    break;
	}
});
}
function ledON(led) {
    var element = document.getElementById(led);
    element.classList.remove("led-off");
    element.classList.add("led-on");
}
function ledOFF(led){
	var element = document.getElementById(led);
	element.classList.remove("led-on");
    element.classList.add("led-off");
}

function table(type){
	if(type == "mma"){
		var result_style = document.getElementById('ID_tig_table8').style;
		result_style.display = 'display: none';
		var result_style = document.getElementById('ID_tig_table9').style;
		result_style.display = 'display: none';
		var result_style = document.getElementById('ID_tig_table10').style;
		result_style.display = 'display: none';
		var result_style = document.getElementById('ID_tig_table11').style;
		result_style.display = 'display: none';
	}
	if(type == "tig"){
		var result_style = document.getElementById('ID_tig_table8').style;
		result_style.display = 'table-row';
		var result_style = document.getElementById('ID_tig_table9').style;
		result_style.display = 'table-row';
		var result_style = document.getElementById('ID_tig_table10').style;
		result_style.display = 'table-row';
		var result_style = document.getElementById('ID_tig_table11').style;
		result_style.display = 'table-row';						
	}	
}
