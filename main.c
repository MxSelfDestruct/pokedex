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
#include <string.h>
#include "pokefuncs.c"
#include "displayfuncs.c"

int main() {
	//Create an array to store the different Pokemon - the Pokedex
	struct Pokemon Pokedex[4];
	
	//Create Placeholder Pokemon - MissingNo.!
	Pokedex[0] = MakePokemon("MissingNo.", 0, 1, 19, 33, 136, 0, 6, 6, 29);
	
	//Create Bulbasaur
	Pokedex[1] = MakePokemon("Bulbasaur", 1, 12, 4, 45, 49, 49, 65, 65, 45);
	
	//Create Charmander
	Pokedex[2] = MakePokemon("Charmander", 4, 10, 0, 39, 52, 43, 60, 50, 65);
								  
	//Create Squirtle
	Pokedex[3] = MakePokemon("Squirtle", 7, 11, 0, 44, 48, 65, 50, 64, 43);
	
	//Display all the Pokemon in the Pokedex (Except MissingNo.)
	for (int i = 0; i < sizeof(Pokedex) / sizeof(Pokedex[0]); i++) {
		ShowInfo(Pokedex[i]);
		ShowStats(Pokedex[i]);
	}
	
	return 0;
}
