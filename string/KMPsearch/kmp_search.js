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


/*
 * 把模式字串逐项展开，计算每项前后缀以及共同项，详细示例
 * 1、从第一个字符开始，逐个递增得到字串组合。
 * 2、计算每个字串的前缀与后缀，前缀即除尾部字符外的全部头部组合，后缀即除首字母外的全部尾部组合。
 * 3、找出前缀和后缀的全部相同项，得到最大内容的长度。
 * 
 * 例子：abababc
 * 
 * 得到如下结果：
 * 
 * 序号, 字符串, 前缀, 后缀, 匹配内容, 内容长度
 * 1, a, [], [], '', 0
 * 2, ab, [a], [b], '', 0
 * 3, aba, [a, ab], [ba, a], 'a', 1
 * 4, abab, [a, ab, aba], [bab, ab, b], 'a', 2
 * 5, ababa, [a, ab, aba, abab], [baba, aba, ba, a], 'aba', 3
 * 6, ababab, [a, ab, aba, abab, ababa], [babab, abab, bab, ab, a], 'abab', 4
 * 7, abababc, [a, ab, aba, abab, ababab], [bababc, ababc, babc, abc, bc, c],
 * '', 0
 */
function printPartialMatchTable(pattern) {
    let patternLen = pattern.length;
    let results = [];
    for (let i = 0; i < patternLen; i++) {
        let item = {
            'prefix': [],
            'postfix': [],
        };
        let content = pattern.substring(0, i + 1);

        // 添加前后缀
        let prefix;
        let postfix;
        let duplicateItems = [];
        let duplicateItem = "";
        for (let j = 0; j < i; j++) {
            // 从前往后
            prefix = content.substring(0, j + 1);
            // 从后往前
            postfix = content.substring(i - j, i + 1);
            item["prefix"].push(prefix);
            item["postfix"].push(postfix);
            if (prefix === postfix && prefix.length > duplicateItem.length) {
                duplicateItem = prefix;
                duplicateItems.push(prefix);
            }
        }

        item["content"] = content;
        item["duplicateItem"] = duplicateItem;
        item["duplicateItems"] = duplicateItems;

        // 添加到最终结果
        results.push(item);
    }

    console.log('模式串:' + pattern)
    console.log("序号, 子串, 前缀, 后缀, 匹配内容, 最大匹配内容长度：");
    for (let i = 0; i < results.length; i++) {
        let item = results[i];
        console.log(
            i + 1 + ", " + item["content"] + ", " + JSON.stringify(item["prefix"]) + ", " +
            JSON.stringify(item["postfix"]) + ", '" + item["duplicateItems"] + "', " +
            item["duplicateItem"].length
        );
    }
}

// 执行测试用例，打印是否正确
(function () {
    console.time("time");
    // 单个测试
    console.log("测试1：单个查找");
    const target = "ABCABAB";
    const text = "AAABABCABABCDABABCABAB";
    const matches = kmpSearch(target, text);
    console.log(target + " found at positions: " + matches + " in " + text);

    // 打印详尽部分匹配表测试
    console.log("测试2：打印详尽部分匹配表");
    printPartialMatchTable("abababc");

    // 多个KMP搜索测试
    console.log("测试3：多个搜索实例");
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
    const pattern = 'abc';
    for (let i = 0; i < textArr.length; i++) {
        console.log(pattern, '', textArr[i], kmpSearch(pattern, textArr[i]));
    }
    console.timeEnd("time");
})();

/*
jarry@jarrys-MacBook-Pro KMPsearch % node kmp_search.js
测试1：单个查找
ABCABAB found at positions: 4 in AAABABCABABCDABABCABAB
测试2：打印详尽部分匹配表
模式串:abababc
序号, 子串, 前缀, 后缀, 匹配内容, 最大匹配内容长度：
1, a, [], [], '', 0
2, ab, ["a"], ["b"], '', 0
3, aba, ["a","ab"], ["a","ba"], 'a', 1
4, abab, ["a","ab","aba"], ["b","ab","bab"], 'ab', 2
5, ababa, ["a","ab","aba","abab"], ["a","ba","aba","baba"], 'a,aba', 3
6, ababab, ["a","ab","aba","abab","ababa"], ["b","ab","bab","abab","babab"], 'ab,abab', 4
7, abababc, ["a","ab","aba","abab","ababa","ababab"], ["c","bc","abc","babc","ababc","bababc"], '', 0
测试3：多个搜索实例
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
time: 8.248ms
 */


/****  其他测试  ****/
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
// 验证
console.log('buildPartialMatchTable("abababc"):', buildPartialMatchTable('abababc'));

function buildPartialMatchTable2(pattern) {
    // 创建一个数组用于存储部分匹配表
    let pmt = new Array(pattern.length).fill(0);
    let j = 0; // 初始化 j 为 0
    // 从模式串的第二个字符开始，依次计算每个位置的部分匹配值
    for (let i = 1; i < pattern.length; i++) {
        // 当字符不匹配时，回溯到前一个位置的部分匹配值
        while (j > 0 && pattern[i] !== pattern[j]) {
            j = pmt[j - 1];
        }
        // 当字符匹配时，更新部分匹配值
        if (pattern[i] === pattern[j]) {
            j++;
        }
        pmt[i] = j; // 将当前位置的部分匹配值存入部分匹配表
    }
    return pmt; // 返回部分匹配表
}

// 验证
console.log('buildPartialMatchTable2("abababc"):', buildPartialMatchTable2('abababc'));

function buildPMTArr(target) {

    const pmtArr = [];
    // 将目标字符串转换为字符数组
    target = target.split('');

    // 外部循环遍历模式串中的每个字符
    for (let j = 0; j < target.length; j++) {
        // 获取模式串不同长度下的部分匹配值
        let pmt = target; // 将目标字符串赋值给pmt
        let pmtNum = 0; // 初始化部分匹配值为0

        // 内部循环，遍历模式串开头到第j个字符的所有可能的前缀和后缀组合
        for (let k = 0; k < j; k++) {
            // 获取前缀
            let head = pmt.slice(0, k + 1);
            // 获取后缀
            let foot = pmt.slice(j - k, j + 1);

            // 判断前缀和后缀是否相等
            if (head.join('') === foot.join('')) {
                let num = head.length; // 获取当前部分匹配的长度
                // 如果当前部分匹配的长度大于已记录的部分匹配长度，则更新pmtNum
                if (num > pmtNum) pmtNum = num;
            }
        }

        // 将当前位置的部分匹配值（即 j + 1 减去已经找到的最长部分匹配长度）添加到部分匹配表数组中
        pmtArr.push(j + 1 - pmtNum);
    }

    // 返回部分匹配表数组
    return pmtArr;
}

/**
 * 使用 KMP 算法在目标字符串中搜索模式串
 * @param {string} target - 模式串，要搜索的字符串
 * @param {string} base - 目标字符串，在其中搜索模式串
 * @returns {number} - 如果找到模式串，则返回其在目标字符串中的起始索引；否则返回 -1
 */
function searchByKMP(target, base) {
    // 用于存储匹配结果的数组
    let isMatch = [];

    // 构建模式串的部分匹配表
    let pmt = buildPMTArr(target);

    // 用于记录移位次数
    let times = 0;
    // 遍历目标字符串中的每个字符
    for (let i = 0; i < base.length; i++) {
        times++;
        let tempIndex = 0; // 临时存储变量，用于处理不匹配情况
        // 遍历模式串中的每个字符
        for (let j = 0; j < target.length; j++) {
            if (i + target.length <= base.length) {
                // 如果目标字符串中剩余长度足够容纳模式串
                if (target.charAt(j) === base.charAt(i + j)) {
                    // 如果当前字符匹配，则将其添加到匹配结果数组中
                    isMatch.push(target.charAt(j));
                } else {
                    // 如果不匹配，则根据部分匹配表进行调整
                    if (!j) break; // 如果第一个字符就不匹配，则直接跳到下一个字符
                    let skip = pmt[j - 1]; // 获取应该跳过的字符数
                    tempIndex = i + skip - 1; // 计算临时索引
                    break;
                }
            }
        }
        // 将当前状态存入调用 KMP 算法的状态信息数组中
        let data = {
            index: i,
            matchArr: isMatch
        };

        // 如果存在临时索引，则跳转到该索引继续匹配
        if (tempIndex) i = tempIndex;
        // 如果匹配结果数组长度等于模式串长度，则表示完全匹配，返回起始索引
        if (isMatch.length === target.length) {
            console.log('移位次数:', times); // 输出移位次数
            return i;
        }
        isMatch = []; // 清空匹配结果数组，准备下一轮匹配
    }
    return -1; // 如果遍历完目标字符串仍未找到完全匹配的模式串，则返回 -1
}
// 验证
console.log('buildPMTArr("abababc"):', buildPMTArr('abababc'));

const target = "ABCABAB";
const text = "AAABABCABABCDABABCABAB";
console.log('searchByKMP(' + target + ',' + text + '):', searchByKMP(target, text));