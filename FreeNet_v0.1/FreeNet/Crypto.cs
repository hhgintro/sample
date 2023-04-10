using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FreeNet
{
public class Crypto
{
    static UInt32 C2 = 26119;
    static UInt32 KEY = 71957;
    static UInt32 C1 = 42875;

    static public bool Encrypt(byte[] source, UInt32 sourceIndex, ref byte[] destination, UInt32 destinationIndex, UInt32 length)
    {
        UInt32 key = KEY;

        if (length <= 0) return false;

        for (UInt32 i = 0; i < length; ++i)
        {
            destination[destinationIndex + i] = (byte)(source[sourceIndex + i] ^ (key >> 8));
            key = (destination[destinationIndex + i] + key) * C1 + C2;
        }
        return true;
    }
    static public bool Decrypt(byte[] source, UInt32 sourceIndex, ref byte[] destination, UInt32 destinationIndex, UInt32 length)
    {
        byte PreviousBlock = 0;
        UInt32 key = KEY;

        if (length <= 0) return false;

        for (UInt32 i = 0; i < length; ++i)
        {
            PreviousBlock = source[sourceIndex + i];
            destination[destinationIndex + i] = (byte)(source[sourceIndex + i] ^ (key >> 8));

            key = (PreviousBlock + key) * C1 + C2;
        }
        return true;
    }
}
}
