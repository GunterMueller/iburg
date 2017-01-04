/*
 * Copyright (c) 1993,1994,1995,1996 David R. Hanson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * <http://www.opensource.org/licenses/mit-license.php>
 */

#ifndef BURG_INCLUDED
#define BURG_INCLUDED

/* iburg.c: */
extern void *alloc(int);

typedef enum { TERM=1, NONTERM } Kind;
typedef struct rule *Rule;
typedef struct term *Term;
struct term {		/* terminals: */
	char *name;		/* terminal name */
	Kind kind;		/* TERM */
	int esn;		/* external symbol number */
	int arity;		/* operator arity */
	Term link;		/* next terminal in esn order */
	Rule rules;		/* rules whose pattern starts with term */
};

typedef struct nonterm *Nonterm;
struct nonterm {	/* non-terminals: */
	char *name;		/* non-terminal name */
	Kind kind;		/* NONTERM */
	int number;		/* identifying number */
	int lhscount;		/* # times nt appears in a rule lhs */
	int reached;		/* 1 iff reached from start non-terminal */
	Rule rules;		/* rules w/non-terminal on lhs */
	Rule chain;		/* chain rules w/non-terminal on rhs */
	Nonterm link;		/* next terminal in number order */
};
extern Nonterm nonterm(char *);
extern Term term(char *, int);

typedef struct tree *Tree;
struct tree {		/* tree patterns: */
	void *op;		/* a terminal or non-terminal */
	Tree left, right;	/* operands */
	int nterms;		/* number of terminal nodes in this tree */
};
extern Tree tree(char *, Tree, Tree);

struct rule {		/* rules: */
	Nonterm lhs;		/* lefthand side non-terminal */
	Tree pattern;		/* rule pattern */
	int ern;		/* external rule number */
	int packed;		/* packed external rule number */
	int cost;		/* associated cost */
	Rule link;		/* next rule in ern order */
	Rule next;		/* next rule with same pattern root */
	Rule chain;		/* next chain rule with same rhs */
	Rule decode;		/* next rule with same lhs */
	Rule kids;		/* next rule with same burm_kids pattern */
};
extern Rule rule(char *, Tree, int, int);
extern int maxcost;		/* maximum cost */

/* gram.y: */
void yyerror(char *, ...);
int yyparse(void);
void yywarn(char *, ...);
extern int errcnt;
extern FILE *infp;
extern FILE *outfp;

#endif /* BURG_INCLUDED */
