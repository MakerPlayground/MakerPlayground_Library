#include "MP_DS18B20.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define REFRESH_INTERVAL 100
#define TEMPERATURE_PRECISION 9

MP_DS18B20::MP_DS18B20(uint8_t pin)
    : wire(OneWire(pin))
    , sensors(DallasTemperature(&wire))
{

}

int MP_DS18B20::init() 
{
    sensors.begin();
    numberOfDevices = sensors.getDeviceCount();
    if (numberOfDevices < 1) {
        return ERR_CONNECT_DEVICE;
    }
    // for(int i=0;i<numberOfDevices; i++) {
    //     if(sensors.getAddress(tempDeviceAddress, i)) {
    //         sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
    //     }
    // }

    /* We support only one device. */
    if(sensors.getAddress(tempDeviceAddress, 0)) {
        sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
    } else {
        // Found ghost device
        return ERR_CONFIG_DEVICE;
    }
    return ERR_OK;
}

void MP_DS18B20::update(unsigned long current_time) {
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        sensors.requestTemperatures();
        temperature = sensors.getTempC(tempDeviceAddress);
        lastMillis = current_time;
    }
}

void MP_DS18B20::printStatus() {
    Serial.print(F("Temperature = "));
    Serial.print(temperature);
    Serial.print(F(" celcius"));
}

double MP_DS18B20::getTemperature() {
    return temperature;
}



// // Data wire is plugged into port 2 on the Arduino
// #define ONE_WIRE_BUS 16
// #define TEMPERATURE_PRECISION 9 // Lower resolution

// // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// OneWire oneWire(ONE_WIRE_BUS);

// // Pass our oneWire reference to Dallas Temperature. 
// DallasTemperature sensors(&oneWire);

// int numberOfDevices; // Number of temperature devices found

// DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address


// // function to print a device address
// void printAddress(DeviceAddress deviceAddress)
// {
//   for (uint8_t i = 0; i < 8; i++)
//   {
//     if (deviceAddress[i] < 16) Serial.print("0");
//     Serial.print(deviceAddress[i], HEX);
//   }
// }


// void setup(void)
// {
//   // start serial port
//   Serial.begin(9600);
//   Serial.println("Dallas Temperature IC Control Library Demo");

//   // Start up the library
//   sensors.begin();
  
//   // Grab a count of devices on the wire
//   numberOfDevices = sensors.getDeviceCount();
  
//   // locate devices on the bus
//   Serial.print("Locating devices...");
  
//   Serial.print("Found ");
//   Serial.print(numberOfDevices, DEC);
//   Serial.println(" devices.");

//   // report parasite power requirements
//   Serial.print("Parasite power is: "); 
//   if (sensors.isParasitePowerMode()) Serial.println("ON");
//   else Serial.println("OFF");
  
//   // Loop through each device, print out address
//   for(int i=0;i<numberOfDevices; i++)
//   {
//     // Search the wire for address
//     if(sensors.getAddress(tempDeviceAddress, i))
// 	{
// 		Serial.print("Found device ");
// 		Serial.print(i, DEC);
// 		Serial.print(" with address: ");
// 		printAddress(tempDeviceAddress);
// 		Serial.println();
		
// 		Serial.print("Setting resolution to ");
// 		Serial.println(TEMPERATURE_PRECISION, DEC);
		
// 		// set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
// 		sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
		
// 		 Serial.print("Resolution actually set to: ");
// 		Serial.print(sensors.getResolution(tempDeviceAddress), DEC); 
// 		Serial.println();
// 	}else{
// 		Serial.print("Found ghost device at ");
// 		Serial.print(i, DEC);
// 		Serial.print(" but could not detect address. Check power and cabling");
// 	}
//   }

// }

// // function to print the temperature for a device
// void printTemperature(DeviceAddress deviceAddress)
// {
//   // method 1 - slower
//   //Serial.print("Temp C: ");
//   //Serial.print(sensors.getTempC(deviceAddress));
//   //Serial.print(" Temp F: ");
//   //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

//   // method 2 - faster
//   float tempC = sensors.getTempC(deviceAddress);
//   Serial.print("Temp C: ");
//   Serial.print(tempC);
//   Serial.print(" Temp F: ");
//   Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
// }

// void loop(void)
// { 
//   // call sensors.requestTemperatures() to issue a global temperature 
//   // request to all devices on the bus
//   Serial.print("Requesting temperatures...");
//   sensors.requestTemperatures(); // Send the command to get temperatures
//   Serial.println("DONE");
  
  
//   // Loop through each device, print out temperature data
//   for(int i=0;i<numberOfDevices; i++)
//   {
//     // Search the wire for address
//     if(sensors.getAddress(tempDeviceAddress, i))
// 	{
// 		// Output the device ID
// 		Serial.print("Temperature for device: ");
// 		Serial.println(i,DEC);
		
// 		// It responds almost immediately. Let's print out the data
// 		printTemperature(tempDeviceAddress); // Use a simple function to print out the data
// 	} 
// 	//else ghost device! Check your power requirements and cabling
	
//   }
//   delay(100);
// }
