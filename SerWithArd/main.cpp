#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "ArAndPi.h"

/*******************************************************
���� wiringPiSetupSys ���г�ʼ��ʱ����ʹ�� BCM ���
     wiringPiSetup ʹ�õ���wiringPi ���ű�ű�
	 wiringPiSetupGpio ʹ�õ���BCM GPIO ���ű�ű�
//ѡ��ͬ�ĳ�ʼ��������һ��Ҫʹ�ö�Ӧ�����ű�ű�
*/

int g_fSerial = 0;





/*****************************************************
param:
byte bCode;
byte bDataLength;//��������Ч���ݵĳ��ȣ�����������ֹ��0xFE
byte abData[28];//��������Ч���ݵ����һλ������0xFE

******************************************************/
int fnSendDataWithSerial(byte bCode,byte bDataLength,byte *abBuffer)
{
	SERIAL_TRANSDATA_U uTransData;
	int i;
	int iNumOfFE;
	int iRet;

	//�������ݲ��ܳ���27�������򷵻ش���-1
	if (bDataLength >= 27)
	{
		return -1;
	}

	
	iNumOfFE = 0;

	//�Ի���������ɨ�裬�����Ƿ���0xFE
	for ( i = 0; i < bDataLength; i++)
	{
		if (0xFE == abBuffer[i])
		{
			iNumOfFE++;
		}
	}


	uTransData.stData.bCode = bCode;

	/*���û��0xFE����ֱ�ӽ��з���,�����ط��͵�������*/
	if (0 == iNumOfFE)
	{
		uTransData.stData.bEndByte = 0x00;
		uTransData.stData.bReserved = 0x00;
		uTransData.stData.bDataLength = bDataLength + 1;
		memcpy(uTransData.stData.abData, abBuffer, bDataLength);
		uTransData.stData.abData[bDataLength] = 0xFE;
		iRet = write(g_fSerial, uTransData.arrayTrans, uTransData.stData.bDataLength + 4);
		return iRet;
	}
	

	/*�����0xFE������ж�η���*/
	//need to be coding here$$$$$$$$$$$$$$$

	return -1;
}

/*****************************************************
param:

******************************************************/
int fnSendTest(byte bOnOff)
{
	byte bCode = 0x11;
	byte bLen = 0x01;
	byte abBuffer[28];

	abBuffer[0] = bOnOff;

	return fnSendDataWithSerial(bCode, 1, abBuffer);

}
/*****************************************************
param:

******************************************************/
int main(void)
{
	int fSerial;
	int iInput = 0;
	bool bExit;
	if (-1 == wiringPiSetupSys())
	{
		printf("wiringPi initialization failed!\r");
		return -1;
	}

	fSerial = serialOpen("/dev/ttyAMA0", 9600);
	if (-1 == fSerial)
	{
		printf("Serial /dev/ttyAMA0 open failed!\r");
		return -2;
	}
	g_fSerial = fSerial;

	bExit = false;
	while (!bExit)
	{
		scanf("%d", &iInput);
		switch (iInput)
		{
		case 0:
			fnSendTest(0);
			break;
		case 1:
			fnSendTest(1);
			break;
		case 2:
			serialPutchar(fSerial, 0x32);
			break;
		case 3:
			serialPuts(fSerial, "This is a good day!");
			break;
		case 4:
			serialPrintf(fSerial, "Serial port hanlder is %d", fSerial);
			break;
		case 99:
			bExit = true;
			break;
		default:
			break;
		}
	}


//	pinMode(LED, OUTPUT);

	//while (true)
	//{
	//	digitalwrite(led, high);  //��
	//	delay(500); // ����
	//	digitalwrite(led, low);	  //��
	//	delay(500);
	//}
	serialClose(fSerial);
	return 0;
}
