
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

# 10 digit phone numbers in India
phone='1234533453'
passwd='passwd'
to_send='4564562342'
import way2sms
q=way2sms.sms(phone, passwd)
q.send(to_send, "testing message")
n=q.msgSentToday()
q.logout()
