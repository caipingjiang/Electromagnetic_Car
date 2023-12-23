#include "zf_common_headfile.h"
#include "my_encoder.h"
#define MOTOR1_DIR               (C10)
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)  //左

#define MOTOR2_DIR               (C11 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)   //右

//uint8 data_buffer[32];
//uint8 data_len;

float	out1,out2;
int32	last_error1, last_error2; //< 上次误差


float	kp = 10;       //P
float	ki = 15;       //I
//void pid_handler()
//{
//	kp = wireless_uart_read_buffer(data_buffer,32);
//	if(data_len != 0)                                                       // 收到了消息 读取函数会返回实际读取到的数据个数
//    {
//       wireless_uart_send_buffer(data_buffer, data_len);
//	}
//	
//}
void my_motor_init(void)
{

    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

}
    

/*************************************************************************
*  函数名称：float constrain_float(float amt, float low, float high)
*  功能说明：pid增量式控制器输出
*  参数说明：
* @param    pid     pid参数
* @param    error   pid输入误差
*  函数返回：PID输出结果   注意输出结果已经包涵了上次结果
*  修改时间：2020年4月1日
*  备    注：
*************************************************************************/
int32 PidIncCtrl_L(float kp,float ki, int32 error)
{
	out1 += (kp * (error - last_error1) + ki * error);
	last_error1 = error;
	if(out1>8000) out1=8000;
	if(out1<0) out1=0;
	return out1;
} 
int32 PidIncCtrl_R(float kp,float ki, int32 error)
{
	
 
  
	out2 += (kp * (error - last_error2) + ki * error);
	last_error2 = error;
	if(out2>8000) out2=8000;
	if(out2<0) out2=0;
	return out2;
}

 
 //左电机
void my_motor_SetSpeed_L(bool dir, const uint32 speed)
{
	uint32 pwml=(uint32)PidIncCtrl_L(kp,ki,(speed-encoder_data_1));
	tft180_show_uint(60,60,pwml,5);
	if (dir == 1)				//正转
	{
		gpio_set_level(MOTOR1_DIR, GPIO_LOW);  
		 pwm_set_duty(MOTOR1_PWM,  pwml);
	}
	else if(dir == 0)			//反转
	{
		gpio_set_level(MOTOR1_DIR, GPIO_HIGH);
		pwm_set_duty(MOTOR1_PWM,  pwml);
	}
}
//右电机
void my_motor_SetSpeed_R(bool dir, const uint32 speed)
{
	uint32 pwmr=(uint32)PidIncCtrl_R(kp,ki,(speed-encoder_data_2));
	tft180_show_uint(60,60,pwmr,5);
	if (dir == 1)				//正转
	{
		gpio_set_level(MOTOR2_DIR, GPIO_LOW); 
		pwm_set_duty(MOTOR2_PWM,  pwmr);
	}
	else if(dir == 0)			//反转
	{
		gpio_set_level(MOTOR2_DIR, GPIO_HIGH);
		pwm_set_duty (MOTOR2_PWM, pwmr);
	}
}

       
