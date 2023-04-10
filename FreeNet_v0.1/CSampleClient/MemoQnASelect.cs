using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CMemoQnASelect : FreeNet.BaseModel
    {
        public UInt32 memopk;      //num
        public UInt32 board;        //댓글 그룹 id
        //sbyte type;       //0:
        //sbyte status;     //0:신규, 1:읽음, 2:처리완료, 98:사용자삭제, 99:운영자삭제
        public string memo;        //작성된 메모내용
        string gm;                  //답변 운영자 계정
        string answer;              //답변 내용
        string time;                //작성일시

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(memopk);
            msgSend.push(board);
            //msgSend.push(type);
            //msgSend.push(status);
            msgSend.push(memo);
            msgSend.push(gm);
            msgSend.push(answer);
            msgSend.push(time);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            memopk      = msgRecv.pop(memopk);
            board       = msgRecv.pop(board);
            //type      = msgRecv.pop(type);
            //status    = msgRecv.pop(status);
            memo        = msgRecv.pop_string();
            gm          = msgRecv.pop_string();
            answer      = msgRecv.pop_string();
            time        = msgRecv.pop_string();
        }
    }
}
