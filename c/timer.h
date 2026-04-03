#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 获取当前时间（毫秒为单位）
 * @return 从某个固定起点开始的毫秒数（通常为系统启动后的高精度时间）
 */
double get_current_time(void);

/**
 * 使当前线程睡眠指定的毫秒数
 * @param milliseconds 要睡眠的毫秒数
 */
void timer_sleep(unsigned long long int milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
