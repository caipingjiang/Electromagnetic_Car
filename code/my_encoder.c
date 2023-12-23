#include "zf_common_headfile.h"
#define ENCODER_1                   (QTIMER1_ENCODER1)
#define ENCODER_1_A                 (QTIMER1_ENCODER1_CH1_C0)
#define ENCODER_1_B                 (QTIMER1_ENCODER1_CH2_C1)

#define ENCODER_2                   (QTIMER1_ENCODER2)
#define ENCODER_2_A                 (QTIMER1_ENCODER2_CH1_C2)
#define ENCODER_2_B                 (QTIMER1_ENCODER2_CH2_C24)
#define PIT_CH                      (PIT_CH0 )                                 // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用

int16 encoder_data_1 = 0;
int16 encoder_data_2 = 0;

//extern int32 PidIncCtrl_L(float kp,float ki, int32 error);
//extern int32 PidIncCtrl_R(float kp,float ki, int32 error);
//extern void my_motor_SetSpeed(bool dir, const uint32 speed);
#include "my_motor.h"
void my_encoder_init(void)
{ 
	encoder_quad_init(ENCODER_1, ENCODER_1_A, ENCODER_1_B);                     // 初始化编码器模块与引脚 正交解码编码器模式
    encoder_quad_init(ENCODER_2, ENCODER_2_A, ENCODER_2_B);                     // 初始化编码器模块与引脚 正交解码编码器模式
    pit_ms_init(PIT_CH, 10);
}



void pit_handler (void)
{
	encoder_data_1 = -encoder_get_count(ENCODER_1);                              // 获取编码器计数
    encoder_clear_count(ENCODER_1);                                             // 清空编码器计数
	
    encoder_data_2 = encoder_get_count(ENCODER_2);                              // 获取编码器计数
    encoder_clear_count(ENCODER_2);                                             // 清空编码器计数                           // 清空编码器计数

	my_motor_SetSpeed_L(1,200);
	my_motor_SetSpeed_R(1,200);
}

