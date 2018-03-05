import sys
import time
from termcolor import colored, cprint
 
text = colored('Hello, World!', 'red', attrs=['reverse', 'underline', 'blink'])
print(text)
cprint('Hello, World!', 'green', 'on_red')
 
print_red_on_cyan = lambda x: cprint(x, 'red', 'on_cyan')
print_red_on_cyan('Hello, World!')
print_red_on_cyan('Hello, Universe!')
 
for i in range(10):
    cprint(i, 'magenta', end=' ')
 
cprint("Attention!", 'red', attrs=['bold'], file=sys.stderr)

def blink(char):                       
    print(char, end = '\r')           
    time.sleep(0.5)                       
    print(' ' * 50, end = '\r')       
    time.sleep(0.5)


blink('a')
blink('b')
