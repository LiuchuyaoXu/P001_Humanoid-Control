// File name    :   "motor_control.c"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Provide interface functions for controlling Dynamixel AX-12A motors.
//                  Use interface functions provided by DynamixelSDK.
// Abbreviations:   
// Notes        :   Check the header file for descriptions of functions.

#include "debug.h"
#include "motor_control.h"

static int* port_num = NULL;

bool open_port()
{
    *port_num = portHandler(AX_DEVICE_PORT);
    packetHandler();

    if(openPort(*port_num)) {
        DEBUG_PRINT("%s\n", "Successful, opened the port!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not open the port!");
        return false;
	}

	if (setBaudRate(*port_num, AX_DEVICE_BAUDRATE)) {
		DEBUG_PRINT("%s\n", "Successful, set the baudrate!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not set the baudrate!");
		return false;
	}

    return true;
}

void close_port()
{
    closePort(*port_num);
}

bool enable_torque()
{

    return true;
}

void diable_torque()
{

}

void set_goal_position()
{

}

void set_goal_speed()
{

}

void read_current_position()
{

}

void read_current_speed()
{

}

void read_load()
{

}

void read_error()
{

}

void read_temperature()
{

}

void read_supply_voltage()
{

}

int main()
{
    if(!open_port()) {
        DEBUG_PRINT("%s\n", "Program failed!");
        return 0;
    }
    if(!enable_torque()) {
        DEBUG_PRINT("%s\n", "Program failed!");
        return 0;
    }

    set_goal_position();
    read_current_position();
    diable_torque();
    close_port();

    return 0;
}