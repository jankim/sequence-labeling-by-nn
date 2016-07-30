﻿/*
This file contains Chinese Character, so `UTF8 with BOM` is used.
*/

#include "type_feature.h"

using namespace std;
namespace slnn{

namespace slnn_char_type{

/* 数字 (没有使用带有歧义的 零， 一、二、等)
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ０, １, ２, ３, 
４, ５, ６, ７, ８, ９, ０,
壹, 贰, 叁, 肆, 伍, 陆, 柒, 
捌, 玖, 拾, 佰, 仟, 
*/

unordered_set<string> Utf8CharTypeDict::DigitTypeCharDict = 
{
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\xef\xbc\x90", "\xef\xbc\x91", "\xef\xbc\x92", "\xef\xbc\x93",
    "\xef\xbc\x94", "\xef\xbc\x95", "\xef\xbc\x96", "\xef\xbc\x97", "\xef\xbc\x98", "\xef\xbc\x99", "\xef\xbc\x90",
    "\xe5\xa3\xb9", "\xe8\xb4\xb0", "\xe5\x8f\x81", "\xe8\x82\x86", "\xe4\xbc\x8d", "\xe9\x99\x86", "\xe6\x9f\x92",
    "\xe6\x8d\x8c", "\xe7\x8e\x96", "\xe6\x8b\xbe", "\xe4\xbd\xb0", "\xe4\xbb\x9f"
};

/* 字母（小写、大写，半角、全角）
a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v,
w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
S, T, U, V, W, X, Y, Z, ａ, ｂ, ｃ, ｄ, 
ｅ, ｆ, ｇ, ｈ, ｉ, ｊ, ｋ, 
ｌ, ｍ, ｎ, ｏ, ｐ, ｑ, ｒ, 
ｓ, ｔ, ｕ, ｖ, ｗ, ｘ, ｙ, 
ｚ, Ａ, Ｂ, Ｃ, Ｄ, Ｅ, Ｆ, 
Ｇ, Ｈ, Ｉ, Ｊ, Ｋ, Ｌ, Ｍ, 
Ｎ, Ｏ, Ｐ, Ｑ, Ｒ, Ｓ, Ｔ,
Ｕ, Ｖ, Ｗ, Ｘ, Ｙ, Ｚ
*/

unordered_set<string> Utf8CharTypeDict::LetterTypeCharDict = 
{
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", 
    "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
    "S", "T", "U", "V", "W", "X", "Y", "Z", "\xef\xbd\x81", "\xef\xbd\x82", "\xef\xbd\x83", "\xef\xbd\x84", 
    "\xef\xbd\x85", "\xef\xbd\x86", "\xef\xbd\x87", "\xef\xbd\x88", "\xef\xbd\x89", "\xef\xbd\x8a", "\xef\xbd\x8b", 
    "\xef\xbd\x8c", "\xef\xbd\x8d", "\xef\xbd\x8e", "\xef\xbd\x8f", "\xef\xbd\x90", "\xef\xbd\x91", "\xef\xbd\x92",
    "\xef\xbd\x93", "\xef\xbd\x94", "\xef\xbd\x95", "\xef\xbd\x96", "\xef\xbd\x97", "\xef\xbd\x98", "\xef\xbd\x99", 
    "\xef\xbd\x9a", "\xef\xbc\xa1", "\xef\xbc\xa2", "\xef\xbc\xa3", "\xef\xbc\xa4", "\xef\xbc\xa5", "\xef\xbc\xa6",
    "\xef\xbc\xa7", "\xef\xbc\xa8", "\xef\xbc\xa9", "\xef\xbc\xaa", "\xef\xbc\xab", "\xef\xbc\xac", "\xef\xbc\xad", 
    "\xef\xbc\xae", "\xef\xbc\xaf", "\xef\xbc\xb0", "\xef\xbc\xb1", "\xef\xbc\xb2", "\xef\xbc\xb3", "\xef\xbc\xb4", 
    "\xef\xbc\xb5", "\xef\xbc\xb6", "\xef\xbc\xb7", "\xef\xbc\xb8", "\xef\xbc\xb9", "\xef\xbc\xba"
};

/* 标点符号 (定位似乎有点问题)
，, 。, ？, ！, ：, ；, 、,
…, …, ～, ＆, ＠, ＃, ,, ., ?,
!, :, ;, ·, …, ~, &, @, #, “, ”, ‘, 
’, 〝, 〞,  , ", ', ＂, ＇, ´, ＇, 
（, ）, 【, 】, 《, 》, ＜, 
＞, ﹝, ﹞, <, >, (, ), [, ], «,
», ‹, ›, 〔, 〕, 〈, 〉, 
{, }, ［, ］, 「, 」, ｛, ｝, 
〖, 〗, 『, 』, ︵, ︷, ︹, 
︿, ︽, ﹁, ﹃, ︻, ︗, /, |, \,
︶, ︸, ︺, ﹀, ︾, ﹂, ﹄, 
︼, ︘, ／, ｜, ＼, ˊ, ¨,
­ ­, ^, ¡, ¦, `, ﹎, ﹍, ﹏, ＿,
_, ¯, ￣, ﹋, ﹉, ﹊, ˋ, ︴,
¿, ˇ, 
*/
unordered_set<string> Utf8CharTypeDict::PuncTypeCharDict = 
{
    "\xef\xbc\x8c", "\xe3\x80\x82", "\xef\xbc\x9f", "\xef\xbc\x81", "\xef\xbc\x9a", "\xef\xbc\x9b", "\xe3\x80\x81", 
    "\xe2\x80\xa6", "\xe2\x80\xa6", "\xef\xbd\x9e", "\xef\xbc\x86", "\xef\xbc\xa0", "\xef\xbc\x83", ",", ".", "?", 
    "!", ":", ";", "\xc2\xb7", "\xe2\x80\xa6", "~", "&", "@", "#", "\xe2\x80\x9c", "\xe2\x80\x9d", "\xe2\x80\x98", 
    "\xe2\x80\x99", "\xe3\x80\x9d", "\xe3\x80\x9e", " ", "\'", "\"", "\xef\xbc\x82", "\xef\xbc\x87", "\xc2\xb4", 
    "\xef\xbc\x87", "\xef\xbc\x88", "\xef\xbc\x89", "\xe3\x80\x90", "\xe3\x80\x91", "\xe3\x80\x8a", "\xe3\x80\x8b", 
    "\xef\xbc\x9c", "\xef\xbc\x9e", "\xef\xb9\x9d", "\xef\xb9\x9e", "<", ">", "(", ")", "[", "]", "\xc2\xab", 
    "\xc2\xbb", "\xe2\x80\xb9", "\xe2\x80\xba", "\xe3\x80\x94", "\xe3\x80\x95", "\xe3\x80\x88", "\xe3\x80\x89",
    "{", "}", "\xef\xbc\xbb", "\xef\xbc\xbd", "\xe3\x80\x8c", "\xe3\x80\x8d", "\xef\xbd\x9b", "\xef\xbd\x9d", 
    "\xe3\x80\x96", "\xe3\x80\x97", "\xe3\x80\x8e", "\xe3\x80\x8f", "\xef\xb8\xb5", "\xef\xb8\xb7", "\xef\xb8\xb9", 
    "\xef\xb8\xbf", "\xef\xb8\xbd", "\xef\xb9\x81", "\xef\xb9\x83", "\xef\xb8\xbb", "\xef\xb8\x97", "/", "|", "\\", 
    "\xef\xb8\xb6", "\xef\xb8\xb8", "\xef\xb8\xba", "\xef\xb9\x80", "\xef\xb8\xbe", "\xef\xb9\x82", "\xef\xb9\x84", 
    "\xef\xb8\xbc", "\xef\xb8\x98", "\xef\xbc\x8f", "\xef\xbd\x9c", "\xef\xbc\xbc", "\xcb\x8a", "\xc2\xa8", 
    "\xc2\xad", "^", "\xc2\xa1", "\xc2\xa6", "`", "\xef\xb9\x8e", "\xef\xb9\x8d", "\xef\xb9\x8f", "\xef\xbc\xbf",
    "_", "\xc2\xaf", "\xef\xbf\xa3", "\xef\xb9\x8b", "\xef\xb9\x89", "\xef\xb9\x8a", "\xcb\x8b", "\xef\xb8\xb4", 
    "\xc2\xbf", "\xcb\x87", "\xe3\x80\x80"
};

} // end of namespace slnn

} // end of namespace slnn