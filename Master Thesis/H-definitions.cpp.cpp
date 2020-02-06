char state_flag(1);	//stage_state 穩定平台之狀態
double now_yaw(0), now_pitch(0), now_roll(0);// now_angles
float locked_yaw(0), locked_pitch(0), locked_roll(0);// locked_angles
float servoY_command(0), servoZ_command(0); //伺服機命令
float servoY_angle(0), servoZ_angle(0); //伺服機角度
char encoder_dataX(0), encoder_dataY(0), encoder_dataZ(0);//Encoder datas of X and Y axes
char encoder_signX(0), encoder_signY(0), encoder_signZ(0);
float now_laser_distance(1000), locked_laser_distance(3800);
float distance_of_rotation_centers(65);
float now_point_position[4];// now point position
float now_compensating_point_position[4];// now point position
float locked_point_position[4] = { 0 };   //locked point position
float compensating_point_position[4] = { 0 };
char rs232_state_flag_header(255), rs232_state_flag_tailer(250);
char rs232_sent_servo_data_header(254), rs232_sent_servo_data_tariler(249);
char rs232_receive_encoder_data_header(253), rs232_receive_encoder_data_tailer(248);