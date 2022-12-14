using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LegAngles : MonoBehaviour
{
    // 1 --> 2 --> 3 --> 4 --> 5 --> 6
    public GameObject[] FirstLegs;
    public GameObject[] SecondLegs;
    public GameObject[] ThirdLegs;
    float[] angles = new float[16];
    // Start is called before the first frame update
    void Start()
    {
        // 아두이노 코드 _esp32s3_exec 에 있는 stand를 초기 상태로 설정
        int[] stand = { 80, 100, 90, 90, 70, 70, 80, 80, 90, 90, 110, 110, 100, 100, 90, 90};
        motorSet(stand);
    }

    // Update is called once per frame
    void Update()
    {
        angles[0] = (SecondLegs[2].transform.localEulerAngles.z-360f)*-1f;  //33
        angles[1] = SecondLegs[4].transform.localEulerAngles.z;                    //32
        angles[2] = (FirstLegs[2].transform.localEulerAngles.y-360f)*-1f;      //16
        angles[3] = (FirstLegs[4].transform.localEulerAngles.y-360f)*-1f;      //17
        angles[4] = ThirdLegs[3].transform.localEulerAngles.z;                      //14
        angles[5] = ThirdLegs[1].transform.localEulerAngles.z;                      //12
        angles[6] = (SecondLegs[3].transform.localEulerAngles.z-360f)*-1f;  //13
        angles[7] = (SecondLegs[1].transform.localEulerAngles.z-360f)*-1f;   //4
        angles[8] = (FirstLegs[3].transform.localEulerAngles.y-360f)*-1f;      //2
        angles[9] = (FirstLegs[1].transform.localEulerAngles.y-360f)*-1f;      //15
        angles[10] = (ThirdLegs[0].transform.localEulerAngles.z-180f)*-1f;   //23
        angles[11] = (ThirdLegs[5].transform.localEulerAngles.z-180f)*-1f;    //22
        angles[12] = SecondLegs[0].transform.localEulerAngles.z;                  //21
        angles[13] = SecondLegs[5].transform.localEulerAngles.z;                  //19
        angles[14] = (FirstLegs[0].transform.localEulerAngles.y-360f)*-1f;    //18
        angles[15] = (FirstLegs[5].transform.localEulerAngles.y-360f)*-1f;    //5

        //설계상의 한계 반영 (다리는 18개이지만, pwm을 위한 timer가 16개)
        //4번 끝다리--> 3번 끝다리, 1번 끝다리 --> 5번 끝다리
        ThirdLegs[2].transform.localEulerAngles = ThirdLegs[3].transform.localEulerAngles;
        ThirdLegs[4].transform.localEulerAngles = ThirdLegs[0].transform.localEulerAngles;
        Debug.Log(angles[0]+", "+ angles[1] + ", " + angles[2] + ", " + angles[3] + ", " + angles[4] + ", " + angles[5] + ", " + angles[6] + ", " + angles[7] + ", " + angles[8] + ", " + angles[9] + ", " + angles[10] + ", " + angles[11] + ", " + angles[12] + ", " + angles[13] + ", " + angles[14] + ", " + angles[15]);
    }

    public void motorSet(int []arr)
    {
        SecondLegs[2].transform.localEulerAngles = motor("z", SecondLegs[2].transform.localEulerAngles, arr[0] * -1f + 360f);
        SecondLegs[4].transform.localEulerAngles = motor("z", SecondLegs[4].transform.localEulerAngles, arr[1]);
        FirstLegs[2].transform.localEulerAngles = motor("y", FirstLegs[2].transform.localEulerAngles, arr[2] * -1f + 360f);
        FirstLegs[4].transform.localEulerAngles = motor("y", FirstLegs[4].transform.localEulerAngles, arr[3] * -1f + 360f);
        ThirdLegs[3].transform.localEulerAngles = motor("z", ThirdLegs[3].transform.localEulerAngles, arr[4]);
        ThirdLegs[1].transform.localEulerAngles = motor("z", ThirdLegs[1].transform.localEulerAngles, arr[5]);
        SecondLegs[3].transform.localEulerAngles = motor("z", SecondLegs[3].transform.localEulerAngles, arr[6] * -1f + 360f);
        SecondLegs[1].transform.localEulerAngles = motor("z", SecondLegs[1].transform.localEulerAngles, arr[7] * -1f + 360f);
        FirstLegs[3].transform.localEulerAngles = motor("y", FirstLegs[3].transform.localEulerAngles, arr[8] * -1f + 360f);
        FirstLegs[1].transform.localEulerAngles = motor("y", FirstLegs[1].transform.localEulerAngles, arr[9] * -1f + 360f);
        ThirdLegs[0].transform.localEulerAngles = motor("z", ThirdLegs[0].transform.localEulerAngles, arr[10] * -1f + 180);
        ThirdLegs[5].transform.localEulerAngles = motor("z", ThirdLegs[5].transform.localEulerAngles, arr[11] * -1f + 180f);
        SecondLegs[0].transform.localEulerAngles = motor("z", SecondLegs[0].transform.localEulerAngles, arr[12]);
        SecondLegs[5].transform.localEulerAngles = motor("z", SecondLegs[5].transform.localEulerAngles, arr[13]);
        FirstLegs[0].transform.localEulerAngles = motor("y", FirstLegs[0].transform.localEulerAngles, arr[14] * -1f + 360f);
        FirstLegs[5].transform.localEulerAngles = motor("y", FirstLegs[5].transform.localEulerAngles, arr[15] * -1f + 360f);
    }

    Vector3 motor(string axis, Vector3 original, float num)
    {
        Vector3 ret = original;
        if(axis == "y")
        {
            ret.y = num;
            return ret;
        }
        else if(axis == "z")
        {
            ret.z = num;
            return ret;
        }
        else
        {
            ret.x = num;
            return ret;
        }
    }
}
