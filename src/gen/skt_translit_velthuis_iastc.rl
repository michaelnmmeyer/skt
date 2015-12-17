%%{

machine skt_translit_velthuis_iastc;

alphtype unsigned char;

# ṅ
action A0 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# ś
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}
# ṣ
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# r̥̄
action A3 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# R̥
action A4 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# Ś
action A5 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 154;
}
# L̥
action A6 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# Ī
action A7 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}
# ā
action A8 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# r̥
action A9 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# Ḍ
action A10 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 140;
}
# Ṇ
action A11 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 134;
}
# Ā
action A12 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}
# Ṃ
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 130;
}
# Ṭ
action A14 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 172;
}
# Ū
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}
# R̥̄
action A16 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ṁ
action A17 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 129;
}
# Ñ
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 145;
}
# L̥̄
action A19 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ḍ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# l̥̄
action A21 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ṃ
action A22 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# ū
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# l̥
action A24 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# ḥ
action A25 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# ṭ
action A26 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# ṇ
action A27 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# Ṅ
action A28 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 132;
}
# Ḥ
action A29 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 164;
}
# ī
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# Ṣ
action A31 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 162;
}
# ñ
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}



main := |*
   ".D" => A10; # Ḍ
   ".H" => A29; # Ḥ
   ".L" => A6; # L̥
   ".LL" => A19; # L̥̄
   ".Ll" => A19; # L̥̄
   ".M" => A13; # Ṃ
   ".N" => A11; # Ṇ
   ".R" => A4; # R̥
   ".RR" => A16; # R̥̄
   ".Rr" => A16; # R̥̄
   ".S" => A31; # Ṣ
   ".T" => A14; # Ṭ
   ".d" => A20; # ḍ
   ".h" => A25; # ḥ
   ".l" => A24; # l̥
   ".ll" => A21; # l̥̄
   ".m" => A22; # ṃ
   ".n" => A27; # ṇ
   ".r" => A9; # r̥
   ".rr" => A3; # r̥̄
   ".s" => A2; # ṣ
   ".t" => A26; # ṭ
   "AA" => A12; # Ā
   "Aa" => A12; # Ā
   "F" => A28; # Ṅ
   "II" => A7; # Ī
   "Ii" => A7; # Ī
   "UU" => A15; # Ū
   "Uu" => A15; # Ū
   "Z" => A5; # Ś
   "aa" => A8; # ā
   "f" => A0; # ṅ
   "ii" => A30; # ī
   "uu" => A23; # ū
   "z" => A1; # ś
   "~N" => A18; # Ñ
   "~n" => A32; # ñ
   "~~" => A17; # ṁ
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_velthuis_iastc(struct skt_buf *buf,
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