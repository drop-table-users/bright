#ifndef _BRIGHTNESS_CHANGE_H
#define _BRIGHTNESS_CHANGE_H

typedef unsigned long ulong;

ulong read_numeric_file(const char* path);
void write_numeric_file(const char* path, ulong num);

ulong max_bright();
ulong current_bright();
void set_bright(ulong new_bright);
void gradual_set_bright(ulong prev, ulong new_);

#endif
