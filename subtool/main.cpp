//
//  main.cpp
//  subtool
//
//  Created by Szigeti József on 08.08.19.
//  Copyright © 2019 Chaos Developing. All rights reserved.
//

#include "subtool.h"


vector <string> params;
string outputPath = "subtool_output.srt";
string inputPath;
long timeShift = 0;


void printHelp(void) {
    
    string str;
    str += "\nUsage:\n";
    str += "subtool -i [path/to/file.srt]  specify input file.\n";
    str += "        -o [path/to/file.srt]  specify output file.\n";
    str += "        -s [value in ms]       shift timings in millisecs.\n\n";
    str += "        If no output is specified, the syntax of the file will be\n";
    str += "        automatically repaired and saved as \"subtool_output.srt\"\n\n";
    str += "example: subtool -i dieHard.srt -o corrected.srt -s 2500\n\n";
    
    cout << str << endl;
    
    exit(0);
}

void setTimeShiftParameter(int idx) {

    if (params.size() <= idx + 1)
        printHelp();
    
    timeShift = atol(params[idx + 1].c_str());
}

void setInputParameter(int idx) {

    if (params.size() <= idx + 1)
        printHelp();
    
    inputPath =  params[idx + 1];
}

void setOutputParameter(int idx) {

    if (params.size() <= idx + 1)
        printHelp();
    
    outputPath = params[idx + 1];
}

int main(int argc, const char * argv[]) {
    
    for (int i = 1; i < argc; i ++) {
        
        params.push_back(argv[i]);
    }
    
    for (int i = 0; i < params.size(); i ++) {
        
        if (!params[i].compare("-i"))
            setInputParameter(i);
        
        else if (!params[i].compare("-o"))
            setOutputParameter(i);
        
        else if (!params[i].compare("-s"))
            setTimeShiftParameter(i);
    }
    
    if (inputPath.size() > 4){
        
        Subtool tool;

        srt_error_t err = tool.openMainFile(inputPath);
        
        if (err == success) {
            
            tool.shiftTimingOfMainFile(timeShift);
            tool.writeOutput(outputPath);
            
        }
        
        else {
            cout << endl << "subtool: The file could not be readed." << endl << endl;
        }
    }
    
    else printHelp();
    
    return 0;
}
