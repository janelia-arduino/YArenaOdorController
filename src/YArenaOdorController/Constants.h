// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_ODOR_CONTROLLER_CONSTANTS_H
#define Y_ARENA_ODOR_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularDeviceBase.h>


namespace y_arena_odor_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=2};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString initial_odors_setting_property_name;

// Parameters
extern ConstantString odors_parameter_name;
extern const long odors_element_min;
extern const long odors_element_max;
extern const long odors_length_min;
extern const long odors_length_max;

// Functions
extern ConstantString get_odors_open_function_name;
extern ConstantString set_odors_open_function_name;

// Callbacks
extern ConstantString set_all_odors_closed_callback_name;

// Errors
}
}
#include "TEENSY40.h"
#endif
