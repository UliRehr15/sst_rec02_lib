/**********************************************************************
 *
 * sst_rec_lib - library for working with data records
 * Hosted on github
 *
 * Copyright (C) 2015 Hans Ulrich Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sst_rec02_lib_test.cpp    13.09.15  Re.    13.09.15  Re.
//
// test frame for sstRec02Lib

#include <stdio.h>
#include <assert.h>

#include <sstRec02Lib.h>

#include "sstRec02LibTest.h"

#define BUFSIZE 100

int main() {
//=============================================================================
    int iStat = 0;
    {
    sstRec02Cls oRecMem_Int(sizeof(int));
    dREC02RECNUMTYP index = 0;

    // standard errors
    iStat = oRecMem_Int.Read(0,2,&index);
    assert(iStat < 0);  // Error: Memory is empty

    iStat = oRecMem_Int.Writ(0,&index,2);
    assert(iStat < 0);  // Error: Memory is empty

    for(int j = 1; j <= 100; j++)
      oRecMem_Int.WritNew(0,&j,&index);

    // Write record at position 2 into sstRec memory
    int iValue=6;
    iStat = oRecMem_Int.Writ(0, &iValue, 2);
    assert(iStat >= 0);

    FILE* file = fopen("sstRec02LibTest.cpp", "r");
    assert(file);
    // Holds 100-character strings:
    sstRec02Cls oRecMem_Str(sizeof(char) * BUFSIZE);
    index = 1;
    char buf[BUFSIZE];
    while(fgets(buf, BUFSIZE, file))
        //stringStash.add(buf);
        oRecMem_Str.WritNew(0,buf,&index);
    fclose(file);

    for(dREC02RECNUMTYP k = 1; k <= oRecMem_Int.count(); k++)
    { int iVal=0;
      oRecMem_Int.Read(0,k,&iVal);
      printf("oRecMem_Int.Read(%d) = %d\n", k, iVal);
    }

    iValue = 0;
    oRecMem_Int.Read( 0, 2, &iValue);
    assert(iValue==6);  // Return Value for record 2 should be 6

    for(dREC02RECNUMTYP i = 1; i <= oRecMem_Str.count(); i++)
    {
        oRecMem_Str.Read(0,i,buf);
        printf("oRecMem_Str.Read(%d) = %s", i, buf);
    }
    putchar('\n');
    }

//=============================================================================
    // Test with storing in file
    {
      sstRec02Cls intStash(sizeof(int));

      int iStat = intStash.NewFile( 0, (char*)"TestInt");
      assert (iStat >= 0);

      dREC02RECNUMTYP index = 0;
      for(int j = 1; j <= 100; j++)
        intStash.WritNew(0,&j,&index);
      iStat = intStash.SetStoreFile(0);
    }
// Open file TestInt.rec and read integer values, then delete file
    {
      sstRec02Cls *poRecMem_Int;
      poRecMem_Int = new sstRec02Cls(sizeof(int));
      int iStat = poRecMem_Int->OpenFile(0,(char*)"TestInt");
      assert (iStat >= 0);

      for(dREC02RECNUMTYP k = 1; k <= poRecMem_Int->count(); k++)
      { int iVal=0;
        poRecMem_Int->Read(0,k,&iVal);
        assert (iVal==k);
        printf("poRecMem_Int->Read(%d) = %d\n", k, iVal);
      }

    putchar('\n');
    delete(poRecMem_Int);
    }
    //=============================================================================
  return 0;
}
//=============================================================================
