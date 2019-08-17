//
//  subtool.cpp
//  subtool
//
//  Created by Szigeti József on 08.08.19.
//  Copyright © 2019 Chaos Developing. All rights reserved.
//

#include "subtool.h"
#include "ChaosCommonLibrary.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


srt_error_t Subtool::openMainFile(string path) {

    srt_error_t err;
    vector <string> lines;
    
    err = readFromFile(path, lines);
    
    if (err != success)
        return err;
        
    mainFile = buildFrames(lines);

    return success;
}


void Subtool::getMainFileFromString(string lines) {

    string str;
    istringstream input(lines);
    vector <string> lns;

    while (getline(input, str)) {
        
        lns.push_back(str);
    }

    mainFile = buildFrames(lns);
}


void Subtool::shiftTimingOfMainFile(long offset) {

   shiftTiming(offset, mainFile);
}


void Subtool::writeOutput(string path) {

    writeOutputFile(path, renderOutput(mainFile));   
}


string Subtool::getOutput(void) {

    return renderOutput(mainFile);
}


srt_error_t Subtool::readFromFile(string path, vector<string> & result) {
    
    ifstream file(path);
    
    if (file.is_open()) {
        
        string line;
        while (getline(file, line)) {

            line.erase(std::remove(line.begin(),line.end(), '\r'),line.end());
            if (line.size())
                result.push_back(line);
        }
        
        file.close();
        
        return success;
    }
    
    return failedOpeningFile;
}


void Subtool::writeOutputFile(string path, string lines) {
    
    ofstream file;
    file.open (path);
    file << lines;
    file.close();
}


srt_error_t Subtool::getFrameTiming(string line, long & start, long & end) {
    
    string startTimeString;
    string endTimeString;
    size_t timingSeparatorIndex;
        
    timingSeparatorIndex = line.find(SRT_TIMING_SEPARATOR);
    
    if (timingSeparatorIndex == string::npos)
        return missingTimingSeparator;
    
    if (timingSeparatorIndex != SRT_TIMING_SEPARATOR_INDEX)
        return invalidTimingFormat;
    
    if (line.size() < SRT_MIN_TIMING_LENGTH)
        return invalidTimingFormat;
    
    startTimeString = line.substr(SRT_START_TIME_INDEX, SRT_TIMING_LENGTH);
    endTimeString = line.substr(SRT_END_TIME_INDEX, SRT_TIMING_LENGTH);
    
    if (startTimeString.size() != SRT_TIMING_LENGTH &&
        endTimeString.size() != SRT_TIMING_LENGTH)
        return invalidTimingFormat;
    
    if (getMilliseconds(startTimeString, start) != success)
        return invalidTimingFormat;
    
    if (getMilliseconds(endTimeString, end) != success)
            return invalidTimingFormat;
            
    return success;
}


srt_error_t Subtool::getMilliseconds(string timing, long & result) {
    
    int hours;
    int minutes;
    int seconds;
    int millis;
    string helper;
    
    if (CCL_GetNthElementOfString(timing.c_str(), hours, ':', 0) != 3)
        return invalidTimingFormat;
    
    CCL_GetNthElementOfString(timing.c_str(), minutes, ':', 1);
    CCL_GetNthElementOfString(timing.c_str(), helper, ':', 2);
    
    if (CCL_GetNthElementOfString(helper.c_str(), seconds, ',', 0) != 2)
            return invalidTimingFormat;
    
    CCL_GetNthElementOfString(timing.c_str(), millis, ',', 1);
    
    result = 0;
    result += hours * 3600000;
    result += minutes * 60000;
    result += seconds * 1000;
    result += millis;
    
    return success;
}

string Subtool::getTimeString(long time) {
    
    string str;
    int hours;
    int minutes;
    int seconds;
    int millis;
    
    hours = (int)time / 3600000;
    time -= hours * 3600000;
    minutes = (int)time / 60000;
    time -= minutes * 60000;
    seconds = (int)time / 1000;
    time -= seconds * 1000;
    millis = (int)time;
    
    if (hours < 10) str += "0";
    str += to_string(hours);
    str += ":";
    if (minutes < 10) str += "0";
    str += to_string(minutes);
    str += ":";
    if (seconds < 10) str += "0";
    str += to_string(seconds);
    str += ",";
    if (millis < 10) str += "0";
    if (millis < 100) str += "0";
    str += to_string(millis);
    
    return str;
}

vector <srt_frame_t> Subtool::buildFrames(vector <string> lines) {
    
    vector <srt_frame_t> frames;
    vector <int> timingsIndices;
    int currentLine;
    
    if (lines.size() == 0) return frames;
    
    for (int i = 0; i < lines.size(); i ++) {
        
        srt_frame_t f;
        
        if (getFrameTiming(lines[i], f.startTime, f.endTime) == success) {
            
            timingsIndices.push_back(i);
            frames.push_back(f);
        }
    }
    
    for (int i = 0; i < frames.size() - 1; i ++) {
        
        int nextTiming = timingsIndices[i + 1];
        
        for(currentLine = timingsIndices[i] + 1;
            currentLine < nextTiming &&
            !std::all_of(lines[currentLine].begin(), lines[currentLine].end(), ::isdigit);
            currentLine ++) {
            
            frames[i].content += lines[currentLine];
            frames[i].content += "\n";
        }
        
        if (i == frames.size() - 2) {
            
            i ++;
            
            for (currentLine = timingsIndices[i] + 1; currentLine < lines.size(); currentLine ++) {
                
                frames[i].content += lines[currentLine];
                frames[i].content += "\n";
            }
        }
        
    }
    
    return frames;
}


string Subtool::renderOutput(vector <srt_frame_t> frames) {
    
    string str;
    
    for (int i = 0; i < frames.size(); i ++) {
        
        str += to_string(i + 1);
        str += "\n";
        str += getTimeString(frames[i].startTime);
        str += SRT_TIMING_SEPARATOR;
        str += getTimeString(frames[i].endTime);
        str += "\n";
        str += frames[i].content;
        str += "\n";
    }
    
    return str;
}

void Subtool::shiftTiming(long millis, vector <srt_frame_t> & frames) {
    
    for (int i = 0; i < frames.size(); i ++) {
        
        frames[i].startTime += millis;
        frames[i].endTime += millis;
    }
    
    for (int i = 0; i < frames.size(); i ++) {
        
        if (frames[i].startTime < 0 && frames[i].endTime < 0) {
            frames.erase(frames.begin() + 0);
            i = -1;
            continue;
        }
        
        if (frames[i].startTime < 0 && frames[i].endTime > 0)
            frames[i].startTime = (long) 0;
    }
}


srt_frame_t Subtool::getFrameFromMainFile(int frameID) {
    
    srt_frame_t frame;
    
    if (frameID > mainFile.size() || frameID <= 0)
        return frame;
    
    frame = mainFile[frameID -1];
    frame.id = frameID;
    
    return frame;
}


int Subtool::getMainFileFramesSize(void) {
    
    return (int) mainFile.size();
}


srt_error_t Subtool::setFrameInMainFile(srt_frame_t frame) {

     srt_frame_t prev, next;
    
    if (frame.id == SRT_INVALID_ID)
        return noSuchFrameID;
    
    if (frame.startTime >= frame.endTime)
        return frameStartsLaterThanEnds;

    // check if the frame exists
    if(frame.id > mainFile.size())
        return noSuchFrameID;
        
    if (mainFile.size() > frame.id)
        next = mainFile[frame.id];
        
    if (mainFile.size() >= 2 && frame.id > 1)
        prev = mainFile[frame.id - 2];
        
    if (next.startTime != SRT_INVALID_TIMING &&
        next.startTime <= frame.endTime)
        return frameEndsLaterThanNextFrameStarts;
        
    if (prev.startTime != SRT_INVALID_TIMING &&
        prev.endTime >= frame.startTime)
        return frameStartsEarlierThanPreviousFrameEnds;
        
    mainFile[frame.id -1] = frame;
    return success;
}

bool Subtool::removeFrameFromMainFile(int frameID) {
    
    if (frameID > mainFile.size() || frameID <= 0)
                return false;
    
    mainFile.erase(mainFile.begin() + (frameID - 1));
        
    return true;
}


srt_error_t Subtool::addFrameToMainFile(srt_frame_t frame) {
    
    // Check if startTime is greater than endTime
    if (frame.startTime >= frame.endTime)
        return frameStartsLaterThanEnds;
    
    // the frame has no id yet, 
    //so place it to the end oft the file
    if (frame.id == SRT_INVALID_ID) {
        
        // There is a previous frame too
        if (mainFile.size() > 0) {
            
            srt_frame_t prev;
            prev = mainFile.back();

            // startTime of the new frame is less
            if (prev.endTime >= frame.startTime)
                return frameStartsEarlierThanPreviousFrameEnds;
        }

        // add frame at the end of the file
        frame.id = (int) mainFile.size() + 1;
        mainFile.push_back(frame);
        
        return success;
    }

    // The frame has an id.
    // Trying to place there
    srt_frame_t prev, next;

    // check if the frame exists
    if(frame.id > mainFile.size())
        return noSuchFrameID;
    
    if (mainFile.size() >= frame.id)
        next = mainFile[frame.id - 1];
    
    if (mainFile.size() >= 2 && frame.id > 1)
        prev = mainFile[frame.id - 2];
    
    if (next.startTime != SRT_INVALID_TIMING &&
        next.startTime <= frame.endTime)
        return frameEndsLaterThanNextFrameStarts;
    
    if (prev.startTime != SRT_INVALID_TIMING &&
        prev.endTime >= frame.startTime)
        return frameStartsEarlierThanPreviousFrameEnds;
    
    mainFile.insert(mainFile.begin() + (frame.id - 1), frame);
    return success;
}
