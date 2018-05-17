import way2sms
import time

'''
160by2

import urllib2
    import json
    phone = raw_input("Enter receiver's number: ")
    msg = raw_input("Enter the message to send: ")
    headers = { "X-Mashape-Authorization": "<Your API key at Mashape>" }
    url = "https://160by2.p.mashape.com/index.php?msg="+msg+"&phone="+phone+"&pwd=your < password>&uid=<your user id>"
    req = urllib2.Request(url, '', headers)
    response = json.loads(urllib2.urlopen(req).read())
    if response['response'] != "done\n":
        print "Error"
    else:
        print "Message sent successfully"
'''

def send_sms(phone, passwd, to_send):
    q.send(to_send, "newsinsearch.com is the site for latest entertainment updates, thanks!")
    n=q.msgSentToday()

# 10 digit phone numbers in India
phone=''
passwd=''
to_send=''

fname='parsed_phone_numbers.txt'

with open(fname) as f:
        content = f.readlines()

# strip whitespace
content = [x.strip() for x in content]
q=way2sms.sms(phone, passwd)

for i in content:
    print (i)
    send_sms(phone,passwd,i)
    time.sleep(5)

q.logout()
