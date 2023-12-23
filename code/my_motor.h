#include "zf_common_headfile.h"
#ifndef _my_motor_h_
#define _my_motor_h_

void my_motor_init(void);
//void my_speed(const uint32 Target_speed);
void my_motor_SetSpeed_L(bool dir, const uint32 speed);
void my_motor_SetSpeed_R(bool dir, const uint32 speed);

int32 PidIncCtrl_L(float kp,float ki, int32 error);
int32 PidIncCtrl_R(float kp,float ki, int32 error);

#endif
