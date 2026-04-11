/*
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 核心思想：
 * - 填充消息到512位的倍数
 * - 分块处理
 * - 位操作和逻辑运算
 *
 * 注意：此实现仅用于教学目的
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
*
 * SHA-256上下文
*/
typedef struct {
    uint32_t state[8];
    uint64_t count;
    uint8_t buffer[64];
} SHA256_CTX;

/*
*
 * SHA-256常量
*/
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/*
*
 * 位操作函数
*/
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

/*
*
 * 初始化SHA-256上下文
*/
void sha256_init(SHA256_CTX *ctx) {
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
    ctx->count = 0;
}

/*
*
 * 处理一个512位块
*/
void sha256_transform(SHA256_CTX *ctx, uint8_t data[64]) {
    uint32_t W[64], t1, t2;
    uint32_t a, b, c, d, e, f, g, h;
    int i;

    for (i = 0; i < 16; i++) {
        W[i] = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) |
               (data[i * 4 + 2] << 8) | (data[i * 4 + 3]);
    }

    for (i = 16; i < 64; i++) {
        W[i] = SIG1(W[i - 2]) + W[i - 7] + SIG0(W[i - 15]) + W[i - 16];
    }

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; i++) {
        t1 = h + EP1(e) + CH(e, f, g) + K[i] + W[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

/*
*
 * 更新SHA-256
*/
void sha256_update(SHA256_CTX *ctx, uint8_t *data, uint32_t len) {
    uint32_t i;

    for (i = 0; i < len; i++) {
        ctx->buffer[ctx->count % 64] = data[i];
        ctx->count++;

        if (ctx->count % 64 == 0) {
            sha256_transform(ctx, ctx->buffer);
        }
    }
}

/*
*
 * 完成SHA-256并输出结果
*/
void sha256_final(SHA256_CTX *ctx, uint8_t digest[32]) {
    uint64_t bitlen = ctx->count * 8;
    uint32_t i = ctx->count % 64;
    uint32_t padlen = (i < 56) ? (56 - i) : (120 - i);

    ctx->buffer[i++] = 0x80;
    for (; i < 64; i++) {
        ctx->buffer[i] = 0;
    }

    if (padlen >= 56) {
        sha256_transform(ctx, ctx->buffer);
        for (i = 0; i < 56; i++) {
            ctx->buffer[i] = 0;
        }
    }

    for (i = 0; i < 8; i++) {
        ctx->buffer[56 + i] = (bitlen >> (56 - i * 8)) & 0xff;
    }

    sha256_transform(ctx, ctx->buffer);

    for (i = 0; i < 32; i++) {
        digest[i] = (ctx->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 0xff;
    }
}

/*
*
 * SHA-256哈希函数
*/
void sha256(const char *message, uint8_t digest[32]) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (uint8_t *)message, strlen(message));
    sha256_final(&ctx, digest);
}

/*
*
 * 将哈希值转换为十六进制字符串
*/
void sha256_hex(uint8_t digest[32], char *hex) {
    for (int i = 0; i < 32; i++) {
        sprintf(hex + i * 2, "%02x", digest[i]);
    }
    hex[64] = '\0';
}

/*
*
 * 主函数
*/
int main() {
    printf("=== SHA-256哈希算法 ===\n");

    const char *message = "Hello, World!";
    printf("消息: %s\n", message);

    uint8_t digest[32];
    sha256(message, digest);

    char hex[65];
    sha256_hex(digest, hex);
    printf("SHA-256: %s\n", hex);

    printf("\n注意：此实现仅用于教学目的，");
    printf("实际应用应使用成熟的加密库。");

    return 0;
}
