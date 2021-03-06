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
sstRec02VectSysCls::sstRec02VectSysCls()
{
  this->ulVectorSize = 0;
  this->vVectorAdr = NULL;
  this->iNumCargoSys = 0;
  this->MemAdr = NULL;
}
//=============================================================================
sstRec02VectSysCls::~sstRec02VectSysCls()
{
  if (this->MemAdr != NULL) free(this->MemAdr);
  if (this->vVectorAdr != NULL) free(this->vVectorAdr);
}
//=============================================================================
int sstRec02VectSysCls::AddCargoSys( int             iKey,
                                     unsigned int    uiSize,
                                     char           *cCargoNam,
                                     sstRec02CargoKeyInternCls *oCargoKey)
//-----------------------------------------------------------------------------
{
  int iStat = 0;

  if ( iKey != 0) return -1;  // Wrong Key
  if ( uiSize <= 0) return -2;  // Cargo Packet must not be empty
  iStat = strlen(cCargoNam);  // Cargo Name has to be length 3
  if(iStat !=3) return -3;
  if (oCargoKey->iKey != 0) return -4;   // Cargo Key should be emtpy

  // is new cargo sys name unique?
  for (int ii=1; ii<=this->iNumCargoSys; ii++)
  {
    iStat = strncmp(this->MemAdr[ii-1].GetCargoSysNam(), cCargoNam, 4);
    if (iStat == 0) return -5;
  }

  int iCargoOffs = 0;
  void *Adr = NULL;

  this->iNumCargoSys++;

  // === Handle cargo array memory
  if (iNumCargoSys == 1)  // first cargo
  {
    iStat = sizeof(sstRec02CargoMemCls);
    Adr = calloc( iStat,1);
    if (Adr <= NULL) assert(0);
    this->MemAdr = (sstRec02CargoMemCls*) Adr;
    this->MemAdr[this->iNumCargoSys-1].SetOffset(0);
  }
  else
  {  // next cargo memory
    iStat = this->iNumCargoSys * sizeof(sstRec02CargoMemCls);
    Adr = realloc(this->MemAdr , iStat);
    if (Adr <= NULL) assert(0);
    this->MemAdr = (sstRec02CargoMemCls*) Adr;
    this->MemAdr[this->iNumCargoSys-1].SetOffset(this->ulVectorSize);
  }

  this->MemAdr[this->iNumCargoSys-1].SetCargoSize( uiSize);
  this->MemAdr[this->iNumCargoSys-1].SetCargoSysNam(cCargoNam);

  // === Handle Vector memory
  this->ulVectorSize = this->ulVectorSize + uiSize;
  if (iNumCargoSys == 1)
  {
    Adr = calloc( this->ulVectorSize,1);
    if (Adr <= NULL) assert(0);
  }
  else
  {
    Adr = realloc(this->vVectorAdr ,this->ulVectorSize);
    if (Adr <= NULL) assert(0);

  }
  this->vVectorAdr = Adr;

  // Recalculate all cargo adresses in vector
  iCargoOffs = 0;
  for (int ii=1;ii<=iNumCargoSys;ii++)
  {
    this->CalcSetPos ( this->vVectorAdr, &Adr, iCargoOffs);
    this->MemAdr[ii-1].SetCargoAdr(Adr);
    iCargoOffs = iCargoOffs + this->MemAdr[ii-1].GetCargoSize();
  }

  // set cargo key
  oCargoKey->iKey = iNumCargoSys;
  strncpy(oCargoKey->iNam,cCargoNam,4);
  oCargoKey->oCargoAdr = this;

  return 0;
}
//=============================================================================
int sstRec02VectSysCls::WrtCargo ( int              iKey,
                                   sstRec02CargoKeyInternCls *oDataKey,
                                   void            *CargoAdr)
{
  sstRec02CargoMemCls *oCargoArrayRec;
  int iStat = 0;
  if ( iKey != 0) return -1;

  // Check Adress of Cargo System
  if (oDataKey->oCargoAdr != this) return -2;

  // Check Name of Cargo System
  iStat = strncmp( oDataKey->iNam, this->MemAdr[oDataKey->iKey-1].GetCargoSysNam(),4);
  if (iStat != 0) return -3;

  // Copy Cargo into Vector at cargo position
  unsigned long ulSize = this->MemAdr[oDataKey->iKey-1].GetCargoSize();

  oCargoArrayRec = this->MemAdr;

  for(int ii=1;ii<=oDataKey->iKey-1;ii++)
  {
    oCargoArrayRec++;
  }

  memcpy(this->MemAdr[oDataKey->iKey-1].GetCargoAdr(), CargoAdr, ulSize);

  return 0;
}
//=============================================================================
int sstRec02VectSysCls::RedCargo ( int              iKey,
                                   sstRec02CargoKeyInternCls *oDataKey,
                                   void            *CargoAdr)
{
  int iStat = 0;

  if ( iKey != 0) return -1;

  if (oDataKey->oCargoAdr != this) return -2;

  iStat = strncmp( oDataKey->iNam, this->MemAdr[oDataKey->iKey-1].GetCargoSysNam(),4);
  if (iStat != 0) return -3;

  memcpy( CargoAdr, this->MemAdr[oDataKey->iKey-1].GetCargoAdr(), this->MemAdr[oDataKey->iKey-1].GetCargoSize());

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
int sstRec02VectSysCls::GetCargoAdr(int                iKey,
                                  sstRec02CargoKeyInternCls   *oDataKey,
                                  void             **vCargoAdr)
{
  int iStat = 0;

  if ( iKey != 0) return -1;

  if (oDataKey->oCargoAdr != this) return -2;

  iStat = strncmp( oDataKey->iNam, this->MemAdr[oDataKey->iKey-1].GetCargoSysNam(),4);
  if (iStat != 0) return -3;

  *vCargoAdr = this->MemAdr[oDataKey->iKey-1].GetCargoAdr();
  return 0;
}

//=============================================================================
int sstRec02VectSysCls::GetOffset (int                iKey,
                                 sstRec02CargoKeyInternCls   *oDataKey,
                                 int               *iOffset)
{
  int iStat = 0;

  if ( iKey != 0) return -1;

  if (oDataKey->oCargoAdr != this) return -2;

  iStat = strncmp( oDataKey->iNam, this->MemAdr[oDataKey->iKey-1].GetCargoSysNam(),4);
  if (iStat != 0) return -3;

  *iOffset = this->MemAdr[oDataKey->iKey-1].GetOffset();
  return 0;
}
//=============================================================================
void sstRec02VectSysCls::ResetMem(int iKey)
{
  if ( iKey == 0) memset( this->vVectorAdr, 0, this->ulVectorSize);
}
//=============================================================================


