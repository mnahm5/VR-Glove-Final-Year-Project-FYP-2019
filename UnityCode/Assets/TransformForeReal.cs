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

public class TransformForeReal : MonoBehaviour
{
    public GameObject parentJoint;
    public GameObject childJoint;
    public GameObject grandChildJoint;

    public float divider = 3;

    private float change = 0.0f;

    bool initialFlag = false;
    int initial = 0;
    int curr = 0;

    UdpClient client;
    IPEndPoint hostIP;
    Thread sensorThread;
    bool threadFlag = true;

    // Use this for initialization
    void Start()
    {
        sensorThread = new Thread(new ThreadStart(GetBendDataUdp));
        sensorThread.IsBackground = true;
        sensorThread.Start();
    }

    void GetBendDataUdp()
    {
        try
        {
            UdpClient client = new UdpClient(51220);
            client.EnableBroadcast = true;
            while (threadFlag)
            {
                IPEndPoint hostIP = new IPEndPoint(IPAddress.Any, 0);
                byte[] data = client.Receive(ref hostIP);
                string returnData = Encoding.ASCII.GetString(data);
                //if (initialFlag)
                //{
                //    curr = Convert.ToInt32(returnData);
                //}
                //else
                //{
                //    initial = Convert.ToInt32(returnData);
                //    initialFlag = true;
                //}

                Debug.Log(returnData);
            }
        }
        catch (Exception e)
        {
            Debug.Log(e);
            sensorThread.Abort();
            client.Close();
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey("right"))
        {
            change += 0.1f;
            if (change > 1f)
            { change = 1f; }
        }
        else if (Input.GetKey("left"))
        {
            change -= 0.1f;
            if (change < 0)
            { change = 0; }
        }
         if (Input.GetKey("right"))
        {
            change += 0.1f;
            if (change > 1f)
            { change = 1f; }
        }
        else if (Input.GetKey("left"))
        {
            change -= 0.1f;
            if (change < 0)
            { change = 0; }
        }

        float tiltAroundZ1 = change * 60;
        float tiltAroundZ2 = (curr - initial) / divider;
        if (tiltAroundZ2 <= 0) { tiltAroundZ2 = 0; }
        string printCurr = string.Format("{0}", tiltAroundZ2);
        //Debug.Log(printCurr);

        Quaternion target1 = Quaternion.Euler(0, 0, tiltAroundZ1);
        Quaternion target2 = Quaternion.Euler(0, 0, tiltAroundZ2);
        Quaternion target3 = Quaternion.Euler(0, 0, tiltAroundZ2 / 2);

        // Dampen towards the target rotations
        parentJoint.transform.localRotation = Quaternion.Slerp(parentJoint.transform.localRotation, target1, Time.deltaTime * 30);
        childJoint.transform.localRotation = Quaternion.Slerp(childJoint.transform.localRotation, target2, Time.deltaTime * 30);
        grandChildJoint.transform.localRotation = Quaternion.Slerp(grandChildJoint.transform.localRotation, target3, Time.deltaTime * 30);
    }

    private void OnApplicationQuit()
    {
        threadFlag = false;
        Debug.Log("Application Quit");
    }
}
