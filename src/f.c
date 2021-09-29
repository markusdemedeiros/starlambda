#include "f.h"

#include <stdio.h>
#include <stdlib.h>


/* ****************************************************************************
 * lambda representation data
 */

term_t* allocate_term(term_t_e type){
	term_t *ret = malloc(sizeof(term_t));
	ret->type = type;
	return ret;
}


/* ****************************************************************************
 * print
 */

void print_lambda_recurse(term_t *term)
{
	switch(term->type)
	{
		case VAR:
			printf("%d", term->lam_var);
			break;
		case LAM:
			printf("\\. ");
			print_lambda_recurse(term->next);
			break;
		case APP:
			printf("(");
			print_lambda_recurse(term->apply_fn);
			printf(") ");
			print_lambda_recurse(term->next);
			break;
	}
}

void print_lambda(term_t *term)
{
	print_lambda_recurse(term);
	printf("\n");
}

void free_lambda(term_t *term)
{
	switch(term->type)
	{
		case APP:	free_lambda(term->apply_fn);
		case LAM:	free_lambda(term->next);
		case VAR:	free(term);
	}
}


term_t *copy_term(term_t* term) 
{
	term_t *ret = malloc(sizeof(term_t));
	ret->type = term->type;
	switch(term->type)
	{
		case APP:
			ret->apply_fn = copy_term(term->apply_fn);
		case LAM:
			ret->next = copy_term(term->next);
			return ret;
		case VAR:
			ret->lam_var = term->lam_var; 
			return ret;
	}
	return NULL;
}

/*	LOR REDEX (leftmost outermost)
 *		http://pages.cs.wisc.edu/~horwitz/CS704-NOTES/1.LAMBDA-CALCULUS.html
 * 		http://pages.cpsc.ucalgary.ca/~robin/class/417/Assignment_2.html
 * if the term is (\x.N) M  then this is the next redex
 * if the term is N M  where N is not an abstraction then try to find the next redex in N (leftmost redex), only if this fails try to find a redex in M.
 * if the term is \x.N then find a redex in N.
 */


/* Returns address to address term pointer */
term_t **find_lor_redex(term_t **p_term)
{
	term_t *term = *p_term;
	switch(term->type)
	{
		term_t **ret;
		case APP:
			if (term->apply_fn->type == LAM) 				return p_term;	// 1. Check if this is redex
			if ( (ret = find_lor_redex(&term->apply_fn)) ) 	return ret;		// 2. Search X in X*
		case LAM:
			if ( (ret = find_lor_redex(&term->next)) ) 		return ret;		// 3. Search X in *X or \*. X
		case VAR:
		default:
			return NULL;													// 4. LOR redex does not exist
	}
}


/*
 * Source: https://github.com/Gabriel439/Haskell-Morte-Library/issues/1
 * 
 *  ** easy proof: up is Z-linear in the first argument (but not in the second)
 *	** ie.
 *  ** up(1,0)up(d,c)s = up(d+1,c)s
 *
 * up(d,c)k       	=  | k     if k < c
 *                     | k + d if k >= c
 * up(d,c)(\. t)  	=  \. up(d,c+1)t
 * up(d,c)(t u)   	=  (up(d,c)t up(d,c)u)
 */

void up(int d, int c, term_t* term)
{
	switch(term->type)
	{
		case LAM:	up(d, c+1, term->next);
					break;

		case APP:	up(d,c,term->next);
					up(d,c,term->apply_fn);
					break;

		case VAR:	if (term->lam_var >= c) term->lam_var += d;
					break;
	}
}


/*
 * k[j := s]      	=  | s  if k = j
 *                     | k  otherwise
 * (\. t)[j := s]  	=  \. t[j+1 := up(1,0)s]
 * (t u)[j := s]   	=  (t[j := s]  u[j := s])
 */


void beta_reduce_recurse(term_t **term_p, int j, term_t *s, int s_up_d)
{
	term_t *term = *term_p;
	switch(term->type)
	{
		case VAR:
			if (term->lam_var == j) 
			{
				free(term);
				*term_p = copy_term(s);
				up(s_up_d, 0, *term_p);
			}
			break;
		case LAM:
			beta_reduce_recurse(&term->next, j+1, s, s_up_d + 1);
			break;
		case APP:
			beta_reduce_recurse(&term->apply_fn, j, s, s_up_d);
			beta_reduce_recurse(&term->next, j, s, s_up_d);
			break;
	}
}

/* (\. t) u ~> up(-1,0)(t[0 := up(1,0)u]) */

int beta_reduce(term_t **expression)
{

	term_t **redex = find_lor_redex(expression);
	if (!redex)		return 0;
	term_t *apply = *redex;	
	/* 1. Unpack redex */

	term_t *replacement = apply->next;
	term_t *function = apply->apply_fn->next;

	/* 2. Perform reduction on inner function */ 
	beta_reduce_recurse(&(function), 0, replacement, 1);
	up(-1, 0, function);

	/* 3. Clean up memory */
	free_lambda(replacement);
	free(apply->apply_fn);
	free(apply);
	(*redex) = function;

	return 1;
}


int cmp_lambda(const term_t* a, const term_t* b)
{
	if (!a || !b)
		return 0;

    if (a->type != b->type)
        return 0;

    switch (a->type)
    {
        case VAR:
            return (a->lam_var == b->lam_var);
        case LAM:
            return cmp_lambda(a->next, b->next);
        case APP:
            return (cmp_lambda(a->next, b->next) 
                &&  cmp_lambda(a->apply_fn, b->apply_fn));
    }
	return 0;
}




int test_link (int x)
{
	return x + 1;
}