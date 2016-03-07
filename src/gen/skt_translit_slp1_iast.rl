%%{

machine skt_translit_slp1_iast;

alphtype unsigned char;

# ú
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# aì
action A1 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# ḹ̀
action A2 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ā̀
action A3 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ||
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}
# ṛ́
action A5 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ṝ̀
action A6 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ḹ́
action A7 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḹ
action A8 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}
# ̃
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}
# ṝ́
action A10 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḷ̀
action A11 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ṛ̀
action A12 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# th
action A13 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}
# ā
action A14 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# ù
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# ṭh
action A16 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}
# ṃ
action A17 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# aù
action A18 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# á
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}
# ḻ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}
# jñ
action A21 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ó
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}
# ḥ
action A23 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# é
action A24 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}
# ò
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}
# ū
action A26 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# ū̀
action A27 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ḷh
action A28 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}
# ī́
action A29 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḷ
action A30 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}
# ṭ
action A31 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# dh
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}
# ū́
action A33 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# L
action A34 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# ḍ
action A35 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# ṇ
action A36 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# è
action A37 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}
# ch
action A38 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
   buf->data[buf->size++] = 104;
}
# kh
action A39 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}
# ṣ
action A40 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# ś
action A41 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ī̀
action A42 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ì
action A43 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# au
action A44 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}
# ḍh
action A45 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}
# gh
action A46 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}
# à
action A47 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}
# kṣ
action A48 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# jh
action A49 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}
# í
action A50 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# aú
action A51 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# ṛ
action A52 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}
# |
action A53 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# ai
action A54 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}
# bh
action A55 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}
# ḷ́
action A56 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ā́
action A57 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ṅ
action A58 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# ṝ
action A59 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}
# ñ
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ph
action A61 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}
# aí
action A62 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# ī
action A63 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}



main := |*
   "." => A53; # |
   ".." => A4; # ||
   "/A" => A57; # ā́
   "/E" => A62; # aí
   "/F" => A10; # ṝ́
   "/I" => A29; # ī́
   "/L" => A34; # L
   "/O" => A51; # aú
   "/U" => A33; # ū́
   "/X" => A7; # ḹ́
   "/a" => A19; # á
   "/e" => A24; # é
   "/f" => A5; # ṛ́
   "/i" => A50; # í
   "/o" => A22; # ó
   "/u" => A0; # ú
   "/x" => A56; # ḷ́
   "A" => A14; # ā
   "B" => A55; # bh
   "C" => A38; # ch
   "D" => A32; # dh
   "E" => A54; # ai
   "F" => A59; # ṝ
   "G" => A46; # gh
   "H" => A23; # ḥ
   "I" => A63; # ī
   "J" => A49; # jh
   "K" => A39; # kh
   "L" => A20; # ḻ
   "M" => A17; # ṃ
   "N" => A58; # ṅ
   "O" => A44; # au
   "P" => A61; # ph
   "Q" => A45; # ḍh
   "R" => A36; # ṇ
   "S" => A41; # ś
   "T" => A13; # th
   "U" => A26; # ū
   "W" => A16; # ṭh
   "X" => A8; # ḹ
   "Y" => A60; # ñ
   "^A" => A3; # ā̀
   "^E" => A1; # aì
   "^F" => A6; # ṝ̀
   "^I" => A42; # ī̀
   "^O" => A18; # aù
   "^U" => A27; # ū̀
   "^X" => A2; # ḹ̀
   "^a" => A47; # à
   "^e" => A37; # è
   "^f" => A12; # ṛ̀
   "^i" => A43; # ì
   "^o" => A25; # ò
   "^u" => A15; # ù
   "^x" => A11; # ḷ̀
   "`A" => A3; # ā̀
   "`E" => A1; # aì
   "`F" => A6; # ṝ̀
   "`I" => A42; # ī̀
   "`O" => A18; # aù
   "`U" => A27; # ū̀
   "`X" => A2; # ḹ̀
   "`a" => A47; # à
   "`e" => A37; # è
   "`f" => A12; # ṛ̀
   "`i" => A43; # ì
   "`o" => A25; # ò
   "`u" => A15; # ù
   "`x" => A11; # ḷ̀
   "f" => A52; # ṛ
   "jY" => A21; # jñ
   "kz" => A48; # kṣ
   "q" => A35; # ḍ
   "w" => A31; # ṭ
   "x" => A30; # ḷ
   "z" => A40; # ṣ
   "|" => A28; # ḷh
   "~" => A9; # ̃
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_slp1_iast(struct skt_buf *buf,
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
