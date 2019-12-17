#pragma once

extern void ChangeScene(int sceneNum);
extern float GetAngle(float x, float y);
extern int getRandomNumber(int min, int max);
extern float mainTime;

extern void Init();
extern void Term();
extern void Lost();
extern void Reset();
extern void Update(float deltaTime);
extern void Render();
extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

extern void LoadingUpdate(float deltaTime);
extern void LoadingRender();
extern bool isLoading;

extern int playerLife;
extern int attackPower;
extern int power;
extern int special;
extern int score;
extern int stage;