#!/usr/bin/env python3

import lxml
import urllib
from lxml import etree
import lxml.html
from bs4 import BeautifulSoup
from collections import namedtuple
import requests
from io import StringIO
import re
htmlParser = "lxml"

#enter your youtube playlist url here
url='https://www.youtube.com/playlist?list=PLy-CGmBdq2VFclPZZRTC5wqV6sKM4WOaI'
url_pref='https://www.youtube.com/playlist?list='

playlists={
        'python':'PLy-CGmBdq2VFclPZZRTC5wqV6sKM4WOaI',
        'javascript':'PLy-CGmBdq2VGHyB9Q681DUImRTI1c2CPp',
        'codingplan':'PLy-CGmBdq2VHgZxbx2Dj320QKg-8J8bTI',
        'algorithms':'PLy-CGmBdq2VGN5OSz3JKP7LkVEVqn-unz',
        'lifehacks':'PLy-CGmBdq2VEBleH7IfEfeuH_xtyFGIKs',
        'basic':'PLy-CGmBdq2VHbFvL5BF9apEX4ib4x2gmR',
        'tkinter':'PLy-CGmBdq2VHCSNo9XO25jI-_RRRGaaB1',
        }
def scrape(url):
    html=urllib.request.urlopen(url)
    response=html.read()
    soup=BeautifulSoup(response, htmlParser)
    links = soup.find_all('a', attrs={'class':'pl-video-title-link'})
    i = 0
    for a in links:
        u = 'https://www.youtube.com'+a.get("href")
        u1 = a.get("href").split("&")[0].split("=")[-1]
        u = 'https://www.youtube.com/watch?v='+u1
        #print('getting:', u)
        uread = urllib.request.urlopen(u).read()
        #print('uread', uread)
        youtube = etree.HTML(uread)
        #print('reading:', youtube)
        ytts = etree.tostring(youtube, pretty_print=True).decode('utf-8')
        #print ('ytts', ytts)
        #get xpath using firepath firefox addon
        video_title = youtube.xpath("//span[@id='eow-title']/@title")
        #print video_title
        c = re.search("<meta name=\"description\".*?content=\"([^\"]*)\"", ytts)
        if not c:
            c = '' 
        else:
            # For JSON parsing, escape \ with \\
            c = c.group(1).replace('\\', '\\\\', 1000)
            print ('c:', c)
        t = ''.join(video_title)
        print ('{"title": "' + t + '", "fileName": ".md", ' + '"description": "' + c + '"' + ', "yt": "'+ u1 + '"},')

def use_old():
    for name, url in playlists.items():
        print (name, url_pref+url)
        scrape(url_pref+url)


"""This class extracts the urls and titles of a given youtube playlist"""
 
class PlayList:
	# name tuple to store outputs
    Video = namedtuple('Video', ['url', 'title'])
    
    def __init__(self, listurl):
        # get the html text
        self.__listurl = self.__makeUrl(listurl)
        htmldoc = requests.get(self.__listurl).text
        # parse the html
        soup = BeautifulSoup(htmldoc, 'html.parser')
        # get all the pl(aylist)-video-title-link(s):
        rawList = soup('a', {'class' : 'pl-video-title-link'})
        # there has to be at least 1 item in a playlist
        if len(rawList) < 1:
            raise ValueError('This might be either a private ' \
                              'or an empty playlist.')
        else:
            # list of the raw hrefs and their anchor texts
            self.__rawList = [(x.get('href'), x.contents[0].strip())
                              for x in rawList]
 
 
    @property
    def playlist(self):
        # return the playlist as a list of named tuples
        return [PlayList.Video._make([self.__getVideoURL(x[0])] + [x[1]])
                for x in self.__rawList]
        
    def __getVideoURL(self, text):
        # helper function split extract url and add prefix
        url = text.split('&')[0]   
        url = 'https://www.youtube.com' + url
        return url
    
    def __makeUrl(self, text):
        # url validation and clean up
        if text.find('playlist?list') != -1:
            return text
        elif text.find('watch?v=') * text.find('list=') > 1:
            return self.__getListUrlfromVideoLink(text)
        else:
            raise ValueError('Playlist ID not found in URL.')
 
 
    def __getListUrlfromVideoLink(self, text):
        # helper function as its name implies
        return r'''https://www.youtube.com/playlist?''' + \
               [x for x in text.split('&')
                if x.startswith('list=')][0]

def Main():
    while(True):
        url = input('Enter the Youtube playlist URL: ')
        if len(url) == 0 or url =='quit':
            break
        pl = PlayList(url)
        print('-' * 45)
        for i, x in enumerate(pl.playlist):
            print('URL: %s - %s.%s'%(x.url, i+1, x.title))
        print('-' * 45)


if __name__ == '__main__':
	use_old()

