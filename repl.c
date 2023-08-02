#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <editline/readline.h>
#include "repl.h"

SHORT_TYPE get_type(double value)
{
  uint64_t converted = *(uint64_t *)&value;
  uint64_t signature = converted & MASK_SIGNATURE;
  if ((~converted & MASK_EXPONENT) != 0)
    return TYPE_FLOAT;

  // Short encoded types
  switch (signature)
  {
  case SIGNATURE_NAN:
    return TYPE_FLOAT;
  case SIGNATURE_FALSE:
  case SIGNATURE_TRUE:
    return TYPE_BOOL;
  case SIGNATURE_NULL:
    return TYPE_NULL;
  case SIGNATURE_INT:
    return TYPE_INT;
  case SIGNATURE_SYM:
    return TYPE_SYM;
  }
  return TYPE_NULL;
}

int32_t decode_int(double value)
{
  return *(uint64_t *)&value & MASK_PAYLOAD_INT;
}

double create_sym(char *value)
{
  uint64_t boxed = kSym | (uint64_t)value;
  return *(double *)&boxed;
}

uint64_t decode_sym(double value)
{
  return *(uint64_t *)&value & MASK_PAYLOAD;
}

void print_value(double value)
{

  switch (get_type(value))
  {

  case TYPE_FLOAT:
  {
    printf("type float. value: %f", value);
    break;
  }

  case TYPE_BOOL:
  {
    printf("%s", value == kTrue ? "#t" : "#f");
    break;
  }

  case TYPE_NULL:
  {
    printf("()");
    break;
  }

  case TYPE_INT:
  {
    printf("type int. value: %d", decode_int(value));
    break;
  }

  case TYPE_SYM:
  {
    printf("type symbol. value: %s", (char *)decode_sym(value));
    break;
  }

  default:
  {
    printf("Unknown value type!");
  }
  }
}

/* tokenization buffer and the next character that we are looking at */
char buf[40], see = ' ';

double new_symbol(char *value)
{
  char *new_sympol_address = malloc(strlen(value) + 1);
  strcpy(new_sympol_address, value);
  return create_sym(new_sympol_address);
}

double new_int(double value)
{
  uint32_t narrow = (int32_t)value;
  uint64_t boxed = kInt | (uint64_t)narrow;
  return *(double *)&boxed;
}

double parse_atom()
{
  double d;
  int i;
  int32_t trunc;
  /* if the token scans as a float, first check if it can be stored as an int32, else return a float, else a symbol*/
  return (sscanf(buf, "%lg%n", &d, &i) > 0 && !buf[i]) ? d == (double)(trunc = d) ? new_int(d) : d : new_symbol(buf);
}

/* advance to the next character */
void look()
{
  int c = getchar();
  see = c;
  if (c == EOF)
    exit(0);
}

/* return nonzero if we are looking at character c, ' ' means any white space */
uint64_t seeing(char c)
{
  return c == ' ' ? see > 0 && see <= c : see == c;
}

/* return the look ahead character from standard input, advance to the next */
char get()
{
  char c = see;
  look();
  return c;
}

/* tokenize into buf[], return first character of buf[] */
char scan()
{
  int i = 0;
  while (seeing(' '))
    look();
  if (seeing('(') || seeing(')') || seeing('\''))
    buf[i++] = get();
  else
    do
      buf[i++] = get();
    while (i < 39 && !seeing('(') && !seeing(')') && !seeing(' '));
  buf[i] = 0;
  return *buf;
}

double Read()
{
  scan();
  /* consider parse_atom(scan()); where scan returns a pointer to buf and parse_atom takes a char * */
  return parse_atom();
}

int main(int argc, char const *argv[])
{
  while (1)
  {
    printf("> ");
    print_value(Read());
    printf("\n");
  }
  return 0;
}
