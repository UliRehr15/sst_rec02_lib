/**********************************************************************
 *
 * sstRec02Lib - cpp template library for sst
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
// sstRec02CargoKey.cpp    28.09.15  Re.    28.09.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec02Lib.h"
#include "sstRec02LibInt.h"

//=============================================================================
sstRec02CargoKeyCls::sstRec02CargoKeyCls()
{
    this->poCargoKeyIntern = new(sstRec02CargoKeyInternCls);
}
//=============================================================================
sstRec02CargoKeyCls::~sstRec02CargoKeyCls()
{
    delete(this->poCargoKeyIntern);
}
//=============================================================================
