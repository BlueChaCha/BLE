
#ifndef BATTERY_H
#define BATTERY_H


void battery_init(void);
void battery_close(void);
void battery_read(void);
void battery_uninit(void);
uint8_t battery_get(void);
#endif
