import conn
import pymysql
connection = conn.getConnection ()
cursor = connection.cursor()
print ("ket noi thanh cong")
def tables():
 cursor.execute("drop table if exists sensors")
sql = """ create table sensors(
			ten int(10) primary key auto_increment,
			toan int(3) not null,
			hoa int(3) not null
			time datetime not null
			)
		"""
cursor.execute(sql)
connection.close()
#ham insert
def insert():
	try:
	 sql = "insert into sensor(temperature,humidity,time) values(12,05,'1996-12-05 12:05:30')"
	 cursor.execute(sql)
	 connection.commit()
	except:
	 connection.rollback()
#ham select
def select():
	try:
	 sql = "select * from sensors"
	 cursor.execute()
	 results = cursor.fetchall()
	 print (results)
	except:
	 print("khong co du lieu")
connection.close()
#ham update
def update():
	try:
	 sql = "update sensors set temperature=40, humidity=50 where id =1"
	 cursor.execute(sql)
	 connection.commit()
	except:
	 connection.rollback()
	 connection.close()
#ham delete
def delete():
	try:
	 sql = "delete from sensors where id<2"
	 cursor.execute(sql)
	 connection.commit()
	except:
	 connection.rollback()
	 connection.close() 	   

