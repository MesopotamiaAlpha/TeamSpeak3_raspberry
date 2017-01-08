# TeamSpeak3_raspberry
Projeto de servidor Ts3 no Raspberry arm
Este projeto ainda esta em fase de desenvolvimento,mas basicamente é para rodar um servidor de Teamspeak 3 32bits dentro de um Raspberry pi 3 com arquitetura ARM.
Logo mais vou estruturar e colocar o passo a passo

!!!!!!!!!!!!!!! TODAS AS INFORMAÇÕES ABAIXO ESTAO BAGUNÇADAS E SÃO ANOTAÇÕES COM O TEMPO ESTOU ARRUMANDO !!!!!!!!!!!!!!!!!!!!!!!!
materia para trocar de cor das letras http://tldp.org/HOWTO/Bash-Prompt-HOWTO/x329.html


I got Teamspeak 3 running using qemu running a x86 Debian squeeze. There is some room for improvement for sure, but for now that's what worked for me. I hope I didn't forget something.

First of all thanks to Dietmar and meigrafd of the raspberry pi forum. Without their work I wouldn't have succeeded.

How to

Installing qemu

We need some software apt-get install git zlib1g-dev libsdl1.2-dev
Download the source of qemu (wget 198.154.101.186/RaspberryPI/qemudidi2.rar) already patched by Dietmar for Raspberry pi. It is qemu 0.15.50 from Thoronir, because the support for ARM host seems to be even worse with the current version.
Unrar it unrar x qemuADLI.part1.rar. You have to use the unrar non-free version (Link to howto)
Configure what to compile (takes about a minute) ./configure --target-list="i386-softmmu" --enable-sdl --extra-cflags="-O3 -mfloat-abi=hard -mfpu=vfp -mcpu=arm1176jzf-s -mtune=arm1176jzf-s -march=armv6zk" --audio-drv-list="alsa oss sdl pa" --audio-card-list="ac97 es1370 sb16 cs4231a adlib gus hda"
Now compile make (takes half an hour at least)
Now install make install
Now qemu is installed successfully.
Preparing Debian Image (using Windows as host)

******************
This problem occur because rt library doesn't link.

Edit Makefile.target in your qemu directory, find LIBS+=-lz, add LIBS+=-lrt beneath this line.

Or say, added following patch locally
**************************************
Disabling the blank screen forever
If you want to disable the blank screen at every startup, just update the /etc/lightdm/lightdm.conf file and add in the [SeatDefaults] section the following command:

[SeatDefaults]
xserver-command=X -s 0 -dpms
 
You need root rights to update the lightdm.conf file. You can use the nano editor:

$ sudo nano /etc/lightdm/lightdm.conf
********************************************

Download and install qemu for Windows (Link)
Download Debian netinstall image (squeeze). I used squeeze, but wheezy might be also good.
Create image using qemu-img.exe create -f qcow2 G:\debian.img 1500M(smaller size should be suffient too)
Install debian x86. I recommend to choose no meta package. qemu-system-i386.exe -cpu 486 -hda G:\debian.img -cdrom G:\debian-8.6.0-i386-netinst.iso -boot d -m 512 -smp 1

After installation run the qemu command again, but with some changes qemu-system-i386.exe -cpu 486 -hda G:\debian.img -boot d -m 512 -smp 1 -redir tcp:9022::22 -redir udp:1234::9987. -redir is used to redirect the network from the guest to the hosts ports.
Now install less and your favorite editor (like nano, vim,etc.) you like to use apt-get install less vim
Install OpenSSH Server apt-get install openssh-server
Install Teamspeak like you usually would do.
Connect to teamspeak from you windows host using localhost:1234 (remember above we redirected the port)
Test to connect to it via ssh/putty using localhost:9022
Shutdown shutdown -hP now the image and copy it via scp(winscp) to your pi.
Run it on the Pi (Use a SSH for the following commands)

***** bios funcional logo a baixo Get the missing qemu Bios wget -O /usr/share/qemu/sgabios.bin http://qemu.weilnetz.de/w32/2012-06-28/sgabios.bin
Start it! qemu -cpu 486 -hda debian.img -m 150m -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 --nographic
If you get a memory error then try it a few times.
If it says starting Grub then wait some minutes (it's booting in the background, but you will never get a prompt here!). Now login with a other SSH terminal to login 'ssh root@localhost -p 9022'
Now start Teamspeak and try to log in on port 9055 of the Pi.
Shutdown again the qemu guest.
Start it again but add -daemonize, so it runs even when you log off. I also made a script to help me.
Performance

My Pi is the 256 MB version overclocked to 1000 Mhz using raspi-config.

The Pi runs constantly at 70% CPU load average. It varies between 50% (using 700 MHz) and nearly 100% using 1000 MHz. But the load shows "0.77, 0.83, 0.80", which is okay.

In the future I hope to either use a native Teamspeak version (my hope is still up) or to use qemu in user mode and better performance with more current version. Time will tell :)

I have yet to test the performance of teamspeak itself, if it is usable for gaming situations. I noticed some milliseconds latence overhead, but not too much to worry yet.


a bios que esta faltando funcionou neste site
https://github.com/qemu/qemu/blob/master/pc-bios/sgabios.bin
qemu/pc-bios/sgabios.bin

wget -O /usr/share/qemu/sgabios.bin qemu/pc-bios/sgabios.bin

comando para iniciar correto:
qemu-system-i386 -cpu SandyBridge -hda debian.img -m 150 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 --nographic

onde 9022 é a porta externa e 22 porta a ser redirecionada
e 9055 porta externa e 9987 porta redirecionada
Foi necessario adicionar a porta no iptables para funcionar corretamente
iptables -I INPUT  -p udp --dport 9055 -j ACCEPT
iptables -A INPUT -p udp --dport 9055 --jump ACCEPT
iptables-save

configurar porta de arquivo e query
voz udp 9055
arquivo  tcp 30033
query tcp 10011

a imagem que esta funcionando esta com um ts ja instalado,mas é so apagar a pasta e descompactar no usuario root

***********
para desabilitar o screensaver
The easiest way is to add the parameter consoleblank=0 to your kernel command-line at boot-time.

Open /etc/default/grub in your favorite editor; you will need to use sudo (for vi, nano, etc.) or gksudo (for gedit, etc.).
Then add consoleblank=0 to the GRUB_CMDLINE_LINUX_DEFAULT=, parameter.
e.g. yours may say:
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash consoleblank=0"
Then run sudo update-grub, and reboot.
************
qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 --nographic
qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9023::22 -redir udp:9056::9987 --nographic
qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9024::22 -redir udp:9057::9987 --nographic
******************************
para logar automaticamente
acesse este arquivo
etc/systemd/system/getty.target.wants/getty@tty1.service

change the line

  ExecStart=-/sbin/agetty --noclear %I $TERM
to

  ExecStart=-/sbin/agetty --noclear -a root %I $TERM
This just follows from the agetty manual page, which states, among other things:

-a, --autologin username

Log the specified user automatically in without asking for a login name and password. The -f username option is added to the /bin/login command line by default. The --login-options option changes this default behavior and then only \u is replaced by the username and no other option is added to the login command line.
*****************************
Per default, the TS3 server creates a virtual voice server on port 9987 (UDP). The ServerQuery is listening on port 10011 (TCP) and file transfers will use port 30033 (TCP)...

ao iniciar o ts ele demora muito para iniciar,quase 20 minutos.

para saber a temperatura do rasp
vcgencmd measure_temp

para iniciar o programa com pid adicione & no final

*********************************
para deixar o grub iniciar o sistema automaticamente
Precisamos acessa-lo com um editor de texto como super usuário. Neste exemplo vou utilizar o Gedit para editar o arquivo do grub.

O arquivo de configuração do gerenciador de boot fica localizado na pasta /etc.

Clique aqui para saber mais SOBRE PASTAS E DIRETÓRIOS NO UBUNTU LINUX. 

O que temos que fazer é bem simples, abra o terminal, CTRL+ALT+T. O arquivo de configuração é o Grub. 

~$sudo gedit /etc/default/grub

Ao abrir o arquivo procure pela linha onde há a seguinte diretiva:

GRUB_DEFAULT=0

Agora troque o "0" por "5", sem aspas, como de fato está, ficando assim:

GRUB_DEFAULT=5

Agora utilize o menu do Gedit e salve a alteração. Feito isso, volte para o terminal, vamos atualizar o Grub. Digite o comando:

~$sudo update-grub

Está feito, inicialize o sistema e veja a alteração.  Veja aqui também outra forma de personalizar o Grub com o grub-customizer.

**************************************

para iniciar um script no inicio edite o arquivo /etc/profile, adicione o caminho do script no inicio deste arquivo

para conferir se a porta 9055 esta onlive use o netcat para pingar na porta UDP, nc -zuvv calbox.ddns.net 9055,na resposta vai mostrar se teve sucesso ou nao ao conectar a porta,verifiquei que caso a porta esteja fechada ele nao esta trazendo nenhum resultado.
E para verficar se a porta TCP esta funcionando use o comando -zvv e a porta

./ts3server_minimal_script.sh filetransfer_ip=0.0.0.0 filetransfer_port=30034

tcp 10011
tcp 30033
udp 9987
tcp 30033
tcp 10011
tcp 41144
