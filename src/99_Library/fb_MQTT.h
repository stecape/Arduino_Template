#ifndef fb_MQTT_h
#define fb_MQTT_h

#include "..\__Include.h"

byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 2, 100);
IPAddress MQTTserver(192, 168, 2, 231);
EthernetClient ethClient;
PubSubClient MQTTclient(ethClient);

//Callback chiamata quando arriva un pacchetto MQTT
// Il client HMI avrà nel will la messa a zero dei comandi, così da evitare bottoni incastrati
//  Topics:										  Messages:
//- HMI/Logic/Command					- [{id:{cm:#}},{id:{cm:#}},{id:{cm:#}}]
//- PLC/Logic/Status					- [{id:{st:#}},{id:{dy:#}},{id:{st:#,dy:#}}]
//- PLC/Logic/Selection				- [{id:{st:#}},{id:{dy:#}},{id:{st:#,dy:#}}]
//- HMI/Logic/Selection				- [{id:{cm:#}},{id:{cm:#}},{id:{cm:#}}]
//- PLC/Analogic/Set					- [{id:{vl:#}},{id:{mn:#}},{id:{mx:#}},{id:{mn:#,mx:#}},{id:{vl:#,mn:#,mx:#}},{id:{vl:#,mx:#}}]
//- HMI/Analogic/Set					- [{id:{vl:#}},{id:{vl:#}},{id:{vl:#}}]
//- PLC/Analogic/Act					- [{id:{vl:#}},{id:{mn:#}},{id:{mx:#}},{id:{mn:#,mx:#}},{id:{vl:#,mn:#,mx:#}},{id:{vl:#,mx:#}}]
//- PLC/Alarm/Logic						- [{id:{ts:#,st:#}},{id:{ts:#,st:#}}]
//- PLC/Alarm/Analogic				- [tbd]
//- HMI/Alarm/Ack							- [tbd]
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void MQTTreconnect() {
  // Loop until we're reconnected
  while (!MQTTclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (MQTTclient.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement... // MANDA TUTTI I PACCHETTIIIIIIIIIIIIII
      MQTTclient.publish("PLC","Alive");
      // ... and resubscribe
      MQTTclient.subscribe("HMI/PLC/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTsetup()
{

  MQTTclient.setServer(MQTTserver, 1883);
  MQTTclient.setCallback(MQTTcallback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

#endif