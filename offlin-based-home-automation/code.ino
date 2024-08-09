/*
MIT License

Copyright (c) 2024 Arghyadeep Debnath

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Gateway: http://192.168.4.1
LED PIN GPIO18, GPIO19;
*/

#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "OFFLINK";
const char *password = "INVENTOAIOFFLINK";

WebServer server(80);

const int ledPin18 = 18; // GPIO18 pin G18
const int ledPin19 = 19; // GPIO19 pin G19
bool ledState18 = LOW;
bool ledState19 = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin18, OUTPUT);
  digitalWrite(ledPin18, ledState18);

  pinMode(ledPin19, OUTPUT);
  digitalWrite(ledPin19, ledState19);

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, []() {
    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; text-align: center; margin-top: 50px; }";
    html += "h1 { color: #333; }";
    html += "form { margin-top: 20px; }";
    html += "input[type=submit] { background-color: #4CAF50; color: white; padding: 10px 15px; font-size: 16px; cursor: pointer; }";
    html += "@media only screen and (max-width: 600px) { body { margin-top: 20px; } }";
    html += "</style></head><body>";
    html += "<h1>InventoAi 2.4G Controller</h1>";
    html += "<p>LED State GPIO18: " + String(ledState18 ? "ON" : "OFF") + "</p>";
    html += "<form action='/on18' method='get'><input type='submit' value='Turn On GPIO18'></form>";
    html += "<form action='/off18' method='get'><input type='submit' value='Turn Off GPIO18'></form>";
    html += "<p>LED State GPIO19: " + String(ledState19 ? "ON" : "OFF") + "</p>";
    html += "<form action='/on19' method='get'><input type='submit' value='Turn On GPIO19'></form>";
    html += "<form action='/off19' method='get'><input type='submit' value='Turn Off GPIO19'></form>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/on18", HTTP_GET, []() {
    ledState18 = HIGH;
    digitalWrite(ledPin18, ledState18);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/off18", HTTP_GET, []() {
    ledState18 = LOW;
    digitalWrite(ledPin18, ledState18);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/on19", HTTP_GET, []() {
    ledState19 = HIGH;
    digitalWrite(ledPin19, ledState19);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/off19", HTTP_GET, []() {
    ledState19 = LOW;
    digitalWrite(ledPin19, ledState19);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
