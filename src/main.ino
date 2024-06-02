#include <WiFi.h>
#include "file.h"
#include "camera.h"
#include "lapse.h"
#include "configs.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void startCameraServer();

void setup()
{
	delay(1000);
	Serial.begin(115200);
	// Serial.setDebugOutput(true);
	Serial.println();
	Serial.println("STARTING UP");
	initFileSystem();
	initCamera();

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	startCameraServer();
	Serial.print("Camera Ready! Use 'http://");
	Serial.print(WiFi.localIP());
	Serial.println("' to connect");
}

void loop()
{
	unsigned long t = millis();
	static unsigned long ot = 0;
	unsigned long dt = t - ot;
	ot = t;
	processLapse(dt);
	delay(1000);
}
