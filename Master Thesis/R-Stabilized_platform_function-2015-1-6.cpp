#include <windows.h>
#include <conio.h>	//_kbhit()
#include <iostream>	//printf()
#include <iomanip>	//setw()
#include <math.h>
/*test*/
int angle_value(0);
int sleep_time(0);
float freqency_of_angle_changing(0);
int account(0);
float servoZ_angle_1(0);

#define button_key 'd'
#define stop_key 'p'
#define plus_key 'w'
#define minus_key 's'
#define radian_to_angle 57.29577

//rs232(2014-1228)
char get_rx_data();	//rx
BOOL WriteABuffer(char* lpBuf, DWORD dwToWrite);	//tx
//functions
void B_button_and_state();
void C_execute();
void C21_1_record_information_of_locked_point();
void C21_locked_point_position();
void C22_sent_locked_flag_to_propeller();
void C31_receive_encoder_data_from_propeller();
void C32_compensating_algorithm();
void C33_sent_servo_command_to_propeller();
void test_now_point_position();
void test_now_compensating_point();
void test_sinewave_to_servo();
void test_servo_angle_curve_fitting();
////////////////////
void B_button_and_state()
{
	extern char state_flag;
	if (_kbhit())	//如果有按按鍵
	{
		switch (_getch())
		{
		case button_key:
			switch (state_flag)
			{
			case 1:
				state_flag = 2;
				break;
			case 3:
				state_flag = 4;
				break;
			}
			break;
		case stop_key:
		{
			state_flag = 0;
			std::cout << "\r State : " << std::fixed << "Program is closing...";
		}
		break;
		case plus_key:
		{
			sleep_time++;
		}
		break;
		case minus_key:
		{
			sleep_time--;
			if (sleep_time < 1)
				sleep_time = 1;
		}
		break;
		}
	}
}
void C_execute()
{

	extern char state_flag;
	extern float locked_point_position[];
	extern float locked_yaw, locked_pitch, locked_roll;
	extern float locked_laser_distance;
	extern float distance_of_rotation_centers;
	extern float now_laser_distance;
	extern float compensating_point_position[3];
	//test
	extern float servoY_angle, servoZ_angle;
	//

	switch (state_flag)
	{
	case 1:	//狀態一:瞄準中(未鎖定)
		break;
	case 2:	//狀態二:開始鎖定	
		std::cout << "\r                                                         ";
		std::cout << "\r State : " << std::fixed << "  Locked";
		//計算鎖定點
		C21_locked_point_position();
		//傳送狀態給晶片
		C22_sent_locked_flag_to_propeller();
		//狀態改成繼續鎖定
		state_flag = 3;
		break;
	case 3:	//狀態三:繼續鎖定

		//讀取移動位移資料
		C31_receive_encoder_data_from_propeller();
		//補償演算法
		C32_compensating_algorithm();
		//test_now_point_position();
		//test_now_compensating_point();
		//發送補償訊號給伺服機

		//Sleep(sleep_time);
		//test_sinewave_to_servo();
		//test_servo_angle_curve_fitting();
		C33_sent_servo_command_to_propeller();
		break;
	case 4: //狀態四:停止鎖定
		std::cout << "\r                                                         ";
		std::cout << "\r State : " << std::fixed << "Unlocked";
		//伺服機角度歸零
		servoY_angle = 0;
		servoZ_angle = 0;
		//傳送命令給伺服機
		C33_sent_servo_command_to_propeller();
		//狀態改成瞄準
		state_flag = 1;
		break;
	}
}


void C21_locked_point_position()
{
	extern float locked_point_position[4];
	extern float locked_yaw, locked_pitch, locked_roll;
	extern float locked_laser_distance;
	extern float distance_of_rotation_centers;
	extern double now_yaw, now_pitch, now_roll;
	//record the locked angle
	locked_yaw = float(now_yaw);
	locked_pitch = float(now_pitch);
	locked_roll = float(now_roll);
	// angle to radain
	locked_yaw = float(locked_yaw / radian_to_angle);
	locked_pitch = float(locked_pitch / radian_to_angle);
	locked_roll = float(locked_roll / radian_to_angle);
	//locked point position calculating
	locked_point_position[0] =
		locked_laser_distance * (cos(locked_yaw) * cos(locked_pitch))
		+ distance_of_rotation_centers
		* (cos(locked_yaw) * sin(locked_pitch) * cos(locked_roll) + sin(locked_yaw) * sin(locked_roll));
	locked_point_position[1] =
		locked_laser_distance * (sin(locked_yaw) * cos(locked_pitch))
		+ distance_of_rotation_centers
		* (sin(locked_yaw) * sin(locked_pitch) * cos(locked_roll) - cos(locked_yaw) * sin(locked_roll));
	locked_point_position[2] =
		locked_laser_distance * (-sin(locked_pitch))
		+ distance_of_rotation_centers * cos(locked_pitch) * cos(locked_roll);
	locked_point_position[3] = 1;
	//  radain to angle 
	locked_yaw = float(locked_yaw * radian_to_angle);
	locked_pitch = float(locked_pitch * radian_to_angle);
	locked_roll = float(locked_roll * radian_to_angle);





}
void C22_sent_locked_flag_to_propeller()
{
	extern HANDLE hCom;
	extern char state_flag;
	extern char rs232_state_flag_header;
	extern char rs232_state_flag_tailer;
	char tx_data[1] = { 0 };
	char rx_data(0);
	char rs232_rx_check = 0;
	char rs232_flag = 1;
	while (1)
	{
		//printf("\n");
		tx_data[0] = rs232_state_flag_header;				//設定檔頭	
		WriteABuffer(tx_data, 1);						//傳送檔頭
		//printf("Send the data : %d  \n",tx_data[0]);
		tx_data[0] = state_flag;										//設定狀態
		WriteABuffer(tx_data, 1);									//傳送狀態
		//rx_data=RX_Data(hCom);								//接受回傳
		//printf("received rx data : %d  \n",rx_data);
		//rs232_rx_check=rs232_state_flag_tailer;		//回傳值check
		//printf("received rs232_rx_check data : %d  \n",rs232_rx_check);
		/*
		if(rx_data==rs232_rx_check)							//檢查回傳
		{
			rs232_flag=0;
		}
		*/
		break;
	}
}

void C31_receive_encoder_data_from_propeller()
{
	extern char lpBuf[4];
	extern HANDLE hCom;
	extern char rs232_receive_encoder_data_header;
	extern char rs232_receive_encoder_data_tailer;
	char tx_data[1] = { 0 };
	char rx_data(0);
	int test1(0);
	extern char encoder_signX, encoder_signY, encoder_dataX, encoder_dataY;

	while (1)
	{
		//printf("\n");
		tx_data[0] = rs232_receive_encoder_data_header;				//設定檔頭	
		WriteABuffer(tx_data, 1);//傳送檔頭
		rx_data = get_rx_data();
		encoder_signX = lpBuf[0];						//接受Encoder X Data 1
		encoder_dataX = lpBuf[1];						//接受Encoder X Data 2
		encoder_signY = lpBuf[2];						//接受Encoder Y Data 1
		encoder_dataY = lpBuf[3];
		/*//接受Encoder Y Data 2
		printf("\r encoder_signX: %d encoder_dataX: %d encoder_signY: %d encoder_dataY: %d"
			,lpBuf[0],lpBuf[1],lpBuf[2],lpBuf[3]);
			*/
		if (encoder_signX == 2)
			encoder_dataX = -encoder_dataX;
		if (encoder_signY == 2)
			encoder_dataY = -encoder_dataY;
		//printf("\r encoderX= %d emcoder Y= %d ",encoder_dataX,encoder_dataY);
		break;
	}
}
void C32_compensating_algorithm()
{
	extern float locked_point_position[4];										//鎖定點座標
	extern char encoder_dataX, encoder_dataY, encoder_dataZ;	//平台移動距離
	extern float distance_of_rotation_centers;								//兩旋轉軸之距離
	extern float compensating_point_position[4];							//受干擾後鎖定點座標
	extern double now_yaw, now_pitch, now_roll;							//目前平台姿態角度
	extern float now_laser_distance;												//補償後之雷射光距離
	double inversed_transform_matrix[4][4] = { 0 };							//反矩陣
	double move_vector_transformation[4] = { 0 };							//移動干擾向量
	//extern float servoY_command,servoZ_command;					//伺服機命令
	extern float servoY_angle, servoZ_angle;									//伺服機角度
	float servoY_angle_old(0), servoZ_angle_old(0);
	float old_controlY(0), old_controlZ(0), difference_controlY(0), difference_controlZ(0);
	//test
	extern float locked_yaw, locked_pitch, locked_roll;
	extern double test1_X, test1_Y;
	//printf("\r encoderX= %d emcoder Y= %d ",encoder_dataX,encoder_dataY);

	//angle to randian
	now_yaw = now_yaw / radian_to_angle;
	now_pitch = now_pitch / radian_to_angle;
	now_roll = now_roll / radian_to_angle;
	//位移向量

	move_vector_transformation[0] = encoder_dataX
		+ distance_of_rotation_centers * (cos(now_yaw) * sin(now_pitch) * cos(now_roll) + sin(now_yaw) * sin(now_roll));
	move_vector_transformation[1] = encoder_dataY
		+ distance_of_rotation_centers * (sin(now_yaw) * sin(now_pitch) * cos(now_roll) - cos(now_yaw) * sin(now_roll));
	move_vector_transformation[2] = encoder_dataZ
		+ distance_of_rotation_centers * cos(now_pitch) * cos(now_roll);
	move_vector_transformation[3] = 1;
	test1_X = move_vector_transformation[0];
	test1_Y = move_vector_transformation[1];
	//反矩陣
	inversed_transform_matrix[0][0] = cos(now_yaw) * cos(now_pitch);
	inversed_transform_matrix[0][1] = sin(now_yaw) * cos(now_pitch);
	inversed_transform_matrix[0][2] = -sin(now_pitch);
	inversed_transform_matrix[0][3] =
		-(inversed_transform_matrix[0][0] * move_vector_transformation[0]
			+ inversed_transform_matrix[0][1] * move_vector_transformation[1]
			+ inversed_transform_matrix[0][2] * move_vector_transformation[2]);

	inversed_transform_matrix[1][0] = (cos(now_yaw) * sin(now_pitch) * sin(now_roll))
		- (sin(now_yaw) * cos(now_roll));
	inversed_transform_matrix[1][1] = (sin(now_yaw) * sin(now_pitch) * sin(now_roll))
		+ (cos(now_yaw) * cos(now_roll));
	inversed_transform_matrix[1][2] = cos(now_pitch) * sin(now_roll);
	inversed_transform_matrix[1][3] =
		-(inversed_transform_matrix[1][0] * move_vector_transformation[0]
			+ inversed_transform_matrix[1][1] * move_vector_transformation[1]
			+ inversed_transform_matrix[1][2] * move_vector_transformation[2]);

	inversed_transform_matrix[2][0] = (cos(now_yaw) * sin(now_pitch) * cos(now_roll))
		+ (sin(now_yaw) * sin(now_roll));
	inversed_transform_matrix[2][1] = (sin(now_yaw) * sin(now_pitch) * cos(now_roll))
		- (cos(now_yaw) * sin(now_roll));
	inversed_transform_matrix[2][2] = cos(now_pitch) * cos(now_roll);
	inversed_transform_matrix[2][3] =
		-(inversed_transform_matrix[2][0] * move_vector_transformation[0]
			+ inversed_transform_matrix[2][1] * move_vector_transformation[1]
			+ inversed_transform_matrix[2][2] * move_vector_transformation[2]);

	inversed_transform_matrix[3][0] = 0;
	inversed_transform_matrix[3][1] = 0;
	inversed_transform_matrix[3][2] = 0;
	inversed_transform_matrix[3][3] = 1;

	//compensating vector counting
	for (int i(0); i < 4; i++)
	{
		double elment(0);
		for (int j(0); j < 4; j++)
		{
			elment = elment + inversed_transform_matrix[i][j] * locked_point_position[j];
		}
		compensating_point_position[i] = float(elment);
	}

	//Z-axis servo angle
	servoZ_angle = float(atan(compensating_point_position[1] / compensating_point_position[0]) * radian_to_angle);
	//tangent(tan)  angle compensation : case 1 (-,+)
	if ((compensating_point_position[1] > 0) && (compensating_point_position[0] < 0))
	{
		servoZ_angle = 360 + servoY_angle;
	}

	//tangent(tan)  angle compensation : case 2 (-,-)
	if ((compensating_point_position[1] < 0) && (compensating_point_position[0] < 0))
	{
		servoZ_angle = 180 + servoZ_angle;
	}
	//tangent(tan)  angle compensation : case 3 (+,-)
	if ((compensating_point_position[1] < 0) && (compensating_point_position[0] > 0))
	{
		//servoZ_angle=servoZ_angle;
	}
	//Y-axis servo angle
	servoY_angle = float(atan(sin(servoZ_angle / radian_to_angle) * compensating_point_position[2] / compensating_point_position[1]) * radian_to_angle);

	//compensation-angle-convergency
	//the rate is 0 now
	if (abs(servoY_angle_old - servoY_angle) > 0)
	{
		servoY_angle_old = servoY_angle;
	}
	else
	{
		servoY_angle = servoY_angle_old;
	}
	if (abs(servoZ_angle_old - servoZ_angle) > 0)
	{
		servoZ_angle_old = servoZ_angle;
	}
	else
	{
		servoZ_angle = servoZ_angle_old;
	}
	//distance of Laser(now_laser_distance)
	now_laser_distance = compensating_point_position[2] / sin(servoY_angle / radian_to_angle);
	//randin to angle
	now_yaw = now_yaw * radian_to_angle;
	now_pitch = now_pitch * radian_to_angle;
	now_roll = now_roll * radian_to_angle;



}
void C33_sent_servo_command_to_propeller()
{
	extern HANDLE hCom;
	extern float servoY_command, servoZ_command;
	extern float servoY_angle, servoZ_angle;
	extern char rs232_sent_servo_data_header;
	extern char rs232_sent_servo_data_tariler;
	char tx_data[1] = { 0 };
	char rx_data(0);
	char servoY_command_2(0), servoZ_command_2(0);

	//補償角度到伺服機角度

	servoY_angle = servoY_angle * 1.0348 - 10.82;
	servoZ_angle = servoZ_angle * 0.975 - 11.5 - 0.9751;
	////補償角度轉換至伺服機命令
	servoY_command = 0.4675 * servoY_angle + 75;
	servoZ_command = -0.4575 * servoZ_angle + 66;

	//showing the angles of servo
/*
	std::cout <<"\r"<< "servoX_data :" << std::fixed << std::setprecision(2) <<servoX_data
					<< "  servoZ_data :" << std::fixed << std::setprecision(2) << servoZ_data;
					*/
					//傳送角度命令給Propeller
					//目前傳送精度 1度
	while (1)
	{
		servoY_command_2 = servoY_command;
		servoZ_command_2 = servoZ_command;
		//printf("\n");
		tx_data[0] = rs232_sent_servo_data_header;						//設定檔頭	
		WriteABuffer(tx_data, 1);											//傳送檔頭
		tx_data[0] = servoY_command;										//設定servoY_data command
		WriteABuffer(tx_data, 1);											//傳送servoY_data command
		tx_data[0] = (servoY_command - servoY_command_2) * 10;//設定servoY_data command_2
		WriteABuffer(tx_data, 1);								//傳送servoY_data command_2
		//printf("servoX_data : %d  \n",tx_data[0]);
		tx_data[0] = servoZ_command;							//設定servoZ_data command
		WriteABuffer(tx_data, 1);								//傳送servoZ_data command
		tx_data[0] = (servoZ_command - servoZ_command_2) * 10;							//設定servoZ_data command_2
		WriteABuffer(tx_data, 1);								//傳送servoZ_data command_2
		//rx_data=RX_Data(hCom);								//接受回傳
		//printf("received rx data : %d  \n",rx_data);
		//rs232_rx_check=rs232_state_flag_tailer;		//回傳值check
		//printf("received rs232_rx_check data : %d  \n",rs232_rx_check);
		/*
		if(rx_data==rs232_rx_check)							//檢查回傳
		{
			rs232_flag=0;
		}
		*/

		break;
	}
}

void test_now_point_position()
{
	extern float now_point_position[4];
	extern double now_yaw, now_pitch, now_roll;// now_angles
	extern float now_laser_distance;
	extern float locked_laser_distance;
	extern float distance_of_rotation_centers;
	extern char encoder_dataX, encoder_dataY, encoder_dataZ;	//平台移動距離
	extern float servoY_angle, servoZ_angle;
	double transform_matrix[4][4] = { 0 };
	double point_vector[4] = { 0 };
	//double test1(0);
	// angle to radain
	now_yaw = float(now_yaw / radian_to_angle);
	now_pitch = float(now_pitch / radian_to_angle);
	now_roll = float(now_roll / radian_to_angle);
	servoY_angle = float(servoY_angle / radian_to_angle);
	servoZ_angle = float(servoZ_angle / radian_to_angle);
	//vector matrix
	point_vector[0] = now_laser_distance;
	point_vector[1] = 0;
	point_vector[2] = 0;
	point_vector[3] = 1;
	//transform matrix
	transform_matrix[0][0] = cos(now_yaw) * cos(now_pitch);
	transform_matrix[0][1] = (cos(now_yaw) * sin(now_pitch) * sin(now_roll))
		- (sin(now_yaw) * cos(now_roll));
	transform_matrix[0][2] = (cos(now_yaw) * sin(now_pitch) * cos(now_roll))
		+ (sin(now_yaw) * sin(now_roll));
	transform_matrix[0][3] = encoder_dataX
		+ distance_of_rotation_centers * (cos(now_yaw) * sin(now_pitch) * cos(now_roll))
		+ (sin(now_yaw) * sin(now_roll));

	transform_matrix[1][0] = sin(now_yaw) * cos(now_pitch);
	transform_matrix[1][1] = (sin(now_yaw) * sin(now_pitch) * sin(now_roll))
		+ (cos(now_yaw) * cos(now_roll));
	transform_matrix[1][2] = (sin(now_yaw) * sin(now_pitch) * cos(now_roll))
		- (cos(now_yaw) * sin(now_roll));
	transform_matrix[1][3] = encoder_dataY
		+ distance_of_rotation_centers * (sin(now_yaw) * sin(now_pitch) * cos(now_roll))
		- (cos(now_yaw) * sin(now_roll));

	transform_matrix[2][0] = -sin(now_pitch);
	transform_matrix[2][1] = cos(now_pitch) * sin(now_roll);
	transform_matrix[2][2] = cos(now_pitch) * cos(now_roll);
	transform_matrix[2][3] = encoder_dataZ
		+ distance_of_rotation_centers * cos(now_pitch) * cos(now_roll);

	transform_matrix[3][0] = 0;
	transform_matrix[3][1] = 0;
	transform_matrix[3][2] = 0;
	transform_matrix[3][3] = 1;
	//compensating vector counting
	for (int i(0); i < 4; i++)
	{
		double elment(0);
		for (int j(0); j < 4; j++)
		{
			elment = elment + transform_matrix[i][j] * point_vector[j];
		}
		now_point_position[i] = float(elment);
	}
	// angle to radain
	now_yaw = float(now_yaw * radian_to_angle);
	now_pitch = float(now_pitch * radian_to_angle);
	now_roll = float(now_roll * radian_to_angle);
	servoY_angle = float(servoY_angle * radian_to_angle);
	servoZ_angle = float(servoZ_angle * radian_to_angle);

}

void test_now_compensating_point()
{
	extern float now_compensating_point_position[4];
	extern double now_yaw, now_pitch, now_roll;// now_angles
	extern float now_laser_distance;
	extern float locked_laser_distance;
	extern float distance_of_rotation_centers;
	extern char encoder_dataX, encoder_dataY, encoder_dataZ;	//平台移動距離
	extern float servoY_angle, servoZ_angle;
	double transform_matrix[4][4] = { 0 };
	double point_vector[4] = { 0 };
	//double test1(0);
	// angle to radain
	now_yaw = float(now_yaw / radian_to_angle);
	now_pitch = float(now_pitch / radian_to_angle);
	now_roll = float(now_roll / radian_to_angle);
	servoY_angle = float(servoY_angle / radian_to_angle);
	servoZ_angle = float(servoZ_angle / radian_to_angle);
	//vector matrix

	point_vector[0] = now_laser_distance * cos(servoZ_angle) * cos(servoY_angle);
	point_vector[1] = now_laser_distance * sin(servoZ_angle) * cos(servoY_angle);
	point_vector[2] = now_laser_distance * sin(servoY_angle);
	point_vector[3] = 1;

	//transform matrix
	transform_matrix[0][0] = cos(now_yaw) * cos(now_pitch);
	transform_matrix[0][1] = (cos(now_yaw) * sin(now_pitch) * sin(now_roll))
		- (sin(now_yaw) * cos(now_roll));
	transform_matrix[0][2] = (cos(now_yaw) * sin(now_pitch) * cos(now_roll))
		+ (sin(now_yaw) * sin(now_roll));
	transform_matrix[0][3] = encoder_dataX
		+ distance_of_rotation_centers * (cos(now_yaw) * sin(now_pitch) * cos(now_roll))
		+ (sin(now_yaw) * sin(now_roll));

	transform_matrix[1][0] = sin(now_yaw) * cos(now_pitch);
	transform_matrix[1][1] = (sin(now_yaw) * sin(now_pitch) * sin(now_roll))
		+ (cos(now_yaw) * cos(now_roll));
	transform_matrix[1][2] = (sin(now_yaw) * sin(now_pitch) * cos(now_roll))
		- (cos(now_yaw) * sin(now_roll));
	transform_matrix[1][3] = encoder_dataY
		+ distance_of_rotation_centers * (sin(now_yaw) * sin(now_pitch) * cos(now_roll))
		- (cos(now_yaw) * sin(now_roll));

	transform_matrix[2][0] = -sin(now_pitch);
	transform_matrix[2][1] = cos(now_pitch) * sin(now_roll);
	transform_matrix[2][2] = cos(now_pitch) * cos(now_roll);
	transform_matrix[2][3] = encoder_dataZ
		+ distance_of_rotation_centers * cos(now_pitch) * cos(now_roll);

	transform_matrix[3][0] = 0;
	transform_matrix[3][1] = 0;
	transform_matrix[3][2] = 0;
	transform_matrix[3][3] = 1;
	//compensating vector counting
	for (int i(0); i < 4; i++)
	{
		double elment(0);
		for (int j(0); j < 4; j++)
		{
			elment = elment + transform_matrix[i][j] * point_vector[j];
		}
		now_compensating_point_position[i] = float(elment);
	}
	// angle to radain
	now_yaw = float(now_yaw * radian_to_angle);
	now_pitch = float(now_pitch * radian_to_angle);
	now_roll = float(now_roll * radian_to_angle);
	servoY_angle = float(servoY_angle * radian_to_angle);
	servoZ_angle = float(servoZ_angle * radian_to_angle);

}
void test_sinewave_to_servo()
{
	extern HANDLE hCom;
	extern double now_yaw, now_pitch, now_roll;
	extern float servoY_command, servoZ_command;
	extern float servoY_angle, servoZ_angle;
	extern char rs232_sent_servo_data_header;
	extern char rs232_sent_servo_data_tariler;
	char tx_data[1] = { 0 };
	char rx_data(0);
	extern int angle_value;
	now_yaw = now_yaw - 281.007;


	servoZ_angle = 60 * sin(angle_value / 57.3);
	std::cout << angle_value << " servoZ_angle: " << servoZ_angle << " now_yaw: " << now_yaw << std::endl;
	angle_value = angle_value + 1;
	if (angle_value > 360)
		angle_value = 0;
	////補償角度轉換至伺服機命令
	servoY_command = -0.4675 * servoY_angle + 85;
	servoZ_command = -0.4575 * servoZ_angle + 66;

	//傳送角度命令給Propeller
	//目前傳送精度 1度

	//printf("\n");
	tx_data[0] = rs232_sent_servo_data_header;			//設定檔頭	
	WriteABuffer(tx_data, 1);									//傳送檔頭
	tx_data[0] = servoY_command;								//設定servoX_data command
	WriteABuffer(tx_data, 1);									//傳送servoX_data command
	tx_data[0] = servoZ_command;								//設定servoZ_data command
	WriteABuffer(tx_data, 1);									//傳送servoZ_data command				

}
void test_servo_angle_curve_fitting()
{
	extern HANDLE hCom;
	extern double now_yaw, now_pitch, now_roll;
	extern float servoY_command, servoZ_command;
	extern float servoY_angle, servoZ_angle;
	extern char rs232_sent_servo_data_header;
	extern char rs232_sent_servo_data_tariler;
	char tx_data[1] = { 0 };
	char rx_data(0);
	extern int angle_value;
	extern int sleep_time;
	extern float freqency_of_angle_changing;
	extern float servoZ_angle_1;

	servoZ_angle = 60 * sin(angle_value / 57.3);
	//freqency_of_angle_changing=2.77/sleep_time;

	/*
	std::cout<<"fre:"<<freqency_of_angle_changing<<" ang:"<<angle_value
		<<" servoZ_angle: "<<servoZ_angle<<" now_yaw: "<<now_yaw<<std::endl;
		*/
	angle_value = int(angle_value + 1);
	account = account + 1;
	if (angle_value > 360)
		angle_value = 0;

	//補償角度到伺服機角度
	servoY_angle = 0;
	servoZ_angle_1 = 1.0348 * servoZ_angle - 10.82;
	//Z軸伺服機補償servoZ_angle=servoZ_angle*0.975-11.5;
	//伺服機角度轉換至伺服機命令
	//servoY_command=-0.4675*servoY_angle_1+85;
	servoZ_command = -0.4575 * servoZ_angle_1 + 66;

	//傳送角度命令給Propeller
	//目前傳送精度 1度

	//printf("\n");
	//tx_data[0]=rs232_sent_servo_data_header;			//設定檔頭	
	//TX_Data(hCom ,tx_data);									//傳送檔頭
	//tx_data[0]=servoY_command;								//設定servoX_data command
	//TX_Data(hCom , tx_data);									//傳送servoX_data command
	//tx_data[0]=servoZ_command;								//設定servoZ_data command
	//TX_Data(hCom , tx_data);									//傳送servoZ_data command				

}