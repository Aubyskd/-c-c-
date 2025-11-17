#include<stdio.h>
#include<math.h>
//我去我真的是天才吧
//我去我真的是天才吧
//我去我真的是天才吧
//我去我真的是天才吧

//渲染参数配置
const int max_iterations = 128;//光线步进最大迭代次数
const float stop_threshold = 0.01f;//表面检测阈值
const float grad_step = 0.01f;//法向量步长
const float clip_far = 10.0f;//远裁剪面距离
//常量定义区
const float PI = 3.14159265359f;
const float PI2 = 6.28318530718f;
const float DEG_TO_RAD = PI / 180.0f;
//结构定义区
typedef struct 
{ 
	float x, y; 
}vec2;//2D变化
typedef struct 
{ 
	float x, y, z; 
}vec3;//3D变化
typedef struct 
{ 
	float m[9]; 
}mat3;//3，3矩阵，行优先储存

//光源位置
const vec3 light_pos = { 20.0f,50.0f,20.0f };

//函数定义区
float min(float a, float b) 
{ 
	return a < b ? a : b; 
}
float max(float a, float b) 
{ 
	return a > b ? a : b; 
}
float clamp(float f, float a, float b)
{
	return max(min(f, b), a);  //限制
}
//2D向量运算
vec2 make2(float x, float y)
{
	vec2 r = { x,y };
	return r;
}
vec2 add2(vec2 a, vec2 b)
{
	vec2 r = { a.x + b.x,a.y + b.y };
	return r;
}
vec2 sub2(vec2 a, vec2 b)
{
	vec2 r = { a.x - b.x,a.y - b.y };
	return r;
}

float dot2(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}//2D向量点积
float length2(vec2 v)
{
	return sqrt(dot2(v, v));
}//2D向量长度
//3D向量运算
vec3 make3(float x, float y, float z)
{
	vec3 r = { x,y,z };
	return r;
}
vec3 add3(vec3 a, vec3 b)
{
	vec3 r = { a.x + b.x,a.y + b.y,a.z + b.z };
	return r;
}
vec3 sub3(vec3 a, vec3 b)
{
	vec3 r = { a.x - b.x,a.y - b.y,a.z - b.z };
	return r;
}
vec3 mul3(vec3 a, vec3 b)
{
	vec3 r = { a.x * b.x,a.y * b.y,a.z * b.z };
	return r;
}//3D向量分量乘
vec3 scale3(vec3 v, float s)
{
	vec3 r = { v.x * s,v.y * s,v.z * s };
	return r;
}

float dot3(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}//3D向量点积
float length3(vec3 v)
{
	return sqrt(dot3(v, v));
}//3D向量长度

vec3 normalize3(vec3 v)
{
	return scale3(v, 1.0f / length3(v));
}//3D向量归一化

//3x3矩阵运算
vec3 mul(mat3 m, vec3 v)
{
	// 生成绕X轴和Y轴的复合旋转矩阵
	return make3(
		m.m[0] * v.x + m.m[3] * v.y + m.m[6] * v.z,
		m.m[1] * v.x + m.m[4] * v.y + m.m[7] * v.z,
		m.m[2] * v.x + m.m[5] * v.y + m.m[8] * v.z);
	
}

mat3 rotationXY(float x, float y)
{
	vec2 c = { cos(x),cos(y) }, s = { sin(x),sin(y) };
	mat3 m = {
		c.y,      0.0f,-s.y,
		s.y * s.x,c.x, c.y * s.x,
		s.y * c.x,-s.x,c.y * c.x
	};
	return m;
}

// ==================== 距离场运算 ====================
// 这些函数用于组合不同的距离场形状
float opI(float d1, float d2)
{
	return max(d1, d2);
}// 交集（Intersection）

float opU(float d1, float d2)
{
	return min(d1, d2);
}// 并集（Union）

float opS(float d1, float d2)
{
	return max(-d1, d2);
}// 差集（Subtraction）

// ==================== 花瓣距离场 ====================

float sdPetal(vec3 p, float s)
{
	// 花瓣的形状函数：使用数学公式定义花瓣的几何形状
	// 通过缩放和位移调整花瓣形态
	p = add3(mul3(p, make3(0.8f, 1.5f, 0.8f)), make3(0.1f, 0.0f, 0.0f));
	// 将3D点投影到2D平面以简化计算
	vec2 q = make2(length2(make2(p.x, p.z)), p.y);
	// 定义花瓣的下半部分
	float lower = length2(q) - 1.0f;
	lower = opS(length2(q) - 0.97f, lower);// 创建内凹效果
	lower = opI(lower, q.y);// 限制在y轴以下
	// 定义花瓣的上半部分
	float upper = length2(sub2(q, make2(s, 0.0f))) + 1.0f - s;
	upper = opS(upper, length2(sub2(q, make2(s, 0.0f))) + 0.97f - s);
	upper = opI(upper, -q.y);// 限制在y轴以上
	upper = opI(upper, q.x - 2.0f); // 限制宽度

	// 定义花瓣的有效区域
	float region = length3(sub3(p, make3(1.0f, 0.0f, 0.0f))) - 1.0f;
	// 组合上半部分、下半部分和区域限制
	return opI(opU(upper, lower), region);
}
// ==================== 玫瑰花距离场 ====================
float map(vec3 p)
{
	// 这是整个玫瑰花的距离场函数
	// 通过迭代多个花瓣来创建完整的玫瑰花

	// d: 最小距离, s: 花瓣缩放参数
	float d = 1000.0f, s = 2.0f;

	// 创建旋转矩阵，使用黄金比例角度 (0.618034 ≈ φ-1)
	mat3 r = rotationXY(0.1f, PI2 * 0.618034f);
	// 调整旋转矩阵的缩放，创造螺旋效果
	r.m[0] *= 1.08f; r.m[1] *= 1.08f; r.m[2] *= 1.08f;
	r.m[3] *= 0.995f; r.m[4] *= 0.995f; r.m[5] *= 0.995f;
	r.m[6] *= 1.08f; r.m[7] *= 1.08f; r.m[8] *= 1.08f;

	// 迭代21次，每次添加一个花瓣
	for (int i = 0; i < 21; i++)
	{
		d = opU(d, sdPetal(p, s));// 将当前花瓣与之前的结果合并
		p = mul(r, p);// 旋转点
		p = add3(p, make3(0.0, -0.02, 0.0)); // 向下移动
		s *= 1.05f; // 逐渐增大花瓣尺寸
	}
	return d;
}
// ==================== 法向量计算 ====================
vec3 gradient(vec3 pos)
{
	// 使用数值微分计算距离场的梯度（法向量）
	const vec3 dx = { grad_step,0.0,0.0 };
	const vec3 dy = { 0.0,grad_step,0.0 };
	const vec3 dz = { 0.0,0.0,grad_step };
	return normalize3(make3(
		map(add3(pos, dx)) - map(sub3(pos, dx)),
		map(add3(pos, dy)) - map(sub3(pos, dy)),
		map(add3(pos, dz)) - map(sub3(pos, dz))));
}
// ==================== 光线步进算法 ====================
float ray_marching(vec3 origin, vec3 dir, float start, float end)
{
	// Ray Marching: 沿着光线方向逐步前进，直到碰到表面
	float depth = start;
	for (int i = 0; i < max_iterations; i++)
	{
		// 计算当前位置到最近表面的距离
		float dist = map(add3(origin, scale3(dir, depth)));
		// 如果距离小于阈值，说明到达了表面
		if (dist < stop_threshold)
			return depth;
		// 沿着光线方向前进，步长与距离成比例
		depth += dist * 0.3;
		// 如果超过最大距离，返回背景
		if (depth >= end)
			return end;
	}
	return end;
}
// ==================== 光照计算 ====================
float shading(vec3 v, vec3 n, vec3 eye)
{
	// 计算表面点的光照效果
	vec3 ev = normalize3(sub3(v, eye));// 视线方向
	vec3 v1 = normalize3(sub3(light_pos, v));// 光线方向
	float diffuse = max(dot3(v1, n), 0.0f);// 漫反射
	// 高光计算
	vec3 h = normalize3(sub3(v1, ev));// 半程向量
	float rim = pow(1.0f - max(-dot3(n, ev), 0.0f), 2.0f) * 0.15f;// 轮廓光
	float ao = clamp(v.y * 0.5f + 0.5f, 0.0f, 1.0f);// 环境光遮蔽
	return clamp(diffuse + rim, 0.0f, 1.0f) * ao;
}
// ==================== 相机设置 ====================
vec3 ray_dir(float fov, vec2 pos)
{
	// 根据视场角和屏幕坐标计算光线方向
	vec3 r = {
		pos.x,pos.y,-tan((90.0f - fov * 0.5f) * DEG_TO_RAD)
	};
	return normalize3(r);
}
// ==================== 主要渲染函数 ====================
float f(vec2 fragCoord)
{
	// 对屏幕上的每个像素计算颜色值
	vec3 dir = ray_dir(45.0f, fragCoord);// 计算光线方向
	vec3 eye = { 0.0f,0.0f,6.0f };// 相机位置
	mat3 rot = rotationXY(-1.0f, 1.0f);// 相机旋转

	dir = mul(rot, dir);// 应用相机旋转到光线方向
	eye = mul(rot, eye);// 应用相机旋转到相机位置

	// 进行光线步进，找到表面
	float depth = ray_marching(eye, dir, 0.0f, clip_far);
	vec3 pos = add3(eye, scale3(dir, depth));// 计算表面点位置
	if (depth >= clip_far)
		return 0.0f;// 背景（黑色）
	else
		return shading(pos, gradient(pos), eye);// 计算光照
}
// ==================== 主程序 ====================
int main()
{
	printf("\033[96m");  //设置红色前景色
	//遍历屏幕上的每个像素
	for (int y = 0; y < 80; y++)
	{
		for (int x = 0; x < 160; x++)
		{
			float intensity = f(make2(
				(x / 160.0f - 0.5f) * 2.0f,
				(y / 80.0f - 0.5f) * -2.0f
			));

			// 根据强度选择颜色
			if (intensity > 0.8f)
				printf("\033[93m");  // 亮黄色
			else if (intensity > 0.5f)
				printf("\033[91m");  // 亮红色
			else if (intensity > 0.2f)
				printf("\033[95m");  // 亮紫色
			else
				printf("\033[32m");  

			int charIndex = (int)(intensity * 11.0f);
			charIndex = clamp(charIndex, 0, 11);
			putchar("  .,-:;+=*#@"[charIndex]);
		}
		putchar('\n');
	}
}