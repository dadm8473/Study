using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Swipe : MonoBehaviour
{
    // 싱글톤
    public static Swipe instance;

    private void Awake()
    {
        if (Swipe.instance == null)
            Swipe.instance = this;
    }

    public Vector3 dragStartPos;
    public Vector3 dragEndPos;

    Camera Camera;

    public bool isMouseClick = false;
    Vector3 mousePos;

    void Start()
    {
        // target 의 position은 ball의 position
        transform.position = BallSpawner.instance.transform.position;
        Camera = GameManager.instance.Camera;
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            dragStartPos = Input.mousePosition;
            dragStartPos = Camera.ScreenToWorldPoint(dragStartPos) + new Vector3(0, 0, 10);
            //Debug.Log(dragStartPos);

            isMouseClick = true;
        }

        if (Input.GetMouseButtonUp(0))
        {
            dragEndPos = Input.mousePosition;
            dragEndPos = Camera.ScreenToWorldPoint(dragEndPos) + new Vector3(0, 0, 10);
            //Debug.Log(dragEndPos);

            isMouseClick = false;
        }

        if(isMouseClick == true)
        {
            mousePos = Input.mousePosition;
            transform.position = Camera.ScreenToWorldPoint(mousePos) + new Vector3(0, 0, 10);

            //Debug.DrawLine(Ball.instance.transform.position, transform.position, Color.green);

            Debug.DrawLine(dragStartPos, transform.position, Color.green);
        }
        else
            Debug.DrawLine(dragStartPos, dragEndPos, Color.black);

        // 카메라 리미트
        //TargetPosLinit();
    }

    void TargetPosLinit()
    {
        // 카메라 리미트
        if (transform.position.x <= -GameManager.instance.object_Limit_X)
        {
            var temp = transform.position;
            temp.x = -GameManager.instance.object_Limit_X;
            transform.position = temp;
        }

        if (transform.position.x >= GameManager.instance.object_Limit_X)
        {
            var temp = transform.position;
            temp.x = GameManager.instance.object_Limit_X;
            transform.position = temp;
        }

        if (transform.position.y <= 0)
        {
            var temp = transform.position;
            temp.y = 0;
            transform.position = temp;
        }

        if (transform.position.y >= GameManager.instance.object_Limit_Y)
        {
            var temp = transform.position;
            temp.y = GameManager.instance.object_Limit_Y;
            transform.position = temp;
        }
    }
}
