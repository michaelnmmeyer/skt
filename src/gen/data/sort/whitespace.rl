/* Recognition of whitespace characters. */

%%{

machine whitespace;

NEXT_LINE = 0xc2 0x85;
LINE_SEPARATOR = 0xe2 0x80 0xa8;
PARAGRAPH_SEPARATOR = 0xe2 0x80 0xa9;

# All newline characters. See https://en.wikipedia.org/wiki/Newline

new_line =
  "\r"
| "\n"
| "\r\n"
| "\v"
| "\f"
| NEXT_LINE
| LINE_SEPARATOR
| PARAGRAPH_SEPARATOR
;

# See https://en.wikipedia.org/wiki/Whitespace_character
# We don't include non-latin whitespace characters. I don't know what to do
# with them.

LINE_TABULATION = 0x0b;
NO_BREAK_SPACE = 0xc2 0xa0;
EN_QUAD = 0xe2 0x80 0x80;
EM_QUAD = 0xe2 0x80 0x81;
EN_SPACE = 0xe2 0x80 0x82;
EM_SPACE = 0xe2 0x80 0x83;
THREE_PER_EM_SPACE = 0xe2 0x80 0x84;
FOUR_PER_EM_SPACE = 0xe2 0x80 0x85;
SIX_PER_EM_SPACE = 0xe2 0x80 0x86;
FIGURE_SPACE = 0xe2 0x80 0x87;
PUNCTUATION_SPACE = 0xe2 0x80 0x88;
THIN_SPACE = 0xe2 0x80 0x89;
HAIR_SPACE = 0xe2 0x80 0x8a;
NARROW_NO_BREAK_SPACE = 0xe2 0x80 0xaf;
MEDIUM_MATHEMATICAL_SPACE = 0xe2 0x81 0x9f;
ZERO_WIDTH_SPACE = 0xe2 0x80 0x8b;

horizontal_space =
  " "
| "\t"
| LINE_TABULATION
| NO_BREAK_SPACE
| EN_QUAD
| EM_QUAD
| EN_SPACE
| EM_SPACE
| THREE_PER_EM_SPACE
| FOUR_PER_EM_SPACE
| SIX_PER_EM_SPACE
| FIGURE_SPACE
| PUNCTUATION_SPACE
| THIN_SPACE
| HAIR_SPACE
| NARROW_NO_BREAK_SPACE
| MEDIUM_MATHEMATICAL_SPACE
| ZERO_WIDTH_SPACE
;

whitespace =
  horizontal_space
| new_line
;
}%%
