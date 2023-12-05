
#include "projekt_sudoku.h"

int main() {
	int typhry;
	int n = 1;
	int genmapa[9][9];
	//hlavny loop celej aplikacie
	do {
		do {
			//hlavne menu kde sa vybera co sa bude robit
			system("cls");
			print("Zvol si hru:\n");
			print("0. Koniec hry\n");
			print("1. Easy\n");
			print("2. Medium\n");
			print("3. Hard\n");
			print("4. Ulozena hra\n");
			print("5. Generovat hru\n");
			print("6. Vytvor vlastnu mapu\n");
			while (scanf("%d", &typhry) != 1 || typhry < 0 || typhry>6) {
				print("Zvol cislo medzi 0 az 6!\n");
			}
		} while (openmap(typhry) == 0);
		//ak je 0 tak sa hlavny loop a tym aplikacia skonci
		if (typhry == 0) {
			n = 0;
		}
		//ak je 6 tak sa spusti funkcia na vytvaranie vlastnych map
		else if (typhry == 6) {
			createmap();
		}
		//ak je 5 tak sa generuje mapa
		else if (typhry == 5) {
			int difficulty;
			print("Zvol si obtiaznost generovanej hry od 1 do 10 kde je 1 najlahsie: ");
			while (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty>10) {
				print("Zvol cislo medzi 1 az 10!\n");
			}
			//vytvorime zaklad mapy s 20 cislami
			generate(genmapa);

			//doriesime-doplnime zaklad mapy 
			solve(genmapa, 0, 0);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					mapa[i][j] = 0;
				}
			}
			//vymazeme random cisla, pocet podla toho co zadal hrac
			for (int i = 0; i < (((11 - difficulty) * 6) + 17); i++) {
				int randomrow = rand() % 9;
				int randomcol = rand() % 9;
				mapa[randomrow][randomcol] = genmapa[randomrow][randomcol];
			}
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					mapa0[i][j] = mapa[i][j];
				}
			}
			hra(typhry, genmapa);
		}
		else {
			//vyplnime genmapu mapou aby sme vedeli ake ma byt riesenie pre kontrolu ci nie je koniec
			solve(genmapa, 0, 0);
			hra(typhry, genmapa);
		}
	} while (n == 1);
}

void hra(int typhry, int genmapa[9][9]) {
	int n = 1;
	do {
		//loop celej hry, vypise sa mapa a zadava sa lokacia a cislo, na konci kontrola ci hra nekonci
		printmap();
		char X;
		int y;
		int x;
		int zmena = 0;
		int error;
		do {
			error = 0;
			print("\nZadaj pismeno a cislo: ");
			if (scanf(" %c%d", &X, &y) == 2) {
				y--;
				if (X == 'A') { x = 0; }
				else if (X == 'B') { x = 1; }
				else if (X == 'C') { x = 2; }
				else if (X == 'D') { x = 3; }
				else if (X == 'E') { x = 4; }
				else if (X == 'F') { x = 5; }
				else if (X == 'G') { x = 6; }
				else if (X == 'H') { x = 7; }
				else if (X == 'I') { x = 8; }
				else if (X == 'S') {
					while (savemap() == 0);
					print("Saving game...");
					print("\nChces pokracovat hrat? (1-ano, 0-nie): ");
					int a;
					while (scanf(" %d", &a) != 1 || (a != 1 && a != 0)) {
						print("\nZle zadane cislo, zadaj 1 alebo 0: ");
						int c;
						while ((c = getchar()) != '\n' && c != EOF);
					}
					if (a == 1) {
						y = 1;
						x = 1;
					}
					else {
						main();
						exit(0);
					}
				}
				else {
					print("Pismeno musi byt od A po I!\n");
					error = 1;
					x = 0;
				}
				if ((y < 0) || (y > 8)) {
					print("Cislo musi byt od 1 do 9!\n");
					error = 1;
				}
				// ak sme to cislo uz mali zadane- nie je 0 v mapa0 tak sa neda zmenit (pri S je jedno ake cislo bolo zadane)
				if ((mapa0[y][x] != 0) && (X != 'S')) {
					print("Toto cislo nejde zmenit\n");
					error = 1;
				}
			}
			else {
				print("Zly format, zadaj pismeno a cislo vo formate: A1 \n");
				error = 1;
			}
			int c;
			//vymazeme string aby sme vedeli znovu zadat scanf
			while ((c = getchar()) != '\n' && c != EOF);
		} while (error == 1);
		// ak by sme chceli mapu ulozit tak sa nebudeme pytat na cislo
		if (X != 'S') {
			print("Zadaj ake tam ma byt cislo: ");
			while ((scanf("%d", &zmena) != 1) || (zmena > 9) || (zmena < 0)) {
				print("Cislo musi byt od 1 do 9!\n");
				print("Zadaj ake tam ma byt cislo: ");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
			//kontrola zadaneho cisla funkciou isSafe
			if (isSafe(mapa, y, x, zmena) || zmena == 0) {
				mapa[y][x] = zmena;
			}
			else {
				print("Cislo porusuje pravidla, skus znova...\n");
			}
		}
		//kontrola ci sa hra nekonci - mapa sa porovnava s vyplnenou genmapou
		int e = 1;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (mapa[i][j] == genmapa[i][j]) {
					e *= 1;
				}
				else {
					e *= 2;
				}
			}
		}
		n = 0;
		if (e == 1) {
			n = 1;
		}
	} while (n == 0);
	printmap();
	print("\nVyhral si!...");
	delay(500);
}

//funkcia na vytvorenie vlastnej mapy, zadavaju sa cisla do cistej mapy, podobny loop ako vo funkcii hra
void createmap() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mapa[i][j] = 0;
		}

	}
	int n = 1;
	do {
		printmap();
		char X;
		int y;
		int x;
		int zmena = 0;
		int error;
		do {
			error = 0;
			print("\nZadaj pismeno a cislo: ");
			if (scanf(" %c%d", &X, &y) == 2) {
				y--;
				if (X == 'A') { x = 0; }
				else if (X == 'B') { x = 1; }
				else if (X == 'C') { x = 2; }
				else if (X == 'D') { x = 3; }
				else if (X == 'E') { x = 4; }
				else if (X == 'F') { x = 5; }
				else if (X == 'G') { x = 6; }
				else if (X == 'H') { x = 7; }
				else if (X == 'I') { x = 8; }
				else if (X == 'S') {
					while (savemap() == 0);
					print("Saving game...");
					print("\nChces pokracovat hrat? (1-ano, 0-nie): ");
					int a;
					while (scanf(" %d", &a) != 1 || (a != 1 && a != 0)) {
						print("\nZle zadane cislo, zadaj 1 alebo 0: ");
						int c;
						while ((c = getchar()) != '\n' && c != EOF);
					}
					if (a == 1) {
						y = 1;
						x = 1;
					}
					else {
						main();
						exit(0);
					}
				}
				else {
					print("Pismeno musi byt od A po I!\n");
					error = 1;
					x = 0;
				}
				if ((y < 0) || (y > 8)) {
					print("Cislo musi byt od 1 do 9!\n");
					error = 1;
				}
				// ak sme to cislo uz mali zadane- nie je 0 v mapa0 tak sa neda zmenit (pri S je jedno ake cislo bolo zadane)
				if ((mapa0[y][x] != 0) && (X != 'S')) {
					print("Toto cislo nejde zmenit\n");
					error = 1;
				}
			}
			else {
				print("Zly format, zadaj pismeno a cislo vo formate: A1 \n");
				error = 1;
			}
			int c;
			//vymazeme string aby sme vedeli znovu zadat scanf
			while ((c = getchar()) != '\n' && c != EOF);
		} while (error == 1);
		// ak by sme chceli mapu ulozit tak sa nebudeme pytat na cislo
		if (X != 'S') {
			print("Zadaj ake tam ma byt cislo: ");
			while ((scanf("%d", &zmena) != 1) || (zmena > 9) || (zmena < 0)) {
				print("Cislo musi byt od 1 do 9!\n");
				print("Zadaj ake tam ma byt cislo: ");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
			//kontrola ci zadane cislo neporusuje pravidla, nemozeme vytvarat mapu ktora sa neda hrat
			if (isSafe(mapa, y, x, zmena) || zmena == 0) {
				mapa[y][x] = zmena;
			}
			else {
				print("Cislo porusuje pravidla, skus znova...\n");
			}
		}
	} while (n == 1);
}

int openmap(int typhry) {
	FILE* fptr;
	int smap = 0;//chceme si ulozit ci sa otvorila mapa z ulozenych map
	//switch aku mapu treba zo suboru otvorit
	switch (typhry) {
	case 1:fptr = fopen("mapa1.txt", "r");
		break;
	case 2:fptr = fopen("mapa2.txt", "r");
		break;
	case 3:fptr = fopen("mapa3.txt", "r");
		break;
	case 4:print("Zvol ktoru ulozenu hru (1 az 5): ");
		int slot;
		smap = 1;
		while (scanf("%d", &slot) != 1 || 1 > slot || slot > 5) {
			print("\nZvol cislo medzi 1 az 5: ");
		}
		switch (slot) {
		case 1:fptr = fopen("savedmap1.txt", "r");
			break;
		case 2:fptr = fopen("savedmap2.txt", "r");
			break;
		case 3:fptr = fopen("savedmap3.txt", "r");
			break;
		case 4:fptr = fopen("savedmap4.txt", "r");
			break;
		case 5:fptr = fopen("savedmap5.txt", "r");
			break;
		}
		break;
	default: return 1;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf(fptr, "%d", &mapa[i][j]);
		}
	}
	//ak je y 1 tak sa mapa otvorila z ulozenych map, musime si urcit mapa0 zo suboru aby sme vedeli menit zadane hodnoty
	if (smap == 1) {
		for (int i = 9; i < 18; i++) {
			for (int j = 0; j < 9; j++) {
				fscanf(fptr, "%d", &mapa0[i - 9][j]);
			}
		}
	}
	else {
		//skopirujeme mapu na mapu0 aby sme ich vedeli porovnavat a urcit co bolo zadane hracom (co sa stale da zmenit)
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				mapa0[i][j] = mapa[i][j];
			}
		}
	}
	fclose(fptr);

	// kontrola ci je mapa prazdna
	int k = 1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (mapa[i][j] != 0) {
				k *= 2;
			}
		}
	}
	if (k == 1) {
		print("Tato mapa je prazdna...");
		delay(300);
		return 0;
	}
	return 1;
}
// funkcia na ukladanie mapy pocas hry
int savemap() {
	print("Vyber slot ulozenia (1 az 5): ");
	int slot;
	scanf("%d", &slot);
	while (slot < 1 && slot>5) {
		print("\nZvol cislo medzi 1 az 5!\n");
		print("Vyber slot ulozenia (1 az 5): ");
		scanf("%d", &slot);
	}
	FILE* fptr;
	// vybera sa 1 z 5 slotov na ulozenie
	switch (slot) {
	case 1:fptr = fopen("savedmap1.txt", "w");
		break;
	case 2:fptr = fopen("savedmap2.txt", "w");
		break;
	case 3:fptr = fopen("savedmap3.txt", "w");
		break;
	case 4:fptr = fopen("savedmap4.txt", "w");
		break;
	case 5:fptr = fopen("savedmap5.txt", "w");
		break;
	default:return 0;
	}
	if (fptr == NULL) {
		print("Problem s otvorenim suboru, skus znova...");
		return 0;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf(fptr, "%d ", mapa[i][j]);
		}
		fprintf(fptr, "\n");
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf(fptr, "%d ", mapa0[i][j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	return 1;
}
void printmap() {
	system("cls");//vymaze obrazovku
	printf("\033[22;2mPre ulozenie hry zadaj: S0 \033[0m\n\n");//zada text v tmavo sedej farbe
	printf("    A B C   D E F   G H I\n\n");
	for (int i = 0; i < 9; i++) {
		// ak je i 3 alebo 6 tak sa najprv vypisu ciarky
		if ((i == 3) or (i == 6)) {
			printf("    ---------------------\n");
		}
		printf("%d   ", (i + 1));
		for (int j = 0; j < 9; j++) {
			if ((j == 3) or (j == 6)) {
				printf("| ");
			}
			//v subore je ulozena 0 ale chceme aby sa nevypisalo nic-medzera
			if (mapa[i][j] == 0) {
				printf("  ");
			}
			else {
				// ak bolo cislo zadane hracom - v mapa0 bolo 0 tak sa vypise farebne
				if (mapa0[i][j] == 0) {
					printf("\033[22;96m%d \033[0m", mapa[i][j]);
				}
				else {
					printf("%d ", mapa[i][j]);
				}
			}
		}
		printf("\n");
	}
}

int isSafe(int genmapa[9][9], int row, int col, int num) {
	//kontrola ci sa uz zadane cislo nenachaza v riadku
	for (int i = 0; i < 9; i++) {
		if (genmapa[row][i] == num) {
			return 0;
		}
	}
	//kontrola ci sa uz zadane cislo nenachaza v stlpci
	for (int i = 0; i < 9; i++) {
		if (genmapa[i][col] == num) {
			return 0;
		}
	}
	//kontrola ci sa uz zadane cislo nenachaza v 3x3 kocke
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (genmapa[i][j] == num) {
				return 0;
			}
		}
	}
	return 1;
}

void generate(int genmapa[9][9]) {
	srand(time(NULL));//musime pouzit pred funkciou rand na vygenerovanie cisel podla casu

	//vyplni 9x9 nulami
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			genmapa[i][j] = 0;
		}
	}

	//na random pozicie i a j vyplni 20 random cisel od 1 do 9
	for (int i = 0; i < 20; i++) {
		int randx, randi, randj = 1;
		do {
			randx = rand() % 9 + 1;
			randi = rand() % 8;
			randj = rand() % 8;
		} while (isSafe(genmapa, randi, randj, randx) == 0);
		genmapa[randi][randj] = randx;
	}
}
int solve(int genmapa[9][9], int row, int col) {
	// kontrola ci nie sme v 8 riadku a 9 stlpci - koniec
	if (row == 8 && col == 9) {
		return 1;
	}
	//  kontorla ci niesme len v 9 stlpci - novy riadok
	if (col == 9)
	{
		row++;
		col = 0;
	}

	// kontrola ci uz nie je v tom mieste zadane nejake cislo, ak ano tak sa posunieme o stlpec dalej
	if (genmapa[row][col] > 0) {
		return solve(genmapa, row, col + 1);
	}
	for (int num = 1; num <= 9; num++)
	{
		// isSafe kontroluje ci cislo neporusuje pravidla- ci uz sa nenachadza v stplci alebo riadku
		if (isSafe(genmapa, row, col, num) == 1) {
			genmapa[row][col] = num;

			//  kontorola dalsieho stlpca- to iste od zaciatku
			if (solve(genmapa, row, col + 1) == 1) {
				return 1;
			}
		}

		// vymazeme zadane cislo lebo porusuje pravidla, skusi o 1 vacsie cislo
		genmapa[row][col] = 0;
	}
	return 0;
}

