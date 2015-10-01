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
#define dREC02FILNAMMAXLEN 260   /**< Maximal File Name Length    */


// Structures and Classes ------------------------------------------------------

//==============================================================================
/**
* @brief Definition Class sstRec02VectSysCls
*
* More Comment
*
* Changed: 01.10.15  Re.
*
* @ingroup sstRecord02InternLib
*
* @author Re.
*
* @date 01.10.15
*/
// ----------------------------------------------------------------------------
class sstRec02VectSysCls
{
  public:   // Öffentliche Funktionen
    //=============================================================================
    /**
    * @brief constructor for vector memory
    *
    * @param dSize [in]  size of vector memory
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
     sstRec02VectSysCls(dREC02RECSIZTYP dSize);  // Konstruktor
     ~sstRec02VectSysCls();  // Destruktor
     //=============================================================================
     /**
     * @brief write record to vector Memory
     *
     * @param iKey     [in]  For the moment 0
     * @param CargoAdr [in]  adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtCargo ( int    iKey,
                    void           *CargoAdr);

     //=============================================================================
     /**
     * @brief Read record from vector memory
     *
     * @param iKey     [in]  For the moment 0
     * @param CargoAdr [in]  Adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RedCargo ( int    iKey,
                    void           *CargoAdr);

     //=============================================================================
     /**
     * @brief Calculate new position in memory
     *
     * @param BasPtr [in]  Basis pointer
     * @param IdxPtr [out] Result pointer = Basis + offset
     * @param Offs   [in]  Offset
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void CalcSetPos ( void   *BasPtr,
                       void  **IdxPtr,
                       long    Offs);

     //=============================================================================
     /**
     * @brief Get size of vector
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     unsigned long GetSize() const;

     //=============================================================================
     /**
     * @brief Get adress of vector
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void* GetAdr() const;
     //=============================================================================
     /**
     * @brief reset memory of vector
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void ResetMem(int iKey);

  private:
    void            *vVectorAdr;     /**< main memory vector with all cargo values */
    unsigned long    ulVectorSize;  /**< size of main memory vector */
};
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
     sstRec01InternCls(dREC02RECSIZTYP Size);  // Constructor
    ~sstRec01InternCls();  // Destructor
     //==============================================================================
     /**
     * @brief // Write new record into intern sstRec memory <BR>
     * iStat = oRecMem.WritNewInt( iKey, vRecAdr, dRecNo);
     *
     * @param iKey    [in]  For the moment 0
     * @param vRecAdr [in]  Record to store
     * @param dRecNo  [out] New index number
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritNewInt(int iKey, void* vRecAdr, dREC02RECNUMTYP *dRecNo);
     //==============================================================================
     /**
     * @brief // Write new record with sstRec vector <BR>
     * iStat = oRecMem.WritNewVector( iKey, vRecAdr, dRecNo);
     *
     * @param iKey    [in]  For the moment 0
     * @param vRecAdr [in]  Record to store
     * @param dRecNo  [out] New index number
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritNewVector(int iKey, void* vRecAdr, dREC02RECNUMTYP *dRecNo);
     //==============================================================================
     /**
     * @brief // Write Record at position in intern sstRec Memory  <BR>
     * iStat = oRecMem.WritInt( iKey, *vRecAdr,  dRecNo);
     *
     * @param iKey    [in] For the moment 0
     * @param vRecAdr [in] Adress of record
     * @param dRecNo  [in] target position to write record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Wrong Record positon
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritInt(int iKey, void* vRecAdr, dREC02RECNUMTYP dRecNo);
     //==============================================================================
     /**
     * @brief // Write Record at position with sstRec vector  <BR>
     * iStat = oRecMem.WritVector( iKey, *vRecAdr, dRecNo);
     *
     * @param iKey    [in] For the moment 0
     * @param vRecAdr [in] Adress of record
     * @param dRecNo  [in] target position to write record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Wrong Record positon
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritVector(int iKey, void* vRecAdr, dREC02RECNUMTYP dRecNo);
     //==============================================================================
     /**
     * @brief // Read record from sstRec memory with Record number <BR>
     * iStat = oRecMem.ReadInt( iKey, dRecNo, *vRecAdr);
     *
     * @param iKey    [in] For the moment 0
     * @param dRecNo  [in] record number to read
     * @param vRecAdr [out read record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Wrong Record positon
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadInt(int iKey, dREC02RECNUMTYP dRecNo, void *vRecAdr);
     //==============================================================================
     /**
     * @brief // Read record from sstRec memory with Record number and vector <BR>
     * iStat = oRecMem.ReadVector( iKey, dRecNo, *vRecAdr);
     *
     * @param iKey    [in] For the moment 0
     * @param dRecNo  [in] record number to read
     * @param vRecAdr [out read record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Wrong Record positon
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadVector(int iKey, dREC02RECNUMTYP dRecNo, void *vRecAdr);
     //==============================================================================
     /**
     * @brief return number of stored records in sstRec memory
     *
     * @return number of records, which are stored
     */
     // ----------------------------------------------------------------------------
     dREC02RECNUMTYP count();
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
    dREC02RECSIZTYP size;         /**< Size of each record */
    dREC02RECNUMTYP quantity;     /**< Number of storage spaces */
    dREC02RECNUMTYP dActStored;   /**< Number of stored records */
    unsigned char* storage;       /**< Dynamically allocated array of bytes */
    FILE*          FilHdl;        /**< File Handle: If not NULL, store in file   */
    bool           bFileNotDelete;  /**< Do File not delete   */
    char cDatnam[dREC02FILNAMMAXLEN]; /**< Filename for storing record data   */
    sstRec02VectSysCls *oVector;  /**< Intern memory space for vector            */
};

//==============================================================================

#endif

// --------------------------------------------------------------- File End ----
