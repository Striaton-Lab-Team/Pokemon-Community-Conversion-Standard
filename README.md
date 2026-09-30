<img width="2209" height="1168" alt="pccs" src="https://github.com/user-attachments/assets/271c46a4-d2b0-49df-a54c-d70d69dd5af4" />
The Pokemon Community Conversion Standard is a C++ library designed to have a small handful of standard ways to convert a Pokemon from Generation 1 or Generation 2 to Generation 3 that are agreed upon by the community. It is by no means official, but is meant to become a standard that the community can agree on. Not every method is perfect for every situation, so there are a few options. This is meant to be a community standard, so please feel free to suggest changes and modifiations! Currently original and legal have been implemented- the other two are on their way!


### Here are the currently implemented conversion methods:

## ORIGINAL:
This method was created for the original release of Poke Transporter GB and is kept as a legacy conversion method. This mostly follows the Virtual Console method, but Mythical Pokemon have the option to be converted into their event forms in order to maintain transferrability.

| Field | Conversion |
|---|---|
| Personality Value | Creates a valid personality value based on the given gender, nature, and Unown form (if relevant) |
| Trainer ID | Copies the Trainer ID directly. Mythical Pokemon are given their event Trainer IDs if they are sanitized |
| Nickname | Nicknames are maintained. Mythical Pokemon nicknames are not overwritten (since it is techincally possible to RNG the same OT and TID) |
| Language | Language is set to match the source game. Korean Pokemon sent from Gold or Silver are set to Japanese and given their default Japanese names |
| Miscellaneous Flags | The Bad Egg, Use Egg Name, Block Box RS, and empty flags are all set to zero, while the Has Species flag is set to one |
| Trainer Nickname | The trainer nickname is maintained. Korean Pokemon from Gold and Silver are given their default Japanese trainer names |
| Markings | Markings are set to be blank |
| Species | The standard Pokemon species are maintained, and MissingNo is converted into a Porygon |
| Item | Items are removed from the Pokemon |
| EXP | Truncates the EXP down to the current level |
| PP Bonuses | PP Bonuses will be maintained |
| Friendship | Friendship is set to 70 |
| Moves | Moves that are not learnable by the Pokemon in Generation 3 are removed. A Pokemon with no moves is given the first move in their level up moveset |
| EVs | EVs are wiped |
| Contest Stats | Contest stats are set to be blank |
| Pokerus | Pokerus strain and days remaining is maintained |
| Met Location | Pokemon will be labeled as met in a fateful encounter |
| Met Level | Met level will be set to the Pokemon's current level. Mythical Pokemon will have their met level set to their event level if  sanitized |
| Game of Origin | Pokemon transferred from Red, Blue, or Yellow will have FireRed as their Game of Origin and Pokemon transferred from Gold, Silver, or Crystal will have HeartGold as their Game of Origin. Mythicals will match their event forms' Game of Origin if sanitized|
| Pokeball | All standard Pokemon will be in a Pokeball, while 'MissingNo' will be in a Masterball |
| Trainer Gender | Trainer Gender will be set as male for all games outside of Crystal. Pokemon caught in Crystal will have their correct Trainer Gender |
| IVs | IVs are set randomly, but will match the PID RNG |
| Ability | Ability is set randomly |
| Ribbons and Fateful Encounter | No ribbons are given. Event Pokemon have their Fateful Encounter flag set |
| Unown Letter | Each form of Unown will maintain their respective letter form |
| Size | Size is set randomly |
| Nature | Assigns based on the modulo of the total EXP, before being truncated |
| Shininess | Shininess is maintained. Mythical Pokemon are changed to no longer be shiny to maintain transferrability if sanitized |

## LEGAL:
This method is designed to make the transferred Pokemon indistiguishable from a completely normal Generation 3 Pokemon. This will sacrifice specific things for the peace of mind knowing that you will have no issues bringing your Pokemon to the most recent generation. Mythical Pokemon have the option to be converted into their event forms in order to maintain transferrability.

| Field | Conversion |
|---|---|
| Personality Value | Creates a valid personality value based on the given gender and Unown form (if relevant) |
| Trainer ID | Copies the Trainer ID directly. Mythical Pokemon are given their event Trainer IDs if they are sanitized |
| Nickname | Nicknames are maintained. Mythical Pokemon nicknames are not overwritten (since it is techincally possible to RNG the same OT and TID) |
| Language | Language is set to match the source game. Korean Pokemon sent from Gold or Silver are set to Japanese and given their default Japanese names |
| Miscellaneous Flags | The Bad Egg, Use Egg Name, Block Box RS, and empty flags are all set to zero, while the Has Species flag is set to one |
| Trainer Nickname | The trainer nickname is maintained. Korean Pokemon from Gold and Silver are given their default Japanese trainer names |
| Markings | Markings are set to be blank |
| Species | The standard Pokemon species are maintained, and MissingNo is converted into a Porygon |
| Item | Items are removed from the Pokemon |
| EXP | Keeps the EXP as is, unless a Pokemon is below a valid hatch level (5) or encounter level for non-hatchable Pokemon |
| PP Bonuses | PP Bonuses will be maintained |
| Friendship | Friendship is set to 70 |
| Moves | Moves that are not learnable by the Pokemon in Generation 3 are removed. A Pokemon with no moves is given the first move in their level up moveset |
| EVs | Stat Experience is converted into EVs in a method that keeps the stats as close as possible. |
| Contest Stats | Contest stats are set to be blank |
| Pokerus | Pokerus strain and days remaining is maintained |
| Met Location | Pokemon will be "Hatched from an Egg" and have their met location set to Pallet Town, unless the Pokemon cannot hatch from an Egg. In that case, they will be given the met location in which they can be caught in |
| Met Level | Met level will be set to zero, as to be read as "Hatched from an Egg". If the Pokemon is not hatchable, the met level will instead be set to the current level  |
| Game of Origin | Pokemon transferred will have FireRed as their Game of Origin. Mythicals will match their event forms' Game of Origin if sanitized|
| Pokeball | All standard Pokemon will be in a Pokeball, while 'MissingNo' will be in a Masterball |
| Trainer Gender | Trainer Gender will be set as male for all games outside of Crystal. Pokemon caught in Crystal will have their correct Trainer Gender |
| IVs | Each stat's IV will be set to twice that of the Pokemon's DV, with a chance to be increased by 1, in order to match the PID RNG |
| Ability | Ability is set randomly |
| Ribbons and Fateful Encounter | No ribbons are given. Mythical Pokemon have their Fateful Encounter flag set |
| Unown Letter | Each form of Unown will maintain their respective letter form |
| Size | Size is randomly generated |
| Nature | Assigns a random nature |
| Shininess | Shininess is maintained. Mythical Pokemon are changed to no longer be shiny to maintain transferrability if sanitized |

### The following two conversion methods are not yet implemented, but are listed for documentation:

## FAITHFUL:
This method is designed to keep as much original information about your Pokemon as possible, even if it might cause a few issues down the road. For instance, a Generation 2 Pokemon transferred with this method will have a Game of Origin of HeartGold. While this Pokemon will be legal if transferred immediately to Generation 4, it would become illegal if it recieved the Champion Ribbon beforehand. Mythical Pokemon are treated the same as all other Pokemon and not modified to match their events.

| Field | Conversion |
|---|---|
| Personality Value | Creates a valid personality value based on the given gender, nature, and Unown form (if relevant) |
| Trainer ID | Copies the Trainer ID directly. Mythical Pokemon are not treated differently |
| Nickname | Nicknames are maintained for all Pokemon |
| Language | Language is set to match the source game. Korean Pokemon sent from Gold or Silver are set to Japanese and given their default Japanese names |
| Miscellaneous Flags | The Bad Egg, Use Egg Name, Block Box RS, and empty flags are all set to zero, while the Has Species flag is set to one |
| Trainer Nickname | The trainer nickname is maintained. Korean Pokemon from Gold and Silver are given their default Japanese trainer names |
| Markings | Markings are set to be blank |
| Species | The standard Pokemon species are maintained, and MissingNo is converted into a Porygon |
| Item | Items are removed from the Pokemon |
| EXP | Keeps the EXP as is |
| PP Bonuses | PP Bonuses will be maintained |
| Friendship | Friendship is maintained |
| Moves | Moves are maintained |
| EVs | Stat Experience is converted into EVs in a method that keeps the stats as close as possible. |
| Contest Stats | Contest stats are set to be blank |
| Pokerus | Pokerus strain and days remaining is maintained |
| Met Location | Pokemon will be labeled as met in a fateful encounter |
| Met Level | Met level will be set to the Pokemon's current level |
| Game of Origin | Pokemon transferred from Red, Blue, or Yellow will have FireRed as their Game of Origin and Pokemon transferred from Gold, Silver, or Crystal will have HeartGold as their Game of Origin. Mythicals will match their event forms' Game of Origin |
| Pokeball | All standard Pokemon will be in a Pokeball, while 'MissingNo' will be in a Masterball |
| Trainer Gender | Trainer Gender will be set as male for all games outside of Crystal. Pokemon caught in Crystal will have their correct Trainer Gender |
| IVs | IVs will be doubled and set accordingly. Each IV may have one added to it in order to be compatible with the PID RNG |
| Ability | Ability is set randomly |
| Ribbons and Fateful Encounter | No ribbons are given. Mythical Pokemon have their Fateful Encounter flag set |
| Unown Letter | Each form of Unown will maintain their respective letter form |
| Size | Size is maintained for Magikarp |
| Nature | Nature is set pseudo-randomly. It will be random, but consistent each time that Pokemon is converted |
| Shininess | Shininess is maintained for all Pokemon |

## VIRTUAL:
This method replicates the conversion method used by Poke Transporter when bringing Pokemon from the Virtual Console releases of Red, Blue, Yellow, Gold, Silver, and Crystal into Pokemon Bank. Some aspects such as the GameBoy Origin Mark and hidden abilities are not carried over, due to not existing in Generation 3. Mythical Pokemon will be treated as any other Pokemon, outside of getting 5 max IVs instead of 3.

| Field | Conversion |
|---|---|
| Personality Value | Creates a valid personality value based on the given gender, nature, and Unown form (if relevant) |
| Trainer ID | Copies the Trainer ID directly. Mythical Pokemon are given their event Trainer IDs |
| Nickname | Nicknames are maintained. Mythical Pokemon nicknames are not overwritten (since it is techincally possible to RNG the same OT and TID) |
| Language | Language is set to match the source game. Korean Pokemon sent from Gold or Silver are set to Japanese and given their default Japanese names |
| Miscellaneous Flags | The Bad Egg, Use Egg Name, Block Box RS, and empty flags are all set to zero, while the Has Species flag is set to one |
| Trainer Nickname | The trainer nickname is maintained. Korean Pokemon from Gold and Silver are given their default Japanese trainer names |
| Markings | Markings are set to be blank |
| Species | The standard Pokemon species are maintained, and MissingNo is converted into a Porygon |
| Item | Items are removed from the Pokemon |
| EXP | Truncates the EXP down to the current level |
| PP Bonuses | PP Bonuses will be maintained |
| Friendship | Friendship is set to 70 |
| Moves | Moves are maintained |
| EVs | EVs are wiped |
| Contest Stats | Contest stats are set to be blank |
| Pokerus | Pokerus is removed |
| Met Location | Pokemon will be labeled as met in a fateful encounter |
| Met Level | Met level will be set to the Pokemon's current level |
| Game of Origin | Pokemon transferred from Red, Blue, or Yellow will have FireRed as their Game of Origin and Pokemon transferred from Gold, Silver, or Crystal will have HeartGold as their Game of Origin. Mythicals will match their event forms' Game of Origin |
| Pokeball | All standard Pokemon will be in a Pokeball, while 'MissingNo' will be in a Masterball |
| Trainer Gender | Trainer Gender will be set as male for all games outside of Crystal. Pokemon caught in Crystal will have their correct Trainer Gender |
| IVs | IVs will be doubled and set accordingly. Each IV may have one added to it in order to be compatible with the PID RNG |
| Ability | The ability will be set to the first ability slot |
| Ribbons and Fateful Encounter | No ribbons are given. Mythical Pokemon have their Fateful Encounter flag set |
| Unown Letter | Each form of Unown will maintain their respective letter form |
| Size | Size is set randomly |
| Nature | Assigns based on the modulo of the total EXP, before being truncated |
| Shininess | Shininess is maintained. Mythical Pokemon are changed to no longer be shiny to maintain transferrability |
