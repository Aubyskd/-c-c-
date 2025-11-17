/*
 * ========================================================================
 * 🌸 樱花夜景生成程序 - 详细注释版 🌸
 * ========================================================================
 *
 * 程序功能：使用递归分形算法生成美丽的樱花树林夜景
 * 核心技术：
 * 1. 递归分形 - 自相似的树形结构生成
 * 2. 概率控制 - 自然随机的分叉模式
 * 3. HSV颜色空间 - 柔和协调的色彩系统
 * 4. 防重叠算法 - 智能的空间布局
 * 5. 多层次渲染 - 丰富的视觉效果
 *
 * 作者学习要点：
 * - 理解递归在图形生成中的应用
 * - 掌握概率在自然模拟中的作用
 * - 学习颜色理论在程序中的实现
 * - 体会算法优化对性能的影响
 * ========================================================================
 */

 // ========================================================================
 // 头文件包含 - 引入必要的功能库
 // ========================================================================
#include<easyx.h>    // EasyX图形库 - 提供绘图功能
#include<math.h>     // 数学库 - 提供三角函数、常数等
#include<stdio.h>    // 标准输入输出库
#include<time.h>     // 时间库 - 用于随机种子
#include<vector>     // STL容器库 - 动态数组

// ========================================================================
// 全局常量定义 - 程序的基本参数
// ========================================================================
#define WIDTH 1200        // 窗口宽度（像素）
#define HEIGHT 800        // 窗口高度（像素）
#define PI 3.1415926      // 圆周率常数

// ========================================================================
// 核心算法参数 - 控制樱花树生成的关键数值
// ========================================================================
double shortRate = 0.65;      // 子枝长度比例（0.65表示子枝是父枝的65%长度）
double offsetAngle = PI / 6;  // 基础分叉角度（30度，控制枝干张开程度）

// ========================================================================
// 数据结构定义 - 组织和管理各种图形元素
// ========================================================================

/**
 * 树木位置结构体 - 用于防止树木重叠
 * 设计思路：记录每棵树的位置和影响范围，实现智能布局
 */
struct TreePosition {
	double x;        // 树木的X坐标
	double radius;   // 树木的影响半径（根据粗细计算）
};

/**
 * 星星结构体 - 定义夜空中的星星
 * 设计思路：不同亮度和颜色的星星营造层次感
 */
struct Star {
	double x, y;          // 星星坐标
	double brightness;    // 亮度值（0.0-1.0，影响大小和效果）
	COLORREF color;      // 星星颜色（RGB值）
};

/**
 * 月亮结构体 - 定义夜空中的月亮
 * 设计思路：单一月亮作为视觉焦点，增加浪漫氛围
 */
struct Moon {
	double x, y;        // 月亮坐标
	double radius;      // 月亮半径
	COLORREF color;     // 月亮颜色
};

/**
 * 装饰花瓣结构体 - 空中飘浮的静态花瓣
 * 设计思路：增加画面层次，营造花瓣飞舞的意境
 */
struct DecorationPetal {
	double x, y;        // 花瓣坐标
	double size;        // 花瓣大小
	COLORREF color;     // 花瓣颜色
	double rotation;    // 旋转角度（用于椭圆变形效果）
};

// ========================================================================
// 全局容器 - 存储所有图形元素
// ========================================================================
std::vector<TreePosition> treePositions;      // 存储所有树木位置
std::vector<Star> stars;                      // 存储所有星星
std::vector<DecorationPetal> decorationPetals; // 存储装饰花瓣
Moon moon;                                    // 月亮对象

// ========================================================================
// 颜色系统 - 全局颜色控制变量
// ========================================================================
/**
 * 当前树的花瓣颜色参数（全局变量）
 * 设计思路：在递归绘制过程中保持同一棵树的颜色一致性
 * HSV颜色空间：Hue(色相) Saturation(饱和度) Value(明度)
 */
double currentTreeHue = 320;         // 当前树的色相（粉色范围）
double currentTreeSaturation = 0.4;  // 当前树的饱和度（控制颜色浓淡）
double currentTreeBrightness = 0.9;  // 当前树的亮度（控制明暗）

// ========================================================================
// 工具函数 - 提供基础的数学和随机功能
// ========================================================================

/**
 * 数值映射函数 - 将一个范围的数值映射到另一个范围
 * @param input: 输入值
 * @param min, max: 输入范围
 * @param oMin, oMax: 输出范围
 * @return: 映射后的值
 *
 * 应用场景：将随机数[0,1]映射到任意范围[a,b]
 * 数学原理：线性插值 output = (input-min)/(max-min) * (oMax-oMin) + oMin
 */
double mapValue(double input, double min, double max, double oMin, double oMax)
{
	double output = 0;

	// 边界情况处理：输入值等于最小值时直接返回输出最小值
	if ((input - min) < 0.000001)  // 使用小数值避免浮点数精度问题
	{
		output = oMin;
	}
	else
	{
		// 线性映射公式
		output = (input - min) * (oMax - oMin) / (max - min) + oMin;
	}
	return output;
}

/**
 * 随机数生成函数 - 生成指定范围内的随机浮点数
 * @param min: 最小值
 * @param max: 最大值
 * @return: [min, max]范围内的随机数
 *
 * 实现原理：
 * 1. rand()生成[0, RAND_MAX]的整数
 * 2. 除以RAND_MAX得到[0, 1]的浮点数
 * 3. 使用mapValue映射到目标范围
 */
double randBetween(double min, double max)
{
	double t = rand() / double(RAND_MAX);  // 生成[0,1]的随机数
	double ret = mapValue(t, 0, 1, min, max);  // 映射到目标范围
	return ret;
}

// ========================================================================
// 防重叠算法 - 智能树木布局系统
// ========================================================================

/**
 * 检查树木位置是否有效（不重叠）
 * @param x: 待检查的X坐标
 * @param radius: 树木影响半径
 * @return: true表示位置有效，false表示会重叠
 *
 * 算法思路：
 * 1. 遍历所有已存在的树木位置
 * 2. 计算新位置与现有树木的距离
 * 3. 如果距离小于两树影响半径之和的1.5倍，则认为重叠
 * 4. 1.5倍系数确保树木间有适当间距，避免过于拥挤
 */
bool isPositionValid(double x, double radius) {
	for (const auto& tree : treePositions) {
		double distance = abs(x - tree.x);  // 计算水平距离
		if (distance < (radius + tree.radius) * 1.5) {  // 1.5倍间距防止拥挤
			return false;  // 位置无效，会重叠
		}
	}
	return true;  // 位置有效，不会重叠
}

/**
 * 获取有效的树木位置 - 智能位置分配算法
 * @param minX, maxX: X坐标范围
 * @param radius: 树木影响半径
 * @param maxAttempts: 最大尝试次数（默认50次）
 * @return: 有效的X坐标
 *
 * 算法流程：
 * 1. 在指定范围内随机生成位置
 * 2. 检查位置是否与现有树木重叠
 * 3. 如果不重叠，记录位置并返回
 * 4. 如果重叠，重新生成（最多尝试50次）
 * 5. 50次后仍未找到，强制返回一个位置（避免死循环）
 */
double getValidTreePosition(double minX, double maxX, double radius, int maxAttempts = 50) {
	for (int i = 0; i < maxAttempts; i++) {
		double x = randBetween(minX, maxX);  // 随机生成X坐标
		if (isPositionValid(x, radius)) {    // 检查位置有效性
			treePositions.push_back({ x, radius });  // 记录有效位置
			return x;  // 返回有效坐标
		}
	}
	// 如果50次尝试都失败，强制返回一个位置（防止死循环）
	double x = randBetween(minX, maxX);
	treePositions.push_back({ x, radius });
	return x;
}

// ========================================================================
// 背景元素初始化函数 - 创建丰富的夜景背景
// ========================================================================

/**
 * 初始化星空背景 - 创建200颗不同类型的星星
 *
 * 设计理念：
 * - 70%白色星星（主体）
 * - 20%淡蓝色星星（冷色调）
 * - 10%暖黄色星星（暖色调）
 * - 不同亮度产生层次感
 */
void initStars() {
	stars.clear();  // 清空现有星星

	// 生成200颗随机星星
	for (int i = 0; i < 200; i++) {
		Star star;
		star.x = randBetween(0, WIDTH);              // 随机X坐标
		star.y = randBetween(0, HEIGHT * 0.75);     // 星星主要在上3/4区域
		star.brightness = randBetween(0.3, 1.0);    // 随机亮度

		// 根据概率分配星星颜色类型
		double colorType = randBetween(0, 1);
		if (colorType < 0.7) {
			// 70%概率：白色星星（经典夜空效果）
			int intensity = (int)(255 * star.brightness);
			star.color = RGB(intensity, intensity, intensity);
		}
		else if (colorType < 0.9) {
			// 20%概率：淡蓝色星星（冷色调，增加层次）
			star.color = RGB(200 * star.brightness, 220 * star.brightness, 255 * star.brightness);
		}
		else {
			// 10%概率：暖黄色星星（暖色调，营造温馨感）
			star.color = RGB(255 * star.brightness, 245 * star.brightness, 200 * star.brightness);
		}
		stars.push_back(star);  // 添加到星星容器
	}
}

/**
 * 初始化月亮 - 创建夜空中的月亮
 *
 * 设计思路：
 * - 位置：右上角区域（符合视觉习惯）
 * - 大小：随机半径40-60像素
 * - 颜色：淡黄色（温暖的月光效果）
 */
void initMoon() {
	moon.x = randBetween(WIDTH * 0.7, WIDTH * 0.9);   // 右上角X坐标
	moon.y = randBetween(HEIGHT * 0.1, HEIGHT * 0.3); // 右上角Y坐标
	moon.radius = randBetween(40, 60);                 // 随机半径
	moon.color = RGB(245, 245, 220);                   // 淡黄色月亮
}

/**
 * 初始化装饰花瓣 - 创建空中飘浮的静态花瓣
 *
 * 设计目的：
 * - 增加画面层次感
 * - 营造花瓣飞舞的浪漫氛围
 * - 与樱花树形成呼应
 */
void initDecorationPetals() {
	decorationPetals.clear();  // 清空现有花瓣

	// 生成30片装饰花瓣
	for (int i = 0; i < 30; i++) {
		DecorationPetal petal;
		petal.x = randBetween(0, WIDTH);              // 随机X坐标
		petal.y = randBetween(0, HEIGHT * 0.8);      // 主要在上4/5区域
		petal.size = randBetween(3, 8);              // 随机大小
		petal.rotation = randBetween(0, 2 * PI);     // 随机旋转角度

		// 使用柔和的粉色（与樱花呼应）
		double hue = randBetween(310, 330);      // 粉色色相范围
		double sat = randBetween(0.2, 0.5);     // 中等饱和度
		double bright = randBetween(0.6, 0.9);  // 较高亮度
		petal.color = HSVtoRGB(hue, sat, bright);

		decorationPetals.push_back(petal);  // 添加到花瓣容器
	}
}

// ========================================================================
// 背景渲染函数 - 绘制完整的夜景背景
// ========================================================================

/**
 * 绘制星空背景 - 渲染完整的夜景背景
 *
 * 渲染顺序：
 * 1. 渐变夜空背景
 * 2. 月亮及其表面纹理
 * 3. 不同效果的星星
 * 4. 飘浮的装饰花瓣
 */
void drawStarryBackground() {
	// ====================================================================
	// 第一步：绘制渐变夜空背景
	// ====================================================================
	/**
	 * 渐变算法：逐行绘制，颜色从上到下渐变
	 * 上方：深蓝紫色（夜空深处）
	 * 下方：稍亮的蓝紫色（地平线附近）
	 */
	for (int y = 0; y < HEIGHT; y++) {
		double ratio = (double)y / HEIGHT;        // 计算当前行的比例[0,1]
		int r = (int)(8 + ratio * 18);           // 红色分量：8→26
		int g = (int)(5 + ratio * 15);           // 绿色分量：5→20
		int b = (int)(25 + ratio * 40);          // 蓝色分量：25→65
		setlinecolor(RGB(r, g, b));              // 设置当前行颜色
		line(0, y, WIDTH, y);                    // 绘制水平线
	}

	// ====================================================================
	// 第二步：绘制月亮及其表面纹理
	// ====================================================================
	setfillcolor(moon.color);                    // 设置月亮主体颜色
	setlinecolor(RGB(200, 200, 180));           // 设置月亮边缘颜色
	fillcircle(moon.x, moon.y, moon.radius);    // 绘制月亮主体

	// 绘制月球表面的陨石坑纹理（增加真实感）
	setfillcolor(RGB(220, 220, 200));           // 稍亮的纹理颜色
	// 大陨石坑
	fillcircle(moon.x - moon.radius * 0.3, moon.y - moon.radius * 0.2, moon.radius * 0.15);
	// 中陨石坑
	fillcircle(moon.x + moon.radius * 0.2, moon.y + moon.radius * 0.3, moon.radius * 0.1);
	// 小陨石坑
	fillcircle(moon.x - moon.radius * 0.1, moon.y + moon.radius * 0.4, moon.radius * 0.08);

	// ====================================================================
	// 第三步：绘制不同效果的星星
	// ====================================================================
	/**
	 * 星星渲染策略：根据亮度分级渲染
	 * - 最亮星（>0.85）：十字+对角线闪烁效果
	 * - 亮星（>0.7）：十字形效果
	 * - 中等星（>0.5）：小圆点
	 * - 暗星（≤0.5）：单像素点
	 */
	for (const auto& star : stars) {
		setfillcolor(star.color);
		setlinecolor(star.color);

		if (star.brightness > 0.85) {
			// 最亮星：复杂闪烁效果
			fillcircle(star.x, star.y, 2);                              // 中心圆点
			line(star.x - 4, star.y, star.x + 4, star.y);             // 水平线
			line(star.x, star.y - 4, star.x, star.y + 4);             // 垂直线
			line(star.x - 2, star.y - 2, star.x + 2, star.y + 2);     // 对角线1
			line(star.x - 2, star.y + 2, star.x + 2, star.y - 2);     // 对角线2
		}
		else if (star.brightness > 0.7) {
			// 亮星：十字形效果
			fillcircle(star.x, star.y, 2);                              // 中心圆点
			line(star.x - 3, star.y, star.x + 3, star.y);             // 水平线
			line(star.x, star.y - 3, star.x, star.y + 3);             // 垂直线
		}
		else if (star.brightness > 0.5) {
			// 中等亮度：简单圆点
			fillcircle(star.x, star.y, 1);
		}
		else {
			// 暗星：单像素点
			putpixel(star.x, star.y, star.color);
		}
	}

	// ====================================================================
	// 第四步：绘制飘浮的装饰花瓣
	// ====================================================================
	/**
	 * 花瓣渲染：椭圆形状，根据旋转角度动态变形
	 * 变形算法：使用三角函数模拟花瓣在空中的翻转效果
	 */
	for (const auto& petal : decorationPetals) {
		setfillcolor(petal.color);
		setlinecolor(petal.color);

		// 根据旋转角度计算椭圆的宽度和高度
		double petalWidth = petal.size * (0.8 + 0.3 * sin(petal.rotation));   // 宽度变化
		double petalHeight = petal.size * (0.6 + 0.2 * cos(petal.rotation));  // 高度变化

		// 绘制椭圆花瓣
		fillellipse(petal.x - petalWidth / 2, petal.y - petalHeight / 2,
			petal.x + petalWidth / 2, petal.y + petalHeight / 2);
	}
}

// ========================================================================
// 核心递归函数 - 樱花树生成算法
// ========================================================================

/**
 * 递归绘制樱花树 - 程序的核心算法
 *
 * @param x, y: 当前枝干的起始坐标
 * @param length: 当前枝干的长度
 * @param angle: 当前枝干的生长角度（弧度）
 * @param thick: 当前枝干的粗细
 * @param flower: 当前递归层数（用于控制递归深度和颜色变化）
 *
 * 算法核心思想：
 * 1. 分形递归：每个枝干可以分出多个子枝干
 * 2. 自然随机：通过概率控制分叉的随机性
 * 3. 层次控制：通过长度阈值和层数限制递归深度
 * 4. 终止条件：当枝干足够小时绘制花朵而非继续分叉
 */
void draw(double x, double y, double length, double angle, double thick, int flower)
{
	// ====================================================================
	// 第一步：计算并绘制当前枝干
	// ====================================================================

	// 使用三角函数计算枝干终点坐标
	double x_end = x + length * cos(angle);  // 终点X = 起点X + 长度×cos(角度)
	double y_end = y + length * sin(angle);  // 终点Y = 起点Y + 长度×sin(角度)

	// 设置枝干绘制样式
	setlinestyle(PS_SOLID, thick);  // 实线，指定粗细

	// 枝干颜色：棕色系，随层数变化（越高层越亮）
	COLORREF branchColor = HSVtoRGB(
		randBetween(10, 25),                           // 色相：棕色范围
		randBetween(0.6, 0.8),                        // 饱和度：中高饱和度
		randBetween(0.3, 0.5) + flower * 0.03        // 亮度：随层数增加而变亮
	);
	setlinecolor(branchColor);

	// 绘制当前枝干
	line(x, y, x_end, y_end);

	// ====================================================================
	// 第二步：计算子枝干参数
	// ====================================================================

	int child = flower + 1;  // 子枝干层数

	// 计算子枝干长度（引入随机性，让树形更自然）
	double childrenlen = shortRate * length * randBetween(0.7, 1.0);  // 基础长度×随机因子
	double left = childrenlen * randBetween(0.8, 1.2);               // 左枝长度
	double mid = childrenlen * randBetween(0.8, 1.2);                // 中枝长度
	double right = childrenlen * randBetween(0.8, 1.2);              // 右枝长度

	// ====================================================================
	// 第三步：递归分叉判断
	// ====================================================================

	/**
	 * 递归继续条件：
	 * 1. 子枝干长度 >= 0.8（避免枝干过小）
	 * 2. 递归层数 <= 14（避免无限递归）
	 *
	 * 满足条件：继续分叉
	 * 不满足条件：绘制花朵（递归终止）
	 */
	if (childrenlen >= 0.8 && child <= 14)
	{
		// 计算子枝干粗细（逐层递减）
		double childThick = thick * randBetween(0.6, 0.85);
		if (childThick < 1.0) {
			childThick = 1.0;  // 最小粗细限制
		}

		// 计算角度变化范围
		double angleVariation = offsetAngle * randBetween(0.7, 1.8);

		// ================================================================
		// 六种分叉类型：创造丰富的树形结构
		// ================================================================

		// 【分叉类型1】左枝 - 85%概率生成
		if (randBetween(0, 1) < 0.85) {
			double leftAngle = angle + angleVariation * randBetween(0.5, 1.3);
			draw(x_end, y_end, left, leftAngle, childThick, child);  // 递归调用
		}

		// 【分叉类型2】左上枝 - 55%概率生成（仅前10层）
		if (randBetween(0, 1) < 0.55 && child <= 10) {
			double leftUpAngle = angle + angleVariation * randBetween(1.2, 1.8);
			double leftUpLen = childrenlen * randBetween(0.6, 0.9);
			draw(x_end, y_end, leftUpLen, leftUpAngle, childThick * 0.8, child);
		}

		// 【分叉类型3】中枝 - 78%概率生成
		if (randBetween(0, 1) < 0.78) {
			double midAngle = angle + offsetAngle * randBetween(-0.9, 0.9);
			draw(x_end, y_end, mid, midAngle, childThick, child);
		}

		// 【分叉类型4】右枝 - 85%概率生成
		if (randBetween(0, 1) < 0.85) {
			double rightAngle = angle - angleVariation * randBetween(0.5, 1.3);
			draw(x_end, y_end, right, rightAngle, childThick, child);
		}

		// 【分叉类型5】右上枝 - 55%概率生成（仅前10层）
		if (randBetween(0, 1) < 0.55 && child <= 10) {
			double rightUpAngle = angle - angleVariation * randBetween(1.2, 1.8);
			double rightUpLen = childrenlen * randBetween(0.6, 0.9);
			draw(x_end, y_end, rightUpLen, rightUpAngle, childThick * 0.8, child);
		}

		// 【分叉类型6】额外小分叉 - 40%概率生成（仅前8层）
		if (randBetween(0, 1) < 0.40 && child <= 8) {
			double extraAngle = angle + randBetween(-PI / 3, PI / 3);  // 随机方向
			double extraLen = childrenlen * randBetween(0.4, 0.7);
			draw(x_end, y_end, extraLen, extraAngle, childThick * 0.6, child);
		}
	}
	// ====================================================================
	// 第四步：递归终止 - 绘制花朵
	// ====================================================================
	else
	{
		setlinestyle(PS_SOLID, 1);  // 花朵使用细线条

		// 花朵颜色计算：基于全局颜色参数，添加微小随机变化
		double hueVariation = randBetween(-5, 5);        // 色相微调
		double satVariation = randBetween(-0.05, 0.05);  // 饱和度微调
		double brightVariation = randBetween(-0.05, 0.05); // 亮度微调

		// 计算最终花朵颜色
		COLORREF flowerColor = HSVtoRGB(
			currentTreeHue + hueVariation,           // 色相
			currentTreeSaturation + satVariation,    // 饱和度
			currentTreeBrightness + brightVariation  // 亮度
		);
		setlinecolor(flowerColor);
		setfillcolor(flowerColor);

		// 计算花朵大小（基于枝干长度，添加随机性）
		double flowerSize = (childrenlen / 2) * randBetween(0.8, 1.5);
		if (flowerSize < 2) flowerSize = 2;  // 最小尺寸限制
		if (flowerSize > 8) flowerSize = 8;  // 最大尺寸限制

		// 绘制花朵主体
		fillcircle(x_end, y_end, flowerSize);

		// 28%概率绘制花瓣效果（增加花朵层次感）
		if (randBetween(0, 1) < 0.28) {
			// 花瓣颜色：比主体稍亮
			COLORREF petalColor = HSVtoRGB(
				currentTreeHue + hueVariation + randBetween(-3, 3),
				currentTreeSaturation + satVariation + randBetween(-0.03, 0.03),
				currentTreeBrightness + brightVariation + randBetween(0, 0.05)
			);
			setfillcolor(petalColor);

			// 绘制5个小花瓣（五瓣花效果）
			for (int i = 0; i < 5; i++) {
				double petalAngle = (2 * PI * i) / 5;  // 每个花瓣间隔72度
				double petalX = x_end + (flowerSize * 0.7) * cos(petalAngle);
				double petalY = y_end + (flowerSize * 0.7) * sin(petalAngle);
				fillcircle(petalX, petalY, flowerSize * 0.4);
			}
		}
	}

	// ====================================================================
	// 性能优化：控制刷新频率
	// ====================================================================
	/**
	 * 性能优化策略：
	 * - 仅5%概率执行刷新操作
	 * - 避免每次递归都刷新屏幕
	 * - 在大量树木绘制时显著提升性能
	 */
	if (randBetween(0, 1) < 0.05) {
		FlushBatchDraw();
	}
}

// ========================================================================
// 主函数 - 程序入口和整体流程控制
// ========================================================================

/**
 * 主函数 - 程序执行流程：
 * 1. 初始化图形环境
 * 2. 生成背景元素
 * 3. 生成樱花树林
 * 4. 进入显示循环
 */
int main()
{
	// ====================================================================
	// 第一步：程序初始化
	// ====================================================================

	// 设置随机种子（确保每次运行产生不同结果）
	srand(time(NULL));

	// 初始化图形窗口
	initgraph(WIDTH, HEIGHT);  // 创建指定大小的窗口
	cleardevice();             // 清空屏幕

	// 开启批量绘制模式（性能优化）
	BeginBatchDraw();

	// ====================================================================
	// 第二步：初始化所有背景元素
	// ====================================================================

	initStars();              // 初始化200颗星星
	initMoon();               // 初始化月亮
	initDecorationPetals();   // 初始化30片装饰花瓣

	// 绘制完整的星空背景
	drawStarryBackground();

	// ====================================================================
	// 第三步：樱花树林生成
	// ====================================================================

	// 清空树木位置记录（为新的布局做准备）
	treePositions.clear();

	// 随机确定树木数量（8-12棵）
	int treeCount = randBetween(8, 12);

	// 逐棵生成樱花树
	for (int i = 0; i < treeCount; i++)
	{
		// ================================================================
		// 为每棵树设置独特的花瓣颜色
		// ================================================================
		/**
		 * 颜色设计理念：
		 * - 色相：310-330度（粉色范围）
		 * - 饱和度：0.15-0.4（柔和不刺眼）
		 * - 亮度：0.85-1.0（明亮淡雅）
		 */
		currentTreeHue = randBetween(310, 330);        // 粉色色相
		currentTreeSaturation = randBetween(0.15, 0.4); // 低饱和度
		currentTreeBrightness = randBetween(0.85, 1.0); // 高亮度

		// ================================================================
		// 根据序号分配树木大小（创造层次感）
		// ================================================================
		double treeThickness, treeHeight, radius;

		if (i < treeCount / 3) {
			// 前1/3：大树（前景）
			treeThickness = randBetween(15, 25);                    // 粗壮主干
			treeHeight = randBetween(0.4, 0.6) * HEIGHT * shortRate; // 较高
			radius = treeThickness * 3;                             // 大影响范围
		}
		else if (i < treeCount * 2 / 3) {
			// 中1/3：中树（中景）
			treeThickness = randBetween(10, 18);                    // 中等主干
			treeHeight = randBetween(0.3, 0.45) * HEIGHT * shortRate; // 中等高度
			radius = treeThickness * 2.5;                          // 中等影响范围
		}
		else {
			// 后1/3：小树（背景）
			treeThickness = randBetween(6, 12);                     // 细小主干
			treeHeight = randBetween(0.2, 0.35) * HEIGHT * shortRate; // 较矮
			radius = treeThickness * 2;                             // 小影响范围
		}

		// ================================================================
		// 获取有效位置并绘制树木
		// ================================================================

		// 获取不重叠的树木位置
		double treeX = getValidTreePosition(WIDTH * 0.1, WIDTH * 0.9, radius);

		// 树木生长角度（基本向上，略有倾斜）
		double treeAngle = -PI / 2 + randBetween(-PI / 12, PI / 12);  // -90°±15°

		// 调用递归函数绘制完整的樱花树
		draw(treeX, HEIGHT, treeHeight, treeAngle, treeThickness, 1);
	}

	// ====================================================================
	// 第四步：最终渲染和显示循环
	// ====================================================================

	// 刷新屏幕，显示完整画面
	FlushBatchDraw();

	// 静态显示循环（程序保持运行状态）
	while (true)
	{
		Sleep(100);  // 休眠100毫秒，减少CPU占用
	}

	return 0;  // 程序正常结束
}

/*
 * ========================================================================
 * 🌸 学习总结 🌸
 * ========================================================================
 *
 * 通过这个樱花夜景程序，你可以学到：
 *
 * 1. 【递归算法】
 *    - 分形几何在自然模拟中的应用
 *    - 递归终止条件的设计
 *    - 参数传递和状态管理
 *
 * 2. 【概率与随机性】
 *    - 如何用概率控制自然现象的随机性
 *    - 随机数在图形生成中的巧妙运用
 *    - 平衡随机性与美感的技巧
 *
 * 3. 【颜色理论】
 *    - HSV颜色空间的优势
 *    - 色彩和谐的数学原理
 *    - 颜色渐变和变化的实现
 *
 * 4. 【算法优化】
 *    - 防重叠算法的设计思路
 *    - 性能优化的实用技巧
 *    - 内存管理和数据结构选择
 *
 * 5. 【图形编程】
 *    - 坐标系统和三角函数应用
 *    - 图形绘制的基本原理
 *    - 批量渲染和刷新控制
 *
 * 6. 【程序设计】
 *    - 模块化设计的重要性
 *    - 参数化编程的灵活性
 *    - 代码可读性和维护性
 *
 * 继续探索，让编程成为创造美的工具！🎨✨
 * ========================================================================
 */