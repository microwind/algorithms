/*
*
 * 凯撒密码 - 简单的替换加密
 *
 * 问题：将字母表中的每个字母移动固定位数
 *
 * 核心思想：
 * - 字母替换
 * - 循环移位
 * - 保持大小写
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
*
 * 凯撒加密
*/
void caesarEncrypt(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        } else if (islower(text[i])) {
            text[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        }
    }
}

/*
*
 * 凯撒解密
*/
void caesarDecrypt(char* text, int shift) {
    caesarEncrypt(text, 26 - (shift % 26));
}

/*
*
 * 主函数
*/
int main() {
    printf("=== 凯撒密码 ===\n");

    char text[100];
    int shift;

    printf("输入明文: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("输入移位数: ");
    scanf("%d", &shift);

    // 加密
    char encrypted[100];
    strcpy(encrypted, text);
    caesarEncrypt(encrypted, shift);
    printf("加密后: %s\n", encrypted);

    // 解密
    char decrypted[100];
    strcpy(decrypted, encrypted);
    caesarDecrypt(decrypted, shift);
    printf("解密后: %s\n", decrypted);

    printf("验证: %s\n", strcmp(text, decrypted) == 0 ? "成功" : "失败");

    return 0;
}
