typedef struct s_command
{
	list* args;		// List of arguments, first one is the path
	list* ofiles;	// list of output files, first one is the actual output
	list* ifile;	// list of input files, first one is the actual input
} t_command;

typedef enum e_token_type
{
	TOKEN_ARG,		// Any string that can be expanded if needed
	TOKEN_NOEXPAND,	// Any string that shouldn't be exapanded (single quotes)
	TOKEN_OUT,		// >
	TOKEN_IN,		// <
	TOKEN_PIPE		// |
} t_token_type;

typedef struct s_token
{
	t_token_type type;
	char* str;
	bool concat_next;	// Should next token be concatenated with me?
}

// Take the next input as example:
echo "hello this is an argument"' concat me! $PLS' arg2 arg3 > output_file.txt $USER | ...

// First we must split it into tokens:
[
	{ .type = TOKEN_ARG, .str = "echo", .concat_next = false },
	{ .type = TOKEN_ARG, .str = "hello this is an argument", .concat_next = true },
	{ .type = TOKEN_NOEXPAND, .str = " concat me! $PLS", .concat_next = false },
	{ .type = TOKEN_ARG, .str = "arg2", .concat_next = false },
	{ .type = TOKEN_ARG, .str = "arg3", .concat_next = false },
	{ .type = TOKEN_OUT, .str = NULL, .concat_next = false },
	{ .type = TOKEN_ARG, .str = "output_file.txt", .concat_next = false },
	{ .type = TOKEN_ARG, .str = "$USER", .concat_next = false },
	{ .type = TOKEN_PIPE, .str = NULL, .concat_next = false },
	...
]

// I highly recommend a function that would look something like this to get the tokens:
t_lexer get_next_token(char** str)
{
	... // I went a bit overboard here.. if you eventually need help I can give you an implementation example
}

// Now expand!
" concat me! $PLS" stays the same because it has TOKEN_NOEXPAND
"$USER" becomes "ohearn"

// Then concatenate where needed
"hello this is an argument" becomes "hello this is an argument concat me! $PLS"
also, because it is now concatenated, the " concat me! $PLS" token gets removed

// construct the TOKEN_IN and TOKEN_OUT's
.str = NULL becomes .str = "output_file.txt"
also, because we constructed the TOKEN_OUT we can remove the "output_file.txt" token

// We are left with (.concat_next not displayed because they are now irrelevant):
[
	{ .type = TOKEN_ARG, .str = "echo" },
	{ .type = TOKEN_ARG, .str = "hello this is an argument concat me! $PLS" },
	{ .type = TOKEN_ARG, .str = "arg2" },
	{ .type = TOKEN_ARG, .str = "arg3" },
	{ .type = TOKEN_OUT, .str = "output_file.txt" },
	{ .type = TOKEN_ARG, .str = "ohearn" },
	{ .type = TOKEN_PIPE, .str = NULL },
	...
]

// now we construct the t_command from our tokens
{
	.args = ["echo", "hello this is an argument concat me! $PLS", "arg2", "arg3", "ohearn"], // Simply add all TOKEN_ARG's to this list
	.ofiles = ["output_file.txt"], // Simply add all TOKEN_OUT's
	.ifiles = NULL // Simply add all TOKEN_IN's (none present, so NULL)
}

// You end up with a list of t_command's, all separated by the pipes
// Congrats, half of minishell done!
// A good structure and proper parsing from the start will save you a lot of edge-cases
