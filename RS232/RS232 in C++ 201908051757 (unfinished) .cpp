
//RS232 in C++ 201908051757 unfinished

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#define ComPort "COM1"

//Function Definition
void OpenComPort();
void CloseComPort();
void TX_Data(HANDLE hCom, int tx_data[1]);
char RX_Data(HANDLE hCom);

// Global Variable
int file_head[1] = { 254 };
int send_data[1] = { 200 };	//Tx data Buffer
char lpBuf[1] = { 5 };		//Rx data Buffer
HANDLE        hCom;
DWORD	cWriteBytes = 0;
////////////////////////////////////////////////////////////////////////////////////////////


void OpenComPort()
{
	DCB           dcb;
	COMMTIMEOUTS  cto;

	hCom = CreateFile(TEXT(ComPort), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);

	//If opening fail

	if (hCom == INVALID_HANDLE_VALUE)
	{
		printf("ComPort Number : ");
		printf(ComPort);
		printf("\n");
		printf(" Wasn't Opened!\n");
	}

	//if opening successful
	else
	{
		printf("COMPORT NUMBER : ");
		printf(ComPort);
		printf("\n");
		printf("Was Opened!\n");
		dcb.DCBlength = sizeof(dcb);
		GetCommState(hCom, &dcb);
		dcb.BaudRate = CBR_115200;
		dcb.fParity = FALSE;
		dcb.fNull = FALSE;
		dcb.StopBits = ONESTOPBIT;
		dcb.Parity = NOPARITY;
		dcb.ByteSize = 8;
		SetCommState(hCom, &dcb);
		cto.ReadIntervalTimeout = 0;
		cto.ReadTotalTimeoutMultiplier = 0;
		cto.ReadTotalTimeoutConstant = 0;
		cto.WriteTotalTimeoutMultiplier = 0;
		cto.WriteTotalTimeoutConstant = 0;
		SetCommTimeouts(hCom, &cto);
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	}
}
void CloseComPort()
{
	CloseHandle(hCom);
	printf("\n");
	printf("Com Port was Closed");
}
void TX_Data(HANDLE hCom, char tx_data[1])
{
	WriteFile(hCom, tx_data, 1, &cWriteBytes, 0);
}
char RX_Data(HANDLE hCom)
{
	//printf("data : %d\n",lpBuf[0]);
	//ReadFile(hCom, lpBuf, 1, &cWriteBytes, 0);
	//printf("\r RX_DATA = %d    ",lpBuf[0]);
	return lpBuf[0];


}

int main()
{
	HANDLE        hCom;
	DWORD	cWriteBytes = 0;
	hCom = CreateFile(TEXT(ComPort), GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);

	char buf[1] = {'a'};

	OpenComPort();
	TX_Data(hCom, buf);
	CloseComPort();
	return 0;
}