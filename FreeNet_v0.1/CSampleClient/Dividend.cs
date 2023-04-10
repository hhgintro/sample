using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CDividend : FreeNet.BaseModel
    {
        int MAX_HORSE_COUNT = 12;
        int TOTAL_BOK_BUTTON = 66;  //11+10+9+8+7+6+5+4+3+2+1

        public float[] fDanDividend;      //[MAX_HORSE_COUNT];
        public float[] fYonDividend;      //[MAX_HORSE_COUNT];
        public float[] fBokDividend;      //[TOTAL_BOK_BUTTON];
        public float[] fBokYonDividend;   //[TOTAL_BOK_BUTTON];
        public float[,] fSsangDividend;    //[MAX_HORSE_COUNT][MAX_HORSE_COUNT];
        public float[,] fTriple;           //[3][MAX_HORSE_COUNT];
        public float fPer;


        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                msgSend.push(fDanDividend[i]);

            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                msgSend.push(fYonDividend[i]);
     
            for (int i = 0; i < TOTAL_BOK_BUTTON; ++i)
                msgSend.push(fBokDividend[i]);

            for (int i = 0; i < TOTAL_BOK_BUTTON; ++i)
                msgSend.push(fBokYonDividend[i]);

            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                for (int j = 0; j < MAX_HORSE_COUNT; ++j)
                msgSend.push(fSsangDividend[i,j]);

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < MAX_HORSE_COUNT; ++j)
                    msgSend.push(fTriple[i, j]);

            msgSend.push(fPer);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
             fDanDividend = new float[MAX_HORSE_COUNT];
            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                fDanDividend[i] = msgRecv.pop(fDanDividend[i]);

            fYonDividend = new float[MAX_HORSE_COUNT];
            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                fYonDividend[i] = msgRecv.pop(fYonDividend[i]);

            fBokDividend = new float[TOTAL_BOK_BUTTON];
            for (int i = 0; i < TOTAL_BOK_BUTTON; ++i)
                fBokDividend[i] = msgRecv.pop(fBokDividend[i]);

            fBokYonDividend = new float[TOTAL_BOK_BUTTON];
            for (int i = 0; i < TOTAL_BOK_BUTTON; ++i)
                fBokYonDividend[i] = msgRecv.pop(fBokYonDividend[i]);

            fSsangDividend = new float[MAX_HORSE_COUNT, MAX_HORSE_COUNT];
            for (int i = 0; i < MAX_HORSE_COUNT; ++i)
                for (int j = 0; j < MAX_HORSE_COUNT; ++j)
                    fSsangDividend[i,j] = msgRecv.pop(fSsangDividend[i,j]);

            fTriple = new float[3, MAX_HORSE_COUNT];
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < MAX_HORSE_COUNT; ++j)
                    fTriple[i,j] = msgRecv.pop(fTriple[i,j]);

            fPer = msgRecv.pop(fPer);
        }

    }
}
