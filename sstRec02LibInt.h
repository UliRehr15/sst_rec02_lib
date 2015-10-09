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
* @brief Definition Class DssCargoMem_Cls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord02InternLib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstRec02CargoMemCls
{
  public:   // Öffentliche Funktionen
     sstRec02CargoMemCls();  // Konstruktor
     ~sstRec02CargoMemCls();  // Destruktor
     //==============================================================================
     /**
     * @brief return Offset
     *
     * @return Offset
     */
     // ----------------------------------------------------------------------------
     int GetOffset();
     //==============================================================================
     /**
     * @brief Set Offset
     *
     * @param iOffset [in] Offset
     */
     // ----------------------------------------------------------------------------
     void SetOffset(int iOffset);
     //==============================================================================
     /**
     * @brief return Cargo Size
     *
     * @return Cargo Size
     */
     // ----------------------------------------------------------------------------
     int GetCargoSize();
     //==============================================================================
     /**
     * @brief Set Cargo Size
     *
     * @param iSize [in] Cargo Size
     */
     // ----------------------------------------------------------------------------
     void SetCargoSize(int iSize);
     //==============================================================================
     /**
     * @brief return adress of cargo name char
     *
     * @return adress of cargo name char
     */
     // ----------------------------------------------------------------------------
     char* GetCargoSysNam();
     //==============================================================================
     /**
     * @brief set cargo name
     *
     * @param cNam [in] adress of cargo name char
     */
     // ----------------------------------------------------------------------------
     void SetCargoSysNam(char *cNam);
     //==============================================================================
     /**
     * @brief get cargo adress
     *
     * @return cargo adress
     */
     // ----------------------------------------------------------------------------
     void* GetCargoAdr();
     //==============================================================================
     /**
     * @brief set cargo adress
     *
     * @param vCargoAdr [in] adress of cargo
     */
     // ----------------------------------------------------------------------------
     void SetCargoAdr(void *vCargoAdr);
     //==============================================================================
  private:  // Private Funktionen
     int iOffset;           /**< Offset from Start of vector */
     int iSize;             /**< Size of cargo sys*/
     char cNam[4];          /**< Name of cargo sys */
     void *CargoAdr;        /**< Adress in vector memory */
};


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
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
     sstRec02VectSysCls();
     ~sstRec02VectSysCls();
     //=============================================================================
     /**
     * @brief // Add cargo system to vector memory and get new identification key <BR>
     * iStat = oVector.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
     *
     * @param iKey      [in]  For the moment 0
     * @param uiSize    [in]  Size of cargo record
     * @param cCargoNam [in]  Name of cargo system (4 Letters)
     * @param oCargoKey [out] key of new cargo object
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Cargo Packet must not be empty
     * @retval   = -3: Cargo Name has to be length 3
     * @retval   = -4: Cargo Key should be empty
     * @retval   = -5: Cargo Name should be unique
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int AddCargoSys( int             iKey,
                      unsigned int    uiSize,
                      char           *cCargoNam,
                      sstRec02CargoKeyInternCls *oCargoKey);
     //=============================================================================
     /**
     * @brief write record to vector Memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  adress of cargo record
     * @param vCargoAdr [in]  adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Cargo key not OK for RecMem object
     * @retval    < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtCargo ( int              iKey,
                    sstRec02CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);

     //=============================================================================
     /**
     * @brief Read record from vector memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  Adress of cargo record
     * @param vCargoAdr [in]  Adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Cargo key not OK for RecMem object
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RedCargo ( int              iKey,
                    sstRec02CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);

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
     * @brief Get Adress of cargo system
     *
     * @param iKey      [in]     For the moment 0
     * @param oDataKey  [in out] Key of cargo object
     * @param vCargoAdr [out]    Adress of cargo system
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetCargoAdr (int               iKey,
                      sstRec02CargoKeyInternCls  *oDataKey,
                      void            **vCargoAdr);
     //=============================================================================
     /**
     * @brief Get offset of cargo system
     *
     * @param iKey     [in]     For the moment 0
     * @param oDataKey [in out] Key of cargo object
     * @param iOffset  [out]    offset of cargo object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetOffset (int                iKey,
                    sstRec02CargoKeyInternCls   *oDataKey,
                    int               *iOffset);
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
    int              iNumCargoSys;  /**< Number of Cargo Systems */
    sstRec02CargoMemCls *MemAdr;        /**< Field of of Cargo Systems */
    void            *vVectorAdr;     /**< main memory vector with all cargo values */
    unsigned long    ulVectorSize;  /**< size of main memory vector */
};
//-----------------------------------------------------------------------------
/**
* @brief Definition Class DssCargoKey_Cls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord02InternLib
*
* @author Re.
*
* @date 19.02.10
*/
//==============================================================================
class sstRec02CargoKeyInternCls
{
  public:   // Öffentliche Funktionen
     sstRec02CargoKeyInternCls();  // Konstruktor
     ~sstRec02CargoKeyInternCls();  // Destruktor
     int  iKey;           /**< Key of cargo sys */
     char iNam[4];        /**< Name of cargo sys*/
     sstRec02VectSysCls *oCargoAdr;  /**< Adress of cargo object  */
  private:  // Private Funktionen
     // int iDummy;
};
//-----------------------------------------------------------------------------
///**
//* @brief Definition Class Cargo_Cls
//*
//* More Comment
//*
//* Changed: 19.02.10  Re.
//*
//* @ingroup sstDss2_Lib
//*
//* @author Re.
//*
//* @date 19.02.10
//*/
//// ----------------------------------------------------------------------------
//class sstRec02CargoCls
//{
//  public:   // Öffentliche Funktionen
//     sstRec02CargoCls();  // Konstruktor
//    ~sstRec02CargoCls();  // Destruktor
//  private:  // Private Funktionen
//     void *Adr;              /**< adress in memory  */
//     unsigned int uiSize;    /**< Size ??  */
//     char cNam[4];           /**< USR, SYS, TRE, LL1, LL2, LL3  */
//};
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
class sstRec02InternCls
{
  public:   // Public functions
    //==============================================================================
    /**
    * @brief constructor with size of one record
    *
    * @param Size [in] Size of one record
    */
    // ----------------------------------------------------------------------------
     sstRec02InternCls(dREC02RECSIZTYP Size);  // Constructor
    ~sstRec02InternCls();  // Destructor
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
     /**
     * @brief // Add cargo system to sstRec memory and get new identification key <BR>
     * iStat = oRecMem.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
     *
     * @param iKey      [in]  For the moment 0
     * @param uiSize    [in]  Size of cargo record
     * @param cCargoNam [in]  Name of cargo system (4 Letters)
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
                      sstRec02CargoKeyInternCls *oCargoKey);
     //=============================================================================
     /**
     * @brief write record to vector Memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  adress of cargo record
     * @param vCargoAdr [in]  adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Cargo key not OK for RecMem object
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtCargo ( int              iKey,
                    sstRec02CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);
     //=============================================================================
     /**
     * @brief Read record from vector memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  Identification Key
     * @param vCargoAdr [in]  Adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =  0: OK
     * @retval   = -1: Wrong Key
     * @retval   = -2: Cargo key not OK for RecMem object
     * @retval   <  0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RedCargo ( int              iKey,
                    sstRec02CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);
     //=============================================================================

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
    // dREC02RECSIZTYP dUsrSize;     /**< Size of each user record */
    dREC02RECNUMTYP quantity;     /**< Number of storage spaces */
    dREC02RECNUMTYP dActStored;   /**< Number of stored records */
    unsigned char* storage;       /**< Dynamically allocated array of bytes */
    FILE*          FilHdl;        /**< File Handle: If not NULL, store in file   */
    bool           bFileNotDelete;  /**< Do File not delete   */
    char cDatnam[dREC02FILNAMMAXLEN]; /**< Filename for storing record data   */
    sstRec02VectSysCls *oVector;  /**< Intern memory space for vector            */
    sstRec02CargoKeyInternCls *oDssUsrKey;
};
//==============================================================================
// iStat = Test_VectorSys_Stack ( iKey);
int Test_VectorSys_Stack (int iKey);

// iStat = Test_VectorSys_Heap ( iKey);
int Test_VectorSys_Heap (int iKey);
//==============================================================================

#endif

// --------------------------------------------------------------- File End ----
