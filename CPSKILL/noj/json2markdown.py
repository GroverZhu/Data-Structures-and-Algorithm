import json
import numpy as np

names = ["1.水题", "2.循环", "3.枚举", "4.函数", "5.数组", "6.字符串", "7.复杂数据", "8.数据结构", "9.思维的体操", "10.挑战ACM-ICPC"]

def combine(paths, dst):
    """将所有的题目合并，暂不去除冗余题目
    Args:
        paths: 题目保存的文件路径
        dst: 合并题目后的文件路径
    """
    problems = [[]]
    flag = 0
    for path in paths:
        with open(path, 'r') as f:
            data = json.load(f)
            data.sort(key=lambda k: (k.get("number", 0))) # 根据题目号进行排序
            if flag == 0:
                problems = np.append(problems, data)
                problems = problems.reshape(10, 10)
                flag = 1
            else:
                data = np.reshape(data, (10, 10))
                problems = np.hstack((problems, data))
    problems = list(problems.flatten())
    with open(dst, 'w') as f:
        json.dump(problems, f, ensure_ascii=False)
    pass

def deduplicate(path, windowns=10*6):
    """去除重复的题目
    Args:
        path: 将题目保存后的文件路径
        windows: 每季的题目是10道题，用n个账号就有10*n道题
    """
    # names = ["1.水题.MD", "2.循环.MD", "3.枚举.MD", "4.函数.MD", "5.数组.MD", "6.字符串.MD", "7.复杂数据.MD", "8.数据结构.MD", "9.思维的体操.MD", "10.挑战ACM-ICPC.MD"]
    with open(path, "r") as f:
        data = json.load(f)
        begin = 0
        fragment = 1
        end = fragment * windowns
        while end <= len(data):
            problems = data[begin:end]
            # 去除冗余题目
            problems.sort(key = lambda k : (k.get("name", 0))) # 根据题目来排序
            i = 0
            temp = []
            while i < len(problems):
                temp = np.append(temp, problems[i])
                j = i + 1
                while j < len(problems) and problems[i]["name"] == problems[j]["name"]:
                    j += 1
                i = j
            problems = list(temp)
            print(len(problems))
            with open(f"{names[fragment - 1]}.json", "w") as f:
                json.dump(problems, f, ensure_ascii=False)
            begin = end
            fragment += 1
            end = fragment * windowns
    pass

def json2markdown():
    """将json形式的文件转化为markdown
    """
    blank = "   \n" #结束换行
    prefix = ">" # markdown前缀
    for path in names:
        with open(f"{path}.json", 'r') as f:
            data = json.load(f)
            md = f"# {path}{blank}\n[TOC]{blank}\n"
            for problem in data:
                name = problem["name"]
                description = problem["description"]
                input = problem["input"]
                output = problem["output"]
                sample_input = problem["sample_input"]
                sample_output = problem["sample_output"]
                image_urls = problem["image_urls"]
                temp = ""
                for line in description:
                    temp += line
                description = temp
                images = ""
                for image in image_urls:
                    url = image.split("/")[-1]
                    images += f"![](./images/{url}){blank}"
                if images != "":
                    temp = f"## {name}{blank}{prefix}**Description:** {description}{blank}{prefix}{images}{prefix}**Input:** {input}{blank}{prefix}**Output:** {output}{blank}{prefix}**Sample Input:** {sample_input}{blank}{prefix}**Sample Output:** {sample_output}{blank}\n\n"
                else:
                    temp = f"## {name}{blank}{prefix}**Description:** {description}{blank}{prefix}**Input:** {input}{blank}{prefix}**Output:** {output}{blank}{prefix}**Sample Input:** {sample_input}{blank}{prefix}**Sample Output:** {sample_output}{blank}\n\n"
                md += temp
            with open(f"{path}.MD", 'w') as f:
                f.write(md)


    pass

if __name__ == "__main__":
    paths = ["./question1.json", "./question2.json", "./question3.json", "./question4.json", "./question5.json", "./question6.json"]
    dst = "./result.json"
    combine(paths, dst)
    deduplicate(dst, 60)
    json2markdown()