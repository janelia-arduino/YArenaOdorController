// ----------------------------------------------------------------------------
// YArenaController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../YArenaController.h"


using namespace y_arena_controller;

YArenaController::YArenaController()
{
}

void YArenaController::setup()
{
  // Parent Setup
  ServoController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(servo_controller::constants::channel_count_property_name);
  channel_count_property.setDefaultValue(constants::channel_count);
  channel_count_property.setRange(constants::channel_count,constants::channel_count);

  modular_server::Property & travel_per_unit_pulse_duration_property = modular_server_.property(servo_controller::constants::travel_per_unit_pulse_duration_property_name);
  travel_per_unit_pulse_duration_property.setDefaultValue(constants::travel_per_unit_pulse_duration_default);
  travel_per_unit_pulse_duration_property.setRange(constants::travel_per_unit_pulse_duration_element_default,constants::travel_per_unit_pulse_duration_element_default);

  modular_server::Property & velocity_limit_property = modular_server_.property(servo_controller::constants::velocity_limit_property_name);
  velocity_limit_property.setDefaultValue(constants::velocity_limit_default);

  modular_server::Property & expose_angle_property = modular_server_.createProperty(constants::expose_angle_property_name,constants::expose_angle_default);
  expose_angle_property.setUnits(servo_controller::constants::degree_units);
  expose_angle_property.setRange(servo_controller::constants::angle_min,servo_controller::constants::angle_max);
  expose_angle_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&YArenaController::updateExposeOrHideAngleHandler));

  modular_server::Property & hide_angle_property = modular_server_.createProperty(constants::hide_angle_property_name,constants::hide_angle_default);
  hide_angle_property.setUnits(servo_controller::constants::degree_units);
  hide_angle_property.setRange(servo_controller::constants::angle_min,servo_controller::constants::angle_max);

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.parameter(servo_controller::constants::channel_parameter_name);

  modular_server::Parameter & duration_parameter = modular_server_.createParameter(constants::duration_parameter_name);
  duration_parameter.setRange(constants::duration_min,constants::duration_max);
  duration_parameter.setUnits(constants::seconds_units);

  // Functions
  modular_server::Function & expose_function = modular_server_.createFunction(constants::expose_function_name);
  expose_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaController::exposeHandler));
  expose_function.addParameter(channel_parameter);

  modular_server::Function & expose_for_duration_function = modular_server_.createFunction(constants::expose_for_duration_function_name);
  expose_for_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaController::exposeForDurationHandler));
  expose_for_duration_function.addParameter(channel_parameter);
  expose_for_duration_function.addParameter(duration_parameter);

  modular_server::Function & expose_all_for_duration_function = modular_server_.createFunction(constants::expose_all_for_duration_function_name);
  expose_all_for_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaController::exposeAllForDurationHandler));
  expose_all_for_duration_function.addParameter(duration_parameter);

  modular_server::Function & hide_function = modular_server_.createFunction(constants::hide_function_name);
  hide_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&YArenaController::hideHandler));
  hide_function.addParameter(channel_parameter);

  // Callbacks
  modular_server::Callback & expose_all_callback = modular_server_.createCallback(constants::expose_all_callback_name);
  expose_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaController::exposeAllHandler));

  modular_server::Callback & hide_all_callback = modular_server_.createCallback(constants::hide_all_callback_name);
  hide_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaController::hideAllHandler));

  modular_server::Callback & toggle_all_callback = modular_server_.createCallback(constants::toggle_all_callback_name);
  toggle_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&YArenaController::toggleAllHandler));
  toggle_all_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  setChannelCountHandler();
  hideAll();
}

void YArenaController::expose(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  double expose_angle;
  modular_server::Property & expose_angle_property = modular_server_.property(constants::expose_angle_property_name);
  expose_angle_property.getElementValue(channel,expose_angle);

  rotateTo(channel,expose_angle);
  exposed_[channel] = true;
}

void YArenaController::exposeForDuration(size_t channel,
  size_t duration)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  expose_durations_[channel] = duration * servo_controller::constants::milliseconds_per_second;
  if (!exposed_[channel])
  {
    expose(channel);
    setAtTargetPositionFunctor(channel,
      makeFunctor((Functor1<int> *)0,*this,&YArenaController::waitThenHideHandler));
  }
  else
  {
    waitThenHideHandler(channel);
  }
}

void YArenaController::exposeAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    expose(channel);
  }
}

void YArenaController::exposeAllForDuration(size_t duration)
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    exposeForDuration(channel,duration);
  }
}

void YArenaController::hide(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  double hide_angle;
  modular_server::Property & hide_angle_property = modular_server_.property(constants::hide_angle_property_name);
  hide_angle_property.getElementValue(channel,hide_angle);

  rotateTo(channel,hide_angle);
  exposed_[channel] = false;
}

void YArenaController::hideAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    hide(channel);
  }
}

bool YArenaController::exposed(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return false;
  }
  return exposed_[channel];
}

void YArenaController::toggle(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  if (exposed(channel))
  {
    hide(channel);
  }
  else
  {
    expose(channel);
  }
}

void YArenaController::toggleAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    toggle(channel);
  }
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void YArenaController::updateExposeOrHideAngleHandler(size_t channel)
{
  if (exposed(channel))
  {
    expose(channel);
  }
  else
  {
    hide(channel);
  }
}

void YArenaController::exposeHandler()
{
  long channel;
  modular_server_.parameter(servo_controller::constants::channel_parameter_name).getValue(channel);
  expose(channel);
}

void YArenaController::exposeForDurationHandler()
{
  long channel;
  modular_server_.parameter(servo_controller::constants::channel_parameter_name).getValue(channel);
  long duration;
  modular_server_.parameter(y_arena_controller::constants::duration_parameter_name).getValue(duration);
  exposeForDuration(channel,duration);
}

void YArenaController::exposeAllForDurationHandler()
{
  long duration;
  modular_server_.parameter(y_arena_controller::constants::duration_parameter_name).getValue(duration);
  exposeAllForDuration(duration);
}

void YArenaController::hideHandler()
{
  long channel;
  modular_server_.parameter(servo_controller::constants::channel_parameter_name).getValue(channel);
  hide(channel);
}

void YArenaController::hideHandler(int channel)
{
  hide(channel);
}

void YArenaController::waitThenHideHandler(int channel)
{
  addEvent(channel,
    expose_durations_[channel],
    makeFunctor((Functor1<int> *)0,*this,&YArenaController::hideHandler));
}

void YArenaController::exposeAllHandler(modular_server::Pin * pin_ptr)
{
  exposeAll();
}

void YArenaController::hideAllHandler(modular_server::Pin * pin_ptr)
{
  hideAll();
}

void YArenaController::toggleAllHandler(modular_server::Pin * pin_ptr)
{
  toggleAll();
}
