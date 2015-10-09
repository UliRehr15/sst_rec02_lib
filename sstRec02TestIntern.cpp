/**********************************************************************
 *
 * sst_rec_lib - library for working with data records
 * Hosted on github
 *
 * Copyright (C) 2015 Uli Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstRec02TestIntern.cpp    02.10.15  Re.    02.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int sstRec02_DoSomeInternTests (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Test writ cargo systems into vector
  iStat = Test_VectorSys_Stack ( 0);

  // Test writ cargo systems into vector
  iStat = Test_VectorSys_Heap ( 0);

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int Test_VectorSys_Stack (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

    sstRec02VectSysCls oDssDataSys;

    sstRec02CargoKeyInternCls oDssDataKey1;
    sstRec02CargoKeyInternCls oDssDataKey2;

    sstRec02TestRec1Cls oCargoData11;
    sstRec02TestRec1Cls oCargoData12;
    sstRec02TestRec2Cls oCargoData21;
    sstRec02TestRec2Cls oCargoData22;

    iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData11), (char*) "XXX", &oDssDataKey1);

  if(iStat != 0)  {    assert(0);  }

  oCargoData11.iValue = 55;
  strncpy(oCargoData11.cVal,"abc", 5);

  iStat = oDssDataSys.WrtCargo ( 0, &oDssDataKey1, &oCargoData11);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);
  if(oCargoData11.iValue != oCargoData12.iValue) assert(0);

  iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData21), (char*) "YYY", &oDssDataKey2);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);
  if(oCargoData11.iValue != oCargoData12.iValue) assert(0);

  iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData21), (char*) "ZZZ", &oDssDataKey2);

  oCargoData21.dValue = 55.5;
  strncpy(oCargoData21.cVal,"dcba", 10);

  iStat = oDssDataSys.WrtCargo ( 0, &oDssDataKey2, &oCargoData21);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);

  if(oCargoData11.iValue != oCargoData12.iValue) assert(0);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey2, &oCargoData22);

  if(oCargoData21.dValue != oCargoData22.dValue) assert(0);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int Test_VectorSys_Heap (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

    sstRec02VectSysCls *oDssDataSys;

    sstRec02CargoKeyInternCls *oDssDataKey1;
    sstRec02CargoKeyInternCls *oDssDataKey2;

    sstRec02TestRec1Cls oCargoData11;
    sstRec02TestRec1Cls oCargoData12;
    sstRec02TestRec2Cls oCargoData21;
    sstRec02TestRec2Cls oCargoData22;

    oDssDataSys = new (sstRec02VectSysCls);

    oDssDataKey1 = new (sstRec02CargoKeyInternCls);
    oDssDataKey2 = new (sstRec02CargoKeyInternCls);

    iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData11), (char*) "XXX", oDssDataKey1);

  if(iStat != 0)  {    assert(0);  }

  oCargoData11.iValue = 55;
  strncpy(oCargoData11.cVal,"abc", 5);

  iStat = oDssDataSys->WrtCargo ( 0, oDssDataKey1, &oCargoData11);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey1, &oCargoData12);

  if(oCargoData11.iValue != oCargoData12.iValue) assert(0);

  iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData21), (char*) "YYY", oDssDataKey2);

  iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData21), (char*) "ZZZ", oDssDataKey2);

  oCargoData21.dValue = 55.5;
  strncpy(oCargoData21.cVal,"dcba", 10);

  iStat = oDssDataSys->WrtCargo ( 0, oDssDataKey2, &oCargoData21);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey1, &oCargoData12);

  if(oCargoData11.iValue != oCargoData12.iValue) assert(0);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey2, &oCargoData22);

  if(oCargoData21.dValue != oCargoData22.dValue) assert(0);

  delete(oDssDataKey2);
  delete(oDssDataKey1);

  delete(oDssDataSys);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
