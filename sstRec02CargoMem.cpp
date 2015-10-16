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
// sstRec02CargoMem.cpp    16.10.15  Re.    16.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
sstRec02CargoMemCls::sstRec02CargoMemCls()
{
  memset( &(*this), 0, sizeof((*this)));
}
//=============================================================================
sstRec02CargoMemCls::~sstRec02CargoMemCls()
{

}
//=============================================================================
int sstRec02CargoMemCls::GetOffset()
{
  return this->iOffset;
}
//=============================================================================
void sstRec02CargoMemCls::SetOffset(int iTmpOffset)
{
  this->iOffset = iTmpOffset;
}
//=============================================================================
int sstRec02CargoMemCls::GetCargoSize()
{
  return this->iSize;
}
//=============================================================================
void sstRec02CargoMemCls::SetCargoSize(int iTmpSize)
{
  this->iSize = iTmpSize;
}
//=============================================================================
char* sstRec02CargoMemCls::GetCargoSysNam()
{
  return this->cNam;
}
//=============================================================================
void sstRec02CargoMemCls::SetCargoSysNam(char *cTmpNam)
{
  strncpy(this->cNam,cTmpNam,4);
}
//=============================================================================
void* sstRec02CargoMemCls::GetCargoAdr()
{
  return this->CargoAdr;
}
//=============================================================================
void sstRec02CargoMemCls::SetCargoAdr(void *vTmpCargoAdr)
{
  this->CargoAdr = vTmpCargoAdr;
}
//=============================================================================



