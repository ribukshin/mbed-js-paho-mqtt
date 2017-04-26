#include "MQTT-js.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "easy-connect.h"

#define logMessage printf

DECLARE_CLASS_CONSTRUCTOR(MQTT)
{
  CHECK_ARGUMENT_COUNT(MQTT, __constructor, (args_count == 1));
	CHECK_ARGUMENT_TYPE_ALWAYS(MQTT, __constructor, 0, object);

	// Extract the NetworkInterface pointer from the first argument.
	NetworkInterface* network_interface =
		(NetworkInterface*) jsmbed_wrap_get_native_handle(args[0]);


  MQTTNetwork mqttNetwork(network_interface);
  MQTT::Client<MQTTNetwork, Countdown> client = MQTT::Client<MQTTNetwork, Countdown>(mqttNetwork);

  const char* mqttHost = "0.tcp.ngrok.io";
  int mqttPort = 10068;

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if ((rc = client.connect(data)) != 0) {
        logMessage("rc from MQTT connect is %d\r\n", rc);
    } else {
      logMessage("Connected to MQTT");
    }

	return js_object;
}
