爬取noj下的题目，根据requirements.txt安装相应的依赖包   

`pip install -r requirements.txt`   

在[cpskill.py](noj/spiders/cpskill.py)文件下，更换自己在CPSKILL平台下的账号密码


```Python
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
```
   

   
运行`scrapy crawl cpskill -o question.json` 这样就可以获取到相应的题目并以JSON形式存储，在json2markdown.py中，提供将这些题目从JSON转为markdown文件的形式，便于阅读.