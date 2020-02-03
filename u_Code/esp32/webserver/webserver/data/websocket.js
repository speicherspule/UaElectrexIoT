var url = "ws://192.168.4.1:81/";

 
// This is called when the page finishes loading
function init_websocket() {
    
    // Connect to WebSocket server
    wsConnect(url);
}
 
// Call this to connect to the WebSocket server
function wsConnect(url) {
    
    // Connect to WebSocket server
    websocket = new WebSocket(url);
    
    // Assign callbacks
    websocket.onopen = function(evt) { onOpen(evt) };
    websocket.onclose = function(evt) { onClose(evt) };
    websocket.onmessage = function(evt) { onMessage(evt) };
    websocket.onerror = function(evt) { onError(evt) };
}
 
// Called when a WebSocket connection is established with the server
function onOpen(evt) {
    // Log connection state
    console.log("Connected");
}
 
// Called when the WebSocket connection is closed
function onClose(evt) {
 
    // Log disconnection state
    console.log("Disconnected");
    
    // Try to reconnect after a few seconds
    setTimeout(function() { wsConnect(url) }, 2000);
}
 
// Called when a message is received from the server
function onMessage(evt) {
    // Print out our received message

    var obj = JSON.parse(evt.data)
    console.log(evt.data)
    addValueTension(new Date().getTime(),obj["27"])
    addValueCurrent(new Date().getTime(),obj["28"])
    gauge_tension.set(obj["27"]); // set actual value
    gauge_current.set(obj["28"]); // set actual value

    gauge_tension.setTextField(document.getElementById("text_tension"));
    gauge_current.setTextField(document.getElementById("text_current"));


    //console.log("Received: " + evt.data);

}
 
// Called when a WebSocket error occurs
function onError(evt) {
    console.log("ERROR: " + evt.data);
}
 
// Sends a message to the server (and prints it to the console)
function doSend(message) {
    console.log("Sending: " + message);
    websocket.send(message);
}
 
// Call the init function as soon as the page loads
window.addEventListener("load", init_websocket, false);
