/**
 * KMP算法是在朴素搜素的基础之上构建部分匹配表，将比较过的内容根据匹配表跳过比较，从而减少计算步骤。
 * KMP跳过的理由是什么呢？
 * 关键点：已匹配的模式串的前n位能否等于匹配部分的主串的后n位
 * 在前面失败时得到的已匹配的部分内容，寻找出主串尾部与模式串头部的最大相同匹配部分，
 * 如果有则跳过中间的部分(计算方式：匹配字串长度-部分匹配值)，这“中间”的部分在模式串移位时可以跳过。
 */
function kmpSearch(pattern, text) {
    /*
     * 构建部分匹配表，这是KMP算法中最重要的一环，通过此表来减少比较步骤。
     * 部分匹配表的意思是，在搜索字符串中，将第一个字符与后面的字符递增组成一个个子串。
     * 比如"ABCDE"文本，分为：A, AB, ABC, ABCD, ABCDE这几个子串。
     * 并从每个子串中分别计算前缀与后缀。
     * 前缀是指除了最后一个字符以外，一个字符串的全部头部组合；例如"ABCD"，前缀是：A, AB, ABC三个前缀。
     * 后缀是指除了第一个字符以外，一个字符串的全部尾部组合。例如"ABCD"，后缀是：BCD, BC, D三个后缀。
     * 再分别计算每个字串的部分匹配值，部分匹配值就是前缀和后缀中最长共有元素的长度。
     * 下面以"ABCDAB"为例
     * 子串1：A，前缀[]，后缀[]，共有元素空，长度0。
     * 子串2：AB，前缀[A]，后缀[B]，共有元素空，长度0。
     * 子串3：ABC，前缀[A, AB]，后缀[BC, C]，共有元素空，长度0。
     * 子串4：ABCD，前缀[A, AB, ABC]，后缀[BCD, CD, D]，共有元素空，长度0。
     * 子串5：ABCDA，前缀[A, AB, ABC, ABCD]，后缀[BCDA, CDA, DA, A]，共有元素"A"，长度1。
     * 子串6：ABCDAB，前缀[A, AB, ABC, ABCAB]，后缀[BCDAB, CDAB, DAB, AB, B]，共有元素"AB"，长度2。
     * 
     * 朴素查找会当遇到不匹配的时候，会移动文本下标，从头开始比较查找字符串。
     * 而KMP搜索词移动的时候，不再从头开始查找，而是跳过查找过的地方，从（字符串长度-部分匹配值）的位置开始匹配。
     */
    function buildPartialMatchTable(pattern) {
        // 初始化部分匹配表，前两个位置固定为 -1 和 0
        let next = [-1, 0];
        let i = 2;
        let j = 0;
        // 从模式串的第三个字符开始构建部分匹配表
        while (i < pattern.length) {
            if (pattern[i - 1] === pattern[j]) { // 当前位置字符与之前位置字符相等
                j++; // 匹配长度增加
                next[i] = j; // 更新部分匹配表的值
                i++; // 继续比较下一个位置
            } else if (j > 0) { // 当前位置字符与之前位置字符不相等，但有部分匹配
                j = next[j]; // 回溯到前一个位置的部分匹配值
            } else { // 没有部分匹配
                next[i] = 0; // 当前位置的部分匹配值为0
                i++; // 继续比较下一个位置
            }
        }
        return next; // 返回构建好的部分匹配表
    };

    // 查找函数
    function find(pattern, text) {
        let i = 0;
        let j = 0;
        // 构建部分匹配表
        const partialMatchTable = buildPartialMatchTable(text);
        // 在文本串中进行查找
        while (i < text.length) {
            if (text[i] === pattern[j]) { // 当前位置字符匹配
                i++; // 继续比较下一个位置
                j++; // 模式串指针后移
                if (j === pattern.length) { // 找到了完全匹配的模式串
                    return i - j; // 返回模式串在文本串中的起始位置
                }
            } else if (j > 0) { // 当前位置字符不匹配，且有部分匹配
                // 从（字符串长度-部分匹配值）的位置开始匹配，而不是从最开始的位置
                j = partialMatchTable[j]; // 利用部分匹配表回溯模式串的位置
            } else { // 当前位置字符不匹配，且没有部分匹配
                i++; // 文本串指针后移
            }
        }
        return -1; // 未找到匹配，返回 -1
    }

    return find(pattern, text);


}

function printPartialMatchTable(pattern) {
    let patternLen = pattern.length;
    let results = [];
    for (let i = 1; i <= patternLen; i++) {
        let item = {};
        let content = pattern.substring(0, i);
        // 添加字串
        item["content"] = content;

        // 添加前后缀
        let contentLen = content.length;
        let prefix = new Array(contentLen - 1);
        let postfix = new Array(contentLen - 1);
        for (let j = 0; j < contentLen - 1; j++) {
            prefix[j] = content.substring(0, j + 1);
            postfix[j] = content.substring(j + 1, contentLen);
        }
        item["prefix"] = prefix;
        item["postfix"] = postfix;

        // 计算共同项
        let duplicateItems = [];
        let duplicateItem = "";
        for (let m = 0; m < prefix.length; m++) {
            for (let n = 0; n < postfix.length; n++) {
                if (prefix[m] === postfix[n]) {
                    if (prefix[m].length > duplicateItem.length) {
                        duplicateItem = prefix[m];
                    }
                    duplicateItems.push(prefix[m]);
                }
            }
        }
        item["duplicateItem"] = duplicateItem;
        item["duplicateItems"] = duplicateItems;

        // 添加到最终结果
        results.push(item);
    }

    console.log("序号, 字符串, 前缀, 后缀, 匹配内容, 内容长度：");
    for (let i = 0; i < results.length; i++) {
        let item = results[i];
        console.log(
            i + 1 + ", " + item["content"] + ", " + JSON.stringify(item["prefix"]) + ", " +
            JSON.stringify(item["postfix"]) + ", '" + item["duplicateItem"] + "', " +
            item["duplicateItem"].length
        );
    }
}

// 执行测试用例，打印是否正确
(function () {
    console.time("time");

    printPartialMatchTable("abababca");

    const pattern = 'abc';

    const textArr = [
        'abc',
        'ababc',
        'abababc',
        'ababababca',
        'abababababcd',
        'ababababababca',
        'abababababababcd',
        'ababaabcbabababababc',
        'ababababababababcabcab',
        'ababababaabcbabababcbaba'
    ];
    for (let i = 0; i < textArr.length; i++) {
        console.log(pattern, '', textArr[i], kmpSearch(pattern, textArr[i]));
    }

    console.timeEnd("time");
})();

/*
jarry@jarrys-MacBook-Pro KMPsearch % node kmp_search.js
序号, 字符串, 前缀, 后缀, 匹配内容, 内容长度：
1, a, [], [], '', 0
2, ab, ["a"], ["b"], '', 0
3, aba, ["a","ab"], ["ba","a"], 'a', 1
4, abab, ["a","ab","aba"], ["bab","ab","b"], 'ab', 2
5, ababa, ["a","ab","aba","abab"], ["baba","aba","ba","a"], 'aba', 3
6, ababab, ["a","ab","aba","abab","ababa"], ["babab","abab","bab","ab","b"], 'abab', 4
7, abababc, ["a","ab","aba","abab","ababa","ababab"], ["bababc","ababc","babc","abc","bc","c"], '', 0
8, abababca, ["a","ab","aba","abab","ababa","ababab","abababc"], ["bababca","ababca","babca","abca","bca","ca","a"], 'a', 1
abc  abc 0
abc  ababc 2
abc  abababc 4
abc  ababababca 6
abc  abababababcd 8
abc  ababababababca 10
abc  abababababababcd 12
abc  ababaabcbabababababc 5
abc  ababababababababcabcab 14
abc  ababababaabcbabababcbaba 9
time: 7.813ms
 */