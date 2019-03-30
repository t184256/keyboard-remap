#!/usr/bin/env python3

# Usage: ./map_generator.py file1 file2 fmt

import sys


SHORT = {
    'CAP': 'CAPSLOCK', 'INS': 'INSERT', 'DEL': 'DELETE',
    'LTA': 'LEFT', 'RTA': 'RIGHT',
    'UPA': 'UP', 'DNA': 'DOWN',
    'LSH': 'LEFTSHIFT', 'RSH': 'RIGHTSHIFT',
    'LCT': 'LEFTCTRL', 'RCT': 'RIGHTCTRL',
    'LAL': 'LEFTALT', 'RAL': 'RIGHTALT',
    'LWI': 'LEFTMETA', 'RWI': 'RIGHTMETA',
    'PUP': 'PAGEUP', 'PDN': 'PAGEDOWN',
    'HOM': 'HOME',
    'BCK': 'BACKSPACE',
    'GRA': 'GRAVE', 'APO': 'APOSTROPHE', 'EQU': 'EQUAL',
    'COM': 'COMMA', 'MIN': 'MINUS',
    'SLA': 'SLASH', 'BSL': 'BACKSLASH', 'SEM': 'SEMICOLON',
    'LBR': 'LEFTBRACE', 'RBR': 'RIGHTBRACE',
    'RET': 'RETURN',
    'MUT': 'MUTE', 'VUP': 'VOLUMEUP', 'VDN': 'VOLUMEDOWN',
    'MIC_MUTE': 'F20',  # I have no idea why, but it works in Linux
    'UND': 'UNDO', 'CUT': 'CUT', 'COP': 'COPY', 'PAS': 'PASTE',
    'MUH': 'MUHENKAN', 'HEN': 'HENKAN', 'KAT': 'KATAKANAHIRAGANA',
    '102': '102ND',
}

ULTRASHORT = {
    '`': 'GRA', '\'': 'APO', '=': 'EQU',
    ',': 'COM', '.': 'DOT', '-': 'MIN',
    '/': 'SLA', '\\': 'BSL', ';': 'SEM',
    '[': 'LBR', ']': 'RBR', '><': '102',
}


def slightly_expand(n):
    return ULTRASHORT[n] if n in ULTRASHORT else n


def fully_expand(n):
    n = slightly_expand(n)
    return SHORT[n] if n in SHORT else n


for l in sys.stdin.readlines():
    if '///' in l:
        l = l.split('///')[0].rstrip() + '\n'
    if l.startswith('#F'):
        fmt = l[2:]  # example '#define KEY_{<} L_{X>}
    elif l.startswith('#f'):
        fmt += l[2:]
    elif l.startswith('#>'):
        from_vals, to_vals = [p.split() for p in l[2:].split(">>>")]
        assert len(from_vals) == len(to_vals)
        for from_val, to_val in zip(from_vals, to_vals):
            if from_val.count('#') > 1 or to_val.count('#') > 1:
                continue
            out = fmt
            out = out.replace('{<}', slightly_expand(from_val))
            out = out.replace('{>}', slightly_expand(to_val))
            out = out.replace('{X<}', fully_expand(from_val))
            out = out.replace('{X>}', fully_expand(to_val))
            out = out.replace('{N<}', from_val)
            out = out.replace('{N>}', to_val)
            print(out.rstrip())
    else:
        print(l.rstrip())
