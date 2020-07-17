import subprocess
import json
import zipfile
import os
import hashlib
import urllib.request
from datetime import datetime, timezone, timedelta

# read compatibility file
compatibility = {}
print('Reading compatibility.txt...')
with open('compatibility.txt', 'r') as file:
    for line in file.readlines():
        tmp = line.split('=')
        compatibility[tmp[0].strip()] = tmp[1].strip()
if 'min_mp_version' not in compatibility:
    print('Error: content of compatibility.txt is not valid. Please create a compatibility file with the following content')
    print()
    print('min_mp_version=<version string e.g. 0.6.0-beta1-40-g249238b4>')
    print()
    exit(1)
print(f"minimum support mp version = {compatibility['min_mp_version']}")

# get versions string from git hash
print('Getting version string from git hash...')
retVal = subprocess.run(['git', 'rev-parse', '--short', 'HEAD'], capture_output=True)
if retVal.returncode == 0:
    version_string = retVal.stdout.decode().strip()
else:
    print('Error: can\'t get verion number from (git rev-parse --short HEAD)')
    exit(1)
print (f'version = {version_string}')

# get current datetime
release_date = datetime.now(timezone(timedelta(hours=7))).isoformat()

current_version = {'version': version_string, 'min_mp_version': compatibility['min_mp_version'], 'release-date': release_date}

# generate library archive (ignore empty subdirectory)
print('Generating library.zip...')
dir_to_zip = ['devices', 'lib', 'lib_ext', 'pin_templates']
with zipfile.ZipFile(version_string + '.zip', 'w', zipfile.ZIP_DEFLATED) as releaseZip:
    releaseZip.writestr(os.path.join('library', 'version.json'), json.dumps(current_version))
    for dir_name in dir_to_zip:
        for root, dirs, files in os.walk(dir_name):
            for filename in files:
                path = os.path.join(root, filename)
                releaseZip.write(path, os.path.join('library', path))

# calculate and append hash
hasher = hashlib.sha256()
with open(version_string + '.zip', 'rb') as file:
    while True:
        chunk = file.read(hasher.block_size)
        if not chunk:
            break
        hasher.update(chunk)
current_version['sha256'] = hasher.hexdigest()

# retrieve previous version information
print('Getting version information from the server...')
with urllib.request.urlopen('https://makerplayground.z23.web.core.windows.net/library/version.json') as response:
    if response.status != 200:
        print('Error: can\'t connect to the version server')
        exit(1)
    versions = json.loads(response.read())
    
# generate version.json
print('Generating version.json...')
with open('version.json', 'w') as file:
    if len(versions) != 0 and versions[0]['min_mp_version'] == current_version['min_mp_version']:
        print('Replacing last entry...')
        versions[0] = current_version
    else:
        print('Insert new entry...')
        versions.insert(0, current_version)
    json.dump(versions, file)
