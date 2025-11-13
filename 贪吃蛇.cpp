#include <Windows.h>
#include <CommCtrl.h>
#include <ctime>

#pragma comment(lib, "Comctl32.lib")
// 隐藏控制台（Windows 子系统入口）
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

// 更稳健地找到桌面图标的 ListView 句柄（兼容 WorkerW）
static HWND GetDesktopListView()
{
	HWND progman = FindWindowA("Progman", "Program Manager");
	HWND defview = nullptr;
	HWND listview = nullptr;

	// 直接在 Progman 下找
	defview = FindWindowExA(progman, nullptr, "SHELLDLL_DefView", nullptr);
	if (defview)
	{
		listview = FindWindowExA(defview, nullptr, "SysListView32", NULL);
		if (listview) return listview;
	}

	// 某些系统 SHELLDLL_DefView 在 WorkerW 下
	HWND workerw = nullptr;
	while ((workerw = FindWindowExA(nullptr, workerw, "WorkerW", nullptr)))
	{
		defview = FindWindowExA(workerw, nullptr, "SHELLDLL_DefView", nullptr);
		if (defview)
		{
			listview = FindWindowExA(defview, nullptr, "SysListView32", NULL);
			if (listview) return listview;
		}
	}
	return nullptr;
}

// 使用 LVM_SETITEMPOSITION32 + 超时，移动更稳定
static BOOL MoveIcon(HWND lv, int index, int x, int y)
{
	POINT pt{ x, y };
	DWORD_PTR result = 0;
	return SendMessageTimeoutA(
		lv, LVM_SETITEMPOSITION32,
		(WPARAM)index, (LPARAM)&pt,
		SMTO_BLOCK, 100, &result
	);
}

int main()
{
	INITCOMMONCONTROLSEX icc{ sizeof(icc), ICC_LISTVIEW_CLASSES };
	InitCommonControlsEx(&icc);

	HWND lv = GetDesktopListView();
	if (!lv) return 0;

	// 关闭自动排列与对齐到网格
	LONG style = GetWindowLongA(lv, GWL_STYLE);
	if (style & LVS_AUTOARRANGE)
	{
		SetWindowLongA(lv, GWL_STYLE, style & ~LVS_AUTOARRANGE);
	}
	DWORD exStyle = ListView_GetExtendedListViewStyle(lv);
	if (exStyle & LVS_EX_SNAPTOGRID)
	{
		ListView_SetExtendedListViewStyle(lv, exStyle & ~LVS_EX_SNAPTOGRID);
	}

	// 切换为大图标视图（若支持）
	SendMessageTimeoutA(lv, LVM_SETVIEW, LV_VIEW_ICON, 0, SMTO_BLOCK, 100, nullptr);

	// 图标数量与屏幕大小
	int iconCount = (int)SendMessageA(lv, LVM_GETITEMCOUNT, 0, 0);
	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN);
	if (iconCount <= 1) return 0; // 至少需要 2 个（蛇 + 食物）

	// 网格参数
	const int cell = 80;
	const int maxLen = min(iconCount - 1, 500);

	// 隐藏多余图标（先不动用的）
	for (int i = 0; i < iconCount; ++i)
	{
		MoveIcon(lv, i, sx + 100, sy + 100);
	}

	// 蛇身、食物与方向
	POINT pos[500] = {};
	POINT food{};
	POINT dir{ 1, 0 };
	int len = min(5, maxLen);
	if (len < 1) len = 1;

	// 初始蛇身位置（从左到右放置）
	for (int i = 0; i < len; ++i)
	{
		pos[i].x = i * cell;
		pos[i].y = 0;
	}

	// 随机数与随机网格生成
	srand((unsigned int)time(nullptr));
	auto randCell = [&](int maxPixel) {
		int gridCount = maxPixel / cell;
		if (gridCount <= 1) return 0;
		return (rand() % (gridCount - 1)) * cell;
		};
	food.x = randCell(sx);
	food.y = randCell(sy);

	// 初始渲染（避免首帧堆一起）
	for (int i = 0; i < len; ++i) MoveIcon(lv, i, pos[i].x, pos[i].y);
	MoveIcon(lv, len, food.x, food.y);
	UpdateWindow(lv);

	// 主循环
	while (true)
	{
		// 方向控制
		if (GetAsyncKeyState(VK_UP) & 0x8000) { if (dir.y != 1) { dir.x = 0;  dir.y = -1; } }
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { if (dir.y != -1) { dir.x = 0;  dir.y = 1; } }
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { if (dir.x != 1) { dir.x = -1; dir.y = 0; } }
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { if (dir.x != -1) { dir.x = 1;  dir.y = 0; } }

		// 身体跟随
		for (int i = len - 1; i > 0; --i) pos[i] = pos[i - 1];

		// 头部前进
		pos[0].x += dir.x * cell;
		pos[0].y += dir.y * cell;

		// 撞墙结束
		if (pos[0].x < 0 || pos[0].x >= sx || pos[0].y < 0 || pos[0].y >= sy) break;

		// 吃到食物 -> 增长并刷新食物
		if (pos[0].x == food.x && pos[0].y == food.y)
		{
			if (len < maxLen) ++len;
			food.x = randCell(sx);
			food.y = randCell(sy);
		}

		// 渲染：蛇各节到 0..len-1，食物到 len
		for (int i = 0; i < len; ++i) MoveIcon(lv, i, pos[i].x, pos[i].y);
		MoveIcon(lv, len, food.x, food.y);
		UpdateWindow(lv);

		Sleep(120); // 帧率
	}

	// 结束时把图标移到屏幕外，避免乱序
	for (int i = 0; i < iconCount; ++i) MoveIcon(lv, i, sx + 100, sy + 100);
	return 0;
}