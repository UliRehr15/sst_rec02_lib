/**********************************************************************
 *
 * sstTemplateLib - cpp template library for sst
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
// sstTemplateLib.cpp    13.07.15  Re.    08.07.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstTemplateLib.h"
#include "sstTemplateLibInt.h"

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int Blanko (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Fatal Errors goes to an assert

  // Pipe |
  // Smaller <
  // Greater >

  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
sstTestBaseCls::sstTestBaseCls()
{

}
//=============================================================================
sstTestInterfaceCls::sstTestInterfaceCls()
{
    poTestIntern = new(sstTestBaseInternCls);
}
//=============================================================================
sstTestInterfaceCls::~sstTestInterfaceCls()
{
    delete(poTestIntern);
}
//=============================================================================
sstTestBaseInternCls::sstTestBaseInternCls()
{

}
//=============================================================================

