%%{

machine skt_translit_iast_nagari;

alphtype unsigned char;

# अ
action A0 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
}
# अ॑
action A1 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 133;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# आ
action A2 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
}
# आ॑
action A3 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 134;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# इ
action A4 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
}
# इ॑
action A5 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ई
action A6 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
}
# ई॑
action A7 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# उ
action A8 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
}
# उ॑
action A9 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 137;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ऊ
action A10 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
}
# ऊ॑
action A11 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 138;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ऋ
action A12 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
}
# ऋ॑
action A13 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ऌ
action A14 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
}
# ऌ॑
action A15 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ए
action A16 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
}
# ए॑
action A17 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 143;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ऐ
action A18 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
}
# ऐ॑
action A19 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 144;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ओ
action A20 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
}
# ओ॑
action A21 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 147;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# औ
action A22 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
}
# औ॑
action A23 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 148;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ॠ
action A24 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
}
# ॠ॑
action A25 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 160;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
}
# ॡ
action A26 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 161;
}
# ं
action A27 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 130;
}
# ः
action A28 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 131;
}
# ऽ
action A29 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 189;
}
# ।
action A30 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 164;
}
# ॥
action A31 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 165;
}
# ०
action A32 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 166;
}
# १
action A33 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 167;
}
# २
action A34 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 168;
}
# ३
action A35 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 169;
}
# ४
action A36 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 170;
}
# ५
action A37 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 171;
}
# ६
action A38 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 172;
}
# ७
action A39 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 173;
}
# ८
action A40 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 174;
}
# ९
action A41 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 175;
}
# क
action A42 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 149;
   fgoto from_consonant;
}
# ख
action A43 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 150;
   fgoto from_consonant;
}
# ग
action A44 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 151;
   fgoto from_consonant;
}
# घ
action A45 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 152;
   fgoto from_consonant;
}
# ङ
action A46 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 153;
   fgoto from_consonant;
}
# च
action A47 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 154;
   fgoto from_consonant;
}
# छ
action A48 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 155;
   fgoto from_consonant;
}
# ज
action A49 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 156;
   fgoto from_consonant;
}
# झ
action A50 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 157;
   fgoto from_consonant;
}
# ञ
action A51 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 158;
   fgoto from_consonant;
}
# ट
action A52 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 159;
   fgoto from_consonant;
}
# ठ
action A53 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 160;
   fgoto from_consonant;
}
# ड
action A54 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 161;
   fgoto from_consonant;
}
# ढ
action A55 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 162;
   fgoto from_consonant;
}
# ण
action A56 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 163;
   fgoto from_consonant;
}
# त
action A57 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 164;
   fgoto from_consonant;
}
# थ
action A58 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 165;
   fgoto from_consonant;
}
# द
action A59 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 166;
   fgoto from_consonant;
}
# ध
action A60 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 167;
   fgoto from_consonant;
}
# न
action A61 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 168;
   fgoto from_consonant;
}
# प
action A62 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 170;
   fgoto from_consonant;
}
# फ
action A63 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 171;
   fgoto from_consonant;
}
# ब
action A64 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 172;
   fgoto from_consonant;
}
# भ
action A65 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 173;
   fgoto from_consonant;
}
# म
action A66 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 174;
   fgoto from_consonant;
}
# य
action A67 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 175;
   fgoto from_consonant;
}
# र
action A68 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 176;
   fgoto from_consonant;
}
# ल
action A69 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 178;
   fgoto from_consonant;
}
# ळ
action A70 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 179;
   fgoto from_consonant;
}
# व
action A71 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 181;
   fgoto from_consonant;
}
# श
action A72 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 182;
   fgoto from_consonant;
}
# ष
action A73 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 183;
   fgoto from_consonant;
}
# स
action A74 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 184;
   fgoto from_consonant;
}
# ह
action A75 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 185;
   fgoto from_consonant;
}
# ॑
action A76 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ा
action A77 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   fgoto main;
}
# ा॑
action A78 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 190;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ि
action A79 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   fgoto main;
}
# ि॑
action A80 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 164;
   buf->data[buf->size++] = 191;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ी
action A81 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   fgoto main;
}
# ी॑
action A82 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 128;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ु
action A83 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   fgoto main;
}
# ु॑
action A84 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 129;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ू
action A85 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   fgoto main;
}
# ू॑
action A86 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 130;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ृ
action A87 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 131;
   fgoto main;
}
# ॄ॑
action A88 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ॢ
action A89 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   fgoto main;
}
# ॢ॑
action A90 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 162;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# े
action A91 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   fgoto main;
}
# े॑
action A92 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 135;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ै
action A93 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   fgoto main;
}
# ै॑
action A94 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 136;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ो
action A95 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   fgoto main;
}
# ो॑
action A96 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 139;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ौ
action A97 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   fgoto main;
}
# ौ॑
action A98 {
   skt_buf_grow(buf, 6);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 140;
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 145;
   fgoto main;
}
# ॄ
action A99 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 132;
   fgoto main;
}
# ॣ
action A100 {
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 163;
   fgoto main;
}
# ्
action A101 {
   fhold;
   skt_buf_grow(buf, 3);
   buf->data[buf->size++] = 224;
   buf->data[buf->size++] = 165;
   buf->data[buf->size++] = 141;
   fgoto main;
}
# trailing 'a'
action A102 {
   fgoto main;
}

from_consonant := |*
   "í" => A80; # ि॑
   "Ḷ" => A89; # ॢ
   "U" => A83; # ु
   "é" => A92; # े॑
   "Ṝ" => A99; # ॄ
   "aI" => A93; # ै
   "ḷ" => A89; # ॢ
   "ú" => A84; # ु॑
   "Ṛ" => A87; # ृ
   "ṛ" => A87; # ृ
   "ai" => A93; # ै
   "Ā" => A77; # ा
   "á" => A76; # ॑
   "au" => A97; # ौ
   "r̥" => A87; # ृ
   "L̥" => A89; # ॢ
   "Ī́" => A82; # ी॑
   "Aú" => A98; # ौ॑
   "aí" => A94; # ै॑
   "ā́" => A78; # ा॑
   "l̥" => A89; # ॢ
   "i" => A79; # ि
   "Ḷ́" => A90; # ॢ॑
   "ā" => A77; # ा
   "ū́" => A86; # ू॑
   "u" => A83; # ु
   "Á" => A76; # ॑
   "ū" => A85; # ू
   "ḷ́" => A90; # ॢ॑
   "ṛ́" => A88; # ॄ॑
   "ṝ́" => A88; # ॄ॑
   "aU" => A97; # ौ
   "aÚ" => A98; # ौ॑
   "AU" => A97; # ौ
   "L̥̄" => A100; # ॣ
   "ī́" => A82; # ी॑
   "E" => A91; # े
   "R̥" => A87; # ृ
   "Ū" => A85; # ू
   "e" => A91; # े
   "O" => A95; # ो
   "É" => A92; # े॑
   "aú" => A98; # ौ॑
   "Ḹ" => A100; # ॣ
   "o" => A95; # ो
   "Í" => A80; # ि॑
   "ī" => A81; # ी
   "I" => A79; # ि
   "Ai" => A93; # ै
   "Ī" => A81; # ी
   "AÍ" => A94; # ै॑
   "Ṛ́" => A88; # ॄ॑
   "aÍ" => A94; # ै॑
   "r̥̄" => A99; # ॄ
   "Ā́" => A78; # ा॑
   "ó" => A96; # ो॑
   "ḹ" => A100; # ॣ
   "l̥̄" => A100; # ॣ
   "Au" => A97; # ौ
   "AÚ" => A98; # ौ॑
   "Aí" => A94; # ै॑
   "Ṝ́" => A88; # ॄ॑
   "Ū́" => A86; # ू॑
   "ṝ" => A99; # ॄ
   "Ó" => A96; # ो॑
   "Ú" => A84; # ु॑
   "R̥̄" => A99; # ॄ
   "AI" => A93; # ै
   "A" => A102; # trailing 'a'
   "a" => A102; # trailing 'a'
   any => A101; # ्
*|;


main := |*
   "A" => A0; # अ
   "a" => A0; # अ
   "AI" => A18; # ऐ
   "AU" => A22; # औ
   "Ai" => A18; # ऐ
   "Au" => A22; # औ
   "AÍ" => A19; # ऐ॑
   "AÚ" => A23; # औ॑
   "Aí" => A19; # ऐ॑
   "Aú" => A23; # औ॑
   "E" => A16; # ए
   "I" => A4; # इ
   "L̥" => A14; # ऌ
   "L̥̄" => A26; # ॡ
   "O" => A20; # ओ
   "R̥" => A12; # ऋ
   "R̥̄" => A24; # ॠ
   "U" => A8; # उ
   "aI" => A18; # ऐ
   "aU" => A22; # औ
   "ai" => A18; # ऐ
   "au" => A22; # औ
   "aÍ" => A19; # ऐ॑
   "aÚ" => A23; # औ॑
   "aí" => A19; # ऐ॑
   "aú" => A23; # औ॑
   "e" => A16; # ए
   "i" => A4; # इ
   "l̥" => A14; # ऌ
   "l̥̄" => A26; # ॡ
   "o" => A20; # ओ
   "r̥" => A12; # ऋ
   "r̥̄" => A24; # ॠ
   "u" => A8; # उ
   "Á" => A1; # अ॑
   "É" => A17; # ए॑
   "Í" => A5; # इ॑
   "Ó" => A21; # ओ॑
   "Ú" => A9; # उ॑
   "á" => A1; # अ॑
   "é" => A17; # ए॑
   "í" => A5; # इ॑
   "ó" => A21; # ओ॑
   "ú" => A9; # उ॑
   "Ā" => A2; # आ
   "Ā́" => A3; # आ॑
   "ā" => A2; # आ
   "ā́" => A3; # आ॑
   "Ī" => A6; # ई
   "Ī́" => A7; # ई॑
   "ī" => A6; # ई
   "ī́" => A7; # ई॑
   "Ū" => A10; # ऊ
   "Ū́" => A11; # ऊ॑
   "ū" => A10; # ऊ
   "ū́" => A11; # ऊ॑
   "Ḷ" => A14; # ऌ
   "Ḷ́" => A15; # ऌ॑
   "ḷ" => A14; # ऌ
   "ḷ́" => A15; # ऌ॑
   "Ḹ" => A26; # ॡ
   "ḹ" => A26; # ॡ
   "Ṛ" => A12; # ऋ
   "Ṛ́" => A13; # ऋ॑
   "ṛ" => A12; # ऋ
   "ṛ́" => A13; # ऋ॑
   "Ṝ" => A24; # ॠ
   "Ṝ́" => A25; # ॠ॑
   "ṝ" => A24; # ॠ
   "ṝ́" => A25; # ॠ॑
   "'" => A29; # ऽ
   "0" => A32; # ०
   "1" => A33; # १
   "2" => A34; # २
   "3" => A35; # ३
   "4" => A36; # ४
   "5" => A37; # ५
   "6" => A38; # ६
   "7" => A39; # ७
   "8" => A40; # ८
   "9" => A41; # ९
   "|" => A30; # ।
   "||" => A31; # ॥
   "Ḥ" => A28; # ः
   "ḥ" => A28; # ः
   "Ṃ" => A27; # ं
   "ṃ" => A27; # ं
   "B" => A64; # ब
   "BH" => A65; # भ
   "Bh" => A65; # भ
   "C" => A47; # च
   "CH" => A48; # छ
   "Ch" => A48; # छ
   "D" => A59; # द
   "DH" => A60; # ध
   "Dh" => A60; # ध
   "G" => A44; # ग
   "GH" => A45; # घ
   "Gh" => A45; # घ
   "H" => A75; # ह
   "J" => A49; # ज
   "JH" => A50; # झ
   "Jh" => A50; # झ
   "K" => A42; # क
   "KH" => A43; # ख
   "Kh" => A43; # ख
   "L" => A69; # ल
   "M" => A66; # म
   "N" => A61; # न
   "P" => A62; # प
   "PH" => A63; # फ
   "Ph" => A63; # फ
   "R" => A68; # र
   "S" => A74; # स
   "T" => A57; # त
   "TH" => A58; # थ
   "Th" => A58; # थ
   "V" => A71; # व
   "Y" => A67; # य
   "b" => A64; # ब
   "bH" => A65; # भ
   "bh" => A65; # भ
   "c" => A47; # च
   "cH" => A48; # छ
   "ch" => A48; # छ
   "d" => A59; # द
   "dH" => A60; # ध
   "dh" => A60; # ध
   "g" => A44; # ग
   "gH" => A45; # घ
   "gh" => A45; # घ
   "h" => A75; # ह
   "j" => A49; # ज
   "jH" => A50; # झ
   "jh" => A50; # झ
   "k" => A42; # क
   "kH" => A43; # ख
   "kh" => A43; # ख
   "l" => A69; # ल
   "m" => A66; # म
   "n" => A61; # न
   "p" => A62; # प
   "pH" => A63; # फ
   "ph" => A63; # फ
   "r" => A68; # र
   "s" => A74; # स
   "t" => A57; # त
   "tH" => A58; # थ
   "th" => A58; # थ
   "v" => A71; # व
   "y" => A67; # य
   "Ñ" => A51; # ञ
   "ñ" => A51; # ञ
   "Ś" => A72; # श
   "ś" => A72; # श
   "Ḍ" => A54; # ड
   "ḌH" => A55; # ढ
   "Ḍh" => A55; # ढ
   "ḍ" => A54; # ड
   "ḍH" => A55; # ढ
   "ḍh" => A55; # ढ
   "Ḻ" => A70; # ळ
   "ḻ" => A70; # ळ
   "Ṅ" => A46; # ङ
   "ṅ" => A46; # ङ
   "Ṇ" => A56; # ण
   "ṇ" => A56; # ण
   "Ṣ" => A73; # ष
   "ṣ" => A73; # ष
   "Ṭ" => A52; # ट
   "ṬH" => A53; # ठ
   "Ṭh" => A53; # ठ
   "ṭ" => A52; # ट
   "ṭH" => A53; # ठ
   "ṭh" => A53; # ठ
   any => {
      skt_buf_grow(buf, 1);
      buf->data[buf->size++] = *p;
   };
*|;

}%%

static void skt_translit_iast_nagari(struct skt_buf *buf,
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
   if (cs == skt_translit_iast_nagari_en_from_consonant) {
      skt_buf_grow(buf, 3);
      buf->data[buf->size++] = 224;
      buf->data[buf->size++] = 165;
      buf->data[buf->size++] = 141;
   }
   skt_buf_truncate(buf, buf->size);
}