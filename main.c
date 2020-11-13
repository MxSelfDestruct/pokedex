/*
 * Pokedex
 * 
 * main.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processing.c"
#include "pokefuncs.c"
#include "displayfuncs.c"

int main() {
	//Initialize the buffer and blank it out, for safety
	char Buffer[1024];
	
	//Blank out Buffer, for safety
	ClearBuffer(Buffer);
	
	int TotalPokemon = 0;
		
	//Try to open pokedex.db
	FILE * PokedexDB = fopen("pokedex.db", "r");
	
	//If we can't find the file, quit
	if (PokedexDB == NULL) {
		printf("Couldn't open pokedex.db! Exiting... \n");
		return 1;
	}
	
	//Gets the number of Pokemon in PokedexDB
	while (fgets(Buffer, sizeof(Buffer), PokedexDB) != NULL) {
		//Ignore comments and empty lines
		if (Buffer[0] == '#' || Buffer[0] == '\n') {
			continue;
		}
		
		//Detects if we hit a new Pokemon entry
		if (strcmp(Buffer, "pokemon:\n") == 0) {
			TotalPokemon++;
		}
	}
	
	//Create an array to store all the Pokemon in the Pokedex.
	//Call it the Pokedex for thematic reasons
	struct Pokemon Pokedex[TotalPokemon];
	
	//Rewind the database
	rewind(PokedexDB);
	
	//Get data for all the Pokemon in PokedexDB
	
	int Pos = 0;
	while (fgets(Buffer, sizeof(Buffer), PokedexDB) != NULL) {	
		//Ignore comments and empty lines
		if (Buffer[0] == '#' || Buffer[0] == '\n') {
			continue;
		}
		
		//Detects if we hit a new Pokemon entry
		if (strcmp(Buffer, "pokemon:\n") == 0) {
			//Get ready to make a new Pokemon struct
			//Use this to appease sscanf
						
			//Identifying info
			char name[10] = "";
			int dexid = 0;
			int type1 = 0;
			int type2 = 0;
			
			//Stats
			int HP = 0;
			int ATK = 0;
			int DEF = 0;
			int SPATK = 0;
			int SPDEF = 0;
			int SPD = 0;
			
			//Read in the next line to get the Pokemon's name
			fgets(Buffer, sizeof(Buffer), PokedexDB);
			//Get the name from quotation marks and strcpy it to name
			strcpy(name, GetTextFromQuotes(Buffer));
			
			dexid = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			type1 = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			type2 = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			
			HP = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			ATK = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			DEF = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPATK = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPDEF = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPD = ReadIntStat(fgets(Buffer, sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
						
			Pokedex[Pos] = MakePokemon(name, dexid, type1, type2,
									   HP, ATK, DEF,
									   SPATK, SPDEF, SPD);
			Pos++;
		}
	}
	
	fclose(PokedexDB);
	
	for (int i = 0; i < sizeof(Pokedex) / sizeof(Pokedex[0]); i++) {
		ShowInfo(Pokedex[i]);
		ShowStats(Pokedex[i]);
	}
	
	
	return 0;
}
