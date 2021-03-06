	@ Does nothing.
	.macro nop
	.byte 0x00
	.endm

	@ Does nothing.
	.macro nop1
	.byte 0x01
	.endm

	@ Terminates script execution.
	.macro end
	.byte 0x02
	.endm

	@ Jumps back to after the last-executed call statement, and continues script execution from there.
	.macro return
	.byte 0x03
	.endm

	@ Jumps to destination and continues script execution from there. The location of the calling script is remembered and can be returned to later.
	.macro call destination
	.byte 0x04
	.4byte \destination
	.endm

	@ Jumps to destination and continues script execution from there.
	.macro goto destination
	.byte 0x05
	.4byte \destination
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), jumps to destination and continues script execution from there.
	.macro goto_if condition, destination
	.byte 0x06
	.byte \condition
	.4byte \destination
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), calls destination.
	.macro call_if condition, destination
	.byte 0x07
	.byte \condition
	.4byte \destination
	.endm

	@ Jumps to the standard function at index function.
	.macro gotostd function
	.byte 0x08
	.byte \function
	.endm

	@ Calls the standard function at index function.
	.macro callstd function
	.byte 0x09
	.byte \function
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), jumps to the standard function at index function.
	.macro gotostd_if condition, function
	.byte 0x0a
	.byte \condition
	.byte \function
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), calls the standard function at index function.
	.macro callstd_if condition, function
	.byte 0x0b
	.byte \condition
	.byte \function
	.endm

	@ Executes a script stored in a default RAM location.
	.macro gotoram
	.byte 0x0c
	.endm

	@ Terminates script execution and "resets the script RAM".
	.macro killscript
	.byte 0x0d
	.endm

	@ Sets mystery event status
	.macro setmysteryeventstatus value
	.byte 0x0e
	.byte \value
	.endm

	@ Sets the specified script bank to immediate value.
	.macro loadword destination, value
	.byte 0x0f
	.byte \destination
	.4byte \value
	.endm

	@ Sets the specified script bank to immediate value.
	.macro loadbyte destination, value
	.byte 0x10
	.byte \destination
	.byte \value
	.endm

	@ Sets the byte at offset to value.
	.macro writebytetoaddr value, offset
	.byte 0x11
	.byte \value
	.4byte \offset
	.endm

	@ Copies the byte value at source into the specified script bank.
	.macro loadbytefromaddr destination, source
	.byte 0x12
	.byte \destination
	.4byte \source
	.endm

	@ Not sure. Judging from XSE's description I think it takes the least-significant byte in bank source and writes it to destination.
	.macro setptrbyte source, destination
	.byte 0x13
	.byte \source
	.4byte \destination
	.endm

	@ Copies the contents of bank source into bank destination.
	.macro copylocal destination, source
	.byte 0x14
	.byte \destination
	.byte \source
	.endm

	@ Copies the byte at source to destination, replacing whatever byte was previously there.
	.macro copybyte destination, source
	.byte 0x15
	.4byte \destination
	.4byte \source
	.endm

	@ Changes the value of destination to value.
	.macro setvar destination, value
	.byte 0x16
	.2byte \destination
	.2byte \value
	.endm

	@ Changes the value of destination by adding value to it. Overflow is not prevented (0xFFFF + 1 = 0x0000).
	.macro addvar destination, value
	.byte 0x17
	.2byte \destination
	.2byte \value
	.endm

	@ Changes the value of destination by subtracting value to it. Overflow is not prevented (0x0000 - 1 = 0xFFFF).
	.macro subvar destination, value
	.byte 0x18
	.2byte \destination
	.2byte \value
	.endm

	@ Copies the value of source into destination.
	.macro copyvar destination, source
	.byte 0x19
	.2byte \destination
	.2byte \source
	.endm

	@ If source is not a variable, then this function acts like setvar. Otherwise, it acts like copyvar.
	.macro setorcopyvar destination, source
	.byte 0x1a
	.2byte \destination
	.2byte \source
	.endm

	@ Compares the values of script banks a and b, after forcing the values to bytes.
	.macro compare_local_to_local byte1, byte2
	.byte 0x1b
	.byte \byte1
	.byte \byte2
	.endm

	@ Compares the least-significant byte of the value of script bank a to a fixed byte value (b).
	.macro compare_local_to_value a, b
	.byte 0x1c
	.byte \a
	.byte \b
	.endm

	@ Compares the least-significant byte of the value of script bank a to the byte located at offset b.
	.macro compare_local_to_addr a, b
	.byte 0x1d
	.byte \a
	.4byte \b
	.endm

	@ Compares the byte located at offset a to the least-significant byte of the value of script bank b.
	.macro compare_addr_to_local a, b
	.byte 0x1e
	.4byte \a
	.byte \b
	.endm

	@ Compares the byte located at offset a to a fixed byte value (b).
	.macro compare_addr_to_value a, b
	.byte 0x1f
	.4byte \a
	.byte \b
	.endm

	@ Compares the byte located at offset a to the byte located at offset b.
	.macro compare_addr_to_addr a, b
	.byte 0x20
	.4byte \a
	.4byte \b
	.endm

	@ Compares the value of `var` to a fixed word value (b).
	.macro compare_var_to_value var, value
	.byte 0x21
	.2byte \var
	.2byte \value
	.endm

	@ Compares the value of `var` to the value of `var2`.
	.macro compare_var_to_var var1, var2
	.byte 0x22
	.2byte \var1
	.2byte \var2
	.endm

	@ Generic compare macro which attempts to deduce argument types based on their values
	@ Any values between 0x4000 to 0x4FFF and 0x8000 to 0x8FFF are considered event variable identifiers
	.macro compare arg1, arg2
		.if ((\arg1 >> 12) == 4 || (\arg1 >> 12) == 8) && ((\arg2 >> 12) == 4 || (\arg2 >> 12) == 8)
			compare_var_to_var \arg1, \arg2
		.elseif ((\arg1 >> 12) == 4 || (\arg1 >> 12) == 8) && (\arg2 >= 0 && \arg2 <= 0xFFFF)
			compare_var_to_value \arg1, \arg2
		.else
			.error "Invalid arguments for 'compare'"
		.endif
	.endm

	@ Calls the native C function stored at `func`.
	.macro callnative func
	.byte 0x23
	.4byte \func
	.endm

	@ Replaces the script with the function stored at `func`. Execution returns to the bytecode script when func returns TRUE.
	.macro gotonative func
	.byte 0x24
	.4byte \func
	.endm

	@ Calls a special function; that is, a piece of ASM code designed for use by scripts and listed in a table of pointers.
	.macro special function
	.byte 0x25
	.2byte SPECIAL_\function
	.endm

	@ Calls a special function. That function's output (if any) will be written to the variable you specify.
	.macro specialvar output, function
	.byte 0x26
	.2byte \output
	.2byte SPECIAL_\function
	.endm

	@ Blocks script execution until a command or ASM code manually unblocks it. Generally used with specific commands and specials. If this command runs, and a subsequent command or piece of ASM does not unblock state, the script will remain blocked indefinitely (essentially a hang).
	.macro waitstate
	.byte 0x27
	.endm

	@ Blocks script execution for time (frames? milliseconds?).
	.macro delay time
	.byte 0x28
	.2byte \time
	.endm

	@ Sets a to 1.
	.macro setflag a
	.byte 0x29
	.2byte \a
	.endm

	@ Sets a to 0.
	.macro clearflag a
	.byte 0x2a
	.2byte \a
	.endm

	@ Compares a to 1.
	.macro checkflag a
	.byte 0x2b
	.2byte \a
	.endm

	@ In FireRed, this command is a nop.
	.macro initclock hour minute
	.byte 0x2c
	.byte \hour
	.byte \minute
	.endm

	@ In FireRed, this command is a nop.
	.macro dodailyevents
	.byte 0x2d
	.endm

	@ Resets the values of variables 0x8000, 0x8001, and 0x8002. Related to RTC in RSE?
	.macro gettime
	.byte 0x2e
	.endm

	@ Plays the specified (sound_number) sound. Only one sound may play at a time, with newer ones interrupting older ones.
	.macro playse sound_number
	.byte 0x2f
	.2byte \sound_number
	.endm

	@ Blocks script execution until the currently-playing sound (triggered by sound) finishes playing.
	.macro waitse
	.byte 0x30
	.endm

	@ Plays the specified (fanfare_number) fanfare.
	.macro playfanfare fanfare_number
	.byte 0x31
	.2byte \fanfare_number
	.endm

	@ Blocks script execution until all currently-playing fanfares finish.
	.macro waitfanfare
	.byte 0x32
	.endm

	@ Plays the specified (song_number) song. The byte is apparently supposed to be 0x00.
	.macro playbgm song_number, unknown
	.byte 0x33
	.2byte \song_number
	.byte \unknown
	.endm

	@ Plays the specified (song_number) song.
	.macro savebgm song_number
	.byte 0x34
	.2byte \song_number
	.endm

	@ Crossfades the currently-playing song into the map's default song.
	.macro fadedefaultbgm
	.byte 0x35
	.endm

	@ Crossfades the currently-playng song into the specified (song_number) song.
	.macro fadenewbgm song_number
	.byte 0x36
	.2byte \song_number
	.endm

	@ Fades out the currently-playing song.
	.macro fadeoutbgm speed
	.byte 0x37
	.byte \speed
	.endm

	@ Fades the currently-playing song back in.
	.macro fadeinbgm speed
	.byte 0x38
	.byte \speed
	.endm

	@ Sends the player to Warp warp on Map bank.map. If the specified warp is 0xFF, then the player will instead be sent to (X, Y) on the map.
	.macro warp map, warp, X, Y
	.byte 0x39
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Clone of warp that does not play a sound effect.
	.macro warpsilent map, warp, X, Y
	.byte 0x3a
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Clone of warp that uses "a walking effect".
	.macro warpdoor map, warp, X, Y
	.byte 0x3b
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Warps the player to another map using a hole animation.
	.macro warphole map
	.byte 0x3c
	map \map
	.endm

	@ Clone of warp that uses a teleport effect. It is apparently only used in R/S/E.[source]
	.macro warpteleport map, warp, X, Y
	.byte 0x3d
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Clone of warp. Used by an (unused?) Safari Zone script to return the player to the gatehouse and end the Safari Game.
	.macro setwarp map, warp, X, Y
	.byte 0x3e
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Sets a default warp place. If a warp tries to send the player to Warp 127 on Map 127.127, they will instead be sent here. Useful when a map has warps that need to go to script-controlled locations (i.e. elevators).
	.macro setdynamicwarp map, warp, X, Y
	.byte 0x3f
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Clone of warp3, except that this writes data to different offsets...
	.macro setdivewarp map, warp, X, Y
	.byte 0x40
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Clone of warp3, except that this writes data to different offsets...
	.macro setholewarp map, warp, X, Y
	.byte 0x41
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Retrieves the player's zero-indexed X- and Y-coordinates in the map, and stores them in the specified variables.
	.macro getplayerxy X, Y
	.byte 0x42
	.2byte \X
	.2byte \Y
	.endm

	@ Retrieves the number of Pokmon in the player's party, and stores that number in variable 0x800D (LASTRESULT).
	.macro countpokemon
	.byte 0x43
	.endm

	@ Attempts to add quantity of item index to the player's Bag. If the player has enough room, the item will be added and variable 0x800D (LASTRESULT) will be set to 0x0001; otherwise, LASTRESULT is set to 0x0000.
	.macro additem index, quantity
	.byte 0x44
	.2byte \index
	.2byte \quantity
	.endm

	@ Removes quantity of item index from the player's Bag.
	.macro removeitem index, quantity
	.byte 0x45
	.2byte \index
	.2byte \quantity
	.endm

	@ Checks if the player has enough space in their Bag to hold quantity more of item index. Sets variable 0x800D (LASTRESULT) to 0x0001 if there is room, or 0x0000 is there is no room.
	.macro checkitemspace index, quantity
	.byte 0x46
	.2byte \index
	.2byte \quantity
	.endm

	@ Checks if the player has quantity or more of item index in their Bag. Sets variable 0x800D (LASTRESULT) to 0x0001 if the player has enough of the item, or 0x0000 if they have fewer than quantity of the item.
	.macro checkitem index, quantity
	.byte 0x47
	.2byte \index
	.2byte \quantity
	.endm

	@ Checks which Bag pocket the specified (index) item belongs in, and writes the value to variable 0x800D (LASTRESULT). This script is used to show the name of the proper Bag pocket when the player receives an item via callstd (simplified to giveitem in XSE).
	.macro checkitemtype index
	.byte 0x48
	.2byte \index
	.endm

	@ Adds a quantity amount of item index to the player's PC. Both arguments can be variables.
	.macro addpcitem index, quantity
	.byte 0x49
	.2byte \index
	.2byte \quantity
	.endm

	@ Checks for quantity amount of item index in the player's PC. Both arguments can be variables.
	.macro checkpcitem index, quantity
	.byte 0x4a
	.2byte \index
	.2byte \quantity
	.endm

	@ In FireRed, this command is a nop. (The argument is read, but not used for anything.)
	.macro adddecor a
	.byte 0x4b
	.2byte \a
	.endm

	@ In FireRed, this command is a nop. (The argument is read, but not used for anything.)
	.macro removedecor a
	.byte 0x4c
	.2byte \a
	.endm

	@ In FireRed, this command is a nop. (The argument is read, but not used for anything.)
	.macro hasdecor a
	.byte 0x4d
	.2byte \a
	.endm

	@ In FireRed, this command is a nop. (The argument is read, but not used for anything.)
	.macro checkdecor a
	.byte 0x4e
	.2byte \a
	.endm

	@ Applies the movement data at movements to the specified (index) Person event. Also closes any standard message boxes that are still open.
	@ This command in fact uses variables to access the Person event ID. So, for example, if you setvar 0x8000 to 0x3, and then use applymovementpos 0x8000 @move1, Person event 3 will have the movements at @move1 applied to them. Thank you Shiny Quagsire for bringing this to my attention.
	.macro applymovement index, movements, mapGroup, mapNum
		.ifb \mapGroup
			.byte 0x4f
			.2byte \index
			.4byte \movements
		.else
			.byte 0x50
			.2byte \index
			.4byte \movements
			.byte \mapGroup
			.byte \mapNum
		.endif
	.endm

	@ Blocks script execution until the movements being applied to the specified (index) Person event finish. If the specified Person event is 0x0000, then the command will block script execution until all Person events affected by applymovement finish their movements. If the specified Person event is not currently being manipulated with applymovement, then this command does nothing.
	.macro waitmovement index, mapBank, mapNum
		.ifb \mapBank
			.byte 0x51
			.2byte \index
		.else
			.byte 0x52
			.2byte \index
			.byte \mapBank
			.byte \mapNum
		.endif
	.endm

	@ Attempts to hide the specified (local_ID, a local ID) Person event on the specified map, by setting its visibility flag if it has a valid one. If the Person does not have a valid visibility flag, this command does nothing.
	@ If no map is specified, then the current map is used
	.macro removeobject localId, mapGroup, mapNum
		.ifb \mapGroup
			.byte 0x53
			.2byte \localId
		.else
			.byte 0x54
			.2byte \localId
			.byte \mapGroup
			.byte \mapNum
		.endif
	.endm

	.macro addobject localId, mapGroup, mapNum
		.ifb \mapGroup
			.byte 0x55
			.2byte \localId
		.else
			.byte 0x56
			.2byte \localId
			.byte \mapGroup
			.byte \mapNum
		.endif
	.endm

	.macro setobjectxy word1, word2, word3
		.byte 0x57
		.2byte \word1
		.2byte \word2
		.2byte \word3
	.endm

	.macro showobject word, byte1, byte2
		.byte 0x58
		.2byte \word
		.byte \byte1
		.byte \byte2
	.endm

	.macro hideobject word, byte1, byte2
		.byte 0x59
		.2byte \word
		.byte \byte1
		.byte \byte2
	.endm

	@ If the script was called by a Person event, then that Person will turn to face toward the tile that the player is stepping off of.
	.macro faceplayer
		.byte 0x5a
	.endm

	.macro turnobject word, byte
		.byte 0x5b
		.2byte \word
		.byte \byte
	.endm

	@ If the Trainer flag for Trainer index is not set, this command does absolutely nothing.
	.macro trainerbattle type, trainer, word, pointer1, pointer2, pointer3, pointer4
		.byte 0x5c
		.byte \type
		.2byte \trainer
		.2byte \word
		.if \type == 0
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
		.elseif \type == 1
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ event script
		.elseif \type == 2
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ event script
		.elseif \type == 3
			.4byte \pointer1 @ text
		.elseif \type == 4
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
		.elseif \type == 5
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
		.elseif \type == 6
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
			.4byte \pointer4 @ event script
		.elseif \type == 7
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
		.elseif \type == 8
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
			.4byte \pointer4 @ event script
		.endif
	.endm


	@ Starts a trainer battle using the battle information stored in RAM (usually by trainerbattle, which actually calls this command behind-the-scenes), and blocks script execution until the battle finishes.
	.macro battlebegin
	.byte 0x5d
	.endm

	.macro ontrainerbattleend
	.byte 0x5e
	.endm

	.macro ontrainerbattleendgoto
	.byte 0x5f
	.endm

	@ Compares Flag (trainer + 0x500) to 1. (If the flag is set, then the trainer has been defeated by the player.)
	.macro checktrainerflag trainer
	.byte 0x60
	.2byte \trainer
	.endm

	@ Sets Flag (trainer + 0x500). (I didn't make a mistake. The command names actually are backwards.)
	.macro settrainerflag trainer
	.byte 0x61
	.2byte \trainer
	.endm

	@ Clears Flag (trainer + 0x500). (I didn't make a mistake. The command names actually are backwards.)
	.macro cleartrainerflag trainer
	.byte 0x62
	.2byte \trainer
	.endm

	.macro setobjectxyperm word1, word2, word3
	.byte 0x63
	.2byte \word1
	.2byte \word2
	.2byte \word3
	.endm

	.macro moveobjectoffscreen word
	.byte 0x64
	.2byte \word
	.endm

	.macro setobjectmovementtype word, byte
	.byte 0x65
	.2byte \word
	.byte \byte
	.endm

	@ If a standard message box (or its text) is being drawn on-screen, this command blocks script execution until the box and its text have been fully drawn.
	.macro waitmessage
	.byte 0x66
	.endm

	@ Starts displaying a standard message box containing the specified text. If text is a pointer, then the string at that offset will be loaded and used. If text is script bank 0, then the value of script bank 0 will be treated as a pointer to the text. (You can use loadpointer to place a string pointer in a script bank.)
	.macro message text
	.byte 0x67
	.4byte \text
	.endm

	@ Holds the current message box open until the player presses a key. The message box is then closed.
	.macro closemessage
	.byte 0x68
	.endm

	@ Ceases movement for all OWs on-screen.
	.macro lockall
	.byte 0x69
	.endm

	@ If the script was called by a Person event, then that Person's movement will cease.
	.macro lock
	.byte 0x6a
	.endm

	@ Resumes normal movement for all OWs on-screen, and closes any standard message boxes that are still open.
	.macro releaseall
	.byte 0x6b
	.endm

	@ If the script was called by a Person event, then that Person's movement will resume. This command also closes any standard message boxes that are still open.
	.macro release
	.byte 0x6c
	.endm

	@ Blocks script execution until the player presses any key.
	.macro waitbutton
	.byte 0x6d
	.endm

	@ Displays a YES/NO multichoice box at the specified coordinates, and blocks script execution until the user makes a selection. Their selection is stored in variable 0x800D (LASTRESULT); 0x0000 for "NO" or if the user pressed B, and 0x0001 for "YES".
	.macro yesnobox X, Y
	.byte 0x6e
	.byte \X
	.byte \Y
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made. Lists of options are predefined and the one to be used is specified with list. If B is set to a non-zero value, then the user will not be allowed to back out of the multichoice with the B button.
	.macro multichoice X, Y, list, B
	.byte 0x6f
	.byte \X
	.byte \Y
	.byte \list
	.byte \B
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made. Lists of options are predefined and the one to be used is specified with list. The default argument determines the initial position of the cursor when the box is first opened; it is zero-indexed, and if it is too large, it is treated as 0x00. If B is set to a non-zero value, then the user will not be allowed to back out of the multichoice with the B button.
	.macro multichoicedefault X, Y, list, default, B
	.byte 0x70
	.byte \X
	.byte \Y
	.byte \list
	.byte \default
	.byte \B
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made. Lists of options are predefined and the one to be used is specified with list. The per_row argument determines how many list items will be shown on a single row of the box.
	.macro multichoicegrid X, Y, list, per_row, B
	.byte 0x71
	.byte \X
	.byte \Y
	.byte \list
	.byte \per_row
	.byte \B
	.endm

	.macro drawbox byte1, byte2, byte3, byte4
	.byte 0x72
	.byte \byte1
	.byte \byte2
	.byte \byte3
	.byte \byte4
	.endm

	.macro erasebox byte1, byte2, byte3, byte4
	.byte 0x73
	.byte \byte1
	.byte \byte2
	.byte \byte3
	.byte \byte4
	.endm

	.macro drawboxtext byte1, byte2, byte3, byte4
	.byte 0x74
	.byte \byte1
	.byte \byte2
	.byte \byte3
	.byte \byte4
	.endm

	@ Displays a box containing the front sprite for the specified (species) Pokmon species.
	.macro drawpokepic species, X, Y
	.byte 0x75
	.2byte \species
	.byte \X
	.byte \Y
	.endm

	@ Hides all boxes displayed with showpokepic.
	.macro erasepokepic
	.byte 0x76
	.endm

	@ In FireRed, this command is a nop. (The argument is discarded.)
	.macro drawcontestwinner a
	.byte 0x77
	.byte \a
	.endm

	@ Displays the string at pointer as braille text in a standard message box. The string must be formatted to use braille characters.
	.macro braillemessage text
	.byte 0x78
	.4byte \text
	.endm

	@ Gives the player one of the specified (species) Pokmon at level level holding item. The unknown arguments should all be zeroes.
	.macro givepoke species, level, item, unknown1, unknown2, unknown3
	.byte 0x79
	.2byte \species
	.byte \level
	.2byte \item
	.4byte \unknown1
	.4byte \unknown2
	.byte \unknown3
	.endm

	.macro giveegg word
	.byte 0x7a
	.2byte \word
	.endm

	.macro setpokemove byte1, byte2, word
	.byte 0x7b
	.byte \byte1
	.byte \byte2
	.2byte \word
	.endm

	@ Checks if at least one Pokmon in the player's party knows the specified (index) attack. If so, variable 0x800D (LASTRESULT) is set to the (zero-indexed) slot number of the Pokmon that knows the move. If not, LASTRESULT is set to 0x0006.
	.macro checkpokemove index
	.byte 0x7c
	.2byte \index
	.endm

	@ Writes the name of the Pokmon at index species to the specified buffer.
	.macro getspeciesname out, species
	.byte 0x7d
	.byte \out
	.2byte \species
	.endm

	@ Writes the name of the first Pokmon in the player's party to the specified buffer.
	.macro getfirstpartypokename out
	.byte 0x7e
	.byte \out
	.endm

	@ Writes the name of the Pokmon in slot slot (zero-indexed) of the player's party to the specified buffer. If an empty or invalid slot is specified, ten spaces ("") are written to the buffer.
	.macro getpartypokename out, slot
	.byte 0x7f
	.byte \out
	.2byte \slot
	.endm

	@ Writes the name of the item at index item to the specified buffer. If the specified index is larger than the number of items in the game (0x176), the name of item 0 ("????????") is buffered instead.
	.macro getitemname out, item
	.byte 0x80
	.byte \out
	.2byte \item
	.endm

	@ In FireRed, this command is a nop. (The first argument is discarded immediately. The second argument is read, but not used for anything.)
	.macro getdecorname a, b
	.byte 0x81
	.byte \a
	.2byte \b
	.endm

	@ Writes the name of the attack at index attack to the specified buffer.
	.macro getmovename out, attack
	.byte 0x82
	.byte \out
	.2byte \attack
	.endm

	@ Converts the value of input to a decimal string, and writes that string to the specified buffer.
	.macro getnumberstring out, input
	.byte 0x83
	.byte \out
	.2byte \input
	.endm

	@ Writes the standard string identified by index to the specified buffer. Specifying an invalid standard string (e.x. 0x2B) can and usually will cause data corruption (I've observed destruction of the stored player name and crashes when entering/exiting certain menu screens).
	.macro getstdstring out, index
	.byte 0x84
	.byte \out
	.2byte \index
	.endm

	@ Copies the string at offset to the specified buffer.
	.macro getstring out, offset
	.byte 0x85
	.byte \out
	.4byte \offset
	.endm

	@ Opens the Pokemart system, offering the specified products for sale.
	.macro pokemart products
	.byte 0x86
	.4byte \products
	.endm

	@ Apparent clone of pokemart.
	.macro pokemartdecor products
	.byte 0x87
	.4byte \products
	.endm

	@ Apparent clone of pokemart.
	.macro pokemartbp products
	.byte 0x88
	.4byte \products
	.endm

	.macro playslotmachine word
	.byte 0x89
	.2byte \word
	.endm

	@ In FireRed, this command is a nop.
	.macro plantberrytree byte1, byte2, byte3
	.byte 0x8a
	.byte \byte1, \byte2, \byte3
	.endm

	@ In FireRed, this command sets the byte at 0x03000EA8 to 0x01. I do not know what that means.
	.macro choosecontestpkmn
	.byte 0x8b
	.endm

	@ In FireRed, this command is a nop.
	.macro startcontest
	.byte 0x8c
	.endm

	@ In FireRed, this command is a nop.
	.macro showcontestresults
	.byte 0x8d
	.endm

	@ In FireRed, this command is a nop.
	.macro contestlinktransfer
	.byte 0x8e
	.endm

	@ Stores a random integer between 0 and limit in variable 0x800D (LASTRESULT).
	.macro random limit
	.byte 0x8f
	.2byte \limit
	.endm

	@ If check is 0x00, this command adds value to the player's money.
	.macro givemoney value, check
	.byte 0x90
	.4byte \value
	.byte \check
	.endm

	@ If check is 0x00, this command subtracts value from the player's money.
	.macro takemoney value, check
	.byte 0x91
	.4byte \value
	.byte \check
	.endm

	@ If check is 0x00, this command will check if the player has value or more money; script variable 0x800D (LASTRESULT) is set to 0x0001 if the player has enough money, or 0x0000 if the do not.
	.macro checkmoney value, check
	.byte 0x92
	.4byte \value
	.byte \check
	.endm

	@ Spawns a secondary box showing how much money the player has.
	.macro showmoneybox X, Y
	.byte 0x93
	.byte \X
	.byte \Y
	.endm

	@ Hides the secondary box spawned by showmoney.
	.macro hidemoneybox X, Y
	.byte 0x94
	.byte \X
	.byte \Y
	.endm

	@ Updates the secondary box spawned by showmoney. (What does it do with its arguments?)
	.macro updatemoneybox X, Y
	.byte 0x95
	.byte \X
	.byte \Y
	.endm

	@ In FireRed, this command is a nop.
	.macro getpricereduction word
	.byte 0x96
	.2byte \word
	.endm

	@ Fades the screen to black or back, using the specified effect. Effect 0x00 fades in, and effect 0x01 fades out. I don't know if other effects exist.
	.macro fadescreen effect
	.byte 0x97
	.byte \effect
	.endm

	.macro fadescreendelay byte1, byte2
	.byte 0x98
	.byte \byte1
	.byte \byte2
	.endm

	.macro setdarklevel word
	.byte 0x99
	.2byte \word
	.endm

	.macro animdarklevel byte
	.byte 0x9a
	.byte \byte
	.endm

	.macro messageautoscroll pointer
	.byte 0x9b
	.4byte \pointer
	.endm

	@ Executes the specified field move animation.
	.macro dofieldeffect animation
	.byte 0x9c
	.2byte \animation
	.endm

	@ Tells the game which party Pokmon to use for the next field move animation.
	.macro setfieldeffect animation, slot
	.byte 0x9d
	.byte \animation
	.2byte \slot
	.endm

	@ Blocks script execution until all playing field move animations complete.
	.macro waitfieldeffect animation
	.byte 0x9e
	.2byte \animation
	.endm

	@ Sets which healing place the player will return to if all of the Pokmon in their party faint. A list of available healing places can be found on PokeCommunity.
	.macro sethealplace flightspot
	.byte 0x9f
	.2byte \flightspot
	.endm

	@ Checks the player's gender. If male, then 0x0000 is stored in variable 0x800D (LASTRESULT). If female, then 0x0001 is stored in LASTRESULT.
	.macro checkplayergender
	.byte 0xa0
	.endm

	@ Plays the specified (species) Pokmon's cry. You can use waitcry to block script execution until the sound finishes.
	.macro playpokecry species, effect
	.byte 0xa1
	.2byte \species
	.2byte \effect
	.endm

	@ Changes the tile at (X, Y) on the current map.
	.macro setmaptile X, Y, tile_number, tile_attrib
	.byte 0xa2
	.2byte \X
	.2byte \Y
	.2byte \tile_number
	.2byte \tile_attrib
	.endm

	@ Queues a weather change to the default weather for the map.
	.macro resetweather
	.byte 0xa3
	.endm

	@ Queues a weather change to type weather.
	.macro setweather type
	.byte 0xa4
	.2byte \type
	.endm

	@ Executes the weather change queued with resetweather or setweather. The current weather will smoothly fade into the queued weather.
	.macro doweather
	.byte 0xa5
	.endm

	@ This command manages cases in which maps have tiles that change state when stepped on (specifically, cracked/breakable floors).
	.macro tileeffect subroutine
	.byte 0xa6
	.byte \subroutine
	.endm

	.macro setmaplayoutindex word
	.byte 0xa7
	.2byte \word
	.endm

	.macro setobjectpriority word, byte1, byte2, byte3
	.byte 0xa8
	.2byte \word
	.byte \byte1
	.byte \byte2
	.byte \byte3
	.endm

	.macro resetobjectpriority word, byte1, byte2
	.byte 0xa9
	.2byte \word
	.byte \byte1
	.byte \byte2
	.endm

	.macro createvobject byte1, byte2, word1, word2, byte3, byte4
	.byte 0xaa
	.byte \byte1
	.byte \byte2
	.2byte \word1
	.2byte \word2
	.byte \byte3
	.byte \byte4
	.endm

	.macro turnvobject byte1, byte2
	.byte 0xab
	.byte \byte1
	.byte \byte2
	.endm

	@ Queues the opening of the door tile at (X, Y) with an animation.
	.macro opendoor X, Y
	.byte 0xac
	.2byte \X
	.2byte \Y
	.endm

	@ Queues the closing of the door tile at (X, Y) with an animation.
	.macro closedoor X, Y
	.byte 0xad
	.2byte \X
	.2byte \Y
	.endm

	@ Executes the state changes queued with setdooropened, setdoorclosed, setdooropened2, and setdoorclosed2.
	.macro waitdooranim
	.byte 0xae
	.endm

	@ Queues the opening of the door tile at (X, Y) without an animation.
	.macro setdooropen X, Y
	.byte 0xaf
	.2byte \X
	.2byte \Y
	.endm

	@ Queues the closing of the door tile at (X, Y) without an animation.
	.macro setdoorclosed X, Y
	.byte 0xb0
	.2byte \X
	.2byte \Y
	.endm

	@ In FireRed, this command is a nop.
	.macro addelevmenuitem
	.byte 0xb1
	.endm

	@ In FireRed, this command is a nop.
	.macro showelevmenu
	.byte 0xb2
	.endm

	.macro checkcoins word
	.byte 0xb3
	.2byte \word
	.endm

	.macro givecoins word
	.byte 0xb4
	.2byte \word
	.endm

	.macro takecoins word
	.byte 0xb5
	.2byte \word
	.endm

	@ Prepares to start a wild battle against a species at Level level holding item. Running this command will not affect normal wild battles. You start the prepared battle with dowildbattle.
	.macro setwildbattle species, level, item
	.byte 0xb6
	.2byte \species
	.byte \level
	.2byte \item
	.endm

	@ Starts a wild battle against the Pokmon generated by setwildbattle. Blocks script execution until the battle finishes.
	.macro dowildbattle
	.byte 0xb7
	.endm

	.macro setvaddress long, word
	.byte 0xb8
	.4byte \long
	.2byte \word
	.endm

	.macro vgoto pointer
	.byte 0xb9
	.4byte \pointer
	.endm

	.macro vcall pointer
	.byte 0xba
	.4byte \pointer
	.endm

	.macro vgoto_if byte, pointer
	.byte 0xbb
	.byte \byte
	.4byte \pointer
	.endm

	.macro vcall_if byte, pointer
	.byte 0xbc
	.byte \byte
	.4byte \pointer
	.endm

	.macro vmessage pointer
	.byte 0xbd
	.4byte \pointer
	.endm

	.macro vloadword pointer
	.byte 0xbe
	.4byte \pointer
	.endm

	.macro vgetstring byte, pointer
	.byte 0xbf
	.byte \byte
	.4byte \pointer
	.endm

	@ Spawns a secondary box showing how many Coins the player has.
	.macro showcoinsbox X, Y
	.byte 0xc0
	.byte \X
	.byte \Y
	.endm

	@ Hides the secondary box spawned by showcoins. It doesn't appear to use its arguments, but they are still required.
	.macro hidecoinsbox X, Y
	.byte 0xc1
	.byte \X
	.byte \Y
	.endm

	@ Updates the secondary box spawned by showcoins. (What does it do with its arguments?)
	.macro updatecoinsbox X, Y
	.byte 0xc2
	.byte \X
	.byte \Y
	.endm

	@ Increases the value of the specified hidden variable by 1. The hidden variable's value will not be allowed to exceed 0x00FFFFFF.
	.macro incrementgamestat a
	.byte 0xc3
	.byte \a
	.endm

	@ Clone of warp... Except that it doesn't appear to have any effect when used in some of FireRed's default level scripts. (If it did, Berry Forest would be impossible to enter...)
	.macro setescapewarp map, warp, X, Y
	.byte 0xc4
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Blocks script execution until cry finishes.
	.macro waitpokecry
	.byte 0xc5
	.endm

	@ Writes the name of the specified (box) PC box to the specified buffer.
	.macro bufferboxname out, box
	.byte 0xc6
	.byte \out
	.2byte \box
	.endm

	@ Sets the color of the text in standard message boxes. 0x00 produces blue (male) text, 0x01 produces red (female) text, 0xFF resets the color to the default for the current OW's gender, and all other values produce black text.
	.macro textcolor color
	.byte 0xc7
	.byte \color
	.endm

	@ The exact purpose of this command is unknown, but it is related to the blue help-text box that appears on the bottom of the screen when the Main Menu is opened.
	.macro loadhelp pointer
	.byte 0xc8
	.4byte \pointer
	.endm

	@ The exact purpose of this command is unknown, but it is related to the blue help-text box that appears on the bottom of the screen when the Main Menu is opened.
	.macro unloadhelp
	.byte 0xc9
	.endm

	@ After using this command, all standard message boxes will use the signpost frame.
	.macro signmsg
	.byte 0xca
	.endm

	@ Ends the effects of signmsg, returning message box frames to normal.
	.macro normalmsg
	.byte 0xcb
	.endm

	@ Compares the value of a hidden variable to a dword.
	.macro comparehiddenvar a, value
	.byte 0xcc
	.byte \a
	.4byte \value
	.endm

	@ Makes the Pokmon in the specified slot of the player's party obedient. It will not randomly disobey orders in battle.
	.macro setobedience slot
	.byte 0xcd
	.2byte \slot
	.endm

	@ Checks if the Pokmon in the specified slot of the player's party is obedient. If the Pokmon is disobedient, 0x0001 is written to script variable 0x800D (LASTRESULT). If the Pokmon is obedient (or if the specified slot is empty or invalid), 0x0000 is written.
	.macro checkobedience slot
	.byte 0xce
	.2byte \slot
	.endm

	@ Depending on factors I haven't managed to understand yet, this command may cause script execution to jump to the offset specified by the pointer at 0x020370A4.
	.macro execram
	.byte 0xcf
	.endm

	@ Sets worldmapflag to 1. This allows the player to Fly to the corresponding map, if that map has a flightspot.
	.macro setworldflag worldmapflag
	.byte 0xd0
	.2byte \worldmapflag
	.endm

	@ Clone of warpteleport? It is apparently only used in FR/LG, and only with specials.[source]
	.macro warpteleport2 map, warp, X, Y
	.byte 0xd1
	map \map
	.byte \warp
	.2byte \X
	.2byte \Y
	.endm

	@ Changes the location where the player caught the Pokmon in the specified slot of their party. A list of valid catch locations can be found on PokeCommunity.
	.macro setcatchlocale slot, location
	.byte 0xd2
	.2byte \slot
	.byte \location
	.endm

	.macro event_d3 unknown
	.byte 0xd3
	.2byte \unknown
	.endm

	.macro event_d4
	.byte 0xd4
	.endm

	@ In FireRed, this command is a nop.
	.macro event_d5 var
	.byte 0xd5
	.2byte \var
	.endm

	.macro event_d6
	.byte 0xd6
	.endm

	.macro warp7 map, byte, word1, word2
	.byte 0xd7
	map \map
	.byte \byte
	.2byte \word1
	.2byte \word2
	.endm

	.macro event_d8
	.byte 0xd8
	.endm

	.macro event_d9
	.byte 0xd9
	.endm

	.macro hidebox2
	.byte 0xda
	.endm

	.macro message3 pointer
	.byte 0xdb
	.4byte \pointer
	.endm

	.macro fadescreen3 byte
	.byte 0xdc
	.byte \byte
	.endm

	.macro buffertrainerclass byte, word
	.byte 0xdd
	.byte \byte
	.2byte \word
	.endm

	.macro buffertrainername byte, word
	.byte 0xde
	.byte \byte
	.2byte \word
	.endm

	.macro pokenavcall pointer
	.byte 0xdf
	.4byte \pointer
	.endm

	.macro warp8 map, byte, word1, word2
	.byte 0xe0
	map \map
	.byte \byte
	.2byte \word1
	.2byte \word2
	.endm

	.macro buffercontesttype byte, word
	.byte 0xe1
	.byte \byte
	.2byte \word
	.endm

	@ Writes the name of the specified (item) item to the specified buffer. If the specified item is a Berry (0x85 - 0xAE) or Poke Ball (0x4) and if the quantity is 2 or more, the buffered string will be pluralized ("IES" or "S" appended). If the specified item is the Enigma Berry, I have no idea what this command does (but testing showed no pluralization). If the specified index is larger than the number of items in the game (0x176), the name of item 0 ("????????") is buffered instead.
	.macro storeitems out, item, quantity
	.byte 0xe2
	.byte \out
	.2byte \item
	.2byte \quantity
	.endm


@ Supplementary

	.macro goto_if_eq dest
	goto_if 1, \dest
	.endm

	.macro switch var
	copyvar 0x8000, \var
	.endm

	.macro case condition, dest
	compare_var_to_value 0x8000, \condition
	goto_if_eq \dest
	.endm

	.macro msgbox text, type=4
	loadword 0, \text
	callstd \type
	.endm

	@ Message box types
	MSGBOX_YESNO = 5

	YES = 1
	NO  = 0

	.macro giveitem item, amount=1, function=0
	setorcopyvar 0x8000, \item
	setorcopyvar 0x8001, \amount
	callstd \function
	.endm

	.macro givedecoration decoration
	setorcopyvar 0x8000, \decoration
	callstd 7
	.endm
