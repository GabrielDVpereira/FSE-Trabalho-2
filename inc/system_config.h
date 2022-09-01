#ifndef SYSTEM
#define SYSTEM



#define SYSTEM_ON 1
#define SYSTEM_OFF 0

#define SYSTEM_RUNING 1
#define SYSTEM_STOPED 0

typedef struct 
{
    int uart_stream;
    unsigned char system_state; 
    unsigned char system_running; 
    int time; 

} SYSTEM_CONFIG;

void init_system_state(int);
SYSTEM_CONFIG get_current_config();
void set_system_state_on();
void set_system_state_off();
void add_system_time();
void decrease_system_time();
int is_system_on();
void set_system_running();
void set_system_stoped();

#endif