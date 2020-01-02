#pragma once

extern void ChangeScene(string sceneName);

extern void Init();
extern void Term();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);