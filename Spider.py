import requests,re
from bs4 import BeautifulSoup
def get_page_reg(html):
    soup = BeautifulSoup(html,'lxml');
    title = soup.find(class_="j_chapterName").string;#找class要用class_
    nextUrl = soup.find(id="j_chapterNext")['href'];
    content = "";
    for p in soup.find(class_="j_readContent").find_all("p"):
        content +=p.string;
    return [title,content,nextUrl];

def get_page(url):
    response = requests.get(url);
    if (response.status_code == 200):
        html=response.text;
#        print(html);
        return html

def str_replace(str):
        return re.sub(r"<p>","",str);
def main(url):
    html = get_page(url);
    result = get_page_reg(html);
    print(result[0]);
    print(str_replace(result[1]));

    with open('wrwd.txt','a') as f:
        f.write(result[0]);
        f.write(str_replace(result[1]));
    main("http:%s" % result[2]);
url = "https://read.qidian.com/chapter/t00aeE2RFyQz2wAI5wVpbA2/QMDIrTaPkYPM5j8_3RRvhw2";
main(url);
    #soup = BeautifulSoup(html);
    #new_html = soup.prettify();优化html结构
    #print(new_html);
    #print(soup.title.string);输出两个title中的字符串
    #soup.p 找p标签 soup.a 找a标签
    #soup.find_all("a") 找所有a标签
    #soup.find(id="link3")
    #for a in soup.find_all('a')
    #   print(a["i1"])
    #soup.get_text()打印出所有文本 爬网页时可以找里面有没有想要的信息 保存这个网址
    #lxml HTML解析器 速度快