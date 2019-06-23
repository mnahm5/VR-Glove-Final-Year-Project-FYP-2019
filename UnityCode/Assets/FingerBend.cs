using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;
using UnityEngine.Networking;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class FingerBend : MonoBehaviour {
    private UdpPackage udpPackage;

    public float divider = 3;

    public GameObject[] joints = new GameObject[15];

    bool[] initialFlags = new bool[10];
    uint[] initialVals = new uint[10];
    uint[] currVals = new uint[10];

    float[] tiltZ = new float[10];
    uint[] dummyCurrent = new uint[10];

    // Use this for initialization
    void Start () {
        GameObject leftHand = GameObject.Find("LeftHand");
        udpPackage = leftHand.GetComponent<UdpPackage>();
        for (int i = 0; i < 10; ++i) initialFlags[i] = false; 
        for (int i = 0; i < 10; ++i) dummyCurrent[i] = (uint) (i+20*i);
    }
	
	// Update is called once per frame
	void Update () {
        for (int i = 0; i < 10; ++i)
        {
            if (initialFlags[i])
            {
                currVals[i] = udpPackage.flexData[i];
                //currVals[i] = dummyCurrent[i];
                //Debug.Log("Current[" + i + "] = " + currVals[i]);
                tiltZ[i] = currVals[i] - initialVals[i]; 
            }
            else
            {
                initialVals[i] = udpPackage.flexData[i];
                initialFlags[i] = true;
                //Debug.Log("Initial[" + i + "] = " + initialVals[i]);
            }
        }

        if (initialFlags[9])
        {
            int j = 0;
            for (int i = 0; i < 10; i += 2)
            {
                tiltZ[i] = (currVals[i] - initialVals[i]) / divider;
                Quaternion target1 = Quaternion.Euler(0, 0, tiltZ[i]);
                Quaternion target2 = Quaternion.Euler(0, 0, tiltZ[i + 1]);
                Quaternion target3 = Quaternion.Euler(0, 0, (tiltZ[i + 1] / 3));

                //Dampen towards the target rotations
                joints[j].transform.localRotation = Quaternion.Slerp(joints[j].transform.localRotation, target1, Time.deltaTime * 30);
                joints[j + 1].transform.localRotation = Quaternion.Slerp(joints[j + 1].transform.localRotation, target2, Time.deltaTime * 30);
                joints[j + 2].transform.localRotation = Quaternion.Slerp(joints[j + 2].transform.localRotation, target3, Time.deltaTime * 30);
                j += 3;
            }
        }
    }
}
