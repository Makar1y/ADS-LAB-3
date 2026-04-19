#ifndef BIGINT_COMPAT_H
#define BIGINT_COMPAT_H

#define count bi_count
#define isEmpty bi_isEmpty
#define isFull bi_isFull
#define makeEmpty bi_makeEmpty
#define clone bi_clone

#include "1vlsa2150/BigInteger.h"

#undef count
#undef isEmpty
#undef isFull
#undef makeEmpty
#undef clone

#endif
