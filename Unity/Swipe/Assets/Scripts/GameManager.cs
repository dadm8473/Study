using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    // 싱글톤
    public static GameManager instance;

    // 카메라
    public Camera Camera;

    private void Awake()
    {
        if (GameManager.instance == null)
            GameManager.instance = this;

        // 카메라 찾기
        if(Camera == null)
            Camera = GameObject.Find("Main Camera").GetComponent<Camera>();
    }

    public float object_Limit_X;
    public float object_Limit_Y;

    void Start()
    {
        //object_Limit_X = transform.position.x + 21f;
        //object_Limit_Y = transform.position.y + 25f;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
