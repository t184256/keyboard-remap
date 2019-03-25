#!/usr/bin/env python3

# Usage: ./map_generator.py file1 file2 fmt

import sys


SHORT = {
    'CAP': 'CAPS_LOCK', 'INS': 'INSERT', 'DEL': 'DELETE',
    'LTA': 'LEFT_ARROW', 'RTA': 'RIGHT_ARROW',
    'UPA': 'UP_ARROW', 'DNA': 'DOWN_ARROW',
    'LSH': 'LEFT_SHIFT', 'RSH': 'RIGHT_SHIFT',
    'LCT': 'LEFT_CTRL', 'RCT': 'RIGHT_CTRL',
    'LAL': 'LEFT_ALT', 'RAL': 'RIGHT_ALT',
    'LWI': 'LEFT_WINDOWS', 'RWI': 'RIGHT_WINDOWS',
    'PUP': 'PAGE_UP', 'PDN': 'PAGE_DOWN',
    'HOM': 'HOME',
    'BCK': 'BACKSPACE',
    'TIL': 'TILDE', 'QUO': 'QUOTE', 'EQU': 'EQUAL',
    'COM': 'COMMA', 'PER': 'PERIOD', 'MIN': 'MINUS',
    'SLA': 'SLASH', 'BSL': 'BACKSLASH', 'SEM': 'SEMICOLON',
    'LBR': 'LEFT_BRACE', 'RBR': 'RIGHT_BRACE',
    'RET': 'RETURN',
    'MUT': 'MUTE', 'VUP': 'VOLUME_UP', 'VDN': 'VOLUME_DOWN',
    'MIC_MUTE': 'F20',  # I have no idea why, but it works in Linux
    'UND': 'UNDO', 'CUT': 'CUT', 'COP': 'COPY', 'PAS': 'PASTE',
}

ULTRASHORT = {
    '`': 'TIL', '\'': 'QUO', '=': 'EQU',
    ',': 'COM', '.': 'PER', '-': 'MIN',
    '/': 'SLA', '\\': 'BSL', ';': 'SEM',
    '[': 'LBR', ']': 'RBR',
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
