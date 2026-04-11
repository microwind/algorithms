/*
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 注意：此实现使用sha2 crate
 * 需要在Cargo.toml中添加: sha2 = "0.10"
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

use sha2::{Sha256, Digest};

/*
*
 * SHA-256哈希函数（使用sha2 crate）
*/
fn sha256_hash(message: &str) -> String {
    let mut hasher = Sha256::new();
    hasher.update(message.as_bytes());
    let result = hasher.finalize();
    format!("{:x}", result)
}

/*
*
 * 主函数
*/
fn main() {
    println!("=== SHA-256哈希算法 ===");

    let message = "Hello, World!";
    println!("消息: {}", message);

    let hash = sha256_hash(message);
    println!("SHA-256: {}", hash);

    println!("\n注意：此实现使用sha2 crate，");
    println!("实际应用应使用成熟的加密库。");
}
