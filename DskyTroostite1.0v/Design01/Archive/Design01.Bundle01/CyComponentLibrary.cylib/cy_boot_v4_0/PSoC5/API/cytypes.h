/*******************************************************************************
* FILENAME: cytypes.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*  CyTypes provides register access macros and approved types for use in
*  firmware.
*
*  Note:
*  Due to endiannesses of the hardware and some compilers, the register
*  access macros for big endian compilers use some library calls to arrange
*  data the correct way.
*
*  Register Access macros and functions perform their operations on an
*  input of type pointer to void.  The arguments passed to it should be
*  pointers to the type associated with the register size.
*  (i.e. a "uint8 *" shouldn't be passed to obtain a 16-bit register value)
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOT_CYTYPES_H)
#define CY_BOOT_CYTYPES_H

#if defined(__C51__)
    #include <intrins.h>
#endif  /* (__C51__) */

/* ARM and C99 or later */
#if defined(__GNUC__) || defined(__ARMCC_VERSION) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
    #include <stdint.h>
#endif  /* (__GNUC__) || defined(__ARMCC_VERSION) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) */

#include "cyfitter.h"


#if defined( __ICCARM__ )
    /* Suppress warning for multiple volatile variables in an expression. */
    /* This is common in component code and the usage is not order dependent. */
    #pragma diag_suppress=Pa082
#endif  /* defined( __ICCARM__ ) */


/***************************************
* Conditional Compilation Parameters
***************************************/


/*******************************************************************************
* FAMILY encodes the overall architectural family
*******************************************************************************/
#define CY_PSOC3 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
#define CY_PSOC4 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4)
#define CY_PSOC5 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5)


/*******************************************************************************
* MEMBER encodes both the family and the detailed architecture
*******************************************************************************/
#define CY_PSOC4A  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4A)
#ifdef CYDEV_CHIP_MEMBER_4D
    #define CY_PSOC4D   (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4D)
    #define CY_PSOC4SF  (CY_PSOC4D)
#else
    #define CY_PSOC4D   (0u != 0u)
    #define CY_PSOC4SF  (CY_PSOC4D)
#endif  /* CYDEV_CHIP_MEMBER_4D */

#define CY_PSOC5A  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)
#ifdef CYDEV_CHIP_MEMBER_5B
    #define CY_PSOC5LP  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5B)
#else
    #define CY_PSOC5LP  (0u != 0u)
#endif  /* CYDEV_CHIP_MEMBER_5B */


/*******************************************************************************
* UDB revisions
*******************************************************************************/
#define CY_UDB_V0 (CY_PSOC5A)
#define CY_UDB_V1 (!CY_UDB_V0)


/*******************************************************************************
*   Base Types. Acceptable types from MISRA-C specifying signedness and size.
*******************************************************************************/
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed   char   int8;
typedef signed   short  int16;
typedef signed   long   int32;
typedef          float  float32;

#if(!CY_PSOC3)

    typedef               double float64;
    typedef          long long   int64;
    typedef unsigned long long   uint64;

#endif  /* (!CY_PSOC3) */

/* Signed or unsigned depending on the compiler selection */
typedef          char   char8;


/*******************************************************************************
*   Memory address functions prototypes
*******************************************************************************/
#if(CY_PSOC3)

    /***************************************************************************
    * Prototypes for absolute memory address functions (cymem.a51) with built-in
    * endian conversion. These functions should be called through the
    * CY_GET_XTND_REGxx and CY_SET_XTND_REGxx macros.
    ***************************************************************************/
    extern uint8  cyread8       (const volatile void far *addr);
    extern void   cywrite8      (volatile void far *addr, uint8 value);

    extern uint16 cyread16      (const volatile void far *addr);
    extern uint16 cyread16_nodpx(const volatile void far *addr);

    extern void   cywrite16      (volatile void far *addr, uint16 value);
    extern void   cywrite16_nodpx(volatile void far *addr, uint16 value);

    extern uint32 cyread24      (const volatile void far *addr);
    extern uint32 cyread24_nodpx(const volatile void far *addr);

    extern void   cywrite24      (volatile void far *addr, uint32 value);
    extern void   cywrite24_nodpx(volatile void far *addr, uint32 value);

    extern uint32 cyread32      (const volatile void far *addr);
    extern uint32 cyread32_nodpx(const volatile void far *addr);

    extern void   cywrite32      (volatile void far *addr, uint32 value);
    extern void   cywrite32_nodpx(volatile void far *addr, uint32 value);


    /***************************************************************************
    * Memory access routines from cymem.a51 for the generated device
    * configuration code. These functions may be subject to change in future
    * revisions of the cy_boot component and they are not available for all
    * devices. Most code should use memset or memcpy instead.
    ***************************************************************************/
    void cymemzero(void far *addr, uint16 size);
    void cyconfigcpy(uint16 size, const void far *src, void far *dest) large;
    void cyconfigcpycode(uint16 size, const void code *src, void far *dest);

    #define CYCONFIGCPY_DECLARED    (1)

#else

    /* Prototype for function to set a 24-bit register. Located at cyutils.c */
    extern void     CySetReg24(uint32 volatile * addr, uint32 value);

    #if(CY_PSOC4)

        extern uint32 CyGetReg24(uint32 const volatile * addr);

    #endif  /* (CY_PSOC4) */

#endif  /* (CY_PSOC3) */


/*******************************************************************************
*   Memory model definitions. To allow code to be 8051-ARM agnostic.
*******************************************************************************/
#if(CY_PSOC3)

    #define CYBDATA     bdata
    #define CYBIT       bit
    #define CYCODE      code
    #define CYCOMPACT   compact
    #define CYDATA      data
    #define CYFAR       far
    #define CYIDATA     idata
    #define CYLARGE     large
    #define CYPDATA     pdata
    #define CYREENTRANT reentrant
    #define CYSMALL     small
    #define CYXDATA     xdata
    #define XDATA       xdata

    #define CY_NOINIT

#else

    #define CYBDATA
    #define CYBIT      uint8
    #define CYCODE
    #define CYCOMPACT
    #define CYDATA
    #define CYFAR
    #define CYIDATA
    #define CYLARGE
    #define CYPDATA
    #define CYREENTRANT
    #define CYSMALL
    #define CYXDATA
    #define XDATA

    #if defined(__ARMCC_VERSION)
        #define CY_NOINIT           __attribute__ ((section(".noinit"), zero_init))
        #define CY_NORETURN         __attribute__ ((noreturn))
        #define CY_SECTION(name)    __attribute__ ((section(name)))
        #define CY_ALIGN(align)     __align(align)
    #elif defined (__GNUC__)
        #define CY_NOINIT           __attribute__ ((section(".noinit")))
        #define CY_NORETURN         __attribute__ ((noreturn))
        #define CY_SECTION(name)    __attribute__ ((section(name)))
        #define CY_ALIGN(align)     __attribute__ ((aligned(align)))
    #elif defined (__ICCARM__)
        #define CY_NOINIT           __no_init
        #define CY_NORETURN         __noreturn
    #endif  /* (__ARMCC_VERSION) */

#endif  /* (CY_PSOC3) */


#if(CY_PSOC3)

    /* 8051 naturally returns an 8 bit value. */
    typedef unsigned char cystatus;

#else

    /* ARM naturally returns a 32 bit value. */
    typedef unsigned long cystatus;

#endif  /* (CY_PSOC3) */


/*******************************************************************************
*  Hardware Register Types.
*******************************************************************************/
typedef volatile uint8  CYXDATA reg8;
typedef volatile uint16 CYXDATA reg16;
typedef volatile uint32 CYXDATA reg32;


/*******************************************************************************
*  Interrupt Types and Macros
*******************************************************************************/
#if(CY_PSOC3)

    #define CY_ISR(FuncName)        void FuncName (void) interrupt 0
    #define CY_ISR_PROTO(FuncName)  void FuncName (void)
    typedef void (CYCODE * cyisraddress)(void);

#else

    #define CY_ISR(FuncName)        void FuncName (void)
    #define CY_ISR_PROTO(FuncName)  void FuncName (void)
    typedef void (* cyisraddress)(void);

    #if defined (__ICCARM__)
        typedef union { cyisraddress __fun; void * __ptr; } intvec_elem;
    #endif  /* defined (__ICCARM__) */

#endif  /* (CY_PSOC3) */


/*******************************************************************************
*  Register Access
*******************************************************************************/
#if(CY_PSOC3)


    /*******************************************************************************
    * KEIL for the 8051 is a big endian compiler This causes problems as the on chip
    * registers are little endian.  Byte swapping for two and four byte registers is
    * implemented in the functions below.  This will require conditional compilation
    * of function prototypes in code.
    *******************************************************************************/

    /* Access macros for 8, 16, 24 and 32-bit registers, IN THE FIRST 64K OF XDATA */

    #define CY_GET_REG8(addr)               (*((const reg8 *)(addr)))
    #define CY_SET_REG8(addr, value)        (*((reg8 *)(addr))  = (uint8)(value))

    #define CY_GET_REG16(addr)              cyread16_nodpx ((const volatile void far *)(const reg16 *)(addr))
    #define CY_SET_REG16(addr, value)       cywrite16_nodpx((volatile void far *)(reg16 *)(addr), value)

    #define CY_GET_REG24(addr)              cyread24_nodpx ((const volatile void far *)(const reg32 *)(addr))
    #define CY_SET_REG24(addr, value)       cywrite24_nodpx((volatile void far *)(reg32 *)(addr),value)

    #define CY_GET_REG32(addr)              cyread32_nodpx ((const volatile void far *)(const reg32 *)(addr))
    #define CY_SET_REG32(addr, value)       cywrite32_nodpx((volatile void far *)(reg32 *)(addr), value)

    /* Access 8, 16, 24 and 32-bit registers, ABOVE THE FIRST 64K OF XDATA */
    #define CY_GET_XTND_REG8(addr)          cyread8((const volatile void far *)(addr))
    #define CY_SET_XTND_REG8(addr, value)   cywrite8((volatile void far *)(addr), value)

    #define CY_GET_XTND_REG16(addr)         cyread16((const volatile void far *)(addr))
    #define CY_SET_XTND_REG16(addr, value)  cywrite16((volatile void far *)(addr), value)

    #define CY_GET_XTND_REG24(addr)         cyread24((const volatile void far *)(addr))
    #define CY_SET_XTND_REG24(addr, value)  cywrite24((volatile void far *)(addr), value)

    #define CY_GET_XTND_REG32(addr)         cyread32((const volatile void far *)(addr))
    #define CY_SET_XTND_REG32(addr, value)  cywrite32((volatile void far *)(addr), value)

#else

    /* 8, 16, 24 and 32-bit register access macros */
    #define CY_GET_REG8(addr)               (*((const reg8 *)(addr)))
    #define CY_SET_REG8(addr, value)        (*((reg8 *)(addr))  = (uint8)(value))

    #define CY_GET_REG16(addr)              (*((const reg16 *)(addr)))
    #define CY_SET_REG16(addr, value)       (*((reg16 *)(addr)) = (uint16)(value))


    #define CY_SET_REG24(addr, value)       CySetReg24((reg32 *) (addr), (value))
    #if(CY_PSOC4)
        #define CY_GET_REG24(addr)          CyGetReg24((const reg32 *) (addr))
    #else
        #define CY_GET_REG24(addr)          (*((const reg32 *)(addr)) & 0x00FFFFFFu)
    #endif  /* (CY_PSOC4) */


    #define CY_GET_REG32(addr)              (*((const reg32 *)(addr)))
    #define CY_SET_REG32(addr, value)       (*((reg32 *)(addr)) = (uint32)(value))


    /* To allow code to be 8051-ARM agnostic. */
    #define CY_GET_XTND_REG8(addr)          CY_GET_REG8(addr)
    #define CY_SET_XTND_REG8(addr, value)   CY_SET_REG8(addr, value)

    #define CY_GET_XTND_REG16(addr)         CY_GET_REG16(addr)
    #define CY_SET_XTND_REG16(addr, value)  CY_SET_REG16(addr, value)

    #define CY_GET_XTND_REG24(addr)         CY_GET_REG24(addr)
    #define CY_SET_XTND_REG24(addr, value)  CY_SET_REG24(addr, value)

    #define CY_GET_XTND_REG32(addr)         CY_GET_REG32(addr)
    #define CY_SET_XTND_REG32(addr, value)  CY_SET_REG32(addr, value)

#endif  /* (CY_PSOC3) */



/*******************************************************************************
*  Data manipulation defines
*******************************************************************************/

/* Get 8 bits of a 16 bit value. */
#define LO8(x)                  ((uint8) ((x) & 0xFFu))
#define HI8(x)                  ((uint8) ((uint16)(x) >> 8))

/* Get 16 bits of a 32 bit value. */
#define LO16(x)                 ((uint16) ((x) & 0xFFFFu))
#define HI16(x)                 ((uint16) ((uint32)(x) >> 16))

/* Swap the byte ordering of a 32 bit value */
#define CYSWAP_ENDIAN32(x)  \
        ((uint32)(((x) >> 24) | (((x) & 0x00FF0000u) >> 8) | (((x) & 0x0000FF00u) << 8) | ((x) << 24)))

/* Swap the byte ordering of a 16 bit value */
#define CYSWAP_ENDIAN16(x)      ((uint16)(((x) << 8) | ((x) >> 8)))


/*******************************************************************************
* Defines the standard return values used PSoC content. A function is
* not limited to these return values but can use them when returning standard
* error values. Return values can be overloaded if documented in the function
* header. On the 8051 a function can use a larger return type but still use the
* defined return codes.
*
* Zero is successful, all other values indicate some form of failure. 1 - 0x7F -
* standard defined values; 0x80 - ...  - user or content defined values.
*******************************************************************************/
#define CYRET_SUCCESS           (0x00u)           /* Successful */
#define CYRET_BAD_PARAM         (0x01u)           /* One or more invalid parameters */
#define CYRET_INVALID_OBJECT    (0x02u)           /* Invalid object specified */
#define CYRET_MEMORY            (0x03u)           /* Memory related failure */
#define CYRET_LOCKED            (0x04u)           /* Resource lock failure */
#define CYRET_EMPTY             (0x05u)           /* No more objects available */
#define CYRET_BAD_DATA          (0x06u)           /* Bad data received (CRC or other error check) */
#define CYRET_STARTED           (0x07u)           /* Operation started, but not necessarily completed yet */
#define CYRET_FINISHED          (0x08u)           /* Operation completed */
#define CYRET_CANCELED          (0x09u)           /* Operation canceled */
#define CYRET_TIMEOUT           (0x10u)           /* Operation timed out */
#define CYRET_INVALID_STATE     (0x11u)           /* Operation not setup or is in an improper state */
#define CYRET_UNKNOWN           ((cystatus) 0xFFFFFFFFu)    /* Unknown failure */


/*******************************************************************************
*   Intrinsic Defines: Processor NOP instruction
*******************************************************************************/
#if(CY_PSOC3)

    #define CY_NOP          _nop_()

#else

    #if defined(__ARMCC_VERSION)

        /* RealView */
        #define CY_NOP      __nop()

    #else

        /* GCC */
        #define CY_NOP      __asm("NOP\n")

    #endif  /* defined(__ARMCC_VERSION) */

#endif  /* (CY_PSOC3) */


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from cy_boot 3.10
*******************************************************************************/

/* Device is PSoC 3 and the revision is ES2 or earlier */
#define CY_PSOC3_ES2 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* Device is PSoC 3 and the revision is ES3 or later */
#define CY_PSOC3_ES3 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
    (CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* Device is PSoC 5 and the revision is ES1 or earlier */
#define CY_PSOC5_ES1 (CY_PSOC5A && \
    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* Device is PSoC 5 and the revision is ES2 or later */
#define CY_PSOC5_ES2 (CY_PSOC5A && \
    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

#endif  /* CY_BOOT_CYTYPES_H */


/* [] END OF FILE */
