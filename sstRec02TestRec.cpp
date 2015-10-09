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
// sstRec02TestRec.cpp    06.10.15  Re.    06.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//==============================================================================
sstRec02TestRec1Cls::sstRec02TestRec1Cls()
{
  this->iValue = 0;
  memset(this->cVal,0,sizeof(this->cVal));
}
//==============================================================================
sstRec02TestRec2Cls::sstRec02TestRec2Cls()
{
  this->iValue = 0;
  this->uiValue = 0;
  this->dValue = 0.0;
  memset(this->cVal,0,sizeof(this->cVal));
}
//==============================================================================
