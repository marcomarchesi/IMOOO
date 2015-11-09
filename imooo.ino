#include "GY_85.h"
#include <Wire.h>
#include "MadgwickAHRS.h"

#define FACTORACC (float)0.0392262
#define FACTORGYR (float)0.0011826
#define FACTORMAG (float)0.092

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
    delay(1000);  //one second
}


void loop()
{
    float ax = (float)GY85.accelerometer_x( GY85.readFromAccelerometer() ) * FACTORACC;
    float ay = (float)GY85.accelerometer_y( GY85.readFromAccelerometer() ) * FACTORACC;
    float az = (float)GY85.accelerometer_z( GY85.readFromAccelerometer() ) * FACTORACC;
    
    float cx = (float)GY85.compass_x( GY85.readFromCompass() ) * FACTORMAG;
    float cy = (float)GY85.compass_y( GY85.readFromCompass() ) * FACTORMAG;
    float cz = (float)GY85.compass_z( GY85.readFromCompass() ) * FACTORMAG;

    float gx = GY85.gyro_x( GY85.readGyro() ) * FACTORGYR ;
    float gy = GY85.gyro_y( GY85.readGyro() ) * FACTORGYR ;
    float gz = GY85.gyro_z( GY85.readGyro() ) * FACTORGYR ;

      Mad.update(gx,gy,gz,ax,ay,az,cx,cy,cz);
      float roll = Mad.getRoll();
      float pitch = Mad.getPitch();
      float yaw = Mad.getYaw();


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



