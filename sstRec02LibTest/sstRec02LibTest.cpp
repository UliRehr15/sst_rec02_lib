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

#define BUFSIZE 100

int main() {
//=============================================================================
    int iStat = 0;
    {
    sstRec02Cls oRecMem_Int(sizeof(int));
    dREC02RECNUMTYP index = 0;
    for(int j = 0; j < 100; j++)
      oRecMem_Int.WritNew(0,&j,&index);

    // Write record at position 2 into sstRec memory
    int iValue=6;
    iStat = oRecMem_Int.Writ(0, &iValue, 2);

    FILE* file = fopen("sstRec02LibTest.cpp", "r");
    assert(file);
    // Holds 80-character strings:
    sstRec02Cls stringStash(sizeof(char) * BUFSIZE);
    index = 0;
    char buf[BUFSIZE];
    while(fgets(buf, BUFSIZE, file))
        //stringStash.add(buf);
        stringStash.WritNew(0,buf,&index);
    fclose(file);

    for(int k = 0; k < oRecMem_Int.count(); k++)
    { int iVal=0;
      oRecMem_Int.Read(0,k,&iVal);
      printf("intStash.fetch(%d) = %d\n", k, iVal);
    }

    iValue = 0;
    oRecMem_Int.Read( 0, 2, &iValue);
    assert(iValue==6);  // Return Value for record 2 should be 6

    for(int i = 0; i < stringStash.count(); i++)
    {
        stringStash.Read(0,i++,buf);
        printf("stringStash.fetch(%d) = %s", i, buf);
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
      for(int j = 0; j < 100; j++)
        intStash.WritNew(0,&j,&index);
      iStat = intStash.SetStoreFile(0);
    }

    {
      sstRec02Cls intStash(sizeof(int));
      int iStat = intStash.OpenFile(0,(char*)"TestInt");
      assert (iStat >= 0);

      for(int k = 0; k < intStash.count(); k++)
      { int iVal=0;
        intStash.Read(0,k,&iVal);
        printf("intStash.fetch(%d) = %d\n", k, iVal);
      }

    putchar('\n');
    }

    //=============================================================================
  return 0;
}
