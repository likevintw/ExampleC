//--------------------------------------------------------------------------------
// Xsens device API example for an MTi / MTx / Mtmk4 device using the C++ API
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//--------------------------------------------------------------------------------
#include <xsensdeviceapi.h> // The Xsens device API header
#include "serialkey.h"
#include <time.h>
#include <iostream>
#include <list>
#include <iomanip>
#include <string>
#include <conio.h> // for non ANSI _kbhit() and _getch()
#include <fstream>
using namespace std;
//--------------------------------------------------------------------------------
// CallbackHandler is an object derived from XsCallback that can be attached to 
// an XsDevice using the XsDevice::setCallbackHandler method.
// Various virtual methods which are automatically called by the XsDevice can be 
// overridden (See XsCallback)
// Only the onPostProcess(...) method is overridden here. This method is called 
// when a new data packet is available. 
// Note that this method will be called from within the thread of the XsDevice so
// proper synchronisation is required.
// It is recommended to keep the implementation of these methods fast; therefore 
// the only action here is to copy the packet to a queue where it can be 
// retrieved later by the main thread to be displayed. All access to the queue is 
// protected by a critical section because multiple threads are accessing it.
//--------------------------------------------------------------------------------

//Definition of Variables
// "#" means is was covered from original program by Kevin.
// The unit of length is millimeter
#define button_key 'd'	//鍵盤中鎖定和停止鎖定的字元鍵
#define stop_key 'p'	//To end program
#define SerialComPort 'COM1' 
#define radian_to_angle 57.29577//test

extern double now_yaw, now_pitch, now_roll;// now_angles
extern char state_flag;
//
float aver_time(0);	//counter of time
char test_flag(1); //for testing
int time_counter(0);
int RxBuf[1] = { 0 };
//test
int time_initial(0), time_finial(0);
int time_account(0);
double test1_X(0), test1_Y(0);

//HANDLE        hCom;		//RS232 Setting
//DWORD	cWriteBytes = 0;	 //RS232 Setting
//--------------------------------------------------------------------------------

//Definition of Functions
//RS232-Main
void create_com_port();
void close_com_port();
void create_read_event();
void close_read_event();
//stabilized_platform_algorithm_function
void B_button_and_state();
void C_execute();
//--------------------------------------------------------------------------------

class CallbackHandler : public XsCallback
{
public:
	CallbackHandler(size_t maxBufferSize = 5) : m_maxNumberOfPacketsInBuffer(maxBufferSize), m_numberOfPacketsInBuffer(0) { InitializeCriticalSection(&m_CriticalSection); }
	virtual ~CallbackHandler() throw() { DeleteCriticalSection(&m_CriticalSection); }

	bool packetAvailable() const { Locker lock(*this); return m_numberOfPacketsInBuffer > 0; }
	XsDataPacket getNextPacket()
	{
		assert(packetAvailable());
		Locker lock(*this);
		XsDataPacket oldestPacket(m_packetBuffer.front());
		m_packetBuffer.pop_front();
		--m_numberOfPacketsInBuffer;
		return oldestPacket;
	}

protected:
	virtual void onDataAvailable(const XsDataPacket* packet)
	{
		Locker lock(*this);
		assert(packet != 0);
		while (m_numberOfPacketsInBuffer >= m_maxNumberOfPacketsInBuffer)
		{
			(void)getNextPacket();
		}
		m_packetBuffer.push_back(*packet);
		++m_numberOfPacketsInBuffer;
		assert(m_numberOfPacketsInBuffer <= m_maxNumberOfPacketsInBuffer);
	}
private:
	mutable CRITICAL_SECTION m_CriticalSection;

	struct Locker
	{
		Locker(CallbackHandler const& self) : m_self(self) { EnterCriticalSection(&m_self.m_CriticalSection); }
		~Locker() throw() { LeaveCriticalSection(&m_self.m_CriticalSection); }
		CallbackHandler const& m_self;
	};
	size_t m_maxNumberOfPacketsInBuffer;
	size_t m_numberOfPacketsInBuffer;
	std::list<XsDataPacket> m_packetBuffer;
};

//--------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if (!setSerialKey())
	{
		std::cout << "Invalid serial key." << std::endl;
		std::cout << "Press [ENTER] to continue." << std::endl; std::cin.get();
		return 1;
	}
	// Create XsControl object
	//std::cout << "Creating XsControl object..." << std::endl;
	XsControl* control = XsControl::construct();
	assert(control != 0);
	try
	{
		// Scan for connected devices
		//std::cout << "Scanning for devices..." << std::endl;
		XsPortInfoList portInfoList = XsScanner::scanPorts();

		// Find an MTi / MTx / MTmk4 device
		XsPortInfoList::const_iterator mtPort = portInfoList.begin();
		while (mtPort != portInfoList.end() && !mtPort->deviceId().isMtix() && !mtPort->deviceId().isMtMk4()) { ++mtPort; }
		if (mtPort == portInfoList.end())
		{
			throw std::runtime_error("No MTi / MTx / MTmk4 device found. Aborting.");
		}
		//#Close the information of the device-ID 
		//std::cout << "Found a device with id: " << mtPort->deviceId().toString().toStdString() << " @ port: " << mtPort->portName().toStdString() << ", baudrate: " << mtPort->baudrate() << std::endl;

		// Open the port with the detected device
		//std::cout << "Opening port..." << std::endl;
		if (!control->openPort(mtPort->portName().toStdString(), mtPort->baudrate()))
		{
			throw std::runtime_error("Could not open port. Aborting.");
		}
		try
		{
			// Get the device object
			XsDevice* device = control->device(mtPort->deviceId());
			assert(device != 0);

			//#Close the information of device
			// Print information about detected MTi / MTx / MTmk4 device
			//std::cout << "Device: " << device->productCode().toStdString() << " opened." << std::endl;

			// Create and attach callback handler to device
			CallbackHandler callback;
			device->addCallbackHandler(&callback);

			// Put the device in configuration mode		
			//std::cout << "Putting device into configuration mode..." << std::endl;
			if (!device->gotoConfig()) // Put the device into configuration mode before configuring the device
			{
				throw std::runtime_error("Could not put device into configuration mode. Aborting.");
			}

			// Configure the device. Note the differences between MTix and MTmk4
			//std::cout << "Configuring the device..." << std::endl;
			if (device->deviceId().isMtix())
			{
				XsOutputMode outputMode = XOM_Orientation; // output orientation data
				XsOutputSettings outputSettings = XOS_OrientationMode_Quaternion; // output orientation data as quaternion
				XsDeviceMode deviceMode(100); // make a device mode with update rate: 100 Hz
				deviceMode.setModeFlag(outputMode);
				deviceMode.setSettingsFlag(outputSettings);

				// set the device configuration				
				if (!device->setDeviceMode(deviceMode))
				{
					throw std::runtime_error("Could not configure MTmki device. Aborting.");
					system("PAUSE");
				}
			}
			else if (device->deviceId().isMtMk4())
			{
				XsOutputConfiguration quat(XDI_Quaternion, 0);
				XsOutputConfigurationList configList;
				configList.push_back(quat);
				if (!device->setOutputConfiguration(configList))
				{

					throw std::runtime_error("Could not configure MTmk4 device. Aborting.");
				}
			}
			else
			{
				throw std::runtime_error("Unknown device while configuring. Aborting.");
			}

			// Put the device in measurement mode	
			//std::cout << "Putting device into measurement mode..." << std::endl;
			if (!device->gotoMeasurement())
			{
				throw std::runtime_error("Could not put device into measurement mode. Aborting.");
			}

			//std::cout << "\nMain loop (press any key to quit)" << std::endl;
			//std::cout << std::string(79, '-') << std::endl;

			//test_data_recode
			extern double test1_X, test1_Y;
			extern float freqency_of_angle_changing, servoZ_angle_1;
			//extern int angle_value,account;
			char filename[] = "Data_1.txt";
			fstream fp;
			fp.open(filename, ios::out);//開啟檔案





			///程式開始
			float angle_compen_angle1(0), angle_compen_angle2(0), angle_compensating(0);
			int time_initial(0);
			int time_accounter1(0), time_account2(0), time_account3(0);
			char angle_compen_flag(0);
			float yaw1(0);
			extern char encoder_dataX, encoder_dataY;
			create_com_port();// open com port
			create_read_event();//open read event
			printf("\n\n\n");
			while (state_flag > 0)
			{
				if (callback.packetAvailable())
				{
					clock_t time = clock();	//計算時間(initial)
					time = clock();
					XsDataPacket packet = callback.getNextPacket();
					XsEuler euler = packet.orientationEuler();
					now_yaw = euler.m_yaw;
					now_pitch = euler.m_pitch;
					now_roll = euler.m_roll;
					if (now_yaw < 0)
						now_yaw = (now_yaw + 360);
					if (time < 120000)
					{
						if (angle_compen_flag == 0)
						{
							angle_compen_flag = 1;
							angle_compen_angle1 = now_yaw;
							Sleep(10);
							time_initial = time;
						}
						else
						{
							angle_compensating = (now_yaw - angle_compen_angle1) / (time - time_initial);
						}
					}
					if (time > 300000)
					{
						if (angle_compen_flag == 1)
						{
							angle_compen_flag = 0;
							std::cout << "\r  For Really " << "rate: " << angle_compensating << "\n";
						}
					}

					yaw1 = now_yaw - 1 * angle_compensating * (time - time_initial);
					//printf("\r ratial %d time  encoderX= %d emcoder Y= %d ",angle_compensating,time,encoder_dataX,encoder_dataY);
					//std::cout<<"\r angle_compensating "<<angle_compensating*1000<<" time "<<time;


					B_button_and_state();
					C_execute();
					/*
					if(angle_value==0)
					{
						time_initial=clock();
					}
					if(angle_value==360)
					{
						time_finial=clock();
						freqency_of_angle_changing=time_finial-time_initial;
						freqency_of_angle_changing=1000/freqency_of_angle_changing;
					}
					*/

					//std::cout<<"\r"<<time<<"   "<<account;
					//std::cout<<"\r  "<<servoY_command<<"   "<<servoZ_command<<account;
					/*
					fp<<"time  "<<time<<"   "
					<<"locked_point   "<<locked_point_position[0]<<"   "<<locked_point_position[1]<<"   "<<locked_point_position[2]<<"   "
						<<"now_point   "<<now_point_position[0]<<"   "<<now_point_position[1]<<"   "<<now_point_position[2]<<"   "
						<<"locked angle    "<<locked_yaw<<"   "<<locked_pitch<<"   "<<locked_roll<<"   "
						<<"now angel     "<<now_yaw<<"   "<<now_pitch<<"   "<<now_roll<<"   "
						<<"dis   "<<encoder_dataX<<"   "<<encoder_dataY<<"   "
						<<"servo angle   "<<servoY_angle<<"   "<<servoZ_angle<<std::endl;

					*/
					/*
					fp<<"   "<<freqency_of_angle_changing
						<<"   "<<time<<"   "
						<<"  "<<test1_X<<"  "<<test1_Y
							<<"     "<<servoY_angle<<"    "<<servoZ_angle<<std::endl;
					*/
					/*monitor of time*/



					/*
					time=time/1000;
					if(time>20)
					{
						break;
					}
					time=time*1000;
					*/
					//Data Monitor
					/*
					std::cout <<"\r"
						<< " L:" << std::setw(2) << std::fixed << std::setprecision(2) << locked_point_position[0]<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << locked_point_position[1]<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << locked_point_position[2]
					<< " L:" << std::setw(2) << std::fixed << std::setprecision(2) << compensating_point_position[0]<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << compensating_point_position[1]<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << compensating_point_position[2]
					<< " L:" << std::setw(2) << std::fixed << std::setprecision(2) <<servoY_angle<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) <<servoZ_angle;
					*/
					/*
					std::cout <<"\r"
						<< " L:" << std::setw(2) << std::fixed << std::setprecision(2) << now_yaw<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << now_pitch<<" "
						<< std::setw(2) << std::fixed << std::setprecision(2) << now_roll;
					*/
					//counter start
					//time=clock()-time; //Counter (final)

					//showing the costing-time
					/*
					std::cout << "\r"
						<< "Spent:" << std::setw(10) << std::fixed << std::setprecision(2) <<time
							  <<"(ms)";
							  */

				}
				Sleep(0);
			}
			printf("\n\n\n");
			//後續動作 
			close_com_port();
			close_read_event();
			fp.close();//關閉檔案

			///程式結束
			//_getch();
			//std::cout << "\n" << std::string(79, '-') << "\n";
			//std::cout << std::endl;
		}
		catch (std::runtime_error const& error)
		{
			std::cout << error.what() << std::endl;
		}
		catch (...)
		{
			//std::cout << "An unknown fatal error has occured. Aborting." << std::endl;			
		}


		// Close port
		//std::cout << "Closing port..." << std::endl;
		control->closePort(mtPort->portName().toStdString());
	}

	catch (std::runtime_error const& error)
	{
		std::cout << error.what() << std::endl;
	}
	catch (...)
	{
		//std::cout << "An unknown fatal error has occured. Aborting." << std::endl;
	}

	// Free XsControl object
	//std::cout << "Freeing XsControl object..." << std::endl;
	control->destruct();

	//std::cout << "Successful exit." << std::endl;

	//std::cout << "Press [ENTER] to continue." << std::endl; std::cin.get();

	return 0;

}d