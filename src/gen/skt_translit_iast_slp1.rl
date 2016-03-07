%%{

machine skt_translit_iast_slp1;

alphtype unsigned char;

# /U
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 85;
}
# ..
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 46;
}
# /F
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 70;
}
# ^I
action A3 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 73;
}
# t
action A4 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 116;
}
# ^a
action A5 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 97;
}
# q
action A6 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 113;
}
# I
action A7 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}
# D
action A8 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}
# /E
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}
# B
action A10 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}
# u
action A11 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 117;
}
# M
action A12 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 77;
}
# L
action A13 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# U
action A14 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}
# F
action A15 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}
# Q
action A16 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}
# /e
action A17 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 101;
}
# Y
action A18 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 89;
}
# ^E
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}
# f
action A20 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}
# ^i
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 105;
}
# /f
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 102;
}
# s
action A23 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 115;
}
# g
action A24 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 103;
}
# p
action A25 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 112;
}
# k
action A26 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 107;
}
# A
action A27 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}
# y
action A28 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 121;
}
# w
action A29 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 119;
}
# G
action A30 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}
# ^f
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 102;
}
# /x
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 120;
}
# P
action A33 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}
# /I
action A34 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 73;
}
# J
action A35 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}
# ^A
action A36 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 65;
}
# z
action A37 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}
# /i
action A38 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 105;
}
# C
action A39 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}
# T
action A40 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}
# X
action A41 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}
# K
action A42 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}
# /A
action A43 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 65;
}
# h
action A44 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 104;
}
# |
action A45 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# N
action A46 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 78;
}
# ^F
action A47 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 70;
}
# E
action A48 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}
# W
action A49 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}
# x
action A50 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}
# ^O
action A51 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}
# ^o
action A52 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 111;
}
# /X
action A53 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 88;
}
# o
action A54 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 111;
}
# c
action A55 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 99;
}
# m
action A56 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 109;
}
# S
action A57 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 83;
}
# O
action A58 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}
# ^X
action A59 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 88;
}
# /O
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}
# i
action A61 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 105;
}
# ~
action A62 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 126;
}
# ^x
action A63 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 120;
}
# j
action A64 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 106;
}
# ^u
action A65 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 117;
}
# H
action A66 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 72;
}
# .
action A67 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 46;
}
# /a
action A68 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 97;
}
# r
action A69 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 114;
}
# ^U
action A70 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 85;
}
# R
action A71 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 82;
}
# v
action A72 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 118;
}
# /u
action A73 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 117;
}
# ^e
action A74 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 101;
}
# n
action A75 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 110;
}
# /L
action A76 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 76;
}
# /o
action A77 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 111;
}
# a
action A78 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 97;
}
# d
action A79 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 100;
}
# e
action A80 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 101;
}
# b
action A81 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 98;
}



main := |*
   "A" => A78; # a
   "AI" => A48; # E
   "AU" => A58; # O
   "Ai" => A48; # E
   "Au" => A58; # O
   "AÌ" => A19; # ^E
   "AÍ" => A9; # /E
   "AÙ" => A51; # ^O
   "AÚ" => A60; # /O
   "Aì" => A19; # ^E
   "Aí" => A9; # /E
   "Aù" => A51; # ^O
   "Aú" => A60; # /O
   "B" => A81; # b
   "BH" => A10; # B
   "Bh" => A10; # B
   "C" => A55; # c
   "CH" => A39; # C
   "Ch" => A39; # C
   "D" => A79; # d
   "DH" => A8; # D
   "Dh" => A8; # D
   "E" => A80; # e
   "G" => A24; # g
   "GH" => A30; # G
   "Gh" => A30; # G
   "H" => A44; # h
   "I" => A61; # i
   "J" => A64; # j
   "JH" => A35; # J
   "Jh" => A35; # J
   "K" => A26; # k
   "KH" => A42; # K
   "Kh" => A42; # K
   "L" => A76; # /L
   "L̥" => A50; # x
   "L̥̄" => A41; # X
   "M" => A56; # m
   "N" => A75; # n
   "O" => A54; # o
   "P" => A25; # p
   "PH" => A33; # P
   "Ph" => A33; # P
   "R" => A69; # r
   "R̥" => A20; # f
   "R̥̄" => A15; # F
   "S" => A23; # s
   "T" => A4; # t
   "TH" => A40; # T
   "Th" => A40; # T
   "U" => A11; # u
   "V" => A72; # v
   "Y" => A28; # y
   "aI" => A48; # E
   "aU" => A58; # O
   "ai" => A48; # E
   "au" => A58; # O
   "aÌ" => A19; # ^E
   "aÍ" => A9; # /E
   "aÙ" => A51; # ^O
   "aÚ" => A60; # /O
   "aì" => A19; # ^E
   "aí" => A9; # /E
   "aù" => A51; # ^O
   "aú" => A60; # /O
   "bH" => A10; # B
   "bh" => A10; # B
   "cH" => A39; # C
   "ch" => A39; # C
   "dH" => A8; # D
   "dh" => A8; # D
   "gH" => A30; # G
   "gh" => A30; # G
   "jH" => A35; # J
   "jh" => A35; # J
   "kH" => A42; # K
   "kh" => A42; # K
   "l̥" => A50; # x
   "l̥̄" => A41; # X
   "pH" => A33; # P
   "ph" => A33; # P
   "r̥" => A20; # f
   "r̥̄" => A15; # F
   "tH" => A40; # T
   "th" => A40; # T
   "|" => A67; # .
   "||" => A1; # ..
   "À" => A5; # ^a
   "Á" => A68; # /a
   "È" => A74; # ^e
   "É" => A17; # /e
   "Ì" => A21; # ^i
   "Í" => A38; # /i
   "Ñ" => A18; # Y
   "Ò" => A52; # ^o
   "Ó" => A77; # /o
   "Ù" => A65; # ^u
   "Ú" => A73; # /u
   "à" => A5; # ^a
   "á" => A68; # /a
   "è" => A74; # ^e
   "é" => A17; # /e
   "ì" => A21; # ^i
   "í" => A38; # /i
   "ñ" => A18; # Y
   "ò" => A52; # ^o
   "ó" => A77; # /o
   "ù" => A65; # ^u
   "ú" => A73; # /u
   "Ā" => A27; # A
   "Ā̀" => A36; # ^A
   "Ā́" => A43; # /A
   "ā" => A27; # A
   "ā̀" => A36; # ^A
   "ā́" => A43; # /A
   "Ī" => A7; # I
   "Ī̀" => A3; # ^I
   "Ī́" => A34; # /I
   "ī" => A7; # I
   "ī̀" => A3; # ^I
   "ī́" => A34; # /I
   "Ś" => A57; # S
   "ś" => A57; # S
   "Ū" => A14; # U
   "Ū̀" => A70; # ^U
   "Ū́" => A0; # /U
   "ū" => A14; # U
   "ū̀" => A70; # ^U
   "ū́" => A0; # /U
   "̃" => A62; # ~
   "Ḍ" => A6; # q
   "ḌH" => A16; # Q
   "Ḍh" => A16; # Q
   "ḍ" => A6; # q
   "ḍH" => A16; # Q
   "ḍh" => A16; # Q
   "Ḥ" => A66; # H
   "ḥ" => A66; # H
   "Ḷ" => A50; # x
   "ḶH" => A45; # |
   "Ḷh" => A45; # |
   "Ḷ̀" => A63; # ^x
   "Ḷ́" => A32; # /x
   "ḷ" => A50; # x
   "ḷH" => A45; # |
   "ḷh" => A45; # |
   "ḷ̀" => A63; # ^x
   "ḷ́" => A32; # /x
   "Ḹ" => A41; # X
   "Ḹ̀" => A59; # ^X
   "Ḹ́" => A53; # /X
   "ḹ" => A41; # X
   "ḹ̀" => A59; # ^X
   "ḹ́" => A53; # /X
   "Ḻ" => A13; # L
   "ḻ" => A13; # L
   "Ṃ" => A12; # M
   "ṃ" => A12; # M
   "Ṅ" => A46; # N
   "ṅ" => A46; # N
   "Ṇ" => A71; # R
   "ṇ" => A71; # R
   "Ṛ" => A20; # f
   "Ṛ̀" => A31; # ^f
   "Ṛ́" => A22; # /f
   "ṛ" => A20; # f
   "ṛ̀" => A31; # ^f
   "ṛ́" => A22; # /f
   "Ṝ" => A15; # F
   "Ṝ̀" => A47; # ^F
   "Ṝ́" => A2; # /F
   "ṝ" => A15; # F
   "ṝ̀" => A47; # ^F
   "ṝ́" => A2; # /F
   "Ṣ" => A37; # z
   "ṣ" => A37; # z
   "Ṭ" => A29; # w
   "ṬH" => A49; # W
   "Ṭh" => A49; # W
   "ṭ" => A29; # w
   "ṭH" => A49; # W
   "ṭh" => A49; # W
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_iast_slp1(struct skt_buf *buf,
                           const char *str, size_t len)
{
   int cs, act;
   const unsigned char *ts, *te;
   const unsigned char *p = (const unsigned char *)str;
   const unsigned char *pe = &p[len];
   const unsigned char *const eof = pe;

   buf->size = 0;
   %% write data;
   %% write init;
   %% write exec;

   skt_buf_truncate(buf, buf->size);
}
