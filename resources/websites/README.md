# 算法与数据结构学习网站

> 好的算法学习，不只靠一本书或一道题，还要找到对的平台和社区。

学算法，光看书不够，还得上网练、看课、读博客、泡论坛。互联网上算法资源丰富，但质量参差不齐。下面精选出优质网站，覆盖学习、练习、交流、进阶四大场景。

<!--
---

## 快速导航

graph LR
    subgraph learning["📚 学习资源"]
        A1["MIT OCW"]
        A2["Stanford"]
        A3["Coursera"]
        A4["VisuAlgo"]
        A5["GeeksforGeeks"]
        A6["GitHub Repos"]
    end

    subgraph practice["💻 刷题练习"]
        B1["LeetCode"]
        B2["HackerRank"]
        B3["Codeforces"]
        B4["牛客网"]
        B5["洛谷"]
        B6["AtCoder"]
    end

    subgraph forum["💬 技术论坛"]
        C1["Stack Overflow"]
        C2["Reddit"]
        C3["CSDN"]
        C4["知乎"]
        C5["Quora"]
        C6["Hacker News"]
    end

    subgraph blog["✍️ 大牛博客"]
        D1["Coding Horror"]
        D2["Joel on Software"]
        D3["Paul Graham"]
        D4["阮一峰"]
        D5["酷壳 CoolShell"]
        D6["Julia Evans"]
    end

    style learning fill:#1D9E75,stroke:#0F6E56,color:#ffffff
    style practice fill:#534AB7,stroke:#3C3489,color:#ffffff
    style forum fill:#D85A30,stroke:#993C1D,color:#ffffff
    style blog fill:#444441,stroke:#2C2C2A,color:#ffffff

-->

---

## 推荐网站一览

| 网站名称 | 类别 | 语言 | 特点 |
|---------|------|------|------|
| [MIT OpenCourseWare](#大学课程) | 学习资源 | 英文 | MIT 算法名课，理论标杆 |
| [VisuAlgo](#在线教程与工具) | 学习资源 | 英文 | 算法可视化演示平台 |
| [GeeksforGeeks](#在线教程与工具) | 学习资源 | 英文 | 算法百科全书 |
| [microwind/algorithms](#github-开源项目) | 学习资源 | 中英 | 本项目，多语言对照实现 |
| [Hello 算法](#github-开源项目) | 学习资源 | 中文 | 中文算法教程新标杆 |
| [LeetCode / 力扣](#面试与综合练习) | 刷题练习 | 中英 | 面试刷题事实标准 |
| [Codeforces](#竞赛编程) | 刷题练习 | 英文 | 全球最活跃竞赛平台 |
| [牛客网](#面试与综合练习) | 刷题练习 | 中文 | 国内大厂真题，校招必备 |
| [Stack Overflow](#英文社区) | 技术论坛 | 英文 | 全球最大编程问答社区 |
| [Hacker News](#英文社区) | 技术论坛 | 英文 | YC 技术新闻社区 |
| [知乎](#中文社区) | 技术论坛 | 中文 | 中文算法讨论高质量平台 |
| [Linus Torvalds](#顶尖开源项目创建者) | 开源领袖 | 英文 | Linux / Git 创造者 |
| [Paul Graham](#技术思想家与知名博主) | 大牛博客 | 英文 | YC 创始人，深度思考 |
| [Jeff Dean](#国际大厂顶级程序员) | 大厂大牛 | 英文 | Google 首席科学家 |
| [Peter Norvig](#国际大厂顶级程序员) | 大厂大牛 | 英文 | Google 研究总监 |
| [Andrej Karpathy](#国际大厂顶级程序员) | 大厂大牛 | 英文 | AI 领域顶尖工程师 |

---

## 按类别分级

### 📚 学习资源类（Learning Resources）

系统学习算法与数据结构的课程、教程和开源项目：

#### 大学课程

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| MIT OpenCourseWare (6.006 / 6.046) | [ocw.mit.edu](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/) | MIT 算法课程免费公开，Erik Demaine 等名师授课，理论严谨、板书精彩，是全球算法教学的标杆。适合有一定基础想深入的学习者。 |
| Harvard CS50 | [cs50.harvard.edu](https://cs50.harvard.edu/) | 哈佛大学最受欢迎的计算机科学入门课，David Malan 授课充满激情，涵盖算法基础、数据结构和多种编程语言。全球超百万人在线学习，入门首选。 |
| Stanford Algorithms | [online.stanford.edu](https://online.stanford.edu/courses/soe-ycsalgorithms1-algorithms-design-and-analysis-part-1) | Tim Roughgarden 的算法课逻辑清晰、讲解透彻，侧重算法设计与分析。Coursera 上有对应的两门课，适合系统性学习。 |
| Princeton Algorithms (Coursera) | [coursera.org](https://www.coursera.org/learn/algorithms-part1) | Sedgewick 亲自授课，配合《算法》教材，Java 实现，可视化演示出色。Coursera 上最受欢迎的算法课之一。 |
| UC Berkeley CS 61B | [cs61b.org](https://cs61b.org/) | 伯克利数据结构经典课程，Josh Hug 授课，Java 实现。课程项目设计精良，从链表到图算法层层递进，是北美 CS 专业的标杆数据结构课。 |
| Khan Academy - Algorithms | [khanacademy.org](https://www.khanacademy.org/computing/computer-science/algorithms) | 零基础友好，动画解释清晰，免费无门槛。适合完全没接触过算法的初学者建立直觉。 |

#### 在线教程与工具

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| VisuAlgo | [visualgo.net](https://visualgo.net/) | 新加坡国立大学出品的算法可视化平台，支持几十种数据结构和算法的动态演示。学排序、学树、学图论必备。 |
| Algorithm Visualizer | [algorithm-visualizer.org](https://algorithm-visualizer.org/) | 开源的交互式算法可视化工具，可以逐步执行代码并观察数据结构变化。适合动手实验、加深理解。 |
| GeeksforGeeks | [geeksforgeeks.org](https://www.geeksforgeeks.org/) | 算法与数据结构的"百科全书"，内容覆盖面极广，每个算法都有多语言实现和复杂度分析。质量偶有参差，但胜在全面。 |
| Programiz | [programiz.com](https://www.programiz.com/dsa) | 结构化的算法与数据结构教程，每个概念配有清晰的图示和 Python/C/Java 代码示例。排版干净、循序渐进，适合自学入门。 |
| Big-O Cheat Sheet | [bigocheatsheet.com](https://www.bigocheatsheet.com/) | 一页纸速查所有常见数据结构和排序算法的时间/空间复杂度。面试前必看、复习时必翻的工具型网站。 |
| OpenDSA | [opendsa.org](https://opendsa-server.cs.vt.edu/) | Virginia Tech 主导的开源交互式数据结构教科书，内嵌可视化和练习题。被全球多所大学采用为教材，学术严谨性高。 |
| TopCoder Tutorials | [topcoder.com](https://www.topcoder.com/thrive/tracks?track=Competitive%20Programming) | 竞赛编程领域的经典教程集合，涵盖动态规划、图论、数论等进阶主题。由顶尖竞赛选手撰写，深度和实战性兼备。 |

#### GitHub 开源项目

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| microwind/algorithms（本项目） | [github.com/microwind/algorithms](https://github.com/microwind/algorithms) | 本项目用 C、Java、Python、JS、Go、TS、Rust、Dart 等多语言实现经典算法与数据结构，注释充分、对比学习，适合理解算法原理和语言差异。 |
| The Algorithms (GitHub) | [github.com/TheAlgorithms](https://github.com/TheAlgorithms) | GitHub 上最大的开源算法仓库集合，覆盖 Python、Java、C++ 等 30+ 语言。代码量极大，适合查阅参考，但注释深度不如专门教学项目。 |
| Hello 算法 | [hello-algo.com](https://www.hello-algo.com/) | 国人开源的算法教程，中文优先，图文并茂，动画丰富，支持多语言代码。入门友好度极高，是中文算法学习的新标杆。 |

---

### 💻 刷题与练习类（Coding Practice）

通过做题提升算法能力，从面试准备到竞赛训练：

#### 面试与综合练习

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| LeetCode / 力扣 | [leetcode.com](https://leetcode.com/) / [leetcode.cn](https://leetcode.cn/) | 面试刷题的事实标准。题库覆盖面广、分类清晰，支持多语言提交和讨论区。力扣中国站有中文题解和周赛，是求职者的必经之路。 |
| HackerRank | [hackerrank.com](https://www.hackerrank.com/) | 企业招聘常用的在线评测平台，题目按领域（算法、数据结构、数学、SQL 等）分类，难度分级合理。界面友好，适合入门到中级练习。 |
| Exercism | [exercism.org](https://exercism.org/) | 以"导师制"为特色的编程练习平台，支持 60+ 语言。不以竞赛为导向，而是通过练习和代码审查提升编码能力，适合想扎实基础的学习者。 |
| Codewars | [codewars.com](https://www.codewars.com/) | 以"Kata"（招式）为单位的编程练习平台，游戏化等级系统（kyu/dan）激励持续进步。题目由社区贡献，覆盖面广，适合日常碎片时间练习。 |
| 牛客网 | [nowcoder.com](https://www.nowcoder.com/) | 国内最大的 IT 笔试面试练习平台，大厂真题多、模拟面试功能完善。校招季必备，中文环境对国内求职者非常友好。 |

#### 竞赛编程

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| Codeforces | [codeforces.com](https://codeforces.com/) | 全球最活跃的竞赛编程（Competitive Programming）平台，每周有比赛，rating 系统激励进步。题目偏难偏竞赛风格，适合想冲击算法竞赛的选手。 |
| AtCoder | [atcoder.jp](https://atcoder.jp/) | 日本的算法竞赛平台，比赛质量高、题目设计精巧。每周有 ABC（入门）到 AGC（高级）不同级别的比赛，近年在国际竞赛圈影响力持续上升。 |
| CodeChef | [codechef.com](https://www.codechef.com/) | 印度的老牌竞赛平台，月赛和 Starters 系列比赛持续运营，题目质量稳定。适合想参加更多比赛、积累实战经验的选手。 |
| SPOJ | [spoj.com](https://www.spoj.com/) | 老牌在线评测系统（Sphere Online Judge），题库超过 20000 题，支持 40+ 语言提交。题目来源广泛，从入门到研究级难度都有，适合深度刷题。 |
| Project Euler | [projecteuler.net](https://projecteuler.net/) | 数学与算法交叉的经典题库，700+ 道题需要数学推导 + 编程实现才能高效求解。不追求速度，追求优雅的解法，是锻炼算法思维和数学能力的绝佳平台。 |
| 洛谷 | [luogu.com.cn](https://www.luogu.com.cn/) | 国内算法竞赛（OI/ACM）社区与题库，题目按知识点和难度标签分类，有完善的题解系统。适合信息学竞赛选手和算法进阶者。 |

---

### 💬 技术论坛类（Technical Forums）

遇到问题求助、参与讨论、获取灵感的社区：

#### 英文社区

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| Stack Overflow | [stackoverflow.com](https://stackoverflow.com/) | 全球最大的编程问答社区，几乎所有算法和数据结构问题都能找到高质量回答。投票机制保证答案质量，是程序员的"急救手册"。 |
| Computer Science Stack Exchange | [cs.stackexchange.com](https://cs.stackexchange.com/) | Stack Exchange 旗下的计算机科学理论专门问答社区，讨论算法复杂度、可计算性、形式化方法等深层话题。学术氛围浓厚，回答严谨。 |
| Reddit (r/algorithms / r/learnprogramming) | [reddit.com/r/algorithms](https://www.reddit.com/r/algorithms/) | 活跃的算法讨论社区，有深度的技术讨论和经验分享。r/learnprogramming 适合初学者，r/algorithms 适合进阶讨论。匿名性带来更坦诚的交流。 |
| Hacker News | [news.ycombinator.com](https://news.ycombinator.com/) | YC 旗下的技术新闻社区，经常有算法论文、开源项目和技术深度文章的讨论。信息密度高、社区品味好，是跟踪技术前沿的窗口。 |
| Dev.to | [dev.to](https://dev.to/) | 新一代开发者社区，界面清爽、氛围友好。算法和数据结构教程类文章质量不错，社区互动积极，适合分享学习心得和阅读他人经验。 |
| Quora | [quora.com](https://www.quora.com/) | 英文问答社区，算法和 CS 相关话题下有不少业界专家的深度回答。相比 Stack Overflow 更偏"为什么"而非"怎么做"，适合理解算法背后的思想。 |

#### 中文社区

| 网站名称 | 链接 | 点评 |
|---------|------|------|
| 知乎 | [zhihu.com](https://www.zhihu.com/) | 中文互联网上算法讨论质量最高的平台之一，有不少大厂工程师和竞赛选手分享算法心得。"如何学习算法"等经典问题下的回答值得反复阅读。 |
| CSDN | [csdn.net](https://www.csdn.net/) | 国内最大的开发者社区，算法博客和教程数量极多。质量参差不齐，但头部博主的内容质量不错，中文搜索算法问题常首先命中 CSDN。 |
| SegmentFault（思否） | [segmentfault.com](https://segmentfault.com/) | 国内模仿 Stack Overflow 的技术问答社区，中文环境友好，内容质量较 CSDN 更集中。标签系统方便按主题检索算法相关问答。 |
| V2EX | [v2ex.com](https://www.v2ex.com/) | 程序员社区，技术讨论氛围好，虽非算法专门论坛，但"程序员"和"算法"节点常有高质量的学习经验分享和资源推荐。 |

---

### ✍️ 大牛博客类（Expert Blogs）

站在巨人的肩膀上，读大牛的思考与实践：

#### 技术思想家与知名博主

| 博主 / 网站 | 链接 | 点评 |
|------------|------|------|
| Coding Horror (Jeff Atwood) | [codinghorror.com](https://blog.codinghorror.com/) | Stack Overflow 联合创始人的博客，文章兼顾技术与人文，"程序员应该读什么书"等经典文章广为传播。写作风格幽默，观点犀利。 |
| Joel on Software (Joel Spolsky) | [joelonsoftware.com](https://www.joelonsoftware.com/) | Stack Overflow 另一位联合创始人，Trello 创始人。文章涵盖软件工程、团队管理和编程哲学，"Joel 测试"至今仍是衡量团队的标准。深度与可读性俱佳。 |
| Paul Graham | [paulgraham.com](https://paulgraham.com/) | YC 创始人，Lisp 黑客。他的文章影响了一代创业者和程序员，《黑客与画家》源自其博客。关于编程语言设计和创业的思考极具深度。 |
| Robert Sedgewick | [sedgewick.io](https://sedgewick.io/) | 《算法》教材作者，Princeton 大学教授，Knuth 的学生。他的网站汇集了算法课程资源、研究论文和可视化演示，是算法教育领域的权威。 |
| Steven Skiena | [skiena.org](https://www.cs.stonybrook.edu/~skiena/) | 《算法设计手册》作者，Stony Brook 大学教授。网站提供算法课程视频、编程挑战资源和"算法仓库"（Algorithm Repository），实战导向。 |
| Martin Fowler | [martinfowler.com](https://martinfowler.com/) | ThoughtWorks 首席科学家，《重构》作者。博客涵盖软件架构、设计模式和工程实践，文章影响了整个软件工程领域的思维方式。 |
| Bob Nystrom | [stuffwithstuff.com](https://stuffwithstuff.com/) | Google 工程师，《Crafting Interpreters》和《Game Programming Patterns》作者。写作清晰优雅，将复杂的编译器和算法概念讲得通俗有趣。 |
| Julia Evans | [jvns.ca](https://jvns.ca/) | 用手绘 zine（小册子）解释操作系统、网络、算法等技术概念，风格独特、通俗易懂。她证明了技术写作可以既严谨又有趣。 |
| Eli Bendersky | [eli.thegreenplace.net](https://eli.thegreenplace.net/) | Google 工程师，博客涵盖编译器、算法、系统编程等主题，文章严谨扎实、代码完整可运行。兼顾理论深度和工程实践的技术博客。 |
| Scott Hanselman | [hanselman.com](https://www.hanselman.com/) | 微软工程师，知名技术播客主持人。博客和播客涵盖编程、工具链和职业发展，内容实用接地气，在 .NET 和 Web 开发社区影响力巨大。 |
| Neetcode | [neetcode.io](https://neetcode.io/) | 算法刷题领域最受欢迎的教程作者之一，YouTube 频道订阅超百万。网站提供 LeetCode 题目的分类路线图和视频讲解，是刷题备面的最佳伴侣。 |
| cp-algorithms | [cp-algorithms.com](https://cp-algorithms.com/) | 竞赛算法的百科全书级网站（原 e-maxx 的英文翻译版），覆盖数论、图论、字符串、几何等竞赛常用算法，每篇都有详细推导和实现代码。ACM 选手必备参考。 |

#### 语言创造者与标准制定者

| 人物 | 链接 | 身份与代表作 | 点评 |
|------|------|-------------|------|
| Guido van Rossum | [gvanrossum.github.io](https://gvanrossum.github.io/) | Python 之父 | Python 语言的创造者和终身仁慈独裁者（BDFL）。他的博客记录了 Python 设计决策的思考过程，以及在 Dropbox 和微软的工程实践。读他的文章能理解"简洁优雅"如何成为一门语言的灵魂。 |
| Bjarne Stroustrup | [stroustrup.com](https://www.stroustrup.com/) | C++ 之父 | C++ 语言的设计者与持续演进者，AT&T 贝尔实验室出身，现任哥伦比亚大学教授。网站汇集了 C++ 设计哲学、FAQ、技术论文和演讲，是理解 C++ 为什么这样设计的第一手资料。 |
| Rob Pike | [commandcenter.blogspot.com](https://commandcenter.blogspot.com/) | Go 语言联合创造者 | Bell Labs 传奇程序员，Unix、Plan 9、UTF-8 的共同创造者，与 Ken Thompson 一起设计了 Go 语言。博客文章不多但篇篇精品，关于简洁性和系统设计的思考影响深远。 |
| Ken Thompson | — | Unix / B 语言 / Go 联合创造者 | 图灵奖得主，Unix 操作系统和 B 语言（C 的前身）的创造者，与 Rob Pike 共同设计 Go。虽无个人博客，但他的论文和演讲是计算机科学史上的里程碑。 |
| Anders Hejlsberg | [github.com/AHejlsberg](https://github.com/AHejlsberg) | TypeScript / C# / Turbo Pascal 之父 | 微软技术 Fellow，先后创造了 Turbo Pascal、Delphi、C# 和 TypeScript 四门语言。在 GitHub 上可以直接看到他对 TypeScript 类型系统的设计讨论和代码提交，是少见的"语言设计实况"。 |
| Chris Lattner | [nondot.org/sabre](http://nondot.org/sabre/) | LLVM / Swift / Mojo 创造者 | LLVM 编译器框架创造者，苹果 Swift 语言设计者，后创立 Modular 公司推出 Mojo 语言。横跨编译器、语言设计和 AI 基础设施三大领域，是当代最具影响力的编程语言工程师。 |
| Ryan Dahl | [tinyclouds.org](https://tinyclouds.org/) | Node.js / Deno 创造者 | 用一个"事件循环"改变了服务端编程的格局。创造 Node.js 后反思其设计缺陷，又创造了 Deno。博客文章和演讲（尤其是"Node.js 十大遗憾"）是理解运行时设计取舍的经典。 |
| Brendan Eich | [brendaneich.com](https://brendaneich.com/) | JavaScript 之父 | 10 天创造了 JavaScript，后联合创立 Mozilla，现为 Brave 浏览器 CEO。博客涵盖 JavaScript 演进、Web 标准和浏览器技术，是理解 Web 平台历史的一手视角。 |
| Douglas Crockford | [crockford.com](https://www.crockford.com/) | JSON 之父 | JSON 数据格式的发明者，《JavaScript: The Good Parts》作者。他对 JavaScript 语言的精炼思考影响了一整代前端开发者，其网站上的文章和演讲仍是 JS 学习的经典资料。 |
| Tim Berners-Lee | [w3.org/People/Berners-Lee](https://www.w3.org/People/Berners-Lee/) | WWW 发明者，W3C 创始人 | 万维网的发明者，HTML、HTTP、URL 三大基石的设计者，W3C 的创始人和长期领导者。图灵奖得主，对开放网络的理念至今仍在指导 Web 标准的演进方向。 |

#### 顶尖开源项目创建者

| 人物 | 链接 | 代表项目 | 点评 |
|------|------|---------|------|
| Linus Torvalds | [github.com/torvalds](https://github.com/torvalds) | Linux 内核 / Git | 21 岁写出 Linux 内核，后来又用两周时间创造了 Git。两个项目分别定义了操作系统和版本控制的行业标准。他在邮件列表中的代码审查和技术讨论是学习系统编程的宝贵资源。 |
| Fabrice Bellard | [bellard.org](https://bellard.org/) | FFmpeg / QEMU / TCC | 可能是世界上最高产的个人程序员。独立创造了 FFmpeg（多媒体处理标准）、QEMU（硬件虚拟化）、TCC（最快 C 编译器）等重量级项目，还曾打破圆周率计算世界纪录。他的个人网站是"一个人就是一支军队"的证明。 |
| Salvatore Sanfilippo (antirez) | [antirez.com](http://antirez.com/) | Redis | Redis 的创造者和长期维护者。博客文章深入讨论数据结构设计、系统编程和开源项目管理，关于 Redis 内部实现的文章是学习高性能数据结构的绝佳材料。 |
| Evan You (尤雨溪) | [evanyou.me](https://evanyou.me/) | Vue.js / Vite | Vue.js 框架和 Vite 构建工具的创造者，全职开源开发者。从一个人的 side project 发展为三大前端框架之一，是个人开源创业的标杆。GitHub 上的 RFC 和设计讨论值得关注。 |
| DHH (David Heinemeier Hansson) | [dhh.dk](https://dhh.dk/) | Ruby on Rails | Ruby on Rails 框架的创造者，Basecamp/37signals 联合创始人。Rails 的"约定优于配置"理念深刻影响了整个 Web 开发行业。博客观点鲜明、文笔犀利，涵盖编程哲学和创业思考。 |
| Mitchell Hashimoto | [mitchellh.com](https://mitchellh.com/) | Terraform / Vagrant / Consul | HashiCorp 联合创始人，创造了 Terraform、Vagrant、Consul 等基础设施工具。博客涵盖系统设计、编译器实现（用 Zig 写 terminal emulator）和工程实践，技术深度极高。 |
| Solomon Hykes | [github.com/shykes](https://github.com/shykes) | Docker | Docker 容器技术的创造者，彻底改变了软件的构建、分发和运行方式。容器化思想源自他对 Linux cgroups 和 namespaces 的创造性组合，是系统级创新的典范。 |
| Jordan Walke | [github.com/jordwalke](https://github.com/jordwalke) | React | Facebook 工程师，React 框架的原始创造者。React 的虚拟 DOM 和组件化思想重新定义了前端开发范式，影响了整个 UI 开发生态（React Native、Vue、Flutter 等都受其启发）。 |

#### 国际大厂顶级程序员

| 人物 | 链接 | 所属公司 / 领域 | 点评 |
|------|------|----------------|------|
| Jeff Dean | [research.google/people/jeff](https://research.google/people/jeff/) | Google 首席科学家 | Google 的"10x 工程师"代表，主导了 MapReduce、BigTable、TensorFlow 等定义时代的系统。他和 Sanjay Ghemawat 的合作被称为"硅谷最强双人组"。他的论文是学习大规模分布式系统的必读。 |
| Sanjay Ghemawat | [research.google/people/sanjay](https://research.google/people/sanjay/) | Google Fellow | Jeff Dean 的长期搭档，共同设计了 Google 的核心基础设施（GFS、MapReduce、BigTable、Spanner）。美国工程院院士，他们的论文奠定了现代分布式系统的理论基础。 |
| Peter Norvig | [norvig.com](https://norvig.com/) | Google 研究总监 | 《人工智能：一种现代方法》合著者，NASA 和 Google 的 AI 研究负责人。个人网站上的编程练习和技术文章（如"十年学会编程"、"拼写纠错"）是算法思维的经典示范。 |
| John Carmack | [github.com/id-Software](https://github.com/id-Software) | id Software / Meta | 游戏引擎之神，Doom 和 Quake 的核心开发者。他在 3D 图形算法、实时渲染和底层优化方面的创新定义了游戏行业。id Software 开源的引擎代码是学习高性能 C 编程的教科书。 |
| Andrej Karpathy | [karpathy.ai](https://karpathy.ai/) | 前 Tesla AI 总监 / OpenAI | 斯坦福博士，先后在 OpenAI 和 Tesla 领导 AI 团队。他的深度学习教程（CS231n）和 YouTube 频道（从零实现 GPT）是 AI 领域最受欢迎的学习资源，将复杂的神经网络算法讲得清晰透彻。 |
| Ilya Sutskever | [research.google/people/ilya](https://scholar.google.com/citations?user=x04W_mMAAAAJ) | OpenAI 联合创始人 | AlexNet 论文合著者，深度学习革命的核心推动者。作为 OpenAI 首席科学家主导了 GPT 系列模型的研究方向。他的论文和演讲是理解现代 AI 算法演进的关键线索。 |
| Yann LeCun | [yann.lecun.com](http://yann.lecun.com/) | Meta 首席 AI 科学家 | 图灵奖得主，卷积神经网络（CNN）之父。从手写数字识别到自动驾驶，他的算法发明深刻改变了计算机视觉领域。个人网站和社交媒体上活跃分享 AI 研究前沿和观点。 |
| James Gosling | [nighthacks.com](http://nighthacks.com/) | Java 之父 | Java 语言的创造者，Sun Microsystems 传奇工程师。Java 的"一次编写、到处运行"理念和 JVM 虚拟机架构影响了后续几乎所有托管语言的设计（C#、Kotlin、Scala 等）。 |
| Guido van Rossum | [gvanrossum.github.io](https://gvanrossum.github.io/) | 微软杰出工程师 | Python 之父，退休后加入微软提升 CPython 性能。从 Google 到 Dropbox 到微软，他在每家公司都在用 Python 解决大规模工程问题。他的技术博客记录了 Python 语言演化的第一手思考。 |

#### 中文博主

| 博主 / 网站 | 链接 | 点评 |
|------------|------|------|
| 阮一峰的网络日志 | [ruanyifeng.com/blog](https://www.ruanyifeng.com/blog/) | 国内最知名的技术博主之一，擅长将复杂技术概念讲清楚。算法、数据结构、计算机科学相关的科普文章质量高，是中文技术写作的标杆。 |
| 酷壳 CoolShell (陈皓) | [coolshell.cn](https://coolshell.cn/) | 已故技术大牛陈皓（左耳朵耗子）的博客，文章涵盖算法、架构、编程语言和工程实践。深度、广度和态度俱佳，是中文技术博客的天花板，值得从头到尾通读。 |

---

## 怎么选网站？

| 你的情况 | 推荐网站 | 理由 |
|---------|---------|------|
| 零基础，想入门算法 | Khan Academy、Harvard CS50、Hello 算法 | 动画讲解、中文友好、零门槛 |
| 想系统学名校课程 | MIT OCW、Stanford、Princeton Coursera | 名师授课、体系完整、免费 |
| 想看算法动画和可视化 | VisuAlgo、Algorithm Visualizer、OpenDSA | 可视化演示、交互式练习 |
| 准备面试、需要刷题 | LeetCode、Neetcode、牛客网 | 题库最全、大厂真题多、有路线图 |
| 想参加算法竞赛 | Codeforces、AtCoder、洛谷 | 定期比赛、rating 激励进步 |
| 想练数学 + 算法 | Project Euler | 700+ 道数学编程题，锻炼思维 |
| 遇到算法问题想求助 | Stack Overflow、CS Stack Exchange、知乎 | 社区活跃、回答质量高 |
| 想跟踪技术前沿 | Hacker News、Martin Fowler、Paul Graham | 信噪比高、思想深度足 |
| 想了解语言设计思想 | Stroustrup、Rob Pike、Chris Lattner | 语言创造者的第一手思考 |
| 想学习大规模系统设计 | Jeff Dean、Peter Norvig、antirez | Google 级别的工程实践 |
| 想用多语言对照学习 | microwind/algorithms（本项目） | 8 种语言实现、注释详尽 |

---

## 返回

- [资源与素材](../README.md)
- [入门指南](../../start-here/)
- [项目首页](../../README.md)
