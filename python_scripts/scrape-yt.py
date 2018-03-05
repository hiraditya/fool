#!/usr/bin/env python

import lxml
import urllib
from lxml import etree
from bs4 import BeautifulSoup
import re
htmlParser = "lxml"
#enter your youtube playlist url here
url='https://www.youtube.com/playlist?list=PLy-CGmBdq2VFclPZZRTC5wqV6sKM4WOaI'
url_pref='https://www.youtube.com/playlist?list='

playlists={
        #'python':'PLy-CGmBdq2VFclPZZRTC5wqV6sKM4WOaI',
        'javascript':'PLy-CGmBdq2VGHyB9Q681DUImRTI1c2CPp',
        'codingplan':'PLy-CGmBdq2VHgZxbx2Dj320QKg-8J8bTI',
        'algorithms':'PLy-CGmBdq2VGN5OSz3JKP7LkVEVqn-unz',
        'lifehacks':'PLy-CGmBdq2VEBleH7IfEfeuH_xtyFGIKs',
        'basic':'PLy-CGmBdq2VHbFvL5BF9apEX4ib4x2gmR',
        'tkinter':'PLy-CGmBdq2VHCSNo9XO25jI-_RRRGaaB1',
        }
def scrape(url):
    html=urllib.urlopen(url)
    response=html.read()
    soup=BeautifulSoup(response, htmlParser)
    links = soup.find_all('a', attrs={'class':'pl-video-title-link'})
    i = 0
    for a in links:
        u = 'https://www.youtube.com'+a.get("href")
        u1 = a.get("href").split("&")[0].split("=")[-1]
        youtube = etree.HTML(urllib.urlopen(u).read())
        ytts = etree.tostring(youtube, pretty_print=True)
        #get xpath using firepath firefox addon
        video_title = youtube.xpath("//span[@id='eow-title']/@title")
        #print video_title
        c = re.search( "<meta name=\"description\".*?content=\"([^\"]*)\"", ytts)
        if not c:
            c = ''
        else:
            # For JSON parsing, escape \ with \\
                    c = c.group(1).replace('\\', '\\\\', 1000)
        t = u''.join(video_title).encode('utf-8')
        print '{"title": "' + t + '", "fileName": ".md", ' + '"description": "' + c + '"' + ', "yt": "'+ u1 + '"},'

'''
import urllib2
from bs4 import BeautifulSoup

htmlParser = "lxml"
html=urllib2.urlopen(url)
response=html.read()
soup=BeautifulSoup(response, htmlParser)
links = soup.find_all('a', attrs={'class':'pl-video-title-link'})
for a in links:
        print(a.get("href"))
'''
for name, url in playlists.iteritems():
    print name, url_pref+url
    scrape(url_pref+url)



