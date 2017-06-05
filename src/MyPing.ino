
// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define PING_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(1000);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping_median(); // Send ping, get ping time in microseconds (uS).
  int tempC = 15;
  float offsetFromTop = 0;
  float distanceToFuel = ((uS / 2) / (1 / ((331.5 + 0.6 * tempC) * 100 / 1000000))); 
  float tank_length = 151.0;
  float tank_width = 68.0;
  float tank_height = 111.5;
  float tank_radius = tank_width / 2;
  float mid_volume_cm3 = 0;
  float sphere_volume_cm3 = 0;
  float total_volume_cm3 = 0;
  const float cm3togal = 0.000264172052;
  float fuelLevel = tank_height + offsetFromTop - distanceToFuel;
  float initialFuelLevel = fuelLevel;
  if (fuelLevel > 0 && fuelLevel <= tank_radius){
    float part1 = ((PI * tank_radius * tank_radius * tank_length)/2);
    float part2 = (tank_radius * tank_length);
    float part3 = (tank_radius - fuelLevel);
    float part4 = (sqrt( fuelLevel * ((2 * tank_radius) - fuelLevel) / (tank_radius * tank_radius) ) );
    float part5 = tank_radius;
    float part6 = (asin(1 - (fuelLevel/tank_radius)));
    float part7 = part2 * ((part3 * part4) + (part5 * part6));
    
    sphere_volume_cm3 = part1 - part7;
    total_volume_cm3 = sphere_volume_cm3;
  } else if (fuelLevel > tank_radius && fuelLevel <= tank_height - tank_radius ) {
    fuelLevel = fuelLevel - tank_radius;
    sphere_volume_cm3 = 274191.93;
    total_volume_cm3 = fuelLevel * tank_width * tank_length + sphere_volume_cm3;   
    
  } else if (fuelLevel > tank_height - tank_radius) {
    fuelLevel = fuelLevel - (tank_height - tank_radius * 2);
    float part1 = ((PI * tank_radius * tank_radius * tank_length)/2);
    float part2 = (tank_radius * tank_length);
    float part3 = (tank_radius - fuelLevel);
    float part4 = (sqrt( fuelLevel * ((2 * tank_radius) - fuelLevel) / (tank_radius * tank_radius) ) );
    float part5 = tank_radius;
    float part6 = (asin(1 - (fuelLevel/tank_radius)));
    float part7 = part2 * ((part3 * part4) + (part5 * part6));
    
    sphere_volume_cm3 = part1 - part7;
    total_volume_cm3 = sphere_volume_cm3 + ((tank_height - tank_radius * 2) * tank_length * tank_width);
        
  }
  
  
  Serial.print("Total Volume cm3: ");
  Serial.print(total_volume_cm3);

  Serial.print("\tDistance: ");
  Serial.print(distanceToFuel);

  Serial.print("\tFuel Level: ");
  Serial.print(initialFuelLevel);

  Serial.print("\tConverted to Gallons: ");
  Serial.print(total_volume_cm3 * cm3togal);
  Serial.println("");
  
}
