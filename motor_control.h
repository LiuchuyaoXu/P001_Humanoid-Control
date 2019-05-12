/* Header file of library for controlling Dynamixel AX-12A motor using DynamixelSDK */
/* Author: Liuchuyao Xu (Raymond) */

#include <stdio.h>

#include "/usr/local/include/dynamixel_sdk/dynamixel_sdk.h"

// Description of the control table can be found at http://emanual.robotis.com/docs/en/dxl/ax/ax-12a/#control-table.
// Control table EEPROM address.
#define ADDR_MODEL_NUMBER         0   // R. Model number.
#define ADDR_FIRMWARE_VERSION     2   // R. Firmware number.
#define ADDR_MOTOR_ID             3   // RW. Motor ID.
#define ADDR_BAUD_RATE            4   // RW. Communication baud rate.
#define ADDR_RETURN_DELAY_TIME    5   // RW. Communication response delay time. 
#define ADDR_CW_ANGLE_LIMIT       6   // RW. Clockwise angle limit.
#define ADDR_CCW_ANGLE_LIMIT      8   // RW. Counter-clockwise angle limit.
#define ADDR_TEMPERATURE_LIMIT    11  // RW. Maximum internal temperate limit.
#define ADDR_MIN_VOLTAGE_LIMIT    12  // RW. Minimum input voltage limit.
#define ADDR_MAX_VOLTAGE_LIMIT    13  // RW. Maximum input voltage limit.
#define ADDR_MAX_TORQUE           14  // RW. Maximum torque.
#define ADDR_STATUS_RETURN_LEVEL  16  // RW. Status return type selection.
#define ADDR_ALARM_LED            17  // RW. Alarm LED error information.
#define ADDR_ALARM_SHUTDOWN       18  // RW. Alarm shutdown error information.

// Control table RAM address.
#define ADDR_TORQUE_ENABLE        24  // RW. Torque on/off.
#define ADDR_STATUS_LED           25  // RW. Status LED on/off.
#define ADDR_CW_MARGIN            26  // RW. Clockwise compliance margin.
#define ADDR_CCW_MARGIN           27  // RW. Counter-clockwise compliance margin.
#define ADDR_CW_SLOPE             28  // RW. Clockwise compliance slope.
#define ADDR_CCW_SLOPE            29  // RW. Counter-clockwise compliance slope.
#define ADDR_GOAL_POSTION         30  // RW. Target position.
#define ADDR_TARGET_SPEED         32  // RW. Target moving speed to target position.
#define ADDR_TORQUE_LIMIT         34  // RW. Torque limit (goal torque).
#define ADDR_PRESENT_POSITION     36  // R. Present position.
#define ADDR_PRESENT_SPEED        38  // R. Present moving speed.
#define ADDR_PRESENT_LOAD         40  // R. Present load.
#define ADDR_PRESENT_VOLTAGE      42  // R. Present input voltage.
#define ADDR_PRESENT_TEMPERATURE  43  // R. Present internal temperature.
#define ADDR_REGISTERED           44  // R. Instruction registered/not registered.
#define ADDR_MOVING               46  // R. Moving/not moving.
#define ADDR_EEPROM_LOCK          47  // RW. EEPROM locked/not locked.
#define ADDR_PUNCH                48  // RW. Minimum current to drive the motor.

// Control table EEPROM data length in bytes.
#define LEN_MODEL_NUMBER         2
#define LEN_FIRMWARE_VERSION     1
#define LEN_MOTOR_ID             1
#define LEN_BAUD_RATE            1 
#define LEN_RETURN_DELAY_TIME    1
#define LEN_CW_ANGLE_LIMIT       2
#define LEN_CCW_ANGLE_LIMIT      2 
#define LEN_TEMPERATURE_LIMIT    1
#define LEN_MIN_VOLTAGE_LIMIT    1 
#define LEN_MAX_VOLTAGE_LIMIT    1 
#define LEN_MAX_TORQUE           2 
#define LEN_STATUS_RETURN_LEVEL  1  
#define LEN_ALARM_LED            1  
#define LEN_ALARM_SHUTDOWN       1 

// Control table RAM data length in bytes.
#define LEN_TORQUE_ENABLE        1  
#define LEN_STATUS_LED           1  
#define LEN_CW_MARGIN            1  
#define LEN_CCW_MARGIN           1 
#define LEN_CW_SLOPE             1  
#define LEN_CCW_SLOPE            1 
#define LEN_GOAL_POSTION         2  
#define LEN_TARGET_SPEED         2 
#define LEN_TORQUE_LIMIT         2 
#define LEN_PRESENT_POSITION     2 
#define LEN_PRESENT_SPEED        2  
#define LEN_PRESENT_LOAD         2 
#define LEN_PRESENT_VOLTAGE      1 
#define LEN_PRESENT_TEMPERATURE  1  
#define LEN_REGISTERED           1  
#define LEN_MOVING               1 
#define LEN_EEPROM_LOCK          1  
#define LEN_PUNCH                2 

/*** ALARM DEFAULT SETTINGS IN MANUAL IS 36 RATHER THAN 0, NOT SURE WHY YET ***/
// Control table EEPROM data user-defined default values.
#define DEFAULT_BAUD_RATE            34     // 57600 bps.
#define DEFAULT_RETURN_DELAY_TIME    250    // 500 microseconds.    
#define DEFAULT_STATUS_RETURN_LEVEL  2      // Status Packet will be returned for all Instructions.  

/*** MACROS SHOULD BE CHANGED TO LEFT_KNEE, LEFT_ANKLE, RIGHT_THIGH, ETC. ***/
// Motor IDs.
#define ID_DXL1                   1
#define ID_DXL2                   2
#define ID_DXL3                   3
#define ID_DXL4                   4
#define ID_DXL5                   5
#define ID_DXL6                   6
#define ID_DXL7                   7
#define ID_DXL8                   8
#define ID_DXL9                   9
#define ID_DXL10                  10

// Other settings.
#define PROTOCOL_VERSION    1.0               // Motor communication protocol version.
#define DEVICE_NAME         "/dev/ttyUSB0"    // Motor port on Linux.

#define ENABLE              1
#define DISABLE             0