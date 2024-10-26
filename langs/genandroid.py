#!/usr/bin/env python
"""Generate Keyboard Mapper combos -> unicode JSON config."""

import json
import sys
import uuid

KEYCODES_NUM = {str(n): n + 7 for n in range(0, 10)}
KEYCODES_LTR = dict(zip('ABCDEF', range(29, 35)))
KEYCODES = {
    **KEYCODES_NUM,
    **KEYCODES_LTR,
    'CTR': 113,
    'ALT': 57,
    'SPC': 62,
    'BCK': 67,
}


def genuuid():
    return str(uuid.uuid4())


def genkeys(*keys):
    return [
        {
          "clickType": 0,
          "deviceId": "io.github.sds100.keymapper.ANY_DEVICE",
          "flags": 1,  # 1 = do not remap
          "keyCode": KEYCODES[key],
          "uid": genuuid()
        }
        for key in keys
    ]


def genblock(i, char):
    seq = ['CTR', 'ALT', *[x for x in f'{ord(char):04x}'.upper()], 'SPC']
    ##seq = [*[x for x in f'{ord(char):04x}'.upper()], 'SPC']
    return {
        "actionList": [
            {
                "data": "consume_key_event",
                "extras": [
                    {
                        "data": "7",
                        "id": "extra_delay_before_next_action"
                    }
                ],
                "flags": 0,
                "type": "SYSTEM_ACTION",
                "uid": genuuid()
            },
        ] + 4 * [
            {
                "data": "67",  # Backspace
                "extras": [],
                "flags": 0,
                "type": "KEY_EVENT",
                "uid": genuuid()
            }
        ] + [
            {
                "data": "67",  # Backspace
                "extras": [
                    {
                        "data": "25",
                        "id": "extra_delay_before_next_action"
                    }
                ],
                "flags": 0,
                "type": "KEY_EVENT",
                "uid": genuuid()
            }
        ] + [
            {
                "data": char,
                "extras": [],
                "flags": 0,
                "type": "TEXT_BLOCK",
                "uid": genuuid()
            },
        ],
        "constraintList": [],
        #"constraintList": [
        #    {
        #        "extras": [
        #            {
        #                "data": "option_lens_back",
        #                "id": "extra_flashlight_camera_lens"
        #            }
        #        ],
        #        "type": "flashlight_on"
        #    }
        #],
        "constraintMode": 1,
        "flags": 0,
        "id": i,
        "isEnabled": True,
        "trigger": {
            "extras": [
                {
                    "data": "32",
                    "id": "extra_sequence_trigger_timeout"
                }
            ],
            "flags": 0,
            "keys": genkeys(*seq),
            "mode": 1
        },
        "uid": genuuid()
      }


#def genmapback(i, char):
#    return {
#        "actionList": [
#            {
#                "data": char,
#                "extras": [
#                    {
#                        "data": "135",
#                        "id": "extra_delay_before_next_action"
#                    }
#                ],
#                "flags": 0,
#                "type": "TEXT_BLOCK",
#                "uid": genuuid()
#            }
#        ],
#        "constraintList": [],
#        #"constraintList": [
#        #    {
#        #        "extras": [
#        #            {
#        #                "data": "option_lens_back",
#        #                "id": "extra_flashlight_camera_lens"
#        #            }
#        #        ],
#        #        "type": "flashlight_off"
#        #    }
#        #],
#        "constraintMode": 1,
#        "flags": 0,
#        "id": i,
#        "isEnabled": True,
#        "trigger": {
#            "extras": [],
#            "flags": 0,
#            "keys": [
#                {
#                    "clickType": 0,
#                    "deviceId": "io.github.sds100.keymapper.ANY_DEVICE",
#                    "flags": 0,
#                    "keyCode": KEYCODES[char],
#                    "uid": genuuid()
#                }
#            ],
#            "mode": 2
#        },
#        "uid": genuuid()
#      }


def main():
    with open('langs/mappings_base.json') as f:
        j = json.load(f)

    i = 4  # first 4 are taken by fingerprint reader
    def append_block(char):
        nonlocal i
        j['keymap_list'].append(genblock(i, char))
        i += 1

    for line in sys.stdin.readlines():
        line = line.split('#', 1)[0].strip()
        if not line:
            continue
        match line.split():
            case [name, char_lower, char_upper]:
                append_block(char_lower)
                append_block(char_upper)
            case [name, char_lower]:
                if char_lower.upper() != char_lower:
                    append_block(char_lower)
                    append_block(char_lower.upper())
                else:
                    append_block(char_lower)
            case _:
                raise RuntimeError(f'malformed line `{line}`')

    #for keycode in KEYCODES.keys():
    #    j['keymap_list'].append(genmapback(i, keycode))
    #    i += 1

    json.dump(j, sys.stdout)


if __name__ == '__main__':
    main()
