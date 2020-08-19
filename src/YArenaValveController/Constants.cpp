// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace y_arena_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"y_arena_controller");

CONSTANT_STRING(firmware_name,"YArenaValveController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"y_arena_controller");

// Pins

// Units

// Properties

// Parameters

// Functions
CONSTANT_STRING(set_valves_function_name,"setValves");

// Callbacks

// Errors
}
}
