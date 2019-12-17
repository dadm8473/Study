using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControllerManager : MonoBehaviour
{
    float velocity_Y;
    Rigidbody myRigidbody;
    public int jumpPower = 15;
    int count = -1;
    int count_TapSound3 = 0;

    void Start()
    {
        // rigidbody 초기화
        myRigidbody = GetComponent<Rigidbody>();
    }
    void Update()
    {
        velocity_Y -= Time.deltaTime;
    }

    void OnCollisionEnter(Collision col) // 충돌 체크
    {
        if (col.gameObject.tag == "Ground")  // 부딪친 오브젝트의 태그가 그라운드일 경우
        {
            myRigidbody.velocity = new Vector3(0, jumpPower, 0);    // 점프

            switch (count)
            {
                case -1:
                    SoundManager.instance.PlaySound("TapSound");    // 탭 사운드 출력
                    count = -count;

                    ////if (count_TapSound3_Helper % 2 == 0)
                    //{
                    //    count_TapSound3++;
                    //    if (count_TapSound3 == 3)
                    //    {
                    //        //SoundManager.instance.PlaySound("TapSound3_2");    // 탭 사운드 출력
                    //    }

                        //    if (count_TapSound3 == 5)
                        //    {
                        //        SoundManager.instance.PlaySound("TapSound3_4");    // 탭 사운드 출력
                        //        count_TapSound3 = 1;
                        //    }
                        //}

                    break;
                case 1:
                    SoundManager.instance.PlaySound("TapSound");
                    SoundManager.instance.PlaySound("TapSound2");    // 탭 사운드 출력
                    count = -count;

                    //count_TapSound3_Helper++;
                    ////if (count_TapSound3_Helper % 2 == 0)
                    //    switch (count_TapSound3)
                    //    {
                    //        case 1:
                    //            //SoundManager.instance.PlaySound("TapSound3_1");    // 탭 사운드 출력
                    //            break;
                    //        case 2:
                    //            break;
                    //        case 3:
                    //            SoundManager.instance.PlaySound("TapSound3_3");    // 탭 사운드 출력
                    //            break;
                    //        case 4:

                    //            break;
                    //    }
                    break;
            }

            switch (count_TapSound3)
            {
                case 1:
                    SoundManager.instance.PlaySound("TapSound3_1");
                    break;
                case 4:
                    SoundManager.instance.PlaySound("TapSound3_2");
                    break;
                case 9:
                    SoundManager.instance.PlaySound("TapSound3_3");
                    break;
                case 12:
                    SoundManager.instance.PlaySound("TapSound3_4");
                    break;
            }

            count_TapSound3++;

            if (count_TapSound3 == 15)
                count_TapSound3 = 1;
        }
    }
}
