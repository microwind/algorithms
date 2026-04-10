/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 *
 * 完整版日历打印程序 (Calendar - Full Version)
 * 根据年月输出当月日历，支持显示前后月份日期
 *
 * 使用面向对象设计，封装为Calendar类
 */

/**
 * 日历类 (Calendar Class)
 *
 * 核心功能：
 * 1. 计算任意日期是星期几
 * 2. 打印指定年月的日历
 * 3. 支持显示前后月份日期填充
 *
 * 基准日期：1900年1月1日（星期一）
 */
class Calendar {
  // 静态常量定义
  private static readonly START_YEAR: number = 1900
  private static readonly START_MONTH: number = 1
  private static readonly START_DAY: number = 1
  private static readonly START_WEEKDAY: number = 1 // 1=星期一

  private static readonly WEEKDAYS: string[] = [
    'Sun',
    'Mon',
    'Tue',
    'Wed',
    'Thu',
    'Fri',
    'Sat'
  ]
  private static readonly MONTH_NAMES: string[] = [
    'Jan.',
    'Feb.',
    'Mar.',
    'Apr.',
    'May',
    'Jun.',
    'Jul.',
    'Aug.',
    'Sep.',
    'Oct.',
    'Nov.',
    'Dec.'
  ]

  /**
   * 判断是否为闰年
   * @param year - 年份
   * @returns true表示闰年
   */
  public isLeapYear(year: number): boolean {
    return (year % 4 === 0 && year % 100 !== 0) || year % 400 === 0
  }

  /**
   * 获取某月的天数
   * @param month - 月份
   * @param year - 年份
   * @returns 该月天数
   */
  public getMonthDays(month: number, year: number): number {
    switch (month) {
      case 2:
        return this.isLeapYear(year) ? 29 : 28
      case 4:
      case 6:
      case 9:
      case 11:
        return 30
      default:
        return 31
    }
  }

  /**
   * 获取上个月的天数
   * @param month - 月份
   * @param year - 年份
   * @returns 上个月天数
   */
  public getLastMonthDays(month: number, year: number): number {
    const lastMonth: number = month === 1 ? 12 : month - 1
    const lastYear: number = month === 1 ? year - 1 : year
    return this.getMonthDays(lastMonth, lastYear)
  }

  /**
   * 计算指定日期是星期几（核心算法）
   * @param month - 月份
   * @param day - 日期
   * @param year - 年份
   * @returns 星期几 (0=周日, 1=周一, ..., 6=周六)
   */
  public getWeekdayOfDate(month: number, day: number, year: number): number {
    let weekday: number = Calendar.START_WEEKDAY

    // 累加从1900年到目标年份-1的所有天数
    for (let i: number = Calendar.START_YEAR; i < year; i++) {
      weekday = (weekday + 365) % 7
      if (this.isLeapYear(i)) {
        weekday = (weekday + 1) % 7
      }
    }

    // 累加从1月到目标月份-1的所有天数
    for (let i: number = Calendar.START_MONTH; i < month; i++) {
      weekday = (weekday + this.getMonthDays(i, year)) % 7
    }

    // 加上目标日期与1日的差值
    if (day > Calendar.START_DAY) {
      weekday = (weekday + (day - Calendar.START_DAY)) % 7
    }

    return weekday
  }

  /**
   * 获取某月第一天是星期几
   * @param month - 月份
   * @param year - 年份
   * @returns 星期几
   */
  public getFirstWeekdayOfMonth(month: number, year: number): number {
    return this.getWeekdayOfDate(month, 1, year)
  }

  /**
   * 获取某月最后一天是星期几
   * @param month - 月份
   * @param year - 年份
   * @returns 星期几
   */
  public getLastWeekdayOfMonth(month: number, year: number): number {
    const lastDay: number = this.getMonthDays(month, year)
    return this.getWeekdayOfDate(month, lastDay, year)
  }

  /**
   * 打印日历标题
   * @param month - 月份
   * @param year - 年份
   */
  private printCalendarTitle(month: number, year: number): void {
    if (month < 1 || month > 12) {
    //   console.error(`无效月份: ${month}`)
      return
    }
    const monthName = Calendar.MONTH_NAMES[month - 1]
    if (!monthName) {
    //   console.error(`名称不存在 ${month}`)
      return
    }
    console.log(`${monthName.padStart(16)} ${year}`)
  }

  /**
   * 打印星期标题
   */
  private printWeeklyTitle(): void {
    let header: string = ''
    for (const day of Calendar.WEEKDAYS) {
      header += day.padStart(5)
    }
    console.log(header)
  }

  /**
   * 打印上个月最后几天（用"]"标记）
   * @param weekday - 当月第一天星期几
   * @param month - 月份
   * @param year - 年份
   */
  private printLastMonthLastDays(
    weekday: number,
    month: number,
    year: number
  ): void {
    const lastDays: number = this.getLastMonthDays(month, year)
    const startDay: number = lastDays - weekday + 1
    let line: string = ''
    for (let i: number = startDay; i <= lastDays; i++) {
      line += `${String(i).padStart(2)}]`
    }
    process.stdout.write(line)
  }

  /**
   * 打印下个月开始几天（用"]"标记）
   * @param weekday - 当月最后一天星期几
   */
  private printNextMonthStartDays(weekday: number): void {
    const nextDays: number = 7 - weekday
    let line: string = ''
    for (let i: number = 1; i < nextDays; i++) {
      line += `${String(i).padStart(2)}]`
    }
    process.stdout.write(line)
  }

  /**
   * 打印日历（包含前后月份日期）
   * @param month - 月份
   * @param year - 年份
   */
  public printCalendar(month: number, year: number): void {
    // 打印标题和星期标题
    this.printCalendarTitle(month, year)
    this.printWeeklyTitle()

    // 计算当月第一天是周几
    const firstWeekday: number = this.getFirstWeekdayOfMonth(month, year)
    let weekday: number = firstWeekday

    // 打印上个月最后几天
    this.printLastMonthLastDays(weekday, month, year)

    // 获取当月总天数
    const daysInMonth: number = this.getMonthDays(month, year)

    // 循环输出当月所有日期
    for (let day: number = 1; day <= daysInMonth; day++) {
      process.stdout.write(String(day).padStart(5))
      if (weekday === 6) {
        // Saturday
        console.log()
      }
      weekday = (weekday + 1) % 7
    }

    // 打印下个月开头几天
    const lastWeekday: number = this.getLastWeekdayOfMonth(month, year)
    this.printNextMonthStartDays(lastWeekday)
    console.log()
  }

  /**
   * 获取星期名称
   * @param weekday - 星期几的数字
   * @returns 星期名称
   */
  public getWeekdayName(weekday: number): string {
    return Calendar.WEEKDAYS[weekday]
  }

  /**
   * 获取月份名称
   * @param month - 月份
   * @returns 月份名称
   */
  public getMonthName(month: number): string {
    return Calendar.MONTH_NAMES[month - 1]
  }

  /**
   * 打印指定时间段的日历
   * @param startYear - 开始年份
   * @param startMonth - 开始月份
   * @param count - 打印的月数
   */
  public printCalendarRange(
    startYear: number,
    startMonth: number,
    count: number
  ): void {
    // 处理初始月份大于12的情况（如传入13则转为次年1月）
    let month: number = startMonth
    let year: number = startYear

    while (month > 12) {
      month -= 12
      year++
    }

    for (let i: number = 0; i < count; i++) {
      console.log(`${month}-${year}`)
      this.printCalendar(month, year)
      console.log()

      month++
      if (month === 13) {
        month = 1
        year++
      }
    }
  }
}

/**
 * 测试主函数
 */
function main(): void {
  console.log('完整版日历打印程序 (Class版本)')
  console.log('==================')

  // 创建Calendar实例
  const calendar: Calendar = new Calendar()

  const month: number = 12
  const day: number = 30
  const year: number = 2003

  // 测试：计算2003年12月30日是星期几
  const weekday: number = calendar.getWeekdayOfDate(month, day, year)
  console.log(`[${weekday}] = ${calendar.getWeekdayName(weekday)}`)
  console.log(
    `TEST: ${calendar.getMonthName(month)} ${year} days = ${calendar.getMonthDays(month, year)}`
  )
  console.log(
    `${year}-${month}-${day} is ${calendar.getWeekdayName(weekday)} = WEEKDAYS[${weekday}]`
  )
  console.log()

  // 使用类方法打印48个月的日历（4年）
  calendar.printCalendarRange(year, month + 1, 48)
}

main()

export { Calendar }
/* 打印结果
jarry@Mac calendar % ts-node Calendar.ts
完整版日历打印程序 (Class版本)
==================
[2] = Tue
TEST: Dec. 2003 days = 31
2003-12-30 is Tue = WEEKDAYS[2]

1-2004
            Jan. 2004
  Sun  Mon  Tue  Wed  Thu  Fri  Sat
28]29]30]31]    1    2    3
    4    5    6    7    8    9   10
   11   12   13   14   15   16   17
   18   19   20   21   22   23   24
   25   26   27   28   29   30   31
*/