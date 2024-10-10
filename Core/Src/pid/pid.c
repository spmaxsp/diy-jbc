

#include "pid.h"

void pid_init(struct s_pid_ctl *pid, float K_r, float T_N, float T_v, float T, float min, float max){
    pid->kp = K_r;

    pid->tn = T_N;
    pid->tv = T_v;
    pid->t = T;

    pid->ki = K_r * T / T_N;
    pid->kd = K_r * T_v / T;

    pid->max = max;
    pid->min = min;

    pid->e_1 = 0;
    pid->y_i1 = 0;
}

void pid_update_parameters(struct s_pid_ctl *pid, float K_r, float T_N, float T_v){
    pid->kp = K_r;

    pid->tn = T_N;
    pid->tv = T_v;

    pid->ki = K_r * pid->t / T_N;
    pid->kd = K_r * T_v / pid->t;
}

void pid_update_process_time(struct s_pid_ctl *pid, float T){
    pid->t = T;

    pid->ki = pid->kp * T / pid->tn;
    pid->kd = pid->kp * pid->tv / T;
}


float pid_calc(struct s_pid_ctl *pid, float setpoint, float value){
    const float i_max = 1000;
    const float i_min = -1000;

    // Calculate error
    float e = setpoint - value;

    // Proportional term
    float y_p = pid->kp * e;

    // Integral term
    float y_i = pid->y_i1 + pid->ki * e;

    // Derivative term
    float y_d = pid->kd * (e - pid->e_1);
    // Anti-windup
    if(y_i > i_max){
        y_i = i_max;
    } else if(y_i < i_min){
        y_i = i_min;
    }

    // Calculate output
    float y = y_p + y_i + y_d;

    // Update stored values
    pid->e_1 = e;
    pid->y_i1 = y_i;

    // Limit output
    if(y > pid->max){
        y = pid->max;
    } else if(y < pid->min){
        y = pid->min;
    }

    return y;
}