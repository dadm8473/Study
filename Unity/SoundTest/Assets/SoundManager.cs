using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    // 싱글톤
    public static SoundManager instance;

    // Start 전
    void Awake()
    {
        // 인스턴스 없으면 생성
        if (SoundManager.instance == null)
            SoundManager.instance = this;
    }

    public void PlaySound(string snd)
    {
        // 받은 사운드 찾아서 출력
        GameObject.Find(snd).GetComponent<AudioSource>().Play();
    }
}
