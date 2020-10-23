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
const long initial_valves_setting_default[ARM_COUNT] =
{
  2,
  2,
  2
};

// Parameters
const long valves_element_min = 0;
const long valves_element_max = VALVE_PER_ARM_COUNT - 1;
const long valves_length_min = ARM_COUNT;
const long valves_length_max = ARM_COUNT;

// Functions

// Callbacks

// Errors
}
}

#endif
