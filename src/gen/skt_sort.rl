%%{

machine skt_sort_key;

alphtype unsigned char;

include symbol "data/sort/symbol.rl";
include whitespace "data/sort/whitespace.rl";

action A0 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 1;
   buf->data[buf->size++] = 1;
}
action A1 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 1;
   buf->data[buf->size++] = 2;
}
action A2 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 2;
   buf->data[buf->size++] = 1;
}
action A3 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 2;
   buf->data[buf->size++] = 2;
}
action A4 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 3;
   buf->data[buf->size++] = 1;
}
action A5 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 3;
   buf->data[buf->size++] = 2;
}
action A6 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 4;
   buf->data[buf->size++] = 1;
}
action A7 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 4;
   buf->data[buf->size++] = 2;
}
action A8 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 5;
   buf->data[buf->size++] = 1;
}
action A9 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 5;
   buf->data[buf->size++] = 2;
}
action A10 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 6;
   buf->data[buf->size++] = 1;
}
action A11 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 6;
   buf->data[buf->size++] = 2;
}
action A12 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 1;
}
action A13 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 7;
   buf->data[buf->size++] = 2;
}
action A14 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 8;
   buf->data[buf->size++] = 1;
}
action A15 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 8;
   buf->data[buf->size++] = 2;
}
action A16 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 9;
   buf->data[buf->size++] = 1;
}
action A17 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 9;
   buf->data[buf->size++] = 2;
}
action A18 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 10;
   buf->data[buf->size++] = 1;
}
action A19 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 10;
   buf->data[buf->size++] = 2;
}
action A20 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 1;
}
action A21 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 11;
   buf->data[buf->size++] = 2;
}
action A22 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 12;
   buf->data[buf->size++] = 1;
}
action A23 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 12;
   buf->data[buf->size++] = 2;
}
action A24 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 13;
   buf->data[buf->size++] = 1;
}
action A25 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 13;
   buf->data[buf->size++] = 2;
}
action A26 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 14;
   buf->data[buf->size++] = 1;
}
action A27 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 14;
   buf->data[buf->size++] = 2;
}
action A28 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 15;
   buf->data[buf->size++] = 1;
}
action A29 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 15;
   buf->data[buf->size++] = 2;
}
action A30 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 1;
}
action A31 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 2;
}
action A32 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 3;
}
action A33 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 16;
   buf->data[buf->size++] = 4;
}
action A34 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 17;
   buf->data[buf->size++] = 1;
}
action A35 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 17;
   buf->data[buf->size++] = 2;
}
action A36 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 1;
}
action A37 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 2;
}
action A38 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 3;
}
action A39 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 18;
   buf->data[buf->size++] = 4;
}
action A40 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 19;
   buf->data[buf->size++] = 1;
}
action A41 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 19;
   buf->data[buf->size++] = 2;
}
action A42 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 20;
   buf->data[buf->size++] = 1;
}
action A43 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 20;
   buf->data[buf->size++] = 2;
}
action A44 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 21;
   buf->data[buf->size++] = 1;
}
action A45 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 21;
   buf->data[buf->size++] = 2;
}
action A46 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 1;
}
action A47 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 2;
}
action A48 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 3;
}
action A49 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 22;
   buf->data[buf->size++] = 4;
}
action A50 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 23;
   buf->data[buf->size++] = 1;
}
action A51 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 23;
   buf->data[buf->size++] = 2;
}
action A52 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 1;
}
action A53 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 2;
}
action A54 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 3;
}
action A55 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 24;
   buf->data[buf->size++] = 4;
}
action A56 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 25;
   buf->data[buf->size++] = 1;
}
action A57 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 25;
   buf->data[buf->size++] = 2;
}
action A58 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 26;
   buf->data[buf->size++] = 1;
}
action A59 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 26;
   buf->data[buf->size++] = 2;
}
action A60 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 1;
}
action A61 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 2;
}
action A62 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 3;
}
action A63 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 27;
   buf->data[buf->size++] = 4;
}
action A64 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 28;
   buf->data[buf->size++] = 1;
}
action A65 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 28;
   buf->data[buf->size++] = 2;
}
action A66 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 1;
}
action A67 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 2;
}
action A68 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 3;
}
action A69 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 29;
   buf->data[buf->size++] = 4;
}
action A70 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 30;
   buf->data[buf->size++] = 1;
}
action A71 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 30;
   buf->data[buf->size++] = 2;
}
action A72 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 31;
   buf->data[buf->size++] = 1;
}
action A73 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 31;
   buf->data[buf->size++] = 2;
}
action A74 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 1;
}
action A75 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 2;
}
action A76 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 3;
}
action A77 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 32;
   buf->data[buf->size++] = 4;
}
action A78 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 33;
   buf->data[buf->size++] = 1;
}
action A79 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 33;
   buf->data[buf->size++] = 2;
}
action A80 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 1;
}
action A81 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 2;
}
action A82 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 3;
}
action A83 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 34;
   buf->data[buf->size++] = 4;
}
action A84 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 35;
   buf->data[buf->size++] = 1;
}
action A85 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 35;
   buf->data[buf->size++] = 2;
}
action A86 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 36;
   buf->data[buf->size++] = 1;
}
action A87 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 36;
   buf->data[buf->size++] = 2;
}
action A88 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 1;
}
action A89 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 2;
}
action A90 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 3;
}
action A91 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 37;
   buf->data[buf->size++] = 4;
}
action A92 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 38;
   buf->data[buf->size++] = 1;
}
action A93 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 38;
   buf->data[buf->size++] = 2;
}
action A94 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 1;
}
action A95 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 2;
}
action A96 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 3;
}
action A97 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 39;
   buf->data[buf->size++] = 4;
}
action A98 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 40;
   buf->data[buf->size++] = 1;
}
action A99 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 40;
   buf->data[buf->size++] = 2;
}
action A100 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 41;
   buf->data[buf->size++] = 1;
}
action A101 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 41;
   buf->data[buf->size++] = 2;
}
action A102 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 1;
}
action A103 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 2;
}
action A104 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 3;
}
action A105 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 42;
   buf->data[buf->size++] = 4;
}
action A106 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 43;
   buf->data[buf->size++] = 1;
}
action A107 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 43;
   buf->data[buf->size++] = 2;
}
action A108 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 1;
}
action A109 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 2;
}
action A110 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 3;
}
action A111 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 44;
   buf->data[buf->size++] = 4;
}
action A112 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 45;
   buf->data[buf->size++] = 1;
}
action A113 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 45;
   buf->data[buf->size++] = 2;
}
action A114 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 1;
}
action A115 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 46;
   buf->data[buf->size++] = 2;
}
action A116 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 1;
}
action A117 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 47;
   buf->data[buf->size++] = 2;
}
action A118 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 1;
}
action A119 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 48;
   buf->data[buf->size++] = 2;
}
action A120 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 49;
   buf->data[buf->size++] = 1;
}
action A121 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 49;
   buf->data[buf->size++] = 2;
}
action A122 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 50;
   buf->data[buf->size++] = 1;
}
action A123 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 50;
   buf->data[buf->size++] = 2;
}
action A124 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 51;
   buf->data[buf->size++] = 1;
}
action A125 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 51;
   buf->data[buf->size++] = 2;
}
action A126 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 52;
   buf->data[buf->size++] = 1;
}
action A127 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 52;
   buf->data[buf->size++] = 2;
}
action A128 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 53;
   buf->data[buf->size++] = 1;
}
action A129 {
   skt_buf_grow(buf, 2);
   buf->data[buf->size++] = 53;
   buf->data[buf->size++] = 2;
}

main := |*
   "A" => A0;
   "a" => A1;
   "Ā" => A2;
   "ā" => A3;
   "I" => A4;
   "i" => A5;
   "Ī" => A6;
   "ī" => A7;
   "U" => A8;
   "u" => A9;
   "Ū" => A10;
   "ū" => A11;
   "R̥" => A12;
   "r̥" => A13;
   "Ṛ" => A14;
   "ṛ" => A15;
   "R̥̄" => A16;
   "r̥̄" => A17;
   "Ṝ" => A18;
   "ṝ" => A19;
   "L̥" => A20;
   "l̥" => A21;
   "Ḷ" => A22;
   "ḷ" => A23;
   "Ḹ" => A24;
   "ḹ" => A25;
   "L̥̄" => A26;
   "l̥̄" => A27;
   "E" => A28;
   "e" => A29;
   "AI" => A30;
   "Ai" => A31;
   "aI" => A32;
   "ai" => A33;
   "O" => A34;
   "o" => A35;
   "AU" => A36;
   "Au" => A37;
   "aU" => A38;
   "au" => A39;
   "Ṃ" => A40;
   "ṃ" => A41;
   "Ḥ" => A42;
   "ḥ" => A43;
   "K" => A44;
   "k" => A45;
   "KH" => A46;
   "Kh" => A47;
   "kH" => A48;
   "kh" => A49;
   "G" => A50;
   "g" => A51;
   "GH" => A52;
   "Gh" => A53;
   "gH" => A54;
   "gh" => A55;
   "Ṅ" => A56;
   "ṅ" => A57;
   "C" => A58;
   "c" => A59;
   "CH" => A60;
   "Ch" => A61;
   "cH" => A62;
   "ch" => A63;
   "J" => A64;
   "j" => A65;
   "JH" => A66;
   "Jh" => A67;
   "jH" => A68;
   "jh" => A69;
   "Ñ" => A70;
   "ñ" => A71;
   "Ṭ" => A72;
   "ṭ" => A73;
   "ṬH" => A74;
   "Ṭh" => A75;
   "ṭH" => A76;
   "ṭh" => A77;
   "Ḍ" => A78;
   "ḍ" => A79;
   "ḌH" => A80;
   "Ḍh" => A81;
   "ḍH" => A82;
   "ḍh" => A83;
   "Ṇ" => A84;
   "ṇ" => A85;
   "T" => A86;
   "t" => A87;
   "TH" => A88;
   "Th" => A89;
   "tH" => A90;
   "th" => A91;
   "D" => A92;
   "d" => A93;
   "DH" => A94;
   "Dh" => A95;
   "dH" => A96;
   "dh" => A97;
   "N" => A98;
   "n" => A99;
   "P" => A100;
   "p" => A101;
   "PH" => A102;
   "Ph" => A103;
   "pH" => A104;
   "ph" => A105;
   "B" => A106;
   "b" => A107;
   "BH" => A108;
   "Bh" => A109;
   "bH" => A110;
   "bh" => A111;
   "M" => A112;
   "m" => A113;
   "Y" => A114;
   "y" => A115;
   "R" => A116;
   "r" => A117;
   "L" => A118;
   "l" => A119;
   "V" => A120;
   "v" => A121;
   "Ś" => A122;
   "ś" => A123;
   "Ṣ" => A124;
   "ṣ" => A125;
   "S" => A126;
   "s" => A127;
   "H" => A128;
   "h" => A129;
   dash;
   whitespace;
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
