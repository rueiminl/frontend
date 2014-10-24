#!/usr/bin/python

import json
import sys
from datetime import datetime

for line in sys.stdin:
	try:
		tweet = json.loads(line)
		id = tweet['id']
                userid = tweet['user']['id_str']
                time = tweet['created_at']
                dt = datetime.strptime(time, '%a %b %d %H:%M:%S +0000 %Y')
                temp = dict()
		temp['text'] = tweet['text']
		print userid + '\t' + dt.strftime('%Y-%m-%d %H:%M:%S') + '\t' + str(id) + '\t' + json.dumps(temp)
	except ValueError, e:
                pass
		
