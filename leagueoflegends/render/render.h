#pragma once

#include "../stdafx.h"

namespace render
{
	extern ImFont* imFont;

	float Distance(Vector2 vec1, Vector2 vec2);
	float Distance(Vector3 vec1, Vector3 vec2);
	Vector3 CalcAngle(Vector3 src, Vector3 dst);
	Vector3 Add(Vector3 src, Vector3 dst);
	Vector3 Subtract(Vector3 src, Vector3 dst);
	Vector3 Divide(Vector3 src, float num);
	Vector3 Multiply(Vector3 src, float num);
	float Magnitude(Vector3 vec);
	Vector3 Normalize(Vector3 src);
	Vector3 GetLine(Vector2 point1, Vector2 point2);
	Vector3 GetVector(Vector3 point1, Vector3 point2);
	float GetDistPointToLine(Vector2 point, Vector2 pointLine1, Vector2 pointLine2);
	bool IsVectorEqual(Vector3 vec1, Vector3 vec2);
	bool IsVector2Null(Vector2 vec);
	bool IsVector3Null(Vector3 vec);
	bool IsOnScreen(Vector2 pos);

	void RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center);
	void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness);
	void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness, uint32_t segments);
	void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments);
	void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags, float thickness);
	void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags);
	void RenderImage(ImTextureID pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
	void RenderImageRounded(ImTextureID pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags);
	void RenderCircleWorld(const Vector3& worldPos, int numPoints, float radius, uintptr_t color, float thickness);

	void Init();
	void Update();

	namespace scriptsrender
	{
		void Update();

		namespace cooldowns
		{
			void DrawCooldownBar(Object* obj);
			void Update();
		}

		namespace recalls
		{
			void DrawRecallFrame();
			void DrawRecall(float relativePositionOffset, std::string name, uint32_t color, bool teleport);
			void Update();
		}

		namespace debug
		{
			void DrawData(Object* obj, int index);
			void DrawObjectData();
			void DrawBoundingRadius(Object* obj);
			void DrawObjectBoundingRadius();
			void DrawCursorWorld();
			void DrawPlayerPaths();
			void Update();
		}
	}
}