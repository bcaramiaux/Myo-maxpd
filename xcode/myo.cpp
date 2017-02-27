//
//  Myo.cpp
//  myo
//
//  Created by Baptiste on 13/08/2015.
//
//

#include "myo.h"

TheMyo::TheMyo(int nc)
{
    numChannels = nc;
    acclDim = 3;
    gyroDim = 3;
    quatDim = 3;
}


void TheMyo::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
    emgdata.clear();
    accdata.clear();
    gyrodata.clear();
    quatdata.clear();
    for (int k=0; k<numChannels;k++) emgdata.push_back(0.0);
    for (int k=0; k<acclDim;k++) accdata.push_back(0.0);
    for (int k=0; k<gyroDim;k++) gyrodata.push_back(0.0);
    for (int k=0; k<quatDim;k++) quatdata.push_back(0.0);
}

void TheMyo::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    emgdata.clear();
    for (int i = 0; i < numChannels; i++)
        emgdata.push_back(emg[i]/(float)256.0);
}

void TheMyo::onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel)
{
    accdata.clear();
    for (int i = 0; i < acclDim; i++)
        accdata.push_back(accel[i]);
}

void TheMyo::onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro)
{
    gyrodata.clear();
    for (int i = 0; i < gyroDim; i++)
        gyrodata.push_back(gyro[i]);
}

void TheMyo::onOrientationData(myo::Myo *myo, uint64_t timestamp, const myo::Quaternion< float > &rotation)
{
    using std::atan2;
    using std::asin;
    using std::sqrt;
    using std::max;
    using std::min;
    
    // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
    float roll = atan2(2.0f * (rotation.w() * rotation.x() + rotation.y() * rotation.z()),
                       1.0f - 2.0f * (rotation.x() * rotation.x() + rotation.y() * rotation.y()));
    float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (rotation.w() * rotation.y() - rotation.z() * rotation.x()))));
    float yaw = atan2(2.0f * (rotation.w() * rotation.z() + rotation.x() * rotation.y()),
                      1.0f - 2.0f * (rotation.y() * rotation.y() + rotation.z() * rotation.z()));
    
    quatdata.clear();
    quatdata.push_back(roll);
    quatdata.push_back(pitch);
    quatdata.push_back(yaw);

}


std::vector<float>& TheMyo::getEmgData()
{
    return emgdata;
}

std::vector<float> & TheMyo::getAccelerometerData()
{
    return accdata;
}

std::vector<float> & TheMyo::getGyroscopeData()
{
    return gyrodata;
}

std::vector<float> & TheMyo::getOrientationData()
{
    return quatdata;
}

int TheMyo::getNumOfChannels()
{
    return numChannels;
}

//
////std::vector<float> getEMG()
////{
////
////}
