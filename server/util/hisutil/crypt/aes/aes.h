
 /*
   -----------------------------------------------------------------------
   Copyright (c) 2001 Dr Brian Gladman <brg@gladman.uk.net>, Worcester, UK
   
   TERMS

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   This software is provided 'as is' with no guarantees of correctness or
   fitness for purpose.
   -----------------------------------------------------------------------

   1. OPERATION
 
   These source code files implement the AES algorithm Rijndael designed by
   Joan Daemen and Vincent Rijmen. The version in aes.c is designed for 
   block and key sizes of 128, 192 and 256 bits (16, 24 and 32 bytes) while 
   that in aespp.c provides for block and keys sizes of 128, 160, 192, 224 
   and 256 bits (16, 20, 24, 28 and 32 bytes).  This file is a common header 
   file for these two implementations and for aesref.c, which is a reference 
   implementation.
   
   This version is designed for flexibility and speed using operations on
   32-bit words rather than operations on bytes.  It provides aes_both fixed 
   and  dynamic block and key lengths and can also run with either big or 
   little endian internal byte order (see aes.h).  It inputs block and key 
   lengths in bytes with the legal values being  16, 24 and 32 for aes.c and 
   16, 20, 24, 28 and 32 for aespp.c
 
   2. THE CIPHER INTERFACE

   byte                 (an unsigned 8-bit type)
   word                 (an unsigned 32-bit type)
   rval:                (a signed 16 bit type for function return values)
        aes_good            (value != 0, a good return)
        aes_bad             (value == 0, an error return)
   enum mode:           (encryption direction)
        aes_enc             (set the key for encryption)
        aes_dec             (set the key for decryption)
        aes_both            (set the key for aes_both)
   class or struct ctx  (structure for the cipher context)

   A facility exists to allow these type names and the following C subroutine 
   names to be modified with specified prefixes to avoid naming conflicts. 

   C subroutine calls:

   rval set_blk(const word block_length, ctx *cx)  (variable block size)
   rval set_key(const byte key[], const word key_length,
                   const enum mode direction, ctx *cx)
   rval encrypt(const byte input_blk[], byte output_blk[], const ctx *cx)
   rval decrypt(const byte input_blk[], byte output_blk[], const ctx *cx)

   IMPORTANT NOTE: If you are using this C interface and your compiler does 
   not set the memory used for objects to zero before use, you will need to 
   ensure that cx.sflg is set to zero before using the C subroutine calls.

   C++ aes class subroutines:

   rval set_blk(const word block_length)  (variable block size)
   rval set_key(const byte key[], const word key_length,
                   const mode direction)
   rval encrypt(const byte input_blk[], byte output_blk[]) const
   rval decrypt(const byte input_blk[], byte output_blk[]) const

   The block length inputs to set_block and set_key are in numbers of
   BYTES, not bits.  The calls to subroutines must be made in the above 
   order but multiple calls can be made without repeating earlier calls
   if their parameters have not changed. If the cipher block length is
   variable but set_blk has not been called before cipher operations a
   value of 16 is assumed (that is, the AES block size). In contrast to 
   earlier versions the block and key length parameters are now checked
   for correctness and the encryption and decryption routines check to 
   ensure that an appropriate key has been set before they are called.

   3. BYTE ORDER WITHIN 32 BIT WORDS

   The fundamental data processing units in Rijndael are 8-bit bytes. The 
   input, the output and the key input are all enumerated arrays of bytes 
   in which bytes are numbered starting at zero and increasing to one less
   than the number of bytes in the array in question.  When these inputs 
   and outputs are considered as bit sequences, the n'th byte contains 
   bits 8n to 8n+7 of the sequence with the lower numbered bit mapped to 
   the most significant bit within the  byte (i.e. that having a numeric 
   value of 128).  However, Rijndael can be implemented more efficiently 
   using 32-bit words to process 4 bytes at a time provided that the order
   of bytes within words is known.  This order is called big-endian if the 
   lowest numbered bytes in words have the highest numeric significance 
   and little-endian if the opposite applies. This code can work in either 
   order irrespective of the native order of the machine on which it runs.
   The byte order used internally is set by defining INTERNAL_BYTE_ORDER
   whereas the order for all inputs and outputs is specified by defining 
   EXTERNAL_BYTE_ORDER, the only purpose of the latter being to determine
   if a byte order change is needed immediately after input and immediately
   before output to account for the use of a different internal byte order.  
   In almost all situations aes_both of these defines will be set to the
   native order of the processor on which the code is to run but other 
   settings may somtimes be useful in special circumstances.

#define INTERNAL_BYTE_ORDER AES_LITTLE_ENDIAN
#define EXTERNAL_BYTE_ORDER AES_LITTLE_ENDIAN

   4. COMPILATION 

   To compile AES (Rijndael) for use in C code
    a. Exclude the AES_DLL define in aes.h
    b. Exclude the AES_IN_CPP define in aes.h

   To compile AES (Rijndael) for use in in C++ code
    a. Exclude the AES_DLL define in aes.h
    b. Include the AES_IN_CPP define in aes.h

   To compile AES (Rijndael) in C as a Dynamic Link Library
    a. Include the AES_DLL define in aes.h
    b. Compile the DLL.  If using the test files, exclude aes.c from
       the test build project and compile it with the same defines 
       as used for the DLL (ensure that the DLL path is correct)

   6. CONFIGURATION OPTIONS (see also aes.c)

   a. define BLOCK_SIZE to set the cipher block size (16, 24 or 32) or
      leave this undefined for dynamically variable block size (this will
      result in much slower code).
   b. set AES_IN_CPP to use the code from C++ rather than C
   c. set AES_DLL if AES (Rijndael) is to be compiled to a DLL
   d. set INTERNAL_BYTE_ORDER to one of the above constants to set the
      internal byte order (the order used within the algorithm code)
   e. set EXTERNAL_BYTE_ORDER to one of the above constants to set the byte
      order used at the external interfaces for the input, output and key
      byte arrays.

   IMPORTANT NOTE: BLOCK_SIZE is in BYTES: 16, 24, 32 or undefined for aes.c
   and 16, 20, 24, 28, 32 or undefined for aespp.c.  If left undefined a 
   slower version providing variable block length is compiled   

#define BLOCK_SIZE  16

   Define AES_IN_CPP if you intend to use the AES C++ class rather than the
   C code directly.

#define AES_IN_CPP

   Define AES_DLL if you wish to compile the code to produce a Windows DLL

#define AES_DLL

   In C code a prefix can be added to the names of cipher subroutines that 
   are normally 'set_blk', 'set_key', 'encrypt' and 'decrypt'.  Hence if 
   NAME_PREFIX is defined its value will be prefixed to each name so that,
   for example:

#define NAME_PREFIX aes_

   will change these subroutine names to: 'aes_set_blk', 'aes_set_key', 
   'aes_encrypt' and 'aes_decrypt'.
 
   In C++ the class subroutine names will be not be prefixed but the C++ code
   will make use of calls to C subroutines using the prefixed names. In this 
   case if a prefix is not defined by the user, a prefix of 'aes_' is used.

   In both C and C++ a prefix can be added to the defined type names: 'byte', 
   'word', 'rval', 'mode' and (in C only) to the structure name 'ctx'. Hence 
   if TYPE_PREFIX is defined its value will be prefixed to each name so that,
   for example:
    
#define TYPE_PREFIX aes_

   will change these names to 'aes_byte', 'aes_word', 'aes_rval', 'aes_mode'
   and 'aes_ctx'.

*/

#ifndef _AES_H
#define _AES_H

#define AES_IN_CPP					// added by jae hyun,kim to use in cpp
#define BLOCK_SIZE  16				// 32 byte크기로 했을때보다 40배이상 빠르다. 아마도 key크기가 줄어서 그런것 같다..
#define TYPE_PREFIX aes_

#define AES_BIG_ENDIAN      1   /* do not change */
#define AES_LITTLE_ENDIAN   2   /* do not change */

#define INTERNAL_BYTE_ORDER AES_LITTLE_ENDIAN
#define EXTERNAL_BYTE_ORDER AES_LITTLE_ENDIAN

#if defined(BLOCK_SIZE) && ((BLOCK_SIZE & 3) || BLOCK_SIZE < 16 || BLOCK_SIZE > 32)
#error an illegal block size has been specified
#endif  

#if defined(AES_DLL)
#undef AES_IN_CPP
#endif

/* Adjust C subroutine names if required or if the C++ interface is being used */

#if defined(AES_IN_CPP) && !defined(NAME_PREFIX)
#define NAME_PREFIX aes_
#endif

#if defined(NAME_PREFIX)
#define c_name(x)   NAME_PREFIX##x
#else
#define c_name(x)   x
#endif

/* Adjust the type names if required to avoid naming conflicts  */

#if defined(TYPE_PREFIX)
#define t_name(x)   TYPE_PREFIX##x
#else
#define t_name(x)   x
#endif

 /*
   The number of key schedule words for different block and key lengths
   (allowing for the method of computation which requires the length to 
   be a multiple of the key length):

   Key Schedule    key length (bytes)
   Length          16  20  24  28  32
                ---------------------
   block     16 |  44  60  54  56  64
   length    20 |  60  60  66  70  80
   (bytes)   24 |  80  80  78  84  96
             28 | 100 100 102  98 112
             32 | 120 120 120 126 120

   Rcon Table      key length (bytes)
   Length          16  20  24  28  32
                ---------------------
   block     16 |  10   9   8   7   7
   length    20 |  14  11  10   9   9
   (bytes)   24 |  19  15  12  11  11
             28 |  24  19  16  13  13
             32 |  29  23  19  17  14
   
   The following values assume that the key length will be variable and may
   be of maximum length (32 bytes). 

   Nk = number_of_key_bytes / 4
   Nc = number_of_columns_in_state / 4
   Nr = number of encryption/decryption rounds
   Rc = number of elements in rcon table
   Ks = number of 32-bit words in key schedule
 */

#define Nr(Nk,Nc)   ((Nk > Nc ? Nk : Nc) + 6)
#define Rc(Nk,Nc)   ((Nb * (Nr(Nk,Nc) + 1) - 1) / Nk)   
#define Ks(Nk,Nc)   (Nk * (Rc(Nk,Nc) + 1))

#if !defined(BLOCK_SIZE)
#define RC_LENGTH    29
#define KS_LENGTH   128
#else
#define RC_LENGTH   5 * BLOCK_SIZE / 4 - (BLOCK_SIZE == 16 ? 10 : 11)
#define KS_LENGTH   4 * BLOCK_SIZE
#endif

/* End of configuration options, but see also aes.c */

typedef unsigned char   t_name(byte);   /* must be an 8-bit storage unit */
typedef unsigned long   t_name(word);   /* must be a 32-bit storage unit */
typedef short           t_name(rval);   /* function return value         */

#define aes_bad     0
#define aes_good    1

enum t_name(const)  {   Nrow =  4,  /* the number of rows in the cipher state       */
                        Mcol =  8,  /* maximum number of columns in the state       */
#if defined(BLOCK_SIZE)         /* set up a statically defined block size       */
                        Ncol =  BLOCK_SIZE / 4,  
                        Shr0 =  0,  /* the cyclic shift values for rows 0, 1, 2 & 3 */
                        Shr1 =  1,  
                        Shr2 =  BLOCK_SIZE == 32 ? 3 : 2,
                        Shr3 =  BLOCK_SIZE == 32 ? 4 : 3
#endif 
                    };

enum t_name(mode)   {   aes_enc  =  1,  /* set if encryption is needed */
                        aes_dec  =  2,  /* set if decryption is needed */
                        aes_both =  3   /* set if both are needed      */
                    };

#if defined(__cplusplus)
extern "C"
{
#endif

/* _stdcall is needed for Visual Basic DLLs but is not necessary for C/C++ */
 
#if defined(AES_DLL)
#define cf_dec  t_name(rval) __declspec(dllexport) _stdcall
#else
#define cf_dec  t_name(rval)
#endif

typedef struct
{
    t_name(word)    Nkey;               /* the number of words in the key input block */
    t_name(word)    Nrnd;               /* the number of cipher rounds                */
    t_name(word)    e_key[KS_LENGTH];   /* the encryption key schedule                */
    t_name(word)    d_key[KS_LENGTH];   /* the decryption key schedule                */
#if !defined(BLOCK_SIZE)
    t_name(word)    Ncol;               /* the number of columns in the cipher state  */
#endif
    t_name(byte)    sflg;               /* encrypt, decrypt or aes_both               */
} t_name(ctx);

cf_dec c_name(set_key)(const t_name(byte) key[], const t_name(word) n_bytes, const enum t_name(mode) f, t_name(ctx) *cx);
cf_dec c_name(encrypt)(const t_name(byte) in_blk[], t_name(byte) out_blk[], const t_name(ctx) *cx);
cf_dec c_name(decrypt)(const t_name(byte) in_blk[], t_name(byte) out_blk[], const t_name(ctx) *cx);
cf_dec c_name(set_blk)(const t_name(word) n_bytes, t_name(ctx) *cx);

#if defined(__cplusplus)
}

#if defined(AES_IN_CPP) 

class aes
{
    t_name(ctx) cx;
public:            
#if defined(BLOCK_SIZE)
    aes()   { cx.sflg = 0; }
#else     
    aes(t_name(word) n_bytes = 16)
            { cx.sflg = 0; c_name(set_blk)(n_bytes, &cx); }
    t_name(rval) set_blk(const t_name(word) n_bytes)
            { return c_name(set_blk)(n_bytes, &cx); }
#endif
    t_name(rval) set_key(const t_name(byte) key[], const t_name(word) n_bytes, const t_name(mode) f)
            { return c_name(set_key)(key, n_bytes, f, &cx); }
    t_name(rval) encrypt(const t_name(byte) in_blk[], t_name(byte) out_blk[]) const
            { return c_name(encrypt)(in_blk, out_blk, &cx); }
    t_name(rval) decrypt(const t_name(byte) in_blk[], t_name(byte) out_blk[]) const
            { return c_name(decrypt)(in_blk, out_blk, &cx); }
};

#endif
#endif

 /*
   upr(x,n): rotates bytes within words by n positions, moving bytes 
   to higher index positions with wrap around into low positions
   ups(x,n): moves bytes by n positions to higher index positions in 
   words but without wrap around
   bval(x,n): extracts a byte from a word
 */

#if (INTERNAL_BYTE_ORDER == AES_LITTLE_ENDIAN)

#define upr(x,n)        (((x) << 8 * (n)) | ((x) >> (32 - 8 * (n))))
#define ups(x,n)        ((x) << 8 * (n))
#define bval(x,n)       ((t_name(byte))((x) >> 8 * (n)))
#define byte_swap(x)    (upr(x,1) & 0x00ff00ff | upr(x,3) & 0xff00ff00)
#define bytes2word(b0, b1, b2, b3)  \
        ((t_name(word))(b3) << 24 | (t_name(word))(b2) << 16 | (t_name(word))(b1) << 8 | (b0))
#else

#define upr(x,n)        (((x) >> 8 * (n)) | ((x) << (32 - 8 * (n))))
#define ups(x,n)        ((x) >> 8 * (n)))
#define bval(x,n)       ((t_name(byte))((x) >> 24 - 8 * (n)))
#define byte_swap(x)    (upr(x,3) & 0x00ff00ff | upr(x,1) & 0xff00ff00)
#define bytes2word(b0, b1, b2, b3)  \
        ((t_name(word))(b0) << 24 | (t_name(word))(b1) << 16 | (t_name(word))(b2) << 8 | (b3))
#endif

#if (INTERNAL_BYTE_ORDER == EXTERNAL_BYTE_ORDER)

#if defined(PACKED_IO)
#define word_in(x)      bytes2word((x)[0], (x)[1], (x)[2], (x)[3])
#define word_out(x,v)   { (x)[0] = bval(v,0); (x)[1] = bval(v,1);   \
                          (x)[2] = bval(v,2); (x)[3] = bval(v,3);   }
#else
#define word_in(x)      *(t_name(word)*)(x)
#define word_out(x,v)   *(t_name(word)*)(x) = (v)
#endif

#else

#if defined(PACKED_IO)
#define word_in(x)      bytes2word((x)[3], (x)[2], (x)[1], (x)[0])
#define word_out(x,v)   { (x)[3] = bval(v,0); (x)[2] = bval(v,1);   \
                          (x)[1] = bval(v,2); (x)[0] = bval(v,3);   }
#else
#define word_in(x)      byte_swap(*(t_name(word)*)(x))
#define word_out(x,v)   *(t_name(word)*)(x) = byte_swap(v)
#endif

#endif
#endif
