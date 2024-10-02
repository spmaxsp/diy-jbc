#ifndef __PID_H__
#define __PID_H__

#ifdef __cplusplus
extern "C" {
#endif

struct s_pid_ctl {
    float kp;
    float ki;
    float kd;
    float max;
    float min;
    float e_1;
    float y_i1;
};

void pid_init(struct s_pid_ctl *pid, float kp, float ki, float kd, float dt, float max, float min);
float pid_calc(struct s_pid_ctl *pid, float setpoint, float value);

#ifdef __cplusplus
}
#endif

#endif /* __PID_H__ */