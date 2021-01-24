//
//  subtool.h
//  subtool
//
//  Created by Szigeti József on 08.08.19.
//  Copyright © 2019 Chaos Developing. All rights reserved.
//

#ifndef __SUBTOOL_H__
#define __SUBTOOL_H__

#include <iostream>
#include <vector>
using namespace std;

#define SRT_TIMING_SEPARATOR            " --> "
#define SRT_INVALID_ID                  0
#define SRT_INVALID_TIMING              -1
#define SRT_MIN_TIMING_LENGTH           29
#define SRT_TIMING_LENGTH               12
#define SRT_START_TIME_INDEX            0
#define SRT_END_TIME_INDEX              17
#define SRT_TIMING_SEPARATOR_INDEX      12               


typedef struct {
    
    int id = SRT_INVALID_ID;
    long startTime = SRT_INVALID_TIMING;
    long endTime = SRT_INVALID_TIMING;
    string content;
} srt_frame_t;


enum srt_error_t {
    
    success,
    unspecified,
    failedOpeningFile,
    missingTimingSeparator,
    invalidTimingFormat,
    noSuchFrameID,
    frameStartsLaterThanEnds,
    frameStartsEarlierThanPreviousFrameEnds,
    frameEndsLaterThanNextFrameStarts
};


class Subtool {

public:
    // Input operations
    srt_error_t openMainFile(string path);
    void getMainFileFromString(string lines);

    // Manipulating and accessing operations
    void shiftTimingOfMainFile(long offset);
    srt_error_t addFrameToMainFile(srt_frame_t frame);
    srt_error_t setFrameInMainFile(srt_frame_t frame);
    bool removeFrameFromMainFile(int frameID);
    srt_frame_t getFrameFromMainFile(int frameID);
    
    
    // Output operations
    string getOutput(void);
    void writeOutput(string path);
    
    vector <srt_frame_t> mainFile;

private:
    srt_error_t readFromFile(string path, vector <string> & result);
    vector <string> readFromString(string lines);
    srt_error_t getFrameTiming(string line, long & start, long & end);
    srt_error_t getMilliseconds(string timing, long & result);
    string getTimeString (long time);
    vector <srt_frame_t> buildFrames(vector <string> lines);
    string renderOutput(vector <srt_frame_t> frames);
    void shiftTiming(long millis, vector <srt_frame_t> & frames);
    void writeOutputFile(string path, string lines);
    srt_frame_t getFrameBefore(long time);
    srt_frame_t getFrameAfter(long time);
};


#endif /*__SUBTOOL_H__*/
