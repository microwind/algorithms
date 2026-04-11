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

/*
*
 * 凯撒加密
*/
fn caesar_encrypt(text: &str, shift: i32) -> String {
    let mut result = String::new();

    for c in text.chars() {
        if c.is_ascii_uppercase() {
            let shifted = ((c as i32 - 'A' as i32 + shift) % 26 + 'A' as i32) as u8;
            result.push(shifted as char);
        } else if c.is_ascii_lowercase() {
            let shifted = ((c as i32 - 'a' as i32 + shift) % 26 + 'a' as i32) as u8;
            result.push(shifted as char);
        } else {
            result.push(c);
        }
    }

    result
}

/*
*
 * 凯撒解密
*/
fn caesar_decrypt(text: &str, shift: i32) -> String {
    caesar_encrypt(text, 26 - (shift % 26))
}

/*
*
 * 主函数
*/
fn main() {
    println!("=== 凯撒密码 ===");

    let text = "Hello, World!";
    let shift = 3;

    println!("明文: {}", text);
    println!("移位数: {}", shift);

    // 加密
    let encrypted = caesar_encrypt(text, shift);
    println!("加密后: {}", encrypted);

    // 解密
    let decrypted = caesar_decrypt(&encrypted, shift);
    println!("解密后: {}", decrypted);

    println!("验证: {}", text == decrypted);
}
