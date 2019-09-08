from xml.etree import cElementTree as ET

xml = ET.parse('Sample.xml')
root = xml.getroot()

i = 0
while i < len(root[0])-1:
    print(len(root[0]))
    print(root[0][i].tag, root[0][i].attrib)

    if 'mutable' in root[0][i].attrib.keys() and root[0][i].attrib['mutable'].lower() == 'false':
        if 'mutable' in root[0][i+1].attrib.keys() and root[0][i+1].attrib['mutable'].lower() == 'false':
            root[0][i + 1].attrib['value'] = root[0][i].attrib['value'] + root[0][i + 1].attrib['value']
            del root[0][i]
            i = 0
            continue
    i += 1



xml.write('newSample.xml')