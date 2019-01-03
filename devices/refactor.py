import json
import os
import io

for path in os.listdir():
    if not os.path.exists(path + "/device.json"):
        continue
    print(path)
    
    with io.open(path + "/device.json", encoding="utf-8") as fp:
        content = json.load(fp)
        del content["dependency"]
        del content["category"]
    with open(path + '/device.json', 'w') as fp:
        json.dump(content, fp, indent=2)
        