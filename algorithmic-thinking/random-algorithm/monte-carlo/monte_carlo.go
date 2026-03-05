package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// 蒙特卡洛算法实现 (Go语言)
//
// 特点：
// - 运行时间固定
// - 给出正确答案的概率很高
// - 可能会返回错误答案，但概率可控

// 蒙特卡洛方法估算π
func monteCarloPi(numSamples int) float64 {
	insideCircle := 0

	for i := 0; i < numSamples; i++ {
		// 在 [0, 1] × [0, 1] 内随机生成点
		x := rand.Float64()
		y := rand.Float64()

		// 判断是否在原点为中心、半径为 1 的圆内
		if x*x+y*y <= 1.0 {
			insideCircle++
		}
	}

	// 圆的面积 / 正方形面积 = π/4
	// 所以 π ≈ 4 * (圆内的点数 / 总点数)
	return 4.0 * float64(insideCircle) / float64(numSamples)
}

// 蒙特卡洛方法计算积分
func monteCarloIntegration(funcX func(float64) float64, a, b float64, numSamples int) float64 {
	sumValues := 0.0

	for i := 0; i < numSamples; i++ {
		// 在 [a, b] 内随机生成 x
		x := a + (b-a)*rand.Float64()
		sumValues += funcX(x)
	}

	// 积分 ≈ (b - a) * (平均函数值)
	return (b - a) * sumValues / float64(numSamples)
}

// 测试函数：x²
func funcXSquared(x float64) float64 {
	return x * x
}

// 测试函数：sin(x)
func funcSin(x float64) float64 {
	return math.Sin(x)
}

// 蒙特卡洛方法估算概率
func monteCarloProbability(numTrials, successThreshold int) float64 {
	successes := 0

	for i := 0; i < numTrials; i++ {
		// 模拟随机事件：掷骰子
		diceRoll := rand.Intn(6) + 1

		// 假设成功条件是掷出大于等于 successThreshold 的点数
		if diceRoll >= successThreshold {
			successes++
		}
	}

	return float64(successes) / float64(numTrials)
}

// 蒙特卡洛方法求解Buffon's针问题估算π
func monteCarloBuffonNeedle(numTrials int, needleLength, lineSpacing float64) float64 {
	intersections := 0

	for i := 0; i < numTrials; i++ {
		// 随机生成针的中心位置和角度
		centerY := rand.Float64() * lineSpacing
		angle := rand.Float64() * math.Pi // [0, π]

		// 计算针的两端到最近线的距离
		halfLength := needleLength / 2.0
		y1 := centerY - halfLength*math.Sin(angle)
		y2 := centerY + halfLength*math.Sin(angle)

		// 检查是否与线相交
		if int(y1/lineSpacing) != int(y2/lineSpacing) {
			intersections++
		}
	}

	// Buffon's针公式：π ≈ (2 * needleLength * numTrials) / (lineSpacing * intersections)
	if intersections == 0 {
		return 0.0 // 避免除零
	}
	return (2.0 * needleLength * float64(numTrials)) / (lineSpacing * float64(intersections))
}

// 蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
func monteCarloPiRejectionSampling(numSamples int) float64 {
	totalPoints := 0
	sumDistance := 0.0

	for totalPoints < numSamples {
		// 在 [-1, 1] × [-1, 1] 内随机生成点
		x := 2.0*rand.Float64() - 1.0
		y := 2.0*rand.Float64() - 1.0

		// 只考虑在单位圆内的点（拒绝采样）
		if x*x+y*y <= 1.0 {
			sumDistance += math.Sqrt(x*x + y*y)
			totalPoints++
		}
	}

	// 平均距离 ≈ 2/3，所以可以用来验证随机性
	return sumDistance / float64(numSamples)
}

// 蒙特卡洛方法估算高维积分
func monteCarloHighDimensionalIntegration(dimensions, numSamples int) float64 {
	sumValues := 0.0

	for i := 0; i < numSamples; i++ {
		product := 1.0
		for d := 0; d < dimensions; d++ {
			x := rand.Float64()
			product *= x // 计算 ∏ x_i
		}
		sumValues += product
	}

	// 在 [0,1]^d 空间内，∫∏ x_i dx = 1/(d+1)^d
	return sumValues / float64(numSamples)
}

// 蒙特卡洛方法模拟排队论问题
func monteCarloQueueSimulation(numCustomers int, arrivalRate, serviceRate float64) float64 {
	totalTime := 0.0

	for i := 0; i < numCustomers; i++ {
		// 顾客到达时间间隔（指数分布）
		arrivalTime := -math.Log(rand.Float64()) / arrivalRate

		// 服务时间（指数分布）
		serviceTime := -math.Log(rand.Float64()) / serviceRate
		totalTime += serviceTime

		_ = arrivalTime // 避免未使用变量警告
	}

	return totalTime / float64(numCustomers) // 平均服务时间
}

func main() {
	rand.Seed(time.Now().UnixNano())

	fmt.Println("=== 蒙特卡洛算法演示 ===\n")

	// 测试π估算
	fmt.Println("1. 蒙特卡洛方法估算π")
	samples := 1000000
	piEstimate := monteCarloPi(samples)
	fmt.Printf("采样数: %d\n", samples)
	fmt.Printf("π估算值: %.6f\n", piEstimate)
	fmt.Printf("π真实值: %.6f\n", math.Pi)
	fmt.Printf("误差: %.6f\n\n", math.Abs(piEstimate-math.Pi))

	// 测试数值积分
	fmt.Println("2. 蒙特卡洛方法计算积分")
	fmt.Println("计算: ∫[0,1] x² dx")
	integralEst := monteCarloIntegration(funcXSquared, 0.0, 1.0, 100000)
	fmt.Printf("估算值: %.6f\n", integralEst)
	fmt.Printf("真实值: %.6f\n", 1.0/3.0)
	fmt.Printf("误差: %.6f\n\n", math.Abs(integralEst-1.0/3.0))

	fmt.Println("计算: ∫[0,π] sin(x) dx")
	integralEst = monteCarloIntegration(funcSin, 0.0, math.Pi, 100000)
	fmt.Printf("估算值: %.6f\n", integralEst)
	fmt.Printf("真实值: %.6f\n", 2.0)
	fmt.Printf("误差: %.6f\n\n", math.Abs(integralEst-2.0))

	// 测试概率估算
	fmt.Println("3. 蒙特卡洛方法估算概率")
	fmt.Println("模拟掷骰子，求掷出≥4点的概率")
	probEstimate := monteCarloProbability(100000, 4)
	fmt.Printf("估算概率: %.6f\n", probEstimate)
	fmt.Printf("理论概率: %.6f\n", 3.0/6.0)
	fmt.Printf("误差: %.6f\n\n", math.Abs(probEstimate-3.0/6.0))

	// 测试Buffon's针问题
	fmt.Println("4. Buffon's针问题估算π")
	needleLength := 1.0
	lineSpacing := 2.0
	piBuffon := monteCarloBuffonNeedle(100000, needleLength, lineSpacing)
	fmt.Printf("针长度: %.1f, 线间距: %.1f\n", needleLength, lineSpacing)
	fmt.Printf("π估算值: %.6f\n", piBuffon)
	fmt.Printf("π真实值: %.6f\n", math.Pi)
	fmt.Printf("误差: %.6f\n\n", math.Abs(piBuffon-math.Pi))

	// 测试拒绝采样
	fmt.Println("5. 蒙特卡洛拒绝采样")
	avgDistance := monteCarloPiRejectionSampling(100000)
	fmt.Printf("单位圆内点到原点的平均距离: %.6f\n", avgDistance)
	fmt.Printf("理论值: %.6f\n", 2.0/3.0)
	fmt.Printf("误差: %.6f\n\n", math.Abs(avgDistance-2.0/3.0))

	// 测试高维积分
	fmt.Println("6. 蒙特卡洛高维积分")
	dimensions := 5
	highDimIntegral := monteCarloHighDimensionalIntegration(dimensions, 100000)
	theoreticalValue := 1.0 / math.Pow(float64(dimensions+1), float64(dimensions))
	fmt.Printf("%d维积分 ∫[0,1]^%d ∏x_i dx\n", dimensions, dimensions)
	fmt.Printf("估算值: %.6f\n", highDimIntegral)
	fmt.Printf("理论值: %.6f\n", theoreticalValue)
	fmt.Printf("误差: %.6f\n\n", math.Abs(highDimIntegral-theoreticalValue))

	// 测试排队论模拟
	fmt.Println("7. 蒙特卡洛排队论模拟")
	numCustomers := 1000
	arrivalRate := 2.0 // 每分钟2个顾客
	serviceRate := 3.0 // 每分钟服务3个顾客
	avgServiceTime := monteCarloQueueSimulation(numCustomers, arrivalRate, serviceRate)
	fmt.Printf("顾客数: %d\n", numCustomers)
	fmt.Printf("到达率: %.1f/分钟, 服务率: %.1f/分钟\n", arrivalRate, serviceRate)
	fmt.Printf("平均服务时间: %.6f分钟\n", avgServiceTime)
	fmt.Printf("理论平均服务时间: %.6f分钟\n", 1.0/serviceRate)
}
