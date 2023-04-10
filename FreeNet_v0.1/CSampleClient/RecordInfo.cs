using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;
//using UnityEngine;

namespace CSampleClient
{
    public class CRecordPrize : FreeNet.BaseModel
    {
        public Int32 m_nRaceNum1;
        public Int32 m_nRaceNum2;
        public Int32 m_nRaceNum3;
        public float m_fDividend;
        public float m_fBestDividend;
        public Int32 m_nPrize;
        public string m_account;

        public void Log()
        {
            Console.Write("\t PRIZE: RaceNum(" + m_nRaceNum1 + "-" + m_nRaceNum2 + "-" + m_nRaceNum3
                + "), Div(" + m_fDividend + "), BestDiv(" + m_fBestDividend
                + "), Prize(" + m_nPrize + "), account(" + m_account + ")\n");
        }
        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_nRaceNum1);
            msgSend.push(m_nRaceNum2);
            msgSend.push(m_nRaceNum3);
            msgSend.push(m_fDividend);
            msgSend.push(m_fBestDividend);
            msgSend.push(m_nPrize);
            msgSend.push(m_account);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            m_nRaceNum1     = msgRecv.pop(m_nRaceNum1);
            m_nRaceNum2     = msgRecv.pop(m_nRaceNum2);
            m_nRaceNum3     = msgRecv.pop(m_nRaceNum3);
            m_fDividend     = msgRecv.pop(m_fDividend);
            m_fBestDividend = msgRecv.pop(m_fBestDividend);
            m_nPrize        = msgRecv.pop(m_nPrize);
            m_account       = msgRecv.pop_string();
        }
    }

    public class CRecordRider : FreeNet.BaseModel
    {
        public string m_szName;
        public float m_fOldRate;
        public float m_fDayRate;
        public Int32 m_nTotal;
        public Int32 m_nWin;
        public Int32 m_nDayTotal;
        public Int32 m_nDayWin;


        public void Log()
        {
            Console.Write("\t RIDER: name(" + m_szName + "), old(" + m_fOldRate + "), day(" + m_fDayRate
                + "), total(" + m_nTotal + "), win(" + m_nWin + "), DayTotal(" + m_nDayTotal + "), DayWin(" + m_nDayWin + ")\n");
        }

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_szName);
            msgSend.push(m_fOldRate);
            msgSend.push(m_fDayRate);
            msgSend.push(m_nTotal);
            msgSend.push(m_nWin);
            msgSend.push(m_nDayTotal);
            msgSend.push(m_nDayWin);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            //m_szName        = msgRecv.pop_utf8();
            m_szName        = msgRecv.pop_string();

            m_fOldRate      = msgRecv.pop(m_fOldRate);
            m_fDayRate      = msgRecv.pop(m_fDayRate);
            m_nTotal        = msgRecv.pop(m_nTotal);
            m_nWin          = msgRecv.pop(m_nWin);
            m_nDayTotal     = msgRecv.pop(m_nDayTotal);
            m_nDayWin       = msgRecv.pop(m_nDayWin);
        }
    }

    public class CRecordDividend : FreeNet.BaseModel
    {
        public float m_fOldRate;
        public float m_fDayRate;
        public Int32 m_nCount;
        public Int32 m_nDayCount;
        public void Log()
        {
            Console.Write("\t DIVIDEND: old(" + m_fOldRate + "), day(" + m_fDayRate + "), cnt(" + m_nCount + "), DayCnt(" + m_nDayCount + ")\n");
        }

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_fOldRate);
            msgSend.push(m_fDayRate);
            msgSend.push(m_nCount);
            msgSend.push(m_nDayCount);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            m_fOldRate      = msgRecv.pop(m_fOldRate);
            m_fDayRate      = msgRecv.pop(m_fDayRate);
            m_nCount        = msgRecv.pop(m_nCount);
            m_nDayCount     = msgRecv.pop(m_nDayCount);
        }
    }

    public class CRecordRank : FreeNet.BaseModel
    {
        public float m_fOldRate;
        public float m_fDayRate;
        public Int32 m_nCount;
        public Int32 m_nDayCount;
        public void Log()
        {
            Console.Write("\t DIVIDEND: old(" + m_fOldRate + "), day(" + m_fDayRate + "), cnt(" + m_nCount + "), DayCnt(" + m_nDayCount + ")\n");
        }

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            msgSend.push(m_fOldRate);
            msgSend.push(m_fDayRate);
            msgSend.push(m_nCount);
            msgSend.push(m_nDayCount);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            m_fOldRate      = msgRecv.pop(m_fOldRate);
            m_fDayRate      = msgRecv.pop(m_fDayRate);
            m_nCount        = msgRecv.pop(m_nCount);
            m_nDayCount     = msgRecv.pop(m_nDayCount);
        }
    }

    public class CRecordInfo : FreeNet.BaseModel, IDisposable
    {
		public List<CRecordPrize> prizes = new List<CRecordPrize>();            //배당 top 20
        public List<CRecordRider> riderBests = new List<CRecordRider>();        //상위 10
        public List<CRecordRider> riderWorsts = new List<CRecordRider>();       //하위 10
        public List<CRecordDividend> dividends = new List<CRecordDividend>();   //배당률 6
        public List<CRecordRank> ranks = new List<CRecordRank>();               //입상률(인기순위) 6

        public void Log()
        {
            Console.Write("***** prize\n");
            for (int i = 0; i < prizes.Count; ++i)
                prizes[i].Log();
            Console.Write("***** best rider\n");
            for (int i = 0; i < riderBests.Count; ++i)
                riderBests[i].Log();
            Console.Write("***** worst rider\n");
            for (int i = 0; i < riderWorsts.Count; ++i)
                riderWorsts[i].Log();
            Console.Write("***** 배당률\n");
            for (int i = 0; i < dividends.Count; ++i)
                dividends[i].Log();
            Console.Write("***** 입상률\n");
            for (int i = 0; i < ranks.Count; ++i)
                ranks[i].Log();
        }

        public void Dispose()
        {
            prizes.Clear();
            riderBests.Clear();
            riderWorsts.Clear();
            dividends.Clear();
            ranks.Clear();
        }

        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            FreeNet.CPacket.push<CRecordPrize>(prizes, ref msgSend);
            FreeNet.CPacket.push<CRecordRider>(riderBests, ref msgSend);
            FreeNet.CPacket.push<CRecordRider>(riderWorsts, ref msgSend);
            FreeNet.CPacket.push<CRecordDividend>(dividends, ref msgSend);
            FreeNet.CPacket.push<CRecordRank>(ranks, ref msgSend);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            FreeNet.CPacket.pop<CRecordPrize>(prizes, ref msgRecv);
            FreeNet.CPacket.pop<CRecordRider>(riderBests, ref msgRecv);
            FreeNet.CPacket.pop<CRecordRider>(riderWorsts, ref msgRecv);
            FreeNet.CPacket.pop<CRecordDividend>(dividends, ref msgRecv);
            FreeNet.CPacket.pop<CRecordRank>(ranks, ref msgRecv);
        }
    }
}
