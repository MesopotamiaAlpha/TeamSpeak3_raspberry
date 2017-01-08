
#!/bin/sh
#este script é para iniciar o ts dentro do servidor e conferir se o processo esta rodando
cd /home/usuario/teamspeak3-server_linux_x86/
./ts3server_minimal_runscript.sh filetransfer_ip=0.0.0.0 filetransfer_port=30035 query_ip=0.0.0.0 query_port=10015 #aqui deve se colocar a porta desejada
        pgrep ts3server && echo '\033[32mO TeamSpeak foi iniciado corretamente\033[0m'
        pgrep ts3server || echo '\033[1;31mO TeamSpeak nao foi iniciado\033[0m'

exit 0;
