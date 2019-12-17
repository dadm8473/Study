using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    // 싱글톤
    public static Ball instance;

    private void Awake()
    {
        if (Ball.instance == null)
            Ball.instance = this;
    }

    Rigidbody rb;   // this Rb
    MeshRenderer rd;    // this Rd
    public Vector3 movePos;    // 움직일 좌표
    public bool isEnter = false;    // 땅에 닿았는가?
    public float speed;   // 속도
    public float alpha = 1; // 알파값
    Vector3 releaseVector; // 움직일 방향

    void Start()
    {
        // rb 받아오기
        rb = GetComponent<Rigidbody>();
        rd = GetComponent<MeshRenderer>();
        movePos = BallSpawner.instance.movePos;
        speed = BallSpawner.instance.speed;

        // 바라보고있는 방향으로 공 발사
        if (movePos.z < 0)
            releaseVector = Quaternion.AngleAxis(movePos.z, transform.right) * transform.forward;
        else if(movePos.z > 0)
            releaseVector = Quaternion.AngleAxis(-movePos.z, transform.right) * transform.forward;
        else
            releaseVector = Quaternion.AngleAxis(movePos.z, transform.right) * transform.forward;

        rb.velocity = releaseVector * speed;
    }

    void Update()
    {
        if(isEnter == true)
        {
            // 땅에 닿으면 BallSpawner으로 이동
            //transform.LookAt(BallSpawner.instance.transform);
            //var releaseVector = Quaternion.AngleAxis(transform.e.x, transform.right) * transform.forward;
            //rb.velocity = releaseVector * (speed * 2);

            transform.position = Vector3.Lerp(transform.position, BallSpawner.instance.transform.position, 0.3f);
        }

        // 리미트
        if (transform.position.x <= -GameManager.instance.object_Limit_X - 2)
        {
            var temp = transform.position;
            temp.x = -GameManager.instance.object_Limit_X + 2;
            transform.position = temp;
            rb.velocity = -rb.velocity;
        }

        if (transform.position.x >= GameManager.instance.object_Limit_X + 2)
        {
            var temp = transform.position;
            temp.x = GameManager.instance.object_Limit_X + 2;
            transform.position = temp;
            rb.velocity = -rb.velocity;
        }

        if (transform.position.y <= -1)
        {
            var temp = transform.position;
            temp.y = -1;
            transform.position = temp;
            rb.velocity = -rb.velocity;
        }

        if (transform.position.y >= GameManager.instance.object_Limit_Y + 2)
        {
            var temp = transform.position;
            temp.y = GameManager.instance.object_Limit_Y + 2;
            transform.position = temp;
            rb.velocity = -rb.velocity;
        }
    }

    private void OnTriggerEnter(Collider col)
    {
        // 충돌
        RaycastHit hit;

        if (Physics.Raycast(transform.position, rb.velocity, out hit))
        {
            // 벽에 충돌할 경우
            if (col.gameObject.tag == "Wall")
            {
                // 움직이는 물체의 Velocity의 음수(빨강) = 입사각
                Debug.DrawRay(transform.position, -rb.velocity, Color.red, 5);

                // 부딛힌 물체의 표면각(파랑)
                Debug.DrawRay(transform.position, hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2, Color.blue, 5);
                Debug.Log(hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);

                // 빨강+파랑(노랑) = 반사각
                Debug.DrawRay(transform.position, rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2), Color.yellow, 5);

                //rb.velocity = (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);

                if (-rb.velocity == rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2))
                    rb.velocity = rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2) * 2;
                else
                    rb.velocity = rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);
                //Debug.Log(rb.velocity);
            }
        }

        // 바닥에 충돌할 경우
        if (col.gameObject.tag == "Ground")
        {
            // 땅에 닿음
            isEnter = true;
            // velociry 초기화
            rb.velocity -= rb.velocity;
            //Debug.Log("Ground");
            // y값 0으로 줌
            //transform.position = new Vector3(transform.position.x, -4.7f, transform.position.z);
            return;
        }
    }

    private void OnTriggerStay(Collider col)
    {
        // 스포너에 충돌할 경우
        if (col.gameObject.tag == "Spawner")
        {
            // 삭제해줌
            if (isEnter)
                gameObject.SetActive(false);
        }
    }
}
