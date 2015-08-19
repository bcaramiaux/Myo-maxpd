# Myo-maxpd
MaxMSP and PureData objects to get raw EMG data from the Thalmic Myo

The current version only includes the MaxMSP object source code. The repo includes a compiled object for Max/MSP 64bits on Mac OSX (note that the myo sdk seems to only accept 64bits architecture). Make sure MaxMSP is running in *64bits*.

To compile the object, clone or download the Myo-maxpd repo, launch the script to get the MaxSDK:
```
./getmaxsdk.sh
```
Then open the xocde project in xcode/ and compile.
