import glob
import pprint
import os
import yaml
from collections import OrderedDict

pprint = pprint.pprint

def load_pin_template_map():
  ret_val = {}
  for file_name in glob.glob('../pin_templates/*.yaml'):
    template_name = os.path.basename(file_name)[:-5]
    with open(file_name, "r", encoding='utf8') as file:
      obj = yaml.load(file)
      ret_val[template_name] = obj['pins']
  return ret_val

pin_template_map = load_pin_template_map()

def read_device_yaml(file_name):
  with open(file_name, "r", encoding='utf8') as file:
    obj = yaml.load(file)
  return obj

def edit_obj(obj):
  pin_template = obj['pin_template']
  device_type = obj['type']
  if 'connection_consume' in obj:
    connection_consume_items = obj['connection_consume']
    if len(set(map(lambda x: x['voltage_level'], pin_template_map[pin_template]))) > 1:
      print("SKIP CONNECTION_CONSUME FOR: " + obj['id'] + " BECAUSE OF MULTI_VOLTAGE_LEVEL")
    if len(set(map(lambda x: x['voltage_level'], pin_template_map[pin_template]))) == 0:
      del obj['connection_consume']
    else:
      voltage_level = pin_template_map[pin_template][0]['voltage_level']
      min_voltage = 9999
      max_voltage = -1
      possible_voltage = [
        ("LEVEL_3v3", 3.3, 3.3),
        ("LEVEL_1", 1, 1),
        ("LEVEL_5", 5, 5),
        ("LEVEL_12", 12, 12),
        ("LEVEL_3v3_5", 3.3, 5)
      ]
      for level, min_v, max_v in possible_voltage:
        if level == voltage_level:
          min_voltage = min_v if min_v < min_voltage else min_voltage
          max_voltage = max_v if max_v > max_voltage else max_voltage
      for item in connection_consume_items:
        for pin_def in item['pins']:
          pin = next(x for x in pin_template_map[pin_template] if x['pin_name'] == pin_def['ref_to'])
          if pin is None:
            print("NO PIN " + obj['ref_to'] + " FOR " + obj['id'])
          pin_def['pin_function'] = pin['pin_function']
          del pin_def['ref_to']
      obj['connection_consume'] = {
        'min_voltage': min_voltage,
        'max_voltage': max_voltage,
        'items': connection_consume_items
      }
  if 'connection_provide' in obj:
    voltages = list(map(lambda x: x['voltage_level'], pin_template_map[pin_template]))
    controller_voltage_level = max(set(voltages), key = voltages.count)
    connection_provide_items = obj['connection_provide']
    for item in connection_provide_items:
      for pin_def in item['pins']:
        pin = next(x for x in pin_template_map[pin_template] if x['pin_name'] == pin_def['ref_to'])
    obj['connection_provide'] = {
      'voltage_level': controller_voltage_level,
      'items': connection_provide_items
    }
  if device_type != 'CONTROLLER':
    del obj['pin_template']
  if 'integrated_devices' in obj:
    for integrate_device in obj['integrated_devices']:
      pin_template = integrate_device['pin_template']
      for pin_def in integrate_device['integrated_connection']:
        pin = next(x for x in pin_template_map[pin_template] if x['pin_name'] == pin_def['ref_to'])
        if pin is None:
          print("NO PIN " + obj['ref_to'] + " FOR " + obj['id'])
        pin_def['pin_function'] = pin['pin_function']
        del pin_def['ref_to']
      del integrate_device['pin_template']
  return obj

def write_device_yaml(file_name, obj):
  with open(file_name, "w") as file:
    file.write(yaml.dump(obj, sort_keys=False))

file_list = glob.glob('*/*.yaml')
for file_name in file_list:
  obj = read_device_yaml(file_name)
  # print(yaml.dump(obj, sort_keys=False))
  obj = edit_obj(obj)
  # print(yaml.dump(obj, sort_keys=False))
  write_device_yaml(file_name, obj)