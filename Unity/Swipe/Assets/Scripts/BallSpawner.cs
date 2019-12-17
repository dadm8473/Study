using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallSpawner : MonoBehaviour
{
    // 싱글톤
    
    public static BallSpawner instance;
    private void Awake()
    {
        if (BallSpawner.instance == null)
            BallSpawner.instance = this;
    }

    public bool isShot = false; // 공을 발사하였는가?
    public bool isAllShot = false; // 공을 모두 발사하였는가?
    public float speed = 8f;   // 공의 속도
    public Vector3 movePos;     // 공을 날릴 좌표
    public int ballAmount;       // 공의 갯수
    public int ballCount;       // 공의 갯수

    public GameObject ball_Object;     // 공
    public List<GameObject> ball_List;  // 공 리스트

    private IEnumerator coroutine;  // 공 발사 코루틴

    Ray ray;    //레이

    void Start()
    {
        // 코루틴 초기화
        coroutine = BallShot();
        ball_List = new List<GameObject>();
        ray = new Ray();
    }

    void Update()
    {
        ray.origin = transform.position;
        ray.direction = transform.up;

        Debug.DrawRay(ray.origin, ray.direction * 10, Color.red);

        if (isShot == false)
        {
            if (Swipe.instance.isMouseClick == true)
            {
                // BallSpawner와 Target의 거리
                Debug.DrawLine(transform.position, Swipe.instance.transform.position, Color.red);

                // 이동할 방향인 좌표
                //movePos = Swipe.instance.transform.position - Swipe.instance.dragStartPos + transform.position;

                //if(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x > 0)
                //    movePos = transform.eulerAngles = new Vector3(-(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x), 0, 0);
                //else
                //    movePos = transform.eulerAngles = new Vector3(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x, 0, 0);

                //if (Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x < 0)    // 0보다 작은 경우
                //    movePos = transform.eulerAngles = new Vector3(-3, 0, 0);
                //else if(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x > 0)    // 0보다 큰경우
                //    movePos = transform.eulerAngles = new Vector3(3, 0, 0);
                //else  // 0 인 경우
                //    movePos = transform.eulerAngles = new Vector3(0, 0, 0);

                movePos = transform.eulerAngles = new Vector3(0, 0, -(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x));

                // 좌표 값 한계
                //if (movePos.x < -5)
                //    movePos.x = -5;
                //if (movePos.x > 5)
                //    movePos.x = 5;

                //if (movePos.y < 4)
                //movePos.y = 4;

                //Debug.Log(movePos);

                // Ball의 이동 경로
                Debug.DrawLine(transform.position, movePos, Color.green);
            }

            // 동작이 멈추고 클릭했을 경우 발사
            if (Input.GetMouseButtonUp(0))
            {
                // 바라보는 rotation으로 이동
                //transform.LookAt(movePos);
                movePos = transform.eulerAngles = new Vector3(0, 0, Swipe.instance.dragStartPos.x - Swipe.instance.transform.position.x);

                //if (Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x < 0)    // 0보다 작은 경우
                //    movePos = transform.eulerAngles = new Vector3(-speed, 0, 
                //        -(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x));
                //else if (Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x > 0)    // 0보다 큰경우
                //    movePos = transform.eulerAngles = new Vector3(-speed, 0, 
                //        -(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x));
                //else  // 0 인 경우
                //    movePos = transform.eulerAngles = new Vector3(-speed, 0, 0);

                movePos = transform.eulerAngles = new Vector3(-speed, 0,
                        -(Swipe.instance.transform.position.x - Swipe.instance.dragStartPos.x));

                // 공 카운트 넘겨주기
                ballCount = ballAmount;
                
                // 공 발사 코루틴 시작
                StartCoroutine(coroutine);

                // 발사 했다는 불 변수
                isShot = true;
            }
        }
        else
        {
            // 좌표를 땅에 처음 닿은 공으로 설정
            //transform.position = ball_List[0].transform.position;

            // 볼을 다 쏘고난 뒤, 마지막 볼이 땅에 닿았을 경우
            if (isAllShot == true)
            {
                if (ball_List[ball_List.Count - 1].activeSelf == false)
                {
                    isShot = false;

                    // 사용한 볼 삭제
                    for (int i = 0; i < ball_List.Count; ++i)
                        Destroy(ball_List[i]);

                    // 볼 리스트 초기화
                    ball_List.Clear();
                }
            }
        }
    }

    IEnumerator BallShot()
    {
        while (true)
        {
            // 딜레이
            yield return new WaitForSeconds(0.1f);

            // 볼 카운트 다쓰면 끄기
            if (ballCount < 1)
            {
                // 볼 다쏨
                isAllShot = true;

                StopCoroutine(coroutine);
            }
            else
            {
                // 공 생성
                GameObject ball = (GameObject)Instantiate(ball_Object, transform);
                ball_List.Add(ball);

                ballCount--;
            }
        }
    }
}
