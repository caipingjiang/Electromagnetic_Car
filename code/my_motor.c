#include "zf_common_headfile.h"
#include "my_encoder.h"
#define MOTOR1_DIR               (C10)
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)  //��

#define MOTOR2_DIR               (C11 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)   //��

//uint8 data_buffer[32];
//uint8 data_len;

float	out1,out2;
int32	last_error1, last_error2; //< �ϴ����


float	kp = 10;       //P
float	ki = 15;       //I
//void pid_handler()
//{
//	kp = wireless_uart_read_buffer(data_buffer,32);
//	if(data_len != 0)                                                       // �յ�����Ϣ ��ȡ�����᷵��ʵ�ʶ�ȡ�������ݸ���
//    {
//       wireless_uart_send_buffer(data_buffer, data_len);
//	}
//	
//}
void my_motor_init(void)
{

    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

}
    

/*************************************************************************
*  �������ƣ�float constrain_float(float amt, float low, float high)
*  ����˵����pid����ʽ���������
*  ����˵����
* @param    pid     pid����
* @param    error   pid�������
*  �������أ�PID������   ע���������Ѿ��������ϴν��
*  �޸�ʱ�䣺2020��4��1��
*  ��    ע��
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

 
 //����
void my_motor_SetSpeed_L(bool dir, const uint32 speed)
{
	uint32 pwml=(uint32)PidIncCtrl_L(kp,ki,(speed-encoder_data_1));
	tft180_show_uint(60,60,pwml,5);
	if (dir == 1)				//��ת
	{
		gpio_set_level(MOTOR1_DIR, GPIO_LOW);  
		 pwm_set_duty(MOTOR1_PWM,  pwml);
	}
	else if(dir == 0)			//��ת
	{
		gpio_set_level(MOTOR1_DIR, GPIO_HIGH);
		pwm_set_duty(MOTOR1_PWM,  pwml);
	}
}
//�ҵ��
void my_motor_SetSpeed_R(bool dir, const uint32 speed)
{
	uint32 pwmr=(uint32)PidIncCtrl_R(kp,ki,(speed-encoder_data_2));
	tft180_show_uint(60,60,pwmr,5);
	if (dir == 1)				//��ת
	{
		gpio_set_level(MOTOR2_DIR, GPIO_LOW); 
		pwm_set_duty(MOTOR2_PWM,  pwmr);
	}
	else if(dir == 0)			//��ת
	{
		gpio_set_level(MOTOR2_DIR, GPIO_HIGH);
		pwm_set_duty (MOTOR2_PWM, pwmr);
	}
}

       
