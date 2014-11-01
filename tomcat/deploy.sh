#!/bin/bash

# env	CLASSPATH=/usr/share/tomcat7/lib/servlet-api.jar
# 	CATALINA_ROOT=/var/lib/tomcat7/webapps/15619

javac src/q?.java -d web/WEB-INF/classes
sudo cp -r web/* $CATALINA_ROOT

