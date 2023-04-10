using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CMoneyDepositSelect : FreeNet.BaseModel
    {
        UInt32 pk;	        //num

        sbyte type;         //0:입금, 1:출금
        sbyte status;       //0:미처리, 1:처리완료

        Int32 add_credit;	//추가 요청 게임머니
        Int32 credit;	    //현재 소지 게임머니

        string time;        //시간

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(pk);

            msgSend.push(type);
            msgSend.push(status);

            msgSend.push(add_credit);
            msgSend.push(credit);

            msgSend.push(time);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            pk          = msgRecv.pop(pk);

            type        = msgRecv.pop(type);
            status      = msgRecv.pop(status);

            add_credit  = msgRecv.pop(add_credit);
            credit      = msgRecv.pop(credit);

            time        = msgRecv.pop_string();
        }
    }
}
