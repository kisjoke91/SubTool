//
//  ChaosCommonLibrary.cpp
//  ChaosCommon
//
//  Created by Szigeti József on 2017. 06. 29..
//  Copyright © 2017. Szigeti József. All rights reserved.
//

#include "ChaosCommonLibrary.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int CCL_GetNthElementOfString(const char * sample, string & res, char separator, int index)
{
    char result[1024];
    memset(result, 0, 1024);
    
    // pointerek ellenőrzése
    if (sample == NULL)
    {
        printf("CCL_GetNthElementOfString(): NULL pointer passed. (sample)\n");
        return -1;
    }
    
    // változók
    const int len = (int)strlen(sample);
    int elementsnum = 0;
    int currelement = 0;
    int lastSeparator = 0;
    int i;
    int ir;
    
    // string hosszának, és formájának ellenőrzése
    if(len < 1)
    {
        printf("CCL_GetNthElementOfString(): The sample string is empty.\n");
        return -1;
    }
    
    if(sample[0] == separator || sample[len - 1] == separator)
    {
        printf("CCL_GetNthElementOfString(): The sample string has invalid format. (Separator on line begin or end)\n");
        return -1;
    }
    
    // string elemeinek számolása
    for(i = 0; i < len; i ++)
    {
        if(sample[i] == separator)
        {
            if(i - lastSeparator - 1 == 0 && i != 1)
            {
                printf("CCL_GetNthElementOfString(): The sample string has invalid format. (Repeated separators)\n");
                return -1;
            }
            elementsnum ++;
            lastSeparator = i;
        }
    }
    
    elementsnum ++;
    
    // index paraméter ellenőrzése
    if(index >= elementsnum)
    {
        printf("CCL_GetNthElementOfString(): The string has fewer elements than specified in the index parameter\n");
        return 0;
    }
    
    // Lapozás a megadott elemig
    for(i = 0; currelement != index; i ++)
    {
        if(sample[i] == separator) currelement ++;
    }
    
    // Az index paraméter által megadott elem másolása a result változóba
    for(ir = 0; sample[i] != separator; i ++)
    {
        result[ir] = sample[i];
        ir ++;
        if(len - 1 == i) break;
    }
    
    result[ir] = 0;
    
    res = result;
    return elementsnum;
}

int CCL_GetNthElementOfString(const char * sample, int & res, char separator, int index) {
    
    string rslt;
    int rc = CCL_GetNthElementOfString(sample, rslt, separator, index);
    
    res = atoi(rslt.c_str());

    return rc;
}

int CCL_GetNthElementOfString(const char * sample, unsigned long & res, char separator, int index) {
    
    string rslt;
    int rc = CCL_GetNthElementOfString(sample, rslt, separator, index);
    
    res = (unsigned long) atol(rslt.c_str());

    return rc;
}

int CCL_GetNthElementOfString(const char * sample, double & res, char separator, int index) {
    
    string rslt;
    int rc = CCL_GetNthElementOfString(sample, rslt, separator, index);
    
    res = atof(rslt.c_str());
    
    return rc;
}

bool CCL_lbcmp(string prefix, string str) {
    
    return strncmp(prefix.c_str(), str.c_str(), strlen(prefix.c_str())) == 0 ? true : false;
}
