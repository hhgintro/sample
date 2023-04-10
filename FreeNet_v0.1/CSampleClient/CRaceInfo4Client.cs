using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CRaceInfo4Client : FreeNet.BaseModel
    {
        public UInt32 m_nRackPK;                    //경주 고유번호

        public List<CHorse4Client> m_strHorse = new List<CHorse4Client>();       // 말 구조체  [12]
        //CHorseInfo m_HorseInfo[12]
        public Int32 m_nHorseCount;                // 말 마리수
        public List<float> m_fPR_;                       // PR 값[12]
        public sbyte m_bE_V;                        // 환경 변수
        //char m_szValueCen[12][60];			// 단문 단평[12]        //HG[2021.02.15]클라에서 처리하도록 개선필요
        public List<sbyte> m_nValueCen;         // 단문 단평(0~ )
        public List<sbyte> m_nTrip;                  // 단문 트립[12]
        public List<Int32> m_nStartWhip;             // 채찍질 시작[12]
        public List<sbyte> m_nWhipCount;              // 채찍질 횟수[12]

        public sbyte m_nStadium;                    // 경기장
        public Int32 m_nRaceNumber1;               // 날짜
        public sbyte m_nRaceNumber2;                // Hour
        public sbyte m_nRaceNumber3;                // Min
        public sbyte m_nHorseType;                  // 말 타입
        public sbyte m_nHorseLevel;                 // 말 등급
        public Int32 m_nMeter;                     // 미터수
        public Int32 m_nRaceCode;                  // 말을 뽑기 위한 코드
        public sbyte m_nRaceLevel;                  // 경주 단계( 1 ~ 10 )
        public sbyte m_nHumidity;                   // 습도
        public List<sbyte> m_nPopRank;                // 인기 순위[12]
        public List<sbyte> m_nPopRank_;               // 전 인기 순위[12]
        public sbyte m_nRankAppNum;                 // 미사용
        public sbyte m_nFinishC;                    // 마지막 코너 번호
        public List<sbyte> m_nRank;                    // 순위[3-->12] : 말수만큼 변경
        public List<float> m_fGap;                    // 순위간 차이 (초)[4]
        public float m_fRealTime;                  // 실제 시간
        public float m_fRaceTime;                  // 게임 시간


        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            //CHorse4Client[] m_strHorse;       // 말 구조체  [12]
            ////CHorseInfo m_HorseInfo[12]
            //Int32 m_nHorseCount;                // 말 마리수
            //float[] m_fPR_;                       // PR 값[12]
            //sbyte m_bE_V;                        // 환경 변수
            ////char m_szValueCen[12][60];			// 단문 단평[12]        //HG[2021.02.15]클라에서 처리하도록 개선필요
            //char m_nTrip[12];                  // 단문 트립[12]
            //Int32 m_nStartWhip[12];             // 채찍질 시작[12]
            //sbyte m_nWhipCount[12];              // 채찍질 횟수[12]

            msgSend.push(m_nRackPK);

            //msgSend.push(m_strHorse);
            FreeNet.CPacket.push<CHorse4Client>(m_strHorse, ref msgSend);
            msgSend.push(m_nHorseCount);

            for(int i=0; i< m_nHorseCount; ++i)
                msgSend.push(m_fPR_[i]);

            msgSend.push(m_bE_V);

            for (int i = 0; i < m_nHorseCount; ++i) {
                msgSend.push(m_nValueCen[i]);
                msgSend.push(m_nTrip[i]);
                msgSend.push(m_nStartWhip[i]);
                msgSend.push(m_nWhipCount[i]);
            }


            //sbyte m_nStadium;                    // 경기장
            //Int32 m_nRaceNumber1;               // 날짜
            //sbyte m_nRaceNumber2;                // Hour
            //sbyte m_nRaceNumber3;                // Min
            //sbyte m_nHorseType;                  // 말 타입
            //sbyte m_nHorseLevel;                 // 말 등급
            //Int32 m_nMeter;                     // 미터수
            //Int32 m_nRaceCode;                  // 말을 뽑기 위한 코드
            //sbyte m_nRaceLevel;                  // 경주 단계( 1 ~ 10 )
            //sbyte m_nHumidity;                   // 습도
            //char m_nPopRank[12];                // 인기 순위
            //char m_nPopRank_[12];               // 전 인기 순위
            //sbyte m_nRankAppNum;                 // 미사용
            //sbyte m_nFinishC;                    // 마지막 코너 번호
            //sbyte m_nRank[3];                    // 순위
            //float m_fGap[4];                    // 순위간 차이 (초)
            //float m_fRealTime;                  // 실제 시간
            //float m_fRaceTime;                  // 게임 시간
            msgSend.push(m_nStadium);
            msgSend.push(m_nRaceNumber1);
            msgSend.push(m_nRaceNumber2);
            msgSend.push(m_nRaceNumber3);
            msgSend.push(m_nHorseType);
            msgSend.push(m_nHorseLevel);
            msgSend.push(m_nMeter);
            msgSend.push(m_nRaceCode);
            msgSend.push(m_nRaceLevel);
            msgSend.push(m_nHumidity);

            for (int i = 0; i < m_nHorseCount; ++i) {
                msgSend.push(m_nPopRank[i]);
                msgSend.push(m_nPopRank_[i]);
            }

            msgSend.push(m_nRankAppNum);
            msgSend.push(m_nFinishC);
            for (int i = 0; i < m_nHorseCount; ++i)
                msgSend.push(m_nRank[i]);
            for (int i = 0; i < 4; ++i)
                msgSend.push(m_fGap[i]);

            msgSend.push(m_fRealTime);
            msgSend.push(m_fRaceTime);

        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            //CHorse4Client[] m_strHorse;       // 말 구조체  [12]
            ////CHorseInfo m_HorseInfo[12]
            //Int32 m_nHorseCount;                // 말 마리수
            //float[] m_fPR_;                       // PR 값[12]
            //sbyte m_bE_V;                        // 환경 변수
            ////char m_szValueCen[12][60];			// 단문 단평[12]        //HG[2021.02.15]클라에서 처리하도록 개선필요
            //char m_nTrip[12];                  // 단문 트립[12]
            //Int32 m_nStartWhip[12];             // 채찍질 시작[12]
            //sbyte m_nWhipCount[12];              // 채찍질 횟수[12]

            m_nRackPK = msgRecv.pop(m_nRackPK);

            //m_strHorse      = msgRecv.pop(m_strHorse);
            //m_strHorse = new List<CHorse4Client>();
            FreeNet.CPacket.pop<CHorse4Client>(m_strHorse, ref msgRecv);
            foreach(CHorse4Client horse in m_strHorse) {
                Console.WriteLine("m_nOrder:{0}", horse.m_nOrder);
            }

            m_nHorseCount = msgRecv.pop(m_nHorseCount);

            m_fPR_ = new List<float>();
            for (int i = 0; i < m_nHorseCount; ++i)
            {
                float val = 0;
                m_fPR_.Add(msgRecv.pop(val));
            }
            
            m_bE_V          = msgRecv.pop(m_bE_V);

            m_nValueCen = new List<sbyte>();
            m_nTrip = new List<sbyte>();
            m_nStartWhip = new List<Int32>();
            m_nWhipCount = new List<sbyte>();
            for (int i = 0; i < m_nHorseCount; ++i) {
                sbyte valuecen = 0;
                sbyte trip = 0;
                Int32 whip = 0;
                sbyte count = 0;

                m_nValueCen.Add(msgRecv.pop(valuecen));
                m_nTrip.Add(msgRecv.pop(trip));
                m_nStartWhip.Add(msgRecv.pop(whip));
                m_nWhipCount.Add(msgRecv.pop(count));
            }

            //sbyte m_nStadium;                    // 경기장
            //Int32 m_nRaceNumber1;               // 날짜
            //sbyte m_nRaceNumber2;                // Hour
            //sbyte m_nRaceNumber3;                // Min
            //sbyte m_nHorseType;                  // 말 타입
            //sbyte m_nHorseLevel;                 // 말 등급
            //Int32 m_nMeter;                     // 미터수
            //Int32 m_nRaceCode;                  // 말을 뽑기 위한 코드
            //sbyte m_nRaceLevel;                  // 경주 단계( 1 ~ 10 )
            //sbyte m_nHumidity;                   // 습도
            //char m_nPopRank[12];                // 인기 순위
            //char m_nPopRank_[12];               // 전 인기 순위
            //sbyte m_nRankAppNum;                 // 미사용
            //sbyte m_nFinishC;                    // 마지막 코너 번호
            //sbyte m_nRank[3];                    // 순위
            //float m_fGap[4];                    // 순위간 차이 (초)
            //float m_fRealTime;                  // 실제 시간
            //float m_fRaceTime;                  // 게임 시간
            m_nStadium      = msgRecv.pop(m_nStadium);
            m_nRaceNumber1  = msgRecv.pop(m_nRaceNumber1);
            m_nRaceNumber2  = msgRecv.pop(m_nRaceNumber2);
            m_nRaceNumber3  = msgRecv.pop(m_nRaceNumber3);
            m_nHorseType    = msgRecv.pop(m_nHorseType);
            m_nHorseLevel   = msgRecv.pop(m_nHorseLevel);
            m_nMeter        = msgRecv.pop(m_nMeter);
            m_nRaceCode     = msgRecv.pop(m_nRaceCode);
            m_nRaceLevel    = msgRecv.pop(m_nRaceLevel);
            m_nHumidity     = msgRecv.pop(m_nHumidity);

            m_nPopRank = new List<sbyte>();
            m_nPopRank_ = new List<sbyte>();
            for (int i = 0; i < m_nHorseCount; ++i) {
                sbyte rank = 0;
                m_nPopRank.Add(msgRecv.pop(rank));
                m_nPopRank_.Add(msgRecv.pop(rank));
            }

            m_nRankAppNum   = msgRecv.pop(m_nRankAppNum);
            m_nFinishC      = msgRecv.pop(m_nFinishC);

            m_nRank = new List<sbyte>();
            for (int i = 0; i < m_nHorseCount; ++i) {
                sbyte rank = 0;
                m_nRank.Add(msgRecv.pop(rank));
            }

            m_fGap = new List<float>();
            for (int i = 0; i < 4; ++i) {
                float gap = 0;
                m_fGap.Add(msgRecv.pop(gap));
            }

            m_fRealTime     = msgRecv.pop(m_fRealTime);
            m_fRaceTime     = msgRecv.pop(m_fRaceTime);

            Console.WriteLine("\t Meter: {0}, racetime:{1} / {2}",m_nMeter , m_fRealTime, m_fRaceTime);
        }

    }
}
