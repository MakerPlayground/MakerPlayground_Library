# **Device Schema**

The device schema is the definition of the device/hardware in [MakerPlayground](https://www.makerplayground.io/) software. It is a document-based data structure that is directly applied to *device.yaml* file.

## **Table of Contents**

- [**Device Schema**](#device-schema)
  - [**Table of Contents**](#table-of-contents)
  - [**Schemas**](#schemas)
    - [**Device Object**](#device-object)
    - [**Cloud Platform Mapping Object**](#cloud-platform-mapping-object)
    - [**Connection Object**](#connection-object)
    - [**Pin Object**](#pin-object)
    - [**Compatibility Object**](#compatibility-object)
    - [**Action/Condition Object**](#actioncondition-object)
    - [**Parameter/Value Object**](#parametervalue-object)
    - [**Platform Mapping Object**](#platform-mapping-object)
    - [**Constraint Object**](#constraint-object)
    - [**Property Object**](#property-object)
    - [**Integrated Device Object**](#integrated-device-object)
    - [**Connection Mapping Object**](#connection-mapping-object)
  - [**Enum Definitions**](#enum-definitions)
    - [**Device Types**](#device-types)
    - [**Platforms**](#platforms)
    - [**Cloud Platforms**](#cloud-platforms)
    - [**Pin Functions**](#pin-functions)
    - [**Port Types**](#port-types)
    - [**Voltage Level**](#voltage-level)
    - [**Generic Devices**](#generic-devices)
    - [**Units**](#units)
    - [**Data Types**](#data-types)
    - [**Control Types**](#control-types)

---

## **Schemas**

### **Device Object**

The device object is the root of the supported device/hardware definition. It is an embbed structure consisting of many properties. Some properties might be a string, number, or array. Some properties could be an other object.

The properties of the device object are defined as follows

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|id|Unique identifier of the device. (It is usually a concatenation of device provider, dash symbol, and the unique id given by device provider)|string|Yes|Adafruit-xxx, Grove-xxxxxxxxx|
|brand|Name of the device owner or provider|string|Yes|Adafruit, SeeedStudio|
|model|Device-specific description such as IC, module name, color|string|Yes|Tactile Switch Button|
|url|Link to device description given by device owner or provider|string|Yes|https://www.adafruit.com/product/1119|
|type|[Type](#device-types) of the device|enum|Yes|MODULE, CONTROLLER, VIRTUAL, INTEGRATED, SHIELD|
|width|Device width in pixel unit. (1 inch = 144 pixels)|number|Yes|120.0|
|height|Device height in pixel unit. (1 inch = 144 pixels)|number|Yes|80.0|
|need_breadboard|Indicate whether breadboard is required when using the device. This property is false by default.|boolean|No|true, false|
|pio_boardid|[Platform IO's board](https://docs.platformio.org/en/latest/projectconf/section_env_board.html#board) for controller device|string|No|uno, atmega328pb, nodemcuv2, esp32dev, m5stack-fire, nodemcu-32s, espino32
|cloud_consume|Name of [Cloud Platform](#cloud-platforms) that the device needs. Normally, the device that has cloud_consume is the cloud device such as virtual LED, button, and gauge|enum|No|BLYNK, NETPIE|
|cloud_provide|Array of the [Cloud Platform Mapping Object](#cloud-platform-mapping-object) that defines the cloud platforms and its code implementation. This property introduces the usable cloud platforms to all devices in the MakerPlayground project.|array|No|-|
|pin_template|Name of the pin template file (without extension) that the device is relied on|string|Yes|ATMEGA328, I2C_3v3, DIGITAL_IN_5V|
|connection_consume|Array of [Connection Object](#connection-object) (the ports appeared on the device). MakerPlayground will completely map them to the available ports of the controller or other devices. The order of the item in the array is belonged to the constructure of implementation class.|array|No|-
|connection_provide|Array of [Connection Object](#connection-object) (the ports appeared on the device). In MakerPlayground, these ports will supply their functions to other device or module.|array|No|-
|compatibility|Array of [Compatibility Object](#compatibility-object) that defines the device features and limitations.|array|Yes|-|
|platforms|Array of [Platform Mapping Object](#platform-mapping-object) that defines the supporting development platform and the implementation of the device.|array|Yes|-|
|property|Array of [Property Object](#property-object) that defines the software-configurable device-specific properties.|array|No|-|
|integrated_devices|Array of [Integrated Device Object](#integrated-device-object) that defines the built-in devices integrated in this device.|array|No|-|

### **Cloud Platform Mapping Object**

The mapping of the supporting cloud platform to the implementation class and its library dependency.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|cloud_platform|Name of supporting [Cloud Platform](#cloud-platforms)|string|Yes|BLYNK
|classname|Name of the file (without extension) and the implementation class|string|Yes|MP_BLYNK_NODEMCU|
|library_dependency|Array of directory that the source files must be included in building process|array|Yes|["blynkkk/blynk-library"]

### **Connection Object**

The port that is physically displayed on the device. A port could have one or more pins.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|name|Unique name of the port that is displayed on device|string|Yes|D1, D2, A3, A4, I2C|
|type|Name of the [Port Type](#port-types)|enum|Yes|GROVE|
|pins|Array of [Pin Object](#pin-object). The pin order is defined in [Port Type](#port-types) section and belonged to the constructure of the implementation class.|array|Yes|[GND, VCC, D2, D1]|

### **Pin Object**

The definition of the pin that is physically appeared on the device. It might be a pin header, pin hole, or pin that is sealed by the port. The pin is normally inherited from the pin in the pin_template defining in the [Device Object](#device-object) section. The defined pin is able to be connected by or to the pin in other devices.

In some board, the multiple pins are referenced to the same point in the circuit. Those pins will inherited from the same pin of the pin template.

The function and voltage level of the pin are also inherited from referencing pin. However, you can overwrite the default function and/or voltage_level by defining those properties. This is the scenario when user wants to limit the pin functions such as A4 and A5 pins in Arduino UNO which are appropiate for ANALOG but not for I2C connection. Another example is a pin of the device that has a built-in level shifter circuit.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|ref_to|Name of the referenced pin in the pin_template|string|Yes|PB0, PB1, PC0, PC1
|x|X position in pixel unit|number|Yes|60.0|
|y|Y position in pixel unit|number|Yes|40.0|
|function|[Pin Function](#pin-functions) or the array of them that will overwrite the default functions|enum|No|VCC, GND, DIGITAL_IN, DIGITAL_OUT|
|voltage_level|[Voltage Level](#voltage-level) that could overwrite the default voltage_level of pin|enum|No|LEVEL_3v3, LEVEL_5, LEVEL_3v3_5, LEVEL_1|

### **Compatibility Object**

The mapping of the generic device name to action, condition, and value. It indicates the supporting features and the limitation of the device. For example, HC-04 could be used as "Distance" sensor. It supports the condition "Compare" value and it provides the value "Distance".

The properties of the compatibility is as follow.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|name|[Generic Device](#generic-devices) name|string|Yes|LED, Button, Accelerometer
|action|Array of supported [actions](#actioncondition-object)|array|No*|-|
|condition|Array of supported [conditions](#actioncondition-object)|array|No*|-|
|value|Array of supported [values](#parametervalue-object)|array|No*|-|

(*) At least one of action, condition and value must be defined.

### **Action/Condition Object**

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|name|Name of the action or condition belonged to the [Generic Device](#generic-devices)|string|Yes|On, Off, Press, Not press, Compare|
|parameter|Array of action or condition [parameters](#parametervalue-object) based on the hardware|array|No|-|

### **Parameter/Value Object**

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|name|Name of parameter that belonged to the action/condition<br>or<br>Name of the value that belonged to the generic device|string|Yes|Percent, Temperature<br>or<br>Brightness<br>[(see more detail)](https://github.com/InGarage/MakerPlayGround/tree/master/src/main/resources/json)|
|constraint|[Constraint](#constraint-object) of the parameter or value that is limited by the hardware.|object|*|-|

(*) For value object, constraint is a required property. For parameter object, constraint is not a required property.

### **Platform Mapping Object**

The mapping of the supporting cloud platform to its implementation.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|platform|Name of development [Platform](#platforms)|string|Yes|ARDUINO_ESP8266
|classname|Name of the sourcecode file without extension in the lib directory (./lib/xxx/) which is the same name to the implementation's class|string|Yes|MP_BLYNK_NODEMCU|
|library_dependency|Array of external libraries (availible in ./lib_ext/) that must be included for the compiling or running process|array|Yes|["blynkkk/blynk-library"]

### **Constraint Object**

Constraint is the limitation of the property or value or parameter that defines in the device spec or datasheet. The constraint is worked in two different cases.

1. For the property constraint, the defined value is ready-to-use.
2. For the value and parameter constraint, the defined value will be intersected to the default constraint of the corresponding value or parameter before used.

There are two different types of constraint:

- **Categorical Constraint**
  
  The categorical constrint is the set of items that defines the supporting property, value or parameter. You should define it by the array of string.

- **Numerical Constraint**
  
  The numeric constraint is defined by the minimum, maximum, and unit of the value that device is supported. You should define it by the object as follows.

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|min|Minimum possible value|number|Yes|0.0|
|max|Maximum possible value|number|Yes|100.0|
|unit|[Unit](#units) according to the value|enum|Yes|Percent|

### **Property Object**

The software configurable property required by the specific device/hardware. For example,

- virtual pin of Blynk's Virtual Gauge
- Image resolution and Frame rate of the camera
- configurable I2C address of some i2C devices.

The properties of the property object are as follows

| Property | Description | Type | Required | Example |
|----------|-------------|:----:|:--------:|---------|
|name|Name of the property required by the device|string|Yes|"virtual pin"
|constraint|[Constraint Object](#constraint-object) that defines the constraint for the property's value|object|Yes|-
|datatype|[Data Type](#data-types) of the property|enum|Yes|DOUBLE, INTEGER, STRING
|controltype|[Control Type](#control-types) of the property displayed to the user|enum|Yes|TEXTBOX, SPINBOX, DROPDOWN

### **Integrated Device Object**

In some device, it may have the other devices integrated to it such as AX-Wifi board by [Innovative Experiments Co. Ltd.](http://www.inexglobal.com/). You could define the integrated device similar to the [Device Object](#device-object) but some properties are difference.
The available properties are as follows.

| Property | Description | Type | Required |Example|
|----------|-------------|:----:|:--------:|-------|
|name|Name of the integrated device|string|Yes|Integrated LED, Integrated Display|
|property|Array of [Property Object](#property-object) that defines the device-specific configuration.|array|No|-|
|pin_template|Name of the pin template file (without extension) that the integrated device is relied on|string|Yes|DIGITAL_IN_5V|
|integrated_connection|Array of [Connection Mapping Object](#connection-mapping-object) that defines the circuit connection between the integrated and the host device. The order of the item in the array is belonged to the constructure of the class implementation.|array|Yes|-|
|compatibility|Array of [Compatibility Object](#compatibility-object) that defines the device features and limitations.|array|Yes|-|
|platforms|Array of [Platform Mapping Object](#platform-mapping-object) that defines the supporting development platform and the implementation of the device.|array|Yes|-|

### **Connection Mapping Object**

The connection mapping defined the connection between the pin of the device to pin of the hosted device. However, the connection is connected inside the board so the X, Y position is not needed. The object properties are as follows.

| Property | Description | Type | Required |Example|
|----------|-------------|:----:|:--------:|-------|
|ref_to|The pin name in the pin_template of the integrated device|string|Yes|DIGITAL_IN, VCC, GND|
|host_ref_to|The pin name in the pin_template of the host device|string|Yes|AD0, VCC, GND|

---

## **Enum Definitions**

### **Device Types**

The type of the device

- MODULE
- CONTROLLER
- VIRTUAL
- INTEGRATED
- SHIELD

### **Platforms**

The development platform supported in MakerPlayground software

| Platform | Description |
|----------|-------------|
|ARDUINO_AVR8|The arduino development platform for AVR 8 bits such as ATMEGA328P, ATMEGA328PB|
|ARDUINO_ESP8266|The arduino development platform for ESP8266|
|ARDUINO_ESP32|The arduino development platform for ESP32|
|RASPBERRYPI|The python development platform with the raspberrypi built-in libraries|

### **Cloud Platforms**

The cloud platform supported in MakerPlayground software

- BLYNK
- NETPIE
- REST
- AZURE

### **Pin Functions**

The function that the pin is supported. The IN and OUT function is considered by a device-centric way. For example, button has VCC, GND and DIGITAL_OUT.

- VCC
- GND
- SCL
- SDA
- SCL1
- SDA1
- DIGITAL_IN
- DIGITAL_OUT
- ANALOG_IN
- ANALOG_OUT
- PWM_OUT
- PWM_IN
- INTERRUPT_LOW
- INTERRUPT_HIGH
- INTERRUPT_CHANGE
- INTERRUPT_RISING
- INTERRUPT_FALLING
- HW_SERIAL_RX
- HW_SERIAL_TX
- HW_SERIAL_RX1
- HW_SERIAL_TX1
- SW_SERIAL_RX
- SW_SERIAL_TX
- HW_OR_SW_SERIAL_RX
- HW_OR_SW_SERIAL_TX
- MOSI
- MISO
- SCK
- MOSI1
- MISO1
- SCK1
- AREF
- RS485_Negative
- RS485_Positive
- NO_FUNCTION

### **Port Types**

Port type is defined to let the MakerPlayground software calculates the correct device connection

| Port Type | Pins order |
|-----------|-------|
|WIRE|[PIN]|
|GROVE|[GND, VCC, DATA2, DATA1]|
|MAKER_PLAYGROUND|[GND, VCC, DATA2, DATA1]|
|M5STACK|[GND, VCC, DATA2, DATA1]|
|INEX3|[GND, DATA, VCC]|
|CSI|[CSI1, CSI2, CSI3, ..., CSI15]|
|UNO_SHIELD|Not defined yet|

### **Voltage Level**

The supporting voltage level for pin

- LEVEL_3v3_5 : operate on both 3.3 and 5 volts
- LEVEL_3v3 : operate on 3.3 volts only
- LEVEL_5 : operate on 5 volts only
- LEVEL_1 : operate on 1 volt only
- LEVEL_12 : operate on 12 volt only

### **Generic Devices**

The table below is the basic list of action/condition/value of each generic devices. For the detailed definition such as parameter and default constraint, please follow [this link](https://github.com/InGarage/MakerPlayGround/tree/master/src/main/resources/json).

| Generic Device | Action | Condition | Value |
|----------------|--------|-----------|-------|
|Accelerometer|-|Compare, Tap, Free Fall|Accel_X, Accel_Y, Accel_Z, Accel_Magnitude|
|Alcohol|-|Compare|Percent|
|Altimeter|-|Compare|Altitude|
|Button|-|Press, Press and release, Not press|-|
|Camera|-|-|Image|
|Color|-|Detect Color|-|
|Current|-|Compare|Ampere|
|Distance|-|Compare|Distance|
|Dust|-|Compare|Atmospheric PM 1.0, Atmospheric PM 2.5, Atmospheric PM 10|
|Energy Meter|-|Compare|Current, Voltage, Power, Frequency, Active Apparent Power, Reactive Apparent Power, Total Active Energy, Total Reactive Energy, Power Factor, Phase Angle|
|Flame|-|Compare|Percent|
|Gesture|-|Swipe Up, Swipe Down, Swipe Left, Swipe Right, Move Forward, Move Backward, Spin Clockwise, Spin Counter Clockwise, Waving, Not Detected|-|
|GPS|-|Compare, Data is valid, Data is not valid|Latitude, Longitude|
|Gyroscope|-|Compare|Gyro_X, Gyro_Y, Gyro_Z|
|Humidity|-|Compare|Humidity|
|Joystick|-|Press up, Press down, Press left, Press right, Press middle, Not press up, Not press down, Not press left, Not press right, Not press middle, Not press all|-|
|Light|-|Compare|Percent|
|LPG|-|Compare|Percent|
|Magnetometer|-|Compare, Direction|Mag_X, Mag_Y, Mag_Z|
|POT|-|Compare|Percent|
|Presence|-|Detect Human, No Human|-|
|Pressuremeter|-|Compare|Pressure|
|RTC|Set DateTime|Compare, Check Day|Hour, Minute, Second, Date, Month, Year|
|Soil Moisture|-|Compare|Percent|
|Sound|-|Compare|SoundLevel|
|Temperature|-|Compare|Temperature|
|Water|-|Detect Water, No Water|-|
|7 Segment|Show Number, Show Two Numbers with Colon, Off|-|-|
|Buzzer|Beep, Play Tone|-|-|
|DC Motor|On, Off|-|-|
|Display|Show Text, Clear Row, Clear Screen|-|-|
|LED|On, Off|-|-|
|Load Driver|On, Off|-|-|
|Relay Module|On, Off|-|-|
|RGB LED|On, Off|-|-|
|RGB LED Strip|Set Color, Fill Color, Set Brightness, Clear|-|-|
|Servo|Move To|-|-|
|Container|Set to|Check Value, Compare|Value|
|Counter|Set to, Count up by 1, Count down by 1, Count by|Value equal to, Value not equal to, Compare|Value|
|Statistics|Add new, Clear all data|Compare|Average, SD, Variance, Count, Min, Max
|Timer|Initialize timer, Stop timer|After, Before|Second|
|Image Recognizer|-|Found, Not Found|-|
|Image to Text|Convert to Text, Convert to Text File|Has Text, Has No Text|Text|
|Map|Pin Location, Clear Pin|-|-|
|Notification|Notify|-|-|
|Telemetry|Send Telemetry|-|-|
|Text to Speech|Convert and play sound, Convert to sound file|-|-|
|Virtual Button|-|Press, Press and release, Not press|-|
|Virtual Gauge|Display number|-|-|
|Virtual LED|On, Off|-|-|
|Virtual Slider|-|Compare|Value|
|Analog (In)|-|Compare|Percent|
|Digital (In)|-|Receive HIGH logic, Receive LOW logic|-|
|Digital (Out)|Set Output HIGH, Set Output LOW|-|-|
|PWM (Out)|Set Duty Cycle|-|-|

### **Units**

The unit of the value or property or action/condition parameter.

- TIME
- METERPERSECSQUARE
- HECTOPASCAL
- METER
- CELSIUS
- FAHRENHEIT
- KELVIN
- RADIUSPERSEC
- DEGREEPERSEC
- DECIBEL
- MICROTESLA
- CENTIMETER
- LUX
- DEGREE
- AMPERE
- MICROGRAMS_PER_CUBIC_METER
- VOLT
- WATT
- VOLT_AMPERE
- VOLT_AMPERE_REACTIVE
- KILO_WATT_HOUR
- KILO_VOLT_AMPERE_REACTIVE_HOUR
- POWER_FACTOR
- SECOND
- MILLISECOND
- WAV
- NUMBER
- PERCENT
- NOT_SPECIFIED
- HERTZ
- BPM

### **Data Types**

The data type of the device property

- DOUBLE
- STRING
- INTEGER
- INTEGER_ENUM
- BOOLEAN_ENUM
- STRING_INT_ENUM
- DATETIME
- IMAGE
- AZURE_COGNITIVE_KEY
- AZURE_IOTHUB_KEY
- RECORD

### **Control Types**

The control type for the device property

- TEXTBOX
- SPINBOX
- DROPDOWN
- SLIDER
- CUSTOMPRINT
- TIME
- CUSTOMSEGMENT
- CHECKBOX
- EXPRESSION
- DATETIMEPICKER
- TEXTBOX_WITH_TEXT_SELECTOR
- IMAGE_SELECTOR
- AZURE_WIZARD
- RECORD
