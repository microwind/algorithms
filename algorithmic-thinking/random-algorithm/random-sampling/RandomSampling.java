package randomalgorithm.randomsampling;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * 随机采样（Reservoir Sampling）- Java 版本
 *
 * 适用于「数据流」场景：数据一条条到达，事先不知道总数 n，
 * 但希望最终能从所有元素中「等概率」抽取 k 个样本。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(k)
 */
public class RandomSampling {

    private static final Random RANDOM = new Random();

    /**
     * 标准水库采样：从 data 中随机选择 k 个元素
     *
     * @param data 可迭代的数据源（可以是列表、流式数据等）
     * @param k    采样数量
     * @param <T>  元素类型
     * @return 等概率抽取的 k 个样本（若数据量 < k，则返回全部）
     */
    public static <T> List<T> reservoirSample(Iterable<T> data, int k) {
        List<T> reservoir = new ArrayList<>(k);
        int i = 0;

        for (T item : data) {
            if (i < k) {
                // 前 k 个元素直接放入水池
                reservoir.add(item);
            } else {
                // 对于第 i 个元素，以 k/(i+1) 的概率替换
                int j = RANDOM.nextInt(i + 1); // [0, i]
                if (j < k) {
                    reservoir.set(j, item);
                }
            }
            i++;
        }

        return reservoir;
    }

    public static void main(String[] args) {
        System.out.println("========== Random Sampling (Java) ==========");

        List<Integer> data = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            data.add(i);
        }
        System.out.println("数据: " + data);

        int k = 3;
        for (int t = 1; t <= 3; t++) {
            List<Integer> sample = reservoirSample(data, k);
            System.out.println("第 " + t + " 次采样: " + sample);
        }
    }
}

