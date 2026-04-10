/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 闰年判断 (Leap Year Check)
 * 判断给定年份是否为闰年
 * 
 * 闰年规则：
 * 1. 能被4整除但不能被100整除的是闰年
 * 2. 能被400整除的也是闰年
 * 3. 其他情况不是闰年
 */

class IsLeapYear {
    
    /**
     * 判断是否为闰年
     * 参数: year - 待判断的年份
     * 返回: true表示闰年，false表示平年
     */
    public static boolean isLeapYear(int year) {
        // 闰年条件：能被4整除且不能被100整除，或者能被400整除
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }
    
    // 测试主函数
    public static void main(String[] args) {
        int[] testYears = {2000, 2004, 1900, 2023, 2024};
        
        System.out.println("闰年判断测试");
        System.out.println("============");
        
        for (int year : testYears) {
            boolean isLeap = isLeapYear(year);
            System.out.printf("%d年: %s%n", year, isLeap ? "闰年" : "平年");
        }
    }
}
