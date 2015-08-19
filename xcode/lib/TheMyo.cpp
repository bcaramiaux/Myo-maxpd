//
//  Myo.cpp
//  myo
//
//  Created by Baptiste on 13/08/2015.
//
//

#include "TheMyo.h"

TheMyo::TheMyo(int nc)
{
    numChannels = nc;
}


void TheMyo::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
    emgdata.clear();
    for (int k=0; k<numChannels;k++) emgdata.push_back(0.0);
}

void TheMyo::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    emgdata.clear();
    for (int i = 0; i < numChannels; i++)
        emgdata.push_back(emg[i]/(float)256.0);
}


std::vector<float>& TheMyo::getEmgData()
{
    return emgdata;
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