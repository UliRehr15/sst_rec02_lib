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

class sstRec02InternCls;
class sstRec02CargoKeyInternCls;

//------------------------------------------------------------------------------


//==============================================================================
/**
* @brief Identification Key for cargo packets
*
* Changed: 16.10.15  Re.
*
* @ingroup sstRecord02Lib
*
* @author Re.
*
* @date 16.10.15
*/
// ----------------------------------------------------------------------------
class sstRec02CargoKeyCls
{
  public:   // Public functions
     sstRec02CargoKeyCls();  // Constructor
    ~sstRec02CargoKeyCls();  // Destructor

     sstRec02CargoKeyInternCls *poCargoKeyIntern;   /**< Pointer to intern object */

};
//==============================================================================
/**
* @brief sst Record Memory Vers. 2 sstRec02Cls
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
    * @brief sstRec constructor with size of one record
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
  dREC02RECNUMTYP count();
  //==============================================================================
  /**
  * @brief // Write new record into sstRec memory <BR>
  * iStat = oRecMem.WritNew(iKey, *vRecAdr, *dPosition);
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
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Wrong Record positon
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Writ(int iKey, void* vRecAdr, dREC02RECNUMTYP dPosition);
  //==============================================================================
  /**
  * @brief // Read record from sstRec memory with Record number <BR>
  * iStat = oRecMem.Read( iKey, dPosition, *vRecAdr);
  *
  * @param iKey      [in]  For the moment 0
  * @param dPosition [in]  record number to read
  * @param vRecAdr   [out] read Record to record adress
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Wrong Record positon
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Read(int iKey, dREC02RECNUMTYP dPosition, void *vRecAdr);
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
  //=============================================================================
  /**
  * @brief // Add cargo system to sstRec memory and get new identification key <BR>
  * iStat = oRecMem.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
  *
  * @param iKey      [in]  For the moment 0
  * @param uiSize    [in]  Size of cargo record
  * @param cCargoNam [in]  Name of cargo system (3 Letters)
  * @param oCargoKey [out] key of new cargo object
  *
  * @return Errorstate
  *
  * @retval   =   0: OK
  * @retval   =  -1: Wrong Key
  * @retval   =  -2: Cargo Packet must not be empty
  * @retval   =  -3: Cargo Name has to be length 3
  * @retval   =  -4: Cargo Key should be empty
  * @retval   =  -5: Cargo Name should be unique
  * @retval   = -10: sstRecMem is not empty
  * @retval   <   0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int AddCargoSys( int                  iKey,
                   unsigned int         uiSize,
                   char                *cCargoNam,
                   sstRec02CargoKeyCls *oCargoKey);
  //=============================================================================
  /**
  * @brief // write cargo packet to vector Memory <BR>
  * iStat = oRecMem.WrtCargo ( iKey, *oCargoKey, *vCargoAdr);
  *
  * @param iKey       [in]  For the moment 0
  * @param oCargoKey  [in]  identification key of cargo packet
  * @param vCargoAdr  [in]  adress of cargo packet
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Cargo key not OK for RecMem object
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int WrtCargo ( int                  iKey,
                 sstRec02CargoKeyCls *oCargoKey,
                 void                *vCargoAdr);
  //=============================================================================
  /**
  * @brief // Read cargo packet from vector memory  <BR>
  * iStat = oRecMem.RedCargo ( iKey, *oCargoKey, *vCargoAdr);
  *
  * @param iKey       [in]   For the moment 0
  * @param oCargoKey  [in]   identification key of cargo packet
  * @param vCargoAdr  [out]  Adress of cargo packet
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Cargo key not OK for RecMem object
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RedCargo ( int                  iKey,
                 sstRec02CargoKeyCls *oCargoKey,
                 void                *vCargoAdr);
  //==============================================================================
  /**
  * @brief // Set record state as deleted  for record dRecNo in RecMem  <BR>
  * iStat = oRecMem.RecSetDeleted ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RecSetDeleted ( int               iKey,
                      dREC02RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Set record state as marked  for record dRecNo in RecMem  <BR>
  * iStat = oRecMem.RecSetMarked ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RecSetMarked( int               iKey,
                     dREC02RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Set record state as undeleted  for record dRecNo in RecMem  <BR>
  * iStat = oRecMem.RecSetUndeleted ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RecSetUndeleted( int               iKey,
                        dREC02RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Set record state as unmarked for record dRecNo in RecMem  <BR>
  * iStat = oRecMem.RecSetUnmarked ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RecSetUnmarked( int               iKey,
                       dREC02RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Get delete state of record dRecNo  <BR>
  * iStat = oRecMem.RecGetDeleteState ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Delete State
  *
  * @retval   = true:  Record is deleted
  * @retval   = false: Record is undeleted
  */
  // ----------------------------------------------------------------------------
  bool RecGetDeleteStatus( int               iKey,
                           dREC02RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Get mark state of record dRecNo <BR>
  * iStat = oRecMem.RecGetMarkState ( iKey,  RecNo);
  *
  * @param iKey   [in]  For the moment 0
  * @param dRecNo [in]  record number
  *
  * @return Mark State
  *
  * @retval   = true : Record is marked
  * @retval   = false: Record is unmarked
  */
  // ----------------------------------------------------------------------------
  bool RecGetMarkStatus( int               iKey,
                         dREC02RECNUMTYP   dRecNo);
  //==============================================================================


private:
  sstRec02InternCls *poRec01Intern;   /**< Pointer to intern object */

};

//==============================================================================
/**
* @brief Small test record class
*
* Changed: 16.10.15 Re.
*
* @ingroup sstRecord02Lib
*
* @author Re.
*
* @date 16.10
*/
// ----------------------------------------------------------------------------
class sstRec02TestRec1Cls
{
  public:   // Public functions
     sstRec02TestRec1Cls();  // Constructor
     int iValue;        /**< Test Integer Value */
     char cVal[5];     /**< Test Character Value */

};
//==============================================================================
/**
* @brief Full test record class
*
* Changed: 16.10.15 Re.
*
* @ingroup sstRecord02Lib
*
* @author Re.
*
* @date 16.10.15
*/
// ----------------------------------------------------------------------------
class sstRec02TestRec2Cls
{
  public:   // Public functions
    sstRec02TestRec2Cls();  // Constructor
    int    iValue;          /**< Test Integer Value */
    unsigned int uiValue;   /**< Test Unsigned Value */
    double dValue;          /**< Test Double Value */
    char cVal[10];         /**< Test Character Value */
};
//==============================================================================

// Do some intern Tests
int sstRec02_DoSomeInternTests (int iKey);

#endif // SST_REC01_LIB
