#include "zf_common_headfile.h"

#define MAX_DUTY            (100 )                                               // 最大 MAX_DUTY% 占空比
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
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                   // 调试端口初始化
    
    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR3_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR3_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR4_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR4_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    interrupt_global_enable(0);
    
    while(1)
    {
        if(duty >= 0)                                                           // 正转
        {
            gpio_set_level(MOTOR1_DIR, GPIO_HIGH);                                         // DIR输出高电平
            pwm_set_duty(MOTOR1_PWM, duty * (PWM_DUTY_MAX / 100));                   // 计算占空比

            gpio_set_level(MOTOR2_DIR, GPIO_HIGH);                                         // DIR输出高电平
            pwm_set_duty(MOTOR2_PWM, duty * (PWM_DUTY_MAX / 100));                   // 计算占空比

            gpio_set_level(MOTOR3_DIR, GPIO_HIGH);                                         // DIR输出高电平
            pwm_set_duty(MOTOR3_PWM, duty * (PWM_DUTY_MAX / 100));                   // 计算占空比

            gpio_set_level(MOTOR4_DIR, GPIO_HIGH);                                         // DIR输出高电平
            pwm_set_duty(MOTOR4_PWM, duty * (PWM_DUTY_MAX / 100));                   // 计算占空比
        }
        else                                                                    // 反转
        {
            gpio_set_level(MOTOR1_DIR, GPIO_LOW);                                          // DIR输出低电平
            pwm_set_duty(MOTOR1_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // 计算占空比
            
            gpio_set_level(MOTOR2_DIR, GPIO_LOW);                                          // DIR输出低电平
            pwm_set_duty(MOTOR2_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // 计算占空比
            
            gpio_set_level(MOTOR3_DIR, GPIO_LOW);                                          // DIR输出低电平
            pwm_set_duty(MOTOR3_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // 计算占空比
            
            gpio_set_level(MOTOR4_DIR, GPIO_LOW);                                          // DIR输出低电平
            pwm_set_duty(MOTOR4_PWM, (-duty) * (PWM_DUTY_MAX / 100));                // 计算占空比

        }
        if(dir)                                                                 // 根据方向判断计数方向 本例程仅作参考
        {
            duty ++;                                                            // 正向计数
            if(duty >= MAX_DUTY)                                                // 达到最大值
            dir = false;                                                        // 变更计数方向
        }
        else
        {
            duty --;                                                            // 反向计数
            if(duty <= -MAX_DUTY)                                               // 达到最小值
            dir = true;                                                         // 变更计数方向
        }
        system_delay_ms(50);
    }
}
