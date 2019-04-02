import pymysql 
def getConnection():
	connection = pymysql.connect ("localhost","root","080396","mydb")
	return connection