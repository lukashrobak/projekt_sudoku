#pragma once

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int mapa[9][9];
int mapa0[9][9];

void hra(int typhry, int genmapa[9][9]);//hlavna funkcia hry kde sa printne mapa a zadava sa cislo a jeho pozicia
int openmap(int typhry); //funkcia na otvaranie mapy zo suboru ak sa mapa negeneruje
int savemap(); //funkcia na ukladanie mapy do suboru
void printmap(); //funkcia na printovanie mapy
void createmap(); //funkcia kde hrac vytvara mapu sam
int isSafe(int genmapa[9][9], int row, int col, int num);// kontorluje ci zadane cislo v riadku a stlpci neporusuje pravidla
void generate(int genmapa[9][9]); // vygeneruje mapu s 20 nahodne vybranymi cislami na nahodnych miestach
int solve(int genmapa[9][9], int row, int col); // doplni neuplnu alebo vygenerovanu mapu



void delay(int miliseconds) {
	clock_t start_time = clock();
	clock_t end_time = start_time + (miliseconds * CLOCKS_PER_SEC) / 1000;
	while (clock() < end_time);
}
//funkcia na printovanie textu pomalsie, vyuziva funkciu delay ktora je postavena na kniznici time.h
void print(const char text[]) {
	for (int i = 0; i < (strlen(text)); i++) {
		printf("%c", text[i]);
		//text sa pise po jednom znaku s delayom 50 milisekund
		delay(50);
	}
}
