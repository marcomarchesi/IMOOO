//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif//=====================================================================================================


#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

//----------------------------------------------------------------------------------------------------
// Variable declaration
class MadgwickAHRS{
public:

	void init(float freq);
//---------------------------------------------------------------------------------------------------
// Function declarations

	void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
	float getRoll();
	float getPitch();
	float getYaw();
  float beta;       // algorithm gain
  float delta;
private:
	float sampleFreq;	
	
  float beta_counter;
  float rho;
	float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame
  float roll,pitch,yaw;
  float past_roll;
};
#endif
//=====================================================================================================
// End of file
//=====================================================================================================
