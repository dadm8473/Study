using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TockenSpawner : MonoBehaviour
{
    // 싱글톤
    public static TockenSpawner instance;

    private void Awake()
    {
        if (TockenSpawner.instance == null)
            TockenSpawner.instance = this;
    }

    public GameObject ballToken;
    int ballCount;

    public bool isStart = false;

    private void Update()
    {
        if(isStart == true)
        {
            //ballCount = Ball.instance.ballCount;

            StartCoroutine("BallShot");

            isStart = false;
        }
    }

    IEnumerator BallShot()
    {
        while (true)
        {
            yield return new WaitForSeconds(0.5f);

            ballCount--;
            GameObject ball = (GameObject)Instantiate(ballToken, transform);

            // 볼 카운트 다쓰면 끄기
            if (ballCount < 1)
            {
                //isEnter = false;
                //isShot = false;
                //ballCount = ballCount_temp;
                Destroy(this);
                break;
            }
        }
    }
}
