// Includes  
#include <WiFi.h>   
#include <WebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>

#define RXD2 16
#define TXD2 17
//Global variables
unsigned char incomingByte,length_data,checksum_recv,checksum_calc = 0,id,length_value,value;
unsigned char bufferpayload[64];
int pos=0,j=0,k=0,p=0,value_int=0,v=0;

//Uart StateMachine states
typedef enum {WaitingStartByte,Framelength,Payload,CheckSum,Value} state_machine_t;
state_machine_t data_state_s;

WebServer server; //Create web server

char* ssid = "TIG DC PULSE 500A";
char* password = "";

// hold uploaded file
File fsUploadFile;
WebSocketsServer webSocket = WebSocketsServer(81);

// Called when receiving any WebSocket message
void onWebSocketEvent(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Echo text message back to client
    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      webSocket.sendTXT(num, payload);
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

void setup()
{
  // Format the file system in case it hasn't been done before
  SPIFFS.begin(true);
  
  // Start access point
  WiFi.softAP(ssid, password);
   
  
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  // Print our IP address
  Serial.println();
  Serial.println("AP running");
  Serial.print("My IP address: ");
  Serial.println(WiFi.softAPIP());

 //handle html files
  server.on("/",handleIndexFile);
  
  // handle JavaScript files
  server.on("/payloadHandler.js",handleJS2File);
  server.on("/websocket.js",handleJS3File);
  server.on("/ui.js",handleJS4File);
  server.on("/gauge.js",handleJS5File);
  server.on("/gauge-functions.js",handleJS6File);

  //handle image files
  server.on("/power.jpg",handleJPG1);
  server.on("/temp.jpg",handleJPG2);
  server.on("/refrig.jpg",handleJPG3);
  server.on("/vrd.jpg",handleJPG4);
  server.on("/gas.jpg",handleJPG5);
  server.on("/water.jpg",handleJPG6);
  server.on("/tighf.jpg",handleJPG7);
  server.on("/liftig.jpg",handleJPG8);
  server.on("/mma.jpg",handleJPG9);
  server.on("/pulse.jpg",handleJPG10);
  server.on("/2t.jpg",handleJPG11);
  server.on("/4t.jpg",handleJPG12);
  server.on("/spot.jpg",handleJPG13);
  server.on("/graph.jpg",handleJPG14);
    
  // handle CSS files
  server.on("/pure-min.css",handleCSS1file);
  server.on("/side-menu.css",handleCSS2file);
  server.on("/grids-responsive-min.css",handleCSS3file);
  
  // list available files
  server.on("/list", HTTP_GET, handleFileList);
  // handle file upload
  server.on("/upload", HTTP_POST, [](){
    server.send(200, "text/plain", "{\"success\":1}");
  }, handleFileUpload);

  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

}

void loop()
{
 webSocket.loop();    //websocket server handling
 server.handleClient();   //wifi server handling
 data_SM();   //UART state machine 
}


// Update file handling functions for the ESP32

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //Serial.print("handleFileUpload Data: "); Serial.println(upload.currentSize);
    if (fsUploadFile) {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
    }
    Serial.print("handleFileUpload Size: "); 
    Serial.println(upload.totalSize);
  }
}

void handleIndexFile()
{
  File file = SPIFFS.open("/index.html","r");
  server.streamFile(file, "text/html");
  file.close();
}

//Handle JavaScript files
void handleJS2File()
{
  File js = SPIFFS.open("/payloadHandler.js","r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS3File()
{
  File js = SPIFFS.open("/websocket.js","r");
  server.streamFile(js, "text/javascript");
  js.close();
}
void handleJS4File()
{
  File js = SPIFFS.open("/ui.js","r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS5File()
{
  File js = SPIFFS.open("/gauge.js","r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS6File()
{
  File js = SPIFFS.open("/gauge-functions.js","r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJPG1()
{
  File jpg = SPIFFS.open("/power.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG2()
{
  File jpg = SPIFFS.open("/temp.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG3()
{
  File jpg = SPIFFS.open("/refrig.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG4()
{
  File jpg = SPIFFS.open("/vrd.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG5()
{
  File jpg = SPIFFS.open("/gas.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG6()
{
  File jpg = SPIFFS.open("/water.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG7()
{
  File jpg = SPIFFS.open("/tighf.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG8()
{
  File jpg = SPIFFS.open("/liftig.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG9()
{
  File jpg = SPIFFS.open("/mma.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG10()
{
  File jpg = SPIFFS.open("/pulse.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG11()
{
  File jpg = SPIFFS.open("/2t.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG12()
{
  File jpg = SPIFFS.open("/4t.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}

void handleJPG13()
{
  File jpg = SPIFFS.open("/spot.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}
void handleJPG14()
{
  File jpg = SPIFFS.open("/graph.jpg","r");
  server.streamFile(jpg,"image/jpg");
  jpg.close();
}

void handleCSS1file()
{
  File css = SPIFFS.open("/pure-min.css","r");
  server.streamFile(css, "text/css");
  css.close();
}
void handleCSS2file()
{
  File css = SPIFFS.open("/side-menu.css","r");
  server.streamFile(css, "text/css");
  css.close();
}
void handleCSS3file()
{
  File css = SPIFFS.open("/grids-responsive-min.css","r");
  server.streamFile(css, "text/css");
  css.close();
}

void handleFileList() {
  if (!server.hasArg("dir")) {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server.arg("dir");
  Serial.println("handleFileList: " + path);


  File root = SPIFFS.open(path);
  path = String();

  String output = "[";
  if(root.isDirectory()){
      File file = root.openNextFile();
      while(file){
          if (output != "[") {
            output += ',';
          }
          output += "{\"type\":\"";
          output += (file.isDirectory()) ? "dir" : "file";
          output += "\",\"name\":\"";
          output += String(file.name()).substring(1);
          output += "\"}";
          file = root.openNextFile();
      }
  }
  output += "]";
  server.send(200, "text/json", output);
}


bool exists(String path){
  bool yes = false;
  File file = SPIFFS.open(path, "r");
  if(!file.isDirectory()){
    yes = true;
  }
  file.close();
  return yes;
}


void data_SM(void){
  
  switch(data_state_s){
    
    case WaitingStartByte:    //Waits for start byte
      checksum_calc = 0;    
      
      if (Serial2.available() > 0) {   
        incomingByte = Serial2.read();
        if(incomingByte == 170){      //If received byte is startbyte
          data_state_s = Framelength;   //Goes to next State
          
        }
      }
      break;

    case Framelength:
    
      if (Serial2.available() > 0) {
        length_data = Serial2.read();    //Stores Frame Length Value
        data_state_s = Payload;         //Goes to next State
        
      }
      
      break;
      
    case Payload:
      
      if (Serial2.available() > 0) {
                
         bufferpayload[pos] = Serial2.read();    //reads byte of payload to buffer
         
         checksum_calc += bufferpayload[pos];   //calculate checksum
         
        if(pos == (length_data-1)){   //Last value of frame 
          pos=0;                      //Puts position back to zero
          data_state_s = CheckSum;    //Goes to next state
        }
        else{
          pos++;                      //If its not last value of frame
          data_state_s = Payload;     //Goes to payload again
        }
      }
      

      break;
      
    case CheckSum:
        if (Serial2.available() > 0) {
          checksum_recv = Serial2.read();    //Receives checksum from uart       
        }
        
       
        if(checksum_recv == checksum_calc){   //If received checksum = calculated checksum
          handlepayload();                    //Valid Payload 
          Serial2.write(0xAB);                 //Send ACK Byte
          
          /*  
          if(p==10){  //send 9 correct ack and 1 incorrect, just for TEST
            Serial.write(0xAC); //Send ack
            p=0;
          }
          else{
            Serial.write(0xAB); //Send ack
            p++;
          }
          */
          data_state_s = WaitingStartByte;
        }
        
        else{
          Serial2.write(0xAC);     //If received checksum != calculated checksum send wrong ACK
          data_state_s = WaitingStartByte;    //Back to waiting for inital frame
        }
        
      break;
      
    default:
      data_state_s = WaitingStartByte;
      break;
  }
}

void handlepayload(void){
  
String output = "{";                    //JSON format
int i = 0;    
                                                                                                                                                                                                                                                                        
  while(i<length_data){                //Percorre o buffer todo
    value_int = 0;
    
    id = bufferpayload[i];
    output += "\"";
    output += id;
    output += "\":";
     
    i++;
    length_value = bufferpayload[i];
    
    i++;
    k=i;
    
    while(k<(i+length_value)){
      
      if(v==0 && length_value > 1){               //if length_value > 1
        value_int = (int)(bufferpayload[k]*256);  //only supports 1 or 2 byte payload
        
        v++;
      }
      else{
        value_int += (int)(bufferpayload[k]);
      }
      k++;
    }
    v=0;
    
    output += "\"";
    output += value_int;
    output += "\"";
    i=k;
    
      if(i != length_data){ // Puts comma but on last 
      output += ",";  
      }
  }
    output += "}";  
    Serial.print(output);
    webSocket.broadcastTXT(output);   //sends through websocket
  
}
