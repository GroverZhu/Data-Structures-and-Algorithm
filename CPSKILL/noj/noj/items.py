# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class NojItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    number = scrapy.Field()
    name = scrapy.Field() # 题目名称
    description = scrapy.Field() # 题目描述
    image_urls = scrapy.Field() # 部分题目的描述有图片
    input = scrapy.Field() # 题目输入
    output = scrapy.Field() # 题目输出
    sample_input = scrapy.Field() # 输入示例
    sample_output = scrapy.Field() # 输出示例
    pass
