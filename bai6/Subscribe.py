import paho.mqtt.client as mqtt
from Get_Data_to_DB import *
#---------------------------------------
#MQTT settings
MQTT_Broker = "localhost"
MQTT_Port = 1883
Keep_Alive_Interval = 45
MQTT_Topic = "home/sensors"

#Gui thong baos khi ket noi thanh cong den server
def on_connect(client, userdata, flags, rc):
	if rc != 0:
		pass
		print("Unable to connect to MQTT Broker...")
	else:
		print ("Connected with MQTT Broker: " + str(MQTT_Broker))
	client.subscribe(MQTT_Topic,0)
#-------------------------------------------------------------
#Gui thong bao khi nah du lieu duwoc publish den topic
def on_message(client, userdata, msg):
	print ("MQTT Data Received...")
	print ("MQTT Topic: " + msg.topic)
	print ("Data: " + str(msg.payload))
	Sensor(msg.payload)
#--------------------------------------------------------------
client = mqtt.Client()
client.username_pw_set(username="cuong",password="080396")
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_Broker,MQTT_Port,Keep_Alive_Interval)
client.loop_forever()