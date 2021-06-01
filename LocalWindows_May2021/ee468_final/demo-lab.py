#https://dev.mysql.com/doc/connector-python/en/connector-python-introduction.html

#python -m pip install mysql-connector-python
import mysql.connector

#to connect to mysql db on your own computer, use localhost
#to connect to a remote computer, use its IP address for host:
mydb = mysql.connector.connect(
  host="localhost", 
  user="root",
  passwd='thekey', #"mypassword",
  auth_plugin='mysql_native_password',
  database="university",
)

#print(mydb)

mycursor = mydb.cursor()

name=input('Enter instructor name to search for:')
sql="select * from instructor where name='"+name+"'"
print(sql)

mycursor.execute(sql)
myresult = mycursor.fetchall()

print(mycursor.rowcount," instructors found")

for (r) in myresult:
   print(r)

mycursor.close()
mydb.close()
