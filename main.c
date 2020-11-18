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

int main(int argc, char *argv[]) {
	//See if we have at least one argument
	
	//If we do, continue as normal.
	if (argc == 2) {
		;
	}
	
	//If we have no args, quit out.	
	else {
		printf("No arguments given! (Expected exactly 1 argument.)\n");
		printf("Exiting...\n");
		return 1;
	}
	
	//Initialize a buffer and blank it out, for safety
	char Buffer[1024];
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
			//Identifying info
			char name[10] = "";
			ClearBuffer(name);
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
			
			//Pokedex blurb
			char info[512] = "";
			ClearBuffer(info);
			
			//Read in the next line to get the Pokemon's name
			fgets(Buffer, sizeof(Buffer), PokedexDB);
			//Get the name from quotation marks and strcpy it to name
			strcpy(name, GetTextFromQuotes(Buffer));
			
			//Get numerical identifying info
			dexid = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			type1 = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			type2 = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			
			//Get the numerical stats
			HP = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			ATK = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			DEF = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPATK = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPDEF = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			SPD = ReadIntStat(fgets(Buffer,
			sizeof(Buffer), PokedexDB));
			ClearBuffer(Buffer);
			
			//Get Pokedex blurb
			fgets(Buffer, sizeof(Buffer), PokedexDB);
			//Get the blurb from quotation marks and strcpy it to info
			strcpy(info, GetTextFromQuotes(Buffer));
			ClearBuffer(Buffer);
						
			Pokedex[Pos] = MakePokemon(name, dexid, type1, type2,
									   HP, ATK, DEF,
									   SPATK, SPDEF, SPD, info);
			Pos++;
		}
	}
	
	fclose(PokedexDB);
	
	//Figure out if the user gave us a name or a dexID
		
	//IMPORTANT: THIS NEEDS TO BE IMPROVED. IT WILL FAIL IF THE USER
	//ENTERS "0" (MissingNo.'s ID) OR ENTERS A NAME WITH A NUMBER IN IT
	//(Ex. Porygon2)
	//Most likely, the oversight is in the GetIntFromString() function.
	
	//If GetIntFromString(argv[1]) evaluates to zero, assume it's a
	//Pokemon's name
	if (GetIntFromString(argv[1]) == 0) {	
		for (int i = 0; i < sizeof(Pokedex) / sizeof(Pokedex[0]); i++) {
			if (strcmp(Pokedex[i].name, argv[1]) == 0) {
				ShowInfo(Pokedex[i]);
				ShowStats(Pokedex[i]);
				ShowBlurb(Pokedex[i]);
				
				return 0;
			}
		}
			
		//If there wasn't a Pokemon with that name, print this and exit
		printf("No information for Pokemon \"%s.\"\n", argv[1]);
		printf("Did you remember to capitalize it?\n");	
	}
	
	//Otherwise, assume it's a dexid.
	else {
		//Compute this once and store it in Target to save time
		int Target = GetIntFromString(argv[1]);
		printf("%d\n", Target);
		for (int i = 0; i < sizeof(Pokedex) / sizeof(Pokedex[0]); i++) {
			if (Pokedex[i].dex == Target) {
				ShowInfo(Pokedex[i]);
				ShowStats(Pokedex[i]);
				ShowBlurb(Pokedex[i]);
				
				return 0;
			}
		}

		//If there wasn't a Pokemon with that dexid, print this and exit
		printf("No information for Pokemon with id \"%s.\"\n", argv[1]);
	}

	return 1;
}
