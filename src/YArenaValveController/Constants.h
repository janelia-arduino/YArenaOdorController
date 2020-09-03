// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef Y_ARENA_VALVE_CONTROLLER_CONSTANTS_H
#define Y_ARENA_VALVE_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularDeviceBase.h>


namespace y_arena_valve_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
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
extern ConstantString initial_valves_setting_property_name;

// Parameters
extern ConstantString valves_parameter_name;
extern const long valves_element_min;
extern const long valves_element_max;
extern const long valves_length_min;
extern const long valves_length_max;

// Functions
extern ConstantString set_valves_function_name;

// Callbacks
extern ConstantString set_all_valves_off_callback_name;

// Errors
}
}
#include "TEENSY40.h"
#endif
