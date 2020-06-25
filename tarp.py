import csv
import requests
import smtplib
import time
headers={"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:69.0) Gecko/20100101 Firefox/69.0'}

aval=[]
with open('tarp.csv','r') as csv_file:
	reader=csv.reader(csv_file)


	for row in reader:
		val=int(row[2])
		val1=int(row[1])
		if(val>250):
			aval.append(val1)
	csv_file.close()
	print(len(aval))


server = smtplib.SMTP('smtp.gmail.com', 587)
server.ehlo()
server.starttls()
server.ehlo()

server.login('myrules4mylife004@gmail.com', 'anbuobkjosvhueei')

subject= 'Danger'

body=aval 

msg= f"Subject: {subject}\n\n{body}"

server.sendmail(

	'myrules4mylife004',
	'bhanuprakash7668@gmail.com',
	msg
	)
print("Email sent")

server.quit()


