#!/bin/bash
export CLASSPATH=/usr/share/tomcat7/lib/servlet-api.jar
export CATALINA_ROOT=/var/lib/tomcat7/webapps/ROOT
sudo iptables -A PREROUTING -t nat -p tcp --dport 80 -j REDIRECT --to-port 8080
