using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CLogRaceSelect : FreeNet.BaseModel
    {
        public Int32 racepk;   //경주번호
        public string race;    //경주
        public UInt16 meter;   //거리
        public sbyte horse;    //출전 말수

        public string rank;    //순위(1,2,3)
        public string dan;     //단승식(1:1.2)
        public string bok;     //복승식(1-2:2.5)
        public string ssang;   //쌍승식(1-2:2.5)
        public string time;    //경주시간

        public sbyte bets;     //배팅한 수

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(racepk);
            msgSend.push(race);
            msgSend.push(meter);
            msgSend.push(horse);

            msgSend.push(rank);
            msgSend.push(dan);
            msgSend.push(bok);
            msgSend.push(ssang);
            msgSend.push(time);

            msgSend.push(bets);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            racepk  = msgRecv.pop(racepk);
            race    = msgRecv.pop_string();
            meter   = msgRecv.pop(meter);
            horse   = msgRecv.pop(horse);

            rank    = msgRecv.pop_string();
            dan     = msgRecv.pop_string();
            bok     = msgRecv.pop_string();
            ssang   = msgRecv.pop_string();
            time    = msgRecv.pop_string();

            bets    = msgRecv.pop(bets);
        }
    }
}
