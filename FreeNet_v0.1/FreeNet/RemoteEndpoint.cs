using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FreeNet
{
    public class BaseModel
    {
        public BaseModel() {}

        public virtual void PackInfo(ref CPacket msgSend) { }
        public virtual void UnpackInfo(CPacket msgRecv) { }
    }

    public class stRemote : BaseModel
    {
        UInt64 remote_;

        public override void PackInfo(ref CPacket msgSend)
        {
            msgSend.push(remote_);
        }

        public override void UnpackInfo(CPacket msgRecv)
        {
            remote_ = msgRecv.pop(remote_);
        }
    }

    public class stRemoteEndpoint : BaseModel
    {
        UInt64 remote;          //group 맴버의 서버에서 할당받은 자신의 host id
        byte entry;
        UInt32 publicIP;        //publicIP : group 맴버의 public ip
        UInt16 portTcp;         //tcp port
        UInt16 portUdp;         //udp port
        UInt32 privateIP;       //privateIP : group 맴버의 private ip
        UInt16 privatePort;     //privatePort : group 맴버의 private port

        public override void PackInfo(ref CPacket msgSend)
        {
            msgSend.push(remote);
            msgSend.push(entry);
            msgSend.push(publicIP);
            msgSend.push(portTcp);
            msgSend.push(portUdp);
            msgSend.push(privateIP);
            msgSend.push(privatePort);
        }

        public override void UnpackInfo(CPacket msgRecv)
        {
            remote      = msgRecv.pop(remote);
            entry       = msgRecv.pop(entry);
            publicIP    = msgRecv.pop(publicIP);
            portTcp     = msgRecv.pop(portTcp);
            portUdp     = msgRecv.pop(portUdp);
            privateIP   = msgRecv.pop(privateIP);
            privatePort = msgRecv.pop(privatePort);
        }
    }
}
