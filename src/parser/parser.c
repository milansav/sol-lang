#include "parser.h"

static Lexeme peek();
static Lexeme curr();
static int has_next();
static void next();
static int accept(Symbol s);
static int expect(Symbol s);

static void program();
static bool statement();
static void let_declaration();
static void const_declaration();
static void type_declaration();
static void expression();
static void condition();
static void term();
static void factor();

LexemeArr* lexeme_arr;
Lexeme curr_lexeme;
u8 lexeme_position;

Symbol curr_sym;

Ast* tree;

static Lexeme peek()
{
	if(has_next())
		return lexeme_arr->arr[lexeme_position + 1];
}

static Lexeme curr()
{
	return curr_lexeme;
}

static int has_next()
{
	return !(lexeme_arr->arr[lexeme_position].type == END);
}

static void next()
{
    if(has_next())
    {
        curr_lexeme = lexeme_arr->arr[++lexeme_position];
        curr_sym = curr_lexeme.type;
    }
}

static int accept(Symbol s)
{
	if(curr_sym == s)
	{
		if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
		{
			g_log("parser.c : accept: accepted");
			printf(" Type: %s Label: %s\n", TypeString[s], curr_lexeme.label);
		}
		next();
		return 1;
	}
	return 0;
}

static int expect(Symbol s)
{

	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_log("parser.c : expect: expecting: ");
		printf("%s\n", TypeString[s]);
	}

	if(accept(s)) return 1;

	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER | OUTPUT_DEBUG))
	{
		g_error("parser.c : statement: syntax error, unexpected symbol at: ");
		printf("%d:%d ", curr_lexeme.row, curr_lexeme.column);
		g_error(": Type: ");
		printf("%s", TypeString[curr_sym]);
		g_error(" Label: ");
		printf("%s\n", curr_lexeme.label);
	}

	return 0;
}

Ast* parser_start(LexemeArr* l)
{
    lexeme_arr = l;
	curr_lexeme = *lexeme_arr->arr;
	curr_sym = curr_lexeme.type;
	lexeme_position = 0;
    //tree = ast_construct();

	program();

	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : Finished parsing");
	}

	return tree;
}

static void program()
{
	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : program");
	}

	while(statement());
}

static bool statement()
{
	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_log("parser.c : statement");
		printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
	}

	if(accept(IDENT))
	{
		if(accept(ASSIGN))
		{
			expression();
			expect(SEMICOLON);
		}
		else if(accept(LPAREN))
		{
			do
			{
				if(curr_sym == STR || curr_sym == CHAR || curr_sym == NUM || curr_sym == IDENT)
				{
					next();
					continue;
				}
			} while (accept(COMMA));
			expect(RPAREN);
			expect(SEMICOLON);
		}
	}
	else if(accept(LCRLBRACKET))
	{
		if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
		{
			g_logln("parser.c : begin statement");
		}

		while(statement());

		expect(RCRLBRACKET);
	}
	else if(accept(LET))
	{
		let_declaration();
	}
	else if(accept(CONST))
	{
		const_declaration();
	}
	else if(accept(TYPE))
	{
		type_declaration();
	}
	else if(curr_sym == END)
	{
		return false;
	}
	else
	{
		if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER | OUTPUT_DEBUG))
		{
			g_error("parser.c : statement: syntax error, unexpected symbol at: ");
			printf("%d:%d ", curr_lexeme.row, curr_lexeme.column);
			g_error(": Type: ");
			printf("%s", TypeString[curr_sym]);
			g_error(" Label: ");
			printf("%s\n", curr_lexeme.label);
		}

		next();
		return false;
	}

	return true;
}

static void let_declaration()
{

	do
	{
		expect(IDENT);

		if(accept(ASSIGN))
		{
			expect(NUM);

			if(curr_sym == SUM || curr_sym == SUB || curr_sym == MUL || curr_sym == DIV)
			{
				expression();
			}
		}

	} while (accept(COMMA));
	
	expect(SEMICOLON);
}

static void const_declaration()
{

}

static void type_declaration()
{

}

static void expression()
{
	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : expression");
		printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
	}

	if(curr_sym == SUM || curr_sym == SUB)
		next();

	term();

	while(curr_sym == SUM || curr_sym == SUB)
	{
		next();
		term();
	}
}

static void condition()
{
	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : condition");
		printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
	}

	expression();

	bool equal = accept(EQL);
	bool nequal = accept(NQL);
	bool less = accept(LSS);
	bool lequal = accept(LQL);
	bool greater = accept(GTR);
	bool gequal = accept(GQL);
	bool variable = accept(IDENT);

	if(curr_sym == RPAREN)
	{
		return;
	}

	if(equal || nequal || less || lequal || greater || gequal)
	{
		expression();
	}
	else
	{
		if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER | OUTPUT_DEBUG))
		{
			g_errorln("parser.c : condition: invalid operator\n");
			printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
		}
	}
}

static void term()
{
	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : term");
		printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
	}

	factor();
	while(curr_sym == MUL || curr_sym == DIV)
	{
		next();
		factor();
	}
}

static void factor()
{

	if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER))
	{
		g_logln("parser.c : factor");
		printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
	}

	if(accept(IDENT))
	{
		return;
	}
	else if(accept(NUM))
	{
		return;
	}
	else if(accept(LPAREN))
	{
		expression();
		expect(RPAREN);
	}
	else
	{
		if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_PARSER | OUTPUT_DEBUG))
		{
			g_errorln("parser.c : factor: syntax error\n");
			printf(" Type: %s Label: %s\n", TypeString[curr_sym], curr_lexeme.label);
			next();
		}
	}
}