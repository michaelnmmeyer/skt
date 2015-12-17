%%{

machine skt_translit_iast_velthuis;

alphtype unsigned char;

# .m
action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 109;
}
# aa
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 97;
   buf->data[buf->size++] = 97;
}
# .l
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 108;
}
# .Rr
action A3 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 114;
}
# Ii
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 73;
   buf->data[buf->size++] = 105;
}
# .rr
action A5 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 114;
}
# uu
action A6 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 117;
   buf->data[buf->size++] = 117;
}
# .M
action A7 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 77;
}
# .r
action A8 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 114;
}
# ~~
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 126;
}
# .R
action A10 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 82;
}
# ~n
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 110;
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
# .Ll
action A14 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 108;
}
# .D
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 68;
}
# z
action A16 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 122;
}
# F
action A17 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 70;
}
# .L
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 76;
}
# Z
action A19 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 90;
}
# f
action A20 {
   skt_buf_grow(buf, 1);
   buf->data[buf->size++] = 102;
}
# .S
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 83;
}
# ~N
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 126;
   buf->data[buf->size++] = 78;
}
# Uu
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 85;
   buf->data[buf->size++] = 117;
}
# Aa
action A24 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 65;
   buf->data[buf->size++] = 97;
}
# .t
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 116;
}
# .h
action A26 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 104;
}
# .n
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 110;
}
# .s
action A28 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 115;
}
# .d
action A29 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 100;
}
# .N
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 78;
}
# ii
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 105;
   buf->data[buf->size++] = 105;
}
# .H
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 72;
}



main := |*
   "L̥" => A18; # .L
   "L̥̄" => A14; # .Ll
   "R̥" => A10; # .R
   "R̥̄" => A3; # .Rr
   "l̥" => A2; # .l
   "l̥̄" => A13; # .ll
   "r̥" => A8; # .r
   "r̥̄" => A5; # .rr
   "Ñ" => A22; # ~N
   "ñ" => A11; # ~n
   "Ā" => A24; # Aa
   "ā" => A1; # aa
   "Ī" => A4; # Ii
   "ī" => A31; # ii
   "Ś" => A19; # Z
   "ś" => A16; # z
   "Ū" => A23; # Uu
   "ū" => A6; # uu
   "Ḍ" => A15; # .D
   "ḍ" => A29; # .d
   "Ḥ" => A32; # .H
   "ḥ" => A26; # .h
   "Ḷ" => A18; # .L
   "ḷ" => A2; # .l
   "Ḹ" => A14; # .Ll
   "ḹ" => A13; # .ll
   "Ṁ" => A9; # ~~
   "ṁ" => A9; # ~~
   "Ṃ" => A7; # .M
   "ṃ" => A0; # .m
   "Ṅ" => A17; # F
   "ṅ" => A20; # f
   "Ṇ" => A30; # .N
   "ṇ" => A27; # .n
   "Ṛ" => A10; # .R
   "ṛ" => A8; # .r
   "Ṝ" => A3; # .Rr
   "ṝ" => A5; # .rr
   "Ṣ" => A21; # .S
   "ṣ" => A28; # .s
   "Ṭ" => A12; # .T
   "ṭ" => A25; # .t
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