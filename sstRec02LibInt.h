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
// sstRec01LibInt.h   13.09.15  Re.   13.09.15  Re.
//
// Intern Datastructures and Prototypes for system "sstRec01Lib"
//

#ifndef   _SST_REC02_LIB_INT_HEADER
#define   _SST_REC02_LIB_INT_HEADER

/**
 * @defgroup sstRecord02InternLib sstRecord02InternLib: Intern cpp sst record library
 *
 * Intern cpp sst record library <BR>
 *
 */


// Defines ---------------------------------------------------------------------

/**
 * @brief Maximal File Name Length
 * @ingroup sstRecord02InternLib
 */
#define dREC01FILNAMNAXLEN 260   /**< Maximal File Name Length    */


// Structures and Classes ------------------------------------------------------

//==============================================================================
/**
* @brief Definition Class sstRec01InternCls
*
* Intern class for sstRecordLib <BR>
*
* Changed: 04.08.15  Re.
*
* @ingroup sstRecord02InternLib
*
* @author Re.
*
* @date 09.07.15
*/
// ----------------------------------------------------------------------------
class sstRec01InternCls
{
  public:   // Public functions
    //==============================================================================
    /**
    * @brief constructor with size of one record
    *
    * @param Size [in] Size of one record
    */
    // ----------------------------------------------------------------------------
     sstRec01InternCls(dREC01RECSIZTYP Size);  // Constructor
    ~sstRec01InternCls();  // Destructor
     //==============================================================================
     /**
     * @brief Write new record into sstRec memory
     *
     * @param iKey    [in]  For the moment 0
     * @param element [in]  Record to store
     * @param index   [out] New index number
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritNew(int iKey, void* element, dREC01RECNUMTYP *index);
     //==============================================================================
     /**
     * @brief Read record from sstRec memory with Record number
     *
     * @param iKey  [in] For the moment 0
     * @param index [in] record number to read
     * @param vAdr  [out read record
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Read(int iKey, dREC01RECNUMTYP index, void *vAdr);
     //==============================================================================
     /**
     * @brief return number of stored records in sstRec memory
     *
     * @return number of records, which are stored
     */
     // ----------------------------------------------------------------------------
     int count();
     //==============================================================================
     /**
     * @brief Open existing or new file of record storing
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
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int OpenFile(int   iKey,
                  char *cSysNam);
     //==============================================================================
     /**
     * @brief Open new file of record storing
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
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int NewFile(int   iKey,
                 char *cSysNam);
     //==============================================================================
     /**
     * @brief Store record data in file
     *
     * @param iKey  [in]  For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: No File open
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetStoreFile(int iKey);
     //==============================================================================
  private:  // Private functions
     //==============================================================================
     /**
     * @brief Shortstory
     *
     * @param iKey [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
    void inflate(int increase);
    //==============================================================================
    dREC01RECSIZTYP size;     /**< Size of each record */
    dREC01RECNUMTYP quantity; /**< Number of storage spaces */
    dREC01RECNUMTYP next;     /**< Number of stored records */
    unsigned char* storage;   /**< Dynamically allocated array of bytes */
    FILE*          FilHdl;    /**< File Handle: If not NULL, store in file   */
    bool           bFileNotDelete;  /**< Do File not delete   */
    char cDatnam[dREC01FILNAMNAXLEN]; /**< Filename for storing record data   */


};

#endif

// --------------------------------------------------------------- File End ----
