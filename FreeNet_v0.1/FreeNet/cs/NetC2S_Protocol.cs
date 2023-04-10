namespace NetC2S
{
	public class PT
	{
		static public uint PT_VERSION = 20210311;
	};

	public enum PROTOCOL : ushort
	{
		NetC2S_CORE_CONNECT_COMPLETED_NTF			= 0xfe00,
		NetC2S_CORE_SIGN_UP_REQ			= 0xfe01,
		NetC2S_CORE_SIGN_UP_ACK			= 0xfe02,
		NetC2S_CORE_HEART_BEAT_REQ			= 0xfe03,
		NetC2S_CORE_HEART_BEAT_ACK			= 0xfe04,
		NetC2S_CORE_JOIN_GROUP_NTF			= 0xfe05,
		NetC2S_CORE_ENTER_GROUP_NTF			= 0xfe06,
		NetC2S_CORE_LEAVE_GROUP_NTF			= 0xfe07,
		NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ			= 0xfe08,
		NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_ACK			= 0xfe09,
		NetC2S_CORE_HOLE_PUNCHING_PEER_READY_REQ			= 0xfe0a,
		NetC2S_CORE_HOLE_PUNCHING_PEER_READY_NTF			= 0xfe0b,
		NetC2S_CORE_HOLE_PUNCHING_PEER_RESULT_NTF			= 0xfe0c,
	}
}