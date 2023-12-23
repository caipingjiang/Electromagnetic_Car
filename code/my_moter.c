#include "zf_common_headfile.h"

#define MAX_DUTY            (100 )                                               // ��� MAX_DUTY% ռ�ձ�
#define MOTOR1_DIR               (D0 )
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)

#define MOTOR2_DIR               (D1 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)

#define MOTOR3_DIR               (D15 )
#define MOTOR3_PWM               (PWM1_MODULE0_CHB_D13)

#define MOTOR4_DIR               (D14 )
#define MOTOR4_PWM               (PWM1_MODULE0_CHA_D12)
int8 duty = 0;
bool dir = true;

int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
    
    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    gpio_init(MOTOR3_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR3_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    gpio_init(MOTOR4_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR4_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    interrupt_global_enable(0);
    
    while(1)
    {
        if(duty >= 0)                                                           // ��ת
        {
            gpio_set_level(MOTOR1_DIR, GPIO_HIGH);                                         // DIR����ߵ�ƽ
            pwm_set_duty(MOTOR1_PWM, duty * (PWM_DUTY_MAX / 100));                   // ����ռ�ձ�

            gpio_set_level(MOTOR2_DIR, GPIO_HIGH);                                         // DIR����ߵ�ƽ
            pwm_set_duty(MOTOR2_PWM, duty * (PWM_DUTY_MAX / 100));                   // ����ռ�ձ�

            gpio_set_level(MOTOR3_DIR, GPIO_HIGH);                                         // DIR����ߵ�ƽ
            pwm_set_duty(MOTOR3_PWM, duty * (PWM_DUTY_MAX / 100));                   // ����ռ�ձ�

            gpio_set_level(MOTOR4_DIR, GPIO_HIGH);                                         // DIR����ߵ�ƽ
            pwm_set_duty(MOTOR4_PWM, duty * (PWM_DUTY_MAX / 100));                   // ����ռ�ձ�
        }
        else                                                                    // ��ת
        {
            gpio_set_level(MOTOR1_DIR, GPIO_LOW);                                          // DIR����͵�ƽ
            pwm_set_duty(MOTOR1_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // ����ռ�ձ�
            
            gpio_set_level(MOTOR2_DIR, GPIO_LOW);                                          // DIR����͵�ƽ
            pwm_set_duty(MOTOR2_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // ����ռ�ձ�
            
            gpio_set_level(MOTOR3_DIR, GPIO_LOW);                                          // DIR����͵�ƽ
            pwm_set_duty(MOTOR3_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // ����ռ�ձ�
            
            gpio_set_level(MOTOR4_DIR, GPIO_LOW);                                          // DIR����͵�ƽ
            pwm_set_duty(MOTOR4_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // ����ռ�ձ�

        }
        if(dir)                                                                 // ���ݷ����жϼ������� �����̽����ο�
        {
            duty ++;                                                            // �������
            if(duty >= MAX_DUTY)                                                // �ﵽ���ֵ
            dir = false;                                                        // �����������
        }
        else
        {
            duty --;                                                            // �������
            if(duty <= -MAX_DUTY)                                               // �ﵽ��Сֵ
            dir = true;                                                         // �����������
        }
        system_delay_ms(50);
    }
}
