import scrapy
from scrapy.http import Request, FormRequest
from noj.items import NojItem
import re
import numpy as np

class CpskillSpider(scrapy.Spider):
    name = 'cpskill'
    allowed_domains = ['noj.nwpu.edu.cn']
    start_urls = ['http://noj.nwpu.edu.cn/cpbox/cpNPUOJ.aspx'] # noj题目链接
    post_headers = {
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.8,en;q=0.6",
        "Cache-Control": "no-cache",
        "Connection": "keep-alive",
        "Content-Type": "application/x-www-form-urlencoded",
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.5 Safari/605.1.15",
        "Referer": "http://noj.nwpu.edu.cn/cpbox/index.aspx",
    }

    def start_requests(self):
        """重写start_request来获取cookie
        """
        # cookie_str = "ASP.NET_SessionId=4wbhuf55exjkmn55o0a45rmi; save=0; myusername=123456; showtype3=0; Columns=4; CheckCode=0BCD60FB8057EC5A"
        # cookies = {i.split("=")[0]:i.split("=")[1] for i in cookie_str.split("; ")}
        # for url in self.start_urls:
        # yield scrapy.Request(self.start_urls[0], callback=self.parse, cookies=cookies)
        return [Request("http://noj.nwpu.edu.cn/cpbox/index.aspx", meta={"cookiejar": 1}, callback=self.post_login)]

    def post_login(self, response):
        """发送登录请求
        """
        form = response.xpath("//*[@id='aspnetForm']")
        viewState = form.xpath("//*[@id='__VIEWSTATE']").extract_first()
        viewStateGenerator = form.xpath("//*[@id='__VIEWSTATEGENERATOR']").extract_first()
        eventValidation = form.xpath("//*[@id='__EVENTVALIDATION']").extract_first()

        # 通过正则来获取验证内容
        viewState =  re.findall(r'value="(.+?)"', viewState)[0]
        viewStateGenerator =  re.findall(r'value="(.+?)"', viewStateGenerator)[0]
        eventValidation =  re.findall(r'value="(.+?)"', eventValidation)[0]
        # 发送表单提交
        result = [FormRequest.from_response(response,
                                            meta={"cookiejar": response.meta["cookiejar"]},
                                            headers = self.post_headers,
                                            formdata={
                                                "__VIEWSTATE": viewState,
                                                "__VIEWSTATEGENERATOR": viewStateGenerator,
                                                "__EVENTVALIDATION": eventValidation,
                                                "index1$username": "", # cpskil网站的用户名
                                                "index1$Password": "", # 密码
                                                "index1$Button1": "%B5%C7%C2%BC+%2F+sign+in",
                                                "index1$save": "0"
                                            },
                                            callback=self.after_login,
                                            dont_filter=True
                                            )]
        return result
    
    def after_login(self, response):
        for url in self.start_urls:
            yield Request(url, meta={"cookiejar": True})
    
    def parse(self, response):
        """将问题链接解析出来
        """
        baseurl = "http://noj.nwpu.edu.cn/cpbox/cpIPPDFReader.aspx"
        content = response.xpath("//*[@id='lblPOJTable']/table").extract_first()
        links = re.findall(r"url:'cpIPPDFReader.aspx(.+?)'", content)
        urls = []
        for link in links:
            urls = np.append(urls, f"{baseurl}{link}")
        for url in urls:
            yield Request(url=url, meta={"cookiejar":True}, callback=self.problem_parse)
        pass

    def problem_parse(self, response):
        """获取每个问题
        """
        question = NojItem()
        # print(response.xpath("//*[@id='lblIPPDFtitle']/text()").extract_first())
        number = response.xpath("//*[@id='lblIPPDFfilename']/text()").extract_first()
        number = re.findall(r'T(.+?).cpp', number)[0]
        question["number"] = number
        question["name"] = response.xpath("//*[@id='lblIPPDFtitle']/text()").extract_first()
        question["description"] = response.xpath("//*[@id='lblIPPDFdescription']/descendant-or-self::text()").extract() #问题描述不止一行
        question["image_urls"] = response.xpath("//*[@id='lblIPPDFdescription']/img/@src").extract() # 图片可能有多个
        question["input"] = response.xpath("//*[@id='lblIPPDFinput']/text()").extract_first()
        question["output"] = response.xpath("//*[@id='lblIPPDFoutput']/text()").extract_first()
        question["sample_input"] = response.xpath("//*[@id='lblIPPDFsampleinput']/text()").extract_first()
        question["sample_output"] = response.xpath("//*[@id='lblIPPDFsampleoutput']/text()").extract_first()
        yield question
    

