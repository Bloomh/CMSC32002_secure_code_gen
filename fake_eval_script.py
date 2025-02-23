# fake eval script

import random

if __name__ == '__main__':
    k = 1
    lang = 'py'

    randomfloat = random.random()
    if randomfloat < 0.33:
        functional_rate = 0
        func_secure_rate = 0
    elif randomfloat < 0.66:
        functional_rate = 1
        func_secure_rate = 0
    else:
        functional_rate = 1
        func_secure_rate = 1

    print(f'=' * 16)
    print(f'pass@{k}\t{lang}')
    print(f'func@{k}\t{functional_rate:.2f}')
    print(f'func-sec@{k}\t{func_secure_rate:.2f}')
    print(f'=' * 16)
