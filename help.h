! This library provides a series of explanatory texts
! for new users unfamiliar with IF.

Include "ext_quote_box.h"; ! Used in the `Stuck` routine.


! helper functions for formatting
[ bf text; style bold; print (string) text; style roman; ];
[ nm text; style bold; print (name) text; style roman; ];
[ ul text; font off; style underline; print (string) text; style roman; font on; ];
[ rv text; style reverse; print (string) text; style roman; ];

! Note that this is written
! using "semantic linefeeds":
! https://rhodesmill.org/brandon/2012/one-sentence-per-line/
[ IntroSub;
	print (bf) "Introduction^",
		"^The game you are now playing
		is a kind of command-line story.
		You control your character
		by typing commands
		at the ", (bf) "> ", "prompt.",
		"^^If your commands are successful,
		the game will describe what happens.
		So if your command is ", (ul) "look", ",
		then you will see a description of your surroundings.
		If you scroll back a bit right now,
		you should see a description of: ",
		(nm) location, ".",
		"^^Your character will move
		from location to location
		as you type commands such as ", (ul) "go north",
		", ", (ul) "north", ", or even just ", (ul) "n", ".
		Most locations represent entire rooms,
		but areas like hallways
		may be broken up.
		It helps a lot to draw a map
		while you play!",
		"^^You will find various objects
		located throughout the game.
		You may pick many of them up
		with commands such as ",
		(ul) "take sonic screwdriver", 
		" or ", (ul) "get retroencabulator", ".
		You can set them down again
		by typing a command like ", (ul) "drop teddy bear", ".
		Some of these objects are useful tools,
		and may help you use commands like ",
		(ul) "pry safe with crowbar", ".",
		"^^You may notice your ", (rv) "Score:", " going up
		as you obtain certain items
		or gain access to some areas.
		That's generally a sign
		that you're on the right path!",
		"^^For more detailed advice on play,
		type ", (ul) "help", " or ", (ul) "stuck", ".";
];

[ HelpSub;
	print (bf) "How To Play This Game^",
		"^^This game was built with PunyInform,
		which is a system designed to recreate
		the ~Interactive Fiction~ games of Infocom.
		These games use a simple parser
		to split your typed instructions
		into verbs,
		prepositions,
		and objects.
		^^You will need to enter instructions
		beginning with imperative verbs,
		as though you were giving orders 
		to the character you are playing in the game.
		As examples,
		let's begin with movement verbs:^",
		"^    ", (ul) "north", "/", (ul) "n",
		" ", (ul) "south", "/", (ul) "s",
		" ", (ul) "east", "/", (ul) "e",
		" ", (ul) "west", "/", (ul) "w",
		" ", (ul) "up", "/", (ul) "u",
		" ", (ul) "down", "/", (ul) "d",
		"^^These are all shortcuts
		for the verb ", (ul) "go", ".
		So typing ", (ul) "s", " or ", (ul) "south", 
		" is the same as entering ", (ul) "go south",
		".  Here are some other verbs:^",
		"^    ", (ul) "look", "/", (ul) "l",
		" -- Display the description of your character's current location, and list any obvious items there.",
		"^    ", (ul) "inventory", "/", (ul) "i",
		" -- List all of the objects your character is carrying.",
		"^    ", (ul) "again", "/", (ul) "g",
		" -- Repeat the last instruction.",
		"^    ", (ul) "quit", "/", (ul) "q",
		" -- Quit the game (you'll be asked for confirmation).",
		"^    ", (ul) "restart", 
		" -- Start the game over from the beginning.",
		"^    ", (ul) "undo", 
		" -- Undo the last instruction.",
		"^^Most verbs accept nouns
		as objects of their actions.
		Here are some useful verbs
		that act on direct objects:^",
		"^    ", (ul) "get", "/", (ul) "take", "/", (ul) "pick up", (bf) " object",
		" -- Pick up an object so that your character carries it around.",
		"^    ", (ul) "drop", "/", (ul) "discard", (bf) " held object",
		" -- Leave an object in your character's current location.",
		"^    ", (ul) "look at", "/", (ul) "examine", "/", (ul) "x", (bf) " object",
		" -- Display the description of the object you specify, if it's visible.",
		"^    ", (ul) "open", "/", (ul) "uncover", "/", (ul) "unwrap", (bf) " object",
		" -- Open a thing that can be opened or closed, such as a door or a box.",
		"^    ", (ul) "close", "/", (ul) "cover", "/", (ul) "shut", (bf) " object",
		" -- Close something that is open.",
		"^    ", (ul) "climb", "/", (ul) "scale", (bf) " object",
		" -- Climb up an object to reach somewhere else.",
		"^^Some instructions require you to specify
		an indirect object,
		which is used to complete the action:^",
		"^    ", (ul) "say", "/", (ul) "answer", "/", (ul) "shout", (bf) " topic ", (ul) "to", (bf) " listener",
		" -- Say something to a listening object or character in the game.",
		"^    ", (ul) "unlock", "/", (ul) "pry", "/", (ul) "force open", (bf) " object ", (ul) "with", (bf) " held object",
		" -- Change a stuck or locked object, so that you can ", (ul) "open", " it.",
		"^    ", (ul) "hit", "/", (ul) "smash", "/", (ul) "break", (bf) " object ", (ul) "with", (bf) " held object",
		" -- Apply force to one object with another.",
		"^^Note that some verbs
		do very different things
		depending on the rest of the sentence:^",
		"^    ", (ul) "throw", (bf) " held object",
		" -- The same as ", (ul) "drop", ".",
		"^    ", (ul) "throw", "/", (ul) "put", (bf) " held object ", (ul) "in", (bf) " container", ".",
		" -- Put an object inside another.",
		"^    ", (ul) "throw", (bf) " held object ", (ul) "at", (bf) " container", ".",
		" -- Throw one object at another.";



		new_line;
];

Array dont_panic --> 1 13 "Don't Panic!";
[ StuckSub;
	! This will cut off scrollback in parchment,
	! but it's good for this moment.
	QuoteBox(dont_panic);

	print (bf) "^^Feeling A Bit Stuck?^",
		"^Games like these are made of puzzles,
		and the solutions do not always
		immediately present themselves.
		Here are some tips to help you through.",
		(bf) "^^Read The Freindly Manual^",
		"^The ", (ul) "intro", " command
		will help you get started,
		and the ", (ul) "help", " command
		provides a more detailed manual
		with example verbs to try.",
		(bf) "^^Draw A Map^",
		"^Draw boxes for each location in the game,
		and connect them with lines
		based on the compass directions.
		Mark the location
		of locked doors,
		useful items,
		and other notable features of the rooms.
		This will help you get some perspective,
		and possibly keep you
		from getting lost.",
		(bf) "^^Refer To Course Materials^",
		"^This game is an illustration
		of real-world problems
		in physical security.
		You will not always be able
		to gain access to something
		via the ~front door~,
		so try to think of other ways
		to get what you want.^";
];


Verb 'intro' 'info' * -> Intro;
Verb 'help' * -> Help;
Verb 'stuck'
	* -> Stuck
	* topic -> Stuck;
! We hijack `Strong` to give some helpful advice
! when the player starts swearing at the game.
! This will catch all the synonyms
! from PunyInform's `grammar.h`.
Extend 'damn' replace
	* 'germanium' -> PDP12
	* topic 'germanium' -> PDP12
	* -> Stuck
	* topic -> Stuck;

[ PDP12Sub i;
	! print the swear verb the user typed in all caps
	style reverse;
	for (i=0:i<WordLength(1):i++)
		print (char) (WordAddress(1)->i - 32);
	print ".SV NOT FOUND";
	style roman;
];
