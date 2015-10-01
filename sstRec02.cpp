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
// sstRec02Lib.cpp    13.09.15  Re.    13.09.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//==============================================================================
sstRec02Cls::sstRec02Cls(dREC02RECSIZTYP Size) {
  poRec01Intern = new sstRec01InternCls(Size);
}
//==============================================================================
sstRec02Cls::~sstRec02Cls() {
    delete(poRec01Intern);
}
//==============================================================================
int sstRec02Cls::WritNew(int iKey, void* vRecAdr, dREC02RECNUMTYP *pdRecNo) {

    return poRec01Intern->WritNewVector( iKey, vRecAdr, pdRecNo);
}
//==============================================================================
int sstRec02Cls::Writ(int iKey, void* vRecAdr, dREC02RECNUMTYP dRecNo)
{
  return poRec01Intern->WritVector( iKey, vRecAdr, dRecNo);
}

//==============================================================================
int sstRec02Cls::Read(int iKey, dREC02RECNUMTYP dRecNo, void *vRecAdr) {
    int iStat = poRec01Intern->ReadVector( iKey, dRecNo, vRecAdr);
    return iStat;
}
//==============================================================================
dREC02RECNUMTYP sstRec02Cls::count() {
    return poRec01Intern->count();
}
//==============================================================================
int sstRec02Cls::OpenFile(int   iKey,
                    char *cSysNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  iStat = this->poRec01Intern->OpenFile(iKey,cSysNam);
  return iStat;
}
//==============================================================================
int sstRec02Cls::NewFile(int   iKey,
                   char *cSysNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  iStat = this->poRec01Intern->NewFile(iKey,cSysNam);
  return iStat;
}
//==============================================================================
int sstRec02Cls::SetStoreFile(int iKey)
{
  if ( iKey != 0) return -1;
  int iStat = this->poRec01Intern->SetStoreFile(iKey);
  return iStat;
}
//==============================================================================
