%%{

machine skt_translit_iast_velthuis;

alphtype unsigned char;

# .r
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
}
# ~N
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 78;
}
# ~~
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 126;
}
# .R
action A3 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
}
# .M
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 77;
}
# .N
action A5 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 78;
}
# .S
action A6 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 83;
}
# .h
action A7 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 104;
}
# .Ll
action A8 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 108;
}
# uu
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 117;
   buf->data[buf->size++] = 117;
}
# .rr
action A10 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 114;
}
# .l
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
}
# .T
action A12 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 84;
}
# .ll
action A13 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 108;
}
# z
action A14 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}
# Ii
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 73;
   buf->data[buf->size++] = 105;
}
# .Rr
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 114;
}
# f
action A17 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}
# Aa
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 65;
   buf->data[buf->size++] = 97;
}
# Z
action A19 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 90;
}
# .H
action A20 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 72;
}
# .s
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 115;
}
# .t
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 116;
}
# aa
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 97;
}
# .L
action A24 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
}
# .d
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 100;
}
# F
action A26 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}
# Uu
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 85;
   buf->data[buf->size++] = 117;
}
# .m
action A28 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 109;
}
# ii
action A29 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 105;
   buf->data[buf->size++] = 105;
}
# .n
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 110;
}
# ~n
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 110;
}
# .D
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 68;
}



main := |*
   "L̥" => A24; # .L
   "L̥̄" => A8; # .Ll
   "R̥" => A3; # .R
   "R̥̄" => A16; # .Rr
   "l̥" => A11; # .l
   "l̥̄" => A13; # .ll
   "r̥" => A0; # .r
   "r̥̄" => A10; # .rr
   "Ñ" => A1; # ~N
   "ñ" => A31; # ~n
   "Ā" => A18; # Aa
   "ā" => A23; # aa
   "Ī" => A15; # Ii
   "ī" => A29; # ii
   "Ś" => A19; # Z
   "ś" => A14; # z
   "Ū" => A27; # Uu
   "ū" => A9; # uu
   "Ḍ" => A32; # .D
   "ḍ" => A25; # .d
   "Ḥ" => A20; # .H
   "ḥ" => A7; # .h
   "Ḷ" => A24; # .L
   "ḷ" => A11; # .l
   "Ḹ" => A8; # .Ll
   "ḹ" => A13; # .ll
   "Ṁ" => A2; # ~~
   "ṁ" => A2; # ~~
   "Ṃ" => A4; # .M
   "ṃ" => A28; # .m
   "Ṅ" => A26; # F
   "ṅ" => A17; # f
   "Ṇ" => A5; # .N
   "ṇ" => A30; # .n
   "Ṛ" => A3; # .R
   "ṛ" => A0; # .r
   "Ṝ" => A16; # .Rr
   "ṝ" => A10; # .rr
   "Ṣ" => A6; # .S
   "ṣ" => A21; # .s
   "Ṭ" => A12; # .T
   "ṭ" => A22; # .t
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_iast_velthuis(struct skt_buf *buf,
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
