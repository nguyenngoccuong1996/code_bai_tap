import pymysql
import json

def Sensor(jsonData):
	json_Dict = json.loads(jsonData.decode('utf-8'))
	SensorID = json_Dict['Sensor_ID']
	Data_and_Time = json_Dict['Date']
	Temperature = json_Dict['Temperature']
	Humidity = json_Dict['Humidity']
	db = pymysql.connect("localhost","root","080396","mydb")
	cursor = db.cursor()
	sql = """INSERT INTO sensors(SensorID,Data_and_Time,Temperature,Humidity)
				VALUES (%s,%s,%s,%s)"""
	val = (SensorID,Data_and_Time,Temperature,Humidity)
	cursor.execute(sql,val)
	db.commit()
	print("Insert completed!")
	db.close()

