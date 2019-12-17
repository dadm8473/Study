using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallToken : MonoBehaviour
{
    Rigidbody rb;   // this Rb
    Vector3 target;
    float speed;

    bool isEnter = false;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();

        target = Ball.instance.movePos;
        speed = Ball.instance.speed;

        transform.LookAt(target);
        var releaseVector = Quaternion.AngleAxis(transform.rotation.x, transform.right) * transform.forward;
        rb.velocity = releaseVector * speed;
    }

    // Update is called once per frame
    void Update()
    {
        if (isEnter == true)
        {
            // 플레이어 쪽으로 이동
            transform.LookAt(Ball.instance.transform.position);
            var releaseVector = Quaternion.AngleAxis(transform.rotation.x, transform.right) * transform.forward;
            rb.velocity = releaseVector * speed;
        }
    }

    private void OnTriggerEnter(Collider col)
    {
        // 충돌
        RaycastHit hit;

        if (Physics.Raycast(transform.position, rb.velocity, out hit))
        {
            // 바닥에 충돌할 경우
            if (col.gameObject.tag == "Ground")
            {
                // velociry 초기화
                rb.velocity -= rb.velocity;
                // 원래 공 쪽으로 돌아가기
                isEnter = true;
                // 0.5초 후에 삭제
                Destroy(this, 0.5f);
                // y값을 4.65로 줌
                transform.position = new Vector3(transform.position.x, -4.65f);
                //Debug.Log(isEnter);
                return;
            }

            //Debug.DrawRay(transform.position, -rb.velocity, Color.red, 5);

            // 움직이는 물체의 Velocity의 음수(빨강) = 입사각

            //Debug.DrawRay(transform.position, hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2, Color.blue, 5);

            // 부딛힌 물체의 표면각(파랑)

            //Debug.DrawRay(transform.position, rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2), Color.yellow, 5);

            // 빨강+파랑(노랑) = 반사각

            if(col.gameObject.tag == "Wall")
                rb.velocity = rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);

            //Debug.Log("OnTrigger");
        }
    }
}
