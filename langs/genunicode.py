#!/usr/bin/env python
"""Generate langs/cz.h / langs/ru.h / ..."""

import sys


def nibbletokey(nibble):
    return nibble.upper()


def genseq(char):
    return [nibbletokey(n) for n in f'{ord(char):04x}']


def genline(name, char):
    return (f'#define emit_unicode_{name}() emit_unicode('
            f'{', '.join(genseq(char))}) // {char}')


if __name__ == '__main__':
    for line in sys.stdin.readlines():
        line = line.split('#', 1)[0].strip()
        if not line:
            continue
        match line.split():
            case [name, char_lower, char_upper]:
                print(genline(f'lower_{name}', char_lower))
                print(genline(f'upper_{name}', char_upper))
            case [name, char_lower]:
                if char_lower.upper() != char_lower:
                    print(genline(f'lower_{name}', char_lower))
                    print(genline(f'upper_{name}', char_lower.upper()))
                else:
                    print(genline(name, char_lower))
            case _:
                raise RuntimeError(f'malformed line `{line}`')
