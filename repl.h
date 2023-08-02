#include <inttypes.h>
// Masks for segments of double
#define MASK_SIGN 0x8000000000000000
#define MASK_EXPONENT 0x7ff0000000000000
#define MASK_QUIET 0x0008000000000000
#define MASK_TYPE 0x0007000000000000
#define MASK_SIGNATURE 0xffff000000000000
#define MASK_PAYLOAD_INT 0x00000000ffffffff
#define MASK_PAYLOAD 0x0000ffffffffffff

// Type IDs for short encoded types
#define MASK_TYPE_NAN 0x0000000000000000
#define MASK_TYPE_FALSE 0x0001000000000000
#define MASK_TYPE_TRUE 0x0002000000000000
#define MASK_TYPE_NULL 0x0003000000000000
#define MASK_TYPE_INT 0x0004000000000000
#define MASK_TYPE_SYM 0x0005000000000000

// Constant short encoded values
#define kNaN (MASK_EXPONENT | MASK_QUIET)
#define kFalse (kNaN | MASK_TYPE_FALSE)
#define kTrue (kNaN | MASK_TYPE_TRUE)
#define kNull (kNaN | MASK_TYPE_NULL)
#define kInt (kNaN | MASK_TYPE_INT)
#define kSym (kNaN | MASK_TYPE_SYM)

// Signatures of encoded types
#define SIGNATURE_NAN kNaN
#define SIGNATURE_FALSE kFalse
#define SIGNATURE_TRUE kTrue
#define SIGNATURE_NULL kNull
#define SIGNATURE_INT kInt
#define SIGNATURE_SYM kSym

typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_NULL,
    TYPE_SYM,
} SHORT_TYPE;

SHORT_TYPE get_type(double value);
int32_t decode_int(double value);
double create_sym(char *value);
uint64_t decode_sym(double value);
void print_value(double value);
double new_symbol(char *value);
double new_int(double value);
double parse_atom();
double Read();
