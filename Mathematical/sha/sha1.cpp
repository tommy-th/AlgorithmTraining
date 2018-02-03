#include <cmath>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

std::string fileContents(const std::string& path) {
    std::ifstream in(path);
    std::stringstream buffer;

    if (not in.fail()) {
        buffer << in.rdbuf();
    }

    return buffer.str();
}

#define BYTE_ROTATE_LEFT32(value, bits) (((value) << (bits)) | (((value) & 0xffffffff) >> (32 - (bits))))

using var = uint32_t;
using var64 = uint64_t;

// CHUNK_BYTES = WORDS_BYTES * WORDS_NUMS
constexpr unsigned int CHUNK_BYTES = 64; // 512 bit
constexpr unsigned int WORDS_BYTES = 4; // 32 bit
constexpr unsigned int WORDS_NUMS = 16;
constexpr unsigned int DIGEST_NUMS = 5;

std::string m;
var64 ml;

void padding() {
// Step1
    // m에 padding을 추가하기 전 length (bit size)
    ml = m.size()*8;

    // message에 '1' 비트 1개 추가 (실제론 0b10000000 추가)
    // 이 다음 과정에서 m + ml이 64bytes(512bit)로 나누어 떨어지도록
    // '0'비트를 계속 추가하기 때문에 미리 byte 단위로 추가 함.
    m += (char)0x80;

    while (m.size() % CHUNK_BYTES != CHUNK_BYTES - sizeof(ml)) {
        m += (char)0x00;
    }

    for (int i=7; i>=0; i--) {
        char byte = (ml >> 8*i) & 0xff;
        m += byte;
    }

    // 이제 m은 64bytes(512bit) 즉 CHUNK_BYTES로 나누어 떨어진다.
}

std::vector<var> chunkToWords(const std::string& chunk) {
    std::vector<var> words(WORDS_NUMS);

// Step2
    for (unsigned int i = 0; i < WORDS_NUMS; i++) {
        words[i] = (chunk[4*i+3] & 0xff)
                   | (chunk[4*i+2] & 0xff)<<8
                   | (chunk[4*i+1] & 0xff)<<16
                   | (chunk[4*i+0] & 0xff)<<24;
    }

    return words;
}

var h[DIGEST_NUMS] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0,
};

void processChunck(unsigned int index) {
    std::string chunk = m.substr(index * CHUNK_BYTES, CHUNK_BYTES);
    std::vector<var> w = chunkToWords(chunk);

// Step3
    // Extend the sixteen 32-bit words into eighty 32-bit words:
    for (unsigned int i = 16; i <= 79; i++) {
        var word = w[i-3] xor w[i-8] xor w[i-14] xor w[i-16];
        word = BYTE_ROTATE_LEFT32(word, 1);
        w.push_back(word);
    }

    // Initialize hash value for this chunk:
    var a = h[0];
    var b = h[1];
    var c = h[2];
    var d = h[3];
    var e = h[4];
    var f, k;

// Step4
    // Main loop:
    for (unsigned int i = 0; i <= 79; i++) {
        if (0 <= i && i <= 19) {
            f = (b bitand c) bitor (~b bitand d);
            k = 0x5A827999;
        }
        else if (20 <= i && i <= 39) {
            f = b xor c xor d;
            k = 0x6ED9EBA1;
        }
        else if (40 <= i && i <= 59) {
            f = (b bitand c) bitor (b bitand d) bitor (c bitand d);
            k = 0x8F1BBCDC;
        }
        else if (60 <= i && i <= 79) {
            f = b xor c xor d;
            k = 0xCA62C1D6;
        }

        var temp = BYTE_ROTATE_LEFT32(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = BYTE_ROTATE_LEFT32(b, 30);
        b = a;
        a = temp;
    }

    // Add this chunk's hash to result so far:
    h[0] = h[0] + a;
    h[1] = h[1] + b;
    h[2] = h[2] + c;
    h[3] = h[3] + d;
    h[4] = h[4] + e;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s {filename}\n", argv[0]);
        return 0;
    }

    m = fileContents(argv[1]);

    padding();

    var64 chunkNums = m.size() / CHUNK_BYTES;
    for (unsigned int i = 0; i < chunkNums; i++) {
        processChunck(i);
    }

    // Hex std::string
    std::ostringstream hh;
    for (unsigned int i = 0; i < DIGEST_NUMS; i++) {
        hh << std::hex << std::setfill('0') << std::setw(8);
        hh << h[i];
    }

    std::cout << hh.str() << std::endl;
}
