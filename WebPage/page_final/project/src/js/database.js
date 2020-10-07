
/*
*Dictionary for TIG Process Values
*/

var dict = {
  ID10 : "TIG HF",
  ID11 : "TIG HF PULSE",
  ID12 : "TIG LIFTARC",
  ID13 : "TIG LIFTARC PULSE",
  ID14 : "MMA",
  ID15 : "MMA PULSE",

  ID10  : "MMA",
  ID21  : "TIG 2T",
  ID22  : "TIG 4T",
  ID23  : "TIG SPOT",

  ID30  : "OFF",
  ID31  : "GAS",
  ID32  : "Water",

  ID140  : "OFF",
  ID141  : "ON",  

  ID260 : "NO ERRORS",
  ID261 : "TEMPERATURE ALARM",
  ID262 : "WATER ALARM",
  ID263 : "N/A",
  ID264 : "N/A",
  ID265 : "N/A",
  ID266 : "ELECTRICAL PHASE FAULT",

  /*
  ID10 : "SOLDER OFF",
  ID11 : "START CURRENT",
  ID12 : "HOTSTART TIME",
  ID13 : "INITIAL CURRENT",
  ID14 : "ARC FORCE",
  ID15 : "MINIMUM CURRENT",
  ID16 : "BASE CURRENT",
  ID17 : "NOMINAL PULSE CURENT",
  ID18 : "VRD ACTIVATION TIME",
 */

  ID1name : "Welding Process",
  ID1unit : "s",

  ID2name : "Torch Operating Mode",
  ID2unit : "s",

  ID3name : "Cooling Mode",
  ID3unit : "s",

  ID4name : "TIG Pré-Gas",
  ID4unit : "s",
  
  ID5name : "TIG Istart",
  ID5unit : "A",

  ID6name : "TIG UpSlope",
  ID6unit : "s",

  ID7name : "TIG Inominal",
  ID7unit : "A",

  ID8name : "TIG Ibase",
  ID8unit : "%",

  ID9name : "TIG Pulse Width",
  ID9unit : "%",

  ID10name : "TIG Pulse Width",
  ID10unit : "Hz",

  ID11name : "TIG DownSlope",
  ID11unit : "s",

  ID12name : "TIG Iend",
  ID12unit : "A",

  ID13name : "TIG PostGas",
  ID13unit : "s",

  ID14name : "Dyamics",
  ID14unit : "",

  ID15name : "TIG Spot Time",
  ID15unit : "s",

  ID16name : "MMA Hotstart",
  ID16unit : "%",

  ID17name : "MMA Hotstart Time",
  ID17unit : "s",

  ID18name : "MMA Inominal",
  ID18unit : "A",

  ID19name : "MMA Arcforce",
  ID19unit : "%",

  ID20name : "MMA Ibase",
  ID20unit : "%",

  ID21name : "MMA Pulse Width",
  ID21unit : "%",

  ID22name : "MMA Pulse Frequency",
  ID22unit : "HZ",

  ID23name : "TIG Welding Status",
  ID23unit : "",

  ID24name : "MMA Welding Status",
  ID24unit : "",

  ID25name : "Welding",
  ID25unit : "",

  ID26name : "Errors",
  ID26unit : "",

  ID27name : "Welding Current Value",
  ID27unit : "A",

  ID28name : "Welding Tension Value",
  ID28unit : "V",

  IDnamename : "Machine's name"
}

/*
*Dictionary for MMA Process Values
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
	unit: "%"
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

var firebaseConfig = {
    apiKey: "AIzaSyC17gKkrvaw3b885RblLWe_TaHHM3kvWQs",
    authDomain: "uaelectrex.firebaseapp.com",
    databaseURL: "https://uaelectrex.firebaseio.com",
    projectId: "uaelectrex",
    storageBucket: "uaelectrex.appspot.com",
    messagingSenderId: "755796152546",
    appId: "1:755796152546:web:f89f509c4a85ce03528ebb",
    measurementId: "G-9W2FNK612B"
  };

 
  
  // Initialize Firebase
  
  firebase.initializeApp(firebaseConfig);
  firebase.analytics();

  var database = firebase.database();

  $.fn.dataTable.ext.errMode = 'none';


  $(document).ready(function () {
    $('#IDTableDetailedConfig').DataTable(
    {
      "pagingType": "numbers", // "simple" option for 'Previous' and 'Next' buttons only
      "searching": false, // false to disable search (or any other option)
      "ordering": false, // false to disable sorting (or any other option)
      "bLengthChange": false,
      "bInfo": false,
      "iDisplayLength": 7,
      "bPaginate" : true,
    }
    );
  });

  $(document).ready(function () {
    var counter = 1;
    var t = $('#IDTableChangeOnConfig').DataTable(
    {
      "pagingType": "numbers", // "simple" option for 'Previous' and 'Next' buttons only
      "searching": false, // false to disable search (or any other option)
      "ordering": true, // false to disable sorting (or any other option)
      "bLengthChange": false,
      "bInfo": false,
      "iDisplayLength": 4,
      "bPaginate" : true,
      "orderFixed": [ 3, 'desc' ]
    }
    );
  });

  function getAll(path){

    firebase.database().ref("maquinas").child(path+"/1").on('value', function(data) {
      obj = data.val();
      if(obj == 0x00){
        document.getElementById('IDWeldingProcess').textContent = "TIG HF";
      }
      else if(obj == 0x01){
        document.getElementById('IDWeldingProcess').textContent = "TIG HF PULSE";
      }
      else if(obj == 0x02){
        document.getElementById('IDWeldingProcess').textContent = "TIG LIFTARC";
      }
      else if(obj == 0x03){
        document.getElementById('IDWeldingProcess').textContent = "TIG LIFTARC PULSE";
      }
      else if(obj == 0x04){
        document.getElementById('IDWeldingProcess').textContent = "MMA";
      }
      else if(obj == 0x05){
        document.getElementById('IDWeldingProcess').textContent = "MMA PULSE";
      }
      else{
        document.getElementById('IDWeldingProcess').textContent = "";
      }            
    });
  
    firebase.database().ref("maquinas").child(path+"/2").on('value', function(data) {
      obj = data.val();
  
      if(obj == 0x00){
        document.getElementById('IDOperatingMode').textContent = "MMA";
      }
      else if(obj == 0x01){
        document.getElementById('IDOperatingMode').textContent = "TIG 2T";
      }
      else if(obj == 0x02){
        document.getElementById('IDOperatingMode').textContent = "TIG 4T";
      }
      else if(obj == 0x03){
        document.getElementById('IDOperatingMode').textContent = "TIG SPOT";
      } 
      else{
        document.getElementById('IDOperatingMode').textContent = "";

      }     
    });
  
    firebase.database().ref("maquinas").child(path+"/3").on('value', function(data) {
      obj = data.val();
      
      if(obj == 0x00){
        document.getElementById('IDCooling').textContent = "OFF";
      }
      if(obj == 0x01){
        document.getElementById('IDCooling').textContent = "GAS";
      }
      if(obj == 0x02){
        document.getElementById('IDCooling').textContent = "WATER";
      }
  
    });
  
    firebase.database().ref("maquinas").child(path+"/4").on('value', function(data) {
      obj = data.val();
      
      var n = obj;
      n = parseInt(n);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(0)', 0).data(ID4.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(0)', 1).data((n*0.1).toFixed(1)+" "+ ID4.unit);
  
    });
   
    firebase.database().ref("maquinas").child(path+"/5").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(1)', 0).data(ID5.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(1)', 1).data(obj+" "+ ID5.unit);
    });
  
    firebase.database().ref("maquinas").child(path+"/6").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(2)', 0).data(ID6.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(2)', 1).data((n*0.1).toFixed(1)+" "+ID6.unit);
    });
  
    firebase.database().ref("maquinas").child(path+"/7").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(3)', 0).data(ID7.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(3)', 1).data(obj+" "+ ID7.unit);
    });        
            
    firebase.database().ref("maquinas").child(path+"/8").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(4)', 0).data(ID8.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(4)', 1).data(obj+" "+ ID8.unit);
    });
    
    firebase.database().ref("maquinas").child(path+"/9").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(5)', 0).data(ID9.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(5)', 1).data(obj+" "+ ID9.unit);
    }); 
          
    firebase.database().ref("maquinas").child(path+"/10").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(6)', 0).data(ID10.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(6)', 1).data(obj+" "+ ID10.unit);
    });
    
    firebase.database().ref("maquinas").child(path+"/11").on('value', function(data) {
      obj = data.val();
      var n = obj;
      $('#IDTableDetailedConfig').DataTable().cell(':eq(7)', 0).data(ID11.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(7)', 1).data(n+" "+ ID11.unit);			
    }); 
    
    firebase.database().ref("maquinas").child(path+"/12").on('value', function(data) {
      obj = data.val();
      var n = obj;
      $('#IDTableDetailedConfig').DataTable().cell(':eq(8)', 0).data(ID12.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(8)', 1).data(n+" "+ ID12.unit);			
    });    
  
    firebase.database().ref("maquinas").child(path+"/13").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(9)', 0).data(ID13.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(9)', 1).data((n*0.1).toFixed(1)+" "+ ID13.unit);				
    }); 
    
    firebase.database().ref("maquinas").child(path+"/14").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);
      if(n == 0x00){
        document.getElementById('IDDynamics').textContent = "OFF";
      }
      if(n == 0x01){
        document.getElementById('IDDynamics').textContent = "ON";
      }    		
    });  
  
    firebase.database().ref("maquinas").child(path+"/15").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);		
      $('#IDTableDetailedConfig').DataTable().cell(':eq(10)', 0).data(ID15.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(10)', 1).data((n*0.1).toFixed(1)+" "+ ID15.unit);
    }); 
  
    firebase.database().ref("maquinas").child(path+"/16").on('value', function(data) {
      obj = data.val();
      $('#IDTableDetailedConfig').DataTable().cell(':eq(11)', 0).data(ID16.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(11)', 1).data(obj+" "+ ID16.unit);
    });          
  
    firebase.database().ref("maquinas").child(path+"/17").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(12)', 0).data(ID17.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(12)', 1).data((n*0.1).toFixed(1)+" "+ ID17.unit);
    });  
  
    firebase.database().ref("maquinas").child(path+"/18").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(13)', 0).data(ID18.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(13)', 1).data(n+" "+ ID18.unit); 
    });  
  
    firebase.database().ref("maquinas").child(path+"/19").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(14)', 0).data(ID19.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(14)', 1).data(n+" "+ ID19.unit); 
    }); 
  
    firebase.database().ref("maquinas").child(path+"/20").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(15)', 0).data(ID20.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(15)', 1).data(obj+" "+ ID20.unit);        
    }); 
  
    firebase.database().ref("maquinas").child(path+"/21").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(16)', 0).data(ID21.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(16)', 1).data(obj+" "+ ID21.unit);        
    }); 
  
    firebase.database().ref("maquinas").child(path+"/22").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      $('#IDTableDetailedConfig').DataTable().cell(':eq(17)', 0).data(ID22.name);
      $('#IDTableDetailedConfig').DataTable().cell(':eq(17)', 1).data((n*0.1).toFixed(1)+" "+ ID22.unit);        
    }); 
 
     firebase.database().ref("maquinas").child(path+"/23").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	

      if(n == 0x00){	//soldadura inactiva
        document.getElementById('IDWeldingState').textContent = "SOLDER OFF";
      }
      if(n == 0x01){	//pregas
        document.getElementById('IDWeldingState').textContent = "PRE GAS";
      }
      if(n == 0x02){	//temporizaçao de HF
        document.getElementById('IDWeldingState').textContent = "HF TIME";
      }
      if(n == 0x03){	//istart
        document.getElementById('IDWeldingState').textContent = "INITIAL CURRENT";
      }					
      if(n == 0x04){	//temporizaçao de rampa de subida
        document.getElementById('IDWeldingState').textContent = "UPSLOPE TIME";
      }
      if(n == 0x05){	//i nominal
        document.getElementById('IDWeldingState').textContent = "NOMINAL CURRENT";
      }	
      if(n == 0x06){	//i nominal pulsada
        document.getElementById('IDWeldingState').textContent = "NOMINAL PULSE CURRENT";
      }	
      if(n == 0x07){	//ibase
        document.getElementById('IDWeldingState').textContent = "BASE CURENT";
      }	
      if(n == 0x08){	//temporizao de rampa de descida
        document.getElementById('IDWeldingState').textContent = "DOWNSLOPE TIME";
      }
      if(n == 0x09){	//corrente final
        document.getElementById('IDWeldingState').textContent = "FINAL CURRENT";
      }
      if(n == 0x0A){	//temporizaçao de post gas
        document.getElementById('IDWeldingState').textContent = "POST GAS TIME";
      }			
      if(n == 0x0B){	//espera de libertaçao de gatilho
        document.getElementById('IDWeldingState').textContent = "WAITING FOR TRIGGER RELEASE";
      }	      
        });
        
      firebase.database().ref("maquinas").child(path+"/24").on('value', function(data) {
      
      obj = data.val();
      var n = obj;
      n = parseInt(n);

      if(n == 0x00){	//soldadura inactiva
        document.getElementById('IDWeldingState').textContent = "SOLDER OFF";
      }
      if(n == 0x01){	//CORRENTE ARRANQUE
        document.getElementById('IDWeldingState').textContent = "START CURRENT";
      }
      if(n == 0x02){	//TEMPORIZAÇAO HOT START
        document.getElementById('IDWeldingState').textContent = "HOTSTART TIME";
      }
      if(n == 0x03){	//CORRENT INICIAL
        document.getElementById('IDWeldingState').textContent = "INITIAL CURRENT";
      }					
      if(n == 0x04){	//ARC FORCE
        document.getElementById('IDWeldingState').textContent = "ARC FORCE";
      }
      if(n == 0x05){	//CORRENTE MINIMA
        document.getElementById('IDWeldingState').textContent = "MINIMUM CURRENT";
      }	
      if(n == 0x06){	//CORRENTE DE BASE 
        document.getElementById('IDWeldingState').textContent = "BASE CURRENT";
      }	
      if(n == 0x07){	//CORRENTE NOMINAL PULSADA
        document.getElementById('IDWeldingState').textContent = "NOMINAL PULSE CURENT";
      }	
      if(n == 0x08){	//TEMPORIZAÇAO DE ACTIVAÇAO DE VRD
        document.getElementById('IDWeldingState').textContent = "VRD ACTIVATION TIME";
      }	
        
      }); 

    firebase.database().ref("maquinas").child(path+"/26").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      if(n == 0x00){
        document.getElementById('IDErrors').textContent = "NO ERRORS";
      }
      if(n == 0x01){
        document.getElementById('IDErrors').textContent = "TEMPERATURE ALARM";
      }    
      if(n == 0x02){
        document.getElementById('IDErrors').textContent = "WATER ALARM";
      }     
      if(n == 0x03){
        document.getElementById('IDErrors').textContent = "N/A";
      }     
      if(n == 0x04){
        document.getElementById('IDErrors').textContent = "N/A";
      }     
      if(n == 0x05){
        document.getElementById('IDErrors').textContent = "N/A";
      }             
      if(n == 0x06){
        document.getElementById('IDErrors').textContent = "ELECTRICAL PHASE FAULT";
      }           
    });     
  
    firebase.database().ref("maquinas").child(path+"/27").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      gauge_current.set(n); // set actual value
      onRefresh(window.chart_Current,n);
      window.chart_Current.update();      
    }); 

    firebase.database().ref("maquinas").child(path+"/28").on('value', function(data) {
      obj = data.val();
      var n = obj;
      n = parseInt(n);	
      gauge_tension.set(n); // set actual value
      onRefresh(window.chart_Tension,n);
      window.chart_Tension.update();      
    }); 
  
    firebase.database().ref("lastChanges").child(path).on('value', function(data) {
      obj = data.val();
      var table = $('#IDTableChangeOnConfig').DataTable();
 
      table
          .clear()
          .draw();
      Object.values(obj).forEach(function (obj) { 

        var aftervalue = obj.afterValue;
        var beforevalue = obj.beforeValue;
        var changedID = obj.changedID;
        var timestamp = obj.timestamp;
        timestamp = new Date(timestamp)

        changedID_dict = 'ID'+changedID+'name';
        
        if(changedID == 1 || changedID == 2 || changedID == 3 || changedID == 14 || changedID == 26){
          stringBefore = 'ID'+changedID+beforevalue;
          stringAfter = 'ID'+changedID+aftervalue;
          beforevalue = dict[stringBefore];
          aftervalue = dict[stringAfter];
        }
        else if(changedID == "name"){

        }
        else{
          stringUnit = 'ID'+changedID+'unit';
          aftervalue = aftervalue + " " + dict[stringUnit];
          beforevalue = beforevalue + " " + dict[stringUnit];
        }
        
        $('#IDTableChangeOnConfig').dataTable().fnAddData( [
          dict[changedID_dict],
          beforevalue,
          aftervalue,
          timestamp] );
      });
    }); 
  }

  
  firebase.database().ref("maquinas").on("child_added", function(snapshot) {
    var val = snapshot.val();
    number = snapshot.key;

    if(val["name"] === ""){
      name = number;
    }
    else{
      name = val["name"];
    }

    $('#side-menu-itens').append($('<li class="c-sidebar-nav-item" style="margin-bottom: 15px;" id="parent'+number+'"><a class="c-sidebar-nav-link" id="'+number+'" style="margin-left: 15px; margin-bottom: 50px; display: inline;"><span class="c-sidebar-nav-icon"></span>'+name+'</a><button type="button" class="btn btn-primary float-right" data-toggle="modal" data-target="#exampleModal" data-whatever="'+number+'"><svg class="c-icon" width="16" height="16"><use xlink:href="vendors/@coreui/icons/svg/free.svg#cil-settings"></use></svg></button></li>'));
    $('#'+number).on("click",function() {
      getAll($(this).attr("id"))});
  });
  


  data = {name: "", 1: "", 2: "", 3: "", 4: "", 5: "", 6: "", 7: "", 8: "", 9: "", 10: "", 11: "", 12: "", 13: "", 14: "", 15: "", 16: "", 17: "", 18: "", 19: "", 20: "", 21: "", 22: "", 23: "", 24: "", 25: "", 26: "", 27: "", 28: ""};

  function addNewMachine(){

    
    firebase.database().ref('maquinas').push(data);
  }

  function deleteMachine(childName){

    
    firebase.database().ref('maquinas/'+childName).remove();
    $('#parent'+childName).remove()
  }

  function storeData(childName,newName_dentro){

 
    
    $('#'+childName).html(newName_dentro);
    firebase.database().ref('maquinas/'+childName).update({'name' : newName_dentro});
  }

  var recipient = "";

  $('#exampleModal').on('show.coreui.modal', function (event) {
    var button = $(event.relatedTarget) // Button that triggered the modal
    recipient = button.data('whatever') // Extract info from data-* attributes

    var modal = $(this)
    modal.find('.modal-title').text('Configuration of '+ recipient)
    modal.find('.modal-body input').val("Enter here a name for your machine i.e: Máquina do Zé")

    modal.find('#modal-button-delete').on("click",function() {
      deleteMachine(recipient);
    });

    modal.find('#modal-button-store').on("click",function() {
      newName = modal.find('.modal-body input').val();
      storeData(recipient,newName);
    });
  });


