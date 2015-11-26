#include "GY_85.h"
#include <Wire.h>
#include "MadgwickAHRS.h"

#define FACTORACC (float)0.0392262
#define FACTORGYR (float)0.0011826
#define FACTORMAG (float)0.092

GY_85 GY85;     //create the object
MadgwickAHRS Mad;

float mx_offset = -8.37f;
float my_offset = 2.99f;
float mz_offset = 0.51f;
float mx_fc = 0.0f;
float my_fc = 0.0f;
float mz_fc = 0.0f;
float mx_max,mx_min;
float my_max,my_min;
float mz_max,mz_min;

// HARD IRON CORRECTION
float get_mag_offset(float min_i,float max_i)
{
  return (min_i + max_i) / 2;
}

float get_mag_fc(float min_i,float max_i,float min_j,float max_j,float min_k,float max_k,int index)
{
  float dmax,dmin,m_fc;
  if (index == 1)
  {
    dmax = max_i;
    dmin = min_i;
  }else if (index == 2)
  {
    dmax = max_j;
    dmin = min_j;
  }else if (index == 3)
  {
    dmax = max_k;
    dmin = min_k;
  }

  m_fc = (((max_i - min_i) / 2) + ((max_j - min_j) / 2) + ((max_k - min_k) / 2)) * (2/3) * (1 / (dmax - dmin));
  return m_fc;
}


void setup()
{
    Wire.begin();
    delay(10);
    Serial.begin(9600);
    delay(10);
    GY85.init();
    Mad.init(50);
    delay(10);  //one second
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


//    mx_max = max(cx,mx_max);
//    my_max = max(cy,my_max);
//    mz_max = max(cz,mz_max);
//    mx_min = min(cx,mx_min);
//    my_min = min(cy,my_min);
//    mz_min = min(cz,mz_min);

//    mx_offset = get_mag_offset(mx_max,mx_min);
//    my_offset = get_mag_offset(my_max,my_min);
//    mz_offset = get_mag_offset(mz_max,mz_min);

//    mx_fc = get_mag_fc(mx_min,mx_max,my_min,my_max,mz_min,mz_max,1);
//    my_fc = get_mag_fc(mx_min,mx_max,my_min,my_max,mz_min,mz_max,2);
//    mz_fc = get_mag_fc(mx_min,mx_max,my_min,my_max,mz_min,mz_max,3);
    

//    Serial.print("X off: ");
//    Serial.print(mx_offset);
//    Serial.print("Y off: ");
//    Serial.print(my_offset);
//    Serial.print("Z off: ");
//    Serial.print(mz_offset);
//    Serial.print("X fc: ");
//    Serial.print(mx_fc);
//    Serial.print("Y fc: ");
//    Serial.print(my_fc);
//    Serial.print("Z fc: ");
//    Serial.println(mz_fc);

    cx = (cx - mx_offset);  // just HARD IRON CORRECTION
    cy = (cy - my_offset);
    cz = (cz - mz_offset);

      Mad.update(gx,gz,-gy,ax,az,-ay,cz,cx,cy);
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
      Serial.print(yaw);
      Serial.print(" ");
      Serial.println(Mad.beta);
  
      delay(20); //50Hz             // only read every 0,5 seconds, 10ms for 100Hz, 20ms for 50Hz
}



