#include "../stdafx.h"

namespace render
{
	ImFont* imFont = NULL;

	void Init()
	{
		ImGuiIO& io = ImGui::GetIO();

		io.Fonts->AddFontDefault();
		imFont = io.Fonts->AddFontDefault();
	}

	void Update()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::Begin("transparentwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

		scriptsrender::Update();

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}

	namespace scriptsrender
	{
		void Update()
		{
			if (settings::GetBool("cooldowns", "enabled")) cooldowns::Update();
			if (settings::GetBool("recalls", "enabled")) recalls::Update();
			debug::Update();
		}
		
		namespace cooldowns
		{
			float width = 128.0f;
			float height = 8.0f;
			float cdWidth = 20.0f;
			float cdHeight = 6.0f;

			float yOffset = 0.0f;
			float xOffset = -width / 2.0f + 8.0f;

			void DrawCooldownBar(Object* obj)
			{
				Vector2 screenPos = functions::GetHpBarPosition(obj);

				Vector2 basePos = Vector2(screenPos.x + xOffset, screenPos.y + yOffset);
				
				Vector2 innerBorderAngle1 = Vector2(basePos.x, basePos.y);
				Vector2 innerBorderAngle2 = Vector2(innerBorderAngle1.x + width - 1.0f, innerBorderAngle1.y + height - 1.0f);

				Vector2 middleBorderAngle1 = Vector2(innerBorderAngle1.x - 1, innerBorderAngle1.y - 1);
				Vector2 middleBorderAngle2 = Vector2(innerBorderAngle2.x + 1, innerBorderAngle2.y + 1);

				Vector2 outerBorderAngle1 = Vector2(middleBorderAngle1.x - 1, middleBorderAngle1.y - 1);
				Vector2 outerBorderAngle2 = Vector2(middleBorderAngle2.x + 1, middleBorderAngle2.y + 1);

				RenderRectFilled(outerBorderAngle1.ToImVec(), outerBorderAngle2.ToImVec(), COLOR_DARK_TRANSPARENT, 0.0f, 0);
				RenderRectFilled(middleBorderAngle1.ToImVec(), middleBorderAngle2.ToImVec(), COLOR_GRAY, 0.0f, 0);
				RenderRectFilled(innerBorderAngle1.ToImVec(), innerBorderAngle2.ToImVec(), COLOR_DARK, 0.0f, 0);

				for (int i = 0; i < 6; i++) {
					Vector2 spellAngle1 = Vector2(innerBorderAngle1.x + i * (cdWidth + 1.0f) + 1.0f, innerBorderAngle1.y + 1.0f);
					Vector2 spellAngle2 = Vector2(innerBorderAngle1.x + (i + 1) * (cdWidth + 1.0f), innerBorderAngle1.y + cdHeight);

					Spell* spell = obj->GetSpellById(i);
					float relativeCooldown = spell->GetRelativeCooldown();

					spellAngle2.x -= relativeCooldown * cdWidth;

					uint32_t color = relativeCooldown == 0.0f ? COLOR_LIGHT_GREEN : COLOR_ORANGE;
					RenderRectFilled(spellAngle1.ToImVec(), spellAngle2.ToImVec(), color, 0.0f, 0);
				}
			}

			void Update()
			{
				for (auto obj : *globals::heroManager)
				{
					if (obj->IsAlive() && obj->IsVisible()) DrawCooldownBar(obj);
				}
			}
		}

		namespace recalls
		{
			using namespace globals::scripts::recalls;

			float width = 416.0f;
			float height = 12.0f;

			float yOffset = 275.0f;

			float nameSize = 18.0f;

			Vector2 topLeft;
			Vector2 bottomRight;

			void DrawRecallFrame()
			{
				RenderRect(topLeft.ToImVec(), bottomRight.ToImVec(), COLOR_WHITE, 0.0f, NULL, 2.0f);
			}

			void DrawRecall(float relativePositionOffset, std::string name, uintptr_t color, bool teleport)
			{
				Vector2 bottomPos = Vector2(topLeft.x + width * relativePositionOffset, bottomRight.y);
				Vector2 topPos = Vector2(bottomPos.x, bottomPos.y - height);
				Vector2 namePos = Vector2(topPos.x, topPos.y - nameSize * 2 - 5.0f);
				Vector2 teleportPos = Vector2(namePos.x, namePos.y - nameSize - 1.0f);

				RenderLine(topPos.ToImVec(), bottomPos.ToImVec(), color, 2.0f);
				RenderText(name, namePos.ToImVec(), nameSize, color, true);
				if (teleport) RenderText("TP", teleportPos.ToImVec(), nameSize, color, true);
			}

			void Update()
			{
				float gameTime = functions::GetGameTime();

				float screenXCenter = globals::windowWidth / 2.0f;
				topLeft = Vector2(screenXCenter - width / 2.0f, globals::windowHeight - yOffset - height);
				bottomRight = Vector2(screenXCenter + width / 2.0f, globals::windowHeight - yOffset);

				if (recallList.size()) DrawRecallFrame();

				for (RecallInfo recallInfo : recallList)
				{
					float maxRecallTime = (recallInfo.state == RecallState::RECALLING || recallInfo.state == RecallState::RECALLING_FINISHED) ? 8.0f : 4.0f;
					maxRecallTime -= timeBuffer;
					float relativePositionOffset = max(0.0f, 1.0f - ((gameTime - recallInfo.startTime) / maxRecallTime));
					uintptr_t recallColor = (recallInfo.state == RecallState::RECALLING || recallInfo.state == RecallState::TELEPORTING) ? COLOR_WHITE : COLOR_RED;
					bool teleporting = (recallInfo.state == RecallState::TELEPORTING || recallInfo.state == RecallState::TELEPORTING_FINISHED) ? true : false;
					DrawRecall(relativePositionOffset, recallInfo.name, recallColor, teleporting);
				}
			}
		}

		namespace debug
		{
			void DrawData(Object* obj, int index)
			{
				Vector2 screenPos = functions::WorldToScreen(obj->GetPosition());
				if (!IsOnScreen(screenPos)) return;
				RenderText(obj->GetName(), (screenPos - Vector2(0.0f, 22.0f)).ToImVec(), 18.0f, COLOR_WHITE, true);
				RenderText("List id: " + std::to_string(index), functions::WorldToScreen(obj->GetPosition()).ToImVec(), 18.0f, COLOR_WHITE, true);
			}

			void DrawObjectData()
			{
				for (int i = 0; i < globals::minionManager->GetListSize(); i++)
				{
					auto obj = globals::minionManager->GetIndex(i);
					if (obj->IsAlive() && obj->IsVisible())
						DrawData(obj, i);
				}

				for (int i = 0; i < globals::heroManager->GetListSize(); i++)
				{
					auto obj = globals::heroManager->GetIndex(i);
					if (obj->IsAlive() && obj->IsVisible())
						DrawData(obj, i);
				}
			}

			void DrawBoundingRadius(Object* obj)
			{
				Vector2 screenPos = functions::WorldToScreen(obj->GetPosition());
				if (!IsOnScreen(screenPos)) return;
				RenderCircleWorld(obj->GetPosition(), 20, obj->GetBoundingRadius(), COLOR_WHITE, 1.0f);
			}

			void DrawObjectBoundingRadius()
			{
				auto pool = globals::minionManager;
				for (int i = 0; i < 2; ++i)
				{
					for (int i = 0; i < pool->GetListSize(); i++)
					{
						auto obj = pool->GetIndex(i);
						if (obj->IsAlive() && obj->IsVisible())
							DrawBoundingRadius(obj);
					}
					pool = globals::heroManager;
				}
			}

			void Update()
			{
				if (settings::GetBool("debug", "draw object data")) DrawObjectData();
				if (settings::GetBool("debug", "draw bounding radius")) DrawObjectBoundingRadius();
			}
		}
	}
}