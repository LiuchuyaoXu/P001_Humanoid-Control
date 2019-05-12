/* Library for controlling Dynamixel AX-12A motor using DynamixelSDK */
/* Author: Liuchuyao Xu (Raymond) */

#include "debug.h"
#include "motor_control.h"

#define DXL_MINIMUM_POSITION_VALUE      100                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4000                // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     10   				// Dynamixel moving status threshold

int torque_enable()
{
	return 0;
}

int port_initialize()
{
	return 0;
}

int main ()
{
	uint8_t dxl_error = 0;                          // Dynamixel error.
	uint16_t dxl_present_position = 0;              // Dynamixel motor present position.
	int dxl_comm_result = COMM_TX_FAIL;             // Communication result.
	int index = 0;
	int dxl_goal_position[2] = { DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE };  // Goal position

	// Initialize PortHandler Structs.
	// Set the port path.
	// Get methods and members of PortHandlerLinux.
	int port_num = portHandler(DEVICE_NAME);

	// Initialize PacketHandler Structs.
	packetHandler();

	// Open port.
	if (openPort(port_num)) {
		DEBUG_PRINT("%s\n", "Successful, opened the port!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not open the port!");
		return 0;
	}

	// Set port baudrate.
	if (setBaudRate(port_num, BAUDRATE)) {
		DEBUG_PRINT("%s\n", "Successful, changed the baudrate!");
	}
	else {
		DEBUG_PRINT("%s\n", "Failed, did not change the baudrate!");
		return 0;
	}

	// Enable Dymamixel motor torque.
	write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_DXL1, AX_ADDR_TORQUE_ENABLE, TORQUE_ENABLE);
	if ((dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS) {
		DEBUG_PRINT("%s\n", getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
	}
	else if ((dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0) {
		DEBUG_PRINT("%s\n", getRxPacketError(PROTOCOL_VERSION, dxl_error));
	}
	else {
		DEBUG_PRINT("%s\n", "Successful, enabled dynamixel motor torque!");
	}

	// Write goal position
    write2ByteTxRx(port_num, PROTOCOL_VERSION, ID_DXL1, AX_ADDR_GOAL_POSITION, dxl_goal_position[index]);
    if ((dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS) {
      	DEBUG_PRINT("%s\n", getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
    }
    else if ((dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0) {
     	DEBUG_PRINT("%s\n", getRxPacketError(PROTOCOL_VERSION, dxl_error));
    }

    do
    {
		// Read present position
		dxl_present_position = read2ByteTxRx(port_num, PROTOCOL_VERSION, ID_DXL1, AX_ADDR_PRESENT_POSITION);
		if ((dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS) {
			DEBUG_PRINT("%s\n", getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
		}
		else if ((dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0) {
			DEBUG_PRINT("%s\n", getRxPacketError(PROTOCOL_VERSION, dxl_error));
		}

      DEBUG_PRINT("[ID:%03d] GoalPos:%03d  PresPos:%03d\n", ID_DXL1, dxl_goal_position[index], dxl_present_position);

    } while ((abs(dxl_goal_position[index] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD));

	// Disable Dynamixel motor torque.
	write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_DXL1, AX_ADDR_TORQUE_ENABLE, TORQUE_DISABLE);
	if ((dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS) {
		DEBUG_PRINT("%s\n", getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
	}
	else if ((dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0) {
		DEBUG_PRINT("%s\n", getRxPacketError(PROTOCOL_VERSION, dxl_error));
	}

	// Close port
  	closePort(port_num);

	return 0;
}
