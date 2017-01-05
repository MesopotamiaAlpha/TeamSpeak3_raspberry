#!/bin/sh
#este script é para iniciar o ts dentro do servido e conferir se o processo esta rodando,adicionei dentro do /etc/profile
cd /home/jose/teamspeak3-server_linux_x86/
./ts3server_minimal_runscript.sh filetransfer_ip=0.0.0.0 filetransfer_port=30035 #aqui deve se colocar a porta desejada
        pgrep ts3server && echo '\033[32mRodando\033[0m'
        pgrep ts3server || echo '\033[1;31mNao esta rodando\033[0m'

exit 0;
