// Copyright Takatoshi Kondo 2015
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(MQTT_WILL_HPP)
#define MQTT_WILL_HPP

#include <string>

#include <mqtt/namespace.hpp>
#include <mqtt/subscribe_options.hpp>
#include <mqtt/property_variant.hpp>
#include <mqtt/move.hpp>

namespace MQTT_NS {

class will {
public:
    /**
     * @brief constructor
     * @param topic
     *        A topic name to publish as a will
     * @param message
     *        The contents to publish as a will
     * @param retain
     *        A retain flag. If set it to true, the contents is retained.<BR>
     *        See http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html#_Toc398718038<BR>
     *        3.3.1.3 RETAIN
     * @param qos
     *        qos
     */
    will(buffer topic,
         buffer message,
         bool retain,
         qos qos_value,
         std::vector<v5::property_variant> props = {})
        :topic_(force_move(topic)),
         message_(force_move(message)),
         retain_(retain),
         qos_(qos_value),
         props_(force_move(props))
    {}

    /**
     * @brief constructor (QoS0)
     * @param topic
     *        A topic name to publish as a will
     * @param message
     *        The contents to publish as a will
     * @param retain
     *        A retain flag. If set it to true, the contents is retained.<BR>
     *        See http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html#_Toc398718038<BR>
     *        3.3.1.3 RETAIN
     */
    will(buffer topic,
         buffer message,
         bool retain = false,
         std::vector<v5::property_variant> props = {})
        :will(force_move(topic), force_move(message), retain, qos::at_most_once, force_move(props))
    {}

    /**
     * @brief constructor (retain = false)
     * @param topic
     *        A topic name to publish as a will
     * @param message
     *        The contents to publish as a will
     * @param qos
     *        qos
     */
    will(buffer topic,
         buffer message,
         qos qos_value,
         std::vector<v5::property_variant> props = {})
        :will(force_move(topic), force_move(message), false, qos_value, force_move(props))
    {}

    buffer const& topic() const {
        return topic_;
    }
    buffer& topic() {
        return topic_;
    }
    buffer const& message() const {
        return message_;
    }
    buffer& message() {
        return message_;
    }
    bool retain() const {
        return retain_;
    }
    qos get_qos() const {
        return qos_;
    }
    std::vector<v5::property_variant> const& props() const {
        return props_;
    }
    std::vector<v5::property_variant>& props() {
        return props_;
    }

private:
    buffer topic_;
    buffer message_;
    bool retain_ = false;
    qos qos_ = qos::at_most_once;
    std::vector<v5::property_variant> props_;
};

} // namespace MQTT_NS

#endif // MQTT_WILL_HPP
