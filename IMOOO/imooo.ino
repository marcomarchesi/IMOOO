#include "GY_85.h"
#include <Wire.h>
#include "MadgwickAHRS.h"

GY_85 GY85;     //create the object
MadgwickAHRS Mad;
void setup()
{
    Wire.begin();
    delay(10);
    Serial.begin(9600);
    delay(10);
    GY85.init();
    Mad.init(50);
    delay(10);
}


void loop()
{
    float ax = (float)GY85.accelerometer_x( GY85.readFromAccelerometer() );
    float ay = (float)GY85.accelerometer_y( GY85.readFromAccelerometer() );
    float az = (float)GY85.accelerometer_z( GY85.readFromAccelerometer() );
    
    float cx = (float)GY85.compass_x( GY85.readFromCompass() );
    float cy = (float)GY85.compass_y( GY85.readFromCompass() );
    float cz = (float)GY85.compass_z( GY85.readFromCompass() );

    float gx = GY85.gyro_x( GY85.readGyro() ) * M_PI/180;
    float gy = GY85.gyro_y( GY85.readGyro() ) * M_PI/180;
    float gz = GY85.gyro_z( GY85.readGyro() ) * M_PI/180;

      Mad.update(gx,gy,gz,ax,ay,az,cx,cy,cz);
      float roll = Mad.getRoll() * 180/M_PI;
      float pitch = Mad.getPitch() *  180/M_PI;
      float yaw = Mad.getYaw() *  180/M_PI;
      
      Serial.print  ( " AB " );
      Serial.print ( ax );
      Serial.print  ( " " );
      Serial.print ( ay );
      Serial.print  ( " " );
      Serial.print ( az );
      Serial.print  ( " " );
      Serial.print  ( gx );
      Serial.print (" ");
      Serial.print ( gy );
      Serial.print (" ");
      Serial.print ( gz );
      Serial.print (" ");
      Serial.print (cx);
      Serial.print (" ");
      Serial.print (cy);
      Serial.print (" ");
      Serial.print (cz);
      Serial.print (" ");
      Serial.print (roll);
      Serial.print(" ");
      Serial.print(pitch);
      Serial.print(" ");
      Serial.println(yaw);
  
      delay(20); //50Hz             // only read every 0,5 seconds, 10ms for 100Hz, 20ms for 50Hz
}
