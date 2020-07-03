
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;

public class StringSearch {

  int find(String str, String text) {
    int strLen = str.length();
    int textLen = text.length();
    for (int i = 0; i < textLen; i++) {
      int j = 0;
      for (; j < strLen; j++) {
        if (str.charAt(j) != text.charAt(i + j)) {
          break;
        }
      }
      if (j == strLen) {
        return i;
      }
    }
    return -1;
  }

  int find2(String str, String text) {
    int strLen = str.length();
    int textLen = text.length();
    int len = textLen - strLen + 1;
    for (int i = 0; i < len; i++) {
      int j = 0;
      while (j < strLen) {
        if (textLen - i < strLen - j) {
          return -1;
        }
        if (str.charAt(j) != text.charAt(i + j)) {
          break;
        }
        j++;
      }
      if (j == strLen) {
        return i;
      }
    }
    return -1;
  }
  
  public static void main(final String args[]) {
    StringSearch stringSearch = new StringSearch();
    String str1 = "ABC";
    String text1 = "AABABC";

    String str2 = "AAB";
    String text2 = "AAAABC";

    String str3 = "ABC";
    String text3 = "AABAC";

    int result = -1;
    long startTime;
    // find test
    startTime = System.currentTimeMillis();
    result = stringSearch.find(str1, text1);
    System.out.println("stringSearch.find(" + str1 + ", " + text1 + ")");
    System.out.println("result:" + result);

    result = stringSearch.find(str2, text2);
    System.out.println("stringSearch.find(" + str2 + ", " + text2 + ")");
    System.out.println("result:" + result);

    result = stringSearch.find(str3, text3);
    System.out.println("stringSearch.find(" + str3 + ", " + text3 + ")");
    System.out.println("result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  
    // find2 test
    startTime = System.currentTimeMillis();
    result = stringSearch.find2(str1, text1);
    System.out.println("stringSearch.find2(" + str1 + ", " + text1 + ")");

    System.out.println("result:" + result);
    result = stringSearch.find2(str2, text2);
    System.out.println("stringSearch.find2(" + str2 + ", " + text2 + ")");

    System.out.println("result:" + result);
    result = stringSearch.find2(str3, text3);
    System.out.println("stringSearch.find2(" + str3 + ", " + text3 + ")");
    System.out.println("result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}

/*
jarry@jarrys-MacBook-Pro nativesearch % java -version
java version "14.0.1" 2020-04-14
Java(TM) SE Runtime Environment (build 14.0.1+7)
Java HotSpot(TM) 64-Bit Server VM (build 14.0.1+7, mixed mode, sharing)
jarry@jarrys-MacBook-Pro nativesearch % javac StringSearch.java
jarry@jarrys-MacBook-Pro nativesearch % java StringSearch      
stringSearch.find(ABC, AABABC)
result:3
stringSearch.find(AAB, AAAABC)
result:2
stringSearch.find(ABC, AABAC)
result:-1

time:22 ms.
stringSearch.find2(ABC, AABABC)
result:3
stringSearch.find2(AAB, AAAABC)
result:2
stringSearch.find2(ABC, AABAC)
result:-1

time:2 ms.
*/