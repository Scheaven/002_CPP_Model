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
ori_xml_path = 'ann'
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
def createElementNode(tag, attr):  # 创建一个元素节�?
    element_node = ET.Element(tag)
    element_node.text = attr
    # 创建一个文本节�?
    # text_node = ET.Element(attr)

    # 将文本节点作为元素节点的子节�?
    # element_node.append(text_node)

    return element_node

    # 封装添加一个子节点的过�?
def createChildNode(tag, attr, parent_node):

    child_node = createElementNode(tag, attr)

    parent_node.append(child_node)

# object节点比较特殊

def createObjectNode(attrs):

    object_node = ET.Element('object')

    createChildNode('name', attrs['classification'],
                    object_node)

    createChildNode('pose',_POSE, object_node)

    createChildNode('truncated', _TRUNCATED, object_node)

    createChildNode('difficult', _DIFFICULT, object_node)

    bndbox_node = ET.Element('bndbox')

    createChildNode('xmin', attrs['xmin'],
                    bndbox_node)

    createChildNode('ymin', attrs['ymin'],
                    bndbox_node)

    createChildNode('xmax', attrs['xmax'],
                    bndbox_node)

    createChildNode('ymax', attrs['ymax'],
                    bndbox_node)

    object_node.append(bndbox_node)

    return object_node

# 将documentElement写入XML文件�?
def writeXMLFile(doc, filename):


    doc.write('tmp.xml', encoding = 'utf-8', xml_declaration=True)

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
def update_xml(xml_path, xml_save_path, jpg_save_name, bg_h, bg_w, width, height, left_dist, top_dist, res):

    tree = ET.parse(xml_path)
    root_node = tree.getroot()
    filename = root_node.find('filename')
    filename.text = jpg_save_name

    size = root_node.find('size')
    size.find('width').text = str(bg_w)
    size.find('height').text = str(bg_h)
    flag =0 
    img=res

    attrs = dict()

    attrs['xmin']= str(left_dist)

    attrs['ymin']= str(top_dist)
    attrs['xmax']= str(left_dist + width)
    attrs['ymax']= str(top_dist + height)

    attrs['classification'] = "person"

    object_node = createObjectNode(attrs)

    root_node.append(object_node)

    # 写入文件

    writeXMLFile(tree, xml_save_path)


def get_random_background_image(background_path):
    file_list = os.listdir(background_path)
    total_num = len(file_list) - 1
    idx = randint(0, total_num)
    # print("idx: ",idx)
    image_path = file_list[idx]
    picture_path = os.path.join(os.path.abspath(background_path), image_path)
    return picture_path, image_path

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
s_xml_path = WSI_MASK_PATH + ori_xml_path

files= os.listdir(s_img_path) #得到文件夹下的所有文件名称
for file in files: #遍历文件夹
     if not os.path.isdir(file): #判断是否是文件夹，不是文件夹才打开
        jpg_file = s_img_path+"/"+file

        n_name = get_random_name(15);
        jpg_save_name = n_name +  ".jpg"
        xml_save_name = n_name + ".xml"

        xml_save_path = WSI_MASK_PATH + '/' + XML_PATH + '/' + xml_save_name
        img_original = cv.imread(jpg_file)
        try:
            h1, w1, _ = img_original.shape
            src = cv.resize(img_original, (w1*2,h1*2))
            w = w1*2
            h = h1*2
        except Exception as e:
            continue
        bg_img, bg_img_path = get_random_background_image(BACKGROUND_IMAGE_PATH)
        dst = cv.imread(bg_img)
        xml_path = s_xml_path+"/"+bg_img_path.split('.')[0] + ".xml"

        res, left_dist, top_dist = merge_picture(src, dst)    

        if left_dist == -1 or top_dist ==-1:
            print("================")
            continue

        bg_h, bg_w, _ = dst.shape

        update_xml(xml_path, xml_save_path, jpg_save_name, bg_h, bg_w, w, h, left_dist, top_dist, res)

        cv.imwrite(WSI_MASK_PATH + '/' + IMAGE_PATH + '/' + jpg_save_name, res)

        # cv.imshow("res", res)
        # cv.waitKey(0)
