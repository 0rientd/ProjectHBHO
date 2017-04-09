#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <time.h>

int main () {
	
	//////////////////////////////////////////
	
	gfxInitDefault(); // 3ds.h | inicia a tela
	
	PrintConsole TelaDeCima, TelaDeBaixo; //3ds.h | Aqui você escolhe o nome das variaveis para setar onde quer printar algo na tela

	consoleInit ( GFX_TOP, &TelaDeCima ); // Iniciando a tela de cima
	consoleInit ( GFX_BOTTOM, &TelaDeBaixo ); // Iniciando a tela de baixo
	
	int count = 0;

	srand ( time ( NULL ) );
	
	int button = 0;
	int num_random = rand() % 5;
	if ( num_random == 0 ) {
		
		num_random++;
		
	}
	
	consoleSelect ( &TelaDeCima ); // Selecionando tela de baixo
	
	//////////////////////////////////////////
	
	while ( aptMainLoop() ) { // Loop do sistena para manter scan

		time_t unixTime = time(NULL); // pegando a hora do sistema a cada frame ( 30 fps )
		struct tm* Horario = gmtime ( ( const time_t * ) &unixTime ); // declarando estrutura da hora do sistema para uma variavel 
	
		int Horas = Horario -> tm_hour; // variavel para horas
		int Minutos = Horario -> tm_min; // varaivel para minutos
	
		printf ("Bem vindo ao ProjectHBHO do HackerOrientado\n");
		printf ("Hora atual -> %02i:%02i\n\n", Horas, Minutos);

		printf ("Pressione START para voltar ao HBL\n\n");
		
		printf ("Jogo do adivinha\n");
		printf ("Aperte A, B, X ou Y para ver se e o numero que \nestou pensando\n");
		printf ("\x1b[0;0H"); // reseta o ponteiro para o inicio da tela 0x0
		
		gfxFlushBuffers(); // limpa o buffer da tela selecionada
		gfxSwapBuffers(); // troca os buffers da tela selecionada
		
		gspWaitForVBlank(); // ainda não sei kkkkkk
	
		hidScanInput(); // Scan de entrada dos botoes
		
		u32 kDown = hidKeysDown(); // u32 = variavel inteira sem ser assinada ( sempre positiva ) recebe paramentro de "pressionar"
		
		if ( kDown & KEY_A ) {
			
			button = 1;
			
			count++;

		} 
		
		if ( kDown & KEY_B ) {
			
			button = 2;

			count++;

		} 
		
		if ( kDown & KEY_X ) {
			
			button = 3;

			count++;
			
		}
		
		if ( kDown & KEY_Y ) {
			
			button = 4;

			count++;
			
		}
		
		if ( kDown & KEY_START ) {
			
			break;
			
			gfxFlushBuffers();
			gfxSwapBuffers();
			
			gspWaitForVBlank();
			
		}

		if ( kDown & KEY_SELECT ) {

			return main();

		}
		
		if ( button == num_random ) {
			
			consoleSelect ( &TelaDeBaixo );
			
			printf ("\x1b[0;0H");

			printf ("Parabens!! voce acertou!!\n");
			printf ("Tentativas = %d\n\n", count);

			printf ("Para reiniciar o jogo, aperte 'Select'\n");
			
			consoleSelect ( &TelaDeCima );
			
		}
		
	}
	
	gfxExit();
	return 0;
	
}