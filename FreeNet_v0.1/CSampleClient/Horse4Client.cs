using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;

namespace CSampleClient
{
    public class CHorse4Client : FreeNet.BaseModel
    {
        public Int32 m_nR1;             // 경주마 1위전적
        public Int32 m_nR2;             // 경주마 2위전적
        public Int32 m_nRT;             // 경주마 통산전적
        public sbyte m_nR1_;            // 경주마 단승률
        public sbyte m_nR2_;            // 경주마 복승률

        public Int32 m_nM1;             // 기승기수 1위전적
        public Int32 m_nM2;             // 기승기수 2위전적
        public Int32 m_nMT;             // 기승기수 통산전적
        public sbyte m_nM1_;            // 기승기수 단승률
        public sbyte m_nM2_;            // 기승기수 복승률

        //
        public sbyte m_nM_L;            // 기수능력
        public sbyte m_nRH;             // 기승수(연속 기승수) 1회차는 -> "교체"로 표시
        //char m_szM_K[5];		        // 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)
        public sbyte m_nM_K;            // 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)

        public float m_fRW;            // 부담중량
        public sbyte m_nWD;             // 부담중량 변화량
        public sbyte m_cV_W;            // 부담중량 잇점
        public sbyte m_nND;             // 게이트(마번) 변화량
        public sbyte m_cV_N;            // 게이트 잇점
        public sbyte m_nJS;             // 조교 마필상태

        //
        public float m_fS1F;           // 구간기록 출발후 200미터 소요시간
        public float m_fS2F;           // 구간기록 출발후 400미터 소요시간
        public float m_fS3F;           // 구간기록 출발후 600미터 소요시간
        public float m_fS4F;           // 구간기록 출발후 800미터 소요시간
        public float m_fS5F;           // 구간기록 출발후 1000미터 소요시간
        public float m_fS6F;           // 구간기록 출발후 1200미터 소요시간
        public float m_fS7F;           // 구간기록 출발후 1400미터 소요시간
        public float m_fS8F;           // 구간기록 출발후 1600미터 소요시간
        public float m_fS9F;           // 구간기록 출발후 1800미터 소요시간
        public float m_fG1F;           // 구간기록 종착전 200미터 소요시간
        public float m_fRC_T;          // 총 소요시간

        //
        public Int32 m_nOrder;			// 자료순서


        public override void PackInfo(ref FreeNet.CPacket msgSend)
        {
            //Int32 m_nR1;            // 경주마 1위전적
            //Int32 m_nR2;            // 경주마 2위전적
            //Int32 m_nRT;            // 경주마 통산전적
            //sbyte m_nR1_;            // 경주마 단승률
            //sbyte m_nR2_;            // 경주마 복승률
            msgSend.push(m_nR1);
            msgSend.push(m_nR2);
            msgSend.push(m_nRT);
            msgSend.push(m_nR1_);
            msgSend.push(m_nR2_);

            //Int32 m_nM1;            // 기승기수 1위전적
            //Int32 m_nM2;            // 기승기수 2위전적
            //Int32 m_nMT;            // 기승기수 통산전적
            //sbyte m_nM1_;            // 기승기수 단승률
            //sbyte m_nM2_;            // 기승기수 복승률
            msgSend.push(m_nM1);
            msgSend.push(m_nM2);
            msgSend.push(m_nMT);
            msgSend.push(m_nM1_);
            msgSend.push(m_nM2_);

            //
            //sbyte m_nM_L;            // 기수능력
            //sbyte m_nRH;             // 기승수(연속 기승수) 1회차는 -> "교체"로 표시
            ////char m_szM_K[5];		// 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)
            //sbyte m_nM_K;            // 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)
            msgSend.push(m_nM_L);
            msgSend.push(m_nRH);
            msgSend.push(m_nM_K);

            //float m_fRW;            // 부담중량
            //sbyte m_nWD;             // 부담중량 변화량
            //sbyte m_cV_W;            // 부담중량 잇점
            //sbyte m_nND;             // 게이트(마번) 변화량
            //sbyte m_cV_N;            // 게이트 잇점
            //sbyte m_nJS;             // 조교 마필상태
            msgSend.push(m_fRW);
            msgSend.push(m_nWD);
            msgSend.push(m_cV_W);
            msgSend.push(m_nND);
            msgSend.push(m_cV_N);
            msgSend.push(m_nJS);

            //
            //float m_fS1F;           // 구간기록 출발후 200미터 소요시간
            //float m_fS2F;           // 구간기록 출발후 400미터 소요시간
            //float m_fS3F;           // 구간기록 출발후 600미터 소요시간
            //float m_fS4F;           // 구간기록 출발후 800미터 소요시간
            //float m_fS5F;           // 구간기록 출발후 1000미터 소요시간
            //float m_fS6F;           // 구간기록 출발후 1200미터 소요시간
            //float m_fS7F;           // 구간기록 출발후 1400미터 소요시간
            //float m_fS8F;           // 구간기록 출발후 1600미터 소요시간
            //float m_fS9F;           // 구간기록 출발후 1800미터 소요시간
            //float m_fG1F;           // 구간기록 종착전 200미터 소요시간
            //float m_fRC_T;          // 총 소요시간
            msgSend.push(m_fS1F);
            msgSend.push(m_fS2F);
            msgSend.push(m_fS3F);
            msgSend.push(m_fS4F);
            msgSend.push(m_fS5F);
            msgSend.push(m_fS6F);
            msgSend.push(m_fS7F);
            msgSend.push(m_fS8F);
            msgSend.push(m_fS9F);
            msgSend.push(m_fG1F);
            msgSend.push(m_fRC_T);

            //
            //Int32 m_nOrder;			// 자료순서
            msgSend.push(m_nOrder);
        }

        public override void UnpackInfo(FreeNet.CPacket msgRecv)
        {
            //Int32 m_nR1;            // 경주마 1위전적
            //Int32 m_nR2;            // 경주마 2위전적
            //Int32 m_nRT;            // 경주마 통산전적
            //sbyte m_nR1_;            // 경주마 단승률
            //sbyte m_nR2_;            // 경주마 복승률
            m_nR1       = msgRecv.pop(m_nR1);
            m_nR2       = msgRecv.pop(m_nR2);
            m_nRT       = msgRecv.pop(m_nRT);
            m_nR1_      = msgRecv.pop(m_nR1_);
            m_nR2_      = msgRecv.pop(m_nR2_);

            //Int32 m_nM1;            // 기승기수 1위전적
            //Int32 m_nM2;            // 기승기수 2위전적
            //Int32 m_nMT;            // 기승기수 통산전적
            //sbyte m_nM1_;            // 기승기수 단승률
            //sbyte m_nM2_;            // 기승기수 복승률
            m_nM1       = msgRecv.pop(m_nM1);
            m_nM2       = msgRecv.pop(m_nM2);
            m_nMT       = msgRecv.pop(m_nMT);
            m_nM1_      = msgRecv.pop(m_nM1_);
            m_nM2_      = msgRecv.pop(m_nM2_);

            //
            //sbyte m_nM_L;            // 기수능력
            //sbyte m_nRH;             // 기승수(연속 기승수) 1회차는 -> "교체"로 표시
            ////char m_szM_K[5];		// 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)
            //sbyte m_nM_K;            // 기수의 질주성향(0:불명,1:선행,2:자유,3:선입,4:추입,5:도주)
            m_nM_L      = msgRecv.pop(m_nM_L);
            m_nRH       = msgRecv.pop(m_nRH);
            m_nM_K      = msgRecv.pop(m_nM_K);

            //float m_fRW;            // 부담중량
            //sbyte m_nWD;             // 부담중량 변화량
            //sbyte m_cV_W;            // 부담중량 잇점
            //sbyte m_nND;             // 게이트(마번) 변화량
            //sbyte m_cV_N;            // 게이트 잇점
            //sbyte m_nJS;             // 조교 마필상태
            m_fRW       = msgRecv.pop(m_fRW);
            m_nWD       = msgRecv.pop(m_nWD);
            m_cV_W      = msgRecv.pop(m_cV_W);
            m_nND       = msgRecv.pop(m_nND);
            m_cV_N      = msgRecv.pop(m_cV_N);
            m_nJS       = msgRecv.pop(m_nJS);

            //
            //float m_fS1F;           // 구간기록 출발후 200미터 소요시간
            //float m_fS2F;           // 구간기록 출발후 400미터 소요시간
            //float m_fS3F;           // 구간기록 출발후 600미터 소요시간
            //float m_fS4F;           // 구간기록 출발후 800미터 소요시간
            //float m_fS5F;           // 구간기록 출발후 1000미터 소요시간
            //float m_fS6F;           // 구간기록 출발후 1200미터 소요시간
            //float m_fS7F;           // 구간기록 출발후 1400미터 소요시간
            //float m_fS8F;           // 구간기록 출발후 1600미터 소요시간
            //float m_fS9F;           // 구간기록 출발후 1800미터 소요시간
            //float m_fG1F;           // 구간기록 종착전 200미터 소요시간
            //float m_fRC_T;          // 총 소요시간
            m_fS1F      = msgRecv.pop(m_fS1F);
            m_fS2F      = msgRecv.pop(m_fS2F);
            m_fS3F      = msgRecv.pop(m_fS3F);
            m_fS4F      = msgRecv.pop(m_fS4F);
            m_fS5F      = msgRecv.pop(m_fS5F);
            m_fS6F      = msgRecv.pop(m_fS6F);
            m_fS7F      = msgRecv.pop(m_fS7F);
            m_fS8F      = msgRecv.pop(m_fS8F);
            m_fS9F      = msgRecv.pop(m_fS9F);
            m_fG1F      = msgRecv.pop(m_fG1F);
            m_fRC_T     = msgRecv.pop(m_fRC_T);

            //
            //Int32 m_nOrder;			// 자료순서
            m_nOrder    = msgRecv.pop(m_nOrder);
        }

    }
}
