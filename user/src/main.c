/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "my_motor.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_adc.h"
// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// �������ǿ�Դ����ֲ�ÿչ���

#define MOTOR1_DIR               (C10)
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)  //��

#define MOTOR2_DIR               (C11 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)   //��

uint16 sum;
uint16 ch1=0,ch2,ch3,ch4;
int16 dif;
int16 adc_err;
int16 adc_err_last;
int16 adc_out;
float servo_kd=1.7 ;
int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
	
    // �˴���д�û����� ���������ʼ�������
	my_motor_init();
	my_servo_init();
	my_servo_duty(30);
	tft180_set_dir(1);
	tft180_init();
	my_encoder_init();
	my_adc_init();
//	wireless_uart_init();
	
	//pit_ms_init(PIT_CH, 100);  
	interrupt_set_priority(PIT_PRIORITY, 0);

	system_delay_ms(1000);
	tft180_set_dir(1);
	tft180_init();
	
	gpio_set_level(MOTOR1_DIR, GPIO_LOW);  
	gpio_set_level(MOTOR2_DIR, GPIO_LOW);
	
	while(1)
	{	
		tft180_show_int(50,5,encoder_data_1,6);
		tft180_show_int(50,50,encoder_data_2,6);
	
//		pwm_set_duty(MOTOR1_PWM,  1500);
//		pwm_set_duty(MOTOR2_PWM,  1500);
//		gpio_set_level(MOTOR1_DIR, GPIO_LOW);  
//		gpio_set_level(MOTOR2_DIR, GPIO_LOW);
//		pwm_set_duty(MOTOR1_PWM,  1500);
//		pwm_set_duty(MOTOR2_PWM,  1500);
		ch1 = adc_mean_filter_convert(ADC_CHANNEL1,8);
		ch2 = adc_mean_filter_convert(ADC_CHANNEL2,8);
		ch3 = adc_mean_filter_convert(ADC_CHANNEL3,8);
		ch4 = adc_mean_filter_convert(ADC_CHANNEL4,8);
		
//		if(ch1<2||ch4<2)
//		{
//			pwm_set_duty(MOTOR1_PWM,  0);
//			pwm_set_duty(MOTOR2_PWM,  0);
//			system_delay_ms(3000);
//		}
	    tft180_show_uint(0,20, ch1,3);
	    tft180_show_uint(0,40, ch2,3);
	    tft180_show_uint(0,60, ch3,3);												
	    tft180_show_uint(0,80, ch4,3);
		
		dif = ch1 - ch4;
		sum = ch1 + ch4;
		adc_err = (dif*20)/sum;
		tft180_show_float(0,100,  adc_err,5,3);
		adc_out = adc_err + servo_kd*(adc_err-adc_err_last);
		adc_err_last = adc_err;
		
		my_servo_duty(45+adc_out);
		my_motor_SetSpeed_L(1,200);
		my_motor_SetSpeed_R(1,200);
//		if(adc_out>10)my_motor_SetSpeed_L(1,200-adc_out);
//		if(adc_out<-10)my_motor_SetSpeed_R(1,200+adc_out);
		//system_delay_ms(100);
		
	}
	
}


