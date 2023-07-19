#include "../stdafx.h"

namespace render
{
	float Distance(Vector2 vec1, Vector2 vec2)
	{
		float x_d = (vec2.x - vec1.x);
		float y_d = (vec2.y - vec1.y);
		return sqrt((x_d * x_d) + (y_d * y_d));
	}

	float Distance(Vector3 vec1, Vector3 vec2)
	{
		float x_d = (vec2.x - vec1.x);
		float y_d = (vec2.y - vec1.y);
		float z_d = (vec2.z - vec1.z);
		return sqrt((x_d * x_d) + (y_d * y_d) + (z_d * z_d));
	}

	Vector3 CalcAngle(Vector3 src, Vector3 dst)
	{
		Vector3 angles;
		angles.x = (-(float)atan2(dst.x - src.x, dst.y - src.y)) / PI * 180.0f;
		angles.y = (atan2(dst.z - src.z, Distance(src, dst))) * 180.0f / PI;
		angles.z = 0.0f;
		return angles;
	}

	Vector3 Add(Vector3 src, Vector3 dst)
	{
		Vector3 sum;
		sum.x = src.x + dst.x;
		sum.y = src.y + dst.y;
		sum.z = src.z + dst.z;
		return sum;
	}

	Vector3 Subtract(Vector3 src, Vector3 dst)
	{
		Vector3 diff;
		diff.x = src.x - dst.x;
		diff.y = src.y - dst.y;
		diff.z = src.z - dst.z;
		return diff;
	}

	Vector3 Divide(Vector3 src, float num)
	{
		Vector3 vec;
		vec.x = src.x / num;
		vec.y = src.y / num;
		vec.z = src.z / num;

		return vec;
	}

	Vector3 Multiply(Vector3 src, float num)
	{
		Vector3 vec;
		vec.x = src.x * num;
		vec.y = src.y * num;
		vec.z = src.z * num;

		return vec;
	}

	float Magnitude(Vector3 vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	Vector3 Normalize(Vector3 src)
	{
		Vector3 vec = Divide(src, Magnitude(src));
		return vec;
	}

	Vector3 GetLine(Vector2 point1, Vector2 point2)
	{
		return Vector3(point1.y - point2.y, point2.x - point1.x, point1.x * point2.y - point2.x * point1.y);
	}

	Vector3 GetVector(Vector3 point1, Vector3 point2)
	{
		return Vector3(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
	}

	float GetDistPointToLine(Vector2 point, Vector2 pointLine1, Vector2 pointLine2)
	{
		Vector3 line = GetLine(pointLine1, pointLine2);
		return abs(line.x * point.x + line.y * point.y + line.z) / sqrt(line.x * line.x + line.y * line.y);
	}

	bool IsVectorEqual(Vector3 vec1, Vector3 vec2)
	{
		return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
	}

	bool IsVector2Null(Vector2 vec)
	{
		return vec.x == 0.0f && vec.y == 0.0f;
	}

	bool IsVector3Null(Vector3 vec)
	{
		return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f;
	}

	bool IsOnScreen(Vector2 pos)
	{
		return pos.x >= 0.0f && pos.y >= 0.0f && pos.x <= globals::windowWidth && pos.y <= globals::windowHeight;
	}

	void RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		ImVec2 textSize = imFont->CalcTextSizeA(size, FLT_MAX, 0.0f, text.c_str());

		float xOffset = (center) ? textSize.x / 2.0f : 0.0f;

		window->DrawList->AddText(imFont, size, { (position.x - xOffset) + 1.0f, (position.y + textSize.y) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), text.c_str());
		window->DrawList->AddText(imFont, size, { (position.x - xOffset) - 1.0f, (position.y + textSize.y) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), text.c_str());
		window->DrawList->AddText(imFont, size, { (position.x - xOffset) + 1.0f, (position.y + textSize.y) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), text.c_str());
		window->DrawList->AddText(imFont, size, { (position.x - xOffset) - 1.0f, (position.y + textSize.y) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), text.c_str());

		window->DrawList->AddText(imFont, size, { position.x - xOffset, position.y + textSize.y }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), text.c_str());
	}

	void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddLine(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), thickness);
	}

	void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness, uint32_t segments)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddCircle(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments, thickness);
	}

	void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments);
	}

	void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddRect(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags, thickness);
	}

	void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddRectFilled(from, to, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	}

	void RenderImage(ImTextureID pTexture, const ImVec2& from, const ImVec2& to, uint32_t color)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddImage(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }));
	}

	void RenderImageRounded(ImTextureID pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		window->DrawList->AddImageRounded(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	}

	void RenderCircleWorld(const Vector3& worldPos, int numPoints, float radius, uintptr_t color, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (float)((color >> 24) & 0xff);
		float r = (float)((color >> 16) & 0xff);
		float g = (float)((color >> 8) & 0xff);
		float b = (float)((color) & 0xff);

		numPoints = min(numPoints, 49);
		ImVec2 points[50];

		float step = 6.2831f / numPoints;
		float theta = 0.f;
		for (int i = 0; i < numPoints; i++, theta += step)
		{
			Vector3 worldSpace = { worldPos.x + radius * cos(theta), worldPos.y, worldPos.z - radius * sin(theta) };
			ImVec2 screenSpace = functions::WorldToScreen(worldSpace).ToImVec();

			points[i] = screenSpace;
		}

		points[numPoints] = points[0];

		window->DrawList->AddPolyline(points, numPoints, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), true, thickness);
	}
}