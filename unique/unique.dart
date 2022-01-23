/**
 * @desc Dart数组去重的N种方法
 * @author jarryli@gmail.com
 */

// 方式1，自前往后逐个对比移除相同项
unique1(List<int> list) {
  var len = list.length;
  for (var i = 0; i < len; i++) {
    for (var j = i + 1; j < len; j++) {
  	  // 拿当前的项逐个与后面的项比较
  	  // 遇到相同的则删除当前项
  	  // 同时整体长度减1，当前位置回退1位
      if (list[i] == list[j]) {
        list.removeAt(i);
        len--;
        i--;
        break;
      }
    }
  }
  return list;
}

// 方式2_1，自后往前逐个对比移除相同项
unique2_1(List<int> list) {
  int len = list.length;
  // 自后往前将当前项与list最前面的开始比较
  // 如果遇到相同项则移除当前项，跳出循环开始下一轮比较
  while (len-- > 0) {
    for (var j = 0; j < len; j++) {
      if (list[j] == list[len]) {
        // print("there is unique item: ${list[len]}");
        list.removeAt(len);
        break;
      }
    }
  }
  return list;
}

// 方式2，自后往前逐个对比移除相同项
unique2(List<int> list) {
  int len = list.length;
  // 自后往前将当前项与list最后面项开始比较
  // 如果遇到相同项则移除当前项，且跳出循环开始下一轮比较
  while (len-- > 0) {
  	// print ("list[$len] = ${list[len]}");
    var idx = len;
    while (idx --> 0) {
      if (list[len] == list[idx]) {
        list.removeAt(idx);
        break;
      }
    }
  }
  return list;
}

// 新建list+contains方式
unique3(List<int> list) {
  List result = [];
  result.add(list[0]);
  for (var i = 1; i < list.length; i++) {
    // 如果新数组里没有该项，那么添加到新数组中
    if (!result.contains(list[i])) {
      result.add(list[i]);
    }
  }
  return result;
}


// 新建list+double loop方式
unique4(List<int> list) {
  List result = [];
  result.add(list[0]);
  for (var i = 1; i < list.length; i++) {
    bool in_result = false;
    // 如果新数组中没有该项，则添加到新数组中
    for (var j = 0; j < result.length; j++) {
      if (list[i] == result[j]) {
        in_result = true;
        break;
      }
    }
    if (!in_result) {
      result.add(list[i]);
    }
  }
  return result;
}

// 新建list+下标对比方式
unique5(List<int> list) {
  List result = [];
  var idx = 0;
  for (var i = 0; i < list.length; i++) {
    // 如果新数组中没有该项，则添加到新数组中
    for (var j = 0; j <= i; j++) {
      // 将当前项逐个与后面项比较,如果相同且下标相同可以认为是第一次出现
      // 则可以添加到新数组中去，如果不是第一次出现则可以跳过
      if (list[i] == list[j]) {
        if (i == j) {
          // 数组长度增加在插入内容
          result.length += 1;
          result[idx] = list[i];
          idx++;
        }
        break;
      }
    }
  }
  return result;
}

// 新建list+下标对比方式
unique6(List<int> list) {
  List result = [];
  for (var i = 0; i < list.length; i++) {
    var idx = 0;
    // 如果新数组中没有该项，则添加到新数组中
    for (var j = 0; j <= i; j++) {
      // 将当前项逐个与后面项比较,如果相同且下标相同可以认为是第一次出现
      // 则可以添加到新数组中去，如果不是第一次出现则可以跳过
      // print("$i, $j ${list[i]} == ${list[j]}");
      if (list[i] == list[j]) {
        if (i == j) {
          result.add(list[i]);
        }
        break;
      }
    }
  }
  return result;
}

// 新建list+indexOf对比值方式
unique7(List<int> list) {
  List result = [];
  for (var i = 0; i < list.length; i++) {
    if (result.indexOf(list[i]) < 0) {
      result.add(list[i]);
    }
  }
  return result;
}

// 新建list+indexOf对比下标方式
unique8(List<int> list) {
  List result = [];
  for (var i = 0; i < list.length; i++) {
    // 如果list中存在该项，且位置与当前下标相同
    // 则表示第一次出现，就添加到新数组中
    if (list.indexOf(list[i]) == i) {
      result.add(list[i]);
    }
  }
  return result;
}

// 新建list+forEach方式
unique9(List<int> list) {
  List result = [];
  addTo(List result, item) {
    if (!result.contains(item)) {
      result.add(item);
    }
  }
  list.forEach((ele) {
    addTo(result, ele);
  });
  return result;
}

// 新建toSet方式，set数据具有去重复性
unique10(List<int> list) {
  
  // 1) 直接转为set
  // return Set.from(list);

  // 2) 全部添加到set
  // var result = new Set();
  // result.addAll(list);

  // 3) 逐个添加到set
  var result = new Set();
  list.forEach((ele) => result.add(ele));
  return result;
}

// 先sort在逐个自后往前删除重复项
unique11(List<int> list) {
  list.sort();
  var len = list.length - 1;
  while (len > 0) {
    if (list[len] == list[len - 1]) {
      list.removeAt(len);
    }
    len--;
  }
  return list;
}

// 先sort在逐个自前往后删除重复项
unique12(List<int> list) {
  list.sort();
  var i = 0;
  var len = list.length;
  while (i < len - 1) {
    if (list[i] == list[i + 1]) {
      list.removeAt(i);
      len--;
      i--;
    }
    i++;
  }
  return list;
}

// 新map key唯一性实现去重复
unique13(List<int> list) {
  Map result = new Map();
  list.forEach((ele) {
    if (result[ele] == null) {
      result[ele] = -1;
    }
  });
  return result.keys.toList();
}

// 利用递归调用来去重复。递归自后往前逐个调用，当长度为1时终止。
// 当后一项与前任一项相同说明有重复，则删除当前项。相当于利用自我调用来替换循环
unique14(List<int> list, int len) {
  if (len < 1) {
    return list;
  }
  var last = len - 1;
  var idx = len - 1;
  while (idx-- > 0) {
    // 拿最后一个逐个其他项比较，当遇到相同项则移除最后项
    if (list[last] == list[idx]) {
      list.removeAt(last);
      break;
    }
  }
  return unique14(list, len - 1);
}

// 利用递归调用来去重复的另外一种方式。递归自后往前逐个调用，当长度为1时终止。
// 与上一个递归不同，这里将不重复的项目作为结果拼接起来
unique15(List<int> list, int len) {
  if (len < 1) {
    return [];
  }
  var result = [];
  var last = len - 1;
  var idx = len - 1;
  bool is_repeat = false;
  while (idx-- > 0) {
    // 拿最后一个逐个其他项比较，判断是否存在重复
    if (list[last] == list[idx]) {
      is_repeat = true;
      break;
    }
  }
  if (!is_repeat) {
    // 如果与其他项不重复则添加到临时数组中
    result.add(list[last]);
  }
  // 通过递归调用，再连接不重复的项
  return unique15(list, len - 1)..addAll(result);
}

void main() {
  var list = [2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5];

  var result = [];
  result = unique1(List.from(list));
  print("unique1 result: $result");

  result = unique2(List.from(list));
  print("unique2 result: $result");

  result = unique3(List.from(list));
  print("unique3 result: $result");

  result = unique4(List.from(list));
  print("unique4 result: $result");

  result = unique5(List.from(list));
  print("unique5 result: $result");

  result = unique6(List.from(list));
  print("unique6 result: $result");

  result = unique7(List.from(list));
  print("unique7 result: $result");

  result = unique8(List.from(list));
  print("unique8 result: $result");

  result = unique9(List.from(list));
  print("unique9 result: $result");

  result = unique11(List.from(list));
  print("unique11 result: $result");

  result = unique12(List.from(list));
  print("unique12 result: $result");

  result = unique13(List.from(list));
  print("unique13 result: $result");

  result = unique14(List.from(list), List.from(list).length);
  print("unique14 result: $result");

  result = unique15(List.from(list), List.from(list).length);
  print("unique15 result: $result");
}