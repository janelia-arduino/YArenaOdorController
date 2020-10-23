// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace y_arena_odor_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"y_arena_odor_controller");

CONSTANT_STRING(firmware_name,"YArenaOdorController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=2,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"y_arena_odor_controller");

// Pins

// Units

// Properties
CONSTANT_STRING(initial_odors_setting_property_name,"initialOdorsSetting");

// Parameters
CONSTANT_STRING(odors_parameter_name,"odors");

// Functions
CONSTANT_STRING(get_odors_open_function_name,"getOdorsOpen");
CONSTANT_STRING(set_odors_open_function_name,"setOdorsOpen");

// Callbacks
CONSTANT_STRING(set_all_odors_closed_callback_name,"setAllOdorsClosed");

// Errors
}
}
