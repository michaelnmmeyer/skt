%%{

machine skt_translit_iast_slp1;

alphtype unsigned char;

# Y
action A0 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 89;
}
# ^U
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 85;
}
# ^x
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 120;
}
# P
action A3 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 80;
}
# ^A
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 65;
}
# e
action A5 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 101;
}
# /u
action A6 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 117;
}
# W
action A7 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 87;
}
# E
action A8 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 69;
}
# /E
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 69;
}
# S
action A10 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 83;
}
# ^I
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 73;
}
# I
action A12 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 73;
}
# .
action A13 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 46;
}
# /X
action A14 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 88;
}
# /e
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 101;
}
# C
action A16 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 67;
}
# D
action A17 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 68;
}
# ^O
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 79;
}
# T
action A19 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 84;
}
# /a
action A20 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 97;
}
# X
action A21 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 88;
}
# /o
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 111;
}
# ^u
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 117;
}
# q
action A24 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 113;
}
# O
action A25 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 79;
}
# N
action A26 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 78;
}
# /F
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 70;
}
# G
action A28 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 71;
}
# d
action A29 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 100;
}
# R
action A30 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 82;
}
# b
action A31 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 98;
}
# ^E
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 69;
}
# /x
action A33 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 120;
}
# B
action A34 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 66;
}
# x
action A35 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 120;
}
# r
action A36 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 114;
}
# L
action A37 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# ..
action A38 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 46;
}
# /i
action A39 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 105;
}
# /f
action A40 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 102;
}
# K
action A41 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 75;
}
# w
action A42 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 119;
}
# Q
action A43 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 81;
}
# s
action A44 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 115;
}
# z
action A45 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}
# F
action A46 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}
# u
action A47 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 117;
}
# f
action A48 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}
# /O
action A49 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 79;
}
# ^o
action A50 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 111;
}
# n
action A51 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 110;
}
# a
action A52 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 97;
}
# t
action A53 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 116;
}
# H
action A54 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 72;
}
# k
action A55 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 107;
}
# v
action A56 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 118;
}
# ^F
action A57 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 70;
}
# J
action A58 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 74;
}
# |
action A59 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# ^e
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 101;
}
# i
action A61 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 105;
}
# A
action A62 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 65;
}
# c
action A63 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 99;
}
# y
action A64 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 121;
}
# M
action A65 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 77;
}
# h
action A66 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 104;
}
# ^i
action A67 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 105;
}
# /U
action A68 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 85;
}
# /A
action A69 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 65;
}
# U
action A70 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 85;
}
# ^X
action A71 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 88;
}
# p
action A72 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 112;
}
# o
action A73 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 111;
}
# ^a
action A74 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 97;
}
# m
action A75 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 109;
}
# /I
action A76 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 73;
}
# j
action A77 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 106;
}
# /L
action A78 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 76;
}
# ^f
action A79 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 94;
   buf->data[buf->size++] = 102;
}
# ~
action A80 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 126;
}
# g
action A81 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 103;
}



main := |*
   "A" => A52; # a
   "AI" => A8; # E
   "AU" => A25; # O
   "Ai" => A8; # E
   "Au" => A25; # O
   "AÌ" => A32; # ^E
   "AÍ" => A9; # /E
   "AÙ" => A18; # ^O
   "AÚ" => A49; # /O
   "Aì" => A32; # ^E
   "Aí" => A9; # /E
   "Aù" => A18; # ^O
   "Aú" => A49; # /O
   "B" => A31; # b
   "BH" => A34; # B
   "Bh" => A34; # B
   "C" => A63; # c
   "CH" => A16; # C
   "Ch" => A16; # C
   "D" => A29; # d
   "DH" => A17; # D
   "Dh" => A17; # D
   "E" => A5; # e
   "G" => A81; # g
   "GH" => A28; # G
   "Gh" => A28; # G
   "H" => A66; # h
   "I" => A61; # i
   "J" => A77; # j
   "JH" => A58; # J
   "Jh" => A58; # J
   "K" => A55; # k
   "KH" => A41; # K
   "Kh" => A41; # K
   "L" => A78; # /L
   "L̥" => A35; # x
   "L̥̄" => A21; # X
   "M" => A75; # m
   "N" => A51; # n
   "O" => A73; # o
   "P" => A72; # p
   "PH" => A3; # P
   "Ph" => A3; # P
   "R" => A36; # r
   "R̥" => A48; # f
   "R̥̄" => A46; # F
   "S" => A44; # s
   "T" => A53; # t
   "TH" => A19; # T
   "Th" => A19; # T
   "U" => A47; # u
   "V" => A56; # v
   "Y" => A64; # y
   "aI" => A8; # E
   "aU" => A25; # O
   "ai" => A8; # E
   "au" => A25; # O
   "aÌ" => A32; # ^E
   "aÍ" => A9; # /E
   "aÙ" => A18; # ^O
   "aÚ" => A49; # /O
   "aì" => A32; # ^E
   "aí" => A9; # /E
   "aù" => A18; # ^O
   "aú" => A49; # /O
   "bH" => A34; # B
   "bh" => A34; # B
   "cH" => A16; # C
   "ch" => A16; # C
   "dH" => A17; # D
   "dh" => A17; # D
   "gH" => A28; # G
   "gh" => A28; # G
   "jH" => A58; # J
   "jh" => A58; # J
   "kH" => A41; # K
   "kh" => A41; # K
   "l̥" => A35; # x
   "l̥̄" => A21; # X
   "pH" => A3; # P
   "ph" => A3; # P
   "r̥" => A48; # f
   "r̥̄" => A46; # F
   "tH" => A19; # T
   "th" => A19; # T
   "|" => A13; # .
   "||" => A38; # ..
   "À" => A74; # ^a
   "Á" => A20; # /a
   "È" => A60; # ^e
   "É" => A15; # /e
   "Ì" => A67; # ^i
   "Í" => A39; # /i
   "Ñ" => A0; # Y
   "Ò" => A50; # ^o
   "Ó" => A22; # /o
   "Ù" => A23; # ^u
   "Ú" => A6; # /u
   "à" => A74; # ^a
   "á" => A20; # /a
   "è" => A60; # ^e
   "é" => A15; # /e
   "ì" => A67; # ^i
   "í" => A39; # /i
   "ñ" => A0; # Y
   "ò" => A50; # ^o
   "ó" => A22; # /o
   "ù" => A23; # ^u
   "ú" => A6; # /u
   "Ā" => A62; # A
   "Ā̀" => A4; # ^A
   "Ā́" => A69; # /A
   "ā" => A62; # A
   "ā̀" => A4; # ^A
   "ā́" => A69; # /A
   "Ī" => A12; # I
   "Ī̀" => A11; # ^I
   "Ī́" => A76; # /I
   "ī" => A12; # I
   "ī̀" => A11; # ^I
   "ī́" => A76; # /I
   "Ś" => A10; # S
   "ś" => A10; # S
   "Ū" => A70; # U
   "Ū̀" => A1; # ^U
   "Ū́" => A68; # /U
   "ū" => A70; # U
   "ū̀" => A1; # ^U
   "ū́" => A68; # /U
   "̃" => A80; # ~
   "Ḍ" => A24; # q
   "ḌH" => A43; # Q
   "Ḍh" => A43; # Q
   "ḍ" => A24; # q
   "ḍH" => A43; # Q
   "ḍh" => A43; # Q
   "Ḥ" => A54; # H
   "ḥ" => A54; # H
   "Ḷ" => A35; # x
   "ḶH" => A59; # |
   "Ḷh" => A59; # |
   "Ḷ̀" => A2; # ^x
   "Ḷ́" => A33; # /x
   "ḷ" => A35; # x
   "ḷH" => A59; # |
   "ḷh" => A59; # |
   "ḷ̀" => A2; # ^x
   "ḷ́" => A33; # /x
   "Ḹ" => A21; # X
   "Ḹ̀" => A71; # ^X
   "Ḹ́" => A14; # /X
   "ḹ" => A21; # X
   "ḹ̀" => A71; # ^X
   "ḹ́" => A14; # /X
   "Ḻ" => A37; # L
   "ḻ" => A37; # L
   "Ṃ" => A65; # M
   "ṃ" => A65; # M
   "Ṅ" => A26; # N
   "ṅ" => A26; # N
   "Ṇ" => A30; # R
   "ṇ" => A30; # R
   "Ṛ" => A48; # f
   "Ṛ̀" => A79; # ^f
   "Ṛ́" => A40; # /f
   "ṛ" => A48; # f
   "ṛ̀" => A79; # ^f
   "ṛ́" => A40; # /f
   "Ṝ" => A46; # F
   "Ṝ̀" => A57; # ^F
   "Ṝ́" => A27; # /F
   "ṝ" => A46; # F
   "ṝ̀" => A57; # ^F
   "ṝ́" => A27; # /F
   "Ṣ" => A45; # z
   "ṣ" => A45; # z
   "Ṭ" => A42; # w
   "ṬH" => A7; # W
   "Ṭh" => A7; # W
   "ṭ" => A42; # w
   "ṭH" => A7; # W
   "ṭh" => A7; # W
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