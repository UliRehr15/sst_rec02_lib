/**********************************************************************
 *
 * sst_rec02_lib - library for working with data records
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
// sstRec02Vector.cpp    24.09.15  Re.    24.09.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
sstRec02VectSysCls::sstRec02VectSysCls(dREC02RECSIZTYP dVecSize)
{
  this->ulVectorSize = dVecSize;
  this->vVectorAdr = NULL;

  vVectorAdr = calloc( dVecSize,1);
  assert(vVectorAdr != NULL);

}
//=============================================================================
sstRec02VectSysCls::~sstRec02VectSysCls()
{
  if (this->vVectorAdr != NULL) free(this->vVectorAdr);
}
//=============================================================================
int sstRec02VectSysCls::WrtCargo ( int     iKey,
                                 void   *vRecAdr)
{
  if ( iKey != 0) return -1;

  memcpy(this->vVectorAdr, vRecAdr, this->ulVectorSize);

  return 0;
}
//=============================================================================
int sstRec02VectSysCls::RedCargo ( int      iKey,
                                 void    *vRecAdr)
{
  if ( iKey != 0) return -1;

  memcpy( vRecAdr, this->vVectorAdr, this->ulVectorSize);

  return 0;
}
//=============================================================================
void sstRec02VectSysCls::CalcSetPos ( void   *BasPtr,
                                    void  **IdxPtr,
                                    long    Offs)
//-----------------------------------------------------------------------------
{
  unsigned char *xxx;

//.............................................................................
  xxx = (unsigned char*) BasPtr;
  xxx = xxx + Offs;
  (*IdxPtr) = (void*) xxx;
}
//=============================================================================
unsigned long sstRec02VectSysCls::GetSize() const
{
  return this->ulVectorSize;
}
//=============================================================================
void* sstRec02VectSysCls::GetAdr() const
{
  return this->vVectorAdr;
}
//=============================================================================
void sstRec02VectSysCls::ResetMem(int iKey)
{
  if ( iKey == 0) memset( this->vVectorAdr, 0, this->ulVectorSize);
}
//=============================================================================


