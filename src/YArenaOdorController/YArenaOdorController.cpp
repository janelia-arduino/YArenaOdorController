// ----------------------------------------------------------------------------
// YArenaOdorController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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
      setArmOdorOutputClosed(arm,odor);
    }
  }

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & initial_odors_setting_property = modular_server_.createProperty(constants::initial_odors_setting_property_name,constants::initial_odors_setting_default);
  initial_odors_setting_property.setRange(constants::odors_element_min,constants::odors_element_max);

  // Parameters
  modular_server::Parameter & odors_parameter = modular_server_.createParameter(constants::odors_parameter_name);
  odors_parameter.setRange(constants::odors_element_min,constants::odors_element_max);
  odors_parameter.setArrayLengthRange(constants::odors_length_min,constants::odors_length_max);

  // Functions
  modular_server::Function & get_odors_open_function = modular_server_.createFunction(constants::get_odors_open_function_name);
  get_odors_open_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaOdorController::getOdorsOpenHandler));

  modular_server::Function & set_odors_open_function = modular_server_.createFunction(constants::set_odors_open_function_name);
  set_odors_open_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaOdorController::setOdorsOpenHandler));
  set_odors_open_function.addParameter(odors_parameter);

  // Callbacks
  modular_server::Callback & set_all_odors_closed_callback = modular_server_.createCallback(constants::set_all_odors_closed_callback_name);
  set_all_odors_closed_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaOdorController::setAllOdorsClosedHandler));

  initializeOdors();
}

YArenaOdorController::Odors YArenaOdorController::getOdorsOpen()
{
  return odors_open_;
}

void YArenaOdorController::setOdorsOpen(Odors odors)
{
  odors_open_.clear();
  for (size_t arm=0; arm<odors.size(); ++arm)
  {
    size_t odor = odors[arm];
    setArmOdorOpen(arm,odor);
    odors_open_.push_back(odor);
  }
}

void YArenaOdorController::setAllOdorsClosed()
{
  odors_open_.clear();
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    setAllArmOdorOutputsClosed(arm);
  }
}

YArenaOdorController::Odors YArenaOdorController::jsonArrayToOdors(ArduinoJson::JsonArray json_array)
{
  Odors odors;
  for (long odor : json_array)
  {
    odors.push_back(odor);
  }
  return odors;
}

void YArenaOdorController::setArmOdorOpen(size_t arm,
  size_t odor)
{
  setAllArmOdorOutputsClosed(arm);
  setArmOdorOutputOpen(arm,odor);
}

void YArenaOdorController::setArmOdorOutputClosed(size_t arm,
  size_t odor)
{
  if ((arm >= constants::ARM_COUNT) || (odor >= constants::ODOR_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::odor_pin_numbers[arm][odor],LOW);
}

void YArenaOdorController::setArmOdorOutputOpen(size_t arm,
  size_t odor)
{
  if ((arm >= constants::ARM_COUNT) || (odor >= constants::ODOR_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::odor_pin_numbers[arm][odor],HIGH);
}

void YArenaOdorController::setAllArmOdorOutputsClosed(size_t arm)
{
  for (size_t v=0; v<constants::ODOR_PER_ARM_COUNT; ++v)
  {
    setArmOdorOutputClosed(arm,v);
  }
}

void YArenaOdorController::initializeOdors()
{
  modular_server::Property & initial_odors_setting_property = modular_server_.property(constants::initial_odors_setting_property_name);
  long odor;
  Odors odors;
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    initial_odors_setting_property.getElementValue(arm,odor);
    odors.push_back(odor);
  }
  setOdorsOpen(odors);
}

void YArenaOdorController::getOdorsOpenHandler()
{
  Odors odors_open = getOdorsOpen();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();

  for (size_t arm=0; arm<odors_open.size(); ++arm)
  {
    modular_server_.response().write(odors_open[arm]);
  }

  modular_server_.response().endArray();
}

void YArenaOdorController::setOdorsOpenHandler()
{
  ArduinoJson::JsonArray json_array;
  modular_server_.parameter(constants::odors_parameter_name).getValue(json_array);
  Odors odors = jsonArrayToOdors(json_array);
  setOdorsOpen(odors);
}

void YArenaOdorController::setAllOdorsClosedHandler(modular_server::Pin * pin_ptr)
{
  setAllOdorsClosed();
}
