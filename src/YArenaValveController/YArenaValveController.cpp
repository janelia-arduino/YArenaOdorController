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
      setArmValveOutputOff(arm,valve);
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
  modular_server::Function & get_valves_on_function = modular_server_.createFunction(constants::get_valves_on_function_name);
  get_valves_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaValveController::getValvesOnHandler));

  modular_server::Function & set_valves_on_function = modular_server_.createFunction(constants::set_valves_on_function_name);
  set_valves_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaValveController::setValvesOnHandler));
  set_valves_on_function.addParameter(valves_parameter);

  // Callbacks
  modular_server::Callback & set_all_valves_off_callback = modular_server_.createCallback(constants::set_all_valves_off_callback_name);
  set_all_valves_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaValveController::setAllValvesOffHandler));

  initializeValves();
}

YArenaValveController::Valves YArenaValveController::getValvesOn()
{
  return valves_on_;
}

void YArenaValveController::setValvesOn(Valves valves)
{
  valves_on_.clear();
  for (size_t arm=0; arm<valves.size(); ++arm)
  {
    size_t valve = valves[arm];
    setArmValveOn(arm,valve);
    valves_on_.push_back(valve);
  }
}

void YArenaValveController::setAllValvesOff()
{
  valves_on_.clear();
  for (size_t arm=0; arm<constants::ARM_COUNT; ++arm)
  {
    setAllArmValveOutputsOff(arm);
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

void YArenaValveController::setArmValveOn(size_t arm,
  size_t valve)
{
  setAllArmValveOutputsOff(arm);
  setArmValveOutputOn(arm,valve);
}

void YArenaValveController::setArmValveOutputOff(size_t arm,
  size_t valve)
{
  if ((arm >= constants::ARM_COUNT) || (valve >= constants::VALVE_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::valve_pin_numbers[arm][valve],LOW);
}

void YArenaValveController::setArmValveOutputOn(size_t arm,
  size_t valve)
{
  if ((arm >= constants::ARM_COUNT) || (valve >= constants::VALVE_PER_ARM_COUNT))
  {
    return;
  }
  digitalWrite(constants::valve_pin_numbers[arm][valve],HIGH);
}

void YArenaValveController::setAllArmValveOutputsOff(size_t arm)
{
  for (size_t v=0; v<constants::VALVE_PER_ARM_COUNT; ++v)
  {
    setArmValveOutputOff(arm,v);
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
  setValvesOn(valves);
}

void YArenaValveController::getValvesOnHandler()
{
  Valves valves_on = getValvesOn();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();

  for (size_t arm=0; arm<valves_on.size(); ++arm)
  {
    modular_server_.response().write(valves_on[arm]);
  }

  modular_server_.response().endArray();
}

void YArenaValveController::setValvesOnHandler()
{
  ArduinoJson::JsonArray json_array;
  modular_server_.parameter(constants::valves_parameter_name).getValue(json_array);
  Valves valves = jsonArrayToValves(json_array);
  setValvesOn(valves);
}

void YArenaValveController::setAllValvesOffHandler(modular_server::Pin * pin_ptr)
{
  setAllValvesOff();
}
