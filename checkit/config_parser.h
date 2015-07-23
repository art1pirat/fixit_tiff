#ifndef _FIXIT_TIFF_CONFIG_PARSER
#define _FIXIT_TIFF_CONFIG_PARSER
#include "../fixit/fixit_tiff.h"
#include "check.h"


/* struct to hold parsing configuration */
typedef struct funcu * funcp;
typedef struct {
        funcp fu_p;
        char * name;
        void * next;
        ret_t result;
} executionentry_t;

typedef struct {
        executionentry_t * start;
        executionentry_t * last; 
} executionplan_t;

typedef enum { mandatory, ifdepends, optional } requirements_t;
typedef enum { range, logical_or, any, only } values_t;


/* definitons of structs of function pointers to hold type information for "lazy evaluation" */

typedef struct f_s {
  ret_t (*functionp)(TIFF *);
} f_t;

typedef struct f_int_s {
  int a;
  ret_t (*functionp)(TIFF *, tag_t a);
} f_int_t;

typedef struct f_intint_s {
  int a;
  unsigned int b;
  ret_t (*functionp)(TIFF*, tag_t a, unsigned int b);
} f_intint_t;

typedef struct f_intintint_s {
  int a;
  unsigned int b;
  unsigned int c;
  ret_t (*functionp)(TIFF*, tag_t a, unsigned int b, unsigned int c);
} f_intintint_t;

typedef struct f_intintintp_s {
  int a;
  int b;
  unsigned int * c;
  ret_t (*functionp)(TIFF*, tag_t a, int b, unsigned int * c);
} f_intintintp_t;

typedef enum { f_dummy, f_void, f_int, f_intint, f_intintint, f_intintintp } ftype_t;

struct funcu {
  ftype_t ftype;
  funcp pred;
  tag_t tag;
  union  {
    struct f_s * fvoidt;
    struct f_int_s * fintt;
    struct f_intint_s * fintintt;
    struct f_intintint_s * fintintintt;
    struct f_intintintp_s * fintintintpt;
  } fu;
};

/* MINTAGS - MAXTAGS is range of possible existing TAG numbers */
#define MINTAGS 254
#define MAXTAGS 65536


typedef struct parser_state_s {
  int lineno;
  int valuelist;
  tag_t tag;
  values_t val;
  requirements_t req;
  unsigned int i_stack[40];
  int i_stackp;
  int called_tags[MAXTAGS];
  FILE * stream;
  int any_reference;
} parser_state_t;

void set_parse_error(char * msg, char * yytext);
int execute_plan (TIFF * tif) ;
void print_plan ();
void print_plan_results ();
void clean_plan ();
void parse_plan ();
void parse_plan_via_stream (FILE * stream);
void add_default_rules_to_plan();

#endif
/* _FIXIT_TIFF_CONFIG_PARSER */
