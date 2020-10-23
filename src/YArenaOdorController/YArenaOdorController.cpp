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
      setArmValveOutputClosed(arm,valve);
    }
  }

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & initial_valves_setting_property = modular_server_.createProperty(constants::initial_valves_setting_property_name,constants::initial_valves_setting_default);
  initial_valves_setting_property.setRange(constants::valves_element_min,constants::valves_element_max);

  // Parameters
  modular_server::Parameter & valves_parameter = modular_server_.createParameter(constants::valves_parameter_name);
  valves_parameter.setRange(constants::valves_element_min,constants::valves_element_max);
  valves_parameter.setArrayLengthRange(constants::valves_length_min,constants::valves_length_max);

  // Functions
  modular_server::Function & get_valves_open_function = modular_server_.createFunction(constants::get_valves_open_function_name);
  get_valves_open_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaValveController::getValvesOpenHandler));

  modular_server::Function & set_valves_open_function = modular_server_.createFunction(constants::set_valves_open_function_name);
  set_valves_open_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaValveController::setValvesOpenHandler));
  set_valves_open_function.addParameter(valves_parameter);

  // Callbacks
  modular_server::Callback & set_all_valves_closed_callback = modular_server_.createCallback(constants::set_all_valves_closed_callback_name);
  set_all_valves_closed_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaValveController::setAllValvesClosedHandler));

  initializeValves();
}

YArenaValveController::Valves YArenaValveController::getValvesOpen()
{
  return valves_open_;
}

void YArenaValveController::setValvesOpen(Valves valves)
{
  valves_open_.clear();
  for (size_t arm=0; arm<valves.size(); ++arm)
  {
    size_t valve = valves[arm];
    setArmValveOpen(arm,valve);
    valves_open_.push_back(valve);
  }
}

void YArenaValveController::setAllValvesClosed()
{
  valves_open_.clear();
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    setAllArmValveOutputsClosed(arm);
  }
}

YArenaValveController::Valves YArenaValveController::jsonArrayToValves(ArduinoJson::JsonArray json_array)
{
  Valves valves;
  for (long valve : json_array)
  {
    valves.push_back(valve);
  }
  return valves;
}

void YArenaValveController::setArmValveOpen(size_t arm,
  size_t valve)
{
  setAllArmValveOutputsClosed(arm);
  setArmValveOutputOpen(arm,valve);
}

void YArenaValveController::setArmValveOutputClosed(size_t arm,
  size_t valve)
{
  if ((arm >= constants::ARM_COUNT) || (valve >= constants::VALVE_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::valve_pin_numbers[arm][valve],LOW);
}

void YArenaValveController::setArmValveOutputOpen(size_t arm,
  size_t valve)
{
  if ((arm >= constants::ARM_COUNT) || (valve >= constants::VALVE_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::valve_pin_numbers[arm][valve],HIGH);
}

void YArenaValveController::setAllArmValveOutputsClosed(size_t arm)
{
  for (size_t v=0; v<constants::VALVE_PER_ARM_COUNT; ++v)
  {
    setArmValveOutputClosed(arm,v);
  }
}

void YArenaValveController::initializeValves()
{
  modular_server::Property & initial_valves_setting_property = modular_server_.property(constants::initial_valves_setting_property_name);
  long valve;
  Valves valves;
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    initial_valves_setting_property.getElementValue(arm,valve);
    valves.push_back(valve);
  }
  setValvesOpen(valves);
}

void YArenaValveController::getValvesOpenHandler()
{
  Valves valves_open = getValvesOpen();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();

  for (size_t arm=0; arm<valves_open.size(); ++arm)
  {
    modular_server_.response().write(valves_open[arm]);
  }

  modular_server_.response().endArray();
}

void YArenaValveController::setValvesOpenHandler()
{
  ArduinoJson::JsonArray json_array;
  modular_server_.parameter(constants::valves_parameter_name).getValue(json_array);
  Valves valves = jsonArrayToValves(json_array);
  setValvesOpen(valves);
}

void YArenaValveController::setAllValvesClosedHandler(modular_server::Pin * pin_ptr)
{
  setAllValvesClosed();
}
