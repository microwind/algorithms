import java.util.*;

/**
 * KMP算法是在朴素搜素的基础之上构建部分匹配表，将比较过的内容根据匹配表跳过比较，从而减少计算步骤。
 * KMP跳过的理由是什么呢？
 * 关键点：已匹配的模式串的前n位能否等于匹配部分的主串的后n位
 * 在前面失败时得到的已匹配的部分内容，寻找出主串尾部与模式串头部的最大相同匹配部分，
 * 如果有则跳过中间的部分(计算方式：匹配字串长度-部分匹配值)，这“中间”的部分在模式串移位时可以跳过。
 */
public class KMPSearch {

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
  private int[] buildPartialMatchTable(String pattern) {
    // 创建一个数组用于存储部分匹配表
    int[] pmt = new int[pattern.length()];
    int j = 0; // 初始化 j 为 0
    // 从模式串的第二个字符开始，依次计算每个位置的部分匹配值
    for (int i = 1; i < pattern.length(); i++) {
      // 当字符不匹配时，回溯到前一个位置的部分匹配值
      while (j > 0 && pattern.charAt(i) != pattern.charAt(j)) {
        j = pmt[j - 1];
      }
      // 当字符匹配时，更新部分匹配值
      if (pattern.charAt(i) == pattern.charAt(j)) {
        j++;
      }
      pmt[i] = j; // 将当前位置的部分匹配值存入部分匹配表
    }
    return pmt; // 返回部分匹配表
  }

  // KMP算法匹配过程
  public List<Integer> find(String pattern, String text) {
    List<Integer> matches = new ArrayList<>(); // 创建一个列表用于存储匹配位置
    int[] partialMatchTable = buildPartialMatchTable(pattern); // 构建模式串的部分匹配表
    int j = 0; // 初始化 j 为 0
    // 遍历文本串，依次进行匹配
    for (int i = 0; i < text.length(); i++) {
      // 当字符不匹配时，回溯到前一个位置的部分匹配值
      while (j > 0 && text.charAt(i) != pattern.charAt(j)) {
        // 从（字符串长度-部分匹配值）的位置开始匹配，而不是从最开始的位置
        j = partialMatchTable[j - 1];
      }
      // 当字符匹配时，更新 j
      if (text.charAt(i) == pattern.charAt(j)) {
        j++;
      }
      // 当 j 等于模式串长度时，表示找到了匹配，将匹配位置存入列表
      if (j == pattern.length()) {
        matches.add(i - j + 1); // 将匹配位置存入列表
        j = partialMatchTable[j - 1]; // 回溯到前一个位置的部分匹配值
      }
    }
    return matches; // 返回匹配位置列表
  }

  /*
   * 部分匹配表计算规则
   * 1、从第一个字符开始，逐个递增得到字串组合。
   * 2、计算每个字串的前缀与后缀，前缀即除尾部字符外的全部头部组合，后缀即除首字母外的全部尾部组合。
   * 3、找出前缀和后缀的全部相同项，得到最大内容的长度。
   * 
   * 例子：abababca
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
   * 8, abababca, [a, ab, abab, ababa, ababab, abababc], [bababca, ababca, babca,
   * abca, bca, ca, a], 'a', 1
   */
  private void printPartialMatchTable(String pattern) {
    int patternLen = pattern.length();
    List<Map<String, Object>> results = new ArrayList<>();
    for (int i = 1; i <= patternLen; i++) {
      Map<String, Object> item = new HashMap<String, Object>();
      String content = pattern.substring(0, i);
      // 添加字串
      item.put("content", content);

      // 添加前后缀
      int contentLen = content.length();
      String[] prefix = new String[contentLen - 1];
      String[] postfix = new String[contentLen - 1];
      for (int j = 0; j < contentLen - 1; j++) {
        prefix[j] = content.substring(0, j + 1);
        postfix[j] = content.substring(j + 1, contentLen);
      }
      item.put("prefix", prefix);
      item.put("postfix", postfix);

      // 计算共同项
      List<String> duplicateItems = new ArrayList<String>();
      String duplicateItem = "";
      for (int m = 0; m < prefix.length; m++) {
        for (int n = 0; n < postfix.length; n++) {
          if (prefix[m].equals(postfix[n])) {
            if (prefix[m].length() > duplicateItem.length()) {
              duplicateItem = prefix[m];
            }
            duplicateItems.add(prefix[m]);
          }
        }
      }
      item.put("duplicateItem", duplicateItem);
      item.put("duplicateItems", duplicateItems);

      // 添加到最终结果
      results.add(item);
    }

    System.out.println("序号, 字符串, 前缀, 后缀, 匹配内容, 内容长度：");
    for (int i = 0; i < results.size(); i++) {
      Map<String, Object> item = results.get(i);
      System.out
          .println((i + 1) + ", " + item.get("content") + ", " + Arrays.toString((String[]) item.get("prefix")) + ", "
              + Arrays.toString((String[]) item.get("postfix")) + ", '" + item.get("duplicateItem") + "', "
              + item.get("duplicateItem").toString().length() + "");
    }
  }

  public static void main(final String args[]) {

    KMPSearch kmpSearch = new KMPSearch();
    // 打印测试
    kmpSearch.printPartialMatchTable("abababca");

    String pattern = "ABABCABAB";
    String text = "ABABCABABCDABABCABAB";
    List<Integer> matches = kmpSearch.find(pattern, text);
    if (matches.isEmpty()) {
      System.out.println("Pattern not found in the text.");
    } else {
      System.out.println("Pattern found at positions: " + matches);
    }

    String[] textArr = {
        "abc",
        "ababc",
        "abababc",
        "ababababca",
        "abababababcd",
        "ababababababca",
        "abababababababcd",
        "ababaabcbabababababc",
        "ababababababababcabcab",
        "ababababaabcbabababcbaba"
    };

    Long startTime = System.currentTimeMillis();

    pattern = "abc";
    for (int i = 0; i < textArr.length; i++) {
      System.out.println(pattern + " " + textArr[i] + " " + kmpSearch.find(pattern,
          textArr[i]));
    }

    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}

/**
 * jarry@jarrys-MacBook-Pro KMPsearch % java -version
 * java version "1.8.0_401"
 * Java(TM) SE Runtime Environment (build 1.8.0_401-b10)
 * Java HotSpot(TM) 64-Bit Server VM (build 25.401-b10, mixed mode)
 * jarry@jarrys-MacBook-Pro KMPsearch % javac KMPSearch.java
 * jarry@jarrys-MacBook-Pro KMPsearch % java KMPSearch
 * 序号, 字符串, 前缀, 后缀, 匹配内容, 内容长度：
 * 1, a, [], [], '', 0
 * 2, ab, [a], [b], '', 0
 * 3, aba, [a, ab], [ba, a], 'a', 1
 * 4, abab, [a, ab, aba], [bab, ab, b], 'ab', 2
 * 5, ababa, [a, ab, aba, abab], [baba, aba, ba, a], 'aba', 3
 * 6, ababab, [a, ab, aba, abab, ababa], [babab, abab, bab, ab, b], 'abab', 4
 * 7, abababc, [a, ab, aba, abab, ababa, ababab], [bababc, ababc, babc, abc, bc,
 * c], '', 0
 * 8, abababca, [a, ab, aba, abab, ababa, ababab, abababc], [bababca, ababca,
 * babca, abca, bca, ca, a], 'a', 1
 * Pattern found at positions: [0, 11]
 * abc abc [0]
 * abc ababc [2]
 * abc abababc [4]
 * abc ababababca [6]
 * abc abababababcd [8]
 * abc ababababababca [10]
 * abc abababababababcd [12]
 * abc ababaabcbabababababc [5, 17]
 * abc ababababababababcabcab [14, 17]
 * abc ababababaabcbabababcbaba [9, 17]
 * 
 * time:1 ms.
 */