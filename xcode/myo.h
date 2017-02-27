//
//  Myo.h
//  myo
//
//  Created by Baptiste on 13/08/2015.
//
//

#ifndef __myo__Myo__
#define __myo__Myo__


#include <myo/myo.hpp>

#include <vector>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <array>
//#include "ext.h"


class TheMyo : public myo::DeviceListener {
    
public:
    
    TheMyo(int nc = 8);
    
    ~TheMyo() {};
    
    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp);
    
    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
    
    
    void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel);
    
    void onGyroscopeData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &gyro);
    
    void onOrientationData(myo::Myo *myo, uint64_t timestamp, const myo::Quaternion< float > &rotation);
    
//    void onConnect(myo::Myo *myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    
    std::vector<float> & getEmgData();
    
    std::vector<float> & getAccelerometerData();
    
    std::vector<float> & getGyroscopeData();
    
    std::vector<float> & getOrientationData();
    
    //
    int getNumOfChannels();
    
private:
    
    // The values of this array is set by onEmgData() above.
    //    std::array<int8_t, 8> emgSamples;
    std::vector<float> emgdata;
    std::vector<float> accdata;
    std::vector<float> gyrodata;
    std::vector<float> quatdata;
    int numChannels;
    int acclDim;
    int gyroDim;
    int quatDim;
    
};

#endif /* defined(__myo__Myo__) */
