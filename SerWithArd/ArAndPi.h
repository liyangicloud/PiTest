#ifndef __LY_ArAndPi_Common_File__
#define __LY_ArAndPi_Common_File__
/**************************************
//����bCode�ĸ���ָ����룬
//���224������0x11��0xEF
//��0x00��0x10��0xF0��0xFF��Ϊ������
0xFE ��Ϊarduino�������ݽ����ı�־
************************************/
#define CODE_COM_TEST_LY 0x11
#define CODE_COM_PRINTSTR_LY 0x12
#define CODE_COM_LIUPLED_LY 0x13

typedef unsigned char byte;
/*********************************
�ṹ��������嶨��
*/
typedef struct stSerialComProtocal{
	byte bCode;
	byte bEndByte;
    byte bDataLength;//��������Ч���ݵĳ��ȣ�����������ֹ��0xFE
	byte bReserved;
	byte abData[28];//��������Ч���ݵ����һλ������0xFE
} SERIAL_PROTOCAL_S;
/*bCode���û����ƣ���ʾ�����ţ�
  bEndByte���������Ϊ0
  bReserved���������Ϊ0
  bDataLengthΪ�������������ݵĳ���
  @@�ýṹ�в��������0xFE���������������˵����
  ǰ���ĸ��ֶ������û���֤�������0xFE��
  ���abData�г���0xFE���������������·������з��ͣ��뷢�Ͷ˺ͽ��ն���ͬ���ı����
  ��1��ɨ��Ҫ���Ƶ����ݣ������0xFE��������������0xFE�����з֣����η���
  ��2������bEndByte��ʾ��Ƭ������
  ��3��bReserved�ֶα�ʾ��ǰƬ���ź�
*/

typedef union unSerialTransDataFormat {
	SERIAL_PROTOCAL_S stData;
	byte arrayTrans[32];
} SERIAL_TRANSDATA_U;







#endif // __LY_ArAndPi_Common_File__
