using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSampleClient
{
    public class CCertifyInfo : FreeNet.BaseModel
    {
        public string m_nickname;
        public byte m_auth;             //권한 ( 1:유저, 3:마스터, 4,5:관리자)
        public Int32 m_credit;         //coin으로 투입한 credit
        public Int32 m_win;		    //게임에서 획득한(win) 금액

        public string m_phone;          //전화번호
        public string m_bank;           //은행계좌번호

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_nickname);
            msgSend.push(m_auth);
            msgSend.push(m_credit);
            msgSend.push(m_win);

            msgSend.push(m_phone);
            msgSend.push(m_bank);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            m_nickname  = msgRecv.pop_string();
            m_auth      = msgRecv.pop(m_auth);
            m_credit    = msgRecv.pop(m_credit);
            m_win       = msgRecv.pop(m_win);

            m_phone     = msgRecv.pop_string();
            m_bank      = msgRecv.pop_string();

        }
    }
}
