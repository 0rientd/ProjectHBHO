// v0.0.1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <3ds.h>

int main() {
	
	gfxInitDefault(); // inicia framebuffer LCD com o padrão GSP_BGR8_OES

	PrintConsole top_screen, bottom_screen; // Atribui às variaveis um padrão de dados sobre o uso do print na tela e retorna um ponteiro do consoleGetDefault()
	consoleInit ( GFX_TOP, &top_screen ); // Iniciando a tela de cima
	consoleInit ( GFX_BOTTOM, &bottom_screen ); // Iniciando a tela de baixo

	consoleSelect(&top_screen);
	
	int count = 0;

	srand(time(NULL));
	
	int button = 0;
	int num_random = rand() % 5;
	if ( num_random == 0 ) {
		
		num_random++;
		
	}

	static SwkbdState teclado;
	static char texto_do_teclado[60];
	SwkbdButton vButtonKB = SWKBD_BUTTON_NONE;

	swkbdInit(&teclado, SWKBD_TYPE_NORMAL, 1, -3);
	swkbdSetInitialText(&teclado, texto_do_teclado);
	swkbdSetHintText(&teclado, "Please enter your name");
	vButtonKB = swkbdInputText(&teclado, texto_do_teclado, sizeof(texto_do_teclado));
	
	while ( aptMainLoop() ) { // Loop do sistena para manter scan

		time_t unixTime = time(NULL); // pegando a hora do sistema a cada frame ( 30 fps )
		struct tm* Horario = gmtime ( ( const time_t * ) &unixTime ); // declarando estrutura da hora do sistema para uma variavel 
	
		int Horas = Horario -> tm_hour; // variavel para horas
		int Minutos = Horario -> tm_min; // varaivel para minutos
		int Segundos = Horario -> tm_sec; // variavel para segundos
	
		u32 kDown = hidKeysDown(); /// unsigned int 32 bit

		if ( vButtonKB == SWKBD_BUTTON_NONE ) {

			return main();

		}

		printf ("Seja bem vindo %s ao ProjectHBHO do HackerOrientado\n", texto_do_teclado);
		printf ("Hora atual -> %02i:%02i:%02i\n\n", Horas, Minutos, Segundos);

		printf ("Pressione START para voltar ao HBL\n\n");
		
		printf ("Jogo do adivinha\n");
		printf ("Aperte A, B, X ou Y para ver se e o numero que \nestou pensando\n");
		printf ("\x1b[0;0H"); // reseta o ponteiro para o inicio da tela 0x0
		
		gfxFlushBuffers(); // limpa o buffer da tela selecionada
		gfxSwapBuffers(); // troca os buffers da tela selecionada
		
		gspWaitForVBlank();
	
		hidScanInput(); // Scan de entrada dos botoes
		
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
			
			consoleSelect(&bottom_screen);
			
			printf ("\x1b[0;0H");

			printf ("Parabens!! voce acertou!!\n");
			printf ("Tentativas = %d\n\n", count);

			printf ("Para reiniciar o jogo, aperte 'Select'\n");
			
			consoleSelect(&top_screen);
			
		}
		
	}
	
	gfxFlushBuffers();
	gfxSwapBuffers();
			
	gspWaitForVBlank();

	gfxExit();
	return 0;
	
}