%%{

machine skt_translit_iast_iastc;

alphtype unsigned char;

# R̥
action A0 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# r̥̄
action A1 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# r̥
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 114;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# l̥
action A3 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}
# R̥̄
action A4 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 82;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
}
# l̥̄
action A5 {
   skt_buf_grow(buf, 5);
   buf->data[buf->size++] = 108;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 132;
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
# L̥
action A7 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 76;
   buf->data[buf->size++] = 204;
   buf->data[buf->size++] = 165;
}



main := |*
   "Ḷ" => A7; # L̥
   "ḷ" => A3; # l̥
   "Ḹ" => A6; # L̥̄
   "ḹ" => A5; # l̥̄
   "Ṛ" => A0; # R̥
   "ṛ" => A2; # r̥
   "Ṝ" => A4; # R̥̄
   "ṝ" => A1; # r̥̄
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_iast_iastc(struct skt_buf *buf,
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
