%%{

machine skt_sort_key;

alphtype unsigned char;

$ACTIONS

main := |*
$RULES
   any => {
      skt_buf_grow(buf, 2);
      buf->data[buf->size++] = 0xff;
      buf->data[buf->size++] = *p;
   }; 
*|;

}%%

void skt_sort_key(struct skt_buf *buf, const char *str, size_t len)
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
