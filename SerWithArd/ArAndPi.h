#ifndef __LY_ArAndPi_Common_File__
#define __LY_ArAndPi_Common_File__
/**************************************
//定义bCode的各个指令代码，
//最多224个，从0x11到0xEF
//从0x00到0x10，0xF0到0xFF作为保留字
0xFE 作为arduino接收数据结束的标志
************************************/
#define CODE_COM_TEST_LY 0x11
#define CODE_COM_PRINTSTR_LY 0x12
#define CODE_COM_LIUPLED_LY 0x13

typedef unsigned char byte;
/*********************************
结构体和联合体定义
*/
typedef struct stSerialComProtocal{
	byte bCode;
	byte bEndByte;
    byte bDataLength;//数组中有效数据的长度，包括最后的终止符0xFE
	byte bReserved;
	byte abData[28];//该数组有效数据的最后一位必须是0xFE
} SERIAL_PROTOCAL_S;
/*bCode由用户控制，表示命令编号；
  bEndByte正常情况下为0
  bReserved正常情况下为0
  bDataLength为缓冲区有用数据的长度
  @@该结构中不允许出现0xFE字样，如有请提出说明，
  前面四个字段由由用户保证不会出现0xFE；
  如果abData中出现0xFE本函数将采用以下方法进行发送，请发送端和接收端做同样的编解码
  （1）扫描要复制的数据，如果有0xFE，则将整个数据以0xFE进行切分，依次发送
  （2）其中bEndByte表示切片的总数
  （3）bReserved字段表示当前片的排号
*/

typedef union unSerialTransDataFormat {
	SERIAL_PROTOCAL_S stData;
	byte arrayTrans[32];
} SERIAL_TRANSDATA_U;







#endif // __LY_ArAndPi_Common_File__
