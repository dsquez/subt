/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef SUBT_IGN_COMMSBROKERPLUGIN_HH_
#define SUBT_IGN_COMMSBROKERPLUGIN_HH_

#include <subt_rf_interface/subt_rf_interface.h>
#include <subt_rf_interface/subt_rf_model.h>
#include <subt_communication_model/subt_communication_model.h>
#include <subt_communication_broker_ign/subt_communication_broker.h>
#include <subt_gazebo_los_model/visibility_rf_model.h>

#include <ignition/plugin/Register.hh>
#include <ignition/launch/Plugin.hh>
#include <ignition/transport/Node.hh>
#include <sdf/Element.hh>

namespace gazebo
{
  /// \brief A plugin that centralizes all SubT robot-to-robot communication.
  ///
  /// The plugin accepts the following parameters in SDF. All parameters have
  /// reasonable defaults.
  ///
  /// <comms_model>         Configuration block for communication system
  ///   <comms_model_type>  Choose the pathloss model
  ///                       (options: log_normal_range, visibility_range)
  ///   <range_config>      Configuration block for range-based models
  ///     <max_range>       Hard limit on maximum range
  ///     <fading_exponent> Fading exponent for pathloss
  ///     <L0>              Pathloss at 1m
  ///     <sigma>           Standard deviation for Normally distributed
  ///                       pathloss
  ///   <visibility_config> Configuration block for visibility-based models
  ///     <visibility_cost_to_fading_exponent> Parameter to convert
  ///                                          visibility cost heuristic to
  ///                                          additional fading exponent
  ///     <comms_cost_max>  Limit visibility cost to this value
  ///   <radio_config>      Configuration block for radio model
  ///     <capacity>        Bitrate limit on the channel
  ///     <tx_power>        Default transmit power (dBm)
  ///     <noise_floor>     Noise floor (dBm)
  ///     <modulation>      Modulation scheme (must by QPSK), used to compute
  ///                       relationship between signal-to-noise ratio (SNR)
  ///                       and bit-error-rate (BER).
  class CommsBrokerPlugin : public ignition::launch::Plugin
  {
    /// \brief Class constructor.
    public: CommsBrokerPlugin() = default;

    // Documentation inherited
    public: virtual void Load(const tinyxml2::XMLElement *_elem);

    /// \brief Callback for World Update events.
    private: void OnClock(const ignition::msgs::Clock &_msg);

    /// \brief Broker instance.
    private: subt::communication_broker::Broker broker;

    /// \brief Last time the plugin checked the ROS parameter server.
    private: double lastROSParameterCheckTime;

    private:
      std::unique_ptr<subt::rf_interface::visibility_model::VisibilityModel>
      visibilityModel;

    /// \brief A transport node.
    private: ignition::transport::Node node;
  };
}
#endif