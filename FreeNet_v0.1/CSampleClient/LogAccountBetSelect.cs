using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CLogAccountBetSelect : FreeNet.BaseModel
    {
        sbyte type;     //struct BET_TYPE (0:단식,1:연식,2:복식,3:복연식,4:쌍식,5:삼복식)
        sbyte horse1;   //말번호
        sbyte horse2;   //말번호
        sbyte horse3;   //말번호(reserved)

        Int32 bet;	    //배팅금액
        Int32 win;	    //수익
        Int32 loss;	    //손실

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(type);
            msgSend.push(horse1);
            msgSend.push(horse2);
            msgSend.push(horse3);

            msgSend.push(bet);
            msgSend.push(win);
            msgSend.push(loss);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            type    = msgRecv.pop(type);
            horse1  = msgRecv.pop(horse1);
            horse2  = msgRecv.pop(horse2);
            horse3  = msgRecv.pop(horse3);

            bet     = msgRecv.pop(bet);
            win     = msgRecv.pop(win);
            loss    = msgRecv.pop(loss);
        }
    }
}
