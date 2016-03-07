%%{

machine skt_translit_iastc_iast;

alphtype unsigned char;

# ṝ
action A0 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 157;
}
# ṛ
action A1 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 155;
}
# ḷ
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 183;
}
# ḹ
action A3 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 185;
}
# Ḹ
action A4 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 184;
}
# Ṛ
action A5 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 154;
}
# Ḷ
action A6 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 184;
   buf->data[buf->size++] = 182;
}
# Ṝ
action A7 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 225;
   buf->data[buf->size++] = 185;
   buf->data[buf->size++] = 156;
}



main := |*
   "L̥" => A6; # Ḷ
   "L̥̄" => A4; # Ḹ
   "R̥" => A5; # Ṛ
   "R̥̄" => A7; # Ṝ
   "l̥" => A2; # ḷ
   "l̥̄" => A3; # ḹ
   "r̥" => A1; # ṛ
   "r̥̄" => A0; # ṝ
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_iastc_iast(struct skt_buf *buf,
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
