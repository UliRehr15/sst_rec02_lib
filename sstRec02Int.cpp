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
sstRec01InternCls::sstRec01InternCls(dREC01RECSIZTYP Size)
{
    size = Size;
    quantity = 0;
    storage = 0;
    next = 0;
    FilHdl = NULL;
    bFileNotDelete = 0;  // Default: File will be deleted
}
//=============================================================================
sstRec01InternCls::~sstRec01InternCls()
{
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
int sstRec01InternCls::WritNew(int iKey, void* element, dREC01RECNUMTYP *index)
{

  if ( iKey != 0) return -1;

  //int iStat = 0;

  if(this->FilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->FilHdl, (this->next) * this->size, SEEK_SET);
    fwrite (element, this->size, 1, this->FilHdl);

  }
  else
  {
      if(next >= quantity) // Enough space left?
        inflate(100);
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(storage[next * size]),
             element, size);

  }

  next++;
  *index = next-1;

  return 0;
}
//=============================================================================
int sstRec01InternCls::Read(int iKey, dREC01RECNUMTYP index, void *vAdr)
{
  if ( iKey != 0) return -1;

  if(this->FilHdl != 0)
  {
    fseek (this->FilHdl, (index)*this->size, SEEK_SET);
    fread (vAdr, this->size, 1, this->FilHdl);
  }
  else
  {
      void *vLocAdr = NULL;

      // if(index >= next || index < 0)
      if(index >= next)
        return -2;  // Not out of bounds?
      // Produce pointer to desired element:
      vLocAdr = (void*) &(storage[index * size]);

      // copy one record data to given record adress
      memcpy( vAdr, vLocAdr, size);
  }

  return 0;  //  &(storage[index * size]);
}
//=============================================================================
//void* sstRec01InternCls::fetch(dREC01RECNUMTYP index)
//{
//  // Not out of bounds?
//  //  if ( index >= next || index < 0)
//    if ( index >= next)
//    return 0;
//  // Produce pointer to desired element
//  return &(storage[index * size]);
//}
//=============================================================================
int sstRec01InternCls::count() {
  return next; // Number of elements in stash
}
//==============================================================================
int sstRec01InternCls::OpenFile(int   iKey,
                                char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->FilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC01FILNAMNAXLEN) <= 0) return -3;
  if (this->next > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC01FILNAMNAXLEN);
  strncat(cDatnam, ".rec", dREC01FILNAMNAXLEN);

  // Reoopen existing or open new file for binary Reading/Writing
  this->FilHdl = fopen( cDatnam, "a+b");
  assert( this->FilHdl != NULL);

  fseek (this->FilHdl, 0, SEEK_END);
  long lSize = ftell(this->FilHdl);

  // Calculate number of existing records in file
  this->next = lSize / this->size;

  return 0;
}
//==============================================================================
int sstRec01InternCls::NewFile(int   iKey,
                               char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->FilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC01FILNAMNAXLEN) <= 0) return -3;
  if (this->next > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC01FILNAMNAXLEN);
  strncat(cDatnam, ".rec", dREC01FILNAMNAXLEN);

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


