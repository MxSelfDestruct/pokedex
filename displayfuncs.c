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
void ShowInfo(struct Pokemon target) {
	printf("Pokemon name: \t%s \n", target.name);
	printf("Pokedex ID: \t%d \n", target.dex);
	
	//Check if the Pokemon has two types. If not, only print type1.
	if (target.type2 == 0) {
		printf("Type: \t\t%s \n", GetPokemonType(target.type1));
	}
	
	//If it does, print both.
	else {
		printf("Types: \t\t%s, %s \n", GetPokemonType(target.type1),
				GetPokemonType(target.type2));
	}
}

//Show a Pokemon's stats
void ShowStats(struct Pokemon target) {
	printf("HP: \t\t%d\n", target.HP);
	printf("Attack: \t%d\n", target.ATK);
	printf("Defense: \t%d\n", target.DEF);
	printf("Sp. Attack: \t%d\n", target.SPATK);
	printf("Sp. Defense: \t%d\n", target.SPDEF);
	printf("Speed: \t\t%d\n", target.SPD);
	printf("\n");
}
