#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "ArAndPi.h"

/*******************************************************
利用 wiringPiSetupSys 进行初始化时必须使用 BCM 编号
     wiringPiSetup 使用的是wiringPi 引脚编号表
	 wiringPiSetupGpio 使用的是BCM GPIO 引脚编号表
//选择不同的初始化函数，一定要使用对应的引脚编号表
*/

int g_fSerial = 0;





/*****************************************************
param:
byte bCode;
byte bDataLength;//数组中有效数据的长度，包括最后的终止符0xFE
byte abData[28];//该数组有效数据的最后一位必须是0xFE

******************************************************/
int fnSendDataWithSerial(byte bCode,byte bDataLength,byte *abBuffer)
{
	SERIAL_TRANSDATA_U uTransData;
	int i;
	int iNumOfFE;
	int iRet;

	//发送数据不能超过27个，否则返回错误-1
	if (bDataLength >= 27)
	{
		return -1;
	}

	
	iNumOfFE = 0;

	//对缓冲区进行扫描，看看是否有0xFE
	for ( i = 0; i < bDataLength; i++)
	{
		if (0xFE == abBuffer[i])
		{
			iNumOfFE++;
		}
	}


	uTransData.stData.bCode = bCode;

	/*如果没有0xFE，则直接进行发送,并返回发送的数据量*/
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
	

	/*如果有0xFE，则进行多次发送*/
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
	//	digitalwrite(led, high);  //开
	//	delay(500); // 毫秒
	//	digitalwrite(led, low);	  //关
	//	delay(500);
	//}
	serialClose(fSerial);
	return 0;
}
