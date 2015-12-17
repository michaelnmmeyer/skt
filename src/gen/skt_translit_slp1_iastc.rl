%%{

machine skt_translit_slp1_iastc;

alphtype unsigned char;

# ṣ
action A0 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# aú
action A1 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
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
# ṭh
action A3 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}
# ù
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# aí
action A5 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
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
# ī́
action A7 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ū
action A8 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# r̥
action A9 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# ò
action A10 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
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
# ṇ
action A12 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# aù
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# bh
action A14 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}
# jh
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}
# ì
action A16 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# ā
action A17 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# aì
action A18 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# é
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}
# ch
action A20 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
   buf->data[buf->size++] = 104;
}
# ̃
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}
# à
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}
# ī̀
action A23 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ṅ
action A24 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# ā̀
action A25 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# á
action A26 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}
# è
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}
# ś
action A28 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ṭ
action A29 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# kh
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}
# ā́
action A31 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ph
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}
# ḷh
action A33 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}
# gh
action A34 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}
# ṛ̀
action A35 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ||
action A36 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}
# ḻ
action A37 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}
# |
action A38 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# ḷ́
action A39 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# r̥̄
action A40 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ñ
action A41 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# dh
action A42 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}
# jñ
action A43 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ó
action A44 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}
# ḍh
action A45 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}
# ū̀
action A46 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ṃ
action A47 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# ī
action A48 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# kṣ
action A49 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# ṛ́
action A50 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ú
action A51 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# ṝ́
action A52 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ḥ
action A53 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# au
action A54 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}
# ai
action A55 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}
# l̥̄
action A56 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ḹ́
action A57 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# L
action A58 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# l̥
action A59 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# í
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# th
action A61 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}
# ḍ
action A62 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# ū́
action A63 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}



main := |*
   "." => A38; # |
   ".." => A36; # ||
   "/A" => A31; # ā́
   "/E" => A5; # aí
   "/F" => A52; # ṝ́
   "/I" => A7; # ī́
   "/L" => A58; # L
   "/O" => A1; # aú
   "/U" => A63; # ū́
   "/X" => A57; # ḹ́
   "/a" => A26; # á
   "/e" => A19; # é
   "/f" => A50; # ṛ́
   "/i" => A60; # í
   "/o" => A44; # ó
   "/u" => A51; # ú
   "/x" => A39; # ḷ́
   "A" => A17; # ā
   "B" => A14; # bh
   "C" => A20; # ch
   "D" => A42; # dh
   "E" => A55; # ai
   "F" => A40; # r̥̄
   "G" => A34; # gh
   "H" => A53; # ḥ
   "I" => A48; # ī
   "J" => A15; # jh
   "K" => A30; # kh
   "L" => A37; # ḻ
   "M" => A47; # ṃ
   "N" => A24; # ṅ
   "O" => A54; # au
   "P" => A32; # ph
   "Q" => A45; # ḍh
   "R" => A12; # ṇ
   "S" => A28; # ś
   "T" => A61; # th
   "U" => A8; # ū
   "W" => A3; # ṭh
   "X" => A56; # l̥̄
   "Y" => A41; # ñ
   "^A" => A25; # ā̀
   "^E" => A18; # aì
   "^F" => A6; # ṝ̀
   "^I" => A23; # ī̀
   "^O" => A13; # aù
   "^U" => A46; # ū̀
   "^X" => A2; # ḹ̀
   "^a" => A22; # à
   "^e" => A27; # è
   "^f" => A35; # ṛ̀
   "^i" => A16; # ì
   "^o" => A10; # ò
   "^u" => A4; # ù
   "^x" => A11; # ḷ̀
   "`A" => A25; # ā̀
   "`E" => A18; # aì
   "`F" => A6; # ṝ̀
   "`I" => A23; # ī̀
   "`O" => A13; # aù
   "`U" => A46; # ū̀
   "`X" => A2; # ḹ̀
   "`a" => A22; # à
   "`e" => A27; # è
   "`f" => A35; # ṛ̀
   "`i" => A16; # ì
   "`o" => A10; # ò
   "`u" => A4; # ù
   "`x" => A11; # ḷ̀
   "f" => A9; # r̥
   "jY" => A43; # jñ
   "kz" => A49; # kṣ
   "q" => A62; # ḍ
   "w" => A29; # ṭ
   "x" => A59; # l̥
   "z" => A0; # ṣ
   "|" => A33; # ḷh
   "~" => A21; # ̃
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_slp1_iastc(struct skt_buf *buf,
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