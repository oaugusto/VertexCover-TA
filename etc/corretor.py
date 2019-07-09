import subprocess
import sys
import difflib
import os

executable_path = sys.argv[1]
dirname = os.path.dirname(os.path.abspath(__file__))

correct = 0
for i in range(1,11):
    try:
        result = subprocess.run(['./' + executable_path, 
                                os.path.join(dirname, 'data/trilha{}.txt'.format(i))],
            stdout=subprocess.PIPE, timeout=60)
    except subprocess.TimeoutExpired:
        print('case {} timeout!'.format(i))
        continue


    if result.returncode != 0:
        print(result)
        print('RETORNOU COM ERRO! return code:', result.returncode)
    
    with open('data/output{}.txt'.format(i), 'r') as fhandle:
        output = fhandle.read()
    
    if result.stdout.decode('utf-8') == output:
        print('Passed case {}'.format(i))
        correct += 1
    else:
        print('Failed case {}'.format(i))

        print('Expected {} got {}'.format(output, result.stdout.decode('utf-8')))

        input('Presse uma tecla pra continuar')
    
print('{} / {} correct'.format(correct, 10))
