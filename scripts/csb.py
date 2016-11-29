import json
from pprint import pprint 
from idautils import *
from idaapi import *


# Code credit to DOD of stackoverflow
def get_bb_id(graph, ea):
    for block in graph:
        if block.startEA <= ea and block.endEA > ea:
            return block.id

def color_block(bb_ea):
    f = get_func(bb_ea)
    print "Function: ", f
    start_ea = f.startEA
    g = FlowChart(f, flags=FC_PREDS)
    bb_id = get_bb_id(g, bb_ea)
    print "bb_id: ", bb_id

    p = idaapi.node_info_t()
    p.bg_color = 0x00ff00 # green

    print (idaapi.set_node_info2(start_ea, bb_id, p, 
                                idaapi.NIF_BG_COLOR | idaapi.NIF_FRAME_COLOR))

def parse_json(filename):
    json_data = open(filename)
    data = json.load(json_data)
    #pprint(data)
    json_data.close()
    return data['branches'] 

filename = AskFile(0,'*.json', "Enter file path to .json file: ")
bdata = parse_json(filename)
for obj in bdata:
    color_block(obj['address'])
    for target in obj['targets']:
        color_block(target)
