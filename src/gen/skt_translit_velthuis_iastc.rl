%%{

machine skt_translit_velthuis_iastc;

alphtype unsigned char;

# Ñ
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 145;
}
# Ā
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 128;
}
# Ī
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 170;
}
# L̥
action A3 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# Ś
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 154;
}
# ṃ
action A5 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 131;
}
# L̥̄
action A6 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# Ṭ
action A7 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 172;
}
# ḥ
action A8 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 165;
}
# r̥
action A9 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# l̥̄
action A10 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# ḍ
action A11 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 141;
}
# R̥̄
action A12 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# l̥
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# Ṅ
action A14 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 132;
}
# ṇ
action A15 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 135;
}
# Ṃ
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 130;
}
# Ṇ
action A17 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 134;
}
# ṭ
action A18 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 173;
}
# ā
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 129;
}
# Ḍ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 140;
}
# ṣ
action A21 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 163;
}
# Ṣ
action A22 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 162;
}
# ū
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 171;
}
# r̥̄
action A24 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# Ū
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 170;
}
# ñ
action A26 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 195;
   buf->data[buf->size++] = 177;
}
# ṅ
action A27 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 133;
}
# Ḥ
action A28 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 164;
}
# R̥
action A29 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# ī
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 196;
   buf->data[buf->size++] = 171;
}
# ṁ
action A31 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 129;
}
# ś
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 197;
   buf->data[buf->size++] = 155;
}



main := |*
   ".D" => A20; # Ḍ
   ".H" => A28; # Ḥ
   ".L" => A3; # L̥
   ".LL" => A6; # L̥̄
   ".Ll" => A6; # L̥̄
   ".M" => A16; # Ṃ
   ".N" => A17; # Ṇ
   ".R" => A29; # R̥
   ".RR" => A12; # R̥̄
   ".Rr" => A12; # R̥̄
   ".S" => A22; # Ṣ
   ".T" => A7; # Ṭ
   ".d" => A11; # ḍ
   ".h" => A8; # ḥ
   ".l" => A13; # l̥
   ".ll" => A10; # l̥̄
   ".m" => A5; # ṃ
   ".n" => A15; # ṇ
   ".r" => A9; # r̥
   ".rr" => A24; # r̥̄
   ".s" => A21; # ṣ
   ".t" => A18; # ṭ
   "AA" => A1; # Ā
   "Aa" => A1; # Ā
   "F" => A14; # Ṅ
   "II" => A2; # Ī
   "Ii" => A2; # Ī
   "UU" => A25; # Ū
   "Uu" => A25; # Ū
   "Z" => A4; # Ś
   "aa" => A19; # ā
   "f" => A27; # ṅ
   "ii" => A30; # ī
   "uu" => A23; # ū
   "z" => A32; # ś
   "~N" => A0; # Ñ
   "~n" => A26; # ñ
   "~~" => A31; # ṁ
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