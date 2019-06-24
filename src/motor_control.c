// File name    :   "motor_control.c"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Provide interface functions for controlling Dynamixel AX-12A motors.
//                  Use interface functions provided by DynamixelSDK.
// Abbreviations:   comm    communication
//                  ax      AX-12A

#include "motor_control.h"

// Evil global variables.
int port_number = 0;
int joints[12] = {  AX_ID_RIGHT_FOOT_ROLL,
                    AX_ID_RIGHT_FOOT_PITCH,
                    AX_ID_RIGHT_KNEE,
                    AX_ID_RIGHT_THIGH_ROLL,
                    AX_ID_RIGHT_THIGH_PITCH,
                    AX_ID_RIGHT_HIP,
                    AX_ID_LEFT_FOOT_ROLL,
                    AX_ID_LEFT_FOOT_PITCH,
                    AX_ID_LEFT_KNEE,
                    AX_ID_LEFT_THIGH_ROLL,
                    AX_ID_LEFT_THIGH_PITCH,
                    AX_ID_LEFT_HIP};
float joint_degrees[20] = {};

// Arguments:
// Return:      True if successful.
//              False if not successful.
// Description: Initialize the serial port for communication with the motor.
bool open_port()
{
    // Initialize port number.
    port_number = portHandler(AX_DEVICE_PORT);
    packetHandler();

    // Open port.
	if (!openPort(port_number)) {
		printf("Failed, could not open the port!\n");
        return false;
	}

    // Set baud rate.
	if (!setBaudRate(port_number, AX_DEVICE_BAUDRATE)) {
		printf("Failed, could not set the baudrate!\n");
		return false;
	}

    return true;
}

// Arguments:
// Return:
// Description: Close the serial port.
void close_port()
{
    closePort(port_number);
}

// Arguments:
// Return:      True if successful.
//              False if not successful.
// Description: Check the result of the last communication with the motor.
bool check_error()
{
    // Check communication error.
    int dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
        return false;
    }

    // Check motor error.
    int dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_error != 0) {
        printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
        return false;
    }

    return true;
}

// Arguments:   Motor ID.
// Return:      True if successful.
//              False if not successful.
// Description: Enable torque for the motor specifed.
bool enable_torque(int ax_id)
{
    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_ENABLE);

    bool result = check_error();
    return result;
}

// Arguments:   Motor ID.
// Return:
// Description: Disable torque for the motor specifed.
void disable_torque(int ax_id)
{
    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_DISABLE);

    check_error();
}

// Arguments:   Motor ID.
//              Goal position in degrees.
// Return:
// Description: Set the goal position for the motor specifed.
void write_position(int ax_id, float joint_degrees)
{
    float motor_degrees = 150.0 - joint_degrees;
    float position = motor_degrees / 300.0 * 1023.0;
    int position_int = position;
    write2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_GOAL_POSITION, position_int);

    check_error();
}

// Arguments:
// Return:
// Description:
void write_speed()
{

}

// Arguments:   Motor ID.
// Return:      The current position of the motor specified.
// Description: Read the current position of the motor specifed.
int read_position(int ax_id)
{
    int current_position = 0;
    current_position = read2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_PRESENT_POSITION);

    check_error();
    return current_position;
}

// Arguments:
// Return:
// Description:
void read_speed()
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
void read_voltage()
{

}

// Arguments:
// Return:
// Description:
void robot_straight()
{
    joint_degrees[AX_ID_RIGHT_FOOT_ROLL] = 5.0;
    joint_degrees[AX_ID_RIGHT_FOOT_PITCH] = 0;
    joint_degrees[AX_ID_RIGHT_KNEE] = 0;
    joint_degrees[AX_ID_RIGHT_THIGH_ROLL] = 5.0;
    joint_degrees[AX_ID_RIGHT_THIGH_PITCH] = 0;
    joint_degrees[AX_ID_RIGHT_HIP] = -45.0;

    joint_degrees[AX_ID_LEFT_FOOT_ROLL] = -5.0;
    joint_degrees[AX_ID_LEFT_FOOT_PITCH] = 0;
    joint_degrees[AX_ID_LEFT_KNEE] = 0;
    joint_degrees[AX_ID_LEFT_THIGH_ROLL] = -5.0;
    joint_degrees[AX_ID_LEFT_THIGH_PITCH] = 0;
    joint_degrees[AX_ID_LEFT_HIP] = 45.0;
}

// Arguments:
// Return:
// Description:
void robot_stand()
{
    joint_degrees[AX_ID_RIGHT_FOOT_ROLL] = 5.0;
    joint_degrees[AX_ID_RIGHT_FOOT_PITCH] = -50.0;
    joint_degrees[AX_ID_RIGHT_KNEE] = 100.0;
    joint_degrees[AX_ID_RIGHT_THIGH_ROLL] = 5.0;
    joint_degrees[AX_ID_RIGHT_THIGH_PITCH] = 60.0;
    joint_degrees[AX_ID_RIGHT_HIP] = -45.0;

    joint_degrees[AX_ID_LEFT_FOOT_ROLL] = -5.0;
    joint_degrees[AX_ID_LEFT_FOOT_PITCH] = 50.0;
    joint_degrees[AX_ID_LEFT_KNEE] = -100.0;
    joint_degrees[AX_ID_LEFT_THIGH_ROLL] = -5.0;
    joint_degrees[AX_ID_LEFT_THIGH_PITCH] = -60.0;
    joint_degrees[AX_ID_LEFT_HIP] = 45.0;
}

// Arguments:
// Return:
// Description:
void robot_execute()
{
    for(int i = 0; i < 12; i++) {
        write_position(joints[i], joint_degrees[joints[i]]);
    }
}

// Arguments:
// Return:
// Description:
void robot_walk_forward()
{
    // Attempting to walk.
    joint_degrees[AX_ID_RIGHT_THIGH_PITCH] = 45.0;
    joint_degrees[AX_ID_RIGHT_KNEE] = 45.0;
    robot_execute();
}

int main()
{
    // Initialize serial port.
    if(!open_port()) {
        printf("Failed, program terminates!\n");
        return -1;
    }

    // Enable torque for all motors.
    for(int i = 0; i < 12; i++) {
        enable_torque(joints[i]);
    }

    robot_stand();
    robot_execute();

    while (!getchar());

    // Disable torque for all motors.
    for(int i = 0; i < 12; i++) {
        disable_torque(joints[i]);
    }

    close_port();
    return 0;
}
