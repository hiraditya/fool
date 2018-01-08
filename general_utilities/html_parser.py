import os

def is_html(f):
    return f.endswith('html')

p='/home/hiraditya/work/basikhobor-docs/'
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

