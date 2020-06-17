// Includes
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>

#define RXD2 16
#define TXD2 17

//Global variables
unsigned char incomingByte, length_data, checksum_recv, checksum_calc = 0, id, length_value, value;
unsigned char bufferpayload[128];
int pos = 0, j = 0, k = 0, p = 0, value_int = 0, v = 0, conn = 0,ackFlag = 0,askForValues=0,receiveConfig=0;

//UART StateMachine states
typedef enum {WaitingStartByte, Framelength, Payload, CheckSum, Value} state_machine_t;
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
  switch (type) {

    // Client has disconnected
    case WStype_DISCONNECTED:{
      Serial.printf("[%u] Disconnected!\n", num);
      conn = 0;
    }
      break;

    // New client has connected
    case WStype_CONNECTED:{
  
        IPAddress ip = webSocket.remoteIP(num);
        //Serial.printf("[%u] Connection from ", num);
        //Serial.println(ip.toString());
        
        Serial.printf("Pedi valores");
        askConfigFiles();
        askForValues = 1;
        data_SM(); 
        conn = 1; 
    }       
        break;

    // Echo text message back to client
    case WStype_TEXT:
      //Serial.printf("[%u] Text: %s\n", num, payload);
      //Serial2.write(0xAC);                 //Send ACK Byte

      //webSocket.sendTXT(num, payload);
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
  
 Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  // Start access point
  /*
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.softAP(ssid, password);
  WiFi.setSleep(false);
  WiFi.mode(WIFI_AP_STA);
  */
  WiFi.enableAP(true);
  delay(100);
  WiFi.softAP(ssid, password);
  delay(500); // Without delay the IP address is sometimes blank
    


  // Print our IP address
  Serial.println();
  Serial.println("AP running");
  Serial.print("My IP address: ");
  Serial.println(WiFi.softAPIP());

  //handle html files
  server.on("/", handleIndexFile);

  // handle JavaScript files
  server.on("/payloadHandler.js", handleJS2File);
  server.on("/websocket.js", handleJS3File);
  server.on("/ui.js", handleJS4File);
  server.on("/gauge.js", handleJS5File);
  server.on("/gauge-functions.js", handleJS6File);

  //handle image files
  server.on("/power.jpg", handleJPG1);
  server.on("/temp.jpg", handleJPG2);
  server.on("/refrig.jpg", handleJPG3);
  server.on("/vrd.jpg", handleJPG4);
  server.on("/gas.jpg", handleJPG5);
  server.on("/water.jpg", handleJPG6);
  server.on("/tighf.jpg", handleJPG7);
  server.on("/liftig.jpg", handleJPG8);
  server.on("/mma.jpg", handleJPG9);
  server.on("/pulse.jpg", handleJPG10);
  server.on("/2t.jpg", handleJPG11);
  server.on("/4t.jpg", handleJPG12);
  server.on("/spot.jpg", handleJPG13);
  server.on("/graph.jpg", handleJPG14);
  server.on("/pregas.jpg", handleJPG15);
  server.on("/istart.jpg", handleJPG16);
  server.on("/upslope.jpg", handleJPG17);
  server.on("/ip.jpg", handleJPG18);
  server.on("/ib.jpg", handleJPG19);
  server.on("/downslope.jpg", handleJPG20);
  server.on("/ifinal.jpg", handleJPG21);
  server.on("/postgas.jpg", handleJPG22);

  // handle CSS files
  server.on("/pure-min.css", handleCSS1file);
  server.on("/side-menu.css", handleCSS2file);
  server.on("/grids-responsive-min.css", handleCSS3file);

  // list available files
  server.on("/list", HTTP_GET, handleFileList);
  
  // handle file upload
  server.on("/upload", HTTP_POST, []() {
    server.send(200, "text/plain", "{\"success\":1}");
  }, handleFileUpload);


  server.begin();
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

}

void loop()
{
  webSocket.loop();    //websocket server handler
  server.handleClient();   //wifi server handler

  if (conn == 1) {
    data_SM();   //UART state machine
  }
}


// Update file handling functions for the ESP32

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    //Serial.print("handleFileUpload Name: "); Serial.println(filename);
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
    //Serial.print("handleFileUpload Size: ");
    //Serial.println(upload.totalSize);
  }
}

void handleIndexFile()
{
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//Handle JavaScript files
void handleJS2File()
{
  File js = SPIFFS.open("/payloadHandler.js", "r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS3File()
{
  File js = SPIFFS.open("/websocket.js", "r");
  server.streamFile(js, "text/javascript");
  js.close();
}
void handleJS4File()
{
  File js = SPIFFS.open("/ui.js", "r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS5File()
{
  File js = SPIFFS.open("/gauge.js", "r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJS6File()
{
  File js = SPIFFS.open("/gauge-functions.js", "r");
  server.streamFile(js, "text/javascript");
  js.close();
}

void handleJPG1()
{
  File jpg = SPIFFS.open("/power.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG2()
{
  File jpg = SPIFFS.open("/temp.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG3()
{
  File jpg = SPIFFS.open("/refrig.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG4()
{
  File jpg = SPIFFS.open("/vrd.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG5()
{
  File jpg = SPIFFS.open("/gas.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG6()
{
  File jpg = SPIFFS.open("/water.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG7()
{
  File jpg = SPIFFS.open("/tighf.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG8()
{
  File jpg = SPIFFS.open("/liftig.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG9()
{
  File jpg = SPIFFS.open("/mma.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG10()
{
  File jpg = SPIFFS.open("/pulse.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG11()
{
  File jpg = SPIFFS.open("/2t.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG12()
{
  File jpg = SPIFFS.open("/4t.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}

void handleJPG13()
{
  File jpg = SPIFFS.open("/spot.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG14()
{
  File jpg = SPIFFS.open("/graph.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}

void handleJPG15()
{
  File jpg = SPIFFS.open("/pregas.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG16()
{
  File jpg = SPIFFS.open("/istart.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG17()
{
  File jpg = SPIFFS.open("/upslope.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG18()
{
  File jpg = SPIFFS.open("/ip.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG19()
{
  File jpg = SPIFFS.open("/ib.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG20()
{
  File jpg = SPIFFS.open("/downslope.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG21()
{
  File jpg = SPIFFS.open("/ifinal.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleJPG22()
{
  File jpg = SPIFFS.open("/postgas.jpg", "r");
  server.streamFile(jpg, "image/jpg");
  jpg.close();
}
void handleCSS1file()
{
  File css = SPIFFS.open("/pure-min.css", "r");
  server.streamFile(css, "text/css");
  css.close();
}
void handleCSS2file()
{
  File css = SPIFFS.open("/side-menu.css", "r");
  server.streamFile(css, "text/css");
  css.close();
}
void handleCSS3file()
{
  File css = SPIFFS.open("/grids-responsive-min.css", "r");
  server.streamFile(css, "text/css");
  css.close();
}

void handleFileList() {
  if (!server.hasArg("dir")) {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server.arg("dir");
  //Serial.println("handleFileList: " + path);


  File root = SPIFFS.open(path);
  path = String();

  String output = "[";
  if (root.isDirectory()) {
    File file = root.openNextFile();
    while (file) {
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


bool exists(String path) {
  bool yes = false;
  File file = SPIFFS.open(path, "r");
  if (!file.isDirectory()) {
    yes = true;
  }
  file.close();
  return yes;
}


void data_SM(void) {

  switch (data_state_s) {

    case WaitingStartByte:    //Waits for start byte
      checksum_calc = 0;

      if (Serial2.available() > 0) {
        incomingByte = Serial2.read();
        //Serial.println(incomingByte);
        if (incomingByte == 170) {    //If received byte is startbyte
          data_state_s = Framelength;   //Goes to next State

        }
      }
      break;

    case Framelength:

      if (Serial2.available() > 0) {
        length_data = Serial2.read();    //Stores Frame Length Value
        //Serial.println(length_data);
        data_state_s = Payload;         //Goes to next State

      }

      break;

    case Payload:

      if (Serial2.available() > 0) {

        bufferpayload[pos] = Serial2.read();    //reads byte of payload to buffer
        //Serial.println(bufferpayload[pos]);
        checksum_calc += bufferpayload[pos];   //calculate checksum

        if (pos == (length_data - 1)) { //Last value of frame
          pos = 0;                    //Puts position back to zero
          data_state_s = CheckSum;    //Goes to next state
        }
        else {
          pos++;                      //If its not last value of frame
          data_state_s = Payload;     //Goes to payload again
        }
      }


      break;

    case CheckSum:
      //Serial.println("checksum state");
      if (Serial2.available() > 0) {
        checksum_recv = Serial2.read();    //Receives checksum from uart.
      }


      if (checksum_recv == checksum_calc) { //If received checksum = calculated checksum
        handlepayload();                    //Valid Payload
        sendValidACK();
        Serial.printf("Recebi bue bem");
        data_state_s = WaitingStartByte;
      }

      else {
        sendNotValidACK();     //If received checksum != calculated checksum send wrong ACK
        Serial.printf("Recebi bue mal");
        data_state_s = WaitingStartByte;    //Back to waiting for inital frame
      }

      break;

    default:
      data_state_s = WaitingStartByte;
      break;
  }
}

void handlepayload(void) {

  String output = "{";                    //JSON format
  int i = 0;

  while (i < length_data) {            //Percorre o buffer todo
    value_int = 0;

    id = bufferpayload[i];

    if((id >=1 && id <= 22)){
      receiveConfig = 1;
    }
    

    
    output += "\"";
    output += id;
    output += "\":";
  
    i++;
    length_value = bufferpayload[i];

    i++;
    k = i;

    while (k < (i + length_value)) {

      if (v == 0 && length_value > 1) {           //if length_value > 1
        value_int = (int)(bufferpayload[k] * 256); //only supports 1 or 2 byte payload

        v++;
      }
      else {
        value_int += (int)(bufferpayload[k]);
      }
      k++;
    }
    v = 0;

    output += "\"";
    output += value_int;
    output += "\"";
    i = k;

    if (i != length_data) { // Puts comma but on last
      output += ",";
    }
  }
  output += "}";



  if(receiveConfig == 1 && askForValues == 1){
    sendValidACK();
    receiveConfig = 0;
    askForValues = 0;
  }
  
  webSocket.broadcastTXT(output);   //sends through websocket        
   
  
}

void askConfigFiles(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x01);
  Serial2.write(0x01);
  Serial2.write(0x01);
  
  Serial2.write(0x03);
}

void sendValidACK(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x02);
  Serial2.write(0x01);
  Serial2.write(0x01);
  
  Serial2.write(0x04);
}

void sendNotValidACK(void){
  Serial2.write(0xAA);
  Serial2.write(0x03);
  
  Serial2.write(0x02);
  Serial2.write(0x01);
  Serial2.write(0x00);
  
  Serial2.write(0x03);
}
