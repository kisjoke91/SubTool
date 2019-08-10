//
//  ChaosCommonLibrary.h
//  ChaosCommon
//
//  Created by Szigeti József on 2017. 06. 29..
//  Copyright © 2017. Szigeti József. All rights reserved.
//

#ifndef __CHAOSCOMMONLIBRARY_H__
#define __CHAOSCOMMONLIBRARY_H__

#include <stdint.h>
#include <string>
using namespace std;

/*@ChaosDoc
 
int CCL_GetNthElementOfString(const char sample, char * result, char separator, int index)
 
Visszaadja egy string előre megadott karakterrel elválasztott n-edik elemét. Figyelem, az első elem indexe
 
Paraméterek:
    const char * sample:    Az elemezendő karakterlánc.
    string & res:           String referencia, amibe a kívánt elem másolásra kerül.
    char separator:         A stringben alkalmazott elválasztóelem
    int index:              Megadja, hányadik elemet másolja a result változóba.

Visszatérési érték:
    -1:     A string hibás formátumú, vagy NULL pointer lett átadva.
    0:      Nincs annyi elem a stringben, mint a megadott index paraméter
    0 <:    A string elemeinek száma
 
*/
int CCL_GetNthElementOfString(const char * sample, string & res, char separator, int index);

int CCL_GetNthElementOfString(const char * sample, int & res, char separator, int index);

int CCL_GetNthElementOfString(const char * sample, double & res, char separator, int index);

int CCL_GetNthElementOfString(const char * sample, unsigned long & res, char separator, int index);


#endif /* __CHAOSCOMMONLIBRARY_H__ */
