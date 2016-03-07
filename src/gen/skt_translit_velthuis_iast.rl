%%{

machine skt_translit_velthuis_iast;

alphtype unsigned char;

# ī
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# ḍ
action A1 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# Ḥ
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 164;
}
# Ū
action A3 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}
# ṇ
action A4 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# Ṣ
action A5 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 162;
}
# Ḍ
action A6 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 140;
}
# Ḹ
action A7 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 184;
}
# ṃ
action A8 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# ṛ
action A9 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}
# ṅ
action A10 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# Ṝ
action A11 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 156;
}
# ṭ
action A12 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# ṝ
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}
# ñ
action A14 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ṣ
action A15 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# Ṭ
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 172;
}
# ā
action A17 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# ḥ
action A18 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# Ñ
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 145;
}
# ś
action A20 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ḷ
action A21 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}
# ḹ
action A22 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}
# Ḷ
action A23 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 182;
}
# Ṇ
action A24 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 134;
}
# Ś
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 154;
}
# Ṛ
action A26 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 154;
}
# ṁ
action A27 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 129;
}
# Ī
action A28 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}
# Ṅ
action A29 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 132;
}
# Ṃ
action A30 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 130;
}
# ū
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# Ā
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}



main := |*
   ".D" => A6; # Ḍ
   ".H" => A2; # Ḥ
   ".L" => A23; # Ḷ
   ".LL" => A7; # Ḹ
   ".Ll" => A7; # Ḹ
   ".M" => A30; # Ṃ
   ".N" => A24; # Ṇ
   ".R" => A26; # Ṛ
   ".RR" => A11; # Ṝ
   ".Rr" => A11; # Ṝ
   ".S" => A5; # Ṣ
   ".T" => A16; # Ṭ
   ".d" => A1; # ḍ
   ".h" => A18; # ḥ
   ".l" => A21; # ḷ
   ".ll" => A22; # ḹ
   ".m" => A8; # ṃ
   ".n" => A4; # ṇ
   ".r" => A9; # ṛ
   ".rr" => A13; # ṝ
   ".s" => A15; # ṣ
   ".t" => A12; # ṭ
   "AA" => A32; # Ā
   "Aa" => A32; # Ā
   "F" => A29; # Ṅ
   "II" => A28; # Ī
   "Ii" => A28; # Ī
   "UU" => A3; # Ū
   "Uu" => A3; # Ū
   "Z" => A25; # Ś
   "aa" => A17; # ā
   "f" => A10; # ṅ
   "ii" => A0; # ī
   "uu" => A31; # ū
   "z" => A20; # ś
   "~N" => A19; # Ñ
   "~n" => A14; # ñ
   "~~" => A27; # ṁ
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_velthuis_iast(struct skt_buf *buf,
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
