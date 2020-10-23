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
CONSTANT_STRING(initial_arena_odors_property_name,"initialArenaOdors");

// Parameters
CONSTANT_STRING(arena_odors_parameter_name,"arena_odors");

// Functions
CONSTANT_STRING(get_arena_odors_function_name,"getArenaOdors");
CONSTANT_STRING(set_arena_odors_function_name,"setArenaOdors");

// Callbacks

// Errors
}
}
