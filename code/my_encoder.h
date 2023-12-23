#ifndef _my_encoder_h_
#define _my_encoder_h_
#define PIT_PRIORITY               (PIT_IRQn)   
#define PIT_CH                      (PIT_CH0 )                                 // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���

#define ENCODER_1                   (QTIMER1_ENCODER1)
#define ENCODER_1_A                 (QTIMER1_ENCODER1_CH1_C0)
#define ENCODER_1_B                 (QTIMER1_ENCODER1_CH2_C1)

#define ENCODER_2                   (QTIMER1_ENCODER2)
#define ENCODER_2_A                 (QTIMER1_ENCODER2_CH1_C2)
#define ENCODER_2_B                 (QTIMER1_ENCODER2_CH2_C24)

void my_encoder_init(void);
void pit_handler (void);

extern int16 encoder_data_1;     //��������ٶ�
extern int16 encoder_data_2;     //�ұ������ٶ�

#endif
