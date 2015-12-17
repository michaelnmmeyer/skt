%%{

machine skt_translit_$INPUT_SCHEME_$OUTPUT_SCHEME;

alphtype unsigned char;

$ACTIONS

$FROM_CONSONANT

main := |*
$RULES
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_$INPUT_SCHEME_$OUTPUT_SCHEME(struct skt_buf *buf,
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
$EOF_CHECK
   skt_buf_truncate(buf, buf->size);
}
