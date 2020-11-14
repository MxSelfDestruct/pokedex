/*
 * Pokedex
 * 
 * displayfuncs.c
 * 
 * Copyright 2020 Nat Hofelt <nat@2darkpark.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

//Show a Pokemon's identifying information
void ShowInfo(struct Pokemon Input) {
	printf("Pokemon name: \t%s \n", Input.name);
	printf("Pokedex ID: \t%d \n", Input.dex);
	
	//Check if the Pokemon has two types. If not, only print type1.
	if (Input.type2 == 0) {
		printf("Type: \t\t%s \n", GetPokemonType(Input.type1));
	}
	
	//If it does, print both.
	else {
		printf("Types: \t\t%s, %s \n", GetPokemonType(Input.type1),
				GetPokemonType(Input.type2));
	}
}

//Show a Pokemon's stats
void ShowStats(struct Pokemon Input) {
	printf("HP: \t\t%d\n", Input.HP);
	printf("Attack: \t%d\n", Input.ATK);
	printf("Defense: \t%d\n", Input.DEF);
	printf("Sp. Attack: \t%d\n", Input.SPATK);
	printf("Sp. Defense: \t%d\n", Input.SPDEF);
	printf("Speed: \t\t%d\n", Input.SPD);
}

//Show a Pokemon's Pokedex blurb
void ShowBlurb(struct Pokemon Input) {
	//Tells this function when to put in a linebreak
	int CharsRead = 0;
	
	//Prints out the blurb char by char
	for (int i = 0; i < strlen(Input.info); i++) {
		putchar(Input.info[i]);
		CharsRead++;
		
		//After we print 60 chars, start looking for spaces
		//Once we find one, insert a linebreak.
		if (CharsRead >= 60) {
			if (Input.info[i] == ' ') {
				putchar('\n');
				CharsRead = 0;
			}
		}
	}
	putchar('\n');
	putchar('\n');
}
