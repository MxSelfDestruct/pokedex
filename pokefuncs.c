/*
 * Pokedex
 * 
 * pokefuncs.c
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

//Defines a Pokemon
struct Pokemon {
	//Identifying info
	char name[10];
	int dex;
	int type1;
	int type2;
	
	//Stats
	int HP;
	int ATK;
	int DEF;
	int SPATK;
	int SPDEF;
	int SPD;
};

//Creates a Pokemon struct based on arguments
struct Pokemon MakePokemon(char name[10], int dex, int type1, int type2, int HP, int ATK, int DEF, int SPATK, int SPDEF, int SPD) {
	struct Pokemon target;
	
	//Identifying info
	strcpy(target.name, name);
	target.dex = dex;
	target.type1 = type1;
	target.type2 = type2;
	
	//Stats
	target.HP = HP;
	target.ATK = ATK;
	target.DEF = DEF;
	target.SPATK = SPATK;
	target.SPDEF = SPDEF;
	target.SPD = SPD;
	
	return target;
}

//Returns a string containing a Pokemon type based on a numerical ID
const char* GetPokemonType(int typeID) {
	/* For my own sanity, here's a quick guide for the IDs of all types
	 * 00: NULL (For Pokemon that don't have a second type)
	 * 01: Normal
	 * 02: Fighting
	 * 03: Flying
	 * 04: Poison
	 * 05: Ground
	 * 06: Rock
	 * 07: Bug
	 * 08: Ghost
	 * 09: Steel
	 * 10: Fire
	 * 11: Water
	 * 12: Grass
	 * 13: Electric
	 * 14: Psychic
	 * 15: Ice
	 * 16: Dragon
	 * 17: Dark
	 * 18: ??? (Used for the move Curse)
	 * 19: Bird (Used for MissingNo.)
	*/
	
	//Array containing the names of all the types
	const char *types[20] = {"NULL", "Normal", "Fighting", "Flying",
							 "Poison", "Ground", "Rock", "Bug",
							 "Ghost", "Steel", "Fire", "Water",
							 "Grass", "Electric", "Psychic", "Ice",
							 "Dragon", "Dark", "???", "Bird"};
	
	return types[typeID];
}
