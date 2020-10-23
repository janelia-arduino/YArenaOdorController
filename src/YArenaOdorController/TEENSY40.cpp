// ----------------------------------------------------------------------------
// TEENSY40.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "TEENSY40.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
namespace y_arena_odor_controller
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

const size_t odor_pin_numbers[ARM_COUNT][ODOR_PER_ARM_COUNT] =
{
  {
    22,
    19,
    16
  },
  {
    21,
    18,
    15
  },
  {
    20,
    17,
    14
  }
};

// Pins

// Units

// Properties
const long initial_arena_odors_default[ARM_COUNT] =
{
  0,
  0,
  0
};

// Parameters
const long arena_odors_element_min = 0;
const long arena_odors_element_max = ODOR_PER_ARM_COUNT - 1;
const long arena_odors_length_min = ARM_COUNT;
const long arena_odors_length_max = ARM_COUNT;

// Functions

// Callbacks

// Errors
}
}

#endif
