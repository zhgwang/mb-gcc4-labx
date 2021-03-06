/*
FUNCTION
	<<strcpy>>---copy string

INDEX
	strcpy

ANSI_SYNOPSIS
	#include <string.h>
	char *strcpy(char *<[dst]>, const char *<[src]>);

TRAD_SYNOPSIS
	#include <string.h>
	char *strcpy(<[dst]>, <[src]>)
	char *<[dst]>;
	char *<[src]>;

DESCRIPTION
	<<strcpy>> copies the string pointed to by <[src]>
	(including the terminating null character) to the array
	pointed to by <[dst]>.

RETURNS
	This function returns the initial value of <[dst]>.

PORTABILITY
<<strcpy>> is ANSI C.

<<strcpy>> requires no supporting OS subroutines.

QUICKREF
	strcpy ansi pure
*/

#include <string.h>
#include <limits.h>

/*SUPPRESS 560*/
/*SUPPRESS 530*/

/* Nonzero if either X or Y is not aligned on a "long" boundary.  */
#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))

#if LONG_MAX == 2147483647L
#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)
#else
#if LONG_MAX == 9223372036854775807L
/* Nonzero if X (a long int) contains a NULL byte. */
#define DETECTNULL(X) (((X) - 0x0101010101010101) & ~(X) & 0x8080808080808080)
#else
#error long int is not a 32bit or 64bit type.
#endif
#endif

#ifndef DETECTNULL
#error long int is not a 32bit or 64bit byte
#endif

char*
_DEFUN (strcpy, (dst0, src0),
	char *dst0 _AND
	_CONST char *src0)
{

#ifndef HAVE_HW_PCMP

#if defined(PREFER_SIZE_OVER_SPEED) || defined(__OPTIMIZE_SIZE__)
  char *s = dst0;

  while (*dst0++ = *src0++)
    ;

  return s;
#else
  char *dst = dst0;
  _CONST char *src = src0;
  long *aligned_dst;
  _CONST long *aligned_src;

  /* If SRC or DEST is unaligned, then copy bytes.  */
  if (!UNALIGNED (src, dst))
    {
      aligned_dst = (long*)dst;
      aligned_src = (long*)src;

      /* SRC and DEST are both "long int" aligned, try to do "long int"
         sized copies.  */
      while (!DETECTNULL(*aligned_src))
        {
          *aligned_dst++ = *aligned_src++;
        }

      dst = (char*)aligned_dst;
      src = (char*)aligned_src;
    }

  while (*dst++ = *src++)
    ;
  return dst0;
#endif /* not PREFER_SIZE_OVER_SPEED */

#else    

  asm volatile ("                                                     \
            or      r9, r0, r0              /* Index register */    \n\
check_alignment:                                                    \n\
        andi    r3, r5, 3                                           \n\
        andi    r4, r6, 3                                           \n\
        bnei    r3, try_align_args                                  \n\
        bnei    r4, regular_strcpy      /* At this point we dont have a choice */       \n\
cpy_loop:                                   \n\
        lw      r3, r6, r9                  \n\
        pcmpbf  r4, r0, r3                  \n\
        bnei    r4, cpy_bytes           /* If r4 != 0, then null present within string */\n\
        sw      r3, r5, r9                  \n\
        brid    cpy_loop                    \n\
        addik   r9, r9, 4                   \n\
cpy_bytes:                                  \n\
        lbu     r3, r6, r9                  \n\
        sb      r3, r5, r9                  \n\
        addik   r4, r4, -1                  \n\
        bneid   r4, cpy_bytes               \n\
        addik   r9, r9, 1               /* delay slot */\n\
cpy_null:                                   \n\
        rtsd    r15, 8                      \n\
        or      r3, r0, r5              /* Return strcpy result */\n\
try_align_args:                             \n\
        xor     r7, r4, r3                  \n\
        bnei    r7, regular_strcpy      /* cannot align args */\n\
        rsubik  r10, r3, 4              /* Number of initial bytes to align */\n\
align_loop:                                 \n\
        lbu     r3, r6, r9                  \n\
        sb      r3, r5, r9                  \n\
        beqid   r3, end_cpy             /* Break if we have seen null character */\n\
        addik   r10, r10, -1                \n\
        bneid   r10, align_loop             \n\
        addik   r9, r9, 1                   \n\
        bri     cpy_loop                    \n\
regular_strcpy:                             \n\
        lbu     r3, r6, r9                  \n\
        sb      r3, r5, r9                  \n\
        bneid   r3, regular_strcpy          \n\
        addik   r9, r9, 1                   \n\
end_cpy:                                    \n\
        rtsd    r15, 8                      \n\
        or      r3, r0, r5              /* Return strcpy result */");
#endif /* ! HAVE_HW_PCMP */
}





