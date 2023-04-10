using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSampleClient
{
    public class CRemoteServerInfo : FreeNet.BaseModel
    {
        public UInt32 ip_;
        public UInt16 portTcp_;
        public UInt16 portUdp_;
        public byte serverstatus_;//default : 1(open)
        public Int16 currentusers_; //lobby서버에서 사용됩니다.

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(ip_);
            msgSend.push(portTcp_);
            msgSend.push(portUdp_);
            msgSend.push(serverstatus_);
            msgSend.push(currentusers_);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            ip_             = msgRecv.pop(ip_);
            portTcp_        = msgRecv.pop(portTcp_);
            portUdp_        = msgRecv.pop(portUdp_);
            serverstatus_   = msgRecv.pop(serverstatus_);
            currentusers_   = msgRecv.pop(currentusers_);
        }
    }
}
