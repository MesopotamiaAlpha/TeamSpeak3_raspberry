# TeamSpeak3_raspberry

Este projeto ainda esta em fase de desenvolvimento,mas basicamente é para rodar um servidor de Teamspeak 3 32bits dentro de um Raspberry pi 3 com arquitetura ARM.
Logo mais vou estruturar e colocar o passo a passo

Bom eu estou documentando este projeto pois levei alguns meses para conseguir o resultado que eu queria no servidor, e quero compartilhar o conhecimento que adquiri para outras pessoas que queiram fazer o mesmo, por muito tempo eu conseguia encontrar algumas pessoas que conseguiram instalar e rodar o Teamspeak server no raspberry mas boa parte não documentava o processo, e alguns casos que encontrava informações elas não funcionavam da maneira correta, obrigando a ter que pesquisar ainda mais para conseguir fazer tudo funcionar.
Eu tenho conhecimento do Exagear que consegue fazer os programas de 32 bits rodarem de forma "nativa" na arquitetura ARM, mas no meu caso não tenho 93 reais para investir em um programa que derrepente posso usar em poucas ocasiões,além do mumble.
Então foi onde resolvi iniciar este projeto de rodar o servidor de Teamspeak de maneira alternativa.
Vou tentar deixar o mais simples de entender pois não quero que outros tenham a mesma dificuldade que tive e tempo que levei para entender e rodar.
Lembrando que esta escolha do qemu tem um desempenho bem devagar para iniciar a maquina virtual e iniciar o servidor dentro dele, é uma escolha alternativa mesmo para quem não quer investir com o Exagear, mas ele não afeta em quase nada no raspberry.

Estou utilizando o raspberry pi 3 e sistema operacional Raspbian mesmo do site da raspberry, fiz uma pequena modificação no sistema somente para não ter a tela de descanço e o aumento da memoria swap onde deixei dentro da pasta opcional o arquivo com o nome zram.

## 1- Primeira parte Preparando o sistema

Bom durante a pesquisa verifiquei que a melhor forma que encontraram de conseguir fazer o servidor do Teamspeak de 32 bits rodar na arquitetura ARM foi de rodar uma máquina virtual dentro do raspberry e rodar o Teamspeak dentro dele, imaginei que talvez ia usar muito recurso do rasp mas consegui achar um meio termo dele onde rodou muito bem.
Para isso vamos instalar no raspbian (sistema operacional usado no raspberry) o qemu:

**sudo apt-get install qemu**


obs:Encontrei alguns projetos mostrando que era necessário compilar e outros fazer uma programação para funcionar o qemu de forma correta, mas no meu caso nao foi necessario.
Beleza com o qemu instalado no raspberry agora vamos preparar o sistema onde o Teamspeak vai rodar, mas temos 2 formas de preparar ele e agora fica a sua escolha, podemos preparar usando o Linux ou usando o Windows e caso queria usar o Windows você precisa instalar o qemu tambem no outro sistema somente para fazer a imagem.

## 2- Segunda parte Baixando e preparando a imagem

Certo agora vamos baixar a iso do sistema que vamos usar, no caso é o [Debian netinst] (https://www.debian.org/CD/netinst/), é uma versão reduzida do debian e devemos baixar a versao i386 (x32) ate a presente data esta nesta versão debian-8.6.0-i386-netinst.iso. Neste [link] (https://cdimage.debian.org/debian-cd/8.6.0/i386/iso-cd/) possui todas as versões da iso.

Agora com a iso baixada e o qemu instalado eu vou seguir os passo que utilizei para criar a imagem no Windows, caso esteja usando o Linux para criar a imagem é so adaptar para seu sistema.

Vamos criar a imagem agora para rodar o sistema, abra o CMD e entre na pasta do qemu _C:\Program Files\qemu_ e para criar a imagem use este comando:
obs: no caso do linux somente rodando o comando qemu-img ele ja chama o programa sem a necessidade de entrar na pasta.

**qemu-img.exe create -f qcow2 C:\debian.img 1500M**


**Explicando:**

-qemu-img.exe: É o programa usado para criar a imagem.

-create: Pedindo para criar.

-f: É o formato usado para a imagem.

-C:\debian.img :É o local e o nome que vai ser criado a imagem.

-1500M: É o tamanho que vai ser criado a imagem e neste caso achei que este tamanho esta perfeito.

------
------

## 3- Terceira parte Instalando o sistema
Agora continuando dentro da pasta do quemu use este comando no CMD para iniciar a maquina e instalar o sistema:

**qemu-system-i386.exe -cpu SandyBridge -hda C:\debian.img -cdrom C:\debian-8.6.0-i386-netinst.iso -boot d -m 512 -smp 1**

**Explicando**:

-qemu-system-i386.exe: É o programa para iniciar a maquina virtual.

-cpu: É o tipo de cpu que vai ser usado e neste caso eu tive problemas com a arquitetura 486 proposta por outras pessoas, e pesquisando encontrei este SandyBridge no qual funcionou sem problemas.

-cdrom: É onde esta a iso do netinst.

-boot: Nao sei XD

-m: Aqui é a quantidade de memoria que vai ser alocada para esta maquina, por ser instalação recomendo que deixe 512 mesmo somente para ser mais rapidinho.

-smp não sei tambem XD

Após isto o qemu vai iniciar a sua imagem criada (debian.img) e instalar o sistema dentro dele, desta parte você pode seguir da forma que prefirir.

------
------
## 4- Quarta parte Iniciando o sistema

Certo agora com o sistema instalado dentro da imagem você vai transferir a imagem para dentro do seu raspberry, e uma das partes importantes entra agora.
Para iniciar a maquina virtual você vai colocar este comando no termina:

**qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987**

**Explicando**

-qemu-system-i386: É o programa para iniciar a maquina virtual.

-cpu: O tipo de cpu que vai ser usada.

-hda: Aqui é onde esta a imagem que criamos e ele vai simular um hd apartir da imagem.

-m: É a quantidade de memoria que vai ser alocada para cada maquina virtual, no caso eu optei por 80 megas e gostei.

-smp: ainda nao sei XD

**-redir: Este comando é para redirecionar as conecções vindas na porta, no caso udp ou tcp> porta inicial> porta final dentro da maquina virtual. Esta parte é importante entender para funcionarm no caso eu quero que a conecção tcp que entrar na porta 9022 seja redirecionada para a porta 22 da minha maquina virtual, assim nao entra em conflito com a minha porta 22 do meu raspberry.*

Obs:Estas portas que coloquei é somente de exemplo, use a que prefirir.

Então a opção redir é primordial para coneguir abrir as portas e funcionar sem entrar em conflito com seu sistema operacional, no caso da porta udp 9055 vai ser onde vai entrar a porta de voz do Teamspeak e redirecionar para dentro da maquina na porta de voz 9987.

Neste primeiro momento de iniciar o sistema o processamento de um dos cores do raspberry vai ficar alto mas ao terminar de iniciar ira voltar ao normal, e é normal a demora do inicio do sistema por fato do baixo recurso e do alto processamento.

------
------
## 5- Quinta parte Iniciando o Teamspeak

Bom agora que seu sistema ja esta rodando vamos baixar o Teamspeak dentro da maquina, no caso vamos baixar o Teamspeak Server versão 32 bits para Linux com o comando:

<code>wget http://dl.4players.de/ts/releases/3.0.13.6/teamspeak3-server_linux_x86-3.0.13.6.tar.bz2</code>

Depois disso vamos descompactar o Teamspeak:

**tar -jxvf teamspeak3-server_linux_x86-3.0.13.6.tar.bz2**

Vamos dar permissão total ao ts:

**sudo chmod 777 teamspeak3-server_linux_x86-3.0.13.6**
obs: se der erro de nao ser sudoer entre como root, execute o comando su e coloque a sua senha de root.

Certo depois disso vamos dentro da pasta do Teamspeak:

**cd teamspeak3-server_linux_x86-3.0.13.6**

E inicie o servidor, vou recomendar o script minimal por que mais para frente vai ter mais comando para usar todas as funcionalidades do servidor:

**./ts3server_minimal_runscript.sh**

E depois disso aguarde ele iniciar o servidor somente para você configurar ele de inici e registrar o token de server admin.
Obs: Para iniciar o servidor ele demora BASTANTE, leva em torno de 15-20 min somente para iniciar. Quando aparecer na tela que a palavra de Query onde mostra as portas utilizadas e etc o servidor ja terminou de levantar, caso contrario aguarde.

Depois de iniciado configure e finalize ele.


## 6- Sexta parte Terminando a configuração

Agora vamos configurar o restante das portas de uso do Teamspeak, o servidor usa as seguintes portas:
voz udp 9055
arquivo  tcp 30033
query tcp 10011

E agora no momento de iniciar o servidor vamos ter que dizer para o Teamspeak usar estas portas por fato de caso você colocar mais de um servidor no seu raspberry você vai precisar direcionar para outras portas, mas caso queira ficar somente com as portas padrão nao tem necessidade de mudar as portas.

Esta parte pode ficar um pouco complicado mas como o servidor precisa de 3 portas para usar todas as funcionalidades nós precisamos iniciar a nossa maquina virtual com redir para 3 portas tirando a de ssh caso queira usar.
Entao vamos usar este comando para iniciar a nossa maquina virtual: 

**qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 -redir tcp:30035::30035 -redir tcp:10015::10015**

**Explicando**

-qemu-system-i386: É o programa para iniciar a maquina virtual.

-cpu: O tipo de cpu que vai ser usada.

-hda: Aqui é onde esta a imagem que criamos e ele vai simular um hd apartir da imagem.

-m: É a quantidade de memoria que vai ser alocada para cada maquina virtual, no caso eu optei por 80 megas e gostei.

-smp: Ainda nao sei XD</p>

**redir: Agora vamos para as portas, preciso de 3 portas para a voz,arquivo e query então adicinei as 3 mais a ssh.**

Obs: Caso tenha certeza que esta correto você pode iniciar a maquina com a opção --nographic para nao aparecer a tela do qemu.

E agora dentro da sua maquina virtual você vai iniciar o Teamspeak e pedindo para que ele use as portas que você abriu, assim você vai conseguir usar todas as portas de forma normal:

**./ts3server_minimal_runscript.sh filetransfer_ip=0.0.0.0 filetransfer_port=30035 query_ip=0.0.0.0 query_port=10015**

Desta forma quando alguem for upar algum arquivo no seu servidor ou fazer alguma query o proprio TS vai direcionar para a porta que você pediu.


## Final

Bom até esta parte o teu servidor ja deve estar rodando e funcionando perfeitamente, em termos de performance da maquina virtual ainda nao encontrei maneiras de acelerar o carregamento do sistema e do servidor, mas o desempenho do client do ts esta perfeito.
Tenho uma pasta no meu github que são de coisas opcionais que coloquei para automatizar o servidor em casos de quedas de luz e etc.. Mas não sou programador então algumas coisas podem estar em um estado primario de programação.
