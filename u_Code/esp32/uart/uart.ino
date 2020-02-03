/*
 * For test purpose only
 * Final version is on webserver project
 */
unsigned char incomingByte,length_data,checksum_recv,checksum_calc = 0,id,length_value,value; // variável
unsigned char bufferpayload[64];
int pos=0,j=0,k=0;

typedef enum {WaitingStartByte,Framelength,Payload,CheckSum,Value} state_machine_t;
state_machine_t data_state_s;

void data_SM(void){

  switch(data_state_s){
    
    case WaitingStartByte:
      checksum_calc = 0;
      
      if (Serial.available() > 0) {
        incomingByte == Serial.read();
        if(incomingByte = 170){
          data_state_s = Framelength;
        }
      }
      break;

    case Framelength:
      if (Serial.available() > 0) {
        length_data = Serial.read();
        data_state_s = Payload;
      }
      
      break;
      
    case Payload:
      
      if (Serial.available() > 0) {
                
         bufferpayload[pos] = Serial.read();  //reads payload to buffer
         
         checksum_calc += bufferpayload[pos]; //calculate checksum
         
        if(pos == (length_data-1)){
          pos=0;
          data_state_s = CheckSum;
        }
        else{
          pos++;
          data_state_s = Payload;
        }
      }
      

      break;
      
    case CheckSum:
        if (Serial.available() > 0) {
          checksum_recv = Serial.read();
          
        }

       
        if(checksum_recv == checksum_calc){   //payload correto
          handlepayload();
          data_state_s = WaitingStartByte;  
        }
        
        else{
          Serial.print("recebido:");
          Serial.println(checksum_recv);
          Serial.print("recebido:");
          Serial.println(checksum_calc);
          Serial.println("checksum não correto");
          data_state_s = WaitingStartByte;  
        }
        
      break;
      
    default:
      break;
  }
}

void handlepayload(void){
String output = "{";
int i = 0;    
                                                                                                                                                                                                                                                                        
  while(i<length_data){                //Percorre o buffer todo
    value = 0;
    id = bufferpayload[i];
    output += "\"";
    output += id;
    output += "\":";
     
    i++;
    length_value = bufferpayload[i];
    i++;
    k=i;
    while(k<(i+length_value)){
      value += bufferpayload[k];
      k++;      
    }
    
    output += "\"";
    output += value;
    output += "\"";
    i=k;
    
    if(i != length_data){
    output += ",";  
    }
  }
    output += "}";
    Serial.println(output);
}
