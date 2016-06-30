Route119_MapScripts:: @ 8151167
	map_script 5, Route119_MapScript1_151172
	map_script 3, Route119_MapScript1_15119B
	.byte 0

Route119_MapScript1_151172:: @ 8151172
	checkflag 2145
	callif 1, Route119_EventScript_15117C
	end

Route119_EventScript_15117C:: @ 815117C
	compare 0x8004, 6
	callif 1, Route119_EventScript_151193
	compare 0x8004, 7
	callif 1, Route119_EventScript_151197
	return

Route119_EventScript_151193:: @ 8151193
	disappear 35
	return

Route119_EventScript_151197:: @ 8151197
	disappear 36
	return

Route119_MapScript1_15119B:: @ 815119B
	call Route119_EventScript_1A014E
	call Route119_EventScript_1A0172
	call Route119_EventScript_1A0196
	compare 0x40b3, 1
	callif 1, Route119_EventScript_1511B9
	special 324
	end

Route119_EventScript_1511B9:: @ 81511B9
	setflag 893
	clearflag 892
	setvar 0x40b3, 2
	return

Route119_EventScript_1511C5:: @ 81511C5
	setvar 0x4001, 1
	jump Route119_EventScript_1511DB
	end

Route119_EventScript_1511D0:: @ 81511D0
	setvar 0x4001, 2
	jump Route119_EventScript_1511DB
	end

Route119_EventScript_1511DB:: @ 81511DB
	lockall
	reappear 25
	checkgender
	compare RESULT, 0
	callif 1, Route119_EventScript_151254
	compare RESULT, 1
	callif 1, Route119_EventScript_151259
	pause 65
	compare 0x4001, 1
	callif 1, Route119_EventScript_1513A6
	compare 0x4001, 2
	callif 1, Route119_EventScript_1513B1
	move 255, Route119_Movement_1A0845
	waitmove 0
	pause 30
	compare 0x4001, 1
	callif 1, Route119_EventScript_1513D2
	compare 0x4001, 2
	callif 1, Route119_EventScript_1513E1
	disappear 25
	reappear 16
	pause 30
	checkgender
	compare RESULT, 0
	jumpeq Route119_EventScript_15125E
	compare RESULT, 1
	jumpeq Route119_EventScript_1512D8
	releaseall
	end

Route119_EventScript_151254:: @ 8151254
	playmusic 415, 1
	return

Route119_EventScript_151259:: @ 8151259
	playmusic 421, 1
	return

Route119_EventScript_15125E:: @ 815125E
	msgbox Route119_Text_1710BB, 4
	switch 0x4023
	case 0, Route119_EventScript_15128D
	case 1, Route119_EventScript_15129D
	case 2, Route119_EventScript_1512AD
	end

Route119_EventScript_15128D:: @ 815128D
	trainerbattle 3, 534, 0, Route119_Text_171156
	jump Route119_EventScript_1512BD
	end

Route119_EventScript_15129D:: @ 815129D
	trainerbattle 3, 537, 0, Route119_Text_171156
	jump Route119_EventScript_1512BD
	end

Route119_EventScript_1512AD:: @ 81512AD
	trainerbattle 3, 531, 0, Route119_Text_171156
	jump Route119_EventScript_1512BD
	end

Route119_EventScript_1512BD:: @ 81512BD
	msgbox Route119_Text_1711B1, 4
	call Route119_EventScript_151352
	msgbox Route119_Text_171214, 4
	jump Route119_EventScript_151362
	end

Route119_EventScript_1512D8:: @ 81512D8
	msgbox Route119_Text_171358, 4
	switch 0x4023
	case 0, Route119_EventScript_151307
	case 1, Route119_EventScript_151317
	case 2, Route119_EventScript_151327
	end

Route119_EventScript_151307:: @ 8151307
	trainerbattle 3, 525, 0, Route119_Text_1713E2
	jump Route119_EventScript_151337
	end

Route119_EventScript_151317:: @ 8151317
	trainerbattle 3, 528, 0, Route119_Text_1713E2
	jump Route119_EventScript_151337
	end

Route119_EventScript_151327:: @ 8151327
	trainerbattle 3, 522, 0, Route119_Text_1713E2
	jump Route119_EventScript_151337
	end

Route119_EventScript_151337:: @ 8151337
	msgbox Route119_Text_17140B, 4
	call Route119_EventScript_151352
	msgbox Route119_Text_171475, 4
	jump Route119_EventScript_151362
	end

Route119_EventScript_151352:: @ 8151352
	giveitem ITEM_HM02
	setflag 110
	return

Route119_EventScript_151362:: @ 8151362
	closebutton
	compare 0x4001, 1
	callif 1, Route119_EventScript_1513D2
	compare 0x4001, 2
	callif 1, Route119_EventScript_1513E1
	disappear 16
	reappear 25
	pause 30
	compare 0x4001, 1
	callif 1, Route119_EventScript_1513BC
	compare 0x4001, 2
	callif 1, Route119_EventScript_1513C7
	disappear 25
	setvar 0x4072, 1
	playmusicbattle 0
	fadedefault
	releaseall
	end

Route119_EventScript_1513A6:: @ 81513A6
	move 25, Route119_Movement_1513F0
	waitmove 0
	return

Route119_EventScript_1513B1:: @ 81513B1
	move 25, Route119_Movement_1513FA
	waitmove 0
	return

Route119_EventScript_1513BC:: @ 81513BC
	move 25, Route119_Movement_151405
	waitmove 0
	return

Route119_EventScript_1513C7:: @ 81513C7
	move 25, Route119_Movement_15140F
	waitmove 0
	return

Route119_EventScript_1513D2:: @ 81513D2
	movespriteperm 16, 25, 32
	movespriteperm 25, 25, 32
	return

Route119_EventScript_1513E1:: @ 81513E1
	movespriteperm 16, 26, 32
	movespriteperm 25, 26, 32
	return

Route119_Movement_1513F0:: @ 81513F0
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_16
	step_end

Route119_Movement_1513FA:: @ 81513FA
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_18
	step_16
	step_end

Route119_Movement_151405:: @ 8151405
	step_18
	step_16
	step_16
	step_16
	step_18
	step_16
	step_16
	step_16
	step_16
	step_end

Route119_Movement_15140F:: @ 815140F
	step_17
	step_16
	step_16
	step_16
	step_18
	step_18
	step_16
	step_16
	step_16
	step_16
	step_end

Route119_EventScript_15141A:: @ 815141A
	msgbox Route119_Text_171698, 2
	end

Route119_EventScript_151423:: @ 8151423
	msgbox Route119_Text_171749, 3
	end

Route119_EventScript_15142C:: @ 815142C
	msgbox Route119_Text_171762, 3
	end

Route119_EventScript_151435:: @ 8151435
	trainerbattle 0, 223, 0, Route119_Text_1BE521, Route119_Text_1BE54F
	msgbox Route119_Text_1BE561, 6
	end

Route119_EventScript_15144C:: @ 815144C
	trainerbattle 0, 224, 0, Route119_Text_1BE5A4, Route119_Text_1BE5DF
	msgbox Route119_Text_1BE5F8, 6
	end

Route119_EventScript_151463:: @ 8151463
	trainerbattle 0, 225, 0, Route119_Text_1BE632, Route119_Text_1BE67B
	msgbox Route119_Text_1BE695, 6
	end

Route119_EventScript_15147A:: @ 815147A
	trainerbattle 0, 618, 0, Route119_Text_1BE6EA, Route119_Text_1BE729
	msgbox Route119_Text_1BE748, 6
	end

Route119_EventScript_151491:: @ 8151491
	trainerbattle 0, 619, 0, Route119_Text_1BE784, Route119_Text_1BE7D3
	msgbox Route119_Text_1BE7E9, 6
	end

Route119_EventScript_1514A8:: @ 81514A8
	trainerbattle 0, 620, 0, Route119_Text_1BE82F, Route119_Text_1BE88D
	msgbox Route119_Text_1BE89A, 6
	end

Route119_EventScript_1514BF:: @ 81514BF
	trainerbattle 0, 552, 0, Route119_Text_1BE8BB, Route119_Text_1BE90E
	specialval RESULT, 57
	compare RESULT, 1
	jumpeq Route119_EventScript_1514E6
	msgbox Route119_Text_1BE937, 6
	end

Route119_EventScript_1514E6:: @ 81514E6
	trainerbattle 5, 552, 0, Route119_Text_1BE98D, Route119_Text_1BE9D0
	msgbox Route119_Text_1BE9E8, 6
	end

Route119_EventScript_1514FD:: @ 81514FD
	trainerbattle 0, 559, 0, Route119_Text_1BEA3A, Route119_Text_1BEA88
	specialval RESULT, 57
	compare RESULT, 1
	jumpeq Route119_EventScript_151524
	msgbox Route119_Text_1BEAB3, 6
	end

Route119_EventScript_151524:: @ 8151524
	trainerbattle 5, 559, 0, Route119_Text_1BEB22, Route119_Text_1BEB49
	msgbox Route119_Text_1BEB68, 6
	end

Route119_EventScript_15153B:: @ 815153B
	trainerbattle 0, 399, 0, Route119_Text_1BEBC0, Route119_Text_1BEC1C
	msgbox Route119_Text_1BEC2A, 6
	end

Route119_EventScript_151552:: @ 8151552
	trainerbattle 0, 400, 0, Route119_Text_1BEC5E, Route119_Text_1BEC9A
	msgbox Route119_Text_1BECB1, 6
	end

Route119_EventScript_151569:: @ 8151569
	trainerbattle 0, 415, 0, Route119_Text_1BECF1, Route119_Text_1BED4C
	msgbox Route119_Text_1BED5C, 6
	end

Route119_EventScript_151580:: @ 8151580
	trainerbattle 0, 416, 0, Route119_Text_1BEDB6, Route119_Text_1BEDEC
	msgbox Route119_Text_1BEE06, 6
	end

Route119_EventScript_151597:: @ 8151597
	trainerbattle 0, 651, 0, Route119_Text_1BEE2D, Route119_Text_1BEE4B
	msgbox Route119_Text_1BEE66, 6
	end

Route119_EventScript_1515AE:: @ 81515AE
	trainerbattle 0, 693, 0, Route119_Text_1BEED0, Route119_Text_1BEF37
	msgbox Route119_Text_1BEF67, 6
	end

Route119_EventScript_1515C5:: @ 81515C5
	lock
	faceplayer
	msgbox Route119_Text_171520, 4
	closebutton
	move LAST_TALKED, Route119_Movement_1A083D
	waitmove 0
	release
	end

Route119_EventScript_1515DC:: @ 81515DC
	lock
	faceplayer
	msgbox Route119_Text_17157C, 4
	closebutton
	move LAST_TALKED, Route119_Movement_1A083D
	waitmove 0
	release
	end

Route119_EventScript_1515F3:: @ 81515F3
	msgbox Route119_Text_1715D7, 2
	end

Route119_EventScript_1515FC:: @ 81515FC
	msgbox Route119_Text_1716F4, 2
	end

Route119_EventScript_151605:: @ 8151605
	msgbox Route119_Text_171774, 3
	end
