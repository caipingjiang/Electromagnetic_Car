/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "my_motor.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_adc.h"
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// 本例程是开源库移植用空工程

#define MOTOR1_DIR               (C10)
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)  //左

#define MOTOR2_DIR               (C11 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)   //右

uint16 sum;
uint16 ch1=0,ch2,ch3,ch4;
int16 dif;
int16 adc_err;
int16 adc_err_last;
int16 adc_out;
float servo_kd=1.7 ;
int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                   // 调试端口初始化
	
    // 此处编写用户代码 例如外设初始化代码等
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


