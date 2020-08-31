// ----------------------------------------------------------------------------
// YArenaValveController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../YArenaValveController.h"


using namespace y_arena_valve_controller;

YArenaValveController::YArenaValveController()
{
}

void YArenaValveController::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Pins
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    for (size_t valve=0; valve<constants::VALVE_PER_ARM_COUNT; ++valve)
    {
      pinMode(constants::valve_pin_numbers[arm][valve],OUTPUT);
      setValveOff(arm,valve);
    }
  }

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties

  // Parameters
  modular_server::Parameter & valves_parameter = modular_server_.createParameter(constants::valves_parameter_name);
  valves_parameter.setRange(constants::valves_element_min,constants::valves_element_max);
  valves_parameter.setArrayLengthRange(constants::valves_length_min,constants::valves_length_max);

  // Functions
  modular_server::Function & set_valves_function = modular_server_.createFunction(constants::set_valves_function_name);
  set_valves_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaValveController::setValvesHandler));
  set_valves_function.addParameter(valves_parameter);

  // Callbacks
}

void YArenaValveController::setValve(size_t arm,
  size_t valve)
{
  for (size_t v=0; v<constants::VALVE_PER_ARM_COUNT; ++v)
  {
    setValveOff(arm,v);
  }
  setValveOn(arm,valve);
}

void YArenaValveController::setValveOff(size_t arm,
  size_t valve)
{
  digitalWrite(constants::valve_pin_numbers[arm][valve],LOW);
}

void YArenaValveController::setValveOn(size_t arm,
  size_t valve)
{
  digitalWrite(constants::valve_pin_numbers[arm][valve],HIGH);
}

void YArenaValveController::setValves(ArduinoJson::JsonArray & valves)
{
  size_t arm = 0;
  for (ArduinoJson::JsonArray::iterator it=valves.begin();
       it != valves.end();
       ++it)
  {
    size_t valve = *it;
    setValve(arm++,valve);
  }
}

void YArenaValveController::setValvesHandler()
{
  ArduinoJson::JsonArray * valves_ptr;
  modular_server_.parameter(constants::valves_parameter_name).getValue(valves_ptr);
  setValves(*valves_ptr);
}
