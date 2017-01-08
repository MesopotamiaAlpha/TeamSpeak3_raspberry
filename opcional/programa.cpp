//Programa feito para iniciar os servidores e com utilidades para monitorar o servidor
//!!!!EM CONSTRUÇÂO AINDA!!!!
//materia para trocar de cor das letras http://tldp.org/HOWTO/Bash-Prompt-HOWTO/x329.html
//outra materia para cores https://www.vivaolinux.com.br/dica/Shell-script-com-texto-colorido
//Iniciador de servidor no raspberry pi 3

#include <iostream>
#include <unistd.h> //biblioteca do sleep
#include <cstdlib>

using namespace std;

int final(){

	int finalvar;
	cout<<"\n Finalizado?";
	cout<<"\n 1 Sim";
	cout<<"\n 2 Nao\n";
	cin>> finalvar;
	switch(finalvar){
		case 1:
			cout<<"\033[32mFinalizado com sucesso\033[0m \n";
		return 0;
		case 2:
			//menu();
		return 0;
	}
}

int servidores(){
	system("clear");
	int servidor;

	int pid1;
	int pid2;
	int pid3;


	cout<<"---------------------------------------\n";
	cout << "|Escolha qual servidor ira iniciar:   |\n";
	cout << "|Servidor 1: Nuclear Squad            |\n";
	cout << "|Servidor 2: Magneto                  |\n";
	cout << "|Servidor 3: Servidor de testes       |\n";
	cout<<"---------------------------------------\n";

	cin>> servidor;

		switch(servidor){
			case 1:
			system("clear");
			chdir("Servidor 1");
			system("lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9022::22 -redir udp:9055::9987 -redir tcp:30035::30035 -redir tcp:10015::10015 &");
			cout << "Servidor inicia com pid :";
			system("pgrep qemu");
			cout<<"\033[32mIniciado com sucesso\033[0m";
			cout<<"\n";
			final();
			return 0;

			case 2:
			system("clear");
			chdir("Servidor 2");
			system("lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9023::22 -redir udp:9056::9987 -redir tcp:30036::30036 -redir tcp:10016::10016 &");
			cout << "Servidor inicia com pid :";
			system("pgrep qemu");
			cout<<"\033[32mIniciado com sucesso\033[0m";
			cout<<"\n";
			final();
			return 0;

			case 3:
			system("clear");
			chdir("Servidor 3");
			system("lxterminal -e qemu-system-i386 -cpu SandyBridge -hda debian.img -m 80 -smp 1 -redir tcp:9024::22 -redir udp:9057::9987 -redir tcp:30037::30037 -redir tcp:10017::10017 &");
			cout << "Servidor inicia com pid :";
			system("pgrep qemu");
			cout<<"\033[32mIniciado com sucesso\033[0m";
			cout<<"\n";
			final();
			return 0;
		}
}


int temperatura(){
	char tempe;
	int contador;
	int variavel;
	system("clear");
	cout << "Para uma verificação escolha a opção 1\n";
	cout<< "Intervalo de tempo para execução: 2min, 5min,20min:";

	cin >> variavel;
	cout<< ("\nTempo escolhido:");
	cout << (variavel);

	switch(variavel){
		case 1:
			cout << "\nEscolhido 1 opção: \n ";
			system ("vcgencmd measure_temp > /home/pi/Desktop/testesaida.txt"); //continuar a fazer os testes,aqui teve a saida da temperatura,agora tem que ler a saida e verificar a temperatura
			cout<< "\nVariavel dentro:";
			cout<<(tempe);
				if (tempe == 0){
					cout<< "Esta vazio\n";
				}else{
					cout<<"tem algo na variavel";
				}
			cout <<("\033[32mFinalizado com sucesso\033[0m\n");
			final();
		return 0;

		case 2:
			cout << "\nEscolhido 2 opção : \n";
			cout<< "\nContador inicial";
			cout<<(contador);
				for(contador = 1; contador <= 2;contador ++){ 
					system ("vcgencmd measure_temp");
					sleep (12);
				}
			cout<< "\nContador final";
			cout<<(contador);
			cout <<("\033[32mFinalizado com sucesso\033[0m\n");
			final();
		return 0;
		case 5:
			cout << "\nEscolhido 5 opção: \n";
			cout<< "\nContador inicial";
			cout<<(contador);
				for(contador = 1; contador <= 5;contador ++){ 
					system ("vcgencmd measure_temp");
					sleep (12);
				}
			cout<< "\nContador final";
			cout<<(contador);
			cout <<("\n\033[32mFinalizado com sucesso\033[0m\n");
			final();
		return 0;
		case 20:
			cout << "\n Escolhido 20 opção: \n";
			cout<< "\nContador inicial";
			cout<<(contador);
				for(contador = 1; contador <= 21;contador ++){ 
					system ("vcgencmd measure_temp");
					sleep (12);
				}
			cout<< "\nContador final";
			cout<<(contador);
			cout <<("\n\033[32mFinalizado com sucesso\033[0m\n");
			final();
		return 0;
				
	}
	
	

}

int glances(){
	system("lxterminal -e glances");
	final();
}

int htop(){
	system("lxterminal -e htop");
	final();
}

int nethogs(){
	system("lxterminal -e nethogs wlan0");
	final();
}

int main (){

	int opcao;
	system("clear");
	cout<< "\n\033[1;31mBem vindo ao iniciador 1.0!\033[0m\n";
	cout<<"---------------------------------------\n";
	cout<<"|  Escolha qual programa deseja usar: |\n";
	cout<<"|  1 Monitor de temperatura.          |\n";
	cout<<"|  2 Servidores.                      |\n";
	cout<<"|  3 Processos glances                |\n";
	cout<<"|  4 Htop                             |\n";
	cout<<"|  5 Nethos no wlan0                  |\n";
	cout<<"---------------------------------------\n";


	cin>> opcao;
	switch (opcao){
		case 1:
			temperatura();
		return 0;
		case 2:
			servidores();
		return 0;
		case 3:
			glances();
		return 0;
		case 4:
			htop();
		return 0;
		case 5:
			nethogs();
		return 0;
	}
}

