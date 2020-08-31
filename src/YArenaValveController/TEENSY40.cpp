// ----------------------------------------------------------------------------
// TEENSY40.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "TEENSY40.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
namespace y_arena_valve_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=2015,
  .version_major=1,
  .version_minor=2,
};

const size_t valve_pin_numbers[ARM_COUNT][VALVE_PER_ARM_COUNT] =
{
  {
    22,
    21,
    20
  },
  {
    19,
    18,
    17
  },
  {
    16,
    15,
    14
  }
};

// Pins

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
