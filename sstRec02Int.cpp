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
sstRec01InternCls::sstRec01InternCls(dREC02RECSIZTYP dRecSize)
{
    size = dRecSize;
    quantity = 0;
    storage = 0;
    dActStored = 0;
    FilHdl = NULL;
    bFileNotDelete = 0;  // Default: File will be deleted
    this->oVector = new sstRec02VectSysCls(dRecSize);
}
//=============================================================================
sstRec01InternCls::~sstRec01InternCls()
{

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
int sstRec01InternCls::WritNewInt(int iKey, void* element, dREC02RECNUMTYP *index)
{

  if ( iKey != 0) return -1;

  if(this->FilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->FilHdl, (this->dActStored) * this->size, SEEK_SET);
    fwrite (element, this->size, 1, this->FilHdl);

  }
  else
  {
      if(dActStored >= quantity) // Enough space left?
        inflate(100);
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(storage[dActStored * size]), element, size);
  }

  dActStored++;
  *index = dActStored;

  return 0;
}
//=============================================================================
int sstRec01InternCls::WritNewVector(int iKey, void* vRecAdr, dREC02RECNUMTYP *dRecNo)
{
    // write record into vector memory
    int iStat = this->oVector->WrtCargo( 0, vRecAdr);

    // Write new record into intern sstRec memory
    iStat = this->WritNewInt( iKey, this->oVector->GetAdr(), dRecNo);
    return iStat;
}

//=============================================================================
int sstRec01InternCls::WritInt(int iKey, void* vRecAdr, dREC02RECNUMTYP index)
{
  if ( iKey != 0) return -1;
  if (index <= 0 || index > dActStored) return -2;

  if(this->FilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->FilHdl, index * this->size, SEEK_SET);
    fwrite (vRecAdr, this->size, 1, this->FilHdl);

  }
  else
  {
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(storage[(index-1) * size]), vRecAdr, size);
  }

  return 0;
}
//=============================================================================
int sstRec01InternCls::WritVector(int iKey, void* vRecAdr, dREC02RECNUMTYP dRecNo)
{

    // write record into vector memory
    int iStat = this->oVector->WrtCargo( 0, vRecAdr);

    // Write Record at position in intern sstRec Memory
    iStat = this->WritInt( iKey, this->oVector->GetAdr(), dRecNo);
    return iStat;
}
//=============================================================================
int sstRec01InternCls::ReadInt(int iKey, dREC02RECNUMTYP index, void *vAdr)
{
    if ( iKey != 0) return -1;
    if(index <= 0 || index > dActStored) return -2;

  if(this->FilHdl != 0)
  {
    fseek (this->FilHdl, (index-1)*this->size, SEEK_SET);
    fread (vAdr, this->size, 1, this->FilHdl);
  }
  else
  {
      void *vLocAdr = NULL;

      // if(index >= next || index < 0)
      if(index >= dActStored)
        return -2;  // Not out of bounds?
      // Produce pointer to desired element:
      vLocAdr = (void*) &(storage[(index-1) * size]);

      // copy one record data to given record adress
      memcpy( vAdr, vLocAdr, size);
  }

  return 0;
}
//=============================================================================
int sstRec01InternCls::ReadVector(int iKey, dREC02RECNUMTYP dRecNo, void *vRecAdr)
{
    // Read record from sstRec memory with Record number
    int iStat = this->ReadInt( iKey, dRecNo, this->oVector->GetAdr());

    // Read record from vector memory
    if (iStat >= 0) iStat = this->oVector->RedCargo( 0, vRecAdr);

    return iStat;
}
//=============================================================================
dREC02RECNUMTYP sstRec01InternCls::count() {
  return dActStored; // Number of actual stored records
}
//==============================================================================
int sstRec01InternCls::OpenFile(int   iKey,
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
  this->dActStored = lSize / this->size;

  return 0;
}
//==============================================================================
int sstRec01InternCls::NewFile(int   iKey,
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
int sstRec01InternCls::SetStoreFile(int iKey)
{
  if ( iKey != 0) return -1;
  this->bFileNotDelete = 1;
  return 0;
}
//=============================================================================
void sstRec01InternCls::inflate(int increase) {
  void* v =
    realloc(storage, (quantity+increase)*size);
  assert(v);  // Was it successful?
  storage = (unsigned char*)v;
  quantity += increase;
}
//=============================================================================


