import sys
from datetime import datetime

def calculate(today,last):
    now = datetime.strptime(today,"%Y-%m-%d")
    latest_u = datetime.strptime(last,"%Y-%m-%d")
    time_final = (now - latest_u).days
    print(time_final)
    return time_final

calculate(sys.argv[1],sys.argv[2])
