using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CLogAccountMoney : FreeNet.BaseModel
    {
        public UInt32 m_credit;     //coin으로 투입한 credit
        public float m_win;		    //게임에서 획득한(win) 금액

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_credit);
            msgSend.push(m_win);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            m_credit    = msgRecv.pop(m_credit);
            m_win       = msgRecv.pop(m_win);
        }
    }
}
