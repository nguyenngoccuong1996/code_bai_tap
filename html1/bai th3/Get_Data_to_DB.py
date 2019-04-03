import pymysql
import json
from datetime import datetime

def Sensor(jsonData):
  json_Dict = json.loads(jsonData.decode('utf-8'))
  Temperature = json_Dict['Temp1']
  Humidity = json_Dict['Hum1']
  Date_and_Time = (datetime.today()).strftime("%d-%b-%Y %H:%M:%S")
  # MO ket noi den Database
  db = pymysql.connect("localhost","root","080396","mydb")
  cursor = db.cursor()
  sql = """INSERT INTO sensors(Temperature,Humidity,Date_and_Time) VALUES (%s,%s,%s)"""
  val = (Temperature,Humidity,Date_and_Time)
  cursor.execute(sql,val)
  db.commit()
  print ("Insert complete values topic to db")
  print ("-----------------------------------------")
  db.close()
