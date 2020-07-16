# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import scrapy
from scrapy.pipelines.images import ImagesPipeline
from scrapy.exceptions import DropItem


class NojPipeline:
    def process_item(self, item, spider):
        return item


class NojImagesPipeline(ImagesPipeline):
    

    def file_path(self, request, response=None, info=None):
        """重命名图片文件的名称
        """
        image_name = request.meta["name"]
        return f"{image_name}"

    def get_media_requests(self, item, info):
        """获取图片
        """
        base_url = "http://noj.nwpu.edu.cn/cpbox/"
        for url in item["image_urls"]:
            name = url.split("/")[-1]
            url = f"{base_url}{url}"
            print("name:" + name)
            yield scrapy.Request(url, meta={"name":name})
        pass

    def item_completed(self, results, item, info):
        # image_paths = [x["path"] for ok, x in results if ok]
        # if not image_paths:
        #     raise DropItem("Item contains no images")
        return item