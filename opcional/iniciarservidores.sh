#!/bin/bash

#Este script é para quando o raspberry ligar ele iniciar o quemu com os servidores,eu coloquei este script na area de trabalho e dentro do
#/etc/profile eu coloquei o caminho para iniciar o script,no caso ele inicia 2 servidores funcionais e 1 de teste


#
### BEGIN INIT INFO
# Provides:          Servidor 3
# Required-Start:    
# Required-Stop:     
# Should-Start:      
# Should-Stop:       
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Servidor ts
# Description:       Servidor ts
### END INIT INFO
#

echo iniciando....

cd /home/pi/Desktop/Servidor\ 1/
lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 -redir tcp:30035::30035 -redir tcp:100$
cd /home/pi/Desktop/Servidor\ 2/
lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9023::22 -redir udp:9056::9987 -redir tcp:30036::30036 -redir tcp:100$
cd /home/pi/Desktop/Servidor\ 3/
lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9024::22 -redir udp:9057::9987 -redir tcp:30037::30037 -redir tcp:100$
cd
exit 0;
