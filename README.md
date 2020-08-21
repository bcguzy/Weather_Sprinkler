# Weather_Sprinkler
A WiFi based sprinkler that uses rainfall totals to determine if a plant needs watering or not.

## Hardware Used  
-ESP8266 NodeMCU
-ESP8266 NodeMCU motor shield
-9V Solenoid Valve
-Power source (9V battery used in this project)
-Fittings and tubing for solenoid Valve
-Female to Female wire for Deep Sleep functionality  
  
The above photo shows the wiring for this project. The solenoid valve was attached to the Motor A terminals on the motor shield board.
9V Battery was attached to the ESP8266 power connector and a jumper wire was used to connect the ESP power and motor power together.
This means that the same power source can be used for both the motor and the ESP8266. A female to female wire was used to connect pin D0 to the reset pin.
Pin D0 is the wake pin and will be used to reset the NodeMCU when the deep sleep timer is up.  
  
## Programing libraries and techniques used  
The arduino IDE was used to develop the software for the sprinkler because of its robust support for the NodeMCU and for ease of use.
[The standard ESP8266 libraries ESP8266Wifi and ESP8266HTTPClient](https://github.com/esp8266/Arduino) were used along with [ArduinoJson](https://github.com/bblanchon/ArduinoJson) for json processing.
Note that the placeholder ssid and password need to be replaced before this github code can be used. Serial outputs were used for debugging and to ensure that data was being recieved.

## Possible Modifications
There are several hardware modifications that could be made to this design to make it more compact and suitible for outdoor use.
A NodeMCU and motor shield were used for easy prototyping but the ESP8266 could be directly soldered to a smaller board for a more compact product.
A smaller power management solution could be used as well such as a small power control board rather than an entire shield.
Valves could be chained together to operate like a sprinkler system as well. The valves could be hooked up to a water supply like a hose to eliminate the need for a reservoir that needs to be refilled.
