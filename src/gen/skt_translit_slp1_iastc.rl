%%{

machine skt_translit_slp1_iastc;

alphtype unsigned char;

# ā̀
action A0 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ò
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 178;
}
# aí
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# ṛ́
action A3 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# aì
action A4 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# à
action A5 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 160;
}
# l̥
action A6 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# L
action A7 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 76;
}
# ā́
action A8 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ai
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 105;
}
# kh
action A10 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 104;
}
# ̃
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 131;
}
# ḹ̀
action A12 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ṅ
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# r̥̄
action A14 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ḥ
action A15 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# ṃ
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# ṭh
action A17 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
   buf->data[buf->size++] = 104;
}
# th
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 116;
   buf->data[buf->size++] = 104;
}
# ī̀
action A19 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ḍ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# ī́
action A21 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ī
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# è
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 168;
}
# kṣ
action A24 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 107;
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# ṭ
action A25 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# ḻ
action A26 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 187;
}
# gh
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 103;
   buf->data[buf->size++] = 104;
}
# aù
action A28 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# ḷ́
action A29 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# í
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 173;
}
# ch
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 99;
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
# ḍh
action A33 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
   buf->data[buf->size++] = 104;
}
# l̥̄
action A34 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# aú
action A35 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}
# |
action A36 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 124;
}
# ù
action A37 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 185;
}
# ḷ̀
action A38 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ì
action A39 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 172;
}
# r̥
action A40 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# ā
action A41 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# é
action A42 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 169;
}
# ṝ̀
action A43 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# ñ
action A44 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ph
action A45 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 112;
   buf->data[buf->size++] = 104;
}
# ū́
action A46 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# dh
action A47 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 100;
   buf->data[buf->size++] = 104;
}
# ṇ
action A48 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# ||
action A49 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 124;
   buf->data[buf->size++] = 124;
}
# au
action A50 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 117;
}
# ḹ́
action A51 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 129;
}
# ū̀
action A52 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# bh
action A53 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 98;
   buf->data[buf->size++] = 104;
}
# jñ
action A54 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ṛ̀
action A55 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 128;
}
# jh
action A56 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 106;
   buf->data[buf->size++] = 104;
}
# ó
action A57 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 179;
}
# ṣ
action A58 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# á
action A59 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 161;
}
# ś
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ū
action A61 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# ḷh
action A62 {
   skt_buf_grow(buf, 4);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
   buf->data[buf->size++] = 104;
}
# ú
action A63 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 186;
}



main := |*
   "." => A36; # |
   ".." => A49; # ||
   "/A" => A8; # ā́
   "/E" => A2; # aí
   "/F" => A32; # ṝ́
   "/I" => A21; # ī́
   "/L" => A7; # L
   "/O" => A35; # aú
   "/U" => A46; # ū́
   "/X" => A51; # ḹ́
   "/a" => A59; # á
   "/e" => A42; # é
   "/f" => A3; # ṛ́
   "/i" => A30; # í
   "/o" => A57; # ó
   "/u" => A63; # ú
   "/x" => A29; # ḷ́
   "A" => A41; # ā
   "B" => A53; # bh
   "C" => A31; # ch
   "D" => A47; # dh
   "E" => A9; # ai
   "F" => A14; # r̥̄
   "G" => A27; # gh
   "H" => A15; # ḥ
   "I" => A22; # ī
   "J" => A56; # jh
   "K" => A10; # kh
   "L" => A26; # ḻ
   "M" => A16; # ṃ
   "N" => A13; # ṅ
   "O" => A50; # au
   "P" => A45; # ph
   "Q" => A33; # ḍh
   "R" => A48; # ṇ
   "S" => A60; # ś
   "T" => A18; # th
   "U" => A61; # ū
   "W" => A17; # ṭh
   "X" => A34; # l̥̄
   "Y" => A44; # ñ
   "^A" => A0; # ā̀
   "^E" => A4; # aì
   "^F" => A43; # ṝ̀
   "^I" => A19; # ī̀
   "^O" => A28; # aù
   "^U" => A52; # ū̀
   "^X" => A12; # ḹ̀
   "^a" => A5; # à
   "^e" => A23; # è
   "^f" => A55; # ṛ̀
   "^i" => A39; # ì
   "^o" => A1; # ò
   "^u" => A37; # ù
   "^x" => A38; # ḷ̀
   "`A" => A0; # ā̀
   "`E" => A4; # aì
   "`F" => A43; # ṝ̀
   "`I" => A19; # ī̀
   "`O" => A28; # aù
   "`U" => A52; # ū̀
   "`X" => A12; # ḹ̀
   "`a" => A5; # à
   "`e" => A23; # è
   "`f" => A55; # ṛ̀
   "`i" => A39; # ì
   "`o" => A1; # ò
   "`u" => A37; # ù
   "`x" => A38; # ḷ̀
   "f" => A40; # r̥
   "jY" => A54; # jñ
   "kz" => A24; # kṣ
   "q" => A20; # ḍ
   "w" => A25; # ṭ
   "x" => A6; # l̥
   "z" => A58; # ṣ
   "|" => A62; # ḷh
   "~" => A11; # ̃
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
