/**********************************************************************
 *
 * sst_rec_lib - library for working with data records
 * Hosted on github
 *
 * Copyright (C) 2014 Hans Ulrich Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstRec02Lib.h   13.09.15  Re.   13.09.15  Re.
//
// Datastructures and Prototypes for system "sstRec02Lib"
//

#ifndef   _SST_REC02_LIB_HEADER
#define   _SST_REC02_LIB_HEADER

/**
 * @defgroup sstRecord02Lib sstRecord02Lib: cpp sst record library (Version 2)
 *
 * cpp sst record library <BR>
 *
 */

// Defines ---------------------------------------------------------------------

/**
 * @brief Record Number Type
 * @ingroup sstRecord02Lib
 */
// typedef int  dREC02RECNUMTYP;    /**< Record Number Type    */
// typedef unsigned int  dREC02RECNUMTYP;    /**< Record Number Type    */
// typedef long  dREC02RECNUMTYP;    /**< Record Number Type    */
typedef unsigned long  dREC02RECNUMTYP;    /**< Record Number Type: Int, Unsigned, Long, Unsigned Long   */

/**
 * @brief Record Size Type
 * @ingroup sstRecord02Lib
 */
// typedef int  dREC02RECNUMTYP;    /**< Record Number Type    */
// typedef unsigned int  dREC02RECNUMTYP;    /**< Record Number Type    */
// typedef long  dREC02RECNUMTYP;    /**< Record Number Type    */
typedef unsigned long  dREC02RECSIZTYP;    /**< Record Size Type: Int, Unsigned, Long, Unsigned Long  */


// forward declaration ---------------------------------------------------------

class sstRec01InternCls;

//------------------------------------------------------------------------------


//==============================================================================
/**
* @brief Definition sstRec02Cls
*
* record storage <BR>
*
* Changed: 04.08.15  Re.
*
* @ingroup sstRecord02Lib
*
* @author Re.
*
* @date 09.07.15
*/
// ----------------------------------------------------------------------------
class sstRec02Cls {
public:
    //==============================================================================
    /**
    * @brief stash constructor with size of one record
    *
    * @param Size [in] Size of one record
    */
    // ----------------------------------------------------------------------------
  sstRec02Cls(dREC02RECSIZTYP Size);
  ~sstRec02Cls();
  //==============================================================================
  /**
  * @brief Get number of stored records
  *
  * @return number of elements in stash memory
  */
  // ----------------------------------------------------------------------------
  int count();
  //==============================================================================
  /**
  * @brief // Write new record into sstRec memory <BR>
  * iStat = oRecMem.WritNew(iKey, vRecAdr, *dPosition);
  *
  * @param iKey      [in]  For the moment 0
  * @param vRecAdr   [in]  adress of Record to store
  * @param dPosition [out] New Positon of new Record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int WritNew(int iKey, void* vRecAdr, dREC02RECNUMTYP *dPosition);
  //==============================================================================
  /**
  * @brief // Write Record at postion in sstRec Memory <BR>
  * iStat = oRecMem.Writ( iKey, *vRecAdr, dPosition);
  *
  * @param iKey      [in] For the moment 0
  * @param vRecAdr   [in] Adress of record
  * @param dPosition [in] target position to write record
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Writ(int iKey, void* vRecAdr, dREC02RECNUMTYP dPosition);
  //==============================================================================
  /**
  * @brief Read record from sstRec memory with Record number
  *
  * @param iKey  [in]  For the moment 0
  * @param index [in]  record number to read
  * @param vAdr  [out] read Record
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Read(int iKey, dREC02RECNUMTYP index, void *vAdr);
  //==============================================================================
  /**
  * @brief open file with name or create new file
  *
  * @param iKey    [in]  For the moment 0
  * @param cSysNam [in]  File Name
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: File already open
  * @retval   = -3: Filename empty
  * @retval   = -4: sstRec not empty
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int OpenFile(int   iKey,
               char *cSysNam);
  //==============================================================================
  /**
  * @brief open new file
  *
  * @param iKey    [in]  For the moment 0
  * @param cSysNam [in]  File Name
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: File already open
  * @retval   = -3: Filename empty
  * @retval   = -4: sstRec not empty
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int NewFile(int   iKey,
              char *cSysNam);
  //==============================================================================
  /**
  * @brief Set file data store
  *
  * @param iKey  [in]  For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int SetStoreFile(int iKey);
  //==============================================================================
private:
  sstRec01InternCls *poRec01Intern;   /**< Pointer to intern object */

};

#endif // SST_REC01_LIB
