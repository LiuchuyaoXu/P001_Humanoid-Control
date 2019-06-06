// File name    :   "motor_control.c"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Provide interface functions for controlling Dynamixel AX-12A motors.
//                  Use interface functions provided by DynamixelSDK.
// Abbreviations:   ax      AX-12A
//                  comm    communication

#include "motor_control.h"

// Arguments:
// Return:      Port number if successful.
//              -1 if non-successful.
// Description: Initialise the serial port for communication with the motor.
int open_port()
{
    // Get port number.
    int port_number = portHandler(AX_DEVICE_PORT);
    packetHandler();

    // Open port.
	if (!openPort(port_number)) {
		printf("Failed, could not open the port!\n");
        return -1;
	}

    // Set baud rate.
	if (!setBaudRate(port_number, AX_DEVICE_BAUDRATE)) {
		printf("Failed, could not set the baudrate!\n");
		return -1;
	}

    return port_number;
}

// Arguments:   Port number.
// Return:
// Description: Close the serial port.
void close_port(int port_number)
{
    closePort(port_number);
}

// Arguments:   Port number.
// Return:      True if successful.
//              False if non-successful.
// Description: Check the result of the last communication with the motor.
bool check_error(int port_number)
{
    // Check communication error.
    int dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
        return false;
    }

    // Check motor error.
    uint8_t dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_error != 0) {
        printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
        return false;
    }

    return true;
}

// Arguments:   Port number.
//              Motor ID.
// Return:      True if successful.
//              False if non-successful.
// Description: Enable torque for the motor specifed.
bool enable_torque(int port_number, int ax_id)
{
    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_ENABLE);

    return check_error(port_number);
}

// Arguments:   Port number.
//              Motor ID.
// Return:
// Description: Disable torque for the motor specifed.
void disable_torque(int port_number, int ax_id)
{
    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_DISABLE);

    check_error(port_number);
}

// Arguments:   Port number.
//              Motor ID.
//              Percent of maximum allowed position.
// Return:
// Description: Set the goal position for the motor specifed.
void set_goal_position(int port_number, int ax_id, int percent)
{
    int position = percent * AX_DEFAULT_CCW_ANGLE_LIMIT / 100;
    write2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_GOAL_POSITION, position);

    check_error(port_number);
}

// Arguments:
// Return:
// Description:
void set_goal_speed()
{

}

// Arguments:   Port number.
//              Motor ID.
// Return:      The current position of the motor specified.
// Description: Read the current position of the motor specifed.
uint16_t read_current_position(int port_number, int ax_id)
{
    uint16_t current_position = 0;
    current_position = read2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_PRESENT_POSITION);

    check_error(port_number);
    return current_position;
}

// Arguments:
// Return:
// Description:
void read_current_speed()
{

}

// Arguments:
// Return:
// Description:
void read_load()
{

}

// Arguments:
// Return:
// Description:
void read_error()
{

}

// Arguments:
// Return:
// Description:
void read_temperature()
{

}

// Arguments:
// Return:
// Description:
void read_supply_voltage()
{

}

int main()
{
    int port_number = open_port();
    if(port_number == -1) {
        printf("Failed, program terminates!\n");
        return -1;
    }
    if(!enable_torque(port_number, AX_ID_DXL3)) {
        printf("Failed, program terminates!\n");
        return -1;
    }

    int dxl_current_position = 0;
    int goal_position = 500;
    int goal_position_percentage = goal_position / AX_DEFAULT_CCW_ANGLE_LIMIT;
    set_goal_position(port_number, AX_ID_DXL3, goal_position_percentage);
    do {
        dxl_current_position = read_current_position(port_number, AX_ID_DXL3);
        printf("[Motor ID:%03d] Goal Position:%03d  Current Position:%03d\n", AX_ID_DXL3, goal_position, dxl_current_position);
    } while ((abs(goal_position - dxl_current_position) > 10));

    disable_torque(port_number, AX_ID_DXL3);
    close_port(port_number);
    return 0;
}
