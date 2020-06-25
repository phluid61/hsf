
LEGIT_START = %w[
  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
  a b c d e f g h i j k l m n o p q r s t u v w x y z
  *
]

LEGIT = %w[
  ! # $ % & ' * + - . ^ _ ` | ~
  0 1 2 3 4 5 6 7 8 9
  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
  a b c d e f g h i j k l m n o p q r s t u v w x y z
  : /
]

$legit_start_hi = 0
$legit_start_lo = 0
$legit_hi = 0
$legit_lo = 0

64.times do |byte|
  bit = 1 << byte

  char = byte.chr
  $legit_start_lo |= bit if LEGIT_START.include? char
  $legit_lo       |= bit if LEGIT.include? char

  char = (byte+64).chr
  $legit_start_hi |= bit if LEGIT_START.include? char
  $legit_hi       |= bit if LEGIT.include? char
end

$legit_start_hi = '%016X' % $legit_start_hi
$legit_start_lo = '%016X' % $legit_start_lo
$legit_hi = '%016X' % $legit_hi
$legit_lo = '%016X' % $legit_lo

puts <<C
#define LEGIT_START(c) ( \\
 ((sh_char_t)(c) >= SH_CHAR_C(64)) ? \\
 ((UINT64_C(1) << ((sh_char_t)(c) - SH_CHAR_C(64))) & UINT64_C(0x#$legit_start_hi)) : \\
 ((UINT64_C(1) <<  (sh_char_t)(c)                 ) & UINT64_C(0x#$legit_start_lo)) \\
)

#define LEGIT(c) ( \\
 ((sh_char_t)(c) >= SH_CHAR_C(64)) ? \\
 ((UINT64_C(1) << ((sh_char_t)(c) - SH_CHAR_C(64))) & UINT64_C(0x#$legit_hi)) : \\
 ((UINT64_C(1) <<  (sh_char_t)(c)                 ) & UINT64_C(0x#$legit_lo)) \\
)
C

