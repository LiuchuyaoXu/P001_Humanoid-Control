// File name    :   "motor_control.c"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Provide interface functions for controlling Dynamixel AX-12A motors.
//                  Use interface functions provided by DynamixelSDK.
// Abbreviations:   ax      AX-12A
//                  comm    communication
// Notes        :   Check the header file for descriptions of functions.

#include "debug.h"
#include "motor_control.h"

int open_port()
{
    int port_number = portHandler(AX_DEVICE_PORT);
    packetHandler();

    if(openPort(port_number)) {
        DEBUG_PRINT("%s\n", "Successful, opened the port!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not open the port!");
        return false;
	}

	if (setBaudRate(port_number, AX_DEVICE_BAUDRATE)) {
		DEBUG_PRINT("%s\n", "Successful, set the baudrate!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not set the baudrate!");
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
    if ((dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL)) != COMM_SUCCESS) {
		DEBUG_PRINT("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
        return false;
	}
	else if ((dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL)) != 0) {
		DEBUG_PRINT("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
        return false;
	}
	else {
		DEBUG_PRINT("%s\n", "Successful, enabled dynamixel motor torque!");
        return true;
	}
}

void diable_torque(int port_number, int ax_id)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;
    write1ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_TORQUE_ENABLE, AX_TORQUE_DISABLE);
    if ((dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL)) != COMM_SUCCESS) {
		DEBUG_PRINT("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
	}
	else if ((dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL)) != 0) {
		DEBUG_PRINT("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
	}
}

void set_goal_position(int port_number, int ax_id, int percentage)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;
    int position = percentage * AX_DEFAULT_CCW_ANGLE_LIMIT / 100;
    write2ByteTxRx(port_number, AX_DEVICE_PROTOCOL, ax_id, AX_ADDR_GOAL_POSITION, position);
    if ((dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL)) != COMM_SUCCESS) {
      	DEBUG_PRINT("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
    }
    else if ((dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL)) != 0) {
     	DEBUG_PRINT("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
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
    if ((dxl_comm_result = getLastTxRxResult(port_number, AX_DEVICE_PROTOCOL)) != COMM_SUCCESS) {
        DEBUG_PRINT("%s\n", getTxRxResult(AX_DEVICE_PROTOCOL, dxl_comm_result));
    }
    else if ((dxl_error = getLastRxPacketError(port_number, AX_DEVICE_PROTOCOL)) != 0) {
        DEBUG_PRINT("%s\n", getRxPacketError(AX_DEVICE_PROTOCOL, dxl_error));
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
        DEBUG_PRINT("%s\n", "Program failed!");
        return 0;
    }
    if(!enable_torque(port_number, AX_ID_DXL3)) {
        DEBUG_PRINT("%s\n", "Program failed!");
        return 0;
    }

    int dxl_current_position = 0;
    int goal_position = 500;
    int goal_position_percentage = goal_position / AX_DEFAULT_CCW_ANGLE_LIMIT;
    set_goal_position(port_number, AX_ID_DXL3, goal_position_percentage);
    do {
        dxl_current_position = read_current_position(port_number, AX_ID_DXL3);
        DEBUG_PRINT("[ID:%03d] GoalPos:%03d  PresPos:%03d\n", AX_ID_DXL3, goal_position, dxl_current_position);
    } while ((abs(goal_position - dxl_current_position) > 10));

    diable_torque(port_number, AX_ID_DXL3);
    close_port(port_number);

    return 0;
}