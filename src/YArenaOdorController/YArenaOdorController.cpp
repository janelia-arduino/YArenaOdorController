// ----------------------------------------------------------------------------
// YArenaOdorController.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "../YArenaOdorController.h"


using namespace y_arena_odor_controller;

YArenaOdorController::YArenaOdorController()
{
}

void YArenaOdorController::setup()
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
    for (size_t odor=0; odor<constants::ODOR_PER_ARM_COUNT; ++odor)
    {
      pinMode(constants::odor_pin_numbers[arm][odor],OUTPUT);
      setArmOdorValveClosed(arm,odor);
    }
  }

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & initial_arena_odors_property = modular_server_.createProperty(constants::initial_arena_odors_property_name,constants::initial_arena_odors_default);
  initial_arena_odors_property.setRange(constants::arena_odors_element_min,constants::arena_odors_element_max);

  // Parameters
  modular_server::Parameter & arena_odors_parameter = modular_server_.createParameter(constants::arena_odors_parameter_name);
  arena_odors_parameter.setRange(constants::arena_odors_element_min,constants::arena_odors_element_max);
  arena_odors_parameter.setArrayLengthRange(constants::arena_odors_length_min,constants::arena_odors_length_max);

  // Functions
  modular_server::Function & get_arena_odors_function = modular_server_.createFunction(constants::get_arena_odors_function_name);
  get_arena_odors_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaOdorController::getArenaOdorsHandler));

  modular_server::Function & set_arena_odors_function = modular_server_.createFunction(constants::set_arena_odors_function_name);
  set_arena_odors_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaOdorController::setArenaOdorsHandler));
  set_arena_odors_function.addParameter(arena_odors_parameter);

  // Callbacks

  initializeArenaOdors();
}

YArenaOdorController::ArenaOdors YArenaOdorController::getArenaOdors()
{
  return arena_odors_;
}

void YArenaOdorController::setArenaOdors(ArenaOdors odors)
{
  arena_odors_.clear();
  for (size_t arm=0; arm<odors.size(); ++arm)
  {
    size_t odor = odors[arm];
    setArmOdor(arm,odor);
    arena_odors_.push_back(odor);
  }
}

YArenaOdorController::ArenaOdors YArenaOdorController::jsonArrayToArenaOdors(ArduinoJson::JsonArray json_array)
{
  ArenaOdors arena_odors;
  for (long odor : json_array)
  {
    arena_odors.push_back(odor);
  }
  return arena_odors;
}

void YArenaOdorController::setArmOdor(size_t arm,
  size_t odor)
{
  setAllArmOdorValvesClosed(arm);
  setArmOdorValveOpen(arm,odor);
}

void YArenaOdorController::setArmOdorValveClosed(size_t arm,
  size_t odor)
{
  if ((arm >= constants::ARM_COUNT) || (odor >= constants::ODOR_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::odor_pin_numbers[arm][odor],LOW);
}

void YArenaOdorController::setArmOdorValveOpen(size_t arm,
  size_t odor)
{
  if ((arm >= constants::ARM_COUNT) || (odor >= constants::ODOR_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::odor_pin_numbers[arm][odor],HIGH);
}

void YArenaOdorController::setAllArmOdorValvesClosed(size_t arm)
{
  for (size_t v=0; v<constants::ODOR_PER_ARM_COUNT; ++v)
  {
    setArmOdorValveClosed(arm,v);
  }
}

void YArenaOdorController::initializeArenaOdors()
{
  modular_server::Property & initial_arena_odors_property = modular_server_.property(constants::initial_arena_odors_property_name);
  long odor;
  ArenaOdors odors;
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    initial_arena_odors_property.getElementValue(arm,odor);
    odors.push_back(odor);
  }
  setArenaOdors(odors);
}

void YArenaOdorController::getArenaOdorsHandler()
{
  ArenaOdors arena_odors = getArenaOdors();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();

  for (size_t arm=0; arm<arena_odors.size(); ++arm)
  {
    modular_server_.response().write(arena_odors[arm]);
  }

  modular_server_.response().endArray();
}

void YArenaOdorController::setArenaOdorsHandler()
{
  ArduinoJson::JsonArray json_array;
  modular_server_.parameter(constants::arena_odors_parameter_name).getValue(json_array);
  ArenaOdors arena_odors = jsonArrayToArenaOdors(json_array);
  setArenaOdors(arena_odors);
}
