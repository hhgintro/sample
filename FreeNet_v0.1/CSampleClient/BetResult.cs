using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CBetResultSingle : FreeNet.BaseModel
    {
        public sbyte type; //struct BET_TYPE( 0:단식, 1:연식, 2:복식, 3:복연식 )
        public sbyte num;  //말번호
        public Int32 bet;	//배팅금액
        public float win;	//수익
        public float div;   //배당률

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(type);
            msgSend.push(num);
            msgSend.push(bet);
            msgSend.push(win);
            msgSend.push(div);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            type = msgRecv.pop(type);
            num = msgRecv.pop(num);
            bet = msgRecv.pop(bet);
            win = msgRecv.pop(win);
            div = msgRecv.pop(div);
        }
    }

    public class CBetResultDouble : FreeNet.BaseModel
    {
        public sbyte type; //struct BET_TYPE( 0:단식, 1:연식, 2:복식, 3:복연식 )
        public sbyte num1;  //말번호
        public sbyte num2;  //말번호
        public Int32 bet;	//배팅금액
        public float win;	//수익
        public float div;   //배당률

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(type);
            msgSend.push(num1);
            msgSend.push(num2);
            msgSend.push(bet);
            msgSend.push(win);
            msgSend.push(div);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            type = msgRecv.pop(type);
            num1 = msgRecv.pop(num1);
            num2 = msgRecv.pop(num2);
            bet = msgRecv.pop(bet);
            win = msgRecv.pop(win);
            div = msgRecv.pop(div);
        }
    }

    public class CBetResultTriple : FreeNet.BaseModel
    {
        public sbyte num1;  //말번호
        public sbyte num2;  //말번호
        public sbyte num3;  //말번호
        public Int32 bet;	//배팅금액
        public float win;	//수익
        public float div;   //배당률

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(num1);
            msgSend.push(num2);
            msgSend.push(num3);
            msgSend.push(bet);
            msgSend.push(win);
            msgSend.push(div);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            num1 = msgRecv.pop(num1);
            num2 = msgRecv.pop(num2);
            num3 = msgRecv.pop(num3);
            bet = msgRecv.pop(bet);
            win = msgRecv.pop(win);
            div = msgRecv.pop(div);
        }
    }
}
