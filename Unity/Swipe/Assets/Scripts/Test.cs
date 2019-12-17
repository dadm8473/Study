using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    // 싱글톤
    public static Test instance;

    // Start 전
    void Awake()
    {
        // 인스턴스 없으면 생성
        if (Test.instance == null)
            Test.instance = this;
    }

    Rigidbody rb;

    Transform savePosition;

    bool isEnter = true;

    Vector3 dragStartPos;
    Vector3 dragEndPos;

    Camera Camera;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        Camera = GameObject.Find("Main Camera").GetComponent<Camera>();
        //savePosition = GetComponent<Transform>();

        //rb.AddForce(Vector3.up * 30000);
        //rb.AddForce(Vector3.left * 60000);

        //rb.velocity = new Vector3(8, 6, 0);
    }

    // Update is called once per frame
    void Update()
    {
        //if (isEnter == true)
        //{
        //    transform.position = savePosition.position;
        //    Debug.Log("Update");
        //}

        if(Input.GetMouseButtonUp(0) && isEnter == true)
        {
            rb.velocity = dragEndPos - dragStartPos;
            isEnter = false;
        }

        if(Input.GetMouseButtonDown(0))
        {
            dragStartPos = Input.mousePosition;
            dragStartPos = Camera.ScreenToWorldPoint(dragStartPos)+ new Vector3(0, 0, 10);
            Debug.Log(dragStartPos);
        }

        if(Input.GetMouseButtonUp(0))
        {
            dragEndPos = Input.mousePosition;
            dragEndPos = Camera.ScreenToWorldPoint(dragEndPos) + new Vector3(0, 0, 10);
            Debug.Log(dragEndPos);
        }
    }

    private void OnCollisionEnter(Collision col)
    {
        //if (col.gameObject.tag == "Ground")
        //{
        //    //savePosition.position = transform.position;
        //    //isEnter = true;
        //    //Debug.Log("Enter");
        //    //Debug.Log(savePosition.position);

        //    RaycastHit hit;

        //    if (Physics.Raycast(transform.position, rb.velocity, out hit))
        //    {
        //        Debug.DrawRay(transform.position, -rb.velocity, Color.red, 5);

        //        // 움직이는 물체의 Velocity의 음수(빨강) = 입사각

        //        Debug.DrawRay(transform.position, hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2, Color.blue, 5);

        //        // 부딛힌 물체의 표면각(파랑)

        //        Debug.DrawRay(transform.position, rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2), Color.yellow, 5);

        //        // 빨강+파랑(노랑) = 반사각

        //        rb.velocity = rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);
        //    }
        //}

        RaycastHit hit;

        if (Physics.Raycast(transform.position, rb.velocity, out hit))
        {
            rb.velocity -= rb.velocity;
            isEnter = true;
        }
    }

    private void OnTriggerEnter(Collider col)
    {
        RaycastHit hit;

        if (Physics.Raycast(transform.position, rb.velocity, out hit))
        {
            Debug.DrawRay(transform.position, -rb.velocity, Color.red, 5);

            // 움직이는 물체의 Velocity의 음수(빨강) = 입사각

            Debug.DrawRay(transform.position, hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2, Color.blue, 5);

            // 부딛힌 물체의 표면각(파랑)

            Debug.DrawRay(transform.position, rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2), Color.yellow, 5);

            // 빨강+파랑(노랑) = 반사각

            rb.velocity = rb.velocity + (hit.normal * Vector3.Dot(-rb.velocity, hit.normal) * 2);

            Debug.Log("OnTrigger");
        }
    }
}
