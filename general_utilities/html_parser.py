import os
import re

def is_html(f):
    return f.endswith('html')

def parse1():
    p='/home/hiraditya/work/docs/'
    print('module.exports.recipes = [')
    for dirname, dirnames, filenames in os.walk(p):
        try:
            from BeautifulSoup import BeautifulSoup
        except ImportError:
            from bs4 import BeautifulSoup
            rn = 1
            for f in filenames:
                if (is_html(f)):
                    html = open(os.path.join(dirname, f)) #the HTML code you've written above
                    parsed_html = BeautifulSoup(html, "lxml")
                    t = parsed_html.body.find('div', attrs={'class':'ingredients'})
                    instr = parsed_html.body.find('ul')

                    if t is not None and instr is not None:
                        print('{')
                        print('id:' + str(rn) + ',')
                        rn = rn + 1
                        # remove the .html from file name
                        print("title:'" + f[:-5] + "',")
                        #print(f[:-5])
                        t1 = t.text.strip().split(',')
                        t1strip = [x.strip() for x in t1]
                        t1quoted = ['"'+x+'",' for x in t1strip]
                        #t1strip = map(str.strip, t1)
                        print ('ingredients: [\n\t\t', end="")
                        print('\n\t\t'.join(t1quoted))
                        print('],')
                        print("image:'../images/',")
                        print('steps:[')
                        #if instr is not None:
                        for it in instr.text.split('\n'):
                            if len(it) != 0:
                                s = '"' + it + '",'
                                print(s)
                                print('],')
                                print("active_time:'0.5 hours',")
                                print("total_time: '1 hours',")
                                print("yield: 2")
                                print("},")
                    html.close()

'''
parse basi
'''
def parse_basi():
    p='/home/hiraditya/work/basi/'
    print('module.exports.bollywood_items = [')
    rn = 1
    for dirname, dirnames, filenames in os.walk(p):
        try:
            from BeautifulSoup import BeautifulSoup
        except ImportError:
            from bs4 import BeautifulSoup
            for f in filenames:
                if (is_html(f)):
                    html = open(os.path.join(dirname, f)) #the HTML code you've written above
                    parsed_html = BeautifulSoup(html, "lxml")
                    h2 = parsed_html.body.find('h2')
                    p = parsed_html.body.find_all('p')
                    # get all html links
                    a = parsed_html.body.find('a')
                    if h2 is not None:
                        print('{')
                        print('id:' + str(rn) + ',')
                        rn = rn + 1
                        # remove the .html from file name
                        h2t = h2.text.replace('\n', ' ').replace('\r', ' ')
                        print('title:"' + h2t + '",')
                        ptxt = [x.text for x in p]
                        res1 = ' '.join(ptxt)
                        res = str(res1).replace('\n', ' ').replace('\r', ' ')
                        print('contents:"' + res + '",')
                        if a is not None:
                            print('source:"' + a.get('href') + '",')
                        print("},")

                    html.close()
    print(']')


#parse_basi()

def print_csv(t, delim, title):
    t1 = t.strip().split(delim)
    t1strip = [x.strip() for x in t1]
    t1quoted = ['"'+x+'",' for x in t1strip]
    #t1strip = map(str.strip, t1)
    print (title+':[\n  ', end="")
    print('\n  '.join(t1quoted))
    print('],')


'''
print title from filename by removing .html
'''
def print_title(t):
    # remove the .html from file name
    print("title:'" + t[:-5] + "',")

'''
parse simple html
'''
def parse_simple_html(dirname, filenames):
    rn = 26
    try:
        from BeautifulSoup import BeautifulSoup
    except ImportError:
        from bs4 import BeautifulSoup
        for f in filenames:
            if (is_html(f)):
                html = open(os.path.join(dirname, f)) #the HTML code you've written above
                parsed_html = BeautifulSoup(html, "lxml")
                h2 = parsed_html.body.find('i')
                p = parsed_html.body.find('p')
                if h2 is not None:
                    print('{')
                    print('id:' + str(rn) + ',')
                    rn = rn + 1
                    # remove the .html from file name
                    print_title(f)
                    print('image:"../images/",')
                    print_csv(h2.text, ',', 'ingredients')
                    print_csv(p.text, '\n', 'steps')
                    print('active_time:"half hours",')
                    print('total_time:"half hours",')
                    print('yield: 2')
                    print('},')

                html.close()


def print_json_begin(m):
    print('module.exports.' + m + ' = [')

def print_json_end():
    print(']')

def parse_html_files():
    f = [
    'falafel.html',
    'eggcucumber_salad.html',
    'banana_cake.html',
    'avocado-rice.html',
    'scrambled_egg.html',
    'patisapta.html',
    'parmesanrice.html',
    'khichuri.html'
    ]
    d = '/home/hiraditya/work/basikhobor-docs/recipe/'
    print_json_begin('recipe')
    parse_simple_html(d, f)
    print_json_end()

parse_html_files()
