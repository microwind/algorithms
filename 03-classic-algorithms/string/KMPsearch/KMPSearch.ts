/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
/**
 * 提取模式串的部分匹配值，构建部分匹配表。
 * @param pattern 模式串
 * @returns 部分匹配表
 */
function makePMT(pattern: string): number[] {
  const len = pattern.length;
  const pmt = new Array(len).fill(0);
  for (let i = 0; i < len; i++) {
    const subPattern = pattern.slice(0, i + 1);
    let j = 0;
    let pmtValue = 0;

    const prefixArr: string[] = [];
    const postfixArr: string[] = [];

    while (j < i) {
      const prefix = subPattern.substring(0, j + 1);
      const postfix = subPattern.substring(i - j, i + 1);
      prefixArr.push(prefix);
      postfixArr.push(postfix);

      if (prefix === postfix && prefix.length > pmtValue) {
        pmtValue = prefix.length;
      }

      j++;
    }

    pmt[i] = pmtValue;

    console.log(i, subPattern, " | ", prefixArr, " | ", postfixArr, " | ", pmtValue);
  }

  console.log("makePMT() pmt:", pmt);
  return pmt;
}

function makePMT2(pattern: string): number[] {
  const pmt = new Array(pattern.length).fill(0);
  let pmtValue = 0;

  for (let i = 1; i < pattern.length; i++) {
    while (pmtValue > 0 && pattern[i] !== pattern[pmtValue]) {
      pmtValue = pmt[pmtValue - 1];
    }

    if (pattern[i] === pattern[pmtValue]) {
      pmtValue++;
    }

    pmt[i] = pmtValue;

    const subPattern = pattern.slice(0, i + 1);
    const prefixArr: string[] = [];
    const postfixArr: string[] = [];

    let j = 0;
    while (j < i) {
      const prefix = pattern.slice(0, j + 1);
      const postfix = subPattern.slice(i - j, i + 1);
      prefixArr.push(prefix);
      postfixArr.push(postfix);

      j++;
    }

    console.log(i, subPattern, " | ", prefixArr, " | ", postfixArr, " | ", pmtValue);
  }

  console.log("makePMT2() pmt:", pmt);
  return pmt;
}

/**
 * KMP搜索算法
 * @param pattern 模式串
 * @param text 目标文本
 * @returns 匹配结果
 */
function kmpSearch(pattern: string, text: string): number[] {
  console.log("pattern:", pattern, "text:", text);

  const matches: number[] = [];
  const pmtTable = makePMT2(pattern);

  let j = 0;
  console.log("根据模式串获取pmtTable:", pmtTable);

  for (let i = 0; i < text.length; i++) {
    while (j > 0 && text[i] !== pattern[j]) {
      j = pmtTable[j - 1];
    }

    if (text[i] === pattern[j]) {
      j++;
    }

    if (j === pattern.length) {
      matches.push(i - j + 1);
      j = pmtTable[j - 1];
    }
  }

  console.log("匹配结果：", matches);
  return matches;
}

// 测试验证
(function () {
  console.log("KMP搜索测试：");
  const pattern = "ABCABAB";
  console.log("pattern:", pattern);
  makePMT(pattern);
  makePMT2(pattern);

  const text1 = "AAABABCABABCDABABCABAB";
  const result1 = kmpSearch(pattern, text1);
  console.log("匹配结果1：", result1); // 应输出 [4, 15]

  const text2 = "ABAAABABCABABCDABABCABAB";
  const result2 = kmpSearch(pattern, text2);
  console.log("匹配结果2：", result2); // 应输出 [6, 17]
})();
