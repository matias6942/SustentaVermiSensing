
# Description

Sensing unit codes. Connect Arduino Nano (Old Bootloader) and run the Node-RED 
dashboard to see real-time graphs of temperature [°C] and soil humidity [%].

Plataform: Linux Mint [Debian Based Distribution]

# Installation Instructions

## Install Node.js 

https://github.com/nodesource/distributions/blob/master/README.md

## Install Node-Red

sudo npm install -g --unsafe-perm node-red

## Go to Node-red Dir Install serial and Dashboard Nodes on local machine

	cd ~/.node-red
	npm i node-red-node-serialport
	npm install node-red-dashboard	

# Running

To start node-red type on terminal:

	node-red

To display a Flow:

    http://localhost:1880

Dashboard:

	http://localhost:1880/ui 
