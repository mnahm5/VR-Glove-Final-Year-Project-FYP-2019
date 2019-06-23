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

public class UdpPackage : MonoBehaviour {

    // General Udp
    private UdpClient UdpClient;
    private Thread sensorThread;
    private bool threadFlag = true;
    public bool udpConnectionReady = false;

    // Udp IPs and Ports
    private IPEndPoint udpSender;
    private IPEndPoint board;
    private int localPort = 51220;

    // Orientation
    public float pitch, roll, yaw;

    // Flex Data
    public uint[] flexData = new uint[10];

	// Use this for initialization
	void Start () {
        UdpClient = new UdpClient(localPort);

        sensorThread = new Thread(new ThreadStart(GetUdpData));
        sensorThread.IsBackground = true;
        sensorThread.Start();
        //Debug.Log("not getting udp data btw");
    }
	
	// Update is called once per frame
	void Update () {
        if (udpConnectionReady)
        {
            // start doing stuff
        }
	}

    public void SendUdp(string message)
    {
        Debug.Log(message);
        if (udpConnectionReady)
        {
            Byte[] sendBytes = Encoding.ASCII.GetBytes(message);
            Debug.Log("SendUdp - Board Address = " + board);
            try
            {
                UdpClient.Send(sendBytes, sendBytes.Length, board);
            }
            catch (Exception e)
            {
                Debug.Log(e);
            }
        }
        else
            Debug.Log("Did not send packet");
    }

    private void GetUdpData()
    {
        try
        {
            UdpClient.EnableBroadcast = true;
            while (threadFlag)
            {
                udpSender = new IPEndPoint(IPAddress.Any, 0);
                byte[] data = UdpClient.Receive(ref udpSender);
                string returnData = Encoding.ASCII.GetString(data);

                ProcessUdpData(returnData);
            }
        }
        catch (Exception e)
        {
            Debug.Log(e);
            sensorThread.Abort();
            UdpClient.Close();
        }
    }

    private void ProcessUdpData(string packetData)
    {
        //Debug.Log(packetData);
        if (packetData.CompareTo("Ready") != 0)
        {
            string[] data = packetData.Split(':');
            switch (data[0])
            {
                case "O":
                    pitch = float.Parse(data[1]);
                    roll = float.Parse(data[2]);
                    yaw = float.Parse(data[3]);
                    break;
                case "F":
                    for (int i = 1; i < data.Length; i++)
                    {
                        flexData[i-1] = (uint) int.Parse(data[i], System.Globalization.NumberStyles.HexNumber);
                    }
                    break;
                default:
                    Debug.Log(data);
                    break;
            }
        }
        else
        {
            udpConnectionReady = true;
            board = udpSender;
            SendUdp("Ready");
        }
    }

    private void OnApplicationQuit()
    {
        threadFlag = false;
    }
}
