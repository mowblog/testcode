import xml.etree.ElementTree as ET
import re

def handle_version_str(src_str):
    # 获取匹配的自组数据
    m = re.search(r'(.*)(V\d{3}R\d{3}C\d{2})(.*)', src_str)
    if m is not None:
        ver = m.group(2)
        print(ver)
        # 通过获取的匹配内容，将其删除
        dst_str = re.sub(ver, '', src_str)
    else:
        return None
    return dst_str

def create_result_xml():
    model = '''<data><country name="China">test</country></data>'''
    root = ET.fromstring(model)

    # 如何通过ET写入一个xml文件
    tree = ET.ElementTree(root)
    tree.write('result.xml')

if __name__ == "__main__":
    ver_str = "Hello_V001R002C20_Release"

    dst_str = handle_version_str(ver_str)
    print(dst_str)

    create_result_xml()

