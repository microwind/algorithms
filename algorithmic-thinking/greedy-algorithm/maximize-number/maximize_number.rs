/*
* Maximize Number - Remove k digits to get maximum value
 *
 * Algorithm:
 * - Given a digit string and k, remove k digits to maximize the resulting number
 * - Use a greedy stack-based approach
 *
 * Time Complexity: O(n) - each digit is pushed/popped at most once
 * Space Complexity: O(n) - for the stack
*/

// / Remove k digits from the string to get maximum resulting number
fn remove_k_digits(num_str: &str, k: usize) -> String {
    let n = num_str.len();

    if k >= n {
        return "0".to_string();
    }

    if k == 0 {
        return num_str.to_string();
    }

    // Stack-based greedy approach
    let mut stack: Vec<char> = vec![];
    let mut to_delete = k;

    for ch in num_str.chars() {
        // Remove smaller digits from stack when we encounter a larger digit
        while to_delete > 0 && !stack.is_empty() && stack[stack.len() - 1] < ch {
            stack.pop();
            to_delete -= 1;
        }
        stack.push(ch);
    }

    // If we still have digits to delete, remove from the end
    while to_delete > 0 && !stack.is_empty() {
        stack.pop();
        to_delete -= 1;
    }

    // Build result
    let mut result: String = stack.iter().collect();

    // Handle leading zeros
    let trimmed = result.trim_start_matches('0');
    if trimmed.is_empty() {
        "0".to_string()
    } else {
        trimmed.to_string()
    }
}

fn test_standard_example() {
    println!("\n[Test 1] Standard example from problem");

    let num_str = "1432219";
    let k = 3;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '4321'");
}

fn test_leading_zeros() {
    println!("\n[Test 2] Remove leading zeros");

    let num_str = "10200";
    let k = 1;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '200'");
}

fn test_same_digits() {
    println!("\n[Test 3] All same digits");

    let num_str = "1111";
    let k = 2;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '11'");
}

fn test_descending_order() {
    println!("\n[Test 4] Descending digits - remove from end");

    let num_str = "54321";
    let k = 2;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '321'");
}

fn test_ascending_order() {
    println!("\n[Test 5] Ascending digits - remove from front");

    let num_str = "12345";
    let k = 2;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '345'");
}

fn test_remove_all() {
    println!("\n[Test 6] Remove all digits");

    let num_str = "123";
    let k = 3;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '0'");
}

fn test_remove_zero() {
    println!("\n[Test 7] Remove zero digits");

    let num_str = "1234";
    let k = 0;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '1234'");
}

fn test_multiple_zeros() {
    println!("\n[Test 8] Multiple zeros in middle");

    let num_str = "100200";
    let k = 2;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
}

fn test_mixed() {
    println!("\n[Test 9] Mixed digits");

    let num_str = "112";
    let k = 1;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
    println!("Expected: '12'");
}

fn test_large_number() {
    println!("\n[Test 10] Large number");

    let num_str = "987654321";
    let k = 4;
    let result = remove_k_digits(num_str, k);

    println!("Input: '{}', k={}", num_str, k);
    println!("Output: '{}'", result);
}

fn main() {
    println!("==================================================");
    println!("MAXIMIZE NUMBER - Remove k Digits (Rust)");
    println!("==================================================");

    test_standard_example();
    test_leading_zeros();
    test_same_digits();
    test_descending_order();
    test_ascending_order();
    test_remove_all();
    test_remove_zero();
    test_multiple_zeros();
    test_mixed();
    test_large_number();
}
