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
// sstRec02Int.cpp    13.09.15  Re.    13.09.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
sstRec02InternCls::sstRec02InternCls(dREC02RECSIZTYP dRecSize)
{
    quantity = 0;
    storage = 0;
    dActStored = 0;
    FilHdl = NULL;
    bFileNotDelete = 0;  // Default: File will be deleted

    this->oDssUsrKey = new (sstRec02CargoKeyInternCls);
    this->oVector = new sstRec02VectSysCls();

    int iStat = this->oVector->AddCargoSys( 0, dRecSize, (char*) "USR", this->oDssUsrKey);
    assert(iStat >= 0);

}
//=============================================================================
sstRec02InternCls::~sstRec02InternCls()
{

    delete (this->oDssUsrKey);
    delete (this->oVector);

    if(storage) {
      puts("freeing storage");
      free(storage);
    }

    if (this->FilHdl != 0)
    {
        // Close File
        int iStat= fclose( this->FilHdl);
        assert(iStat >= 0);

        if(!this->bFileNotDelete)
        {
            // Remove file from disk
            iStat = remove ( this->cDatnam);
            assert(iStat >= 0);
        }
    }
}
//=============================================================================
int sstRec02InternCls::WritNewInt(int iKey, void* element, dREC02RECNUMTYP *index)
{

  if ( iKey != 0) return -1;

  if(this->FilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->FilHdl, (this->dActStored) * this->oVector->GetSize(), SEEK_SET);
    fwrite (element, this->oVector->GetSize(), 1, this->FilHdl);

  }
  else
  {
      if(dActStored >= quantity) // Enough space left?
        inflate(100);
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(storage[dActStored * this->oVector->GetSize()]),
              element,
              this->oVector->GetSize());
  }

  dActStored++;
  *index = dActStored;

  return 0;
}
//=============================================================================
int sstRec02InternCls::WritNewVector(int iKey, void* vRecAdr, dREC02RECNUMTYP *dRecNo)
{
    // write record into vector memory
    int iStat = this->oVector->WrtCargo( 0, this->oDssUsrKey, vRecAdr);

    // Write new record into intern sstRec memory
    iStat = this->WritNewInt( iKey, this->oVector->GetAdr(), dRecNo);
    return iStat;
}

//=============================================================================
int sstRec02InternCls::WritInt(int iKey, void* vRecAdr, dREC02RECNUMTYP index)
{
  if ( iKey != 0) return -1;
  if (index <= 0 || index > dActStored) return -2;

  if(this->FilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->FilHdl, index * this->oVector->GetSize(), SEEK_SET);
    fwrite (vRecAdr, this->oVector->GetSize(), 1, this->FilHdl);

  }
  else
  {
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(storage[(index-1) * this->oVector->GetSize()]), vRecAdr, this->oVector->GetSize());
  }

  return 0;
}
//=============================================================================
int sstRec02InternCls::WritVector(int iKey, void* vRecAdr, dREC02RECNUMTYP dRecNo)
{

    // write record into vector memory
    int iStat = this->oVector->WrtCargo( 0, this->oDssUsrKey, vRecAdr);

    // Write Record at position in intern sstRec Memory
    iStat = this->WritInt( iKey, this->oVector->GetAdr(), dRecNo);
    return iStat;
}
//=============================================================================
int sstRec02InternCls::ReadInt(int iKey, dREC02RECNUMTYP index, void *vAdr)
{
    if ( iKey != 0) return -1;
    if(index <= 0 || index > dActStored) return -2;

  if(this->FilHdl != 0)
  {
    fseek (this->FilHdl, (index-1) * this->oVector->GetSize(), SEEK_SET);
    fread (vAdr, this->oVector->GetSize(), 1, this->FilHdl);
  }
  else
  {
      void *vLocAdr = NULL;

      // if(index >= next || index < 0)
      if(index > dActStored)
        return -2;  // Not out of bounds?

      // Produce pointer to desired element:
      vLocAdr = (void*) &(storage[(index-1) * this->oVector->GetSize()]);

      // copy one record data to given record adress
      memcpy( vAdr, vLocAdr, this->oVector->GetSize());
  }

  return 0;
}
//=============================================================================
int sstRec02InternCls::ReadVector(int iKey, dREC02RECNUMTYP dRecNo, void *vRecAdr)
{
    // Read record from sstRec memory with Record number
    int iStat = this->ReadInt( iKey, dRecNo, this->oVector->GetAdr());

    // Read record from vector memory
    if (iStat >= 0) iStat = this->oVector->RedCargo( 0, this->oDssUsrKey, vRecAdr);

    return iStat;
}
//=============================================================================
dREC02RECNUMTYP sstRec02InternCls::count() {
  return dActStored; // Number of actual stored records
}
//==============================================================================
int sstRec02InternCls::OpenFile(int   iKey,
                                char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->FilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC02FILNAMMAXLEN) <= 0) return -3;
  if (this->dActStored > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC02FILNAMMAXLEN);
  strncat(cDatnam, ".rec", dREC02FILNAMMAXLEN);

  // Reoopen existing or open new file for binary Reading/Writing
  this->FilHdl = fopen( cDatnam, "a+b");
  assert( this->FilHdl != NULL);

  fseek (this->FilHdl, 0, SEEK_END);
  long lSize = ftell(this->FilHdl);

  // Calculate number of existing records in file
  this->dActStored = lSize / this->oVector->GetSize();

  return 0;
}
//==============================================================================
int sstRec02InternCls::NewFile(int   iKey,
                               char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->FilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC02FILNAMMAXLEN) <= 0) return -3;
  if (this->dActStored > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC02FILNAMMAXLEN);
  strncat(cDatnam, ".rec", dREC02FILNAMMAXLEN);

  // Open new file for binary Reading/Writing
  this->FilHdl = fopen( cDatnam, "w+b");
  assert( this->FilHdl != NULL);

  return 0;
}
//==============================================================================
int sstRec02InternCls::SetStoreFile(int iKey)
{
  if ( iKey != 0) return -1;
  this->bFileNotDelete = 1;
  return 0;
}
//=============================================================================
void sstRec02InternCls::inflate(int increase) {
  void* v = realloc(storage, (quantity+increase) * this->oVector->GetSize());
  assert(v);  // Was it successful?
  storage = (unsigned char*)v;
  quantity += increase;
}
//=============================================================================
int sstRec02InternCls::AddCargoSys( int                  iKey,
                              unsigned int         uiSize,
                              char                *cCargoNam,
                              sstRec02CargoKeyInternCls *oCargoKey)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    if (this->count()!= 0) return -10;

    iStat = this->oVector->AddCargoSys(iKey,uiSize,cCargoNam,oCargoKey);

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}

//==============================================================================
int sstRec02InternCls::WrtCargo ( int              iKey,
                            sstRec02CargoKeyInternCls *oDataKey,
                            void            *vCargoAdr)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    iStat = this->oVector->WrtCargo(0,oDataKey,vCargoAdr);

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}
//==============================================================================
int sstRec02InternCls::RedCargo ( int              iKey,
                            sstRec02CargoKeyInternCls *oDataKey,
                            void            *vCargoAdr)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    iStat = this->oVector->RedCargo(0,oDataKey,vCargoAdr);

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}
//==============================================================================


