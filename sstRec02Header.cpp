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
// sstRec02Header.cpp    12.10.15  Re.    12.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
sstRec02HeaderCls::sstRec02HeaderCls()
{
  strncpy(cVersionstring,(char*)"sstRec02",10);    /**< Version String, for exampe sstRec02 */
  dRecSize = 0;  /**< Size of every Record */
  memset( cRecChgDateTime, 0, 18);    /**< Write Change Date, for exampe 151012 */
  memset( cRecNewDateTime, 0, 18);    /**< Write New Date, for exampe 151012 */
  bDel = 0;    /**< Delete Flag */
  bMark = 0;   /**< Mark Flag */
}
//=============================================================================
dREC02RECSIZTYP sstRec02HeaderCls::getRecSize() const
{
  return this->dRecSize;
}
//=============================================================================
void sstRec02HeaderCls::setRecSize(const dREC02RECSIZTYP &dTmpValue)
{
  this->dRecSize = dTmpValue;
}
//=============================================================================
char* sstRec02HeaderCls::GetVersStr()
{
  return this->cVersionstring;
}
//=============================================================================
void sstRec02HeaderCls::SetVersStr(char *cTmpNam)
{
  strncpy(this->cVersionstring,cTmpNam,10);
}
//=============================================================================
void sstRec02HeaderCls::SetNewDate()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d.%X", &tstruct);
  strncpy(this->cRecNewDateTime,buf,18);
}
//=============================================================================
void sstRec02HeaderCls::SetChangeDate()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d.%X", &tstruct);
  strncpy(this->cRecChgDateTime,buf,18);
}
//==============================================================================
void sstRec02HeaderCls::RecSetDeleted()
{
  this->bDel = true;
}
//==============================================================================
void sstRec02HeaderCls::RecSetMarked()
{
  this->bMark = true;
}
//==============================================================================
void sstRec02HeaderCls::RecSetUndeleted()
{
  this->bDel = false;
}
//==============================================================================
void sstRec02HeaderCls::RecSetUnmarked()
{
  this->bMark = false;
}
//==============================================================================
bool sstRec02HeaderCls::RecGetDeleteStatus()
{
  return this->bDel;
}
//==============================================================================
bool sstRec02HeaderCls::RecGetMarkStatus()
{
  return this->bMark;
}
//==============================================================================
