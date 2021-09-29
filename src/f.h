#ifndef F_H
#define F_H 


typedef enum {
	VAR,
	LAM,
	APP
} term_t_e;

typedef struct term_t_s {
	struct term_t_s *next;				/* \a. x => next = x */
	struct term_t_s *apply_fn;			/* a b => apply_fn = a, next = b */
	int lam_var;					    /* VAR (ith lambda) => lam_var = i*/
	term_t_e type;
} term_t;

term_t*         allocate_term       (term_t_e type);
int 			cmp_lambda			(const term_t* a, const term_t* b);

void            print_lambda        (term_t *term);
void            free_lambda         (term_t *term);
term_t*         copy_term           (term_t *term);
term_t**        find_lor_redex      (term_t **term);
int             beta_reduce         (term_t **term);

int 			test_link           (int x);

#endif	// f.h
