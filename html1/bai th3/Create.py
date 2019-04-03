import pymysql

db = pymysql.connect("localhost","root","080396","mydb")

cursor = db.cursor()

cursor.execute("DROP TABLE IF EXISTS sensors")

sql = """CREATE TABLE sensors(
		ID INT(10) PRIMARY KEY AUTO_INCREMENT,
		Temperature INT(10) NOT NULL,
		Humidity INT(10) NOT NULL,
		Date_and_Time CHAR(30) NOT NULL

	)"""

cursor.execute(sql)
db.close();