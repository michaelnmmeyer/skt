%%{

machine skt_translit_slp1_iast;

alphtype unsigned char;

# jh
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}
# ḹ̀
action A1 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ò
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}
# ṛ
action A3 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}
# ḷ̀
action A4 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ī̀
action A5 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# í
action A6 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# ṭ
action A7 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# ñ
action A8 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# dh
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}
# ú
action A10 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# ̃
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}
# aù
action A12 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# ḹ́
action A13 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# aí
action A14 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# L
action A15 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# aú
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# ḷ́
action A17 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ū̀
action A18 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# aì
action A19 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# jñ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# è
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}
# ī
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# ā̀
action A23 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ṛ́
action A24 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḷ
action A25 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}
# ḷh
action A26 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}
# ṛ̀
action A27 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# |
action A28 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# á
action A29 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}
# ḍ
action A30 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# th
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}
# ṝ́
action A32 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ù
action A33 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# é
action A34 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}
# ā́
action A35 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ṝ̀
action A36 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ū
action A37 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# ṃ
action A38 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# à
action A39 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}
# ch
action A40 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
   buf->data[buf->size++] = 104;
}
# ì
action A41 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# kh
action A42 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}
# kṣ
action A43 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# ā
action A44 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# ph
action A45 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}
# ī́
action A46 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḥ
action A47 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# ḹ
action A48 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}
# ṭh
action A49 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}
# ó
action A50 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}
# ṣ
action A51 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# ai
action A52 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}
# gh
action A53 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}
# ||
action A54 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}
# ḻ
action A55 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}
# ś
action A56 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ḍh
action A57 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}
# ṝ
action A58 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}
# bh
action A59 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}
# ū́
action A60 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# au
action A61 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}
# ṅ
action A62 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# ṇ
action A63 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}



main := |*
   "." => A28; # |
   ".." => A54; # ||
   "/A" => A35; # ā́
   "/E" => A14; # aí
   "/F" => A32; # ṝ́
   "/I" => A46; # ī́
   "/L" => A15; # L
   "/O" => A16; # aú
   "/U" => A60; # ū́
   "/X" => A13; # ḹ́
   "/a" => A29; # á
   "/e" => A34; # é
   "/f" => A24; # ṛ́
   "/i" => A6; # í
   "/o" => A50; # ó
   "/u" => A10; # ú
   "/x" => A17; # ḷ́
   "A" => A44; # ā
   "B" => A59; # bh
   "C" => A40; # ch
   "D" => A9; # dh
   "E" => A52; # ai
   "F" => A58; # ṝ
   "G" => A53; # gh
   "H" => A47; # ḥ
   "I" => A22; # ī
   "J" => A0; # jh
   "K" => A42; # kh
   "L" => A55; # ḻ
   "M" => A38; # ṃ
   "N" => A62; # ṅ
   "O" => A61; # au
   "P" => A45; # ph
   "Q" => A57; # ḍh
   "R" => A63; # ṇ
   "S" => A56; # ś
   "T" => A31; # th
   "U" => A37; # ū
   "W" => A49; # ṭh
   "X" => A48; # ḹ
   "Y" => A8; # ñ
   "^A" => A23; # ā̀
   "^E" => A19; # aì
   "^F" => A36; # ṝ̀
   "^I" => A5; # ī̀
   "^O" => A12; # aù
   "^U" => A18; # ū̀
   "^X" => A1; # ḹ̀
   "^a" => A39; # à
   "^e" => A21; # è
   "^f" => A27; # ṛ̀
   "^i" => A41; # ì
   "^o" => A2; # ò
   "^u" => A33; # ù
   "^x" => A4; # ḷ̀
   "`A" => A23; # ā̀
   "`E" => A19; # aì
   "`F" => A36; # ṝ̀
   "`I" => A5; # ī̀
   "`O" => A12; # aù
   "`U" => A18; # ū̀
   "`X" => A1; # ḹ̀
   "`a" => A39; # à
   "`e" => A21; # è
   "`f" => A27; # ṛ̀
   "`i" => A41; # ì
   "`o" => A2; # ò
   "`u" => A33; # ù
   "`x" => A4; # ḷ̀
   "f" => A3; # ṛ
   "jY" => A20; # jñ
   "kz" => A43; # kṣ
   "q" => A30; # ḍ
   "w" => A7; # ṭ
   "x" => A25; # ḷ
   "z" => A51; # ṣ
   "|" => A26; # ḷh
   "~" => A11; # ̃
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