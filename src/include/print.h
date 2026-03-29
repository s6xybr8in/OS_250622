#ifndef PRINT_H
#define PRINT_H
int is_transmit_empty();
void write_serial(char a);
void print(char *str);
void printf(char *format, ...);
void print_int(int val);
void print_hex(int val);
#endif