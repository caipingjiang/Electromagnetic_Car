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

#define speed(x)					(x)
uint8 speed=220;
uint16 sum;
uint16 ch1,ch2,ch3,ch4;
int16 dif;
float adc_err;
float adc_err_last;
float adc_out;
float servo_kd = 1.4 ;
float servo_kp = 12;
int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
	
    // �˴���д�û����� ���������ʼ�������
	my_motor_init();
	my_servo_init();
	my_encoder_init();
	my_adc_init();
	tft180_set_dir(1);
	tft180_init();
	interrupt_set_priority(PIT_PRIORITY, 0);

	key_index_enum key_index_array[KEY_NUMBER] = {KEY_1,KEY_2,KEY_3,KEY_4};
	key_init(5);//��ʼ��ɨ�����ڣ�ms��
	
	system_delay_ms(1000);
	
	tft180_show_string(0, 0,"AD:");
	tft180_show_string(30,0, "p:");
	tft180_show_string(30,20,"i:");
	tft180_show_string(30,45,"p:");
	tft180_show_string(30,65,"d:");
	tft180_show_string(88,0,"speed");
	tft180_show_uint(88,20,speed,3);
	tft180_draw_line(25,0,25,100,RGB565_GREEN);
	tft180_draw_line(85,0,85,100,RGB565_GREEN);
	while(1)
	{	
		//��ʾ����
		tft180_show_int(88,45, encoder_data_1,4);
		tft180_show_int(88,65,encoder_data_2,4);
		tft180_show_int(50,0, kp,2);
		tft180_show_int(50,20,ki,2);
		tft180_show_int(50,45,servo_kp,2);
		tft180_show_float(50,65,servo_kd,3,2);
		tft180_show_float(0,100,adc_out,2,1);
		tft180_show_uint(0,20, ch1,3);
	    tft180_show_uint(0,40, ch2,3);
	    tft180_show_uint(0,60, ch3,3);												
	    tft180_show_uint(0,80, ch4,3);
		
		//�ɼ�adc��ѹ
		ch1 = adc_mean_filter_convert(ADC_CHANNEL1,8);
		ch2 = adc_mean_filter_convert(ADC_CHANNEL2,8);
		ch3 = adc_mean_filter_convert(ADC_CHANNEL3,8);
		ch4 = adc_mean_filter_convert(ADC_CHANNEL4,8);
		
		//�����Ⱥ�
		dif = ch1 - ch4;
		sum = ch1 + ch4;
		
		//pd�����������Ǽ����ֲ���
		adc_err = (float)(dif*servo_kp)/sum;
		adc_out = (float)adc_err + (float)(servo_kd*(adc_err-adc_err_last));
		adc_err_last = adc_err;
		
		my_servo_duty(45+adc_out);
		my_motor_SetSpeed_L(1, speed(speed)*(1-0.0135*adc_out));
		my_motor_SetSpeed_R(1, speed(speed)*(1+0.0135*adc_out));
		
		
		//����ɨ��
		key_scanner();
        if( KEY_SHORT_PRESS == key_get_state(KEY_1) )                            // ���ⰴ���̰�
        {
            // �̰��İ������ɿ�ʱ ״̬�Żᱻ key_scanner ��λΪ KEY_SHORT_PRESS
            // ���Ե����������״̬
            key_clear_all_state();
			if(kp-2>=0){kp-=2;}
        }
        if( KEY_SHORT_PRESS == key_get_state(KEY_2) )
        {
             key_clear_all_state();
			if(kp+2<=30){kp+=2; }
        }
		if( KEY_SHORT_PRESS == key_get_state(KEY_3) )
        {
             key_clear_all_state();
			if(ki-0.2>=0){ki-=0.2;}
        }
		if( KEY_SHORT_PRESS == key_get_state(KEY_4) )
        {
             key_clear_all_state();
			if(ki+2<=30){ki+=2;}
        }
		
		if( KEY_LONG_PRESS == key_get_state(KEY_1) )                           
        {
             // һֱ����ʶ��Ϊ����ʱ����һֱ��Ϊ����״̬����ʹ���״̬��־��Ҳû�ã�
			// ���ſ���Ϊ����״̬
            key_clear_all_state();
			if(servo_kp-2>=0){servo_kp-=0.1;}
        }
        if( KEY_LONG_PRESS == key_get_state(KEY_2) )
        {
             key_clear_all_state();
			if(servo_kp+2<=30){servo_kp+=0.1; }
        }
		if( KEY_LONG_PRESS == key_get_state(KEY_3) )
        {
             key_clear_all_state();
			if(servo_kd-0.2>=0){servo_kd-=0.01;}
        }
		if( KEY_LONG_PRESS == key_get_state(KEY_4) )
        {
             key_clear_all_state();
			if(servo_kd<=15){servo_kd+=0.01;}
        }
        
		
	}
	
}


