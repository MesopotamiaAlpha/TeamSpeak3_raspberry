# TeamSpeak3_raspberry
Projeto de servidor Ts3 no Raspberry arm
Este projeto ainda esta em fase de desenvolvimento,mas basicamente é para rodar um servidor de Teamspeak 3 32bits dentro de um Raspberry pi 3 com arquitetura ARM.
Logo mais vou estruturar e colocar o passo a passo

!!!!!!!!!!!!!!! TODAS AS INFORMAÇÕES ABAIXO ESTAO BAGUNÇADAS E SÃO ANOTAÇÕES COM O TEMPO ESTOU ARRUMANDO !!!!!!!!!!!!!!!!!!!!!!!!

Bom eu estou documentando este projeto pois eu levei alguns meses para conseguir o resultado que eu queria no servidor, e quero compartilhar o conhecimento que adquiri para outras pessoas que queiram fazer o mesmo, por muito tempo eu conseguia encontrar algumas pessoas que conseguiram instalar e rodar o Teamspeak server no raspberry mas boa parte nao documentava o processo, e alguns casos que encontrava informações elas nao funcionavam da maneira correta, obrigando a ter que pesquisar ainda mais para conseguir fazer tudo funcionar.
Eu tenho conhecimento do Exagear que consegue fazer os programas de 32 bits rodarem de forma "nativa" na arquitetura ARM, mas no meu caso nao tenho 93 reais para investir em um programa que derrepente posso usar em poucas ocasioes.
Então foi onde resolvi iniciar este projeto de rodar o servidor de Teamspeak de maneira alternativa.
Vou tentar deixar o mais simples de entender pois nao quero que outros tenham a mesma dificuldade que tive e tempo que levei para entender e rodar.
Lembrando que esta escolha do qemu tem um desempenho bem devagar para iniciar a maquina virtual e iniciar o servidor dentro dele, é uma escolha alternativa mesmo para quem nao quer investir com o Exagear, mas ele nao afeta em quase nada no raspberry.


Estou utilizando o raspberry pi 3 e sistema operacional Raspbian mesmo do site da raspberry, fiz uma pequena modificação no sistema somente para nao ter a tela de descanço e o aumento da memoria swap onde deixei dentro da pasta opcional o arquivo com o nome zram.

######Primeira parte Preparando o sistema

Bom durante a pesquisa verifiquei que a melhor forma que encontraram de conseguir fazer o servidor do Teamspeak de 32 bits rodar na arquitetura ARM foi de rodar uma maquina virtual dentro do raspberry e rodar o Teamspeak dentro dele, imaginei que talvez ia usar muito recurso do rasp mas consegui achar um meio termo dele onde rodou muito bem.
Para isso vamos instalar no raspbian (sistema operacional usado no raspberry) o qemu:

sudo apt-get install qemu

obs:Encontrei alguns projetos mostrando que era necessário compilar e outros fazer uma programação para funcionar o qemu de forma correta, mas no meu caso nao foi necessario.

Beleza com o qemu instalado no raspberry agora vamos preparar o sistema onde o Teamspeak vai rodar, mas temos 2 formas de preparar ele e agora fica a sua escolha, podemos preparar usando o Linux ou usando o Windows e caso queria usar o Windows você precisa instalar o qemu tambem no outro sistema somente para fazer a imagem.

######Segunda parte Baixando e preparando a imagem

Certo agora vamos baixar a iso do sistema que vamos usar, no caso é o [Debian netinst] (https://www.debian.org/CD/netinst/), é uma versão reduzida do debian e devemos baixar a versao i386 (x32) ate a presente data esta nesta versão debian-8.6.0-i386-netinst.iso. Neste [link] (https://cdimage.debian.org/debian-cd/8.6.0/i386/iso-cd/) possui todas as versões da iso.

Agora com a iso baixada e o qemu instalado eu vou seguir os passo que utilizei para criar a imagem no Windows, caso esteja usando o Linux para criar a imagem é so adaptar para seu sistema.

Vamos criar a imagem agora para rodar o sistema, abra o CMD e entre na pasta do qemu _C:\Program Files\qemu_