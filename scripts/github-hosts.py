# -*- coding=utf-8 -*-

import re
import requests

def get_hosts(url):
    res = requests.get(url).text
    ip = re.search(r'(([01]{0,1}\d{0,1}\d|2[0-4]\d|25[0-5])\.){3}([01]{0,1}\d{0,1}\d|2[0-4]\d|25[0-5])',res).group()
    return ip

with open('/etc/hosts','w') as f:
    nu = ''
    f.write(nu)

ua = "https://github.com.ipaddress.com/"
ub = "https://fastly.net.ipaddress.com/github.global.ssl.fastly.net"
uc = "https://githubusercontent.com.ipaddress.com/raw.githubusercontent.com"
ud = "https://github.com.ipaddress.com/assets-cdn.github.com"
ue = "https://coursera.org.ipaddress.com"
uf = "https://cloudfront.net.ipaddress.com/d3c33hcgiwev3.cloudfront.net"

da = 'github.com'           
db = 'github.global.ssl.fastly.net'
dc = 'raw.githubusercontent.com'
dd = 'assets-cdn.github.com'
de = "coursera.org"
df = "d3c33hcgiwev3.cloudfront.net"

ip_a = get_hosts(ua)
ip_b = get_hosts(ub)
ip_c = get_hosts(uc)
ip_d = get_hosts(ud)
ip_e = get_hosts(ue)
ip_f = get_hosts(uf)

host_a = '{}  {}'.format(ip_a,da)
host_b = '{}  {}'.format(ip_b,db)
host_c = '{}  {}'.format(ip_c,dc)
host_d = '{}  {}'.format(ip_d,dd)
host_e = '{}  {}'.format(ip_e,de)
host_f = '{}  {}'.format(ip_f,df)

hosts = [host_a,host_b,host_c,host_d,host_e,host_f]
for host in hosts:
    with open('/etc/hosts','a') as f:
        #print(host)
        f.write(host+'\n')
