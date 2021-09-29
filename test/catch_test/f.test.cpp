#include "catch.hpp"
extern "C"
{
#include "../../src/f.h"
}

#define DEBUG_PRINT


TEST_CASE("SIMPLE_BOUND", "[weight=1][part=test]") {
    term_t *app = allocate_term(APP);
    term_t *lam = allocate_term(LAM);
    term_t *bv = allocate_term(VAR);
    term_t *ubv = allocate_term(VAR);

    app->next = ubv;
    ubv->lam_var = 10;
    app->apply_fn = lam;
    lam->next = bv;
    bv->lam_var = 0;

    printf("    ");
    print_lambda(app);
    beta_reduce(&app);
    printf(" => ");
    print_lambda(app);
    printf("exp ");
    printf("10");
    printf("\n");
    free_lambda(app);
}


TEST_CASE("SIMPLE_UNBOUND", "[weight=1][part=test]") {
    term_t *outl = allocate_term(LAM);
    term_t *outl1 = allocate_term(LAM);
    term_t *outl2 = allocate_term(LAM);
    term_t *app = allocate_term(APP);
    term_t *lam = allocate_term(LAM);
    term_t *bv = allocate_term(VAR);
    term_t *ubv = allocate_term(VAR);

    outl->next = outl1;
    outl1->next = outl2;
    outl2->next = app;
    app->next = ubv;
    ubv->lam_var = 2;
    app->apply_fn = lam;
    lam->next = bv;
    bv->lam_var = 0;

    printf("    ");
    print_lambda(outl);
    beta_reduce(&outl);
    printf(" => ");
    print_lambda(outl);
    printf("exp ");
    printf("\\. \\. \\. 2");
    printf("\n");
    free_lambda(outl);
}



term_t *setup_manylambda_testcase(int x, int y, int z)
{
    //      \a. \b. \c. (\d. \e. \f. (X) (Y) ) (Z)
    term_t *la = allocate_term(LAM);
    term_t *lb = allocate_term(LAM);
    term_t *lc = allocate_term(LAM);
    term_t *ld = allocate_term(LAM);
    term_t *le = allocate_term(LAM);
    term_t *lf = allocate_term(LAM);

    term_t *apo = allocate_term(APP);
    term_t *api = allocate_term(APP);

    term_t *va = allocate_term(VAR);
    term_t *vb = allocate_term(VAR);
    term_t *vc = allocate_term(VAR);

    la->next = lb;
    lb->next = lc;
    lc->next = apo;
    apo->next = vb;

    apo->apply_fn = ld;
    ld->next = le;
    le->next = lf;
    lf->next = api;
    api->next = vc;

    api->apply_fn = va;

    va->lam_var = x;
    vb->lam_var = y;
    vc->lam_var = z;

    return la;
}


void run_manylambda_case(int x, int z, int y, int r1, int r2)
{
    term_t *la = setup_manylambda_testcase(x, y, z);
    
    #ifdef DEBUG_PRINT
    printf("    ");
    print_lambda(la);
    #endif

    beta_reduce(&la);

    #ifdef DEBUG_PRINT
    printf(" => ");
    print_lambda(la);
    #endif

    free_lambda(la);
}


TEST_CASE("PRINT_A", "[weight=1][part=test]")
{   

    //                                5   2     1 
    //      \a. \b. \c. (\d. \e. \f. (a) (d) ) (b)
    //  =>  \a. \b.      \c. \d. \f. (a) (b)
    //                                4   3
    run_manylambda_case(5, 2, 1, 4, 3);
    printf("ab\n\n");
    //                                0   1     1 
    //      \a. \b. \c. (\d. \e. \f. (f) (e) ) (b)
    //  =>  \a. \b.      \c. \d. \e. (f) (d)
    //                                2   1        
    run_manylambda_case(0, 1, 1, 2, 1);
    printf("fd\n\n");
    //                                2   4     1
    //      \a. \b. \c. (\d. \e. \f. (d) (b) ) (b)
    //  =>  \a. \b.      \c. \d. \e. (b) (b)
    //                                3   3
    run_manylambda_case(2, 4, 1, 3, 3);
    printf("bb\n\n");
    //                                2   4     2
    //      \a. \b. \c. (\d. \e. \f. (d) (b) ) (a)
    //  =>  \a. \b.      \c. \d. \e. (a) (b)
    //                                4   3
    run_manylambda_case(2, 4, 2, 4, 3);
    printf("ab\n\n");
    //                                2   2     1
    //      \a. \b. \c. (\d. \e. \f. (d) (d) ) (b)
    //  =>  \a. \b.      \c. \d. \e. (b) (b)
    //                                3   3
    run_manylambda_case(2, 2, 1, 4, 3);    
    printf("bb\n\n");
}


term_t *setup_manylambda_2_testcase(int x, int y, int z)
{
    //      \a. \b. \c. (\d. \e. \f. (X) (Y) ) (\d. (d) (Z))
    term_t *la = allocate_term(LAM);
    term_t *lb = allocate_term(LAM);
    term_t *lc = allocate_term(LAM);
    term_t *ld = allocate_term(LAM);
    term_t *le = allocate_term(LAM);
    term_t *lf = allocate_term(LAM);

    term_t *ldr = allocate_term(LAM);
    term_t *apr = allocate_term(APP);
    term_t *vdr = allocate_term(VAR);

    term_t *apo = allocate_term(APP);
    term_t *api = allocate_term(APP);

    term_t *va = allocate_term(VAR);
    term_t *vb = allocate_term(VAR);
    term_t *vc = allocate_term(VAR);

    la->next = lb;
    lb->next = lc;
    lc->next = apo;
    apo->next = ldr;
    ldr->next = apr;
    apr->next = vb;
    apr->apply_fn = vdr;

    apo->apply_fn = ld;
    ld->next = le;
    le->next = lf;
    lf->next = api;
    api->next = vc;

    api->apply_fn = va;

    va->lam_var = x;
    vb->lam_var = y;
    vc->lam_var = z;
    vdr->lam_var = 0;

    return la;
}

void run_manylambda_2_case(int x, int z, int y)
{
    term_t *la = setup_manylambda_2_testcase(x, y, z);
    
    #ifdef DEBUG_PRINT
    printf("    ");
    print_lambda(la);
    #endif

    beta_reduce(&la);

    #ifdef DEBUG_PRINT
    printf(" => ");
    print_lambda(la);
    #endif

    beta_reduce(&la);

    #ifdef DEBUG_PRINT
    printf(" => ");
    print_lambda(la);
    #endif


    free_lambda(la);
}


TEST_CASE("PRINT_B", "[weight=1][part=test]") {
    //                                2   4              3
    //      \a. \b. \c. (\d. \e. \f. (d) (b) ) (\d. (d) (a))
    //      \a. \b.      \c. \d. \e. (\f. (f) (a)) (b)
    run_manylambda_2_case(2,4,3);
}



TEST_CASE("PRINT_D", "[weight=1][part=test]") {
    // \a. \b. \c. \d. \e. (\f. 0 ?) (b)
    term_t *la = allocate_term(LAM);
    term_t *lb = allocate_term(LAM);
    term_t *lc = allocate_term(LAM);
    term_t *ld = allocate_term(LAM);
    term_t *le = allocate_term(LAM);
    

    term_t *apo = allocate_term(APP);
    term_t *vb = allocate_term(VAR);


    term_t *api = allocate_term(APP);
    term_t *lf = allocate_term(LAM);
    term_t *vf = allocate_term(VAR);
    term_t *vq = allocate_term(VAR);




    la->next = lb;
    lb->next = lc;
    lc->next = ld;
    ld->next = le;
    le->next = apo;
    apo->next = vb;
    apo->apply_fn = lf;
    lf->next = api;
    api->apply_fn = vf;
    api->next = vq;

    vf->lam_var = 1;
    vb->lam_var = 10;
    vq->lam_var = 5;
    
    printf("\n=== ");
    print_lambda(la);
    printf("LOR:");
    print_lambda(*find_lor_redex(&la));
    printf(" => ");
    beta_reduce(&la);
    print_lambda(la);

    free_lambda(la);


}




TEST_CASE("PRINT_C", "[weight=1][part=test]") {
    term_t *app = allocate_term(APP);

    term_t *la = allocate_term(LAM);
    term_t *lb = allocate_term(LAM);

    term_t *vao = allocate_term(VAR);
    term_t *vbi = allocate_term(VAR);

    la->next = app;
    app->next = vao;
    app->apply_fn = lb;
    lb->next = vbi;
    app->next = vao;

    vao->lam_var = 6;
    vbi->lam_var = 0;
    
    printf("\n    ");
    print_lambda(la);
    printf(" => ");
    beta_reduce(&la);
    print_lambda(la);

    free_lambda(la);
}

