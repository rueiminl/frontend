#!/usr/bin/python

import sys
import codecs
import json

afinnlist = dict()
bannedlist = dict()
AFINN = open('AFINN.txt', 'r')
for line in AFINN:
	word, value = line.split('\t', 1)
	value = int(value)
	afinnlist[word] = value
AFINN.close()
banned = open('banned.txt', 'r')
for line in banned:
	bannedlist[line.strip()] = 1 
banned.close()
for line in sys.stdin:
	userid, time, id, text = line.split('\t', 3)
	sentiment = 0
	words = json.loads(text)['text'].split(' ')
	for j in range(len(words)):
		    wordlist = []
		    prev = 0
		    for i in range(len(words[j])):
		        if not words[j][i].isalnum():
			    wordlist.append(words[j][prev:i])
			    wordlist.append(words[j][i])
		            prev = i + 1
                    if prev < len(words[j]):
                        wordlist.append(words[j][prev:len(words[j])])
		    for k in range(len(wordlist)):
    		        if wordlist[k].lower() in afinnlist.keys():
   			    sentiment += afinnlist[wordlist[k].lower()]   
    			if wordlist[k].lower() in bannedlist.keys():
    			    wordlist[k] = wordlist[k][0] + (len(wordlist[k]) - 2) * '*' + wordlist[k][-1]
    		    words[j] = ''.join(wordlist)
   	print (userid + ',' + time + ',' + id + ',' + str(sentiment) + ',' + '\"' + ' '.join(words) + '\";`').encode('utf-8')
