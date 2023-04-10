using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CNoticeSelect : FreeNet.BaseModel
    {
        public UInt32 noticepk;       //번호
        public sbyte type;          //0:공지, 1:이벤트
        public string notice;       //메모
        public string endtime;      //마감시간

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(noticepk);
            msgSend.push(type);
            msgSend.push(notice);
            msgSend.push(endtime);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            noticepk    = msgRecv.pop(noticepk);
            type        = msgRecv.pop(type);
            notice      = msgRecv.pop_string();
            endtime     = msgRecv.pop_string();
        }
    }
}
