! vim: set filetype=inform
! This provides a series of explanatory texts for new users unfamiliar with IF.

! helper function for formatting
[ bf text; style bold; print (string) text; style roman; ];
[ nm text; style bold; print (name) text; style roman; ];
[ ul text; style underline; print (string) text; style roman; ];
[ rv text; style reverse; print (string) text; style roman; ];

[ IntroSub;
	print (bf) "Introduction^",
		"^The game you are now playing
		is a kind of command-line story.
		You control your character
		by typing commands
		at the ", (bf) "> ", "prompt.",
		"^ If your commands are successful,
		the game will describe what happens.
		So if your command is ", (ul) "look", ",
		then you will see a description of your surroundings.
		If you scroll back a bit right now,
		you should see a description of: ",
		(nm) location, ".",
		"^ Your character will move
		from location to location
		as you type commands such as ", (ul) "go north",
		", ", (ul) "north", ", or even just ", (ul) "n", ".
		Most locations represent entire rooms,
		but areas like hallways
		may be broken up.",
		"^ You will find various objects
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
		"^ You may notice your ", (rv) "Score:", " going up
		as you obtain certain items
		or gain access to some areas.
		That's generally a sign
		that you're on the right path!",
		"^^For more detailed advice on play,
		type ", (ul) "help", " or ", (ul) "stuck", ".";
];

[ HelpSub;
	print "XXX: FIXME TO BE WRITTEN";
];

Verb 'intro' * -> Intro;
Verb 'help' * -> Help;
Verb 'stuck' * -> Strong; ! We use the StrongSub so we print advice if the player starts swearing, instead of scolding them for their language.

