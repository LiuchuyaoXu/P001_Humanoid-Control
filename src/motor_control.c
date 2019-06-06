// File name    :   "motor_control.c"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Provide interface functions for controlling Dynamixel AX-12A motors.
//                  Use interface functions provided by DynamixelSDK.
// Abbreviations:   ax      AX-12A
//                  comm    communication
// Notes        :   Check the header file for descriptions of functions.

#include "motor_control.h"

int open_port()
{
    int port_number = portHandler(AX_DEVICE_PORT);
    packetHandler();

	if (!openPort(port_number)) {
		printf("Failed, could not open the port!\n");
        return false;
	}

	if (!setBaudRate(port_number, AX_DEVICE_BAUDRATE)) {
		printf("Failed, could not set the baudrate!\n");
		return false;
	}

    return port_number;
}

void close_port(int port_number)
{
    closePort(port_number);
}

bool enable_torque(int port_number, int ax_id)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;

    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_ENABLE);

    dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
		printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
        return false;
	}
	if (dxl_error != 0) {
		printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
        return false;
	}

    return true;
}

void disable_torque(int port_number, int ax_id)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;

    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_DISABLE);

    dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
		printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
	}
	if (dxl_error != 0) {
		printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
	}
}

void set_goal_position(int port_number, int ax_id, int percentage)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;
    int position = percentage * AX_DEFAULT_CCW_ANGLE_LIMIT / 100;

    write2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_GOAL_POSITION, position);

    dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
      	printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
    }
    if (dxl_error != 0) {
     	printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
    }
}

void set_goal_speed()
{

}

uint16_t read_current_position(int port_number, int ax_id)
{
    uint16_t current_position = 0;
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;

    current_position = read2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_PRESENT_POSITION);

    dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL);
    dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
    }
    if (dxl_error != 0) {
        printf("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
    }

    return current_position;
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
    int port_number = open_port();
    if(!port_number) {
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
        printf("[ID:%03d] GoalPos:%03d  PresPos:%03d\n", AX_ID_DXL3, goal_position, dxl_current_position);
    } while ((abs(goal_position - dxl_current_position) > 10));

    disable_torque(port_number, AX_ID_DXL3);
    close_port(port_number);
    return -1;
}
