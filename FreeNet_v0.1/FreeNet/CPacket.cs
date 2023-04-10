using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FreeNet
{
	/// <summary>
	/// byte[] 버퍼를 참조로 보관하여 pop_xxx 매소드 호출 순서대로 데이터 변환을 수행한다.
	/// </summary>
	public class CPacket
	{
		public IPeer owner { get; private set; }
		public byte[] buffer { get; private set; }
		public int position { get; private set; }

		UInt16 protocol_id;

		public static CPacket create(UInt16 protocol_id, byte context)
		{
			//CPacket packet = new CPacket();
			CPacket packet = CPacketBufferManager.pop();
			packet.set_protocol(protocol_id, context);
            return packet;
		}


        public static void destroy(CPacket packet)
		{
			CPacketBufferManager.push(packet);
		}

		public CPacket(byte[] buffer, IPeer owner)
		{
			// 참조로만 보관하여 작업한다.
			// 복사가 필요하면 별도로 구현해야 한다.
			this.buffer = buffer;

			// 헤더는 읽을필요 없으니 그 이후부터 시작한다.
			this.position = Defines.MSG_HEADER_SIZE;

			this.owner = owner;
		}

		public CPacket()
		{
			this.buffer = new byte[Defines.MSG_TOTAL_SIZE];
		}

		public Int16 pop_protocol_id()
		{
            this.position = Defines.MSG_HEADER_PROTOCOL_ID_POS;
            return pop((Int16)0);
		}
        public UInt16 pop_protocol_size()
        {
            this.position = Defines.MSG_HEADER_PROTOCOL_SIZE_POS;
            return pop((UInt16)0);
        }

		public void set_protocol(UInt16 protocol_id)
		{
			this.protocol_id = protocol_id;
            //this.buffer = new byte[Defines.MSG_TOTAL_SIZE];

            // 헤더는 나중에 넣을것이므로 데이터 부터 넣을 수 있도록 위치를 점프시켜놓는다.
            this.position = Defines.MSG_HEADER_SIZE;

			push(protocol_id);
		}
        public void set_protocol(UInt16 protocol_id, byte context)
        {
            this.protocol_id = protocol_id;
            //this.buffer = new byte[Defines.MSG_TOTAL_SIZE];

            // 헤더는 나중에 넣을것이므로 데이터 부터 넣을 수 있도록 위치를 점프시켜놓는다.
            this.position = Defines.MSG_HEADER_PROTOCOL_ID_POS;

            push(protocol_id);
            push(context);

			this.position = Defines.MSG_HEADER_SIZE;
        }
        public void set_context(byte context)
        {
            // 헤더는 나중에 넣을것이므로 데이터 부터 넣을 수 있도록 위치를 점프시켜놓는다.
            this.position = Defines.MSG_HEADER_PROTOCOL_RELIABLE;

            push(context);
        }

        public void record_size()
		{
			Int16 body_size = (Int16)(this.position - Defines.MSG_HEADER_SIZE);
			byte[] header = BitConverter.GetBytes(body_size);
			header.CopyTo(this.buffer, 0);
		}
        public void record_num()
        {
            UInt32 num = 0;
            this.position = Defines.MSG_HEADER_PROTOCOL_NUM_POS;

            push(num);
        }

        //buffer의 처음위치 지정한다.
        public void reset_pos(int size)
        {
            this.position = Defines.MSG_HEADER_SIZE + size;
        }

        public void Encrypt()
       {
            UInt16 size = (ushort)(this.position - Defines.MSG_HEADER_SIZE);
            //UInt16 size = BitConverter.ToUInt16(buffer, 0);

            byte[] enData = new byte[size];
            //encrypt
            Crypto.Encrypt(buffer, (uint)Defines.MSG_HEADER_SIZE, ref enData, 0, size);
            //copy
            Array.Copy(enData, 0, buffer, Defines.MSG_HEADER_SIZE, size);
        }

        public void Decrypt()
        {
            UInt16 size = BitConverter.ToUInt16(buffer, Defines.MSG_HEADER_PROTOCOL_SIZE_POS);
            byte[] deBuffer = new byte[size];
            FreeNet.Crypto.Decrypt(buffer, (uint)Defines.MSG_HEADER_SIZE, ref deBuffer, 0, size);
            Array.Copy(deBuffer, 0, buffer, FreeNet.Defines.MSG_HEADER_SIZE, size);
        }

        public sbyte pop(sbyte arg)
        {
            sbyte data = (sbyte)this.buffer[this.position];
            this.position += sizeof(sbyte);
            return data;
        }
        public byte pop(byte arg)
        {
            byte data = this.buffer[this.position];
            this.position += sizeof(byte);
            return data;
        }
        public Int16 pop(Int16 arg)
        {
            Int16 data = BitConverter.ToInt16(this.buffer, this.position);
            this.position += sizeof(Int16);
            return data;
        }
        public UInt16 pop(UInt16 arg)
        {
            UInt16 data = BitConverter.ToUInt16(this.buffer, this.position);
            this.position += sizeof(UInt16);
            return data;
        }

        public Int32 pop(Int32 arg)
        {
            Int32 data = BitConverter.ToInt32(this.buffer, this.position);
            this.position += sizeof(Int32);
            return data;
        }
        public UInt32 pop(UInt32 arg)
        {
            UInt32 data = BitConverter.ToUInt32(this.buffer, this.position);
            this.position += sizeof(UInt32);
            return data;
        }
        public UInt64 pop(UInt64 arg)
        {
            UInt64 data = BitConverter.ToUInt64(this.buffer, this.position);
            this.position += sizeof(UInt64);
            return data;
        }
        public float pop(float arg)
        {
            float data = BitConverter.ToSingle(this.buffer, this.position);
            this.position += sizeof(float);
            return data;
        }

        public string pop_string()
        {
            // 문자열 길이는 최대 2바이트 까지. 0 ~ 32767
            Int16 len = BitConverter.ToInt16(this.buffer, this.position);
            this.position += sizeof(Int16);

            // 인코딩은 utf8로 통일한다.
            string data = System.Text.Encoding.Unicode.GetString(this.buffer, this.position, len);
            this.position += len;

            return data;
        }
        //public string pop_utf8()
        //{
        //    // 문자열 길이는 최대 2바이트 까지. 0 ~ 32767
        //    Int16 len = BitConverter.ToInt16(this.buffer, this.position);
        //    this.position += sizeof(Int16);

        //    // 인코딩은 utf8로 통일한다.
        //    string data = System.Text.Encoding.UTF8.GetString(this.buffer, this.position, len);
        //    this.position += len;

        //    return data;
        //}

        public static void pop<T>(List<T> listData, ref CPacket msg) where T : BaseModel , new()
        {
            UInt16 count = msg.pop((UInt16)0); //count
            for (UInt16 i = 0; i < count; ++i)
            {
                T obj = new T();
                obj.UnpackInfo(msg);
                listData.Add(obj);
            }

        }

        public static void push<T>(List<T> listData, ref CPacket msg) where T : BaseModel
        {
            msg.push((UInt16)listData.Count);   //size
            foreach (T obj in listData) {
                obj.PackInfo(ref msg);
            }

        }

        public void push(sbyte data)
        {
            this.buffer[this.position] = (byte)data;
            this.position += sizeof(sbyte);
        }
        public void push(byte data)
        {
            this.buffer[this.position] = data;
            this.position += sizeof(byte);
        }
        public void push(Int16 data)
		{
			byte[] temp_buffer = BitConverter.GetBytes(data);
			temp_buffer.CopyTo(this.buffer, this.position);
			this.position += temp_buffer.Length;
		}
        public void push(UInt16 data)
        {
            byte[] temp_buffer = BitConverter.GetBytes(data);
            temp_buffer.CopyTo(this.buffer, this.position);
            this.position += temp_buffer.Length;
        }
        public void push(Int32 data)
		{
			byte[] temp_buffer = BitConverter.GetBytes(data);
			temp_buffer.CopyTo(this.buffer, this.position);
			this.position += temp_buffer.Length;
		}
        public void push(UInt32 data)
        {
            byte[] temp_buffer = BitConverter.GetBytes(data);
            temp_buffer.CopyTo(this.buffer, this.position);
            this.position += temp_buffer.Length;
        }
        public void push(UInt64 data)
        {
            byte[] temp_buffer = BitConverter.GetBytes(data);
            temp_buffer.CopyTo(this.buffer, this.position);
            this.position += temp_buffer.Length;
        }
        public void push(float data)
        {
            byte[] temp_buffer = BitConverter.GetBytes(data);
            temp_buffer.CopyTo(this.buffer, this.position);
            this.position += temp_buffer.Length;
        }

        public void push(string data)
		{
			byte[] temp_buffer = Encoding.Unicode.GetBytes(data);

			Int16 len = (Int16)temp_buffer.Length;
			byte[] len_buffer = BitConverter.GetBytes(len);
			len_buffer.CopyTo(this.buffer, this.position);
			this.position += sizeof(Int16);

			temp_buffer.CopyTo(this.buffer, this.position);
			this.position += temp_buffer.Length;
		}
	}
}
