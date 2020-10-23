# -*- coding:utf-8 -*-
import glob
import os
import cv2 as cv
import xml.dom
import xml.dom.minidom
import xml.etree.ElementTree as ET
from random import randint
import random

WSI_MASK_PATH = './'
IMAGE_PATH = 'JPEGImages'
human_img = 'image'
XML_PATH = 'Annotations'
BACKGROUND_IMAGE_PATH = './bg'


_FOLDER_NODE= 'VOC2007'
_ROOT_NODE= 'annotation'
_DATABASE_NAME= 'LOGODection'
_ANNOTATION= 'PASCAL VOC2007'
_AUTHOR= 'Scheaven'
_SEGMENTED= '0'
_DIFFICULT= '0'
_TRUNCATED= '0'
_POSE= 'Unspecified'



# 封装创建节点的过�?
def createElementNode(doc,tag, attr):  # 创建一个元素节�?
    element_node = doc.createElement(tag)

    # 创建一个文本节�?
    text_node = doc.createTextNode(attr)

    # 将文本节点作为元素节点的子节�?
    element_node.appendChild(text_node)

    return element_node

    # 封装添加一个子节点的过�?
def createChildNode(doc,tag, attr,parent_node):

    child_node = createElementNode(doc, tag, attr)

    parent_node.appendChild(child_node)

# object节点比较特殊

def createObjectNode(doc,attrs):

    object_node = doc.createElement('object')

    createChildNode(doc, 'name', attrs['classification'],
                    object_node)

    createChildNode(doc, 'pose',
                    _POSE, object_node)

    createChildNode(doc, 'truncated',
                    _TRUNCATED, object_node)

    createChildNode(doc, 'difficult',
                    _DIFFICULT, object_node)

    bndbox_node = doc.createElement('bndbox')

    createChildNode(doc, 'xmin', attrs['xmin'],
                    bndbox_node)

    createChildNode(doc, 'ymin', attrs['ymin'],
                    bndbox_node)

    createChildNode(doc, 'xmax', attrs['xmax'],
                    bndbox_node)

    createChildNode(doc, 'ymax', attrs['ymax'],
                    bndbox_node)

    object_node.appendChild(bndbox_node)

    return object_node

# 将documentElement写入XML文件�?
def writeXMLFile(doc, filename):

    tmpfile =open('tmp.xml','w')

    doc.writexml(tmpfile, addindent=''*4,newl = '\n',encoding = 'utf-8')

    tmpfile.close()

    # 删除第一行默认添加的标记

    fin =open('tmp.xml')

    fout =open(filename, 'w')

    lines = fin.readlines()

    for line in lines[1:]:

        if line.split():

         fout.writelines(line)

        # new_lines = ''.join(lines[1:])

        # fout.write(new_lines)

    fin.close()

    fout.close()

# width,height为最终图片参数
def create_xml(xml_save_path, jpg_save_name, width, height, left_dist, top_dist, res):
        my_dom = xml.dom.getDOMImplementation()

        doc = my_dom.createDocument(None,_ROOT_NODE,None)

        # 获得根节�?
        root_node = doc.documentElement

        # folder节点

        createChildNode(doc, 'folder',_FOLDER_NODE, root_node)

        # filename节点

        createChildNode(doc, 'filename', jpg_save_name, root_node)

        # source节点

        source_node = doc.createElement('source')

        # source的子节点

        createChildNode(doc, 'database',_DATABASE_NAME, source_node)

        createChildNode(doc, 'annotation',_ANNOTATION, source_node)

        createChildNode(doc, 'image','flickr', source_node)

        createChildNode(doc, 'flickrid','NULL', source_node)

        root_node.appendChild(source_node)

        # owner节点

        owner_node = doc.createElement('owner')

        # owner的子节点

        createChildNode(doc, 'flickrid','NULL', owner_node)

        createChildNode(doc, 'name',_AUTHOR, owner_node)

        root_node.appendChild(owner_node)

        # size节点

        size_node = doc.createElement('size')

        createChildNode(doc, 'width',str(width), size_node)

        createChildNode(doc, 'height',str(height), size_node)

        createChildNode(doc, 'depth',str(3), size_node)

        root_node.appendChild(size_node)

        # segmented节点

        createChildNode(doc, 'segmented',_SEGMENTED, root_node)


        attrs = dict()

        attrs['xmin']= str(left_dist)

        attrs['ymin']= str(top_dist)
        attrs['xmax']= str(left_dist + width)
        attrs['ymax']= str(top_dist + height)

        attrs['classification'] = "person"
        # 构建XML文件名称

        # 创建XML文件

        # createXMLFile(attrs, width, height, xml_file_name)
        # object节点

        object_node = createObjectNode(doc, attrs)

        root_node.appendChild(object_node)

        # 写入文件

        writeXMLFile(doc, xml_save_path)


def get_random_background_image(background_path):
    file_list = os.listdir(background_path)
    total_num = len(file_list) - 1
    idx = randint(0, total_num)
    # print("idx: ",idx)
    image_path = file_list[idx]
    picture_path = os.path.join(os.path.abspath(background_path), image_path)
    return picture_path

def get_random_name(ran_len):
    ran_cord = ""
    for x in range(ran_len):
        ran_cord += str(random.randint(0,9))

    return ran_cord

def merge_picture(src_img, dst_img):
    src_rows, src_cols, _ = src_img.shape
    dst_rows, dst_cols, _ = dst_img.shape
    print(dst_cols,":",src_cols,":",dst_cols - src_cols - 1)
    print(dst_rows,":",src_rows,":",dst_rows - src_rows - 1)
    try:
        tl_left = randint(0, dst_cols - src_cols - 30)
        tl_top = randint(0, dst_rows - src_rows - 30)
        br_right = tl_left + src_cols
        br_bottom = tl_top + src_rows
        dst_img[tl_top:br_bottom, tl_left:br_right] = src_img
    except Exception as e:
        return dst_img, -1, -1
       
    return dst_img, tl_left, tl_top


if not os.path.exists(IMAGE_PATH):
    os.makedirs(IMAGE_PATH)

if not os.path.exists(XML_PATH):
    os.makedirs(XML_PATH)

s_img_path = WSI_MASK_PATH + human_img

files= os.listdir(BACKGROUND_IMAGE_PATH) #遍历背景（负样本信息）
for file in files: #遍历文件夹
     if not os.path.isdir(file): #判断是否是文件夹，不是文件夹才打开
        jpg_file = BACKGROUND_IMAGE_PATH+"/"+file
        n_name = get_random_name(15);
        jpg_save_name = n_name +  ".jpg"
        xml_save_name = n_name + ".xml"

        xml_save_path = WSI_MASK_PATH + '/' + XML_PATH + '/' + xml_save_name
        img_original = cv.imread(jpg_file)
        dst = cv.imread(get_random_background_image(s_img_path))
        res, left_dist, top_dist = merge_picture(dst, img_original)    
        try:
            h, w, _ = dst.shape
        except Exception as e:
            continue
        if left_dist == -1 or top_dist ==-1:
            print("================")
            continue

        create_xml(xml_save_path, jpg_save_name, w, h, left_dist, top_dist, res)

        cv.imwrite(WSI_MASK_PATH + '/' + IMAGE_PATH + '/' + jpg_save_name, res)
        # cv.imshow("res", res)
        # cv.waitKey(0)
