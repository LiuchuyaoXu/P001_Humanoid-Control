// File name    :   "motor_control.h"
// Author       :   Liuchuyao Xu (Raymond)     
// Description  :   Macros for controlling Dynamixel AX-12A motors.
// Abbreviations:   R/W     read/write
//                  AX      AX-12A
//                  ADDR    address
//                  LEN     length
//                  CW/CCW  clockwise/counter-clockwise
// Notes        :   Details of the control table can be found at
//                   http://emanual.robotis.com/docs/en/dxl/ax/ax-12a/#control-table.


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "/usr/local/include/dynamixel_sdk/dynamixel_sdk.h"

// Motor EEPROM control table data length in bytes.
#define AX_LEN_MODEL_NUMBER         2
#define AX_LEN_FIRMWARE_VERSION     1
#define AX_LEN_MOTOR_ID             1
#define AX_LEN_BAUD_RATE            1 
#define AX_LEN_RETURN_DELAY_TIME    1
#define AX_LEN_CW_ANGLE_LIMIT       2
#define AX_LEN_CCW_ANGLE_LIMIT      2 
#define AX_LEN_TEMPERATURE_LIMIT    1
#define AX_LEN_MIN_VOLTAGE_LIMIT    1 
#define AX_LEN_MAX_VOLTAGE_LIMIT    1 
#define AX_LEN_MAX_TORQUE           2 
#define AX_LEN_STATUS_RETURN_LEVEL  1  
#define AX_LEN_ALARM_LED            1  
#define AX_LEN_ALARM_SHUTDOWN       1 

// Motor RAM control table data length in bytes.
#define AX_LEN_TORQUE_ENABLE        1  
#define AX_LEN_STATUS_LED           1  
#define AX_LEN_CW_MARGIN            1  
#define AX_LEN_CCW_MARGIN           1 
#define AX_LEN_CW_SLOPE             1  
#define AX_LEN_CCW_SLOPE            1 
#define AX_LEN_GOAL_POSITION        2  
#define AX_LEN_TARGET_SPEED         2 
#define AX_LEN_TORQUE_LIMIT         2 
#define AX_LEN_PRESENT_POSITION     2 
#define AX_LEN_PRESENT_SPEED        2  
#define AX_LEN_PRESENT_LOAD         2 
#define AX_LEN_PRESENT_VOLTAGE      1 
#define AX_LEN_PRESENT_TEMPERATURE  1  
#define AX_LEN_REGISTERED           1  
#define AX_LEN_MOVING               1 
#define AX_LEN_EEPROM_LOCK          1  
#define AX_LEN_PUNCH                2 

// Motor EEPROM control table address.
#define AX_ADDR_MODEL_NUMBER            0   // R.   Model number.
#define AX_ADDR_FIRMWARE_VERSION        2   // R.   Firmware number.
#define AX_ADDR_MOTOR_ID                3   // R/W. Motor ID.
#define AX_ADDR_BAUD_RATE               4   // R/W. Communication baud rate.
#define AX_ADDR_RETURN_DELAY_TIME       5   // R/W. Communication response delay time. 
#define AX_ADDR_CW_ANGLE_LIMIT          6   // R/W. Clockwise angle limit.
#define AX_ADDR_CCW_ANGLE_LIMIT         8   // R/W. Counter-clockwise angle limit.
#define AX_ADDR_TEMPERATURE_LIMIT       11  // R/W. Maximum internal temperate limit.
#define AX_ADDR_MIN_VOLTAGE_LIMIT       12  // R/W. Minimum supply voltage limit.
#define AX_ADDR_MAX_VOLTAGE_LIMIT       13  // R/W. Maximum supply voltage limit.
#define AX_ADDR_MAX_TORQUE              14  // R/W. Maximum torque.
#define AX_ADDR_STATUS_RETURN_LEVEL     16  // R/W. Status return type selection.
#define AX_ADDR_ALARM_LED               17  // R/W. Alarm LED error information.
#define AX_ADDR_ALARM_SHUTDOWN          18  // R/W. Alarm shutdown error information.

// Motor RAM control table address.
#define AX_ADDR_TORQUE_ENABLE           24  // R/W. Torque on/off.
#define AX_ADDR_STATUS_LED              25  // R/W. Status LED on/off.
#define AX_ADDR_CW_MARGIN               26  // R/W. Clockwise compliance margin.
#define AX_ADDR_CCW_MARGIN              27  // R/W. Counter-clockwise compliance margin.
#define AX_ADDR_CW_SLOPE                28  // R/W. Clockwise compliance slope.
#define AX_ADDR_CCW_SLOPE               29  // R/W. Counter-clockwise compliance slope.
#define AX_ADDR_GOAL_POSITION           30  // R/W. Target position.
#define AX_ADDR_TARGET_SPEED            32  // R/W. Target moving speed.
#define AX_ADDR_TORQUE_LIMIT            34  // R/W. Torque limit.
#define AX_ADDR_PRESENT_POSITION        36  // R.   Present position.
#define AX_ADDR_PRESENT_SPEED           38  // R.   Present moving speed.
#define AX_ADDR_PRESENT_LOAD            40  // R.   Present load.
#define AX_ADDR_PRESENT_VOLTAGE         42  // R.   Present input voltage.
#define AX_ADDR_PRESENT_TEMPERATURE     43  // R.   Present internal temperature.
#define AX_ADDR_REGISTERED              44  // R.   Instruction registered/not registered.
#define AX_ADDR_MOVING                  46  // R.   Moving/not moving.
#define AX_ADDR_EEPROM_LOCK             47  // R/W. EEPROM locked/unlocked.
#define AX_ADDR_PUNCH                   48  // R/W. Minimum current to drive the motor.

// Motor EEPROM control table data default values.
#define AX_DEFAULT_MODEL_NUMBER         12
#define AX_DEFAULT_MOTOR_ID             1
#define AX_DEFAULT_BAUD_RATE            1 
#define AX_DEFAULT_RETURN_DELAY_TIME    250
#define AX_DEFAULT_CW_ANGLE_LIMIT       0
#define AX_DEFAULT_CCW_ANGLE_LIMIT      1023 
#define AX_DEFAULT_TEMPERATURE_LIMIT    70
#define AX_DEFAULT_MIN_VOLTAGE_LIMIT    60
#define AX_DEFAULT_MAX_VOLTAGE_LIMIT    140 
#define AX_DEFAULT_MAX_TORQUE           1023
#define AX_DEFAULT_STATUS_RETURN_LEVEL  2
#define AX_DEFAULT_ALARM_LED            36  
#define AX_DEFAULT_ALARM_SHUTDOWN       36

// Motor RAM control table data default values.
#define AX_DEFAULT_TORQUE_ENABLE        0 
#define AX_DEFAULT_STATUS_LED           0  
#define AX_DEFAULT_CW_MARGIN            1  
#define AX_DEFAULT_CCW_MARGIN           1 
#define AX_DEFAULT_CW_SLOPE             32  
#define AX_DEFAULT_CCW_SLOPE            32
#define AX_DEFAULT_REGISTERED           0
#define AX_DEFAULT_MOVING               0 
#define AX_DEFAULT_EEPROM_LOCK          0  
#define AX_DEFAULT_PUNCH                32 

/*** SHOULD BE CHANGED TO LEFT_KNEE, LEFT_ANKLE, RIGHT_THIGH, ETC. ***/
// Motor IDs.
#define AX_ID_DXL1     1
#define AX_ID_DXL2     2
#define AX_ID_DXL3     3
#define AX_ID_DXL4     4
#define AX_ID_DXL5     5
#define AX_ID_DXL6     6
#define AX_ID_DXL7     7
#define AX_ID_DXL8     8
#define AX_ID_DXL9     9
#define AX_ID_DXL10    10

// Other settings.
#define AX_DEVICE_PORT      "/dev/ttyUSB0"  // Motor port on Linux.
#define AX_DEVICE_BAUDRATE  1000000         // Motor communication baudrate.
#define AX_DEVICE_PROTOCOL  1.0             // Motor protocol version.

#define AX_TORQUE_ENABLE    1
#define AX_TORQUE_DISABLE   0

// Function prototypes.

// Arguments    :   void
// Return       :   int port_number
// Description  :   Open the port for communication with the motor.
//                  Set the baudrate of the port.
//                  Return a port number to be used for other functions.
int open_port();

// Arguments    :   int port_number
// Return       :   void
// Description  :   Close the port specified by the port number.
void close_port(int port_number);

// Arguments    :   
// Return       :
// Description  :
bool enable_torque(int port_number, int ax_id);

// Arguments    :   
// Return       :
// Description  :
void diable_torque(int port_number, int ax_id);

// Arguments    :   
// Return       :
// Description  :
void set_goal_position(int port_number, int ax_id, int percentage);

// Arguments    :   
// Return       :
// Description  :
void set_goal_speed();

// Arguments    :   
// Return       :
// Description  :
uint16_t read_current_position(int port_number, int ax_id);

// Arguments    :   
// Return       :
// Description  :
void read_current_speed();

// Arguments    :   
// Return       :
// Description  :
void read_load();

// Arguments    :   
// Return       :
// Description  :
void read_error();

// Arguments    :   
// Return       :
// Description  :
void read_temperature();

// Arguments    :   
// Return       :
// Description  :
void read_supply_voltage();
