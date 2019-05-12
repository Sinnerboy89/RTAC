# RTAC
Coding challenge involving the implementation of real-time audio convolution in JUCE

Instructions/notes:

1) The folder consists of Matlab codes for 5.1 real time audio convolution
2) file-01 to file-06 are the FL, FR, C, LFE, RL, RR audio channels
3) Also attached are hrir file in .mat format for the corresponding locations
4) This matlab code is written using the real-time audio toolbox in matlab
5) Run “realtimeaudioConvolution_5p1_HRIRs.mlx”

To-Do

  * Fix runtime errors (jassert, file format issue)
  * Save output and compare with benchmark
  * Tidy up 5.1 input
  * Get "online" (have getnextaudioblock deal with I/O)
  * Add load interface, process button and play button
  * Run profiling / assess real-time aspect
  * Consider methods of optimizing in MATLAB then JUCE
  * Add graphs/plots
  * Prepare points from to-do list and commit history

Done:
  * Chop out small test section (full input too long)
  * Try out live script and get benchmark stereo output
  * Determine what live script is actually doing
  * Load 5.1 input ready for convolver function
  * Finish myHRTFConvolver conversion
